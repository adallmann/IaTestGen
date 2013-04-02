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
package de.uniwue.info2.numerics;

import java.nio.ByteOrder;

/**
 * This class is used to represent floating-point numbers.
 * 
 * @author Michael Jedich
 * 
 */
public abstract class FloatingPoint {
	private ByteOrder system_endian;
	protected String binary_code_little_endian;
	protected String binary_code_big_endian;
	protected String hex_code_little_endian;
	protected String hex_code_big_endian;
	protected short coefficient_length;
	protected short exponent_length;
	protected short binary_code_length;

	/**
	 * 
	 * @param value
	 */
	protected FloatingPoint(String value) {
		// parse string and convert to binary-code if necessary
		parseValueString(value);

		// calculate big-endian binary-code
		setBinaryCodeBigEndian(ConversionTools.littleToBigEndian(getBinaryCodeLittleEndian()));

		// calculate little-endian hex-code
		setHexCodeLittleEndian(ConversionTools.getHex(getBinaryCodeLittleEndian()));

		// calculate big-endian hex-code
		setHexCodeBigEndian(ConversionTools.getHex(getBinaryCodeBigEndian()));

		// calculate binary length (1 stands for the algebraic sign)
		binary_code_length = (short) (1 + getCoefficientLength() + getExponentLength());

		// get system endian type
		this.system_endian = ByteOrder.nativeOrder();
	}

	/**
	 * 
	 * @param value
	 */
	private void parseValueString(String value) {
		value = value.trim();
		if (value.matches("(0b)[0-1\\s]+") && value.trim().length() >= 16) {
			// if string contains a binary-code
			this.setBinaryCodeLittleEndian(value);
		} else if (value.matches("(0x)[0-9a-fA-F\\s]+") && value.trim().length() >= 2) {
			// if string contains a hex-code
			this.setBinaryCodeLittleEndian(ConversionTools.hexToBinary(value));
		} else if (value
				.matches("(\\+|-)?(([0-9]+\\.[0-9]*)||([0-9]*\\.[0-9]+)||[0-9]+)((e|E)(\\+|-)?[1-9]+)?(d|D|f|F)?")) {
			// if string contains a decimal
			this.setBinaryCodeLittleEndian(ConversionTools
					.normalizeBinaryString(floatValueToBinaryString(value)));
		}
	}

	/**
	 * Get bit-length.
	 * 
	 * @return length of binary code.
	 */
	public short getBinaryCodeLength() {
		return binary_code_length;
	}

	public ByteOrder getSystemEndian() {
		return system_endian;
	}

	public void setSystemEndian(ByteOrder system_endian) {
		this.system_endian = system_endian;
	}

	protected abstract String floatValueToBinaryString(String value);

	public abstract short getCoefficientLength();

	public abstract short getExponentLength();

	/*------------------------------------------------------ */
	/*-------------------BINARY-HANDLING-------------------- */
	/*------------------------------------------------------ */

	public void setBinaryCodeLittleEndian(String binary_code) {
		this.binary_code_little_endian = ConversionTools.normalizeBinaryString(binary_code);
	}

	public void setBinaryCodeBigEndian(String binary_code) {
		this.binary_code_big_endian = ConversionTools.normalizeBinaryString(binary_code);
	}

	public String getBinaryCodeLittleEndian() {
		return binary_code_little_endian;
	}

	public String getBinaryCodeBigEndian() {
		return binary_code_big_endian;
	}

	public String getBinaryCodeForCurrentSystem() {
		if (getSystemEndian() == ByteOrder.LITTLE_ENDIAN) {
			return getBinaryCodeLittleEndian();
		} else {
			return getBinaryCodeBigEndian();
		}
	}

	/*------------------------------------------------------ */
	/*--------------------HEX-HANDLING---------------------- */
	/*------------------------------------------------------ */

	public String getHexCodeBigEndian() {
		return hex_code_big_endian;
	}

	public void setHexCodeBigEndian(String hex_code_big_endian) {
		this.hex_code_big_endian = hex_code_big_endian;
	}

	public String getHexCodeLittleEndian() {
		return hex_code_little_endian;
	}

	public void setHexCodeLittleEndian(String hex_code_little_endian) {
		this.hex_code_little_endian = hex_code_little_endian;
	}

	public String getHexCodeForCurrentSystem() {
		if (getSystemEndian() == ByteOrder.LITTLE_ENDIAN) {
			return getHexCodeLittleEndian();
		} else {
			return getHexCodeBigEndian();
		}
	}

	/**
	 * Override toString-method
	 */
	public String toString() {
		String str = "system:\t\t\t"
				+ system_endian
				+ " [coefficient: "
				+ getCoefficientLength()
				+ "-bit] [exponent: "
				+ getExponentLength()
				+ "-bit] --> ["
				+ getBinaryCodeLength()
				+ "-bit]"
				+ "\nlittle-endian binary:\t"
				+ ConversionTools.getBitStringWithByteSeperator(this
						.getBinaryCodeLittleEndian()) + "\nbig-endian binary:\t"
				+ ConversionTools.getBitStringWithByteSeperator(this.getBinaryCodeBigEndian())
				+ "\nlittle-endian hex:\t" + this.getHexCodeLittleEndian()
				+ "\nbig-endian hex:\t\t" + this.getHexCodeBigEndian() + "\n\n";
		return str;
	}

}
