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
#include <tlelib/tlenode.h>

using namespace tlelib;

class NodeTest: public Node, public ::testing::Test
{
};

//
//---- TESTS -------------------------------------------------------------------

TEST(NodeTest, Node_exceptions)
{
    std::string line1 = "Mir";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349"
                                                   "  00000-0  31166-3 0   112";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295"
                                                  " 196.0076 15.79438158   394";

    EXPECT_NO_THROW(Node());
    EXPECT_EQ(Node::NoError, Node().lastError());

    EXPECT_NO_THROW(Node(line1, line2, line3, true));
    EXPECT_EQ(Node::NoError,
                         Node(line1, line2, line3, true).lastError());

    EXPECT_NO_THROW(Node(line2, line3, true));
    EXPECT_EQ(Node::NoError, Node(line2, line3, true).lastError());

    // Opearating with existing node
    Node node;
    EXPECT_NO_THROW(node.assign(line1, line2, line3));
    EXPECT_EQ(Node::NoError, node.lastError());

    EXPECT_NO_THROW(node.assign(line2, line3));
    EXPECT_EQ(Node::NoError, node.lastError());

    // Too short lines
    node = Node("1 16609U 86017A   ", "2 16609  51.6129 108.0599 0012107"
                                        " 160.8295 196.0076 15.79438158   394");
    EXPECT_EQ(Node::TooShortString, node.lastError());

    node = Node("1 16609U 86017A   86053.30522506  .00057349  00000-0  31166-3"
                " 0   112", "2 16609  51.6129 108.0599 0012107 160.8295"
                " 196.0076 15.79438158");
    EXPECT_EQ(Node::TooShortString, node.lastError());

    // Checksum error
    node = Node("1 16609U 86017A   86053.30522506  .00057349  00000-0  31166-3"
                " 0   115", "2 16609  51.6129 108.0599 0012107 160.8295"
                " 196.0076 15.79438158   394");
    EXPECT_EQ(Node::ChecksumError, node.lastError());

    node = Node("1 16609U 86017A   86053.30522506  .00057349  00000-0  31166-3"
                " 0   112", "2 16609  51.6129 108.0599 0012107 160.8295"
                " 196.0076 15.79438158   398");
    EXPECT_EQ(Node::ChecksumError, node.lastError());
}
//------------------------------------------------------------------------------

TEST(NodeTest, Node_Elements)
{
    std::string line1 = "Mir                     ";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349  00000-0"
                                                            "  31166-3 0   112";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295 196.0076"
                                                           " 15.79438158   394";

    Node node(line1, line2, line3);
    EXPECT_EQ("Mir", node.satelliteName());
    EXPECT_EQ("16609", node.satelliteNumber());
    EXPECT_EQ('U', node.classification());
    EXPECT_EQ("86017A", node.designator());
    EXPECT_EQ('0', node.ephemerisType());
    EXPECT_EQ(11, node.elementNumber());
    EXPECT_EQ(39, node.revolutionNumber());
    EXPECT_DOUBLE_EQ(0.00057349, node.dn());
    EXPECT_DOUBLE_EQ(0, node.d2n());
    EXPECT_DOUBLE_EQ(0.31166e-3, node.bstar());
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

TEST(NodeTest, Node_Output)
{
    std::string line1 = "Mir                     ";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349  00000-0"
                                                            "  31166-3 0   112";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295 196.0076"
                                                           " 15.79438158   394";
    EXPECT_EQ(line1, Node(line1, line2, line3).firstString());
    EXPECT_EQ(line2, Node(line1, line2, line3).secondString());
    EXPECT_EQ(line3, Node(line1, line2, line3).thirdString());
}
//------------------------------------------------------------------------------

TEST(NodeTest, Node_swap)
{
    std::string line1 = "Mir                     ";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349  00000-0"
                                                            "  31166-3 0   112";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295 196.0076"
                                                           " 15.79438158   394";
    Node node1(line1, line2, line3);
    Node node1_origin(line1, line2, line3);

    line1 = "ASIASAT 6               ";
    line2 = "1 40141U 14052A   14277.84589631 -.00000387  00000-0  10000-3 0"
                                                                       "   362";
    line3 = "2 40141   0.0409 337.4123 0002696 277.4110 182.9520  1.00272844"
                                                                       "   312";
    Node node2(line1, line2, line3);
    node1.swap(node2);

    EXPECT_EQ(node1_origin.satelliteName(), node2.satelliteName());
    EXPECT_EQ(node1_origin.satelliteNumber(), node2.satelliteNumber());
    EXPECT_EQ(node1_origin.designator(), node2.designator());

    EXPECT_DOUBLE_EQ(node1_origin.n(), node2.n());
    EXPECT_DOUBLE_EQ(node1_origin.dn(), node2.dn());
    EXPECT_DOUBLE_EQ(node1_origin.d2n(), node2.d2n());
    EXPECT_DOUBLE_EQ(node1_origin.i(), node2.i());
    EXPECT_DOUBLE_EQ(node1_origin.Omega(), node2.Omega());
    EXPECT_DOUBLE_EQ(node1_origin.omega(), node2.omega());
    EXPECT_DOUBLE_EQ(node1_origin.M(), node2.M());
    EXPECT_DOUBLE_EQ(node1_origin.bstar(), node2.bstar());
    EXPECT_DOUBLE_EQ(node1_origin.e(), node2.e());
    EXPECT_DOUBLE_EQ(node1_origin.preciseEpoch(), node2.preciseEpoch());

    EXPECT_EQ(node1_origin.epoch(), node2.epoch());
    EXPECT_EQ(node1_origin.elementNumber(), node2.elementNumber());
    EXPECT_EQ(node1_origin.revolutionNumber(), node2.revolutionNumber());

    EXPECT_EQ(node1_origin.firstString(), node2.firstString());
    EXPECT_EQ(node1_origin.secondString(), node2.secondString());
    EXPECT_EQ(node1_origin.thirdString(), node2.thirdString());
}
//------------------------------------------------------------------------------

TEST(NodeTest, Node_copy_constructor)
{
    std::string line1 = "Mir                     ";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349  00000-0"
                                                            "  31166-3 0   112";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295 196.0076"
                                                           " 15.79438158   394";
    Node node1(line1, line2, line3);
    Node node2(node1);

    EXPECT_NO_THROW(node2.firstString());
    EXPECT_NO_THROW(node2.secondString());
    EXPECT_NO_THROW(node2.thirdString());

    EXPECT_EQ(node1.satelliteName(), node2.satelliteName());
    EXPECT_EQ(node1.satelliteNumber(), node2.satelliteNumber());
    EXPECT_EQ(node1.designator(), node2.designator());

    EXPECT_DOUBLE_EQ(node1.n(), node2.n());
    EXPECT_DOUBLE_EQ(node1.dn(), node2.dn());
    EXPECT_DOUBLE_EQ(node1.d2n(), node2.d2n());
    EXPECT_DOUBLE_EQ(node1.i(), node2.i());
    EXPECT_DOUBLE_EQ(node1.Omega(), node2.Omega());
    EXPECT_DOUBLE_EQ(node1.omega(), node2.omega());
    EXPECT_DOUBLE_EQ(node1.M(), node2.M());
    EXPECT_DOUBLE_EQ(node1.bstar(), node2.bstar());
    EXPECT_DOUBLE_EQ(node1.e(), node2.e());
    EXPECT_DOUBLE_EQ(node1.preciseEpoch(), node2.preciseEpoch());

    EXPECT_EQ(node1.epoch(), node2.epoch());
    EXPECT_EQ(node1.elementNumber(), node2.elementNumber());
    EXPECT_EQ(node1.revolutionNumber(), node2.revolutionNumber());

    EXPECT_EQ(node1.firstString(), node2.firstString());
    EXPECT_EQ(node1.secondString(), node2.secondString());
    EXPECT_EQ(node1.thirdString(), node2.thirdString());
}
//------------------------------------------------------------------------------

TEST(NodeTest, Node_assigment)
{
    std::string line1 = "Mir                     ";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349  00000-0"
                                                            "  31166-3 0   112";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295 196.0076"
                                                           " 15.79438158   394";
    Node node1;

    {
        Node tmp_node(line1, line2, line3);
        node1 = tmp_node;
    }

    EXPECT_NO_THROW(node1.firstString());
    EXPECT_NO_THROW(node1.secondString());
    EXPECT_NO_THROW(node1.thirdString());

    Node node2(line1, line2, line3);
    EXPECT_EQ(node1.satelliteName(), node2.satelliteName());
    EXPECT_EQ(node1.satelliteNumber(), node2.satelliteNumber());
    EXPECT_EQ(node1.designator(), node2.designator());

    EXPECT_DOUBLE_EQ(node1.n(), node2.n());
    EXPECT_DOUBLE_EQ(node1.dn(), node2.dn());
    EXPECT_DOUBLE_EQ(node1.d2n(), node2.d2n());
    EXPECT_DOUBLE_EQ(node1.i(), node2.i());
    EXPECT_DOUBLE_EQ(node1.Omega(), node2.Omega());
    EXPECT_DOUBLE_EQ(node1.omega(), node2.omega());
    EXPECT_DOUBLE_EQ(node1.M(), node2.M());
    EXPECT_DOUBLE_EQ(node1.bstar(), node2.bstar());
    EXPECT_DOUBLE_EQ(node1.e(), node2.e());
    EXPECT_DOUBLE_EQ(node1.preciseEpoch(), node2.preciseEpoch());

    EXPECT_EQ(node1.epoch(), node2.epoch());
    EXPECT_EQ(node1.elementNumber(), node2.elementNumber());
    EXPECT_EQ(node1.revolutionNumber(), node2.revolutionNumber());

    EXPECT_EQ(node1.firstString(), node2.firstString());
    EXPECT_EQ(node1.secondString(), node2.secondString());
    EXPECT_EQ(node1.thirdString(), node2.thirdString());
}
//------------------------------------------------------------------------------
