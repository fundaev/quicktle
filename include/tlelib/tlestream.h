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
    \file tlestream.h
    \brief File contains the definition of Stream object.
*/

#ifndef TLESTREAM_H
#define TLESTREAM_H

#include <iostream>
#include <tlelib/tlenode.h>

namespace tlelib
{

/*!
    \brief Class for operations with an input stream.
*/
class Stream
{
public:
    /*!
        \brief Constructor.
        \param source - input stream
        \param file_type - TLE file type (2- or 3-lines)
    */
    Stream(std::istream &source, const FileType fileType = TwoLines);
    /*!
        \brief Extract the Node object from the input stream.
        \param node - the Node object
        \return Reference to input stream
    */
    std::istream &operator>>(Node &node);
    /*!
        \brief Operator bool()
        \return True if the input stream can be read further.
    */
    operator bool();
    /*!
        \brief Set the parsing mode
        \param parsingMode - parsing mode: true means, that the node object,
                             obtained by >> operator, shoud parse the lines
                             immediately, false - should parse the lines
                             when it is required (lazy initalization).
        \return Previous value of parsing mode.
    */
    bool enforceParsing(bool parsingMode);

private:
    Stream() {} //!< Default constructor is unavailable.

    std::istream *m_source;
    FileType m_fileType;
    bool m_enforceParsing;
};
//------------------------------------------------------------------------------

} // namespace tlelib

#endif // TLESTREAM_H
