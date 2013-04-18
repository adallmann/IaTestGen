/*
 *    IaTestGen - Interval arithmetic test generator
 *    Copyright 2013
 *
 *    Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
 *    Institute of Computer Science,
 *    University of Wuerzburg, Germany
 *
 *    Michael Jedich (m.jedich@gmail.com)
 *    University of Wuerzburg, Germany
 *
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
package de.uniwue.info2.generator;

import static de.uniwue.info2.generator.cases.PlaceHolder.ARITHMETIC_EVAL;
import static de.uniwue.info2.generator.cases.PlaceHolder.ARITHMETIC_LIB_IMPORTS;
import static de.uniwue.info2.generator.cases.PlaceHolder.TEST_LIB_IMPORTS;
import static de.uniwue.info2.generator.cases.PlaceHolder.VAR_ARGS;
import static de.uniwue.info2.generator.cases.PlaceHolder.ASSERTS;
import static de.uniwue.info2.generator.cases.PlaceHolder.CALCULATED_OUTPUT;
import static de.uniwue.info2.generator.cases.PlaceHolder.CUSTOM_METHODS;
import static de.uniwue.info2.generator.cases.PlaceHolder.DYNAMIC_TEST_METHODS;
import static de.uniwue.info2.generator.cases.PlaceHolder.EXPECTED_OUTPUT;
import static de.uniwue.info2.generator.cases.PlaceHolder.HEAD_COMMENT;
import static de.uniwue.info2.generator.cases.PlaceHolder.INTERVAL_NAME;
import static de.uniwue.info2.generator.cases.PlaceHolder.INTERVAL_TYPE;
import static de.uniwue.info2.generator.cases.PlaceHolder.LANGUAGE_IMPORTS;
import static de.uniwue.info2.generator.cases.PlaceHolder.LOWER_VALUE;
import static de.uniwue.info2.generator.cases.PlaceHolder.NAME;
import static de.uniwue.info2.generator.cases.PlaceHolder.PARAM_TYPE;
import static de.uniwue.info2.generator.cases.PlaceHolder.TEST_CASES;
import static de.uniwue.info2.generator.cases.PlaceHolder.TEST_CASE_COMMENTS;
import static de.uniwue.info2.generator.cases.PlaceHolder.TEST_CASE_NAME;
import static de.uniwue.info2.generator.cases.PlaceHolder.TYPE;
import static de.uniwue.info2.generator.cases.PlaceHolder.UPPER_VALUE;
import static de.uniwue.info2.generator.cases.PlaceHolder.VALUE;
import static de.uniwue.info2.generator.cases.PlaceHolder.getID;
import static de.uniwue.info2.generator.cases.PlaceHolder.inputName;
import static de.uniwue.info2.generator.cases.PlaceHolder.outputName;
import static de.uniwue.info2.generator.cases.PlaceHolder.outputType;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.commons.lang.StringUtils;

import de.uniwue.info2.generator.cases.ArithmeticLibrarySpecification;
import de.uniwue.info2.generator.cases.LanguageSpecification;
import de.uniwue.info2.generator.cases.UnitTestLibrarySpecification;
import de.uniwue.info2.numerics.FloatingPoint;
import de.uniwue.info2.operations.Endpoints;
import de.uniwue.info2.operations.GenericParameter;
import de.uniwue.info2.operations.Interval;
import de.uniwue.info2.operations.Operation;
import de.uniwue.info2.operations.Set;
import de.uniwue.info2.parser.DSLParser;
import de.uniwue.info2.parser.ParseException;

/**
 * This class generated unit-tests for all given language-specifications.
 *
 * @author Michael Jedich
 *
 */
public class TestcaseGenerator {

	// list of operations specified by Domain Specific Language
	private OperationsPool operations_;

	private static final String DSL_PARSER_AUTHORS = DSLParser.getParserAuthors();
	private static final String DSL_PARSER_VERSION = DSLParser.getParserVersion();
	private static final String DSL_PARSER_DESCRIPTION = DSLParser.getParserDescription();

	private String dslAuthors_;
	private String dslVersion_;
	private String dslDescription_;

	// output folder
	private File outputFolder_;
	// generated string to write in test-file
	private String currentBuild_;
	private BufferedWriter currentFileWriter_, currentLogWriter_;

	// current language specification (c++, python, etc.)
	private LanguageSpecification currentLanguageSpecification_;
	private ArithmeticLibrarySpecification currentArithmeticLibrary_;
	private UnitTestLibrarySpecification currentUnitTestLibrary_;

	// translations for current language specification
	private HashMap<Class<?>, String[]> currentTypeTranslation_;
	private HashMap<String, String> currentOperationsTranslationTable_;
	private HashMap<String, String> currentMixedTypesOperationsTranslationTable_;
	private HashMap<Boolean, String> currentBooleanTranslation_;

	private HashMap<Class<?>, String[]> currentPositiveInfinityTable_;
	private HashMap<Class<?>, String[]> currentNegativeInfinityTable_;
	private String[] currentEmptyIntervalTranslation_;
	private String[] currentEntireIntervalTranslation_;

	private String lineComment_;
	private Boolean littleEndian_;
	private Class<?> currentMixedType;

	private static final DecimalFormat INDEX = new DecimalFormat("00");

	// name for testfunctions, at the end a counter is being added
	private static final String TESTCASE = "test_";

	/**
	 * Generator for unit-tests.
	 *
	 * @param dsl
	 *         Domain Specific Language
	 * @param output
	 *         Output-folder, where all files are generated
	 */
	public TestcaseGenerator(File dsl, File output) {
		// instantiate dsl parser (generated by JavaCC)
		try {
			DSLParser parser = new DSLParser(dsl);
			// get all operations extracted from dsl by our parser
			this.operations_ = parser.parse();
			// set output folder
			this.outputFolder_ = output;
			// get dsl informations from head block comment
			this.dslAuthors_ = parser.getDslAuthors();
			this.dslVersion_ = parser.getDslVersion();
			this.dslDescription_ = parser.getDslDescription();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (ParseException e) {
			e.printStackTrace();
		}
	}

	/**
	 * Generate unit-tests for given language-specification.
	 *
	 * @param targetLanguage
	 *         the language-specification you want to generate unit-tests for.
	 * @param useOptionalOperations
	 *         if true, optional operations are also generated
	 * @return true if unit-tests were successfully generated
	 */
	public boolean generateUnitTest(LanguageSpecification targetLanguage, Boolean useOptionalOperations, List<String> optionalExceptions,
			Boolean littleEndian) {
		// log operations which are not supported by current language
		// specification
		StringBuffer log;
		// given language-specification
		this.currentLanguageSpecification_ = targetLanguage;
		// get language-specific primitive-types translations (e.g. short, int,
		// float, boolean
		// ...)
		this.currentTypeTranslation_ = currentLanguageSpecification_.getTypesTranslation();
		// get boolean translation (true, false)
		this.currentBooleanTranslation_ = currentLanguageSpecification_.getBooleanTranslation();

		// get line comment definition
		this.lineComment_ = this.currentLanguageSpecification_.getLineCommentToken();

		this.littleEndian_ = littleEndian;

		// testfunctions counter, used for function-names
		short currentTestNumber = 1;

		// starts with available unit-test libraries
		for (UnitTestLibrarySpecification uSpec : this.currentLanguageSpecification_.getUnitTestLibraryList()) {
			this.currentUnitTestLibrary_ = uSpec;
			// then iterates through arithmetic libraries
			for (ArithmeticLibrarySpecification aSpec : this.currentLanguageSpecification_.getArithmeticLibraryList()) {
				log = new StringBuffer();

				this.currentArithmeticLibrary_ = aSpec;
				// get translations for negative and positive infinity-limits
				this.currentPositiveInfinityTable_ = this.currentArithmeticLibrary_.getPositiveInfinityTranslation();
				this.currentNegativeInfinityTable_ = this.currentArithmeticLibrary_.getNegativeInfinityTranslation();

				// add interval translation from arithmetic library
				this.currentTypeTranslation_.put(Interval.class, aSpec.getIntervalTranslation());
				this.currentEmptyIntervalTranslation_ = aSpec.getEmptyIntervalTranslation();
				this.currentEntireIntervalTranslation_ = aSpec.getEntireIntervalTranslation();

				// add all operation-translations
				this.currentOperationsTranslationTable_ = aSpec.getOperationsTranslation();

				this.currentMixedTypesOperationsTranslationTable_ = aSpec.getMixedTypesOperationsTranslation();
				// add operations to get lower and upper limit from intervall
				this.currentOperationsTranslationTable_.put("intervalLowerLimit", aSpec.getIntervalLowerLimit());
				this.currentOperationsTranslationTable_.put("intervalUpperLimit", aSpec.getIntervalUpperLimit());

				// get main program code-sequence
				this.currentBuild_ = this.currentLanguageSpecification_.getCodeSequence();

				// insert head comment with authors, version and description
				this.currentBuild_ = replacePlaceHolder(this.currentBuild_, HEAD_COMMENT, this.getHeadComment());

				// inserts imports and definitions from current
				// LanguageSpecification-subclass
				this.currentBuild_ = replacePlaceHolder(this.currentBuild_, LANGUAGE_IMPORTS,
						this.currentLanguageSpecification_.getImportsAndDefinitions());

				// inserts imports and definitions from current
				// ArithmeticLibrarySpecification-subclass
				this.currentBuild_ = replacePlaceHolder(this.currentBuild_, ARITHMETIC_LIB_IMPORTS, aSpec.getImportsAndDefinitions());

				// inserts imports and definitions from current
				// ArithmeticLibrarySpecification-subclass
				this.currentBuild_ = replacePlaceHolder(this.currentBuild_, TEST_LIB_IMPORTS, uSpec.getImportsAndDefinitions());

				// inserts custom methods from current
				// LanguageSpecification-subclass
				this.currentBuild_ = replacePlaceHolder(this.currentBuild_, CUSTOM_METHODS,
						this.currentLanguageSpecification_.getLanguageCustomMethods());

				// get program code-sequence of test-case-section
				this.currentBuild_ = replacePlaceHolder(this.currentBuild_, TEST_CASES, uSpec.getCodeSequence());

				// write all test methods into this string
				String testMethods = "";

				// iterate through all given operations
				Iterator<Operation> operationIterator = this.operations_.getOperations();
				while (operationIterator.hasNext()) {
					Operation operation = operationIterator.next();

					// given mixed type
					this.currentMixedType = operation.getMixedType();
					boolean mixed_types = checkOperationForMixType(operation);

					// testing if operation is implemented
					if ((this.currentOperationsTranslationTable_.containsKey(operation.getName()) && !mixed_types)
							|| (this.currentMixedTypesOperationsTranslationTable_.containsKey(operation.getName()) && mixed_types)) {

						// check if recommended operations are marked for generation
						// elaboate if block for more clarity
						boolean generateCurrentOp = false;
						if (operation.isRequired()) {
							generateCurrentOp = true;
						} else if (useOptionalOperations && !optionalExceptions.contains(operation.getName())) {
							generateCurrentOp = true;
						} else if (!useOptionalOperations && optionalExceptions.contains(operation.getName())) {
							generateCurrentOp = true;
						}

						if (generateCurrentOp) {
							Set currentSetConfig = operation.getSetRelation();
							boolean isNegated = operation.isNegated();
							// get raw test-method from unit-test-library
							testMethods += uSpec.getTestMethod();

							// add comment provided by dsl to current operation
							String operationComments = getOperationComment(operation);
							testMethods = replacePlaceHolder(testMethods, TEST_CASE_COMMENTS, operationComments);

							// build test-case name from operations information
							String testcaseName = TESTCASE + INDEX.format(currentTestNumber++);
							String operationName = "_" + operation.getName().toLowerCase().replaceAll("[^a-z]", "");
							if (!operationName.equals("_")) {
								testcaseName += operationName;
							}

							// insert one test method with current operation
							// name
							testMethods = replacePlaceHolder(testMethods, TEST_CASE_NAME, testcaseName);

							// get input and output parameter of current
							// operation
							List<GenericParameter<?>> input_parameter = operation.getInputList();
							List<GenericParameter<?>> output_parameter = operation.getOutputList();

							// type declarations defined by current language
							// specification
							String declarations = "";
							// assert string given by unit-test-library
							String assertString = "";
							// raw operation string by name
							String function = "";

							if (mixed_types) {
								function = this.currentMixedTypesOperationsTranslationTable_.get(operation.getName());
							} else {
								function = this.currentOperationsTranslationTable_.get(operation.getName());
							}

							if (function == null) {
								throw new NullPointerException("function-translation is null!");
							}

							String var_arguments = "";
							// declare all input parameter
							for (int i = 0; i < input_parameter.size(); i++) {
								GenericParameter<?> input = input_parameter.get(i);

								String inputName = "";
								if (input_parameter.size() < 2) {
									inputName = "input";
								}
								else {
									inputName = "input_" + INDEX.format(i + 1);
								}

								// add to comment, that input parameter was
								// defined
								declarations += this.lineComment_ + " input parameter " + (i + 1) + ":" + "\n";
								if (input.hasType(Interval.class)) {
									Interval<?> interval = (Interval<?>) input.getValue();

									if (interval.isEmpty()) {
										declarations += getNewIntervalString(interval, inputName, true, false);
									}
									else if (interval.isEntire()) {
										declarations += getNewIntervalString(interval, inputName, false, true);
									}
									else {
										declarations += getNewIntervalString(interval, inputName, false, false);
									}

								} else {
									declarations += getParameterString(input, inputName);
								}

								if (function.contains(inputName(i + 1))) {
									function = function.replace(inputName(i + 1), inputName);
								} else if (function.contains(VAR_ARGS)) {
									if (function.split(VAR_ARGS).length > 1) {
										System.err.println("only one variable arguments parameter is possible");
									} else {
										var_arguments += aSpec.getParameterSeparator() + " " + inputName;
									}
								}
							}

							if (!var_arguments.isEmpty()) {
								function = function.replace(VAR_ARGS, var_arguments);
							} else {
								function = function.replace(VAR_ARGS, "");
							}

							// declare all output parameter
							for (int i = 0; i < output_parameter.size(); i++) {
								GenericParameter<?> output = output_parameter.get(i);

								String expectedOutputName = "";
								String outputName = "";

								if (output_parameter.size() < 2) {
									expectedOutputName = "output";
									outputName = "lib_output";
								}
								else {
									expectedOutputName = "output_" + INDEX.format(i + 1);
									outputName = "lib_output_" + INDEX.format(i + 1);
								}

								String type = "";

								// add to comment, that output parameter was
								// defined
								declarations += this.lineComment_ + " expected output parameter " + (i + 1) + ":" + "\n";
								assertString += "\n" + this.lineComment_ + " assert function for output " + (i + 1) + ":";

								if (output.hasType(Interval.class)) {
									Interval<?> interval = (Interval<?>) output.getValue();
									// get type translation from current
									// language-specification
									type = this.currentTypeTranslation_.get(interval.getTypeClass())[0];

									if (interval.isEmpty()) {
										declarations += getNewIntervalString(interval, expectedOutputName, true, false);
									}
									else if (interval.isEntire()) {
										declarations += getNewIntervalString(interval, expectedOutputName, false, true);
									}
									else {
										declarations += getNewIntervalString(interval, expectedOutputName, false, false);
									}

									// get interval translation from current
									// arithmetic-library-specification
									String intervalType = this.currentTypeTranslation_.get(((Interval<?>) output.getValue()).getTypeClass())[0];
									
									if (interval.isEmpty()) {
										assertString += getAssertFunctionForEmptyInterval(expectedOutputName, outputName, currentSetConfig, isNegated);
									}
									else if (interval.isEntire()) {
										assertString += getAssertFunctionForEntireInterval(expectedOutputName, outputName, currentSetConfig, isNegated);
									}
									else {
										assertString += getAssertFunctionForInterval(intervalType, expectedOutputName, outputName, currentSetConfig, isNegated);
									}

								} else {
									declarations += getParameterString(output, expectedOutputName);
									type = this.currentTypeTranslation_.get(output.getTypeClass())[0];
									assertString += "\n" + getAssertString(expectedOutputName, outputName, null, isNegated) + "\n";
								}
								function = function.replace(outputName(i + 1), outputName);
								String[] intervalTranslation = this.currentTypeTranslation_.get(output.getTypeClass());
								function = function.replace(outputType(i + 1), intervalTranslation[0].replace(INTERVAL_TYPE, type));
							}
							// add comment to current operation function
							declarations += "\n" + this.lineComment_ + " operation to test: " + operation.getName();
							declarations += "\n" + function;
							testMethods = replacePlaceHolder(testMethods, ARITHMETIC_EVAL, declarations);
							testMethods = replacePlaceHolder(testMethods, ASSERTS, assertString);
							testMethods += "\n\n";
						}
					} else {
						String error = "";
						if (!mixed_types) {
							error = "Operation with name: \"" + operation.getName() + "\" is not implemented! \n";
						} else {
							error = "Mixed Type operation with name: \"" + operation.getName() + "\" is not implemented! \n";
						}
						log.append(error);
						System.err.println(error);
					}
				}

				// insert generated testcase-functions
				this.currentBuild_ = replacePlaceHolder(currentBuild_, DYNAMIC_TEST_METHODS, testMethods);

				// build filename for current language specification
				String outputFileName = (this.currentLanguageSpecification_.getOptionName() + "_" + this.currentUnitTestLibrary_.getOptionName())
						.toLowerCase().replace("^[a-z0-9_]", "_") + "_" + this.currentArithmeticLibrary_.getOptionName()

				+ "." + this.currentLanguageSpecification_.getExtension();
				File outputFile = new File(this.outputFolder_, outputFileName);

				try {
					// if old file exists, backup it with current time in
					// filename
					if (outputFile.exists()) {
						backUpOldFile(outputFile);
					}
					// write file
					this.currentFileWriter_ = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(new File(outputFolder_, outputFileName))));

					if (log.length() > 2) {
						this.currentLogWriter_ = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(new File(outputFolder_, outputFileName
								+ ".log"))));
						this.currentLogWriter_.write(log.toString());
						this.currentLogWriter_.flush();
					}

					this.currentFileWriter_.write(currentBuild_.toString());
					this.currentFileWriter_.flush();
				} catch (FileNotFoundException e) {
					e.printStackTrace();
				} catch (IOException e) {
					e.printStackTrace();
				}

				this.currentTypeTranslation_ = currentLanguageSpecification_.getTypesTranslation();
			}
		}

		try {
			if (this.currentLogWriter_ != null) {
				this.currentLogWriter_.close();
			}
			if (this.currentFileWriter_ != null) {
				this.currentFileWriter_.close();
				return true;
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		return false;
	}

	private boolean checkOperationForMixType(Operation operation) {
		List<GenericParameter<?>> input = operation.getInputList();
		List<GenericParameter<?>> output = operation.getOutputList();
		boolean isMixedType = (checkParameterForMixedType(input) || checkParameterForMixedType(output));

		this.currentMixedType = operation.getMixedType();
		if (this.currentMixedType != null && output.size() == 1) {
			if (output.get(0).hasType(Interval.class)) {
				Interval<?> interval = (Interval<?>) output.get(0).getValue();
				if (!interval.hasType(this.currentMixedType)) {
					throw new IllegalArgumentException("\nERROR: Operation with name: \"" + operation.getName()
							+ "\" was declared with mixed types,\nbut doesn't use the declared output-parameter-type: " + this.currentMixedType.getSimpleName()
							+ "\n");
				}
			}
		}

		if (this.currentMixedType != null) {
			if (!isMixedType) {
				System.err.println("NOTICE: Operation with name: \"" + operation.getName()
						+ "\" was declared with mixed types,\nbut actually has no mixed types!\n");
			}
		} else {

		}
		return isMixedType;
	}

	private boolean checkParameterForMixedType(List<GenericParameter<?>> parameter) {

		for (int i = 0; i < parameter.size(); i++) {
			GenericParameter<?> input = parameter.get(i);
			if (input.hasType(Interval.class)) {
				Interval<?> interval = (Interval<?>) input.getValue();
				if (this.currentMixedType == null) {
					this.currentMixedType = interval.getTypeClass();
				} else if (!interval.hasType(this.currentMixedType)) {
					return true;
				}
			}
		}
		return false;
	}

	/**
	 * Get blockcomment for given operation.
	 *
	 * @param op
	 *         the operation
	 * @return blockcomment containing operation-infos
	 */
	private String getOperationComment(Operation op) {
		StringBuffer comment = new StringBuffer();
		comment.append(getSingleCommentTag("name", op.getName()));
		comment.append(getSingleCommentTag("description", op.getDescription()));
		comment.append(getSingleCommentTag("required", String.valueOf(op.isRequired())));
		return comment.toString();
	}

	/**
	 * Get first blockcomment of generated unit-test-file.
	 *
	 * @return blockcomment with parser and dsl-information
	 */
	private String getHeadComment() {
		StringBuffer comment = new StringBuffer();
		comment.append(this.lineComment_ + " " + StringUtils.repeat("*", 60) + "\n");
		comment.append(getSingleCommentTag("parser_description", DSL_PARSER_DESCRIPTION));
		comment.append(getSingleCommentTag("parser_authors", DSL_PARSER_AUTHORS));
		comment.append(getSingleCommentTag("parser_version", DSL_PARSER_VERSION));
		comment.append(this.lineComment_ + " " + StringUtils.repeat("*", 60) + "\n");
		comment.append(getSingleCommentTag("dsl_description", this.dslDescription_));
		comment.append(getSingleCommentTag("dsl_authors", this.dslAuthors_));
		comment.append(getSingleCommentTag("dsl_version", this.dslVersion_));
		comment.append(this.lineComment_ + " " + StringUtils.repeat("*", 60) + "\n");
		return comment.toString();
	}

	/**
	 * Generates single comment-string.
	 *
	 * @param description
	 *         given description
	 * @param commentString
	 *         given comment string
	 * @return single comment-string
	 */
	private String getSingleCommentTag(String description, String commentString) {
		String tag = "";
		if (commentString != null) {
			if (!commentString.trim().isEmpty()) {
				tag = this.lineComment_ + " @" + description + "\n" + this.lineComment_ + " \t\t"
						+ commentString.trim().replace("\n", "\n" + this.lineComment_ + " \t\t") + "\n";
			}
		}
		return tag;
	}

	/**
	 * Assemles an assert function.
	 *
	 * @param type
	 *         current type
	 * @param expectedOutputName
	 *         expected result
	 * @param outputName
	 *         actual result
	 * @return assert-function as string
	 */
	private String getAssertFunctionForInterval(String type, String expectedOutputName, String outputName, Set set, boolean negate) {
		String first_lower_limit_name = "lo_" + expectedOutputName;
		String second_lower_limit_name = "lo_" + outputName;

		String first_upper_limit_name = "hi_" + expectedOutputName;
		String second_upper_limit_name = "hi_" + outputName;

		String first_lower_limit_def = currentOperationsTranslationTable_.get("intervalLowerLimit").replace(outputType(1), type)
				.replace(outputName(1), first_lower_limit_name).replace(inputName(1), expectedOutputName);
		String second_lower_limit_def = currentOperationsTranslationTable_.get("intervalLowerLimit").replace(outputType(1), type)
				.replace(outputName(1), second_lower_limit_name).replace(inputName(1), outputName);

		String first_upper_limit_def = currentOperationsTranslationTable_.get("intervalUpperLimit").replace(outputType(1), type)
				.replace(outputName(1), first_upper_limit_name).replace(inputName(1), expectedOutputName);
		String second_upper_limit_def = currentOperationsTranslationTable_.get("intervalUpperLimit").replace(outputType(1), type)
				.replace(outputName(1), second_upper_limit_name).replace(inputName(1), outputName);

		if (negate) {
			negate = !negate;
			if (set == Set.PROPER_SUBSET) {
				set = Set.SUPERSET;
			} else if (set == Set.SUBSET) {
				set = Set.PROPER_SUPERSET;
			} else if (set == Set.PROPER_SUPERSET) {
				set = Set.SUBSET;
			} else if (set == Set.SUPERSET) {
				set = Set.PROPER_SUBSET;
			}
		}

		String lower_limit_test = getAssertString(first_lower_limit_name, second_lower_limit_name, set, negate);
		if (set != null) {
			negate = !negate;
		}
		String upper_limit_test = getAssertString(first_upper_limit_name, second_upper_limit_name, set, negate);

		return ("\n" + first_lower_limit_def + "\n" + second_lower_limit_def + "\n" + lower_limit_test + "\n" + first_upper_limit_def + "\n"
				+ second_upper_limit_def + "\n" + upper_limit_test + "\n");
	}

	/**
	 * Assembles an assert function for an empty interval.
	 *
	 * @param expectedOutputName
	 *         expected result
	 * @param outputName
	 *         actual result
	 * @return assert-function as string
	 */
	private String getAssertFunctionForEmptyInterval(String expectedOutputName, String outputName, Set set, boolean negate) {
		String bool_expected = "bool_" + expectedOutputName;
		String bool_output = "bool_" + outputName;
		String type = this.currentTypeTranslation_.get(Boolean.class)[0];

		String first_lower_limit_def = currentOperationsTranslationTable_.get("is_empty").replace(outputType(1), type)
				.replace(outputName(1), bool_expected).replace(inputName(1), expectedOutputName);
		String second_lower_limit_def = currentOperationsTranslationTable_.get("is_empty").replace(outputType(1), type)
				.replace(outputName(1), bool_output).replace(inputName(1), outputName);
		String lower_limit_test = getAssertString(bool_expected, bool_output, set, negate);

		return ("\n" + first_lower_limit_def + "\n" + second_lower_limit_def + "\n" + lower_limit_test + "\n");
	}

	/**
	 * Assembles an assert function for an entire interval.
	 *
	 * @param expectedOutputName
	 *         expected result
	 * @param outputName
	 *         actual result
	 * @return assert-function as string
	 */
	private String getAssertFunctionForEntireInterval(String expectedOutputName, String outputName, Set set, boolean negate) {
		String bool_expected = "bool_" + expectedOutputName;
		String bool_output = "bool_" + outputName;
		String type = this.currentTypeTranslation_.get(Boolean.class)[0];

		String first_lower_limit_def = currentOperationsTranslationTable_.get("is_entire").replace(outputType(1), type)
				.replace(outputName(1), bool_expected).replace(inputName(1), expectedOutputName);
		String second_lower_limit_def = currentOperationsTranslationTable_.get("is_entire").replace(outputType(1), type)
				.replace(outputName(1), bool_output).replace(inputName(1), outputName);
		String lower_limit_test = getAssertString(bool_expected, bool_output, set, negate);

		return ("\n" + first_lower_limit_def + "\n" + second_lower_limit_def + "\n" + lower_limit_test + "\n");
	}

	/**
	 * General method to assemble assert-function.
	 *
	 * @param first
	 *         expected output
	 * @param second
	 *         actual output
	 * @return assert function as string
	 */
	private String getAssertString(String first, String second, Set set, boolean negate) {
		String assertString = currentUnitTestLibrary_.getAssertFunction(set, negate);
		assertString = assertString.replace(EXPECTED_OUTPUT, first);
		assertString = assertString.replace(CALCULATED_OUTPUT, second);
		return assertString;
	}

	/**
	 * Get one parameter declaration for a give GenericParameter-String.
	 *
	 * @param par
	 *         the GenericParameter to build parameter string for.
	 * @param name
	 *         name of parameter
	 * @return translated parameter-string
	 */
	private String getParameterString(GenericParameter<?> par, String name) {
		return getParameterString(par.getTypeClass(), par, name);
	}

	/**
	 * Get one parameter declaration for a give GenericParameter-String.
	 *
	 * @param type
	 *         type of parameter
	 * @param par
	 *         the GenericParameter to build parameter string for.
	 * @param name
	 *         name of parameter
	 * @return translated parameter-string
	 */
	private String getParameterString(Class<?> type, GenericParameter<?> par, String name) {
		String[] translation = null;
		String parameter = null;

		if (par.hasType(Endpoints.class)) {
			Endpoints card = (Endpoints) par.getValue();
			if (card == Endpoints.NEGATIVE_INFINITY) {
				translation = currentNegativeInfinityTable_.get(type);
			}
			if (card == Endpoints.POSITIVE_INFINITY) {
				translation = currentPositiveInfinityTable_.get(type);
			}
		} else {
			translation = currentTypeTranslation_.get(type);
		}

		if (translation != null) {
			parameter = translation[1];
			parameter = parameter.replace(TYPE, translation[0]);
			parameter = parameter.replace(NAME, name);

			if (par.hasType(Endpoints.class)) {
				parameter = parameter.replace(TYPE, translation[0]);
			} else if (par.hasType(FloatingPoint.class)) {
				String fl;

				if (littleEndian_ == null) {
					fl = ((FloatingPoint) par.getValue()).getHexCodeForCurrentSystem();
				} else if (littleEndian_ == true) {
					fl = ((FloatingPoint) par.getValue()).getHexCodeLittleEndian();
				} else {
					fl = ((FloatingPoint) par.getValue()).getHexCodeBigEndian();
				}
				parameter = parameter.replace(VALUE, fl);

			} else if (par.hasType(Boolean.class)) {
				String value = currentBooleanTranslation_.get(par.getValue());
				parameter = parameter.replace(VALUE, value);
			} else if (par.hasType(Number.class)) {
				parameter = parameter.replace(VALUE, String.valueOf((Number) par.getValue()));
			}
		}
		return parameter + "\n";
	}

	/**
	 * Get interval declaration.
	 *
	 * @param interval
	 *         given interval
	 * @param name
	 *         name of interval
	 * @param empty
	 *         specifies, if interval is empty
	 * @return interval string
	 */
	private String getNewIntervalString(Interval<?> interval, String name, boolean empty, boolean entire) {
		String declaration = "";

		String inputType = currentTypeTranslation_.get(interval.getTypeClass())[0];

		if (empty) {
			declaration += currentEmptyIntervalTranslation_[1];
			declaration = declaration.replace(PARAM_TYPE, currentEmptyIntervalTranslation_[0]);
			declaration = declaration.replace(INTERVAL_TYPE, inputType);
			declaration = declaration.replace(INTERVAL_NAME, name) + "\n";
			return declaration;
		}
		else if(entire) {
			declaration += currentEntireIntervalTranslation_[1];
			declaration = declaration.replace(PARAM_TYPE, currentEntireIntervalTranslation_[0]);
			declaration = declaration.replace(INTERVAL_TYPE, inputType);
			declaration = declaration.replace(INTERVAL_NAME, name) + "\n";
			return declaration;
		}

		GenericParameter<?> lowerLimit = null;
		GenericParameter<?> upperLimit = null;

		if (interval.getLower_limit() != null) {
			lowerLimit = new GenericParameter<Object>(interval.getLower_limit());
		} else {
			lowerLimit = new GenericParameter<Object>(interval.getLowerEndpoint());
		}

		if (interval.getUpper_limit() != null) {
			upperLimit = new GenericParameter<Object>(interval.getUpper_limit());
		} else {
			upperLimit = new GenericParameter<Object>(interval.getUpperEndpoint());
		}

		String inputLowerName = name + "_lower";
		String inputUpperName = name + "_upper";

		declaration += getParameterString(interval.getTypeClass(), lowerLimit, inputLowerName);
		declaration += getParameterString(interval.getTypeClass(), upperLimit, inputUpperName);

		String[] intervalTranslation = currentTypeTranslation_.get(Interval.class);

		declaration += intervalTranslation[1];
		declaration = declaration.replace(PARAM_TYPE, intervalTranslation[0]);
		declaration = declaration.replace(INTERVAL_TYPE, inputType);
		declaration = declaration.replace(INTERVAL_NAME, name);
		declaration = declaration.replace(LOWER_VALUE, inputLowerName);
		declaration = declaration.replace(UPPER_VALUE, inputUpperName) + "\n";
		return declaration;
	}

	/**
	 * Function to replace one PlaceHolder-String in current unit-test.
	 *
	 * @param original
	 *         original string, to replace PlaceHolder in.
	 * @param placeholder
	 *         PlaceHolder-string
	 * @param insert
	 *         new string to replace PlaceHolder with.
	 * @return new modified string
	 */
	private String replacePlaceHolder(String original, String placeholder, String insert) {
		Pattern variable = Pattern.compile("\\" + getID() + "(\\{[st]{1}_[0-9]*\\})?" + placeholder.replace(getID(), "") + "\\" + getID(),
				Pattern.CASE_INSENSITIVE);
		Matcher variableMatcher = variable.matcher(original);

		while (variableMatcher.find()) {
			String var = variableMatcher.group();

			Pattern spacePattern = Pattern.compile("\\{[st]{1}_[0-9]*\\}", Pattern.CASE_INSENSITIVE);
			Matcher spaceMatcher = spacePattern.matcher(var);

			if (spaceMatcher.find()) {
				String spaceIndicator = spaceMatcher.group();
				String spaceVar = spaceIndicator.replaceAll("[\\{\\}ts_]", "");
				String space = "";
				if (spaceIndicator.contains("{t_")) {
					space = StringUtils.repeat("\t", Short.valueOf(spaceVar));
				} else if (spaceIndicator.contains("{s_")) {
					space = StringUtils.repeat(" ", Short.valueOf(spaceVar));
				}
				insert = space + insert.replace("\n", "\n" + space);
			}
			original = original.replace(var, insert);
		}
		return original;
	}

	/**
	 * back up old generated files
	 *
	 * @param file
	 *         old file to backup
	 */
	private void backUpOldFile(File file) {
		long datetime = file.lastModified();
		Date d = new Date(datetime);
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy_MM_dd-hh_mm_ss");
		String dateString = sdf.format(d);

		File temp = new File(file.getParent() + File.separator + dateString + "-" + file.getName() + ".bak");
		if (temp.exists())
			temp.delete();
		file.renameTo(temp);
	}
}
