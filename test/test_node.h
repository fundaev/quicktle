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

#include <string>
#include <iostream>
#include <ctime>
#include <cmath>
#include <gtest/gtest.h>
#include <quicktle/node.h>
#include <quicktle/func.h>

#define E_RELATIVE_ERROR 1e-7
#define GM 3.986004418e14

using namespace quicktle;

class NodeTest: public Node, public ::testing::Test
{
public:
    double dE() const
    {
        return fabs(E()) * E_RELATIVE_ERROR;
    }
    double dnu() const
    {
        return fabs( 2 * sqrt( (1 + e()) / (1 - e()) ) * dE()
               / ( 1 - e() * cos(E()) ) );
    }
    double dr() const
    {
        return fabs(p() * e() * sin(nu()) * dnu() / pow(1 + e() * cos(nu()), 2));
    }
    double dx() const
    {
        return fabs( -r() * (
                cos(Omega()) * sin(omega() + nu())
                + sin(Omega()) * cos(omega() + nu()) * cos(i())
        ) * dnu() + x() * dr() / r() );
    }
    double dy() const
    {
        return fabs( r() * (
                -sin(Omega()) * sin(omega() + nu())
                + cos(Omega()) * cos(omega() + nu()) * cos(i())
        ) * dnu() + y() * dr() / r() );
    }
    double dz() const
    {
        return fabs( r() * cos(omega() + nu()) * sin(i()) * dnu()
                     + z() * dr() / r() );
    }
};

//
//---- TESTS -------------------------------------------------------------------

TEST_F(NodeTest, exceptions)
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

    // Operating with existing node
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

TEST_F(NodeTest, elements)
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
    EXPECT_DOUBLE_EQ(2 * 0.00057349 * 2 * M_PI / 86400 / 86400, node.dn());
    EXPECT_DOUBLE_EQ(6 * 0 * 2 * M_PI / 86400 / 86400 / 86400, node.d2n());
    EXPECT_DOUBLE_EQ(0.31166e-3, node.bstar());
    EXPECT_DOUBLE_EQ(deg2rad(51.6129), node.i());
    EXPECT_DOUBLE_EQ(deg2rad(108.0599), node.Omega());
    EXPECT_DOUBLE_EQ(0.0012107, node.e());
    EXPECT_DOUBLE_EQ(deg2rad(160.8295), node.omega());
    EXPECT_DOUBLE_EQ(deg2rad(196.0076), node.M());
    EXPECT_DOUBLE_EQ(15.79438158 * 2 * M_PI / 86400, node.n());
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

TEST_F(NodeTest, output)
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

TEST_F(NodeTest, swap)
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

TEST_F(NodeTest, copyConstructor)
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

TEST_F(NodeTest, assigment)
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

TEST_F(NodeTest, nu_E_M)
{
    set_e(0.5);

    set_M(0);
    EXPECT_DOUBLE_EQ(0, E());
    EXPECT_DOUBLE_EQ(0, nu());

    set_M(M_PI);
    EXPECT_NEAR(M_PI, E(), dE());
    EXPECT_NEAR(M_PI, nu(), dE());

    set_M(M_PI_4);
    EXPECT_NE(M(), E());
    EXPECT_NE(M(), nu());
    EXPECT_NE(nu(), E());

    set_M(M_PI_2);
    EXPECT_NE(M(), E());
    EXPECT_NE(M(), nu());
    EXPECT_NE(nu(), E());

    set_M(-M_PI_4);
    EXPECT_NE(M(), E());
    EXPECT_NE(M(), nu());
    EXPECT_NE(nu(), E());

    set_M(-M_PI_2);
    EXPECT_NE(M(), E());
    EXPECT_NE(M(), nu());
    EXPECT_NE(nu(), E());

    set_e(0);

    set_M(M_PI_4);
    EXPECT_NEAR(M(), E(), dE());
    EXPECT_NEAR(M(), nu(), dE());
    EXPECT_DOUBLE_EQ(nu(), E());

    set_M(M_PI_2);
    EXPECT_NEAR(M(), E(), dE());
    EXPECT_NEAR(M(), nu(), dE());
    EXPECT_DOUBLE_EQ(nu(), E());

    set_M(-M_PI_4);
    EXPECT_NEAR(M(), E(), dE());
    EXPECT_NEAR(M(), nu(), dE());
    EXPECT_DOUBLE_EQ(nu(), E());

    set_M(-M_PI_2);
    EXPECT_NEAR(M(), E(), dE());
    EXPECT_NEAR(M(), nu(), dE());
    EXPECT_DOUBLE_EQ(nu(), E());
}
//------------------------------------------------------------------------------

TEST_F(NodeTest, set_E_set_nu)
{
    set_e(0.3);
    double angle = M_PI / 7;
    set_E(angle);
    EXPECT_DOUBLE_EQ(angle - 0.3 * sin(angle), M());
    EXPECT_NEAR(angle, E(), dE());

    set_nu(angle);
    EXPECT_NEAR(angle, nu(), dE());

    Node node;
    node.set_e(e());

    node.set_M(M());
    EXPECT_NEAR(E(), node.E(), dE());
    EXPECT_NEAR(nu(), node.nu(), dE());
}
//------------------------------------------------------------------------------

TEST_F(NodeTest, a_p_r)
{
    set_e(0);
    set_n(15);
    set_nu(M_PI / 7);
    EXPECT_DOUBLE_EQ(15, n());
    EXPECT_DOUBLE_EQ(p(), a());
    EXPECT_DOUBLE_EQ(p(), r());

    double e = 0.6;
    double nu = M_PI / 7;

    set_e(e);
    set_nu(nu);
    EXPECT_NE(p(), a());
    EXPECT_NE(p(), r());

    double r = p() / (1 + e * cos(nu));
    EXPECT_NEAR(r, NodeTest::r(), dr());
}
//------------------------------------------------------------------------------

TEST_F(NodeTest, x_y_z)
{
    double a = 10000;
    double e = 0;
    double i = 0;
    double nu = M_PI / 3;

    set_e(e);
    set_n(sqrt(GM / pow(a, 3)));
    set_i(i);
    set_nu(nu);

    EXPECT_NEAR(a * cos(nu), x(), dx());
    EXPECT_NEAR(a * sin(nu), y(), dy());
    EXPECT_NEAR(0, z(), dz());

    i = M_PI / 5;
    set_i(i);
    EXPECT_NEAR(a * cos(nu), x(), dx());
    EXPECT_NEAR(a * sin(nu) * cos(i), y(), dy());
    EXPECT_NEAR(a * sin(nu) * sin(i), z(), dz());
}
//------------------------------------------------------------------------------