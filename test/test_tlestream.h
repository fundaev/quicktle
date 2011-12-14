/*-----------------------------------------------------------------------------+
 | TLELib                                                                      |
 | Copyright 2011 Sergei V. Fundaev                                            |
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

#include <iostream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>
#include <tlelib/tlefunc.h>
#include <tlelib/tlenode.h>
#include <tlelib/tlestream.h>

using namespace tlelib;

class tle_stream_test: public tle_stream, public ::testing::Test
{
};

//
//---- TESTS -------------------------------------------------------------------

TEST(tle_stream_test, input)
{
    std::string line1 = "Mir                     \n";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349  00000-0  31166-3 0   112\n";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295 196.0076 15.79438158   394\n";

    std::stringstream lines(std::stringstream::in | std::stringstream::out);
    lines << line1 << line2 << line3;

    tle_stream tle(lines, three_lines);
    tle_node node;
    tle >> node;

    // Check values
    EXPECT_TRUE(node.sat_name() == "Mir");
    EXPECT_TRUE(node.sat_number() == "16609");
    EXPECT_TRUE(node.designator() == "86017A");
    EXPECT_TRUE(node.classification() == 'U');
    EXPECT_DOUBLE_EQ(0.00057349,  node.dn());
    EXPECT_DOUBLE_EQ(0, node.d2n());
    EXPECT_DOUBLE_EQ(0.00031166, node.BSTAR());
    EXPECT_DOUBLE_EQ(51.6129, node.i());
    EXPECT_DOUBLE_EQ(108.0599, node.Omega());
    EXPECT_DOUBLE_EQ(0.0012107, node.e());
    EXPECT_DOUBLE_EQ(160.8295, node.omega());
    EXPECT_DOUBLE_EQ(196.0076, node.M());
    EXPECT_DOUBLE_EQ(15.79438158, node.n());
    EXPECT_EQ(39, node.revolution_number());
    EXPECT_EQ(11, node.element_number());
    EXPECT_TRUE(node.ephemeris_type() == '0');
}
//------------------------------------------------------------------------------

TEST(tle_stream_test, output)
{
    tle_node node;
    node.sat_name() = "Mir";
    node.sat_number() = "16609";
    node.classification() = 'U';
    node.designator() = "86017A";
    node.precise_epoch() = string2date("86053.30522506");
    node.dn() = 0.00057349;
    node.d2n() = 0;
    node.BSTAR() = 0.00031166;
    node.i() = 51.6129;
    node.Omega() = 108.0599;
    node.e() = 0.0012107;
    node.omega() = 160.8295;
    node.M() = 196.0076;
    node.n() = 15.79438158;
    node.revolution_number() = 39;
    node.element_number() = 11;
    node.ephemeris_type() = '0';

    // Output
    std::stringstream lines(std::stringstream::in | std::stringstream::out);
    lines << node;
    // Get first line
    char str[72] = "";
    lines.getline(str, 72);
    EXPECT_TRUE(std::string(str) == "1 16609U 86017A   86053.30522506  .00057349  00000-0  31166-3 0   112");
    // Get second line
    lines.getline(str, 72);
    EXPECT_TRUE(std::string(str) == "2 16609  51.6129 108.0599 0012107 160.8295 196.0076 15.79438158   394");
}
//------------------------------------------------------------------------------

TEST(tle_stream_test, parsingMode)
{
    std::string line1 = "Mir                     \n";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349  00000-0  31166-3 0   112\n";
    std::string line3 = "2zsdfgsdfdsggsdfsdfsdfsdfsdfsdfsdfdsgdgrsasdfasdfsdfsdfgfdgdfgdsfgsd2\n"; // invalid line with valid checksum

    std::stringstream lines(std::stringstream::in | std::stringstream::out);
    lines << line1 << line2 << line3;

    tle_stream tle(lines, three_lines);
    tle_node node;
    EXPECT_NO_THROW(tle >> node); // second line is invalid, but node does not parse it here

    // Set enforce parsing
    lines.seekg(0, std::ios::beg);
    tle.enforce_parsing(true);
    EXPECT_THROW(tle >> node, tle_invalid_format); // second line is invalid and node tries to parse it here
}
//------------------------------------------------------------------------------
