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

#include <gtest/gtest.h>
#include <dataset.h>

using namespace tlelib;

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
    Node node(line1, line2, line3);

    DataSet dataSet;

    for (int i = 0; i < 10; ++i)
    {
        node.setPreciseEpoch(node.epoch() + 3600);
        dataSet.append(node);
    }

    EXPECT_EQ(10, dataSet.size());
}
//------------------------------------------------------------------------------
