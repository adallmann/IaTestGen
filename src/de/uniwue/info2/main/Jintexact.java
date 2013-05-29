package de.uniwue.info2.main;
// ************************************************************
// @parser_description
// 		Early Version of Parser Generator
// @parser_authors
// 		Copyright 2013
// 		Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
// 		Institute of Computer Science,
// 		University of Wuerzburg, Germany
// 		
// 		Michael Jedich (m.jedich@gmail.com)
// 		University of Wuerzburg, Germany
// @parser_version
// 		0.8
// ************************************************************
// @dsl_description
// 		Sample-file with a couple of simple 
// 		  testfunctions for libieeep1788
// @dsl_authors
// 		Marco Nehmeier,
// 		Michael Jedich
// @dsl_version
// 		0.8, 21.03.2013
// ************************************************************

import java.math.BigInteger;
import com.kenai.jinterval.rational_bounds.RealInterval;
import com.kenai.jinterval.number.Rational;
import org.junit.Test;
import junit.framework.TestCase;

public class Jintexact extends TestCase {

	// @name
	// 		inf
	// @required
	// 		true
	@Test
	public void test_01_inf()
	{
		// input parameter 1:
		double input_lower = Hex.toDouble("0x4024000000000000");
		double input_upper = Hex.toDouble("0x402E000000000000");
		RealInterval input = RealInterval.valueOf(Rational.valueOf(input_lower), Rational.valueOf(input_upper));
		// expected output parameter 1:
		double output = Hex.toDouble("0x4024000000000000");
		
		// operation to test: inf
		double lib_output = input.exactInf().doubleValue();	
		// assert function for output 1:
		assertTrue(lib_output == output);
	}
	
	// @name
	// 		is_empty
	// @required
	// 		true
	@Test
	public void test_02_isempty()
	{
		// input parameter 1:
		RealInterval input = RealInterval.EMPTY;
		// expected output parameter 1:
		boolean output = true;
		
		// operation to test: is_empty
		boolean lib_output = input.isEmpty();	
		// assert function for output 1:
		assertTrue(lib_output == output);
	}
	
	// @name
	// 		contains
	// @required
	// 		true
	@Test
	public void test_03_contains()
	{
		// input parameter 1:
		double input_01_lower = Hex.toDouble("0xC024000000000000");
		double input_01_upper = Hex.toDouble("0x4008000000000000");
		RealInterval input_01 = RealInterval.valueOf(Rational.valueOf(input_01_lower), Rational.valueOf(input_01_upper));
		// input parameter 2:
		double input_02_lower = Hex.toDouble("0x3FF0000000000000");
		double input_02_upper = Hex.toDouble("0x4000000000000000");
		RealInterval input_02 = RealInterval.valueOf(Rational.valueOf(input_02_lower), Rational.valueOf(input_02_upper));
		// expected output parameter 1:
		boolean output = true;
		
		// operation to test: contains
		boolean lib_output = input_01.subset(input_02);	
		// assert function for output 1:
		assertTrue(lib_output == output);
	}
	
	// @name
	// 		add
	// @required
	// 		true
	@Test
	public void test_04_add()
	{
		// input parameter 1:
		double input_01_lower = Hex.toDouble("0x4024000000000000");
		double input_01_upper = Hex.toDouble("0x402E000000000000");
		RealInterval input_01 = RealInterval.valueOf(Rational.valueOf(input_01_lower), Rational.valueOf(input_01_upper));
		// input parameter 2:
		double input_02_lower = Hex.toDouble("0x3FF0000000000000");
		double input_02_upper = Hex.toDouble("0x4000000000000000");
		RealInterval input_02 = RealInterval.valueOf(Rational.valueOf(input_02_lower), Rational.valueOf(input_02_upper));
		// expected output parameter 1:
		Rational output_lower = Rational.NEGATIVE_INFINITY;
		Rational output_upper = Rational.POSITIVE_INFINITY;
		RealInterval output = RealInterval.valueOf(Rational.valueOf(output_lower), Rational.valueOf(output_upper));
		
		// operation to test: add
		RealInterval lib_output = input_01.add(input_02);	
		// assert function for output 1:
		double lo_output = output.exactInf().doubleValue();
		double lo_lib_output = lib_output.exactInf().doubleValue();
		assertTrue(lo_lib_output > lo_output || lo_lib_output == lo_output);
		double hi_output = output.exactSup().doubleValue();
		double hi_lib_output = lib_output.exactSup().doubleValue();
		assertTrue(hi_lib_output < hi_output || hi_lib_output == hi_output);
		
	}
	
	// @name
	// 		add
	// @required
	// 		true
	@Test
	public void test_05_add()
	{
		// input parameter 1:
		float input_01_lower = Hex.toFloat("0x41200000");
		float input_01_upper = Hex.toFloat("0x41700000");
		RealInterval input_01 = RealInterval.valueOf(Rational.valueOf(input_01_lower), Rational.valueOf(input_01_upper));
		// input parameter 2:
		float input_02_lower = Hex.toFloat("0x3F800000");
		float input_02_upper = Hex.toFloat("0x40000000");
		RealInterval input_02 = RealInterval.valueOf(Rational.valueOf(input_02_lower), Rational.valueOf(input_02_upper));
		// expected output parameter 1:
		double output_lower = Hex.toDouble("0x4026000000000000");
		double output_upper = Hex.toDouble("0x4031000000000000");
		RealInterval output = RealInterval.valueOf(Rational.valueOf(output_lower), Rational.valueOf(output_upper));
		
		// operation to test: add
		RealInterval lib_output = input_01.add(input_02);	
		// assert function for output 1:
		double lo_output = output.exactInf().doubleValue();
		double lo_lib_output = lib_output.exactInf().doubleValue();
		assertTrue(lo_lib_output == lo_output);
		double hi_output = output.exactSup().doubleValue();
		double hi_lib_output = lib_output.exactSup().doubleValue();
		assertTrue(hi_lib_output == hi_output);
		
	}
	
	// Custom methods of IA-Library;
	public Jintexact() {
		RealInterval.enterExactContext();
	}
}

class Hex {
	// Hex to Double Conversion
	public static double toDouble(String hex) {
		long bits = new BigInteger(hex.replaceAll(
		"((0[xX]{1})|([\\s]+))", ""), 16).longValue();
		return Double.longBitsToDouble(bits);
	}

	// Hex to Float Conversion
	public static float toFloat(String hex) {
		int bits = Long.valueOf(hex.replaceAll(
		"((0[xX]{1})|([\\s]+))", ""), 16).intValue();
		return Float.intBitsToFloat(bits);
	}
}

