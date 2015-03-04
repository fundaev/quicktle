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
    \file dataset.h
    \brief File contains the definition of quicktle::DataSet class.
*/

#ifndef TLEDATASET_H
#define TLEDATASET_H

#include <vector>
#include <node.h>

namespace quicktle
{

class DataSet
{
public:
    typedef std::vector<Node>::size_type IndexType;
    /*!
        \brief Append new node to data set
        \param node - TLE-node
        \return Reference to itself
    */
    DataSet& append(const Node &node);
    /*!
        \brief Remove \a node from data set
        \param node - TLE-node
        \return True if specified node is found and removed,
                else returns false
    */
    bool remove(const Node &node);
    /*!
        \brief Clear data set
    */
    void clear();
    /*!
        \brief Number of nodes in data set
        \return Number of nodes in data set
    */
    IndexType size() const;
    /*!
        \brief Get node at the given index
        \param index - node index
        \return Node at the given index
    */
    const Node* node(const IndexType &index) const;
    /*!
        \brief Find the node with nearest to \a t date and time
               and returns its copy
        \param t - date and time
        \return Copy of the nearest node
    */
    Node nearestNode(const time_t &t) const;

private:
    IndexType nearestNotLess(const time_t &t, bool &found) const;

	std::vector<Node> m_data;
};

} // namespace quicktle

#endif // TLEDATASET_H
