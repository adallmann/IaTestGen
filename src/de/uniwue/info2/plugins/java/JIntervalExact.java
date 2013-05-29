package de.uniwue.info2.plugins.java;

import static de.uniwue.info2.generator.PlaceHolder.*;

import java.util.HashMap;

import de.uniwue.info2.generator.ArithmeticLibrarySpecification;
import de.uniwue.info2.numerics.prec.DoublePrecisionFloat;
import de.uniwue.info2.numerics.prec.SinglePrecisionFloat;

public class JIntervalExact extends ArithmeticLibrarySpecification {
	private static final String OPTION_NAME = "jint-exact";
	private static final String LIBRARY_NAME = "JInterval Exact";
	private static final String LIBRARY_VERSION = "01-Oct-2011";
	private static final String CONTEXT = "RealInterval.enterExactContext()";

	private static final String IMPORT = "import com.kenai.jinterval";
	private static final String PAR_SEPARATOR = ",";

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
		return PAR_SEPARATOR;
	}

	@Override
	public String getCustomMethods() {
		final StringBuffer buffer = new StringBuffer();
		buffer.append("public ");
		buffer.append(ARITHMETIC_SPEC_NAME);
		buffer.append("() {\n\t");
		buffer.append(CONTEXT);
		buffer.append(";\n}");
		return buffer.toString();
	}

	@Override
	public String getImportsAndDefinitions() {
		final StringBuffer imports = new StringBuffer();
		imports.append(IMPORT + ".rational_bounds.RealInterval;\n");
		imports.append(IMPORT + ".number.Rational;");
		return imports.toString();
	}

	@Override
	public String[] getIntervalTranslation() {
		final StringBuffer interval = new StringBuffer();
		interval.append(PARAM_TYPE);
		interval.append(" ");
		interval.append(INTERVAL_NAME);
		interval.append(" = ");
		interval.append(PARAM_TYPE);
		interval.append(".valueOf(Rational.valueOf(");
		interval.append(LOWER_VALUE);
		interval.append("), Rational.valueOf(");
		interval.append(UPPER_VALUE);
		interval.append("));");
		return new String[] { "RealInterval", interval.toString() };
	}

	@Override
	public String[] getEmptyIntervalTranslation() {
		final StringBuffer interval = new StringBuffer();
		interval.append(PARAM_TYPE);
		interval.append(" ");
		interval.append(INTERVAL_NAME);
		interval.append(" = RealInterval.EMPTY;");
		return new String[] { "RealInterval", interval.toString() };
	}

	@Override
	public String[] getEntireIntervalTranslation() {
		// TODO: no entire-function found
		return null;
	}

	/*
	 * Desired list of elementaty functions in Russian of the library (TRANSLATED BY GOOGLE TRANSLATE)
	 *
	 * Characteristics of the interval -- mid-range, radius width, absolute value, mignituda.
	 *
	 * Elementary arithmetic -- Addition. Subtraction. Multiplication. Division. Square. dual. pro.
	 *
	 * Elementary functions -- Exhibitor. Logarithm to the base two. The logarithm to the base 10. Logarithm. Sinus. Cosine. The tangent. Arc
	 * tangent. The arc cosine. Arcsin. Secant. Cosecant.
	 *
	 * Matrix operations -- Addition matrices. Subtraction of matrices. Matrix multiplication. Addition of a scalar. Subtraction of a scalar.
	 * The multiplication by a scalar. Division by a scalar. Transposition. Determinants. Bringing the matrix to a triangular form. Bringing
	 * the matrix to diagonal form. The solution of the linear system of equations.
	 */
	@Override
	public HashMap<String, String> getOperationsTranslation() {
		String debug = "";
		// debug = "\n\nSystem.out.println(\"$TEST_CASE_NAME$ ----------------------------\\n" + inputName(1) + ":\\n\" + " + inputName(1)
		// + " + \"\\n\" + \"" + outputName(1) + ":\\n\" + " + outputName(1) + ");\n\n";

		// example-output
		// RealInterval lib_output_01 = input_01.intersect(input_02);
		// RealInterval lib_output_01 = input_01.add(input_02);
		HashMap<String, String> op = new HashMap<String, String>();
		op.put("is_empty", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".isEmpty();");
		op.put("intersect", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".intersect(" + inputName(2) + ");");
		op.put("inf", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".exactInf()." + outputType(1) + "Value();" + debug);
		op.put("sup", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".exactSup()." + outputType(1) + "Value();" + debug);
		op.put("mid", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".exactMid()." + outputType(1) + "Value();" + debug);
		op.put("wid", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".exactWid()." + outputType(1) + "Value();" + debug);
		op.put("is_equal", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".seq(" + inputName(2) + ");");
		// op.put("is_equal", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".equals(" + inputName(2) + ");");
		op.put("add", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".add(" + inputName(2) + ");" + debug);
		op.put("sub", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".subtract(" + inputName(2) + ");" + debug);
		op.put("mul", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".multiply(" + inputName(2) + ");" + debug);
		op.put("div", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".divide(" + inputName(2) + ");" + debug);
		op.put("neg", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".negate();" + debug);
		op.put("inv", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".inverse();" + debug);
		op.put("sqrt", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".sqrt();" + debug);
		op.put("sqr", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".sqr();" + debug);
		op.put("pow", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".pow(" + inputName(2) + ");" + debug);
		op.put("exp", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".exp();" + debug);
		op.put("log", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".log();" + debug);
		op.put("log2", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".log2();" + debug);
		op.put("log10", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".log10();" + debug);
		op.put("sin", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".sin();" + debug);
		op.put("cos", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".cos();" + debug);
		op.put("tan", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".tan();" + debug);
		op.put("asin", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".asin();" + debug);
		op.put("acos", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".acos();" + debug);
		op.put("atan", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".atan();" + debug);
		op.put("strictly_less", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".clt(" + inputName(2) + ");" + debug);
		op.put("less", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".cle(" + inputName(2) + ");" + debug);
		op.put("strictly_greater", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".cgt(" + inputName(2) + ");" + debug);
		op.put("greater", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".cge(" + inputName(2) + ");" + debug);
		op.put("contained_in", outputType(1) + " " + outputName(1) + " = " + inputName(2) + ".subset(" + inputName(1) + ");" + debug);
		op.put("contains", outputType(1) + " " + outputName(1) + " = " + inputName(1) + ".subset(" + inputName(2) + ");" + debug);
		return op;
	}

	@Override
	public HashMap<String, String> getMixedTypesOperationsTranslation() {
		return getOperationsTranslation();
	}

	@Override
	public String getIntervalUpperLimit() {
		// double lo_output_01 = output_01.doubleInf();
		final StringBuffer limit = new StringBuffer();
		limit.append(outputType(1));
		limit.append(" ");
		limit.append(outputName(1));
		limit.append(" = ");
		limit.append(inputName(1));
		limit.append(".exactSup().");
		limit.append(outputType(1));
		limit.append("Value();");
		return limit.toString();
	}

	@Override
	public String getIntervalLowerLimit() {
		// double lo_output_01 = output_01.doubleInf();
		final StringBuffer limit = new StringBuffer();
		limit.append(outputType(1));
		limit.append(" ");
		limit.append(outputName(1));
		limit.append(" = ");
		limit.append(inputName(1));
		limit.append(".exactInf().");
		limit.append(outputType(1));
		limit.append("Value();");
		return limit.toString();
	}

	@Override
	public HashMap<Class<?>, String[]> getNegativeInfinityTranslation() {
		return getInfinityTranslation(false);
	}

	@Override
	public HashMap<Class<?>, String[]> getPositiveInfinityTranslation() {
		return getInfinityTranslation(true);
	}

	private HashMap<Class<?>, String[]> getInfinityTranslation(boolean positive) {
		HashMap<Class<?>, String[]> map = new HashMap<Class<?>, String[]>();
		final String rational = "Rational";
		String infinity;
		if (positive)
			infinity = TYPE + " " + NAME + " = " + rational + ".POSITIVE_INFINITY;";
		else
			infinity = TYPE + " " + NAME + " = " + rational + ".NEGATIVE_INFINITY;";
		map.put(Short.class, new String[] { rational, infinity });
		map.put(Integer.class, new String[] { rational, infinity });
		map.put(Long.class, new String[] { rational, infinity });
		map.put(SinglePrecisionFloat.class, new String[] { rational, infinity });
		map.put(DoublePrecisionFloat.class, new String[] { rational, infinity });
		return map;
	}

}
