/*-----------------------------------------------------------------------------+
 | TLELib                                                                      |
 | Copyright 2011-2014 Sergei Fundaev                                          |
 +-----------------------------------------------------------------------------+
 | This file is part of TLELib.                                                |
 |                                                                             |
 | TLELib is free software: you can redistribute it and/or modify              |
 | it under the terms of the GNU Lesser General Public License as published by |
 | the Free Software Foundation, either version 3 of the License, or           |
 | (at your option) any later version.                                         |
 |                                                                             |
 | TLELib is distributed in the hope that it will be useful,                   |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of              |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               |
 | GNU Lesser General Public License for more details.                         |
 |                                                                             |
 | You should have received a copy of the GNU Lesser General Public License    |
 | along with TLELib. If not, see <http://www.gnu.org/licenses/>.              |
 +----------------------------------------------------------------------------*/

#include <string>
#include <iostream>
#include <ctime>

#include <gtest/gtest.h>
#include <tlelib/tlefunc.h>

using namespace tlelib;

//
//---- TESTS -------------------------------------------------------------------

TEST(Functions, int2string)
{
    EXPECT_TRUE(int2string(0) == "0");
    EXPECT_TRUE(int2string(1) == "1");
    EXPECT_TRUE(int2string(-1) == "-1");
    EXPECT_TRUE(int2string(32000) == "32000");
    EXPECT_TRUE(int2string(-32000) == "-32000");
    EXPECT_TRUE(int2string(10) == "10");
    EXPECT_TRUE(int2string(-0) == "0");
    EXPECT_TRUE(int2string(262, 4, false) == " 262");
}
//------------------------------------------------------------------------------

TEST(Functions, double2string)
{
    EXPECT_TRUE(double2string(12.35, 8, 3) == "12.350  ");
    EXPECT_TRUE(double2string(12.35, 8, 1, false, false, false) == "    12.3");
    EXPECT_TRUE(double2string(12.35, 8, 2, true, false, false) == "  1235-2");
    EXPECT_TRUE(double2string(26.778123, 8, 3, true, false, false) == " 26778-3");
    EXPECT_TRUE(double2string(0, 1, 0) == "0");
    EXPECT_TRUE(double2string(0, 4, 1, true) == "000-0");
    EXPECT_TRUE(double2string(0, 8, 3, true, true, false) == " 00000-0");
    //std::cout << "\"" << double2string(0.00010191, 8, 3, true, true, false) << "\"" << std::endl;
}
//------------------------------------------------------------------------------

TEST(Functions, string2string)
{
    EXPECT_TRUE(string2string("abcdef", 4) == "abcd");
    EXPECT_TRUE(string2string("abcdef", 4, true, false) == "abcdef");
    EXPECT_TRUE(string2string("abcdef", 7) == "abcdef ");
    EXPECT_TRUE(string2string("abcdef", 8, false) == "  abcdef");
}
//------------------------------------------------------------------------------

TEST(Functions, date2string)
{
    // Prepare date
    struct tm t0;
    t0.tm_year = 111;
    t0.tm_mon = 3;
    t0.tm_mday = 6;
    t0.tm_hour = 11;
    t0.tm_min = 12;
    t0.tm_sec = 2;
    // Convert date to string
    std::string s = date2string(mktime(&t0), 14);
    // Convert string to date
    tle_node::error_code error = tle_node::no_error;
    std::time_t dt = static_cast<std::time_t>(string2date(s, error));
    struct tm *t1 = localtime(&dt);
    // Comparison
    EXPECT_EQ(tle_node::no_error, error);
    EXPECT_EQ(t0.tm_year, t1->tm_year);
    EXPECT_EQ(t0.tm_mon, t1->tm_mon);
    EXPECT_EQ(t0.tm_mday, t1->tm_mday);
    EXPECT_EQ(t0.tm_hour, t1->tm_hour);
    EXPECT_EQ(t0.tm_min, t1->tm_min);
    EXPECT_EQ(t0.tm_sec, t1->tm_sec);

    // Compare strings
    std::string s0 = "86053.30522506";
    error = tle_node::no_error;
    double t = string2date(s0, error);
    std::string s1 = date2string(t, 14);
    EXPECT_EQ(tle_node::no_error, error);
    EXPECT_EQ(s0, s1);
}
//------------------------------------------------------------------------------

TEST(Functions, string2int)
{
    tle_node::error_code error = tle_node::no_error;
    EXPECT_EQ(0, string2int("0", error));
    EXPECT_EQ(tle_node::no_error, error);

    EXPECT_EQ(1, string2int("1", error));
    EXPECT_EQ(tle_node::no_error, error);

    EXPECT_EQ(-1, string2int("-1", error));
    EXPECT_EQ(tle_node::no_error, error);

    EXPECT_EQ(32000, string2int(" 32000", error));
    EXPECT_EQ(tle_node::no_error, error);

    EXPECT_EQ(-32000, string2int("-32000  ", error));
    EXPECT_EQ(tle_node::no_error, error);

    EXPECT_EQ(10, string2int(" 10  ", error));
    EXPECT_EQ(tle_node::no_error, error);

    EXPECT_EQ(0, string2int("-0 ", error));
    EXPECT_EQ(tle_node::no_error, error);

    //Exceptions
    string2int("e123", error);
    EXPECT_EQ(tle_node::invalid_format, error);

    string2int("123-", error);
    EXPECT_EQ(tle_node::invalid_format, error);

    string2int(".123", error);
    EXPECT_EQ(tle_node::invalid_format, error);

    string2int("+123.", error);
    EXPECT_EQ(tle_node::invalid_format, error);

    EXPECT_EQ(123, string2int("+123 ", error));
    EXPECT_EQ(tle_node::no_error, error);

    EXPECT_EQ(-123, string2int("-123 ", error));
    EXPECT_EQ(tle_node::no_error, error);
}
//------------------------------------------------------------------------------

TEST(Functions, string2double)
{
    tle_node::error_code error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(0, string2double("0", error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(10, string2double("10", error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(-10, string2double("-10", error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(0.0123, string2double("123e-4", error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(-123.456, string2double(" -123.456", error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(1230, string2double("123e1  ", error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(-1230, string2double(" -12.3e+2", error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(123456.78, string2double(" 123456.78  ", error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(0, string2double(" -0  ", error));
    EXPECT_EQ(tle_node::no_error, error);

    // Exceptions
    error = tle_node::no_error;
    string2double("e123.5", error);
    EXPECT_EQ(tle_node::invalid_format, error);

    error = tle_node::no_error;
    string2double("123.-5", error);
    EXPECT_EQ(tle_node::invalid_format, error);

    error = tle_node::no_error;
    string2double("12+3.5", error);
    EXPECT_EQ(tle_node::invalid_format, error);

    error = tle_node::no_error;
    string2double("123e", error);
    EXPECT_EQ(tle_node::invalid_format, error);
}
//------------------------------------------------------------------------------

TEST(Functions, trim)
{
    EXPECT_EQ("123", trim("123"));
    EXPECT_EQ("test", trim(" test"));
    EXPECT_EQ("TeSt123", trim("TeSt123       "));
    EXPECT_EQ("a2c", trim(" a2c  "));
}
//------------------------------------------------------------------------------

TEST(Functions, parseChar)
{
    tle_node::error_code error = tle_node::no_error;
    EXPECT_EQ('\0', parseChar(NULL, 5, error));
    EXPECT_EQ(tle_node::no_error, error);

    std::string str("Test string");

    error = tle_node::no_error;
    EXPECT_EQ('s', parseChar(&str, 2, error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_EQ('g', parseChar(&str, 10, error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_EQ('\0', parseChar(&str, 11, error));
    EXPECT_EQ(tle_node::too_short_string, error);
}
//------------------------------------------------------------------------------

TEST(Functions, parseString)
{
    tle_node::error_code error = tle_node::no_error;
    EXPECT_EQ("", parseString(NULL, 5, 2, error));
    EXPECT_EQ(tle_node::no_error, error);

    std::string str("Test string");

    error = tle_node::no_error;
    EXPECT_EQ("Test", parseString(&str, 0, 4, error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_EQ("ng", parseString(&str, 9, 2, error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_EQ("", parseString(&str, 9, 3, error));
    EXPECT_EQ(tle_node::too_short_string, error);
}
//------------------------------------------------------------------------------

TEST(Functions, parseInt)
{
    tle_node::error_code error = tle_node::no_error;
    EXPECT_EQ(0, parseInt(NULL, 1, 2, error));
    EXPECT_EQ(tle_node::no_error, error);

    std::string str("123");

    error = tle_node::no_error;
    EXPECT_EQ(23, parseInt(&str, 1, 2, error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_EQ(1, parseInt(&str, 0, 1, error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_EQ(3, parseInt(&str, 2, 1, error));
    EXPECT_EQ(tle_node::no_error, error);

    str = "a-12345";

    error = tle_node::no_error;
    EXPECT_EQ(12345, parseInt(&str, 2, 5, error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_EQ(-12345, parseInt(&str, 1, 6, error));
    EXPECT_EQ(tle_node::no_error, error);

    str = "  5 ";

    error = tle_node::no_error;
    EXPECT_EQ(5, parseInt(&str, 0, 3, error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_EQ(5, parseInt(&str, 2, 1, error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_EQ(5, parseInt(&str, 0, 4, error));
    EXPECT_EQ(tle_node::no_error, error);

    str = "a-12345";
    EXPECT_EQ(0, parseInt(&str, 4, 5, error));
    EXPECT_EQ(tle_node::too_short_string, error);

    error = tle_node::no_error;
    EXPECT_EQ(0, parseInt(&str, 0, 2, error));
    EXPECT_EQ(tle_node::invalid_format, error);
}
//------------------------------------------------------------------------------

TEST(Functions, parseDouble)
{
    tle_node::error_code error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(0, parseDouble(NULL, 1, 2, error));
    EXPECT_EQ(tle_node::no_error, error);

    std::string str("-123.456");

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(123.4, parseDouble(&str, 1, 5, error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(-123.45, parseDouble(&str, 0, 7, error));
    EXPECT_EQ(tle_node::no_error, error);

    str = "123e-4";

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(0.0123, parseDouble(&str, 0, 6, error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(23, parseDouble(&str, 1, 2, error));
    EXPECT_EQ(tle_node::no_error, error);

    str = "-58797-4";

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(-0.000058797, parseDouble(&str, 0, 8, error));
    EXPECT_EQ(tle_node::no_error, error);

    str = "abc123e-4";

    error = tle_node::no_error;
    EXPECT_NO_THROW(parseDouble(&str, 3, 6, error));
    EXPECT_EQ(tle_node::no_error, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(0, parseDouble(&str, 3, 7, error));
    EXPECT_EQ(tle_node::too_short_string, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(0, parseDouble(&str, 2, 4, error));
    EXPECT_EQ(tle_node::invalid_format, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(0, parseDouble(&str, 3, 4, error));
    EXPECT_EQ(tle_node::invalid_format, error);

    error = tle_node::no_error;
    EXPECT_DOUBLE_EQ(0, parseDouble(&str, 3, 5, error));
    EXPECT_EQ(tle_node::invalid_format, error);
}
//------------------------------------------------------------------------------

TEST(Functions, string2date)
{
    tle_node::error_code error = tle_node::no_error;
    std::string str = "11349.37521666";
    std::time_t t = static_cast<std::time_t>(string2date(str, error));
    struct tm *t0 = gmtime(&t);

    EXPECT_EQ(tle_node::no_error, error);
    EXPECT_EQ(111, t0->tm_year);
    EXPECT_EQ(11, t0->tm_mon);
    EXPECT_EQ(15, t0->tm_mday);
    EXPECT_EQ(9, t0->tm_hour);
    EXPECT_EQ(0, t0->tm_min);
    EXPECT_EQ(18, t0->tm_sec);

    // Convertion
    std::string s0 = "11348.60068410";
    error = tle_node::no_error;
    double dt = string2date(s0, error);
    std::string s1 = date2string(dt, 14);
    EXPECT_EQ(tle_node::no_error, error);
    EXPECT_EQ(s0, s1);
}
//------------------------------------------------------------------------------

TEST(Functions, checksum)
{
    EXPECT_EQ(5, checksum("1234567890"));
    EXPECT_EQ(5, checksum(" 1  23 45.6789+0"));
    EXPECT_EQ(7, checksum(" 1 23-4 567-890"));
}
//------------------------------------------------------------------------------

TEST(Functions, normalize_angle)
{
    EXPECT_DOUBLE_EQ(124, normalize_angle(124));
    EXPECT_DOUBLE_EQ(274.15, normalize_angle(274.15));
    EXPECT_DOUBLE_EQ(45.237, normalize_angle(405.237));
    EXPECT_DOUBLE_EQ(17.64, normalize_angle(-342.36));
    EXPECT_DOUBLE_EQ(0, normalize_angle(360));
    EXPECT_DOUBLE_EQ(0, normalize_angle(720));
}
//------------------------------------------------------------------------------
