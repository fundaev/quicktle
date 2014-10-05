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
#include <tlelib/tleexception.h>

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
    std::time_t dt = static_cast<std::time_t>(string2date(s));
    struct tm *t1 = localtime(&dt);
    // Comparison
    EXPECT_EQ(t0.tm_year, t1->tm_year);
    EXPECT_EQ(t0.tm_mon, t1->tm_mon);
    EXPECT_EQ(t0.tm_mday, t1->tm_mday);
    EXPECT_EQ(t0.tm_hour, t1->tm_hour);
    EXPECT_EQ(t0.tm_min, t1->tm_min);
    EXPECT_EQ(t0.tm_sec, t1->tm_sec);

    // Compare strings
    std::string s0 = "86053.30522506";
    double t = string2date(s0);
    std::string s1 = date2string(t, 14);
    EXPECT_TRUE(s0 == s1);
}
//------------------------------------------------------------------------------

TEST(Functions, string2int)
{
    EXPECT_EQ(0, string2int("0"));
    EXPECT_EQ(1, string2int("1"));
    EXPECT_EQ(-1, string2int("-1"));
    EXPECT_EQ(32000, string2int(" 32000"));
    EXPECT_EQ(-32000, string2int("-32000  "));
    EXPECT_EQ(10, string2int(" 10  "));
    EXPECT_EQ(0, string2int("-0 "));

    //Exceptions
    EXPECT_THROW(string2int("e123"), tle_invalid_format);
    EXPECT_THROW(string2int("123-"), tle_invalid_format);
    EXPECT_THROW(string2int("12-3"), tle_invalid_format);
    EXPECT_THROW(string2int(".123"), tle_invalid_format);
    EXPECT_THROW(string2int("+123."), tle_invalid_format);
    EXPECT_NO_THROW(string2int("+123 "));
    EXPECT_NO_THROW(string2int(" -123"));
}
//------------------------------------------------------------------------------

TEST(Functions, string2double)
{
    EXPECT_DOUBLE_EQ(0, string2double("0"));
    EXPECT_DOUBLE_EQ(10, string2double("10"));
    EXPECT_DOUBLE_EQ(-10, string2double("-10"));
    EXPECT_DOUBLE_EQ(0.0123, string2double("123e-4"));
    EXPECT_DOUBLE_EQ(-123.456, string2double(" -123.456"));
    EXPECT_DOUBLE_EQ(1230, string2double("123e1  "));
    EXPECT_DOUBLE_EQ(-1230, string2double(" -12.3e+2"));
    EXPECT_DOUBLE_EQ(123456.78, string2double(" 123456.78  "));
    EXPECT_DOUBLE_EQ(0, string2double(" -0  "));

    // Exceptions
    EXPECT_THROW(string2double("e123.5"), tle_invalid_format);
    EXPECT_THROW(string2double("123.-5"), tle_invalid_format);
    EXPECT_THROW(string2double("12+3.5"), tle_invalid_format);
    EXPECT_THROW(string2double("123e"), tle_invalid_format);
}
//------------------------------------------------------------------------------

TEST(Functions, trim)
{
    EXPECT_TRUE(trim("123") == "123");
    EXPECT_TRUE(trim(" test") == "test");
    EXPECT_TRUE(trim("TeSt123       ") == "TeSt123");
    EXPECT_TRUE(trim(" a2c  ") == "a2c");
}
//------------------------------------------------------------------------------

TEST(Functions, parseChar)
{
    std::string str("Test string");
    EXPECT_TRUE(parseChar(NULL, 5) == '\0');
    EXPECT_TRUE(parseChar(&str, 2) == 's');
    EXPECT_TRUE(parseChar(&str, 10) == 'g');
    EXPECT_THROW(parseChar(&str, 11), tle_too_short_string);
}
//------------------------------------------------------------------------------

TEST(Functions, parseString)
{
    std::string str("Test string");
    EXPECT_TRUE(parseString(NULL, 5, 2) == "");
    EXPECT_TRUE(parseString(&str, 0,4) == "Test");
    EXPECT_TRUE(parseString(&str, 9, 2) == "ng");
    // Exceptions
    EXPECT_THROW(parseString(&str, 9, 3), tle_too_short_string);
}
//------------------------------------------------------------------------------

TEST(Functions, parseInt)
{
    std::string str("123");
    EXPECT_EQ(0, parseInt(NULL, 1, 2));
    EXPECT_EQ(23, parseInt(&str, 1, 2));
    EXPECT_EQ(1, parseInt(&str, 0, 1));
    EXPECT_EQ(3, parseInt(&str, 2, 1));
    str = "a-12345";
    EXPECT_EQ(12345, parseInt(&str, 2, 5));
    EXPECT_EQ(-12345, parseInt(&str, 1, 6));
    str = "  5 ";
    EXPECT_EQ(5, parseInt(&str, 0, 3));
    EXPECT_EQ(5, parseInt(&str, 2, 1));
    EXPECT_EQ(5, parseInt(&str, 0, 4));

    // Exceptions
    str = "a-12345";
    EXPECT_THROW(parseInt(&str, 4, 5), tle_too_short_string);
    EXPECT_THROW(parseInt(&str, 0, 2), tle_invalid_format);
}
//------------------------------------------------------------------------------

TEST(Functions, parseDouble)
{
    std::string str("-123.456");
    EXPECT_DOUBLE_EQ(0, parseDouble(NULL, 1, 2));
    EXPECT_DOUBLE_EQ(123.4, parseDouble(&str, 1, 5));
    EXPECT_DOUBLE_EQ(-123.45, parseDouble(&str, 0, 7));

    str = "123e-4";
    EXPECT_DOUBLE_EQ(0.0123, parseDouble(&str, 0, 6));
    EXPECT_DOUBLE_EQ(23, parseDouble(&str, 1, 2));

    str = "-58797-4";
    EXPECT_DOUBLE_EQ(-0.000058797, parseDouble(&str, 0, 8, true));

    // Exceptions
    str = "abc123e-4";
    EXPECT_NO_THROW(parseDouble(&str, 3, 6));
    EXPECT_THROW(parseDouble(&str, 3, 7), tle_too_short_string);
    EXPECT_THROW(parseDouble(&str, 2, 4), tle_invalid_format);
    EXPECT_THROW(parseDouble(&str, 3, 4), tle_invalid_format);
    EXPECT_THROW(parseDouble(&str, 3, 5), tle_invalid_format);
}
//------------------------------------------------------------------------------

TEST(Functions, string2date)
{
    std::string str = "11349.37521666";
    std::time_t t = static_cast<std::time_t>(string2date(str));
    struct tm *t0 = gmtime(&t);

    EXPECT_EQ(111, t0->tm_year);
    EXPECT_EQ(11, t0->tm_mon);
    EXPECT_EQ(15, t0->tm_mday);
    EXPECT_EQ(9, t0->tm_hour);
    EXPECT_EQ(0, t0->tm_min);
    EXPECT_EQ(18, t0->tm_sec);

    // Convertion
    std::string s0 = "11348.60068410";
    double dt = string2date(s0);
    std::string s1 = date2string(dt, 14);
    EXPECT_TRUE(s0 == s1);
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
