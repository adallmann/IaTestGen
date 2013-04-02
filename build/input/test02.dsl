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
 * 		true;
 */
inv( interval<float>[10, 15] ) = interval<double>[8, 14];


/**
 * Fam-test.
 * @required
 * 		true;
 */
fma( interval<double>[10, 15], interval<float>[1, 2], interval<double>[1, 2] ) = interval<double>[8, 14];
