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
// 		Sample-file with a couple of simple testfunctions for libieeep1788
// @dsl_authors
// 		Michael Jedich
// @dsl_version
// 		0.8, 21.03.2013
// ************************************************************

#include <iostream>


#include "p1788/p1788.hpp"
template<typename T>
using interval = p1788::infsup::interval<T, p1788::flavor::infsup::ieee754_flavor>;


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "main_unit_test"
#include <boost/test/unit_test.hpp>


// Hex to Float Conversion
const unsigned float_length = sizeof(float);
float hexStringToFloat(std::string hexStr) {
	unsigned char temp[float_length];
	std::string searchString("0x");
	std::string::size_type pos = 0;
	while ((pos = hexStr.find(searchString, pos)) != std::string::npos) {
		hexStr.replace(pos, searchString.size(), "");
		pos++; 
	}
	for (unsigned i = 0; i < hexStr.size(); i += 2)
		temp[i / 2] = strtol(hexStr.substr(i, 2).c_str(), 0, 16);
	unsigned char hex_array[float_length];
	for (unsigned i = 0; i < float_length; i++) {
		hex_array[float_length - 1 - i] = temp[i];
	}
	float x;
	std::copy(hex_array, hex_array + float_length, reinterpret_cast<char*> (&x));
	return x;
}

// Hex to Double Conversion
unsigned double_length = sizeof(double);
double hexStringToDouble(std::string hexStr) {
	unsigned char temp[double_length];
	std::string searchString("0x");
	std::string::size_type pos = 0;
	while ((pos = hexStr.find(searchString, pos)) != std::string::npos) {
		hexStr.replace(pos, searchString.size(), "");
		pos++;
	}
	for (unsigned i = 0; i < hexStr.size(); i += 2)
		temp[i / 2] = strtol(hexStr.substr(i, 2).c_str(), 0, 16);
	unsigned char hex_array[double_length];
	for (unsigned i = 0; i < double_length; i++) {
		hex_array[double_length - 1 - i] = temp[i];
	}
	double x;
	std::copy(hex_array, hex_array + double_length,
	reinterpret_cast<char*> (&x));
	return x;
}

BOOST_AUTO_TEST_SUITE(testSuite)

// @name
// 		add
// @description
// 		default - no mixed types
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_01_add)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hexStringToDouble("0x3FF0000000000000");
	double input_02_upper = hexStringToDouble("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: add
	interval<double> lib_output_01 = add(input_01, input_02);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		add
// @description
// 		calculated result should be a PROPER SUBSET of the expected
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_02_add)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hexStringToDouble("0x3FF0000000000000");
	double input_02_upper = hexStringToDouble("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: add
	interval<double> lib_output_01 = add(input_01, input_02);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 > lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 < hi_output_01);
	
}

// @name
// 		add
// @description
// 		calculated result should be NOT A PROPER SUBSET of the expected (--> superset)
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_03_add)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hexStringToDouble("0x3FF0000000000000");
	double input_02_upper = hexStringToDouble("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: add
	interval<double> lib_output_01 = add(input_01, input_02);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 < lo_output_01 || lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 > hi_output_01 || hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		add
// @description
// 		calculated result should be a SUBSET (not proper subset) of the expected
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_04_add)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hexStringToDouble("0x3FF0000000000000");
	double input_02_upper = hexStringToDouble("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: add
	interval<double> lib_output_01 = add(input_01, input_02);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 > lo_output_01 || lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 < hi_output_01 || hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		add
// @description
// 		calculated result should be a PROPER SUPERSET of the expected
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_05_add)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hexStringToDouble("0x3FF0000000000000");
	double input_02_upper = hexStringToDouble("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: add
	interval<double> lib_output_01 = add(input_01, input_02);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 < lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 > hi_output_01);
	
}

// @name
// 		add
// @description
// 		calculated result should be a SUPERSET (not a proper one) of the expected
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_06_add)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hexStringToDouble("0x3FF0000000000000");
	double input_02_upper = hexStringToDouble("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: add
	interval<double> lib_output_01 = add(input_01, input_02);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 < lo_output_01 || lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 > hi_output_01 || hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		add
// @description
// 		-addition operation with mixed data types
// 		-negation
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_07_add)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hexStringToFloat("0x3F800000");
	float input_02_upper = hexStringToFloat("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_01_lower = hexStringToDouble("0x4014000000000000");
	double output_01_upper = hexStringToDouble("0x4022000000000000");
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: add
	interval<double> lib_output_01 = p1788::infsup::add<interval<double>>(input_01, input_02);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		mul
// @description
// 		with mixed data types
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_08_mul)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hexStringToFloat("0x3F800000");
	float input_02_upper = hexStringToFloat("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: mul
	interval<float> lib_output_01 = p1788::infsup::mul<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		pos
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_09_pos)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: pos
	interval<double> lib_output_01 = pos(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		pos
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_10_pos)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: pos
	interval<float> lib_output_01 = p1788::infsup::pos<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		neg
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_11_neg)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: neg
	interval<double> lib_output_01 = neg(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		neg
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_12_neg)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: neg
	interval<float> lib_output_01 = p1788::infsup::neg<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		inv
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_13_inv)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: inv
	interval<double> lib_output_01 = inv(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		inv
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_14_inv)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: inv
	interval<float> lib_output_01 = p1788::infsup::inv<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		fma
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_15_fma)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hexStringToDouble("0x3FF0000000000000");
	double input_02_upper = hexStringToDouble("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hexStringToDouble("0x3FF0000000000000");
	double input_03_upper = hexStringToDouble("0x4000000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: fma
	interval<double> lib_output_01 = fma(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		fma
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_16_fma)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hexStringToFloat("0x3F800000");
	float input_02_upper = hexStringToFloat("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hexStringToDouble("0x3FF0000000000000");
	double input_03_upper = hexStringToDouble("0x4000000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: fma
	interval<double> lib_output_01 = p1788::infsup::fma<interval<double>>(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		sqr
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_17_sqr)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: sqr
	interval<double> lib_output_01 = sqr(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		sqr
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_18_sqr)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: sqr
	interval<float> lib_output_01 = p1788::infsup::sqr<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		pown
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_19_pown)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	int input_02 = 10;
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: pown
	interval<double> lib_output_01 = pown(input_01, input_02);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		pown
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_20_pown)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	int input_02 = 10;
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: pown
	interval<float> lib_output_01 = p1788::infsup::pown<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		pow
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_21_pow)
{
	// input parameter 1:
	float input_01_lower = hexStringToFloat("0x41200000");
	float input_01_upper = hexStringToFloat("0x41700000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hexStringToFloat("0x3F800000");
	float input_02_upper = hexStringToFloat("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: pow
	interval<float> lib_output_01 = pow(input_01, input_02);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		pow
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_22_pow)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hexStringToFloat("0x3F800000");
	float input_02_upper = hexStringToFloat("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: pow
	interval<float> lib_output_01 = p1788::infsup::pow<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		exp
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_23_exp)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: exp
	interval<double> lib_output_01 = exp(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		exp
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_24_exp)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: exp
	interval<float> lib_output_01 = p1788::infsup::exp<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		exp2
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_25_exp)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: exp2
	interval<double> lib_output_01 = exp2(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		exp2
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_26_exp)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: exp2
	interval<float> lib_output_01 = p1788::infsup::exp2<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		exp10
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_27_exp)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: exp10
	interval<double> lib_output_01 = exp10(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		exp10
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_28_exp)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: exp10
	interval<float> lib_output_01 = p1788::infsup::exp10<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		log
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_29_log)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: log
	interval<double> lib_output_01 = log(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		log
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_30_log)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: log
	interval<float> lib_output_01 = p1788::infsup::log<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		log2
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_31_log)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: log2
	interval<double> lib_output_01 = log2(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		log2
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_32_log)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: log2
	interval<float> lib_output_01 = p1788::infsup::log2<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		log10
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_33_log)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: log10
	interval<double> lib_output_01 = log10(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		log10
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_34_log)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: log10
	interval<float> lib_output_01 = p1788::infsup::log10<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		sin
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_35_sin)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: sin
	interval<double> lib_output_01 = sin(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		sin
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_36_sin)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: sin
	interval<float> lib_output_01 = p1788::infsup::sin<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		cos
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_37_cos)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: cos
	interval<double> lib_output_01 = cos(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		cos
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_38_cos)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: cos
	interval<float> lib_output_01 = p1788::infsup::cos<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		tan
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_39_tan)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: tan
	interval<double> lib_output_01 = tan(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		tan
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_40_tan)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: tan
	interval<float> lib_output_01 = p1788::infsup::tan<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		asin
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_41_asin)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: asin
	interval<double> lib_output_01 = asin(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		asin
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_42_asin)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: asin
	interval<float> lib_output_01 = p1788::infsup::asin<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		acos
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_43_acos)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: acos
	interval<double> lib_output_01 = acos(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		acos
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_44_acos)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: acos
	interval<float> lib_output_01 = p1788::infsup::acos<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		atan
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_45_atan)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: atan
	interval<double> lib_output_01 = atan(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		atan
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_46_atan)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: atan
	interval<float> lib_output_01 = p1788::infsup::atan<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		atan2
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_47_atan)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hexStringToDouble("0x3FF0000000000000");
	double input_02_upper = hexStringToDouble("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: atan2
	interval<double> lib_output_01 = atan2(input_01, input_02);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		atan2
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_48_atan)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hexStringToFloat("0x3F800000");
	float input_02_upper = hexStringToFloat("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: atan2
	interval<float> lib_output_01 = p1788::infsup::atan2<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		sinh
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_49_sinh)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: sinh
	interval<double> lib_output_01 = sinh(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		sinh
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_50_sinh)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: sinh
	interval<float> lib_output_01 = p1788::infsup::sinh<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		cosh
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_51_cosh)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: cosh
	interval<double> lib_output_01 = cosh(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		cosh
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_52_cosh)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: cosh
	interval<float> lib_output_01 = p1788::infsup::cosh<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		tanh
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_53_tanh)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: tanh
	interval<double> lib_output_01 = tanh(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		tanh
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_54_tanh)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: tanh
	interval<float> lib_output_01 = p1788::infsup::tanh<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		asinh
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_55_asinh)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: asinh
	interval<double> lib_output_01 = asinh(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		asinh
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_56_asinh)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: asinh
	interval<float> lib_output_01 = p1788::infsup::asinh<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		acosh
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_57_acosh)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: acosh
	interval<double> lib_output_01 = acosh(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		acosh
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_58_acosh)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: acosh
	interval<float> lib_output_01 = p1788::infsup::acosh<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		atanh
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_59_atanh)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: atanh
	interval<double> lib_output_01 = atanh(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		atanh
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_60_atanh)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: atanh
	interval<float> lib_output_01 = p1788::infsup::atanh<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		sign
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_61_sign)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: sign
	interval<double> lib_output_01 = sign(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		sign
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_62_sign)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: sign
	interval<float> lib_output_01 = p1788::infsup::sign<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		ceil
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_63_ceil)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: ceil
	interval<double> lib_output_01 = ceil(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		ceil
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_64_ceil)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: ceil
	interval<float> lib_output_01 = p1788::infsup::ceil<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		floor
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_65_floor)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: floor
	interval<double> lib_output_01 = floor(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		floor
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_66_floor)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: floor
	interval<float> lib_output_01 = p1788::infsup::floor<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		trunc
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_67_trunc)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: trunc
	interval<double> lib_output_01 = trunc(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		trunc
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_68_trunc)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: trunc
	interval<float> lib_output_01 = p1788::infsup::trunc<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		round_ties_to_even
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_69_roundtiestoeven)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: round_ties_to_even
	interval<double> lib_output_01 = round_ties_to_even(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		round_ties_to_even
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_70_roundtiestoeven)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: round_ties_to_even
	interval<float> lib_output_01 = p1788::infsup::round_ties_to_even<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		round_ties_to_away
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_71_roundtiestoaway)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: round_ties_to_away
	interval<double> lib_output_01 = round_ties_to_away(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		round_ties_to_away
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_72_roundtiestoaway)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: round_ties_to_away
	interval<float> lib_output_01 = p1788::infsup::round_ties_to_away<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		abs
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_73_abs)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: abs
	interval<double> lib_output_01 = abs(input_01);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		abs
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_74_abs)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: abs
	interval<float> lib_output_01 = p1788::infsup::abs<interval<float>>(input_01);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		min
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_75_min)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hexStringToDouble("0x4024000000000000");
	double input_02_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: min
	interval<double> lib_output_01 = min(input_01, input_02);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		min
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_76_min)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hexStringToDouble("0x4024000000000000");
	double input_02_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hexStringToDouble("0x4024000000000000");
	double input_03_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// input parameter 4:
	double input_04_lower = hexStringToDouble("0x4024000000000000");
	double input_04_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_04(input_04_lower, input_04_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: min
	interval<float> lib_output_01 = p1788::infsup::min<interval<float>>(input_01, input_02, input_03, input_04);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		max
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_77_max)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hexStringToDouble("0x4024000000000000");
	double input_02_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_01_lower = -std::numeric_limits<double>::infinity();
	double output_01_upper = +std::numeric_limits<double>::infinity();
	interval<double> output_01(output_01_lower, output_01_upper);
	
	// operation to test: max
	interval<double> lib_output_01 = max(input_01, input_02);
	
	// assert function for output 1:
	double lo_output_01 = output_01.lower();
	double lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	double hi_output_01 = output_01.upper();
	double hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

// @name
// 		max
// @required
// 		true
BOOST_AUTO_TEST_CASE(testcase_78_max)
{
	// input parameter 1:
	double input_01_lower = hexStringToDouble("0x4024000000000000");
	double input_01_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hexStringToDouble("0x4024000000000000");
	double input_02_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hexStringToDouble("0x4024000000000000");
	double input_03_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// input parameter 4:
	double input_04_lower = hexStringToDouble("0x4024000000000000");
	double input_04_upper = hexStringToDouble("0x402E000000000000");
	interval<double> input_04(input_04_lower, input_04_upper);
	// expected output parameter 1:
	float output_01_lower = -std::numeric_limits<float>::infinity();
	float output_01_upper = +std::numeric_limits<float>::infinity();
	interval<float> output_01(output_01_lower, output_01_upper);
	
	// operation to test: max
	interval<float> lib_output_01 = p1788::infsup::max<interval<float>>(input_01, input_02, input_03, input_04);
	
	// assert function for output 1:
	float lo_output_01 = output_01.lower();
	float lo_lib_output_01 = lib_output_01.lower();
	BOOST_REQUIRE(lo_lib_output_01 == lo_output_01);
	float hi_output_01 = output_01.upper();
	float hi_lib_output_01 = lib_output_01.upper();
	BOOST_REQUIRE(hi_lib_output_01 == hi_output_01);
	
}

BOOST_AUTO_TEST_SUITE_END()
