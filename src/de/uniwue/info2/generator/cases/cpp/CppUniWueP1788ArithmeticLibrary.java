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

import static de.uniwue.info2.generator.cases.PlaceHolder.INTERVAL_NAME;
import static de.uniwue.info2.generator.cases.PlaceHolder.INTERVAL_TYPE;
import static de.uniwue.info2.generator.cases.PlaceHolder.LOWER_VALUE;
import static de.uniwue.info2.generator.cases.PlaceHolder.NAME;
import static de.uniwue.info2.generator.cases.PlaceHolder.PARAM_TYPE;
import static de.uniwue.info2.generator.cases.PlaceHolder.TYPE;
import static de.uniwue.info2.generator.cases.PlaceHolder.UPPER_VALUE;
import static de.uniwue.info2.generator.cases.PlaceHolder.inputName;
import static de.uniwue.info2.generator.cases.PlaceHolder.outputName;
import static de.uniwue.info2.generator.cases.PlaceHolder.outputType;

import java.util.HashMap;

import de.uniwue.info2.generator.cases.ArithmeticLibrarySpecification;
import de.uniwue.info2.numerics.prec.DoublePrecisionFloat;
import de.uniwue.info2.numerics.prec.SinglePrecisionFloat;

/**
 * Translation for Cpp Boost IA Library.
 *
 * @author Michael Jedich
 *
 */
public class CppUniWueP1788ArithmeticLibrary extends ArithmeticLibrarySpecification {
	private static final String OPTION_NAME = "uniwue";
	private static final String LIBRARY_NAME = "LIBIEEEl1788 IA Library";
	private static final String LIBRARY_VERSION = "x.xx";
	private HashMap<String, String> op = new HashMap<String, String>();
	private HashMap<String, String> opmx = new HashMap<String, String>();
	private String mix_type_loc = "p1788::infsup::";

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
		StringBuffer buffer = new StringBuffer();
		buffer.append("#include \"p1788/p1788.hpp\"\n");
		buffer.append("template<typename T>\n");
		buffer.append("using interval = "+ mix_type_loc + "interval<T, p1788::flavor::infsup::ieee754_flavor>;\n");
		return buffer.toString();
	}

	@Override
	public String getIntervalUpperLimit() {
		String upperLimit = outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".upper()" + ";";
		return upperLimit;
	}

	@Override
	public String getIntervalLowerLimit() {
		String lowerLimit = outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".lower()" + ";";
		return lowerLimit;
	}


	private void initOperationTranslation() {
		if (op.isEmpty() || opmx.isEmpty()) {
			String[] one_one = { "pos", "neg", "inv", "sqrt" };
			String[] one_two = { "add", "sub", "mul", "div" };
			String[] one_three = { "fma", "interval_case" };


			for (String name : one_one) {
				addOperationOneOneSingle(name);
				addOperationOneOneMixType(name);
			}
			for (String name : one_two) {
				addOperationOneTwoSingle(name);
				addOperationOneTwoMixType(name);
			}
			for (String name : one_three) {
				addOperationOneThreeSingle(name);
				addOperationOneThreeMixType(name);
			}
		}
	}

	@Override
	public HashMap<String, String> getOperationsTranslation() {
		initOperationTranslation();
		return op;
	}

	@Override
	public HashMap<String, String> getMixedTypesOperationsTranslation() {
		initOperationTranslation();
		return opmx;
	}

	@Override
	public String[] getIntervalTranslation() {
		String[] translation = new String[] { "interval<" + INTERVAL_TYPE + ">",
				PARAM_TYPE + " " + INTERVAL_NAME + "(" + LOWER_VALUE + ", " + UPPER_VALUE + ");" };
		return translation;
	}

	@Override
	public String[] getEmptyIntervalTranslation() {
		// interval<double, P> output_01 = interval<double, P>::empty();
		String[] translation = new String[] { "interval<" + INTERVAL_TYPE + ">",
				PARAM_TYPE + " " + INTERVAL_NAME + " = " + PARAM_TYPE + "::empty();" };
		return translation;
	}

	@Override
	public String checkIfIntervalEmptyTranslation() {
		String lowerLimit = outputType(1) + " " + outputName(1) + " = empty(" + inputName(1) + ");";
		return lowerLimit;
	}

	@Override
	public HashMap<Class<?>, String[]> getNegativeInfinityTranslation() {
		HashMap<Class<?>, String[]> map = new HashMap<Class<?>, String[]>();

		String infinity = TYPE + " " + NAME + " = " + "-INFINITY;";

		map.put(Short.class, new String[] { "short", infinity });
		map.put(Integer.class, new String[] { "int", infinity });
		map.put(Long.class, new String[] { "long", infinity });

		map.put(SinglePrecisionFloat.class, new String[] { "float", infinity });
		map.put(DoublePrecisionFloat.class, new String[] { "double", infinity });

		return map;
	}

	@Override
	public HashMap<Class<?>, String[]> getPositiveInfinityTranslation() {
		HashMap<Class<?>, String[]> map = new HashMap<Class<?>, String[]>();

		String infinity = TYPE + " " + NAME + " = " + "+INFINITY;";

		map.put(Short.class, new String[] { "short", infinity });
		map.put(Integer.class, new String[] { "int", infinity });
		map.put(Long.class, new String[] { "long", infinity });

		map.put(SinglePrecisionFloat.class, new String[] { "float", infinity });
		map.put(DoublePrecisionFloat.class, new String[] { "double", infinity });

		return map;
	}

	private void addOperationOneOneSingle(String name) {
		// interval<double> lib_output_01 = pos(input_01);
		String map = outputType(1) + " " + outputName(1) + " = " + name + "(" + inputName(1) + ");";
		if (!op.containsKey(name)) {
			op.put(name, map);
		}
	}

	private void addOperationOneOneMixType(String name) {
		// interval<double> lib_output_01 = pos(input_01);
		String map = outputType(1) + " " + outputName(1) + " = " + mix_type_loc + name + "<" + outputType(1) + ">(" + inputName(1) + ");";
		if (!opmx.containsKey(name)) {
			opmx.put(name, map);
		}
	}

	private void addOperationOneTwoSingle(String name) {
		// interval<double> lib_output_01 = add(input_01, input_02);
		String map = outputType(1) + " " + outputName(1) + " = " + name + "(" + inputName(1) + ", " + inputName(2) + ");";
		if (!op.containsKey(name)) {
			op.put(name, map);
		}
	}

	private void addOperationOneTwoMixType(String name) {
		// interval<double> lib_output_01 = p1788::infsup::add<double>(input_01, input_02);
		String map = outputType(1) + " " + outputName(1) + " = " + mix_type_loc + name + "<" + outputType(1) + ">(" + inputName(1) + ", "
				+ inputName(2) + ");";
		if (!opmx.containsKey(name)) {
			opmx.put(name, map);
		}
	}


	private void addOperationOneThreeSingle(String name) {
		// interval<double> lib_output_01 = add(input_01, input_02);
		String map = outputType(1) + " " + outputName(1) + " = " + name + "(" + inputName(1) + ", " + inputName(2) + ", " + inputName(3)+ ");";
		if (!op.containsKey(name)) {
			op.put(name, map);
		}
	}

	private void addOperationOneThreeMixType(String name) {
		// std::cout << "fma mt: " << p1788::infsup::fma<interval<float>>(d_a, f_b, d_c) << std::endl << std::endl;
		String map = outputType(1) + " " + outputName(1) + " = " + mix_type_loc + name + "<" + outputType(1) + ">(" + inputName(1) + ", "
				+ inputName(2) + ", " + inputName(3)+ ");";
		if (!opmx.containsKey(name)) {
			opmx.put(name, map);
		}
	}




}
