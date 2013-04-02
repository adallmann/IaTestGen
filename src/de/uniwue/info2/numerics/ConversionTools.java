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

/**
 * This class is used as a utility class of FloatingPoint. It provides basic methods to convert
 * floating-point to hexadecimal.
 * 
 * @author Michael Jedich
 * 
 */
public class ConversionTools {
	private static final String[] hex = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
			"A", "B", "C", "D", "E", "F" };

	private static final String[] binary = { "0000", "0001", "0010", "0011", "0100", "0101",
			"0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111" };

	public static String getHex(String bit_string) {
		StringBuffer str = new StringBuffer();
		str.append("0x");
		for (int i = 0; i < bit_string.length(); i += 4) {
			for (int z = 0; z < binary.length; z++) {
				if (bit_string.substring(i, i + 4).equals(binary[z])) {
					str.append(hex[z]);
				}
			}
		}
		return str.toString();
	}

	public static String hexToBinary(String hex_string) {
		hex_string = hex_string.trim().toUpperCase();
		if (hex_string.startsWith("0X")) {
			hex_string = hex_string.replace("0X", "");
		}
		StringBuffer str = new StringBuffer();
		for (int i = 0; i < hex_string.length(); i++) {
			for (int z = 0; z < hex.length; z++) {
				if (hex_string.substring(i, i + 1).equals(hex[z])) {
					str.append(binary[z]);
				}
			}
		}
		return str.toString();
	}

	public static String littleToBigEndian(String little_endian_binary_code) {
		short bit_length = (short) little_endian_binary_code.length();
		if (bit_length % 8 == 0) {
			Boolean[] little = bitStringToBitArray(little_endian_binary_code);
			bit_length = (short) bit_length;
			Boolean[] big = new Boolean[bit_length];
			short tempSize = (short) (bit_length - 8);
			for (int i = 0; i < bit_length / 2; i++) {
				big[tempSize++] = little[i];
				big[i] = little[tempSize - 1];
				if ((i + 1) % 8 == 0) {
					tempSize -= 16;
				}
			}
			return getBitArrayToString(big);
		} else {
			// TODO: error handling
		}
		return null;
	}

	public static String getBitArrayToString(Boolean[] bitset) {
		StringBuffer str = new StringBuffer();
		for (int i = 0; i < bitset.length; i++) {
			if (bitset[i] != null) {
				str.append(bitset[i] ? "1" : "0");
			}
		}
		return str.toString();
	}

	public static String getBitStringWithByteSeperator(String bits) {
		StringBuffer str = new StringBuffer();
		for (int i = 0; i < bits.length(); i++) {
			str.append(bits.charAt(i));
			if ((i + 1) % 8 == 0 && i < bits.length() - 1) {
				str.append(" ");
			}
		}
		return str.toString();
	}

	public static Boolean[] bitStringToBitArray(String bit_string) {
		short bit_length = (short) bit_string.length();
		Boolean[] b = new Boolean[bit_length];
		for (int i = 0; i < bit_length; i++) {
			char bit = bit_string.charAt(i);
			if (bit == '0' || bit == '1') {
				b[i] = (bit == '1') ? true : false;
			} else {
				throw new NumberFormatException();
			}
		}
		return b;
	}

	public static String normalizeBinaryString(String binary_code) {
		binary_code = binary_code.toUpperCase().replaceAll("\\s", "").replace("0B", "");

		short length = (short) (binary_code.length() % 8);
		if (length > 0) {
			for (int i = 0; i < 8 - length; i++) {
				binary_code = "0" + binary_code;
			}
		}
		return binary_code;
	}

	public static void validateBinaryString() {

	}

}
