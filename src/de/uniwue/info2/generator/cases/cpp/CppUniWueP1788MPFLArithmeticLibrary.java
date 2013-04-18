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
import static de.uniwue.info2.generator.cases.PlaceHolder.VAR_ARGS;
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
public class CppUniWueP1788MPFLArithmeticLibrary extends ArithmeticLibrarySpecification {
	private static final String OPTION_NAME = "wuempfr";
	private static final String LIBRARY_NAME = "UNIWUE LIBIEEEP1788 IA Implementation - MPFR-Flavor";
	private static final String LIBRARY_VERSION = "x.xx";
	private static final String FLAVOR = "p1788::flavor::infsup::mpfr_flavor";

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
	public String getParameterSeparator() {
		return ",";
	}

	@Override
	public String getImportsAndDefinitions() {
		StringBuffer buffer = new StringBuffer();
		buffer.append("#include <limits>\n");
		buffer.append("#include \"p1788/p1788.hpp\"\n");
		buffer.append("template<typename T>\n");
		buffer.append("using interval = " + mix_type_loc + "interval<T, " + FLAVOR + ">;\n");
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
	public String[] getEntireIntervalTranslation() {
		String[] translation = new String[] { "interval<" + INTERVAL_TYPE + ">",
				PARAM_TYPE + " " + INTERVAL_NAME + " = " + PARAM_TYPE + "::entire();" };
		return translation;
	}

	@Override
	public HashMap<Class<?>, String[]> getNegativeInfinityTranslation() {
		HashMap<Class<?>, String[]> map = new HashMap<Class<?>, String[]>();

		// double output_01_lower = -std::numeric_limits<double>::infinity();
		String infinity = TYPE + " " + NAME + " = " + "-std::numeric_limits<" + TYPE + ">::infinity();";

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

		// String infinity = TYPE + " " + NAME + " = " + "+INFINITY;";
		String infinity = TYPE + " " + NAME + " = " + "+std::numeric_limits<" + TYPE + ">::infinity();";

		map.put(Short.class, new String[] { "short", infinity });
		map.put(Integer.class, new String[] { "int", infinity });
		map.put(Long.class, new String[] { "long", infinity });

		map.put(SinglePrecisionFloat.class, new String[] { "float", infinity });
		map.put(DoublePrecisionFloat.class, new String[] { "double", infinity });

		return map;
	}

	private void initOperationTranslation() {
		if (op.isEmpty() || opmx.isEmpty()) {

			String[] one = { "inf", "sup", "mid", "rad", "wid", "mag", "mig", "is_empty", "is_entire", "pos", "neg", "inv", "sqrt", "sqr", "exp",
					"exp2", "exp10", "log", "log2", "log10", "sin", "cos", "tan", "asin", "acos", "atan", "sinh", "cosh", "tanh", "asinh", "acosh",
					"atanh", "sign", "ceil", "floor", "trunc", "round_ties_to_away", "round_ties_to_even", "abs" };

			String[] two = { "intersect", "hull", "is_equal", "contained_in", "contains", "less", "greater", "precedes", "succeeds", "is_interior",
					"contains_interior", "strictly_less", "strictly_greater", "strictly_precedes", "strictly_succeeds", "are_disjoint", "add", "sub",
					"mul", "div", "pown", "pow", "atan2", "cancel_plus", "cancel_minus" };

			String[] three = { "fma", "interval_case" };

			String[] one_var = { "min", "max", "sqr_rev", "inv_rev", "abs_rev", "pown_rev", "tan_rev", "sin_rev", "cos_rev", "cosh_rev", "mul_rev",
					"div_rev1", "div_rev2", "pow_rev1", "pow_rev2", "atan2_rev1", "atan2_rev2" };


			for (String name : one) {
				addOperations(name, 1, false);
			}
			for (String name : two) {
				addOperations(name, 2, false);
			}
			for (String name : three) {
				addOperations(name, 3, false);
			}
			for (String name : one_var) {
				addOperations(name, 1, true);
			}

			// some special functions
			String map = outputType(1) + " " + outputName(1) + " = " + "mid_rad(" + inputName(1)
					+ ").first;" + "\n";
			map += outputType(2) + " " + outputName(2) + " = " + "mid_rad(" + inputName(1)
					+ ").second;" + "\n";

			op.put("mid_rad", map);

		}
	}

	private void addOperations(String name, int input_count, boolean input_varargs) {
		addOperation(name, input_count, false, input_varargs);
		addOperation(name, input_count, true, input_varargs);
	}

	private void addOperation(String name, int input_count, boolean mixed_type, boolean input_varargs) {
		StringBuffer map = new StringBuffer();
		map.append(outputType(1) + " " + outputName(1) + " = ");

		if (mixed_type) {
			map.append(mix_type_loc);
			map.append(name);
			map.append("<" + outputType(1) + ">");
		} else {
			map.append(name);
		}

		map.append("(");

		for (int i = 1; i <= input_count; i++) {
			map.append(inputName(i));
			if (i < input_count) {
				map.append(", ");
			}
		}

		// TODO: momentan ist nur ein variabler parameter moeglich
		if (input_varargs) {
			map.append(VAR_ARGS);
		}

		map.append(");");

		if (mixed_type && !opmx.containsKey(name)) {
			opmx.put(name, map.toString());
		} else if (!op.containsKey(name)) {
			op.put(name, map.toString());
		}
	}

}
