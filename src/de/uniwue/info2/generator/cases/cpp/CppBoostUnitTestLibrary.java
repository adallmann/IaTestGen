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
package de.uniwue.info2.generator.cases.cpp;

import de.uniwue.info2.generator.cases.UnitTestLibrarySpecification;

import static de.uniwue.info2.generator.cases.PlaceHolder.*;

/**
 * Translation basic structures of cpp programming language.
 * 
 * @author Michael Jedich
 * 
 */
public class CppBoostUnitTestLibrary extends UnitTestLibrarySpecification {
	private static final String OPTION_NAME = "boost";
	private static final String LIBRARY_NAME = "Boost Test Library";
	private static final String LIBRARY_VERSION = "1.49.0";

	@Override
	public String getOptionName() {
		return OPTION_NAME;
	}

	@Override
	public String getLibraryName() {
		return LIBRARY_NAME;
	}

	@Override
	public String getVersion() {
		return LIBRARY_VERSION;
	}

	@Override
	public String getImportsAndDefinitions() {
		String imports = "#define BOOST_TEST_DYN_LINK" + "\n"
				+ "#define BOOST_TEST_MODULE \"main_unit_test\"\n"
				+ "#include <boost/test/unit_test.hpp>";
		return imports;
	}

	@Override
	public String getCodeSequence() {
		StringBuffer buffer = new StringBuffer();
		buffer.append("BOOST_AUTO_TEST_SUITE(testSuite)" + "\n\n");
		buffer.append(DYNAMIC_TEST_METHODS);
		buffer.append("BOOST_AUTO_TEST_SUITE_END()");

		return buffer.toString();
	}

	@Override
	public String getTestMethod() {
		StringBuffer buffer = new StringBuffer();
		// comment for current test-function
		buffer.append(TEST_CASE_COMMENTS);
		buffer.append("BOOST_AUTO_TEST_CASE(");
		// adds name to test-function
		buffer.append(TEST_CASE_NAME);
		buffer.append(")" + "\n" + "{" + "\n");
		// adds input and output-parameter and the operation to test
		buffer.append(addIndentationTabs(ARITHMETIC_EVAL, 1) + "\n");
		// adds assert-function from the unit-test-library
		buffer.append(addIndentationTabs(ASSERTS, 1) + "\n");
		buffer.append("}");
		return buffer.toString();
	}

	@Override
	public String getAssertFunction() {
		String equalFunction = "BOOST_REQUIRE_EQUAL(" + EXPECTED_OUTPUT + ", "
				+ CALCULATED_OUTPUT + ");";
		return equalFunction;
	}
}
