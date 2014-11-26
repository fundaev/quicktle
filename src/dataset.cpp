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
/*!
    \file dataset.cpp
    \brief File contains the realization of methods of tlelib::DataSet class
*/

#include <dataset.h>

namespace tlelib
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

DataSet::IndexType DataSet::nearestNotLess(const time_t &t, bool &found)
{
    found = false;
    IndexType size = m_data.size();
    if (!size)
        return 0;

    time_t value;
    if (t >= (value = m_data.at(size - 1).epoch()))
    {
        found = (value == t);
        return size;
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

} //namespace tlelib
