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
    \file dataset.h
    \brief File contains the definition of tlelib::DataSet class.
*/

#ifndef TLEDATASET_H
#define TLEDATASET_H

#include <vector>
#include <node.h>

namespace tlelib
{

class DataSet
{
public:
    /*!
        \brief Append new node to data set
        \param node - TLE-node
        \return Reference to itself
    */
    DataSet& append(const Node &node);

private:
	unsigned long nearestNotLess(const time_t &t, bool &found);

	std::vector<Node> m_data;
};

} // namespace tlelib

#endif // TLEDATASET_H
