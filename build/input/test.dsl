/**
 * Simple example of the 
 * Domain Specific Language.
 *
 * @author 
 * 	Michael Jedich;
 * @version 
 * 	0.8, 23.03.2012;
 * @description 
 * 	Sample file with two testfunctions;
 */

/**
 * Ein Test für die Subtraktion.
 * @description 
 * 	Simple subtraction test: 
 * 	[-2 , 15] - [2.12, 4.5112] = [-6.5112, 12.88];
 */
subtraction( interval<float>[-2, 15], interval<float>[2.12, 4.5112] ) 
	= interval<float>[0xC0D05BC0, 0x414E147B];

/**
 * Median-Test.
 */
$lower=double:0x4000000000000000;
$upper=double:0x4028000000000000;
median( interval<double>[$lower, $upper] ) =  int: 7;
