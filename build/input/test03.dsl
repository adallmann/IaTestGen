/**
 * Example Domain-Specific-Language.
 *
 * @author 
 *		Michael Jedich;
 * @version 
 *		0.8, 23.03.2012;
 * @description 
 *		Sample-file with a couple of simple testfunctions;
 */



// variables for addition-test
$lowerLimit01 		= double: 0x3FC0A3D70A3D70A4;
$upperLimit01 		= double: 0x3FCD70A3D70A3D71;
$lowerLimit02		= double: 0x3FD0A3D70A3D70A4;
$additionResult 	= interval<double>[$lowerLimit02, 0x3FDD70A3D70A3D71];

/**
 * Addition-test.
 * @description 
 *		Simple addition test;
 */
addition(interval<double>[$lowerLimit01, $upperLimit01], 
		interval<double>[0x3FC0A3D70A3D70A4, 0x3FCD70A3D70A3D71]) = $additionResult;
		
addition(interval<double>[3, +inf], interval<double>[3, +inf]) = interval<double>[6, +inf];

/**
 * Substraction-test.
 * @description 
 *		Simple substraction test;
 */
substraction( interval<int>[10, 15], interval<int>[1, 2] ) = interval<int>[8, 14];

/**
 * @description 
 *		Midpoint/Median-Test;
 */
median( interval<double>[2, 12] ) =  double: 7;

/**
 * @description 
 *		Interval contains given number - test;
 * @optional
 *		true;
 */
is_in( double: 0.3, interval<double>[0.2, 0.677] ) = true;

/**
 * @description 
 *		Interval contains given number - test;
 */
bisect( interval<int>[5, 10] ) = interval<int>[5, 7], interval<int>[7, 10];

