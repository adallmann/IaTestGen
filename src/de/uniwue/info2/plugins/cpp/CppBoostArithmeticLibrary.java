package de.uniwue.info2.plugins.cpp;
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
// package de.uniwue.info2.generator.cases.cpp;
// 
// import static de.uniwue.info2.generator.cases.PlaceHolder.INTERVAL_NAME;
// import static de.uniwue.info2.generator.cases.PlaceHolder.INTERVAL_TYPE;
// import static de.uniwue.info2.generator.cases.PlaceHolder.LOWER_VALUE;
// import static de.uniwue.info2.generator.cases.PlaceHolder.NAME;
// import static de.uniwue.info2.generator.cases.PlaceHolder.PARAM_TYPE;
// import static de.uniwue.info2.generator.cases.PlaceHolder.TYPE;
// import static de.uniwue.info2.generator.cases.PlaceHolder.UPPER_VALUE;
// import static de.uniwue.info2.generator.cases.PlaceHolder.inputName;
// import static de.uniwue.info2.generator.cases.PlaceHolder.outputName;
// import static de.uniwue.info2.generator.cases.PlaceHolder.outputType;
// 
// import java.util.HashMap;
// 
// import de.uniwue.info2.generator.cases.ArithmeticLibrarySpecification;
// import de.uniwue.info2.numerics.prec.DoublePrecisionFloat;
// import de.uniwue.info2.numerics.prec.SinglePrecisionFloat;
// 
// /**
//  * Translation for Cpp Boost IA Library.
//  * 
//  * @author Michael Jedich
//  * 
//  */
// public class CppBoostArithmeticLibrary extends ArithmeticLibrarySpecification {
// 	private static final String OPTION_NAME = "boost";
// 	private static final String LIBRARY_NAME = "Boost Interval Arithmetic Library";
// 	private static final String LIBRARY_VERSION = "1.49.0";
// 
// 	@Override
// 	public String getOptionName() {
// 		return OPTION_NAME;
// 	}
// 
// 	@Override
// 	public String getLibraryName() {
// 		return LIBRARY_NAME;
// 	}
// 
// 	@Override
// 	public String getVersion() {
// 		return LIBRARY_VERSION;
// 	}
// 
// 	@Override
// 	public String getImportsAndDefinitions() {
// 		StringBuffer buffer = new StringBuffer();
// 		buffer.append("#define BOOST_NUMERIC_INTERVAL_HPP\n");
// 		buffer.append("#include <boost/limits.hpp>\n");
// 		buffer.append("#include <boost/numeric/interval/interval.hpp>\n");
// 		buffer.append("#include <boost/numeric/interval/policies.hpp>\n");
// 		buffer.append("#include <boost/numeric/interval/hw_rounding.hpp>\n");
// 		buffer.append("#include <boost/numeric/interval/rounded_arith.hpp>\n");
// 		buffer.append("#include <boost/numeric/interval/rounded_transc.hpp>\n");
// 		buffer.append("#include <boost/numeric/interval/constants.hpp>\n");
// 		buffer.append("#include <boost/numeric/interval/checking.hpp>\n");
// 		buffer.append("#include <boost/numeric/interval/compare.hpp>\n");
// 		buffer.append("#include <boost/numeric/interval/utility.hpp>\n");
// 		buffer.append("#include <boost/numeric/interval/arith.hpp>\n");
// 		buffer.append("#include <boost/numeric/interval/arith2.hpp>\n");
// 		buffer.append("#include <boost/numeric/interval/arith3.hpp>\n");
// 		buffer.append("#include <boost/numeric/interval/transc.hpp>\n");
// 		buffer.append("using namespace boost;\n");
// 		buffer.append("using namespace numeric;\n");
// 		buffer.append("using namespace interval_lib;\n");
// 		buffer.append("using namespace std;\n");
// 		buffer.append("typedef policies<save_state<rounded_transc_exact<double> >, "
// 				+ "checking_base<double> > P;");
// 		return buffer.toString();
// 	}
// 
// 	@Override
// 	public String getIntervalUpperLimit() {
// 		String upperLimit = outputType(1) + " " + outputName(1) + " = " + inputName(1)
// 				+ ".upper()" + ";";
// 		return upperLimit;
// 	}
// 
// 	@Override
// 	public String getIntervalLowerLimit() {
// 		String lowerLimit = outputType(1) + " " + outputName(1) + " = " + inputName(1)
// 				+ ".lower()" + ";";
// 		return lowerLimit;
// 	}
// 
// 	@Override
// 	public HashMap<String, String> getOperationsTranslation() {
// 		HashMap<String, String> op = new HashMap<String, String>();
// 		String map;
// 
// 		map = outputType(1) + " " + outputName(1) + " = " + inputName(1) + " + "
// 				+ inputName(2) + ";";
// 		op.put("addition", map);
// 
// 		map = outputType(1) + " " + outputName(1) + " = " + inputName(1) + " - "
// 				+ inputName(2) + ";";
// 		op.put("subtraction", map);
// 
// 		map = outputType(1) + " " + outputName(1) + " = " + "median(" + inputName(1) + ");";
// 		op.put("median", map);
// 
// 		map = outputType(1) + " " + outputName(1) + " = " + "in(" + inputName(1) + ", "
// 				+ inputName(2) + ");";
// 		op.put("is_in", map);
// 
// 		map = outputType(1) + " " + outputName(1) + " = " + "bisect(" + inputName(1)
// 				+ ").first;" + "\n";
// 		map += outputType(2) + " " + outputName(2) + " = " + "bisect(" + inputName(1)
// 				+ ").second;" + "\n";
// 		op.put("bisect", map);
// 
// 		return op;
// 	}
// 
// 
// 	@Override
// 	public HashMap<String, String> getMixedTypesOperationsTranslation() {
// 		HashMap<String, String> op = new HashMap<String, String>();
// 		String map;
// 
// 		return op;
// 	}
// 
// 	@Override
// 	public String[] getIntervalTranslation() {
// 		String[] translation = new String[] {
// 				"interval<" + INTERVAL_TYPE + ", P>",
// 				PARAM_TYPE + " " + INTERVAL_NAME + "(" + LOWER_VALUE + ", " + UPPER_VALUE
// 						+ ");" };
// 		return translation;
// 	}
// 
// 	@Override
// 	public String[] getEmptyIntervalTranslation() {
// 		// interval<double, P> output_01 = interval<double, P>::empty();
// 		String[] translation = new String[] { "interval<" + INTERVAL_TYPE + ", P>",
// 				PARAM_TYPE + " " + INTERVAL_NAME + " = " + PARAM_TYPE + "::empty();" };
// 		return translation;
// 	}
// 
// 	@Override
// 	public String checkIfIntervalEmptyTranslation() {
// 		String lowerLimit = outputType(1) + " " + outputName(1) + " = empty(" + inputName(1)
// 				+ ");";
// 		return lowerLimit;
// 	}
// 
// 	@Override
// 	public HashMap<Class<?>, String[]> getNegativeInfinityTranslation() {
// 		HashMap<Class<?>, String[]> map = new HashMap<Class<?>, String[]>();
// 
// 		String infinity = TYPE + " " + NAME + " = " + "-INFINITY;";
// 
// 		map.put(Short.class, new String[] { "short", infinity });
// 		map.put(Integer.class, new String[] { "int", infinity });
// 		map.put(Long.class, new String[] { "long", infinity });
// 
// 		map.put(SinglePrecisionFloat.class, new String[] { "float", infinity });
// 		map.put(DoublePrecisionFloat.class, new String[] { "double", infinity });
// 
// 		return map;
// 	}
// 
// 	@Override
// 	public HashMap<Class<?>, String[]> getPositiveInfinityTranslation() {
// 		HashMap<Class<?>, String[]> map = new HashMap<Class<?>, String[]>();
// 
// 		String infinity = TYPE + " " + NAME + " = " + "+INFINITY;";
// 
// 		map.put(Short.class, new String[] { "short", infinity });
// 		map.put(Integer.class, new String[] { "int", infinity });
// 		map.put(Long.class, new String[] { "long", infinity });
// 
// 		map.put(SinglePrecisionFloat.class, new String[] { "float", infinity });
// 		map.put(DoublePrecisionFloat.class, new String[] { "double", infinity });
// 
// 		return map;
// 	}
// 
// }
