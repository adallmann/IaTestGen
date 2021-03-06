/* Generated By:JavaCC: Do not edit this line. DSLParserConstants.java */
package de.uniwue.info2.parser;


/**
 * Token literal values and constants.
 * Generated by org.javacc.parser.OtherFilesGen#start()
 */
public interface DSLParserConstants {

  /** End of File. */
  int EOF = 0;
  /** RegularExpression Id. */
  int BEGIN_BLOCK_COMMENT = 6;
  /** RegularExpression Id. */
  int AUTHOR_TAG = 9;
  /** RegularExpression Id. */
  int VERSION_TAG = 10;
  /** RegularExpression Id. */
  int DESCRIPTION_TAG = 11;
  /** RegularExpression Id. */
  int OPTIONAL_TAG = 12;
  /** RegularExpression Id. */
  int TAG = 14;
  /** RegularExpression Id. */
  int VARIABLE_NAME = 18;
  /** RegularExpression Id. */
  int SHORT = 19;
  /** RegularExpression Id. */
  int INTEGER = 20;
  /** RegularExpression Id. */
  int LONG = 21;
  /** RegularExpression Id. */
  int DIGITS_INTEGER = 22;
  /** RegularExpression Id. */
  int FLOAT = 23;
  /** RegularExpression Id. */
  int DOUBLE = 24;
  /** RegularExpression Id. */
  int DIGITS_FLOAT = 25;
  /** RegularExpression Id. */
  int BIN_32 = 26;
  /** RegularExpression Id. */
  int BIN_64 = 27;
  /** RegularExpression Id. */
  int HEX_8 = 28;
  /** RegularExpression Id. */
  int HEX_16 = 29;
  /** RegularExpression Id. */
  int BOOL = 30;
  /** RegularExpression Id. */
  int BOOL_TRUE = 31;
  /** RegularExpression Id. */
  int BOOL_FALSE = 32;
  /** RegularExpression Id. */
  int INTERVAL = 33;
  /** RegularExpression Id. */
  int NEGATIVE_INFINITY = 34;
  /** RegularExpression Id. */
  int POSITIVE_INFINITY = 35;
  /** RegularExpression Id. */
  int EMPTY_SET = 36;
  /** RegularExpression Id. */
  int ENTIRE_SET = 37;
  /** RegularExpression Id. */
  int EOL = 38;
  /** RegularExpression Id. */
  int CLOSE_PAR_LIST = 39;
  /** RegularExpression Id. */
  int OPEN_PAR_LIST = 40;
  /** RegularExpression Id. */
  int EQUAL = 41;
  /** RegularExpression Id. */
  int SP = 42;
  /** RegularExpression Id. */
  int NG = 43;
  /** RegularExpression Id. */
  int SUBSETEQ = 44;
  /** RegularExpression Id. */
  int SUBSETNEQ = 45;
  /** RegularExpression Id. */
  int SUPERSETEQ = 46;
  /** RegularExpression Id. */
  int SUPERSETNEQ = 47;
  /** RegularExpression Id. */
  int OPEN_TYPE = 48;
  /** RegularExpression Id. */
  int CLOSE_TYPE = 49;
  /** RegularExpression Id. */
  int OPEN_INTERVAL_VARS = 50;
  /** RegularExpression Id. */
  int CLOSE_INTERVAL_VARS = 51;
  /** RegularExpression Id. */
  int PRIMITIVE_PAR_SEP = 52;

  /** Lexical state. */
  int DEFAULT = 0;
  /** Lexical state. */
  int BLOCK_COMMENT = 1;
  /** Lexical state. */
  int TAG_CONTENT = 2;
  /** Lexical state. */
  int VARIABLE = 3;

  /** Literal token values. */
  String[] tokenImage = {
    "<EOF>",
    "\" \"",
    "\"\\t\"",
    "\"\\n\"",
    "<token of kind 4>",
    "\"$\"",
    "\"/*\"",
    "<token of kind 7>",
    "\"*/\"",
    "\"@author\"",
    "\"@version\"",
    "\"@description\"",
    "\"@required\"",
    "\";\"",
    "<TAG>",
    "\" \"",
    "\"\\t\"",
    "\"\\n\"",
    "<VARIABLE_NAME>",
    "\"short\"",
    "\"int\"",
    "\"long\"",
    "<DIGITS_INTEGER>",
    "\"float\"",
    "\"double\"",
    "<DIGITS_FLOAT>",
    "<BIN_32>",
    "<BIN_64>",
    "<HEX_8>",
    "<HEX_16>",
    "\"bool\"",
    "\"true\"",
    "\"false\"",
    "\"interval\"",
    "\"-inf\"",
    "\"+inf\"",
    "\"empty\"",
    "\"entire\"",
    "\";\"",
    "\")\"",
    "\"(\"",
    "\"=\"",
    "\",\"",
    "\"!\"",
    "\"subseteq=\"",
    "\"subsetneq=\"",
    "\"superseteq=\"",
    "\"supersetneq=\"",
    "\"<\"",
    "\">\"",
    "\"[\"",
    "\"]\"",
    "\":\"",
    "\"intersect\"",
    "\"hull\"",
    "\"inf\"",
    "\"sup\"",
    "\"mid\"",
    "\"rad\"",
    "\"mid_rad\"",
    "\"wid\"",
    "\"mag\"",
    "\"mig\"",
    "\"is_empty\"",
    "\"is_entire\"",
    "\"is_equal\"",
    "\"contained_in\"",
    "\"contains\"",
    "\"less\"",
    "\"greater\"",
    "\"precedes\"",
    "\"succeeds\"",
    "\"is_interior\"",
    "\"contains_interior\"",
    "\"strictly_less\"",
    "\"strictly_greater\"",
    "\"strictly_precedes\"",
    "\"strictly_succeeds\"",
    "\"are_disjoint\"",
    "\"pos\"",
    "\"neg\"",
    "\"add\"",
    "\"sub\"",
    "\"mul\"",
    "\"div\"",
    "\"inv\"",
    "\"sqrt\"",
    "\"fma\"",
    "\"interval_case\"",
    "\"sqr\"",
    "\"pown\"",
    "\"pow\"",
    "\"exp\"",
    "\"exp2\"",
    "\"exp10\"",
    "\"log\"",
    "\"log2\"",
    "\"log10\"",
    "\"sin\"",
    "\"cos\"",
    "\"tan\"",
    "\"asin\"",
    "\"acos\"",
    "\"atan\"",
    "\"atan2\"",
    "\"sinh\"",
    "\"cosh\"",
    "\"tanh\"",
    "\"asinh\"",
    "\"acosh\"",
    "\"atanh\"",
    "\"sign\"",
    "\"ceil\"",
    "\"floor\"",
    "\"trunc\"",
    "\"round_ties_to_even\"",
    "\"round_ties_to_away\"",
    "\"abs\"",
    "\"min\"",
    "\"max\"",
    "\"sqr_rev\"",
    "\"inv_rev\"",
    "\"abs_rev\"",
    "\"pown_rev\"",
    "\"sin_rev\"",
    "\"cos_rev\"",
    "\"tan_rev\"",
    "\"cosh_rev\"",
    "\"mul_rev\"",
    "\"div_rev1\"",
    "\"div_rev2\"",
    "\"pow_rev1\"",
    "\"pow_rev2\"",
    "\"atan2_rev1\"",
    "\"atan2_rev2\"",
    "\"cancel_plus\"",
    "\"cancel_minus\"",
    "\"rootn\"",
    "\"expm1\"",
    "\"exp2m1\"",
    "\"exp10m1\"",
    "\"logp1\"",
    "\"log2p1\"",
    "\"log10p1\"",
    "\"compoundm1\"",
    "\"hypot\"",
    "\"r_sqrt\"",
    "\"sin_pi\"",
    "\"cos_pi\"",
    "\"tan_pi\"",
    "\"asin_pi\"",
    "\"acos_pi\"",
    "\"atan_pi\"",
    "\"atan2_pi\"",
  };

}
