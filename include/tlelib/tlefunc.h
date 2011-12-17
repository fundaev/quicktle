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
    \file  tlefunc.h
    \brief File contains the prototypes of functions, used by TLELib library.
*/

#ifndef TLEFUNC_H
#define TLEFUNC_H

#include <string>
#include <ctime>

namespace tlelib
{

/*!
    \brief Convert a variable of 'int' type into variable of 'std::string' type.
    \param val - an integer value
    \param fieldLength - length of the result string
    \param leftAlign - aligment of the value in the string: true - at left side, false - at right side.
    \return An object of std::string type.
*/
std::string int2string(const int val, const std::size_t fieldLength = 0, const bool leftAlign = true);

/*!
    \brief Convert a variable of 'double' type into variable of 'std::string' type.
    \param val - a value of 'double' type
    \param fieldLength - length of the result string
    \param precission - the number of digits after decimal point
    \param scientific - specifies, if the value should be presented in the scientific format. Note: in this format the 'e' symbol is not printed (i.e. 1-5 instead of 1e-5)
    \param decimalPointAssumed - specifies whether it is necessary to output the value without decimal point. For example: 0157 instead of 0.0157 or 145-6 instead of 1.45-5.
    \param leftAlign - aligment of the value in the string: true - at left side, false - at right side.
    \return An object of std::string type.
*/
std::string double2string(const double val, const std::size_t fieldLength, const std::size_t precission=6, const bool scientific=false, const bool decimalPointAssumed = false, const bool leftAlign = true);

/*!
    \brief Correct the length of a string: add the spece symbols or cut it off if it's necessary.
    \param str - an value of std::string type
    \param fieldLength - length of the result string
    \param leftAlign - aligment of the value in the string: true - at left side, false - at right side.
    \param allowCutOff - defines, if it is possible to cut the string off if its actual length exceeds the fieldLength.
    \return An object of std::string type.
*/
std::string string2string(const std::string &str, const std::size_t fieldLength, const bool leftAlign = true, const bool allowCutOff = true);

/*!
    \brief Convert a date, defined by the double value, into variable of 'std::string' type.
    \param date - the number of seconds since Jan 1, #UNIX_FIRST_YEAR
    \param fieldLength - length of the result string
    \param leftAlign - aligment of the value in the string: true - at left side, false - at right side.
    \return An object of std::string type.
*/
std::string date2string(const double date, const std::size_t fieldLength, const bool leftAlign = true);

/*!
    \brief Convert a string into integer variable.
    \param str - a string for convertion
    \return A variable of 'int' type.
*/
int string2int(const std::string &str);

/*!
    \brief Convert a string into 'double' variable.
    \param str - a string for convertion
    \return A variable of 'double' type.
*/
double string2double(const std::string &str);

/*!
    \brief Convert a string into date: number of seconds (including fractional part) since Jan 1, #UNIX_FIRST_YEAR
    \param str - a string for convertion
    \return A variable of 'double' type.
*/
double string2date(const std::string &str);

/*!
    \brief Remove the spaces from the start and end of the given string.
    \param str - the given string
    \return The string without space symbols at the start and end.
*/
std::string trim(const std::string& str);

/*!
    \brief Take a symbol at the given position from the given string.
    \param line - the given string
    \param index - index of symbol
    \return A 'char' value.
*/
char parseChar(const std::string *line, const std::size_t index);

/*!
    \brief Take a substring of the specified length at the given position from the given string.
    \param line - the given string
    \param start - index of position, where the substring is started
    \param length - length of the substring
    \return A value of 'std::string' type.
*/
std::string parseString(const std::string *line, const std::size_t start, const std::size_t length);

/*!
    \brief Take a substring from the given string and convert it by the string2int() function.
    \param line - the given string
    \param start - index of position, where the substring is started
    \param length - length of the substring
    \return A value of 'int' type.
*/
int parseInt(const std::string *line, const std::size_t start, const std::size_t length);

/*!
    \brief Take a substring from the given string and convert it by the string2double() function.
    \param line - the given string
    \param start - index of position, where the substring is started
    \param length - length of the substring
    \param decimalPointAssumed - specifies, if the value in the string is presented as a fractional part of the number.
    \return A value of 'double' type.
*/
double parseDouble(const std::string *line, const std::size_t start, const std::size_t length, const bool decimalPointAssumed=false);

/*!
    \brief Calculate the checksum for the given string, using the Modulo 10 algorithm
    \param str - the string, for which the checksum should be calculated
    \return Return the checksum of 'int' type.
*/
int checksum(const std::string &str);

/*!
    \brief Make the angle value between 0 and 360 degrees
    \param angle - angle
    \return Angle [0 - 360) degrees
*/
double normalize_angle(double angle);

} // namespace tlelib
#endif // TLEFUNC_H
