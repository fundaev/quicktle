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
    \file tlestream.h
    \brief File contains the definition of tle_stream object.
*/

#ifndef TLESTREAM_H
#define TLESTREAM_H

#include <iostream>

#include <tlelib/tlenode.h>

namespace tlelib
{

enum tle_file_type {two_lines, three_lines};

class tle_stream
{
    std::istream *m_source;
    tle_file_type m_file_type;
    tle_stream() {}
public:
    tle_stream(std::istream &source, const tle_file_type = two_lines);
    std::istream &operator>>(tle_node &node);
    operator bool();
};
//------------------------------------------------------------------------------

} // namespace tlelib

#endif // TLESTREAM_H
