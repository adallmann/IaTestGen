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
// 		Marco Nehmeier,
// 		Michael Jedich
// @dsl_version
// 		0.8, 21.03.2013
// ************************************************************

#include <iostream>


#include <limits>
#include "p1788/p1788.hpp"
template<typename T>
using interval = p1788::infsup::interval<T, p1788::flavor::infsup::ieee754_flavor>;


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "main_unit_test"
#include <boost/test/unit_test.hpp>


// Hex to Float Conversion
const unsigned float_length = sizeof(float);
float hex_string_to_float(std::string hexStr) {
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
const unsigned double_length = sizeof(double);
double hex_string_to_double(std::string hexStr) {
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
// 		intersect
// @description
// 		default - no mixed types
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_01_intersect)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x3FC0A3D70A3D70A4");
	double input_01_upper = hex_string_to_double("0x3FCD70A3D70A3D71");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x3FF0000000000000");
	double input_02_upper = hex_string_to_double("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = hex_string_to_double("0x3FC0A3D70A3D70A4");
	double output_upper = hex_string_to_double("0x3FDD70A3D70A3D71");
	interval<double> output(output_lower, output_upper);
	
	// operation to test: intersect
	interval<double> lib_output = intersect(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		intersect
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_02_intersect)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x3FC0A3D70A3D70A4");
	double input_01_upper = hex_string_to_double("0x3FCD70A3D70A3D71");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: intersect
	interval<float> lib_output = p1788::infsup::intersect<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		hull
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_03_hull)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x3FF0000000000000");
	double input_02_upper = hex_string_to_double("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: hull
	interval<double> lib_output = hull(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		hull
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_04_hull)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: hull
	interval<float> lib_output = p1788::infsup::hull<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		inf
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_05_inf)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output = hex_string_to_double("0x4028000000000000");
	
	// operation to test: inf
	double lib_output = inf(input);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		sup
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_06_sup)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output = hex_string_to_double("0x4028000000000000");
	
	// operation to test: sup
	double lib_output = sup(input);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output != output);
	
}

// @name
// 		mid
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_07_mid)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output = hex_string_to_double("0x4028000000000000");
	
	// operation to test: mid
	double lib_output = mid(input);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		rad
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_08_rad)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output = hex_string_to_double("0x4028000000000000");
	
	// operation to test: rad
	double lib_output = rad(input);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		mid_rad
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_09_midrad)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_01 = hex_string_to_double("0x401C000000000000");
	// expected output parameter 2:
	double output_02 = hex_string_to_double("0x4020000000000000");
	
	// operation to test: mid_rad
	double lib_output_01 = mid_rad(input).first;
	double lib_output_02 = mid_rad(input).second;
	
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output_01 == output_01);
	
	// assert function for output 2:
	BOOST_REQUIRE(lib_output_02 == output_02);
	
}

// @name
// 		wid
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_10_wid)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output = hex_string_to_double("0x4028000000000000");
	
	// operation to test: wid
	double lib_output = wid(input);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		mag
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_11_mag)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output = hex_string_to_double("0x4028000000000000");
	
	// operation to test: mag
	double lib_output = mag(input);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		mig
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_12_mig)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output = hex_string_to_double("0x4028000000000000");
	
	// operation to test: mig
	double lib_output = mig(input);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		pos
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_13_pos)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: pos
	interval<double> lib_output = pos(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pos
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_14_pos)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: pos
	interval<float> lib_output = p1788::infsup::pos<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		neg
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_15_neg)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: neg
	interval<double> lib_output = neg(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		neg
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_16_neg)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: neg
	interval<float> lib_output = p1788::infsup::neg<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		add
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_17_add)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x3FF0000000000000");
	double input_02_upper = hex_string_to_double("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: add
	interval<double> lib_output = add(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output < lo_output || lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output > hi_output || hi_lib_output == hi_output);
	
}

// @name
// 		add
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_18_add)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = hex_string_to_double("0x4014000000000000");
	double output_upper = hex_string_to_double("0x4022000000000000");
	interval<double> output(output_lower, output_upper);
	
	// operation to test: add
	interval<double> lib_output = p1788::infsup::add<interval<double>>(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sub
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_19_sub)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: sub
	interval<float> lib_output = p1788::infsup::sub<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sub
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_20_sub)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = hex_string_to_double("0x4014000000000000");
	double output_upper = hex_string_to_double("0x4022000000000000");
	interval<double> output(output_lower, output_upper);
	
	// operation to test: sub
	interval<double> lib_output = p1788::infsup::sub<interval<double>>(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		mul
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_21_mul)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: mul
	interval<float> lib_output = p1788::infsup::mul<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		mul
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_22_mul)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = hex_string_to_double("0x4014000000000000");
	double output_upper = hex_string_to_double("0x4022000000000000");
	interval<double> output(output_lower, output_upper);
	
	// operation to test: mul
	interval<double> lib_output = p1788::infsup::mul<interval<double>>(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		div
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_23_div)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: div
	interval<float> lib_output = p1788::infsup::div<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		div
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_24_div)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = hex_string_to_double("0x4014000000000000");
	double output_upper = hex_string_to_double("0x4022000000000000");
	interval<double> output(output_lower, output_upper);
	
	// operation to test: div
	interval<double> lib_output = p1788::infsup::div<interval<double>>(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		inv
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_25_inv)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: inv
	interval<double> lib_output = inv(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		inv
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_26_inv)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: inv
	interval<float> lib_output = p1788::infsup::inv<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sqrt
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_27_sqrt)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: sqrt
	interval<double> lib_output = sqrt(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sqrt
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_28_sqrt)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: sqrt
	interval<float> lib_output = p1788::infsup::sqrt<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		fma
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_29_fma)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x3FF0000000000000");
	double input_02_upper = hex_string_to_double("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x3FF0000000000000");
	double input_03_upper = hex_string_to_double("0x4000000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: fma
	interval<double> lib_output = fma(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		fma
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_30_fma)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x3FF0000000000000");
	double input_03_upper = hex_string_to_double("0x4000000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: fma
	interval<double> lib_output = p1788::infsup::fma<interval<double>>(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		interval_case
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_31_intervalcase)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x3FF0000000000000");
	double input_02_upper = hex_string_to_double("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x3FF0000000000000");
	double input_03_upper = hex_string_to_double("0x4000000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: interval_case
	interval<double> lib_output = interval_case(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		interval_case
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_32_intervalcase)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x3FF0000000000000");
	double input_03_upper = hex_string_to_double("0x4000000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: interval_case
	interval<double> lib_output = p1788::infsup::interval_case<interval<double>>(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sqr
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_33_sqr)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: sqr
	interval<double> lib_output = sqr(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sqr
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_34_sqr)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: sqr
	interval<float> lib_output = p1788::infsup::sqr<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pown
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_35_pown)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	int input_02 = 10;
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: pown
	interval<double> lib_output = pown(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pown
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_36_pown)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	int input_02 = 10;
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: pown
	interval<float> lib_output = p1788::infsup::pown<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pow
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_37_pow)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x41200000");
	float input_01_upper = hex_string_to_float("0x41700000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: pow
	interval<float> lib_output = pow(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pow
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_38_pow)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: pow
	interval<float> lib_output = p1788::infsup::pow<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		exp
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_39_exp)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: exp
	interval<double> lib_output = exp(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		exp
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_40_exp)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: exp
	interval<float> lib_output = p1788::infsup::exp<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		exp2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_41_exp)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: exp2
	interval<double> lib_output = exp2(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		exp2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_42_exp)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: exp2
	interval<float> lib_output = p1788::infsup::exp2<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		exp10
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_43_exp)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: exp10
	interval<double> lib_output = exp10(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		exp10
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_44_exp)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: exp10
	interval<float> lib_output = p1788::infsup::exp10<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		log
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_45_log)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: log
	interval<double> lib_output = log(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		log
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_46_log)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: log
	interval<float> lib_output = p1788::infsup::log<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		log2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_47_log)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: log2
	interval<double> lib_output = log2(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		log2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_48_log)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: log2
	interval<float> lib_output = p1788::infsup::log2<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		log10
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_49_log)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: log10
	interval<double> lib_output = log10(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		log10
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_50_log)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: log10
	interval<float> lib_output = p1788::infsup::log10<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sin
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_51_sin)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: sin
	interval<double> lib_output = sin(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sin
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_52_sin)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: sin
	interval<float> lib_output = p1788::infsup::sin<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cos
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_53_cos)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: cos
	interval<double> lib_output = cos(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cos
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_54_cos)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: cos
	interval<float> lib_output = p1788::infsup::cos<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		tan
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_55_tan)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: tan
	interval<double> lib_output = tan(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		tan
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_56_tan)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: tan
	interval<float> lib_output = p1788::infsup::tan<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		asin
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_57_asin)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: asin
	interval<double> lib_output = asin(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		asin
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_58_asin)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: asin
	interval<float> lib_output = p1788::infsup::asin<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		acos
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_59_acos)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: acos
	interval<double> lib_output = acos(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		acos
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_60_acos)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: acos
	interval<float> lib_output = p1788::infsup::acos<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atan
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_61_atan)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: atan
	interval<double> lib_output = atan(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atan
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_62_atan)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: atan
	interval<float> lib_output = p1788::infsup::atan<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atan2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_63_atan)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x3FF0000000000000");
	double input_02_upper = hex_string_to_double("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: atan2
	interval<double> lib_output = atan2(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atan2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_64_atan)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: atan2
	interval<float> lib_output = p1788::infsup::atan2<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sinh
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_65_sinh)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: sinh
	interval<double> lib_output = sinh(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sinh
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_66_sinh)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: sinh
	interval<float> lib_output = p1788::infsup::sinh<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cosh
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_67_cosh)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: cosh
	interval<double> lib_output = cosh(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cosh
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_68_cosh)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: cosh
	interval<float> lib_output = p1788::infsup::cosh<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		tanh
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_69_tanh)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: tanh
	interval<double> lib_output = tanh(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		tanh
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_70_tanh)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: tanh
	interval<float> lib_output = p1788::infsup::tanh<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		asinh
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_71_asinh)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: asinh
	interval<double> lib_output = asinh(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		asinh
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_72_asinh)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: asinh
	interval<float> lib_output = p1788::infsup::asinh<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		acosh
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_73_acosh)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: acosh
	interval<double> lib_output = acosh(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		acosh
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_74_acosh)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: acosh
	interval<float> lib_output = p1788::infsup::acosh<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atanh
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_75_atanh)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: atanh
	interval<double> lib_output = atanh(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atanh
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_76_atanh)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: atanh
	interval<float> lib_output = p1788::infsup::atanh<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sign
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_77_sign)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: sign
	interval<double> lib_output = sign(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sign
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_78_sign)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: sign
	interval<float> lib_output = p1788::infsup::sign<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		ceil
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_79_ceil)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: ceil
	interval<double> lib_output = ceil(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		ceil
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_80_ceil)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: ceil
	interval<float> lib_output = p1788::infsup::ceil<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		floor
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_81_floor)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: floor
	interval<double> lib_output = floor(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		floor
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_82_floor)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: floor
	interval<float> lib_output = p1788::infsup::floor<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		trunc
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_83_trunc)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: trunc
	interval<double> lib_output = trunc(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		trunc
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_84_trunc)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: trunc
	interval<float> lib_output = p1788::infsup::trunc<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		round_ties_to_even
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_85_roundtiestoeven)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: round_ties_to_even
	interval<double> lib_output = round_ties_to_even(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		round_ties_to_even
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_86_roundtiestoeven)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: round_ties_to_even
	interval<float> lib_output = p1788::infsup::round_ties_to_even<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		round_ties_to_away
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_87_roundtiestoaway)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: round_ties_to_away
	interval<double> lib_output = round_ties_to_away(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		round_ties_to_away
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_88_roundtiestoaway)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: round_ties_to_away
	interval<float> lib_output = p1788::infsup::round_ties_to_away<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		abs
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_89_abs)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: abs
	interval<double> lib_output = abs(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		abs
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_90_abs)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: abs
	interval<float> lib_output = p1788::infsup::abs<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		min
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_91_min)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: min
	interval<double> lib_output = min(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		min
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_92_min)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// input parameter 4:
	double input_04_lower = hex_string_to_double("0x4024000000000000");
	double input_04_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_04(input_04_lower, input_04_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: min
	interval<float> lib_output = p1788::infsup::min<interval<float>>(input_01, input_02, input_03, input_04);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		max
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_93_max)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: max
	interval<double> lib_output = max(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		max
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_94_max)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// input parameter 4:
	double input_04_lower = hex_string_to_double("0x4024000000000000");
	double input_04_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_04(input_04_lower, input_04_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: max
	interval<float> lib_output = p1788::infsup::max<interval<float>>(input_01, input_02, input_03, input_04);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sqr_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_95_sqrrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: sqr_rev
	interval<double> lib_output = sqr_rev(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sqr_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_96_sqrrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: sqr_rev
	interval<float> lib_output = p1788::infsup::sqr_rev<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sqr_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_97_sqrrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: sqr_rev
	interval<double> lib_output = sqr_rev(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sqr_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_98_sqrrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: sqr_rev
	interval<float> lib_output = p1788::infsup::sqr_rev<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		inv_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_99_invrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: inv_rev
	interval<double> lib_output = inv_rev(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		inv_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_100_invrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: inv_rev
	interval<float> lib_output = p1788::infsup::inv_rev<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		inv_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_101_invrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: inv_rev
	interval<double> lib_output = inv_rev(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		inv_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_102_invrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: inv_rev
	interval<float> lib_output = p1788::infsup::inv_rev<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		abs_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_103_absrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: abs_rev
	interval<double> lib_output = abs_rev(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		abs_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_104_absrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: abs_rev
	interval<float> lib_output = p1788::infsup::abs_rev<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		abs_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_105_absrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: abs_rev
	interval<double> lib_output = abs_rev(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		abs_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_106_absrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: abs_rev
	interval<float> lib_output = p1788::infsup::abs_rev<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pown_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_107_pownrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	int input_03 = 5;
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: pown_rev
	interval<double> lib_output = pown_rev(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pown_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_108_pownrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	int input_03 = 5;
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: pown_rev
	interval<float> lib_output = p1788::infsup::pown_rev<interval<float>>(input_01, input_02, input_03);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pown_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_109_pownrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	int input_02 = 5;
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: pown_rev
	interval<double> lib_output = pown_rev(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pown_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_110_pownrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	int input_02 = 5;
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: pown_rev
	interval<float> lib_output = p1788::infsup::pown_rev<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sin_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_111_sinrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: sin_rev
	interval<double> lib_output = sin_rev(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sin_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_112_sinrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: sin_rev
	interval<float> lib_output = p1788::infsup::sin_rev<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sin_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_113_sinrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: sin_rev
	interval<double> lib_output = sin_rev(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		sin_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_114_sinrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: sin_rev
	interval<float> lib_output = p1788::infsup::sin_rev<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cos_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_115_cosrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: cos_rev
	interval<double> lib_output = cos_rev(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cos_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_116_cosrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: cos_rev
	interval<float> lib_output = p1788::infsup::cos_rev<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cos_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_117_cosrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: cos_rev
	interval<double> lib_output = cos_rev(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cos_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_118_cosrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: cos_rev
	interval<float> lib_output = p1788::infsup::cos_rev<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		tan_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_119_tanrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: tan_rev
	interval<double> lib_output = tan_rev(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		tan_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_120_tanrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: tan_rev
	interval<float> lib_output = p1788::infsup::tan_rev<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		tan_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_121_tanrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: tan_rev
	interval<double> lib_output = tan_rev(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		tan_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_122_tanrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: tan_rev
	interval<float> lib_output = p1788::infsup::tan_rev<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cosh_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_123_coshrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: cosh_rev
	interval<double> lib_output = cosh_rev(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cosh_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_124_coshrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: cosh_rev
	interval<float> lib_output = p1788::infsup::cosh_rev<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cosh_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_125_coshrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: cosh_rev
	interval<double> lib_output = cosh_rev(input);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cosh_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_126_coshrev)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: cosh_rev
	interval<float> lib_output = p1788::infsup::cosh_rev<interval<float>>(input);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		mul_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_127_mulrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: mul_rev
	interval<double> lib_output = mul_rev(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		mul_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_128_mulrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: mul_rev
	interval<float> lib_output = p1788::infsup::mul_rev<interval<float>>(input_01, input_02, input_03);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		mul_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_129_mulrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: mul_rev
	interval<double> lib_output = mul_rev(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		mul_rev
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_130_mulrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: mul_rev
	interval<float> lib_output = p1788::infsup::mul_rev<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		div_rev1
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_131_divrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: div_rev1
	interval<double> lib_output = div_rev1(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		div_rev1
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_132_divrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: div_rev1
	interval<float> lib_output = p1788::infsup::div_rev1<interval<float>>(input_01, input_02, input_03);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		div_rev1
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_133_divrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: div_rev1
	interval<double> lib_output = div_rev1(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		div_rev1
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_134_divrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: div_rev1
	interval<float> lib_output = p1788::infsup::div_rev1<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		div_rev2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_135_divrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: div_rev2
	interval<double> lib_output = div_rev2(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		div_rev2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_136_divrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: div_rev2
	interval<float> lib_output = p1788::infsup::div_rev2<interval<float>>(input_01, input_02, input_03);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		div_rev2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_137_divrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: div_rev2
	interval<double> lib_output = div_rev2(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		div_rev2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_138_divrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: div_rev2
	interval<float> lib_output = p1788::infsup::div_rev2<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pow_rev1
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_139_powrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: pow_rev1
	interval<double> lib_output = pow_rev1(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pow_rev1
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_140_powrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: pow_rev1
	interval<float> lib_output = p1788::infsup::pow_rev1<interval<float>>(input_01, input_02, input_03);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pow_rev1
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_141_powrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: pow_rev1
	interval<double> lib_output = pow_rev1(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pow_rev1
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_142_powrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: pow_rev1
	interval<float> lib_output = p1788::infsup::pow_rev1<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pow_rev2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_143_powrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: pow_rev2
	interval<double> lib_output = pow_rev2(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pow_rev2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_144_powrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: pow_rev2
	interval<float> lib_output = p1788::infsup::pow_rev2<interval<float>>(input_01, input_02, input_03);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pow_rev2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_145_powrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: pow_rev2
	interval<double> lib_output = pow_rev2(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		pow_rev2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_146_powrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: pow_rev2
	interval<float> lib_output = p1788::infsup::pow_rev2<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atan2_rev1
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_147_atanrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: atan2_rev1
	interval<double> lib_output = atan2_rev1(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atan2_rev1
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_148_atanrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: atan2_rev1
	interval<float> lib_output = p1788::infsup::atan2_rev1<interval<float>>(input_01, input_02, input_03);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atan2_rev1
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_149_atanrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: atan2_rev1
	interval<double> lib_output = atan2_rev1(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atan2_rev1
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_150_atanrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: atan2_rev1
	interval<float> lib_output = p1788::infsup::atan2_rev1<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atan2_rev2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_151_atanrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: atan2_rev2
	interval<double> lib_output = atan2_rev2(input_01, input_02, input_03);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atan2_rev2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_152_atanrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// input parameter 3:
	double input_03_lower = hex_string_to_double("0x4024000000000000");
	double input_03_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_03(input_03_lower, input_03_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: atan2_rev2
	interval<float> lib_output = p1788::infsup::atan2_rev2<interval<float>>(input_01, input_02, input_03);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atan2_rev2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_153_atanrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x4024000000000000");
	double input_02_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: atan2_rev2
	interval<double> lib_output = atan2_rev2(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		atan2_rev2
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_154_atanrev)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x41200000");
	float input_02_upper = hex_string_to_float("0x41700000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: atan2_rev2
	interval<float> lib_output = p1788::infsup::atan2_rev2<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cancel_plus
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_155_cancelplus)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: cancel_plus
	interval<float> lib_output = p1788::infsup::cancel_plus<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cancel_plus
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_156_cancelplus)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x3FF0000000000000");
	double input_02_upper = hex_string_to_double("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: cancel_plus
	interval<double> lib_output = cancel_plus(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cancel_minus
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_157_cancelminus)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	float output_lower = -std::numeric_limits<float>::infinity();
	float output_upper = +std::numeric_limits<float>::infinity();
	interval<float> output(output_lower, output_upper);
	
	// operation to test: cancel_minus
	interval<float> lib_output = p1788::infsup::cancel_minus<interval<float>>(input_01, input_02);
	
	// assert function for output 1:
	float lo_output = output.lower();
	float lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	float hi_output = output.upper();
	float hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

// @name
// 		cancel_minus
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_158_cancelminus)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0x4024000000000000");
	double input_01_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x3FF0000000000000");
	double input_02_upper = hex_string_to_double("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	double output_lower = -std::numeric_limits<double>::infinity();
	double output_upper = +std::numeric_limits<double>::infinity();
	interval<double> output(output_lower, output_upper);
	
	// operation to test: cancel_minus
	interval<double> lib_output = cancel_minus(input_01, input_02);
	
	// assert function for output 1:
	double lo_output = output.lower();
	double lo_lib_output = lib_output.lower();
	BOOST_REQUIRE(lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output == hi_output);
	
}

BOOST_AUTO_TEST_SUITE_END()
