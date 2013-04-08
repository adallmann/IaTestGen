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

import java.util.HashMap;

/**
 * This class is used to translate structures of an interval arithmetic library. Please look at
 * the example implementation: CppBoostArithmeticLibrary
 * 
 * 
 * @author Michael Jedich
 * 
 */
public abstract class ArithmeticLibrarySpecification {

	/**
	 * Returns the full name of used IA-Library.
	 * 
	 * @return library-name as string
	 */
	public abstract String getLibraryName();

	/**
	 * Returns short name of used interval arithmetic library. This name is used by the
	 * CommandLineInterpreter to generate options.
	 * 
	 * @return shortened library name
	 */
	public abstract String getOptionName();

	/**
	 * Returns version of used interval arithmetic library
	 * 
	 * @return version
	 */
	public abstract String getVersion();

	/**
	 * Returns imports and definitions of current library.
	 * 
	 * @return imports and definitions
	 */
	public abstract String getImportsAndDefinitions();

	/**
	 * Return the translation for an interval in a string-array with length 2. <br>
	 * The first position is the interval-datatype (e.g. interval<" + INTERVAL_TYPE + ">) <br>
	 * The second postition is the rule to declarate this datatype (e.g. PARAM_TYPE + " " +
	 * INTERVAL_NAME + "(" + LOWER_VALUE + ", " + UPPER_VALUE + ");" };) <br>
	 * <br>
	 * 
	 * 
	 * Subclasses have to use following PlaceHolders: <br>
	 * <br>
	 * 
	 * INTERVAL_TYPE --> interval-datatype<br>
	 * PARAM_TYPE --> PlaceHolder of INTERVAL_TYPE in HashMap-value <br>
	 * INTERVAL_NAME --> name of declarated interval<br>
	 * LOWER_VALUE --> lower limit of interval<br>
	 * UPPER_VALUE --> upper limit of interval<br>
	 * <br>
	 * 
	 * e.g.: String[] translation = new String[] { "interval<" + INTERVAL_TYPE + ", P>",
	 * PARAM_TYPE + " " + INTERVAL_NAME + "(" + LOWER_VALUE + ", " + UPPER_VALUE + ");" };
	 * 
	 * @return translation string of interval
	 */
	public abstract String[] getIntervalTranslation();

	/**
	 * Returns the translation of an operation in a HashMap.<br>
	 * The key is the name of the operation as string.<br>
	 * The value is the translation of the operation<br>
	 * <br>
	 * 
	 * 
	 * Subclasses have to use PlaceHolders represented by following methods: <br>
	 * <br>
	 * 
	 * outputType(int s) --> type of output-parameter by sequence number <br>
	 * outputName(int s) --> name of output-parameter by sequence number <br>
	 * inputName(int s) --> name of input-parameter by sequence number <br>
	 * <br>
	 * 
	 * an example of boost ia-library: <br>
	 * <br>
	 * 
	 * HashMap<String, String> op = new HashMap<String, String>(); <br>
	 * String map = outputType(1) + " " + outputName(1) + " <br>
	 * = " + inputName(1) + " + " + inputName(2) + ";"; <br>
	 * op.put("addition", map);<br>
	 * 
	 * @return translation or operation
	 */
	public abstract HashMap<String, String> getOperationsTranslation();


	/**
 	 * Same as getOperationsTranslation, but for mixed data types 
 	 */
	public abstract HashMap<String, String> getMixedTypesOperationsTranslation();

	/**
	 * Returns the translation of a method to get lower limit of given interval.
	 * 
	 * Subclasses have to use PlaceHolders represented by following methods: <br>
	 * <br>
	 * 
	 * outputType(1) --> type of output-parameter by sequence number <br>
	 * outputName(1) --> name of output-parameter by sequence number <br>
	 * inputName(1) --> name of input-parameter by sequence number <br>
	 * <br>
	 * 
	 * Just use the same procedure as in getOperationsTranslation(), but there is just one
	 * input (the interval) and one output (the limit).<br>
	 * 
	 * e.g.: String lowerLimit = outputType(1) + " " + outputName(1) + " = " + inputName(1) +
	 * ".lower()" + ";"; <br>
	 * 
	 * @return translation of method
	 */
	public abstract String getIntervalUpperLimit();

	/**
	 * Returns the translation of a method to get upper limit of given interval.
	 * 
	 * Subclasses have to use PlaceHolders represented by following methods: <br>
	 * <br>
	 * 
	 * outputType(1) --> type of output-parameter by sequence number <br>
	 * outputName(1) --> name of output-parameter by sequence number <br>
	 * inputName(1) --> name of input-parameter by sequence number <br>
	 * <br>
	 * 
	 * Just use the same procedure as in getOperationsTranslation(), but there is just one
	 * input (the interval) and one output (the limit). <br>
	 * 
	 * e.g.: String upperLimit = outputType(1) + " " + outputName(1) + " = " + inputName(1) +
	 * ".upper()" + ";";
	 * 
	 * @return translation of method
	 */
	public abstract String getIntervalLowerLimit();

	/**
	 * Returns the translation of a method to check, if a given interval is empty.
	 * 
	 * Subclasses have to use PlaceHolders represented by following methods: <br>
	 * <br>
	 * 
	 * outputType(1) --> type of output-parameter by sequence number <br>
	 * outputName(1) --> name of output-parameter by sequence number <br>
	 * inputName(1) --> name of input-parameter by sequence number <br>
	 * <br>
	 * 
	 * Just use the same procedure as in getOperationsTranslation(), but there is just one
	 * input (the interval) and one output (boolean). <br>
	 * 
	 * e.g.: String lowerLimit = outputType(1) + " " + outputName(1) + " = empty(" +
	 * inputName(1) + ");";
	 * 
	 * @return translation of method to check if given interval is empty
	 */
	public abstract String checkIfIntervalEmptyTranslation();

	/**
	 * Return the translation for an empty interval in a string-array with length 2. <br>
	 * The first position is the interval-datatype <br>
	 * The second postition is the rule to declarate this datatype<br>
	 * <br>
	 * 
	 * 
	 * Subclasses have to use following PlaceHolders: <br>
	 * <br>
	 * 
	 * INTERVAL_TYPE --> interval-datatype<br>
	 * PARAM_TYPE --> PlaceHolder of INTERVAL_TYPE in HashMap-value <br>
	 * INTERVAL_NAME --> name of declarated interval<br>
	 * <br>
	 * 
	 * e.g.: String[] translation = new String[] { "interval<" + INTERVAL_TYPE + ", P>",
	 * PARAM_TYPE + " " + INTERVAL_NAME + " = " + PARAM_TYPE + "::empty();" };
	 * 
	 * 
	 * @return translation string of interval
	 */
	public abstract String[] getEmptyIntervalTranslation();

	/**
	 * Translation of a negative interval-limit.
	 * 
	 * @return translated string
	 */
	public abstract HashMap<Class<?>, String[]> getNegativeInfinityTranslation();

	/**
	 * Translation of a positive interval-limit.
	 * 
	 * @return translated string
	 */
	public abstract HashMap<Class<?>, String[]> getPositiveInfinityTranslation();


	/**
	 * Simple Parameter seperator like: ',' 
	 * 
	 * @return translated string
	 */
	public abstract String getParameterSeparator();

}
