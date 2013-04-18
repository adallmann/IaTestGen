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


// -----------------------------------------------------------------------------
// Unit Tests will be generated with given Annotations: 
// @author, @version, @description
// close annotations with a semicolon
// -----------------------------------------------------------------------------

/**
 * Example Domain-Specific-Language.
 *
 * @author 
 *    Marco Nehmeier,
 *		Michael Jedich;
 * @version 
 *		0.8, 21.03.2013;
 * @description 
 *		Sample-file with a couple of simple testfunctions for libieeep1788;
 */

  
// -----------------------------------------------------------------------------
// Some examples of variables 
// -----------------------------------------------------------------------------

$lowerLimit01 		= double: 0x3FC0A3D70A3D70A4;
$upperLimit01 		= double: 0x3FCD70A3D70A3D71;
$lowerLimit02 		= float: 	0xC0D05BC0;
$upperLimit02 		= float: 	0x414E147B;
$sampleInteger 		= int: 		5;
$sampleInterval 	= interval<double>[$lowerLimit01, 0x3FDD70A3D70A3D71];
$sampleInfinite 	= interval<double>[-inf, +inf];



// -----------------------------------------------------------------------------
// posible set operators:
// -----------------------------------------------------------------------------
// supersetneq= // --> proper superset
// superseteq= 
// subsetneq= // --> proper subset
// subseteq=
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Non-arithmetic set operations, see P1788/D7.1 Sect. 9.6.7
// -----------------------------------------------------------------------------

/**
 * Intersect-test. Each operation-test can have its own description.
 * @description 
 *	  default - no mixed types;	
 * @required
 * 		true;
 */
intersect( interval<double>[0x3FC0A3D70A3D70A4, 0x3FCD70A3D70A3D71], 
	interval<double>[1, 2] ) = $sampleInterval;
intersect<interval<float>>( interval<double>[0x3FC0A3D70A3D70A4, 0x3FCD70A3D70A3D71], 
	interval<float>[1, 2] ) = interval<float>[-inf, +inf];

hull( interval<double>[10, 15], interval<double>[1, 2] ) 
	= interval<double>[-inf, +inf];
hull<interval<float>>( interval<double>[10, 15], interval<float>[1, 2] ) 
	= interval<float>[-inf, +inf];

// -----------------------------------------------------------------------------
// Numeric functions on intervals, see P1788/D7.1 Sect. 9.6.9
// -----------------------------------------------------------------------------

inf( interval<double>[10, 15]) = double: 12;

sup( interval<double>[10, 15]) != double: 12;

mid( interval<double>[10, 15]) = double: 12;

rad( interval<double>[10, 15]) = double: 12;

mid_rad( interval<double>[10, 15]) = double: 7, double: 8;

wid( interval<double>[10, 15]) = double: 12;

mag( interval<double>[10, 15]) = double: 12;

mig( interval<double>[10, 15]) = double: 12;

// -----------------------------------------------------------------------------
// Boolean functions on intervals, see P1788/D7.0 Sect. 9.6.10
// -----------------------------------------------------------------------------

// is_empty( interval<float>[empty] ) = true;
// 
// is_entire( interval<float>[entire] ) = false;
// 
// is_equal( interval<float>[1,2], interval<float>[1,2] ) = true;
// 
// contained_in( interval<float>[1,2], interval<float>[1,2] ) = true;
// 
// contains( interval<float>[1,2], interval<float>[1,2] ) = true;
// 
// less( interval<float>[1,2], interval<float>[1,2] ) = true;
// 
// greater( interval<float>[1,2], interval<float>[1,2] ) = true;
// 
// precedes( interval<float>[1,2], interval<float>[1,2] ) = true;
// 
// succeeds( interval<float>[1,2], interval<float>[1,2] ) = true;
// 
// is_interior( interval<float>[1,2], interval<float>[1,2] ) = true;
// 
// contains_interior( interval<float>[1,2], interval<float>[1,2] ) = true;
// 
// strictly_less( interval<float>[1,2], interval<float>[1,2] ) = true;
// 
// strictly_greater( interval<float>[1,2], interval<float>[1,2] ) = true;
// 
// strictly_precedes( interval<float>[1,2], interval<float>[1,2] ) = true;
// 
// strictly_succeeds( interval<float>[1,2], interval<float>[1,2] ) = true;
// 
// are_disjoint( interval<float>[1,2], interval<float>[1,2] ) = true;

// -----------------------------------------------------------------------------
// Forward elementary functions
// -----------------------------------------------------------------------------

pos( interval<double>[10, 15] ) = interval<double>[-inf, +inf];
pos<interval<float>>(interval<double>[10, 15] ) = interval<float>[-inf, +inf];

neg( interval<double>[10, 15] ) = interval<double>[-inf, +inf];
neg<interval<float>>(interval<double>[10, 15] ) = interval<float>[-inf, +inf];
 
add( interval<double>[10, 15], interval<double>[1, 2] ) superseteq= interval<double>[-inf, +inf];
add<interval<double>>( interval<double>[10, 15], interval<float>[1, 2] ) 
	!= interval<double>[5.0, 9];

sub<interval<float>>( interval<double>[10, 15], interval<float>[1, 2] ) 
	= interval<float>[-inf, +inf];
sub<interval<double>>( interval<double>[10, 15], interval<float>[1, 2] ) 
	= interval<double>[5.0, 9];

mul<interval<float>>( interval<double>[10, 15], interval<float>[1, 2] ) 
	= interval<float>[-inf, +inf];
mul<interval<double>>( interval<double>[10, 15], interval<float>[1, 2] ) 
	= interval<double>[5.0, 9];

div<interval<float>>( interval<double>[10, 15], interval<float>[1, 2] ) 
	= interval<float>[-inf, +inf];
div<interval<double>>( interval<double>[10, 15], interval<float>[1, 2] ) 
	= interval<double>[5.0, 9];

inv( interval<double>[10, 15] ) = interval<double>[-inf, +inf];
inv<interval<float>>(interval<double>[10, 15] ) = interval<float>[-inf, +inf];

sqrt( interval<double>[10, 15] ) = interval<double>[-inf, +inf];
sqrt<interval<float>>(interval<double>[10, 15] ) = interval<float>[-inf, +inf];

fma( interval<double>[10, 15], interval<double>[1, 2], 
	interval<double>[1, 2] ) = interval<double>[-inf, +inf];
fma<interval<double>>( interval<double>[10, 15], interval<float>[1, 2], 
	interval<double>[1, 2] ) = interval<double>[-inf, +inf];

interval_case( interval<double>[10, 15], interval<double>[1, 2], 
	interval<double>[1, 2] ) = interval<double>[-inf, +inf];
interval_case<interval<double>>( interval<double>[10, 15], interval<float>[1, 2], 
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

sqr_rev(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
sqr_rev<interval<float>>(interval<double>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
sqr_rev(interval<double>[10, 15]) = interval<double>[-inf, +inf];
sqr_rev<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

inv_rev(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
inv_rev<interval<float>>(interval<double>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
inv_rev(interval<double>[10, 15]) = interval<double>[-inf, +inf];
inv_rev<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

abs_rev(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
abs_rev<interval<float>>(interval<double>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
abs_rev(interval<double>[10, 15]) = interval<double>[-inf, +inf];
abs_rev<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

pown_rev(interval<double>[10, 15], interval<double>[10, 15], int: 5) = interval<double>[-inf, +inf];
pown_rev<interval<float>>(interval<double>[10, 15], interval<double>[10, 15], int: 5) = interval<float>[-inf, +inf];
pown_rev(interval<double>[10, 15], int:5) = interval<double>[-inf, +inf];
pown_rev<interval<float>>(interval<double>[10, 15], int:5) = interval<float>[-inf, +inf];

sin_rev(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
sin_rev<interval<float>>(interval<double>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
sin_rev(interval<double>[10, 15]) = interval<double>[-inf, +inf];
sin_rev<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

cos_rev(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
cos_rev<interval<float>>(interval<double>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
cos_rev(interval<double>[10, 15]) = interval<double>[-inf, +inf];
cos_rev<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

tan_rev(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
tan_rev<interval<float>>(interval<double>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
tan_rev(interval<double>[10, 15]) = interval<double>[-inf, +inf];
tan_rev<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

cosh_rev(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
cosh_rev<interval<float>>(interval<double>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
cosh_rev(interval<double>[10, 15]) = interval<double>[-inf, +inf];
cosh_rev<interval<float>>(interval<double>[10, 15]) = interval<float>[-inf, +inf];

mul_rev(interval<double>[10, 15], interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
mul_rev<interval<float>>(interval<double>[10, 15], interval<float>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
mul_rev(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
mul_rev<interval<float>>(interval<double>[10, 15], interval<float>[10, 15]) = interval<float>[-inf, +inf];

div_rev1(interval<double>[10, 15], interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
div_rev1<interval<float>>(interval<double>[10, 15], interval<float>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
div_rev1(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
div_rev1<interval<float>>(interval<double>[10, 15], interval<float>[10, 15]) = interval<float>[-inf, +inf];

div_rev2(interval<double>[10, 15], interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
div_rev2<interval<float>>(interval<double>[10, 15], interval<float>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
div_rev2(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
div_rev2<interval<float>>(interval<double>[10, 15], interval<float>[10, 15]) = interval<float>[-inf, +inf];

pow_rev1(interval<double>[10, 15], interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
pow_rev1<interval<float>>(interval<double>[10, 15], interval<float>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
pow_rev1(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
pow_rev1<interval<float>>(interval<double>[10, 15], interval<float>[10, 15]) = interval<float>[-inf, +inf];

pow_rev2(interval<double>[10, 15], interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
pow_rev2<interval<float>>(interval<double>[10, 15], interval<float>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
pow_rev2(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
pow_rev2<interval<float>>(interval<double>[10, 15], interval<float>[10, 15]) = interval<float>[-inf, +inf];

atan2_rev1(interval<double>[10, 15], interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
atan2_rev1<interval<float>>(interval<double>[10, 15], interval<float>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
atan2_rev1(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
atan2_rev1<interval<float>>(interval<double>[10, 15], interval<float>[10, 15]) = interval<float>[-inf, +inf];

atan2_rev2(interval<double>[10, 15], interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
atan2_rev2<interval<float>>(interval<double>[10, 15], interval<float>[10, 15], interval<double>[10, 15]) = interval<float>[-inf, +inf];
atan2_rev2(interval<double>[10, 15], interval<double>[10, 15]) = interval<double>[-inf, +inf];
atan2_rev2<interval<float>>(interval<double>[10, 15], interval<float>[10, 15]) = interval<float>[-inf, +inf];


// -----------------------------------------------------------------------------
// Cancellative addition and subtraction, see P1788/D7.0 Sect. 9.6.6
// -----------------------------------------------------------------------------

cancel_plus<interval<float>>( interval<double>[10, 15], interval<float>[1, 2] ) = interval<float>[-inf, +inf];
cancel_plus( interval<double>[10, 15], interval<double>[1, 2] ) = interval<double>[-inf, +inf];

cancel_minus<interval<float>>( interval<double>[10, 15], interval<float>[1, 2] ) = interval<float>[-inf, +inf];
cancel_minus( interval<double>[10, 15], interval<double>[1, 2] ) = interval<double>[-inf, +inf];

// -----------------------------------------------------------------------------
// Recommended forward elementary functions on intervals, 
// see P1788/D7.0 Sect. 9.7.1 Table 5
// -----------------------------------------------------------------------------

// TODO: noch nicht implementiert

// -----------------------------------------------------------------------------
// Recommended interval overlapping, see P1788/D7.0 Sect. 9.7.2
// -----------------------------------------------------------------------------

// TODO: noch nicht implementiert

// -----------------------------------------------------------------------------
// Recommended slope functions, see P1788/D7.0 Sect. 9.7.3 Table 7
// -----------------------------------------------------------------------------

// TODO: noch nicht implementiert
