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

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/**
 * This class is used to translate structures of a programming Language.
 * 
 * @author Michael Jedich
 * 
 */
public abstract class LanguageSpecification {

	private List<ArithmeticLibrarySpecification> arithmeticLibraryList = new ArrayList<ArithmeticLibrarySpecification>();
	private List<UnitTestLibrarySpecification> unitTestLibraryList = new ArrayList<UnitTestLibrarySpecification>();

	/**
	 * Get shortened name of programming language.
	 * 
	 * @return short name
	 */
	public abstract String getOptionName();

	/**
	 * Get full name of programming language.
	 * 
	 * @return full name
	 */
	public abstract String getLanguageName();

	/**
	 * Get extension of source-code files.
	 * 
	 * @return extension string
	 */
	public abstract String getExtension();

	/**
	 * Get boolean translation.
	 * 
	 * @return
	 */
	public abstract HashMap<Boolean, String> getBooleanTranslation();

	/**
	 * Get primitives types translation. <br>
	 * 
	 * Subclasses have to use following PlaceHolders: <br>
	 * <br>
	 * TYPE<br>
	 * NAME<br>
	 * VALUE<br>
	 * 
	 * @return
	 */
	public abstract HashMap<Class<?>, String[]> getTypesTranslation();

	/**
	 * Get basic structure of a class of current programming language.<br>
	 * 
	 * 
	 * Subclasses have to use following PlaceHolders: <br>
	 * <br>
	 * HEAD_COMMENT<br>
	 * LANGUAGE_IMPORTS<br>
	 * ARITHMETIC_LIB_IMPORTS<br>
	 * TEST_LIB_IMPORTS<br>
	 * CUSTOM_METHODS<br>
	 * TEST_CASES<br>
	 * 
	 * @return
	 */
	public abstract String getCodeSequence();

	/**
	 * Returns imports and definitions of current programming language.
	 * 
	 * @return imports and definitions
	 */
	public abstract String getImportsAndDefinitions();

	/**
	 * Returns custom methods and variables.
	 * 
	 * @return custom methods
	 */
	public abstract String getLanguageCustomMethods();

	/**
	 * Returns String which is used to mark line comments.
	 * 
	 * @return
	 */
	public abstract String getLineCommentToken();

	/**
	 * Return list of linked arithmetic libraries.
	 * 
	 * @return list of ia-libraries
	 */
	public List<ArithmeticLibrarySpecification> getArithmeticLibraryList() {
		return arithmeticLibraryList;
	}

	/**
	 * Returns name to use for file-naming.
	 * 
	 * @return
	 */
	public abstract String getOutputFileName();

	/**
	 * Return list of linked arithmetic libraries.
	 * 
	 * @return list of ia-libraries
	 */
	public List<UnitTestLibrarySpecification> getUnitTestLibraryList() {
		return unitTestLibraryList;
	}

	protected void addArithmeticLibrary(ArithmeticLibrarySpecification library) {
		arithmeticLibraryList.add(library);
	}

	protected void addUnitTestLibrary(UnitTestLibrarySpecification library) {
		unitTestLibraryList.add(library);
	}
}
