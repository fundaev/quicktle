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

#include <gtest/gtest.h>
#include <quicktle/dataset.h>

using namespace quicktle;

class DataSetTest: public DataSet, public ::testing::Test
{
};

//
//---- TESTS -------------------------------------------------------------------

TEST(DataSetTest, append)
{
    std::string line1 = "Satellite-1";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349"
            "  00000-0  31166-3 0   112";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295"
            " 196.0076 15.79438158   394";
    // Right order: node5, node3, node1, node4, node2
    Node node1(line1, line2, line3);
    node1.setSatelliteName("Satellite-1");

    Node node2(node1);
    node2.setSatelliteName("Satellite-2");
    node2.setPreciseEpoch(node1.epoch() + 86400);

    Node node3(node2);
    node3.setSatelliteName("Satellite-3");
    node3.setPreciseEpoch(node1.epoch() - 86400);

    Node node4(node3);
    node4.setSatelliteName("Satellite-4");
    node4.setPreciseEpoch(node1.epoch() + 3600);

    Node node5(node4);
    node5.setSatelliteName("Satellite-5");
    node5.setPreciseEpoch(node1.epoch() - 2 * 86400);

    DataSet dataSet;
    dataSet.append(node1);
    dataSet.append(node2);
    dataSet.append(node3);
    dataSet.append(node4);
    dataSet.append(node5);

    EXPECT_EQ(5, dataSet.size());
    EXPECT_EQ("Satellite-5", dataSet.node(0)->satelliteName());
    EXPECT_EQ("Satellite-3", dataSet.node(1)->satelliteName());
    EXPECT_EQ("Satellite-1", dataSet.node(2)->satelliteName());
    EXPECT_EQ("Satellite-4", dataSet.node(3)->satelliteName());
    EXPECT_EQ("Satellite-2", dataSet.node(4)->satelliteName());

    dataSet.clear();
    EXPECT_EQ(0, dataSet.size());
}
//------------------------------------------------------------------------------

TEST(DataSetTest, node)
{
    std::string line1 = "Satellite-1";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349"
            "  00000-0  31166-3 0   112";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295"
            " 196.0076 15.79438158   394";
    Node node1(line1, line2, line3);
    node1.setSatelliteName("Satellite-1");

    Node node2(node1);
    node2.setSatelliteName("Satellite-2");
    node2.setPreciseEpoch(node2.epoch() + 86400);

    Node node3(node2);
    node3.setSatelliteName("Satellite-3");
    node3.setPreciseEpoch(node3.epoch() + 86400);

    Node node4(node3);
    node4.setSatelliteName("Satellite-4");
    node4.setPreciseEpoch(node4.epoch() + 86400);

    Node node5(node4);
    node5.setSatelliteName("Satellite-5");
    node5.setPreciseEpoch(node5.epoch() + 86400);

    DataSet dataSet;
    dataSet.append(node1);
    dataSet.append(node2);
    dataSet.append(node3);
    dataSet.append(node4);
    dataSet.append(node5);

    EXPECT_EQ(5, dataSet.size());
    EXPECT_EQ(NULL, dataSet.node(-1));
    EXPECT_EQ(NULL, dataSet.node(5));
    EXPECT_EQ("Satellite-1", dataSet.node(0)->satelliteName());
    EXPECT_EQ("Satellite-2", dataSet.node(1)->satelliteName());
    EXPECT_EQ("Satellite-3", dataSet.node(2)->satelliteName());
    EXPECT_EQ("Satellite-4", dataSet.node(3)->satelliteName());
    EXPECT_EQ("Satellite-5", dataSet.node(4)->satelliteName());

    dataSet.clear();
    EXPECT_EQ(0, dataSet.size());
}
//------------------------------------------------------------------------------

TEST(DataSetTest, remove)
{
    std::string line1 = "Satellite-1";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349"
            "  00000-0  31166-3 0   112";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295"
            " 196.0076 15.79438158   394";
    Node node1(line1, line2, line3);
    node1.setSatelliteName("Satellite-1");

    Node node2(node1);
    node2.setSatelliteName("Satellite-2");
    node2.setPreciseEpoch(node2.epoch() + 86400);

    Node node3(node2);
    node3.setSatelliteName("Satellite-3");
    node3.setPreciseEpoch(node3.epoch() + 86400);

    Node node4(node3);
    node4.setSatelliteName("Satellite-4");
    node4.setPreciseEpoch(node4.epoch() + 86400);

    Node node5(node4);
    node5.setSatelliteName("Satellite-5");
    node5.setPreciseEpoch(node5.epoch() + 86400);

    DataSet dataSet;
    dataSet.append(node1);
    dataSet.append(node2);
    dataSet.append(node3);
    dataSet.append(node4);
    dataSet.append(node5);

    EXPECT_EQ(5, dataSet.size());
    EXPECT_EQ("Satellite-1", dataSet.node(0)->satelliteName());
    EXPECT_EQ("Satellite-2", dataSet.node(1)->satelliteName());
    EXPECT_EQ("Satellite-3", dataSet.node(2)->satelliteName());
    EXPECT_EQ("Satellite-4", dataSet.node(3)->satelliteName());
    EXPECT_EQ("Satellite-5", dataSet.node(4)->satelliteName());

    dataSet.remove(node3);

    EXPECT_EQ(4, dataSet.size());
    EXPECT_EQ("Satellite-1", dataSet.node(0)->satelliteName());
    EXPECT_EQ("Satellite-2", dataSet.node(1)->satelliteName());
    EXPECT_EQ("Satellite-4", dataSet.node(2)->satelliteName());
    EXPECT_EQ("Satellite-5", dataSet.node(3)->satelliteName());

    dataSet.clear();
    EXPECT_EQ(0, dataSet.size());
}
//------------------------------------------------------------------------------

TEST(DataSetTest, nearestNode)
{
    std::string line1 = "Satellite-1";
    std::string line2 = "1 16609U 86017A   86053.30522506  .00057349"
            "  00000-0  31166-3 0   112";
    std::string line3 = "2 16609  51.6129 108.0599 0012107 160.8295"
            " 196.0076 15.79438158   394";
    Node node1(line1, line2, line3);
    node1.setSatelliteName("Satellite-1");

    Node node2(node1);
    node2.setSatelliteName("Satellite-2");
    node2.setPreciseEpoch(node1.epoch() + 86400);

    Node node3(node2);
    node3.setSatelliteName("Satellite-3");
    node3.setPreciseEpoch(node2.epoch() + 86400);

    Node node4(node3);
    node4.setSatelliteName("Satellite-4");
    node4.setPreciseEpoch(node3.epoch() + 86400);

    Node node5(node4);
    node5.setSatelliteName("Satellite-5");
    node5.setPreciseEpoch(node4.epoch() + 86400);

    DataSet dataSet;
    dataSet.append(node1);
    dataSet.append(node2);
    dataSet.append(node3);
    dataSet.append(node4);
    dataSet.append(node5);

    EXPECT_EQ(5, dataSet.size());
    EXPECT_EQ("Satellite-1", dataSet.nearestNode(node1.epoch()).satelliteName());
    EXPECT_EQ("Satellite-1", dataSet.nearestNode(node1.epoch() + 3600).satelliteName());
    EXPECT_EQ("Satellite-1", dataSet.nearestNode(node1.epoch() + 43199).satelliteName());
    EXPECT_EQ("Satellite-2", dataSet.nearestNode(node1.epoch() + 43200).satelliteName());
    EXPECT_EQ("Satellite-2", dataSet.nearestNode(node1.epoch() + 43201).satelliteName());
    EXPECT_EQ("Satellite-2", dataSet.nearestNode(node2.epoch() - 3600).satelliteName());
    EXPECT_EQ("Satellite-2", dataSet.nearestNode(node2.epoch()).satelliteName());

    EXPECT_EQ("Satellite-5", dataSet.nearestNode(node5.epoch() - 3600).satelliteName());
    EXPECT_EQ("Satellite-1", dataSet.nearestNode(node1.epoch() - 86400 * 365).satelliteName());
    EXPECT_EQ("Satellite-5", dataSet.nearestNode(node5.epoch()).satelliteName());
    EXPECT_EQ("Satellite-5", dataSet.nearestNode(node5.epoch() + 86400 * 365 * 10).satelliteName());

    dataSet.clear();
    EXPECT_EQ(0, dataSet.size());
}
//------------------------------------------------------------------------------
