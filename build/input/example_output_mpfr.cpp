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
using interval = p1788::infsup::interval<T, p1788::flavor::infsup::mpfr_flavor>;


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
unsigned double_length = sizeof(double);
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
// 		is_empty
// @description
// 		default - no mixed types
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_01_isempty)
{
	// input parameter 1:
	interval<float> input = interval<float>::empty();
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: is_empty
	bool lib_output = is_empty(input);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		is_entire
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_02_isentire)
{
	// input parameter 1:
	interval<float> input = interval<float>::entire();
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: is_entire
	bool lib_output = is_entire(input);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		is_equal
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_03_isequal)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: is_equal
	bool lib_output = is_equal(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		contained_in
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_04_containedin)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: contained_in
	bool lib_output = contained_in(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		contains
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_05_contains)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: contains
	bool lib_output = contains(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		less
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_06_less)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: less
	bool lib_output = less(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		greater
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_07_greater)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: greater
	bool lib_output = greater(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		precedes
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_08_precedes)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: precedes
	bool lib_output = precedes(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		succeeds
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_09_succeeds)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: succeeds
	bool lib_output = succeeds(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		is_interior
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_10_isinterior)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: is_interior
	bool lib_output = is_interior(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		contains_interior
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_11_containsinterior)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: contains_interior
	bool lib_output = contains_interior(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		strictly_less
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_12_strictlyless)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: strictly_less
	bool lib_output = strictly_less(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		strictly_greater
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_13_strictlygreater)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: strictly_greater
	bool lib_output = strictly_greater(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		strictly_precedes
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_14_strictlyprecedes)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: strictly_precedes
	bool lib_output = strictly_precedes(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		strictly_succeeds
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_15_strictlysucceeds)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: strictly_succeeds
	bool lib_output = strictly_succeeds(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

// @name
// 		are_disjoint
// @required
// 		true
BOOST_AUTO_TEST_CASE(test_16_aredisjoint)
{
	// input parameter 1:
	float input_01_lower = hex_string_to_float("0x3F800000");
	float input_01_upper = hex_string_to_float("0x40000000");
	interval<float> input_01(input_01_lower, input_01_upper);
	// input parameter 2:
	float input_02_lower = hex_string_to_float("0x3F800000");
	float input_02_upper = hex_string_to_float("0x40000000");
	interval<float> input_02(input_02_lower, input_02_upper);
	// expected output parameter 1:
	bool output = true;
	
	// operation to test: are_disjoint
	bool lib_output = are_disjoint(input_01, input_02);
	
	// assert function for output 1:
	BOOST_REQUIRE(lib_output == output);
	
}

BOOST_AUTO_TEST_SUITE_END()
