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

import static de.uniwue.info2.generator.cases.PlaceHolder.ARITHMETIC_LIB_IMPORTS;
import static de.uniwue.info2.generator.cases.PlaceHolder.CUSTOM_METHODS;
import static de.uniwue.info2.generator.cases.PlaceHolder.HEAD_COMMENT;
import static de.uniwue.info2.generator.cases.PlaceHolder.LANGUAGE_IMPORTS;
import static de.uniwue.info2.generator.cases.PlaceHolder.NAME;
import static de.uniwue.info2.generator.cases.PlaceHolder.TEST_CASES;
import static de.uniwue.info2.generator.cases.PlaceHolder.TEST_LIB_IMPORTS;
import static de.uniwue.info2.generator.cases.PlaceHolder.TYPE;
import static de.uniwue.info2.generator.cases.PlaceHolder.VALUE;

import java.util.HashMap;

import de.uniwue.info2.generator.cases.LanguageSpecification;
import de.uniwue.info2.numerics.prec.DoublePrecisionFloat;
import de.uniwue.info2.numerics.prec.SinglePrecisionFloat;

/**
 * Translation for Cpp Boost IA Library.
 * 
 * @author Michael Jedich
 * 
 */
public class CppSpecification extends LanguageSpecification {
	private static final String OPTION_NAME = "cpp";
	private static final String EXTENSION = "cpp";
	private static final String LANGUAGE_NAME = "C++";

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
	public String getLineCommentToken() {
		return "//";
	}
	
	@Override
	public String getImportsAndDefinitions() {
		StringBuffer buffer = new StringBuffer();
		buffer.append("#include <iostream>\n");
		return buffer.toString();
	}
	
	@Override
	public String getCodeSequence() {
		StringBuffer buffer = new StringBuffer();
		
		// description from dsl
		buffer.append(HEAD_COMMENT + "\n");
		
		// imports and definitions
		buffer.append(LANGUAGE_IMPORTS + "\n\n");
		buffer.append(ARITHMETIC_LIB_IMPORTS + "\n\n");
		buffer.append(TEST_LIB_IMPORTS + "\n");
		
		// section for custom methods
		buffer.append(CUSTOM_METHODS + "\n");
		
		// test functions
		buffer.append(TEST_CASES + "\n");
		
		return buffer.toString();
	}
	

	@Override
	public HashMap<Class<?>, String[]> getTypesTranslation() {
		HashMap<Class<?>, String[]> types = new HashMap<Class<?>, String[]>();
		String[] translation;
		translation = new String[] { "short", TYPE + " " + NAME + " = " + VALUE + ";" };
		types.put(Short.class, translation);
		translation = new String[] { "int", TYPE + " " + NAME + " = " + VALUE + ";" };
		types.put(Integer.class, translation);
		translation = new String[] { "long", TYPE + " " + NAME + " = " + VALUE + ";" };
		types.put(Long.class, translation);
		translation = new String[] { "bool", TYPE + " " + NAME + " = " + VALUE + ";" };
		types.put(Boolean.class, translation);
		
		translation = new String[] { "float",
				TYPE + " " + NAME + " = " + "hex_string_to_float(\"" + VALUE + "\");" };
		types.put(SinglePrecisionFloat.class, translation);

		translation = new String[] { "double",
				TYPE + " " + NAME + " = " + "hex_string_to_double(\"" + VALUE + "\");" };
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



		buffer.append("\n\n// Hex to Float Conversion\n");
		buffer.append("const unsigned float_length = sizeof(float);\n");
		buffer.append("float hex_string_to_float(std::string hexStr) {\n");
		buffer.append("\tunsigned char temp[float_length];\n");
		buffer.append("\tstd::string searchString(\"0x\");\n");
		buffer.append("\tstd::string::size_type pos = 0;\n");
		buffer.append("\twhile ((pos = hexStr.find(searchString, pos)) != std::string::npos) {\n");
		buffer.append("\t\thexStr.replace(pos, searchString.size(), \"\");\n");
		buffer.append("\t\tpos++; \n\t}\n");
		buffer.append("\tfor (unsigned i = 0; i < hexStr.size(); i += 2)\n");
		buffer.append("\t\ttemp[i / 2] = strtol(hexStr.substr(i, 2).c_str(), 0, 16);\n");
		buffer.append("\tunsigned char hex_array[float_length];\n");
		buffer.append("\tfor (unsigned i = 0; i < float_length; i++) {\n");
		buffer.append("\t\thex_array[float_length - 1 - i] = temp[i];\n\t}\n");
		buffer.append("\tfloat x;\n");
		buffer.append("\tstd::copy(hex_array, hex_array + float_length, reinterpret_cast<char*> (&x));\n");
		buffer.append("\treturn x;\n}\n\n");


		buffer.append("// Hex to Double Conversion\n");
		buffer.append("const unsigned double_length = sizeof(double);\n");
		buffer.append("double hex_string_to_double(std::string hexStr) {\n");
		buffer.append("\tunsigned char temp[double_length];\n");
		buffer.append("\tstd::string searchString(\"0x\");\n");
		buffer.append("\tstd::string::size_type pos = 0;\n");
		buffer.append("\twhile ((pos = hexStr.find(searchString, pos)) != std::string::npos) {\n");
		buffer.append("\t\thexStr.replace(pos, searchString.size(), \"\");\n");
		buffer.append("\t\tpos++;\n\t}\n");
		buffer.append("\tfor (unsigned i = 0; i < hexStr.size(); i += 2)\n");
		buffer.append("\t\ttemp[i / 2] = strtol(hexStr.substr(i, 2).c_str(), 0, 16);\n");
		buffer.append("\tunsigned char hex_array[double_length];\n");
		buffer.append("\tfor (unsigned i = 0; i < double_length; i++) {\n");
		buffer.append("\t\thex_array[double_length - 1 - i] = temp[i];\n\t}\n");
		buffer.append("\tdouble x;\n");
		buffer.append("\tstd::copy(hex_array, hex_array + double_length,\n");
		buffer.append("\treinterpret_cast<char*> (&x));\n");
		buffer.append("\treturn x;\n}\n");

		return buffer.toString();
	}
}
