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
package de.uniwue.info2.main;

import java.io.File;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;
import java.io.FileInputStream;
import java.io.BufferedInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;

import org.apache.commons.cli.BasicParser;
import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.OptionBuilder;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;
import org.apache.commons.lang.StringUtils;

import de.uniwue.info2.generator.TestcaseGenerator;
import de.uniwue.info2.generator.cases.ArithmeticLibrarySpecification;
import de.uniwue.info2.generator.cases.LanguageFactory;
import de.uniwue.info2.generator.cases.LanguageSpecification;
import de.uniwue.info2.generator.cases.UnitTestLibrarySpecification;

/**
 * Main class with Commandline-Interpreter.
 * <p>
 * User has to specify location of a Domain-Specific-Language-File, output-folder
 *
 * @author Michael Jedich
 *
 */
public class CommandLineInterpreter {

	// options and associated information
	private static final String GENERATING_DIALOG = "Generating test-file for target-language: ";

	private static final String HELP_OPTION = "help";
	private static final String HELP_OPTION_SHORT = "h";
	private static final String HELP_DESCRIPTION = "Shows this infopage.";

	private static final String HELP2_OPTION = "extended_help";
	private static final String HELP2_OPTION_SHORT = "H";
	private static final String HELP2_DESCRIPTION = "Shows a detailed infopage.";

	private static final String DSL_OPTION = "dsl";
	private static final String DSL_OPTION_SHORT = "i";
	private static final String DSL_DESCRIPTION = "Domain Specific Language.";
	private static final String DSL_ARGUMENT = "dsl-file";

	private static final String OUTPUT_OPTION = "output";
	private static final String OUTPUT_OPTION_SHORT = "o";
	private static final String OUTPUT_DESCRIPTION = "Folder for generated unit test-files.\n";
	private static final String OUTPUT_ARGUMENT = "output-dir";

	private static final String OPTIONAL_OPTION = "optional";
	private static final String OPTIONAL_OPTION_SHORT = "p";
	private static final String OPTIONAL_DESCRIPTION = "Generate test-functions for operations marked as optional.\n";

	private static final String OPTIONAL_FUNCTIONS_CONFIG_OPTION = "optional_config";
	private static final String OPTIONAL_FUNCTIONS_CONFIG_SHORT = "P";
	private static final String OPTIONAL_FUNCTIONS_CONFIG_DESCRIPTION = "Specify exceptions for optional operations.";
	private static final String OPTIONAL_FUNCTIONS_CONFIG_ARGUMENT = "config-file";

	private static final String BIG_ENDIAN_OPTION = "big_endian";
	private static final String BIG_ENDIAN_OPTION_SHORT = "q";
	private static final String BIG_ENDIAN_DESCRIPTION = "Use big endian to format hexadecimal.\n";

	private static final String LITTLE_ENDIAN_OPTION = "little_endian";
	private static final String LITTLE_ENDIAN_OPTION_SHORT = "r";
	private static final String LITTLE_ENDIAN_DESCRIPTION = "Use little endian to format hexadecimal.\n";

	private static final String LANGUAGE_SPECIFICATION = "Generate unit-tests for all available libraries in ";

	// name of program/jar-file
	private static final String CLASS = "ia_gen.jar";

	private static final String SEPERATOR = StringUtils.repeat("*", 74);
	private static final DecimalFormat INDEX = new DecimalFormat("00");

	private static final String HEADER = "--by default, test-files " + "are generated for all available language specs.--\n";

	/**
	 * Prints Help for Commandline-Interpreter.
	 *
	 * @param options
	 *         possible options
	 */
	private static void printHelp(Options options) {
		HelpFormatter helpFormater = new HelpFormatter();
		helpFormater.printHelp(CLASS, "\n" + SEPERATOR + "\n" + HEADER + SEPERATOR + "\n", options, SEPERATOR + "\n", true);
	}

	/**
	 * Prints Help for Commandline-Interpreter.
	 *
	 * @param options
	 *         possible options
	 */
	private static void printExtendedHelp(Options options) {
		HelpFormatter helpFormater = new HelpFormatter();
		helpFormater.printHelp(CLASS, "\n" + SEPERATOR + "\n" + HEADER + SEPERATOR + "\n", options, SEPERATOR + "\n", true);
	}

	@SuppressWarnings("static-access")
	public static void main(String[] args) {

		/*-------------------------------------------------------- */
		/*---------------SETTING TARGET LANGUAGE------------------ */
		/*-------------------------------------------------------- */
		LanguageFactory languageFactory = new LanguageFactory();

		CommandLine line = null;
		CommandLineParser parser = new BasicParser();
		Options options = new Options();
		// options to display in the help page
		Options options_short = new Options();

		// add help option
		Option help_option = new Option(HELP_OPTION_SHORT, HELP_OPTION, false, HELP_DESCRIPTION);
		options.addOption(help_option);
		options_short.addOption(help_option);
		// add extended help option
		Option help2_option = new Option(HELP2_OPTION_SHORT, HELP2_OPTION, false, HELP2_DESCRIPTION);
		options.addOption(help2_option);
		options_short.addOption(help2_option);
		// add optional operations option
		options.addOption(new Option(OPTIONAL_OPTION_SHORT, OPTIONAL_OPTION, false, OPTIONAL_DESCRIPTION));
		options.addOption(new Option(BIG_ENDIAN_OPTION_SHORT, BIG_ENDIAN_OPTION, false, BIG_ENDIAN_DESCRIPTION));
		options.addOption(new Option(LITTLE_ENDIAN_OPTION_SHORT, LITTLE_ENDIAN_OPTION, false, LITTLE_ENDIAN_DESCRIPTION));
		// add optional operations config option
		options.addOption(OptionBuilder.withLongOpt(OPTIONAL_FUNCTIONS_CONFIG_OPTION).withArgName(OPTIONAL_FUNCTIONS_CONFIG_ARGUMENT)
				.withDescription(OPTIONAL_FUNCTIONS_CONFIG_DESCRIPTION).hasArg().create(OPTIONAL_FUNCTIONS_CONFIG_SHORT));
		// add dsl option
		Option dsl_option = OptionBuilder.withLongOpt(DSL_OPTION).withArgName(DSL_ARGUMENT).withDescription(DSL_DESCRIPTION).hasArg()
				.isRequired().create(DSL_OPTION_SHORT);
		options.addOption(dsl_option);
		options_short.addOption(dsl_option);
		// add output-folder option
		Option output_option = OptionBuilder.withLongOpt(OUTPUT_OPTION).isRequired().withArgName(OUTPUT_ARGUMENT)
				.withDescription(OUTPUT_DESCRIPTION).hasArg().create(OUTPUT_OPTION_SHORT);
		options.addOption(output_option);
		options_short.addOption(output_option);

		// count possible language-specifications
		short optionCounter = 1;

		// get all possible language-specifications from language-factory and iterate through them
		List<LanguageSpecification> lSpecs = languageFactory.getAvailableLanguageSpecifications_();

		for (LanguageSpecification lSpec : lSpecs) {
			// get all possible unit-specifications for current language and iterate through them
			List<UnitTestLibrarySpecification> uSpecs = languageFactory.getAvailableUnitTestLibraries_(lSpec.getOptionName());
			String languageDescriptionAll = LANGUAGE_SPECIFICATION + lSpec.getLanguageName();
			String languageCounter = "s" + INDEX.format(optionCounter++);

			for (UnitTestLibrarySpecification uSpec : uSpecs) {
				// get all possible arithmetic-library-specifications for current language and iterate through
				// them
				List<ArithmeticLibrarySpecification> aSpecs = languageFactory.getAvailableArithmeticLibraries_(lSpec.getOptionName());
				for (ArithmeticLibrarySpecification aSpec : aSpecs) {
					String languageDescription = "Generate unit-test for " + lSpec.getLanguageName() + "\n*[" + uSpec.getLibraryName() + " - "
							+ uSpec.getVersion() + "]\n*[" + aSpec.getLibraryName() + " - " + aSpec.getVersion() + "]";

					// if there is more than one option, generate suitable option-names and add them all to
					// commandline options
					if (uSpecs.size() > 1 || aSpecs.size() > 1) {
						options.addOption(OptionBuilder.withLongOpt(lSpec.getOptionName() + "_" + uSpec.getOptionName() + "_" + aSpec.getOptionName())
								.withDescription(languageDescription).hasArg(false).create("s" + INDEX.format(optionCounter++)));
					} else {
						// if there is only one option, use language-name as option-name
						languageDescriptionAll = languageDescription;
					}
				}
				// add specifications to options
				options.addOption(OptionBuilder.withLongOpt(lSpec.getOptionName()).withDescription(languageDescriptionAll).hasArg(false)
						.create(languageCounter));
			}
		}

		/*-------------------------------------------------------- */
		/*-------------------PARSE USER INPUT--------------------- */
		/*-------------------------------------------------------- */
		try {
			// manual search for help-arguments
 			for (String arg: args) {
				arg = arg.trim().replace("-", "");
 				if (arg.equals(HELP_OPTION_SHORT) || arg.equals(HELP_OPTION)) {
					printHelp(options_short);
					return;
				}
 				if (arg.equals(HELP2_OPTION_SHORT) || arg.equals(HELP2_OPTION)) {
					printExtendedHelp(options);
					return;
				}
 			}
			
			// parse arguments	
			line = parser.parse(options, args);

			File dsl_file = null;
			File output_folder = null;
			File optional_config = null;
			Properties optional_operations = null;
			Boolean optional = false;
			Boolean little_endian = null;
			ArrayList<String> optional_exceptions = new ArrayList<String>();

			// if help-option found print help
			if (line.hasOption(HELP2_OPTION_SHORT) || args.length == 0) {
				printExtendedHelp(options);
				return;
			}

			// if help-option found print help
			if (line.hasOption(HELP_OPTION_SHORT) || args.length == 0) {
				System.out.println("\n");
				printHelp(options_short);
				return;
			}

			if (line.hasOption(OPTIONAL_OPTION_SHORT)) {
				optional = true;
			}

			if (line.hasOption(LITTLE_ENDIAN_OPTION)) {
				little_endian = true;
			}

			if (line.hasOption(BIG_ENDIAN_OPTION)) {
				little_endian = false;
			}

			// if dsl-option found, check if file exists and is readable
			// print help if error occurs
			if (line.hasOption(DSL_OPTION_SHORT)) {
				dsl_file = new File(line.getOptionValue(DSL_OPTION_SHORT));
				if (!dsl_file.exists()) {
					System.err.println("\n" + SEPERATOR + "\n" + "ERROR - DSL-file doesn't exist:\n" + dsl_file + "\n" + SEPERATOR + "\n");
					printHelp(options_short);
					return;
				} else if (dsl_file.isDirectory()) {
					System.err.println("\n" + SEPERATOR + "\n" + "ERROR - DSL-file is a directory:\n" + dsl_file + "\n" + SEPERATOR + "\n");
					printHelp(options_short);
					return;
				} else if (!dsl_file.canRead()) {
					System.err.println("\n" + SEPERATOR + "\n" + "ERROR - Need read-permission for DSL-file:\n" + dsl_file + "\n" + SEPERATOR + "\n");
					printHelp(options_short);
					return;
				}
			}

			// if output-option found, check if folder exists and if write-permission was granted
			// print help if error occurs
			if (line.hasOption(OUTPUT_OPTION_SHORT)) {
				output_folder = new File(line.getOptionValue(OUTPUT_OPTION_SHORT));
				if (!output_folder.exists()) {
					System.err.println("\n" + SEPERATOR + "\n" + "ERROR - Output-folder doesn't exist:\n" + output_folder + "\n" + SEPERATOR + "\n");
					printHelp(options_short);
					return;
				} else if (!output_folder.isDirectory()) {
					System.err.println("\n" + SEPERATOR + "\n" + "ERROR - Output-folder is not a directory:\n" + output_folder + "\n" + SEPERATOR + "\n");
					printHelp(options_short);
					return;
				} else if (!output_folder.canWrite() || !output_folder.canRead()) {
					System.err.println("\n" + SEPERATOR + "\n" + "ERROR - Missing permissions for output-folder:\n" + output_folder + "\n" + SEPERATOR
							+ "\n");
					printHelp(options_short);
					return;
				}
			}

			if (line.hasOption(OPTIONAL_FUNCTIONS_CONFIG_SHORT)) {
				optional_config = new File(line.getOptionValue(OPTIONAL_FUNCTIONS_CONFIG_OPTION));
				if (!dsl_file.exists()) {
					System.err.println("\n" + SEPERATOR + "\n" + "ERROR - config-file doesn't exist:\n" + dsl_file + "\n" + SEPERATOR + "\n");
					printExtendedHelp(options);
					return;
				} else if (dsl_file.isDirectory()) {
					System.err.println("\n" + SEPERATOR + "\n" + "ERROR - config-file is a directory:\n" + dsl_file + "\n" + SEPERATOR + "\n");
					printExtendedHelp(options);
					return;
				} else if (!dsl_file.canRead()) {
					System.err.println("\n" + SEPERATOR + "\n" + "ERROR - Need read-permission for config-file:\n" + dsl_file + "\n" + SEPERATOR + "\n");
					printExtendedHelp(options);
					return;
				}
			}

			if (optional_config != null) {
				optional_operations = new Properties();
				BufferedInputStream stream = new BufferedInputStream(new FileInputStream(optional_config));
				optional_operations.load(stream);
				stream.close();
				String optional_prop = optional_operations.getProperty("GENERATE_OPTIONAL");
				if (optional_prop != null) {
					if (optional_prop.trim().toLowerCase().equals("true")) {
						optional = true;
					} else if (optional_prop.trim().toLowerCase().equals("false")) {
						optional = false;
					} else if (!optional_prop.trim().isEmpty()) {
						System.err.println("\n" + SEPERATOR + "\n"
								+ "ERROR - Syntax incorrect in config-file:\nUse \"true\" or \"false\" for \"GENERATE_OPTIONAL\"\n" + SEPERATOR + "\n");
						printExtendedHelp(options);
						return;
					}
				}
				String exceptions = optional_operations.getProperty("EXCLUSIONS"); 
				if (exceptions != null) {
					for (String exc : optional_operations.getProperty("EXCLUSIONS").split(";")) {
						optional_exceptions.add(exc.trim());
					}
				}
			}

			/*-------------------------------------------------------- */
			/*-------------------START GENERATING--------------------- */
			/*-------------------------------------------------------- */

			// instantiate generator for unit-tests
			TestcaseGenerator mainGenerator = new TestcaseGenerator(dsl_file, output_folder);

			boolean overrideDefaultSpecs = false;

			// check if user input contains a language-specifications
			// if user specified language, set overrideDefaultSpecs to true, so that only given specifications
			// are used
			for (int i = 1; i <= optionCounter; i++) {
				String opt = "s" + INDEX.format(i);
				if (line.hasOption(opt)) {
					LanguageSpecification targetSpecification = languageFactory.getLanguageSpecification(options.getOption(opt).getLongOpt());
					String output = (GENERATING_DIALOG + targetSpecification.getLanguageName());


					// finally generate unit-test for current language-specification
					boolean successful = mainGenerator.generateUnitTest(targetSpecification, optional, optional_exceptions, little_endian);

					if (successful) {
						System.out.println(output + "\n--> Successfully generated.");
					} else {
						System.err.println(output + "\n--> ERROR - see logfile");
					}
					overrideDefaultSpecs = true;
				}
			}


			// skip, if user already defined one language-specification
			// if user did not define language-specification, generate unit-tests for all
			// possible language-specifications (default)
			if (!overrideDefaultSpecs) {
				for (int i = 0; i < lSpecs.size(); i++) {
					LanguageSpecification specification = languageFactory.getLanguageSpecification(lSpecs.get(i).getOptionName());

					String output = INDEX.format(i + 1) + " - " + GENERATING_DIALOG + specification.getLanguageName();

					// finally generate unit-test for current language-specification
					boolean successful = mainGenerator.generateUnitTest(specification, optional, optional_exceptions, little_endian);

					if (successful) {
						System.out.println(output + "\n--> Successfully generated.");
					} else {
						System.err.println(output + "\n--> ERROR - see logfile");
					}
				}
			}

		} catch (ParseException | IOException p) {
				System.err.println("\n" + SEPERATOR + "\n" + "ERROR - WRONG ARGUMENTS:\n" + p.getMessage() + "\n" + SEPERATOR + "\n");
				printHelp(options_short);
				System.out.println("\n");
		}
	}
}
