package de.uniwue.info2.plugins.java;

import java.util.HashMap;

import de.uniwue.info2.generator.LanguageSpecification;
import de.uniwue.info2.numerics.prec.DoublePrecisionFloat;
import de.uniwue.info2.numerics.prec.SinglePrecisionFloat;

import static de.uniwue.info2.generator.PlaceHolder.*;

public class JavaSpecification extends LanguageSpecification {
	private static final String OPTION_NAME = "java";
	private static final String LANGUAGE_NAME = "Java";
	private static final String EXTENSION = OPTION_NAME;

	@Override
	public String getOptionName() {
		return OPTION_NAME;
	}

	@Override
	public String getLanguageName() {
		return LANGUAGE_NAME;
	}

	@Override
	public String getExtension() {
		return EXTENSION;
	}

	@Override
	public String getOutputFileName() {
		return ARITHMETIC_SPEC_NAME;
	}

	@Override
	public String getCodeSequence() {
		StringBuffer buffer = new StringBuffer();
		
		// description from dsl
		buffer.append(HEAD_COMMENT);
		
		// imports and definitions
		buffer.append(LANGUAGE_IMPORTS);
		buffer.append(ARITHMETIC_LIB_IMPORTS);
		buffer.append(TEST_LIB_IMPORTS);
		
		// test functions
		buffer.append(TEST_CASES);

		// section for custom methods
		buffer.append(CUSTOM_METHODS);
		
		return buffer.toString();
	}

	@Override
	public String getLineCommentToken() {
		return "//";
	}

	@Override
	public String getImportsAndDefinitions() {
		return "import java.math.BigInteger;";
	}

	@Override
	public HashMap<Class<?>, String[]> getTypesTranslation() {
		HashMap<Class<?>, String[]> types = new HashMap<Class<?>, String[]>();
		String[] translation;

		translation = new String[] { "short",   TYPE + " " + NAME + " = " + VALUE + ";"};
		types.put(Short.class, translation);
		translation = new String[] { "int",   TYPE + " " + NAME + " = " + VALUE + ";"};
		types.put(Integer.class, translation);
		translation = new String[] { "long",  TYPE + " " + NAME + " = " + VALUE + ";"};
		types.put(Long.class, translation);
		translation = new String[] { "boolean",   TYPE + " " + NAME + " = " + VALUE + ";"};
		types.put(Boolean.class, translation);
		translation = new String[] { "float", TYPE + " " + NAME + " = " + "Hex.toFloat(\"" + VALUE + "\");" };
		types.put(SinglePrecisionFloat.class, translation);
		translation = new String[] { "double", TYPE + " " + NAME + " = " + "Hex.toDouble(\""+VALUE+"\");" };
		types.put(DoublePrecisionFloat.class, translation);

		return types;
	}

	@Override
	public HashMap<Boolean, String> getBooleanTranslation() {
		HashMap<Boolean, String> booleanMap = new HashMap<Boolean, String>();
		booleanMap.put(Boolean.TRUE, "true");
		booleanMap.put(Boolean.FALSE, "false");
		return booleanMap;
	}

	@Override
	public String getLanguageCustomMethods() {
		StringBuffer buffer = new StringBuffer();
		buffer.append("class Hex {\n");
		// hex to double method
		buffer.append("\t// Hex to Double Conversion\n");
		buffer.append("\tpublic static double toDouble(String hex) {\n");
		buffer.append("\t\tlong bits = new BigInteger(hex.replaceAll(\n\t\t\""
				+ "((0[xX]{1})|([\\\\s]+))\", \"\"), 16).longValue();\n");
		buffer.append("\t\treturn Double.longBitsToDouble(bits);\n\t}\n\n");
		// hex to float method
		buffer.append("\t// Hex to Float Conversion\n");
		buffer.append("\tpublic static float toFloat(String hex) {\n");
		buffer.append("\t\tint bits = Long.valueOf(hex.replaceAll(\n\t\t\""
				+ "((0[xX]{1})|([\\\\s]+))\", \"\"), 16).intValue();\n");
		buffer.append("\t\treturn Float.intBitsToFloat(bits);\n\t}\n}");
		return buffer.toString();
	}

}
