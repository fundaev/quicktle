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

#ifndef TLEFUNC_H
#define TLEFUNC_H

#include <string>
#include <ctime>

namespace tlelib
{

std::string int2string(const int val, const std::size_t minWidth = 0, const bool leftAlign = true);
std::string double2string(const double val, const std::size_t fieldLength, const std::size_t precission=6, const bool scientific=false, const bool decimalPointAssumed = false, const bool leftAlign = true);
std::string string2string(const std::string &str, const std::size_t fieldLength, const bool leftAlign = true, const bool allowCutOff = true);
std::string date2string(const double date, const std::size_t fieldLength, const bool leftAlign = true);
int string2int(const std::string &str);
double string2double(const std::string &str);
std::string trim(const std::string& str);
char parseChar(const std::string *line, const std::size_t index);
std::string parseString(const std::string *line, const std::size_t start, const std::size_t length);
int parseInt(const std::string *line, const std::size_t start, const std::size_t length);
double parseDouble(const std::string *line, const std::size_t start, const std::size_t length, const bool decimalPointAssumed=false);
double string2date(const std::string &str);
int checksum(const std::string &str);

} // namespace tlelib
#endif // TLEFUNC_H
