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
 * Implementation of double precision floating point.
 * 
 * @author Michael Jedich
 * 
 */
public class DoublePrecisionFloat extends FloatingPoint {
	private static final short DOUBLE_COEFFICIENT_LENGTH = 52;
	private static final short DOUBLE_EXPONENT_LENGTH = 11;

	public DoublePrecisionFloat(String value) {
		super(value);
	}

	@Override
	public short getCoefficientLength() {
		return DOUBLE_COEFFICIENT_LENGTH;
	}

	@Override
	public short getExponentLength() {
		return DOUBLE_EXPONENT_LENGTH;
	}

	@Override
	protected String floatValueToBinaryString(String value) {
		double d = Double.parseDouble(value);
		String binary;
		if (d == 0) {
			binary = StringUtils.repeat("0", 64);
		} else {
			binary = Long.toBinaryString(Double.doubleToLongBits(d));
		}
		return binary;
	}

}
