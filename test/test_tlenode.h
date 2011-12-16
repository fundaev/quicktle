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

#include <string>
#include <iostream>
#include <ctime>

#include <gtest/gtest.h>
#include <tlelib/tlenode.h>
#include <tlelib/tleexception.h>

using namespace tlelib;

class tle_node_test: public tle_node, public ::testing::Test
{
};

//
//---- TESTS -------------------------------------------------------------------

TEST(tle_node_test, tle_node_exceptions)
{
    std::string line1 = "Mir";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349  00000-0  31166-3 0   112";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295 196.0076 15.79438158   394";

    EXPECT_NO_THROW(tle_node());
    EXPECT_NO_THROW(tle_node(line1, line2, line3, true));
    EXPECT_NO_THROW(tle_node(line2, line3, true));

    // Opearating with existing node
    tle_node node;//(line1, line2, line3);
    EXPECT_NO_THROW(node.assign(line1, line2, line3));
    EXPECT_NO_THROW(node.assign(line2, line3));

    // Too short lines
    EXPECT_THROW(tle_node("1 16609U 86017A   ", "2 16609  51.6129 108.0599 0012107 160.8295 196.0076 15.79438158   394"), tle_too_short_string);
    EXPECT_THROW(tle_node("1 16609U 86017A   86053.30522506  .00057349  00000-0  31166-3 0   112", "2 16609  51.6129 108.0599 0012107 160.8295 196.0076 15.79438158"), tle_too_short_string);

    // Checksum error
    EXPECT_THROW(tle_node("1 16609U 86017A   86053.30522506  .00057349  00000-0  31166-3 0   115", "2 16609  51.6129 108.0599 0012107 160.8295 196.0076 15.79438158   394"), tle_checksum_error);
    EXPECT_THROW(tle_node("1 16609U 86017A   86053.30522506  .00057349  00000-0  31166-3 0   112", "2 16609  51.6129 108.0599 0012107 160.8295 196.0076 15.79438158   398"), tle_checksum_error);
}
//------------------------------------------------------------------------------

TEST(tle_nodeTest, tle_node_Elements)
{
    std::string line1 = "Mir                     ";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349  00000-0  31166-3 0   112";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295 196.0076 15.79438158   394";

    tle_node node(line1, line2, line3);
    EXPECT_TRUE(node.sat_name() == "Mir");
    EXPECT_TRUE(node.sat_number() == "16609");
    EXPECT_TRUE(node.classification() == 'U');
    EXPECT_TRUE(node.designator() == "86017A");
    EXPECT_TRUE(node.ephemeris_type() == '0');
    EXPECT_EQ(11, node.element_number());
    EXPECT_EQ(39, node.revolution_number());
    EXPECT_DOUBLE_EQ(0.00057349, node.dn());
    EXPECT_DOUBLE_EQ(0, node.d2n());
    EXPECT_DOUBLE_EQ(0.31166e-3, node.BSTAR());
    EXPECT_DOUBLE_EQ(51.6129, node.i());
    EXPECT_DOUBLE_EQ(108.0599, node.Omega());
    EXPECT_DOUBLE_EQ(0.0012107, node.e());
    EXPECT_DOUBLE_EQ(160.8295, node.omega());
    EXPECT_DOUBLE_EQ(196.0076, node.M());
    EXPECT_DOUBLE_EQ(15.79438158, node.n());
    // Epoch: Feb 23, 1986 07:19:23 UTC
    std::time_t dt = node.epoch();
    std::tm *t = gmtime(&dt);
    EXPECT_EQ(86, t->tm_year); // 1986
    EXPECT_EQ(1, t->tm_mon);   // Feb
    EXPECT_EQ(22, t->tm_mday); // 22
    EXPECT_EQ(7, t->tm_hour);  // 07
    EXPECT_EQ(19, t->tm_min);  // 19
    EXPECT_EQ(31, t->tm_sec);  // 31
}
//------------------------------------------------------------------------------

TEST(tle_nodeTest, tle_node_Output)
{
    std::string line1 = "Mir                     ";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349  00000-0  31166-3 0   112";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295 196.0076 15.79438158   394";

    EXPECT_TRUE(tle_node(line1, line2, line3).first_string() == line1);
    EXPECT_TRUE(tle_node(line1, line2, line3).second_string() == line2);
    EXPECT_TRUE(tle_node(line1, line2, line3).third_string() == line3);
}
//------------------------------------------------------------------------------
