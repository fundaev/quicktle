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
/*!
    \file tlestream.cpp
    \brief File contains the realization of tle_stream object.
*/

#define TLE_LINE_LENGTH 72 //!< Length of TLE line

#include <string>
#include <iostream>

#include <tlelib/tlestream.h>

using namespace tlelib;

tle_stream::tle_stream(std::istream &source, const tle_file_type file_type)
{
    m_source = &source;
    m_file_type = file_type;
    m_enforce_parsing = false;
}
//------------------------------------------------------------------------------

std::istream &tle_stream::operator>>(tle_node &node)
{
    char buf[TLE_LINE_LENGTH] = "";

    m_source->getline(buf, TLE_LINE_LENGTH);
    std::string line1(buf);
    m_source->getline(buf, TLE_LINE_LENGTH);
    std::string line2(buf);

    if (m_file_type == three_lines)
    {
        m_source->getline(buf, TLE_LINE_LENGTH);
        std::string line3(buf);
        node.assign(line1, line2, line3, m_enforce_parsing);
    }
    else
        {
            node.assign(line1, line2, m_enforce_parsing);
        }

    return *m_source;
}
//------------------------------------------------------------------------------

tle_stream::operator bool()
{
    return *m_source ? true : false;
}
//------------------------------------------------------------------------------

bool tle_stream::enforce_parsing(bool parsingMode)
{
    bool res = m_enforce_parsing;
    m_enforce_parsing = parsingMode;
    return res;
}
//------------------------------------------------------------------------------
