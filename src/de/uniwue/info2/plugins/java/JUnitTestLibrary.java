package de.uniwue.info2.plugins.java;

import de.uniwue.info2.generator.UnitTestLibrarySpecification;
import de.uniwue.info2.operations.Set;

import static de.uniwue.info2.generator.PlaceHolder.*;

public class JUnitTestLibrary extends UnitTestLibrarySpecification {
	private static final String OPTION_NAME = "junit";
	private static final String LIBRARY_NAME = "JUnit testing framework";
	private static final String LIBRARY_VERSION = "4.0";

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
	public String getTestMethod() {
		StringBuffer buffer = new StringBuffer();
		// comment for current test-function
		buffer.append(TEST_CASE_COMMENTS);
		buffer.append("@Test\npublic void ");
		// adds name to test-function
		buffer.append(TEST_CASE_NAME);
		buffer.append("()" + "\n" + "{" + "\n");
		// adds input and output-parameter and the operation to test
		buffer.append(addIndentationTabs(ARITHMETIC_EVAL, 1));
		// adds assert-function from the unit-test-library
		buffer.append(addIndentationTabs(ASSERTS, 1));
		buffer.append("}");
		return buffer.toString();
	}

	@Override
	public String getImportsAndDefinitions() {
		// String imports = "import static org.junit.Assert.*;\n" + "import org.junit.Test;\n" + "import junit.framework.TestCase;";
		String imports = "import org.junit.Test;\n" + "import junit.framework.TestCase;";
		return imports;
	}

	@Override
	public String getCodeSequence() {
		StringBuffer buffer = new StringBuffer();
		buffer.append("public class "); 
		buffer.append(ARITHMETIC_SPEC_NAME);
		buffer.append(" extends TestCase {\n\n"); 
		buffer.append(addIndentationTabs(DYNAMIC_TEST_METHODS, 1));
		buffer.append(addIndentationTabs(ARITHMETIC_CUSTOM_METHODS, 1));
		buffer.append("}");
		return buffer.toString();
	}

	@Override
	public String getAssertFunction(Set set, boolean negate) {
		String operator = "";
		String equalFunction = "";

		// if no set-relation is given
		if (set == null) {
			if (negate) 
				operator = " != ";
			else 
				operator = " == ";
		}
		else if (set == Set.PROPER_SUBSET || set == Set.SUBSET) {
			if (negate) 
				operator = " < ";
			else 
				operator = " > ";
		} else if (set == Set.PROPER_SUPERSET || set == Set.SUPERSET) {
			if (negate) 
				operator = " > ";
			else 
				operator = " < ";
		}

		equalFunction += "assertTrue(" + CALCULATED_OUTPUT + operator 
					+ EXPECTED_OUTPUT;

		if ( set == Set.SUBSET || set == Set.SUPERSET) {
			equalFunction += " || " + CALCULATED_OUTPUT + " == " 
					+ EXPECTED_OUTPUT;
		}

		equalFunction += ");";

		return equalFunction;
	}
}
