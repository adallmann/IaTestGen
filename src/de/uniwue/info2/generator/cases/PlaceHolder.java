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
package de.uniwue.info2.generator.cases;

/**
 * This class is used to store Placeholders used in LanguageSpecification,
 * ArithmeticLibrarySpecification and UnitTestLibrarySpecification. PlaceHolders are stored as
 * strings, to simplify debugging. <br>
 * You can output the unit test string at any point of the generation process to see which
 * PlaceHolders still have to be replaced. <br>
 * 
 * @author Michael Jedich
 * 
 */
public final class PlaceHolder {

	// String to identify placeholder
	private static final String ID = "$";

	// place holder used in "getCodeSequence" by Subclasses of "LanguageSpecification"
	public static final String HEAD_COMMENT = ID + "HEAD_COMMENT" + ID;
	public static final String LANGUAGE_IMPORTS = ID + "LANGUAGE_DEF" + ID;
	public static final String ARITHMETIC_LIB_IMPORTS = ID + "ARITHMETIC_LIB_DEF" + ID;
	public static final String TEST_LIB_IMPORTS = ID + "TEST_LIB_DEF" + ID;
	public static final String CUSTOM_METHODS = ID + "CUSTOM_METHODS" + ID;
	public static final String TEST_CASES = ID + "TEST_CASES" + ID;

	// place holder used in "getCodeSequence" by Subclasses of "UnitTestLibrarySpecification"
	public static final String DYNAMIC_TEST_METHODS = ID + "DYNAMIC_TEST_METHODS" + ID;

	// place holder used in "getTestMethod()" by Subclasses of "UnitTestLibrarySpecification"
	public static final String TEST_CASE_COMMENTS = ID + "TEST_CASE_COMMENTS" + ID;
	public static final String TEST_CASE_NAME = ID + "TEST_CASE_NAME" + ID;
	public static final String ARITHMETIC_EVAL = ID + "ARITHMETIC_EVAL" + ID;
	public static final String ASSERTS = ID + "ASSERTS" + ID;

	// place holder used in "getTestEquals()" by Subclasses of "UnitTestLibrarySpecification"
	public static final String EXPECTED_OUTPUT = ID + "EXPECTED_OUTPUT" + ID;
	public static final String CALCULATED_OUTPUT = ID + "CALCULATED_OUTPUT" + ID;

	// operation parameter used in "getOperationsTranslation()" by Subclasses of
	// "ArithmeticLibrarySpecification"
	public static final String OPERATION_INPUT = ID + "OPERATION_INPUT" + ID;
	public static final String OPERATION_OUTPUT = ID + "OPERATION_OUTPUT" + ID;
	public static final String OPERATION_TYPE = ID + "OPERATION_TYPE" + ID;

	// interval parameter used in "getIntervalTranslation()" by Subclasses of
	// "ArithmeticLibrarySpecification"
	public static final String INTERVAL_TYPE = ID + "INTERVAL_TYPE" + ID;
	public static final String INTERVAL_NAME = ID + "INTERVAL_NAME" + ID;
	public static final String LOWER_VALUE = ID + "LOWER_VALUE" + ID;
	public static final String UPPER_VALUE = ID + "UPPER_VALUE" + ID;
	public static final String PARAM_TYPE = ID + "PARAM_TYPE" + ID;

	// place holder used in "getTypesTranslation()" by Subclasses of "LanguageSpecification"
	public static final String TYPE = ID + "TYPE" + ID;
	public static final String NAME = ID + "NAME" + ID;
	public static final String VALUE = ID + "VALUE" + ID;

	// arbitrary number of values symbol
	public static final String VAR_ARGS = ID + "__VAR_ARGS__" + ID;

	/**
	 * Adds spaces as intendentation.
	 * 
	 * @param placeHolder
	 *            PlaceHolder to intendent
	 * @param amount
	 *            number of spaces
	 * @return returns PlaceHolder-String with intendentation
	 */
	public static String addIndentationSpaces(String placeHolder, int amount) {
		if (amount < 1) {
			return placeHolder;
		}
		return ID + "{s_" + String.valueOf(amount) + "}" + placeHolder.replace(ID, "") + ID;
	}

	/**
	 * Adds Tabs as intendentation.
	 * 
	 * @param placeHolder
	 *            PlaceHolder to intendent
	 * @param amount
	 *            number of tabs
	 * @return returns PlaceHolder-String with intendentation
	 */
	public static String addIndentationTabs(String placeHolder, int amount) {
		if (amount < 1) {
			return placeHolder;
		}
		return ID + "{t_" + String.valueOf(amount) + "}" + placeHolder.replace(ID, "") + ID;
	}

	/**
	 * Returns PlaceHolder for the name of the input parameter.
	 * 
	 * @param sequenceNumber
	 *            sequence number of input parameter. e.g. 2 for second parameter
	 * @return returns PlaceHolder-string for given parameter
	 */
	public static String inputName(int sequenceNumber) {
		if (sequenceNumber < 1) {
			throw new IllegalArgumentException("The sequenceNumber must begin with \"1\"!");
		}
		return ID + OPERATION_INPUT.replace(ID, "") + String.valueOf(sequenceNumber) + ID;
	}


	/**
	 * Returns PlaceHolder for the name of the input parameter.
	 * 
	 * @return returns PlaceHolder-string for given parameter
	 */
	public static String outputName() {
		return outputName(99); 
	}

	/**
	 * Returns PlaceHolder for the name of the output parameter.
	 * 
	 * @param sequenceNumber
	 *            sequence number of output parameter. e.g. 2 for second parameter
	 * @return returns PlaceHolder-string for given parameter
	 */
	public static String outputName(int sequenceNumber) {
		if (sequenceNumber < 1) {
			throw new IllegalArgumentException("The sequenceNumber must begin with \"1\"!");
		}
		return ID + OPERATION_OUTPUT.replace(ID, "") + String.valueOf(sequenceNumber) + ID;
	}

	/**
	 * Returns PlaceHolder for the parameter type for a given sequence number.
	 * 
	 * @param sequenceNumber
	 *            sequence number of the parameter. e.g. 2 for second parameter
	 * @return returns PlaceHolder-string for given parameter type.
	 */
	public static String outputType(int sequenceNumber) {
		if (sequenceNumber < 1) {
			throw new IllegalArgumentException("The sequenceNumber must begin with \"1\"!");
		}
		return ID + OPERATION_TYPE.replace(ID, "") + String.valueOf(sequenceNumber) + ID;
	}

	/**
	 * Returns the ID for a PlaceHolder-String, it is used to identify a PlaceHolder in unit
	 * test-string.
	 * 
	 * @return the id of a PlaceHolder
	 */
	public static String getID() {
		return ID;
	}
}
