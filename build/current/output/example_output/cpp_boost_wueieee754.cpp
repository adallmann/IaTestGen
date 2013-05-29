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
// 		inf
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_01_inf)
{
	// input parameter 1:
	double input_lower = hex_string_to_double("0x4024000000000000");
	double input_upper = hex_string_to_double("0x402E000000000000");
	interval<double> input(input_lower, input_upper);
	// expected output parameter 1:
	double output = hex_string_to_double("0x4024000000000000");
	
	// operation to test: inf
	double lib_output = inf(input);	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
}

// @name
// 		is_empty
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_02_isempty)
{
	// input parameter 1:
	interval<double> input = interval<double>::empty();
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: is_empty
	bool lib_output = is_empty(input);	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
}

// @name
// 		contains
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_03_contains)
{
	// input parameter 1:
	double input_01_lower = hex_string_to_double("0xC024000000000000");
	double input_01_upper = hex_string_to_double("0x4008000000000000");
	interval<double> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	double input_02_lower = hex_string_to_double("0x3FF0000000000000");
	double input_02_upper = hex_string_to_double("0x4000000000000000");
	interval<double> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: contains
	bool lib_output = contains(input_01, input_02);	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
}

// @name
// 		add
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_04_add)
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
	BOOST_REQUIRE(lo_lib_output > lo_output || lo_lib_output == lo_output);
	double hi_output = output.upper();
	double hi_lib_output = lib_output.upper();
	BOOST_REQUIRE(hi_lib_output < hi_output || hi_lib_output == hi_output);
	
}

// @name
// 		add
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_05_add)
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
	double output_lower = hex_string_to_double("0x4026000000000000");
	double output_upper = hex_string_to_double("0x4031000000000000");
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
// 		mul
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_06_mul)
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
	float output_lower = hex_string_to_float("0x41200000");
	float output_upper = hex_string_to_float("0x41F00000");
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
BOOST_AUTO_TEST_CASE(test_07_mul)
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
	double output_lower = hex_string_to_double("0x4024000000000000");
	double output_upper = hex_string_to_double("0x403E000000000000");
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

BOOST_AUTO_TEST_SUITE_END()

