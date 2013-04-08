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
$sampleInfinite 	= interval<double>[-inf, +inf];


// -----------------------------------------------------------------------------
// Forward elementary functions
// -----------------------------------------------------------------------------

/**
 * Addition-test.
 * @description 
 *	  default - no mixed types;	
 * @required
 * 		true;
 */
add( interval<double>[10.0, 15.0], interval<double>[1.0, 2.0] ) = $sampleInfinite;

/**
 * @description
 * 		calculated result should be a PROPER SUBSET of the expected;
 * @required
 * 		true;
 */
add( interval<double>[10, 15], interval<double>[1, 2] ) subsetneq= interval<double>[-inf, +inf];

/**
 * @description
 * 		calculated result should be NOT A PROPER SUBSET of the expected (--> superset);
 * @required
 * 		true;
 */
add( interval<double>[10, 15], interval<double>[1, 2] ) !subsetneq= interval<double>[-inf, +inf];

/**
 * @description
 * 		calculated result should be a SUBSET (not proper subset) of the expected;
 * @required
 * 		true;
 */
add( interval<double>[10, 15], interval<double>[1, 2] ) subseteq= interval<double>[-inf, +inf];

/**
 * @description
 * 		calculated result should be a PROPER SUPERSET of the expected;
 * @required
 * 		true;
 */
add( interval<double>[10, 15], interval<double>[1, 2] ) supersetneq= interval<double>[-inf, +inf];

/**
 * @description
 * 		calculated result should be a SUPERSET (not a proper one) of the expected;
 * @required
 * 		true;
 */
add( interval<double>[10, 15], interval<double>[1, 2] ) superseteq= interval<double>[-inf, +inf];

/**
 * @description 
 *		-addition operation with mixed data types
 * 		-negation;
 * @required
 * 		true;
 */
add<interval<double>>( interval<double>[10, 15], interval<float>[1, 2] ) 
	!= interval<double>[5.0, 9];

/**
 * Multiplication-test.
 * @description 
 *		with mixed data types;
 * @required
 * 		true;
 */
mul<interval<float>>( interval<double>[10, 15], interval<float>[1, 2] ) 
	= interval<float>[-inf, +inf];


// ---------------------------------------------------------------------

pos( interval<double>[10, 15] ) = interval<double>[-inf, +inf];
pos<interval<float>>(interval<double>[10, 15] ) = interval<float>[-inf, +inf];

neg( interval<double>[10, 15] ) = interval<double>[-inf, +inf];
neg<interval<float>>(interval<double>[10, 15] ) = interval<float>[-inf, +inf];

inv( interval<double>[10, 15] ) = interval<double>[-inf, +inf];
inv<interval<float>>(interval<double>[10, 15] ) = interval<float>[-inf, +inf];

fma( interval<double>[10, 15], interval<double>[1, 2], 
	interval<double>[1, 2] ) = interval<double>[-inf, +inf];
fma<interval<double>>( interval<double>[10, 15], interval<float>[1, 2], 
	interval<double>[1, 2] ) = interval<double>[-inf, +inf];

sqr(interval<double>[10, 15]) = interval<double>[-inf, +inf];
sqr<interval<float>>( interval<double>[10, 15] ) = interval<float>[-inf, +inf];

pown(interval<double>[10, 15], int: 10) = interval<double>[-inf, +inf];
pown<interval<float>>(interval<double>[10, 15], int: 10) = interval<float>[-inf, +inf];

pow(interval<float>[10, 15], interval<float>[1, 2] ) 
	= interval<float>[-inf, +inf];
pow<interval<float>>( interval<double>[10, 15], interval<float>[1, 2] ) 
	= interval<float>[-inf, +inf];

exp(interval<double>[10, 15]) = interval<double>[-inf, +inf];
exp<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

exp2(interval<double>[10, 15]) = interval<double>[-inf, +inf];
exp2<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

exp10(interval<double>[10, 15]) = interval<double>[-inf, +inf];
exp10<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

log(interval<double>[10, 15]) = interval<double>[-inf, +inf];
log<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

log2(interval<double>[10, 15]) = interval<double>[-inf, +inf];
log2<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

log10(interval<double>[10, 15]) = interval<double>[-inf, +inf];
log10<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

sin(interval<double>[10, 15]) = interval<double>[-inf, +inf];
sin<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

cos(interval<double>[10, 15]) = interval<double>[-inf, +inf];
cos<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

tan(interval<double>[10, 15]) = interval<double>[-inf, +inf];
tan<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

asin(interval<double>[10, 15]) = interval<double>[-inf, +inf];
asin<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

acos(interval<double>[10, 15]) = interval<double>[-inf, +inf];
acos<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

atan(interval<double>[10, 15]) = interval<double>[-inf, +inf];
atan<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

atan2(interval<double>[10, 15], interval<double>[1, 2] ) 
	= interval<double>[-inf, +inf];
atan2<interval<float>>( interval<double>[10, 15], interval<float>[1, 2] ) 
	= interval<float>[-inf, +inf];

sinh(interval<double>[10, 15]) = interval<double>[-inf, +inf];
sinh<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

cosh(interval<double>[10, 15]) = interval<double>[-inf, +inf];
cosh<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

tanh(interval<double>[10, 15]) = interval<double>[-inf, +inf];
tanh<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

asinh(interval<double>[10, 15]) = interval<double>[-inf, +inf];
asinh<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

acosh(interval<double>[10, 15]) = interval<double>[-inf, +inf];
acosh<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

atanh(interval<double>[10, 15]) = interval<double>[-inf, +inf];
atanh<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

sign(interval<double>[10, 15]) = interval<double>[-inf, +inf];
sign<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

ceil(interval<double>[10, 15]) = interval<double>[-inf, +inf];
ceil<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

floor(interval<double>[10, 15]) = interval<double>[-inf, +inf];
floor<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

trunc(interval<double>[10, 15]) = interval<double>[-inf, +inf];
trunc<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

round_ties_to_even(interval<double>[10, 15]) = interval<double>[-inf, +inf];
round_ties_to_even<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

round_ties_to_away(interval<double>[10, 15]) = interval<double>[-inf, +inf];
round_ties_to_away<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

abs(interval<double>[10, 15]) = interval<double>[-inf, +inf];
abs<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

min(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
min<interval<float>>(interval<double>[10, 15], interval<double>[10, 15], 
	interval<double>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];

max(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
max<interval<float>>(interval<double>[10, 15], interval<double>[10, 15], 
	interval<double>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];

// -----------------------------------------------------------------------------
// Reverse elementary functions, see P1788/D7.0 Sect. 9.6.5 Table 2
// -----------------------------------------------------------------------------

// reverse version of unary point functions




