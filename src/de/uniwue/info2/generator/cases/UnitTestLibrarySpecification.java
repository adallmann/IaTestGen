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

import de.uniwue.info2.operations.Set;

/**
 * This class is used to translate structures of a unit test library.
 * 
 * @author Michael Jedich
 * 
 */
public abstract class UnitTestLibrarySpecification {
	/**
	 * Returns short name of used unit test-library. This name is used by the
	 * CommandLineInterpreter to generate options.
	 * 
	 * @return shortened library name
	 */
	public abstract String getOptionName();

	/**
	 * Returns the full name of used unit test-library.
	 * 
	 * @return library-name as string
	 */
	public abstract String getLibraryName();

	/**
	 * Returns version of used unit test library
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
	 * Return basic structure of a unit test-class.<br>
	 * 
	 * Subclasses have to use following PlaceHolders: <br><br>
	 * DYNAMIC_TEST_METHODS<br>
	 * 
	 * @return
	 */
	public abstract String getCodeSequence();

	/**
	 * Returns translation of one test method.<br>
	 * 
	 * Subclasses have to use following PlaceHolders: <br><br>
	 * TEST_CASE_COMMENTS<br>
	 * TEST_CASE_NAME<br>
	 * ARITHMETIC_EVAL<br>
	 * ASSERTS<br>
	 * 
	 * @return
	 */
	public abstract String getTestMethod();

	/**
	 * Returns assert-function to compare to variables.<br>
	 * 
	 * Subclasses have to use following PlaceHolders: <br><br>
	 * EXPECTED_OUTPUT<br>
	 * CALCULATED_OUTPUT<br>
	 * 
	 * @return
	 */
	public abstract String getAssertFunction(Set set, boolean negate);
}
