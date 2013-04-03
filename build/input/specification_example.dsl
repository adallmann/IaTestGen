// 
//    IaTestGen - Interval arithmetic test generator
//    Copyright 2013
// 
//    Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
//    Institute of Computer Science,
//    University of Wuerzburg, Germany
// 
//    Michael Jedich (m.jedich@gmail.com)
//    University of Wuerzburg, Germany
// 
// 
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
// 
//    http://www.apache.org/licenses/LICENSE-2.0
// 
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
// 


/**
 * Example Domain-Specific-Language.
 *
 * @author 
 *		Michael Jedich;
 * @version 
 *		0.8, 21.03.2013;
 * @description 
 *		Sample-file with a couple of simple testfunctions for libieeep1788;
 */

// sample variables: 
$lowerLimit01 		= double: 0x3FC0A3D70A3D70A4;
$upperLimit01 		= double: 0x3FCD70A3D70A3D71;
$lowerLimit02 		= float: 	0xC0D05BC0;
$upperLimit02 		= float: 	0x414E147B;
$sampleInteter 		= int: 		5;
$sampleInterval 	= interval<double>[$lowerLimit01, 0x3FDD70A3D70A3D71];

/**
 * Addition-test.
 * @required
 * 		true;
 */
add( interval<double>[10, 15], interval<double>[1, 2] ) = interval<double>[8, 14];

/**
 * Addition-test.
 * @description 
 *		addition operation with mixed data types;
 * @required
 * 		true;
 */
add( interval<double>[10, 15], interval<float>[1, 2] ) = interval<double>[8, 14];


/**
 * Multiplication-test.
 * @description 
 *		with mixed data types;
 * @required
 * 		true;
 */
mul( interval<double>[10, 15], interval<float>[1, 2] ) = interval<float>[8, 14];

/**
 * Pos-test.
 * @required
 * 		true;
 */
pos( interval<double>[10, 15] ) = interval<double>[8, 14];

/**
 * Neg-test.
 * @required
 * 		true;
 */
neg( interval<double>[10, 15] ) = interval<double>[8, 14];

/**
 * Inv-Test.
 * @required
 * 		false;
 */
inv( interval<float>[10, 15] ) = interval<double>[8, 14];


/**
 * Fam-test.
 * @required
 * 		false;
 */
fma( interval<double>[10, 15], interval<float>[1, 2], interval<double>[1, 2] ) = interval<double>[8, 14];
