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
    \file stream.h
    \brief File contains the definition of quicktle::Stream class.
*/

#ifndef TLESTREAM_H
#define TLESTREAM_H

#include <iostream>
#include <quicktle/dataset.h>

namespace quicktle
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
        \param fileType - TLE file type (2- or 3-lines)
    */
    Stream(std::istream &source, const FileType fileType = TwoLines);
    /*!
        \brief Extract the Node object from the input stream.
        \param node - the Node object
        \return Reference to input stream
    */
    Stream& operator>>(Node &node);
    /*!
        \brief Extract the Node object from the input stream
               and put it into data set
        \param dataSet - data set
        \return Reference to input stream
    */
    Stream& operator>>(DataSet &dataSet);
    /*!
        \brief Operator bool()
        \return True if the input stream can be read further.
    */
    operator bool();
    /*!
        \brief Set the parsing mode
        \param parsingMode - parsing mode: true means, that the node object,
                             obtained by >> operator, should parse the lines
                             immediately, false - should parse the lines
                             when it is required (lazy initialization).
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

} // namespace quicktle

#endif // TLESTREAM_H
