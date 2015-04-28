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
/*!
    \file dataset.cpp
    \brief File contains the realization of methods of quicktle::DataSet class
*/

#include <quicktle/dataset.h>

namespace quicktle
{

DataSet& DataSet::append(const Node &node)
{
    bool found = false;
    IndexType index = nearestNotLess(node.epoch(), found);

    if (found)
        m_data[index] = node;
    else if (index >= m_data.size())
        m_data.push_back(node);
    else
        m_data.insert(m_data.begin() + index, node);

	return *this;
}
//------------------------------------------------------------------------------

DataSet::IndexType DataSet::nearestNotLess(const time_t &t, bool &found) const
{
    found = false;
    IndexType size = m_data.size();
    if (!size)
        return 0;

    time_t value;
    if (t >= (value = m_data.at(size - 1).epoch()))
    {
        found = (value == t);
        return (found ? size - 1 : size);
    }

    if (t <= (value = m_data.at(0).epoch()))
    {
        found = (value == t);
        return 0;
    }

    IndexType begin = 0;
    IndexType end = size - 1;
    while (begin < end)
    {
        IndexType middle = begin + (end - begin) / 2;
        if (m_data.at(middle).epoch() < t)
            begin = middle + 1;
        else
            end = middle;
    }

    found = (m_data.at(end).epoch() == t);

    return end;
}
//------------------------------------------------------------------------------

DataSet::IndexType DataSet::size() const
{
    return m_data.size();
}
//------------------------------------------------------------------------------

bool DataSet::remove(const Node &node)
{
    bool found = false;
    IndexType index = nearestNotLess(node.epoch(), found);

    if (!found)
        return false;

    m_data.erase(m_data.begin() + index);
    return true;
}
//------------------------------------------------------------------------------

const Node& DataSet::node(const IndexType &index) const
{
    return m_data.at(index);
}
//------------------------------------------------------------------------------

const Node& DataSet::nearestNode(const time_t &t) const
{
    IndexType size = m_data.size();
    bool found = false;
    IndexType index = nearestNotLess(t, found);

    if (index == size)
        index = size - 1;

    if (index > 0)
    {
        time_t dtLeft = t - m_data.at(index - 1).epoch();
        time_t dtRight = m_data.at(index).epoch() - t;
        if (dtLeft < dtRight)
            --index;
    }

    return m_data.at(index);
}
//------------------------------------------------------------------------------

void DataSet::clear()
{
    m_data.clear();
}
//------------------------------------------------------------------------------

} //namespace quicktle
