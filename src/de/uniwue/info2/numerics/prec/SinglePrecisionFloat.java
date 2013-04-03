/*
 *    IaTestGen - Interval arithmetic test generator
 *    Copyright 2013
 *
 *    Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
 *    Institute of Computer Science,
 *    University of Wuerzburg, Germany
 *    
 *    Michael Jedich (m.jedich@gmail.com)
 *    University of Wuerzburg, Germany
 *    
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *    http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
package de.uniwue.info2.numerics.prec;

import org.apache.commons.lang.StringUtils;

import de.uniwue.info2.numerics.FloatingPoint;

/**
 * Implementation of single precision floating point.
 * 
 * @author Michael Jedich
 * 
 */
public class SinglePrecisionFloat extends FloatingPoint {
	private static final short SINGLE_COEFFICIENT_LENGTH = 23;
	private static final short SINGLE_EXPONENT_LENGTH = 8;

	public SinglePrecisionFloat(String value) {
		super(value);
	}

	@Override
	public short getCoefficientLength() {
		return SINGLE_COEFFICIENT_LENGTH;
	}

	@Override
	public short getExponentLength() {
		return SINGLE_EXPONENT_LENGTH;
	}

	@Override
	protected String floatValueToBinaryString(String value) {
		float f = Float.parseFloat(value);
		String binary;
		if (f == 0) {
			binary = StringUtils.repeat("0", 32);
		} else {
			binary = Integer.toBinaryString(Float.floatToIntBits(f));
		}
		return binary;
	}
}
