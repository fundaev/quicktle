/*-----------------------------------------------------------------------------+
 | QuickTle                                                                    |
 | Copyright 2011-2015 Sergei Fundaev                                          |
 +-----------------------------------------------------------------------------+
 | This file is part of QuickTle library.                                      |
 |                                                                             |
 | QuickTle is free software: you can redistribute it and/or modify            |
 | it under the terms of the GNU Lesser General Public License as published by |
 | the Free Software Foundation, either version 3 of the License, or           |
 | (at your option) any later version.                                         |
 |                                                                             |
 | QuickTle is distributed in the hope that it will be useful,                 |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of              |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               |
 | GNU Lesser General Public License for more details.                         |
 |                                                                             |
 | You should have received a copy of the GNU Lesser General Public License    |
 | along with QuickTle. If not, see <http://www.gnu.org/licenses/>.            |
 +----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <gtest/gtest.h>
#include <quicktle/func.h>
#include <quicktle/node.h>
#include <quicktle/stream.h>

using namespace quicktle;

class StreamTest: public Stream, public ::testing::Test
{
};

//
//---- TESTS -------------------------------------------------------------------

TEST(StreamTest, input)
{
    std::string line1 = "Mir                     \n";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349  00000-0"
                                                          "  31166-3 0   112\n";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295 196.0076"
                                                         " 15.79438158   394\n";

    std::stringstream lines(std::stringstream::in | std::stringstream::out);
    lines << line1 << line2 << line3;

    Stream tle(lines, ThreeLines);
    Node node;
    tle >> node;

    // Check values
    EXPECT_EQ("Mir", node.satelliteName());
    EXPECT_EQ("16609", node.satelliteNumber());
    EXPECT_EQ("86017A", node.designator());
    EXPECT_EQ('U', node.classification());
    EXPECT_DOUBLE_EQ(2 * 0.00057349 * 2 * M_PI / 86400 / 86400,  node.dn());
    EXPECT_DOUBLE_EQ(0, node.d2n());
    EXPECT_DOUBLE_EQ(0.00031166, node.bstar());
    EXPECT_DOUBLE_EQ(deg2rad(51.6129), node.i());
    EXPECT_DOUBLE_EQ(deg2rad(108.0599), node.Omega());
    EXPECT_DOUBLE_EQ(0.0012107, node.e());
    EXPECT_DOUBLE_EQ(deg2rad(160.8295), node.omega());
    EXPECT_DOUBLE_EQ(deg2rad(196.0076), node.M());
    EXPECT_DOUBLE_EQ(15.79438158 * 2 * M_PI / 86400, node.n());
    EXPECT_EQ(39, node.revolutionNumber());
    EXPECT_EQ(11, node.elementNumber());
    EXPECT_EQ('0', node.ephemerisType());
}
//------------------------------------------------------------------------------

TEST(StreamTest, output)
{
    Node node;
    node.setSatelliteName("Mir");
    node.setSatelliteNumber("16609");
    node.setClassification('U');
    node.setDesignator("86017A");
    Node::ErrorCode error;
    node.setPreciseEpoch(string2date("86053.30522506", error));
    node.set_dn(2 * 0.00057349 * 2 * M_PI / 86400 / 86400);
    node.set_d2n(0);
    node.set_bstar(0.00031166);
    node.set_i(deg2rad(51.6129));
    node.set_Omega(deg2rad(108.0599));
    node.set_e(0.0012107);
    node.set_omega(deg2rad(160.8295));
    node.set_M(deg2rad(196.0076));
    node.set_n(15.79438158  * 2 * M_PI / 86400);
    node.setRevolutionNumber(39);
    node.setElementNumber(11);
    node.setEphemerisType('0');

    // Output
    std::stringstream lines(std::stringstream::in | std::stringstream::out);
    lines << node;
    // Get first line
    char str[72] = "";
    lines.getline(str, 72);
    EXPECT_EQ("1 16609U 86017A   86053.30522506  .00057349  00000-0  31166-3 0"
                                                    "   112", std::string(str));
    // Get second line
    lines.getline(str, 72);
    EXPECT_EQ("2 16609  51.6129 108.0599 0012107 160.8295 196.0076 15.79438158"
                                                    "   394", std::string(str));
}
//------------------------------------------------------------------------------

TEST(StreamTest, parsingMode)
{
    std::string line1 = "Mir                     \n";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349  00000-0"
                                                          "  31166-3 0   112\n";
    std::string line3 = "2zsdfgsdfdsggsdfsdfsdfsdfsdfsdfsdfdsgdgrsasdfasdfsdf"
                    "sdfgfdgdfgdsfgsd2\n"; // invalid line with valid checksum

    std::stringstream lines(std::stringstream::in | std::stringstream::out);
    lines << line1 << line2 << line3;

    Stream tle(lines, ThreeLines);
    Node node;
    EXPECT_NO_THROW(tle >> node);
    // second line is invalid, but node does not parse it here
    EXPECT_EQ(Node::NoError, node.lastError());

    // Set enforce parsing
    lines.seekg(0, std::ios::beg);
    tle.enforceParsing(true);
    EXPECT_NO_THROW(tle >> node); 
    // second line is invalid and node tries to parse it here
    EXPECT_EQ(Node::InvalidFormat, node.lastError()); 
}
//------------------------------------------------------------------------------
