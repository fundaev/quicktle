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
    \file func.cpp
    \brief File contains the realizations of the functions, defined
           in the func.h file and used by the QuickTle library.
*/

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <func.h>

#define UNIX_FIRST_YEAR 1970
#define MAX_ANGLE 360.0

namespace quicktle
{

std::string int2string(const int val, const std::size_t fieldLength,
                       const bool leftAlign)
{
    std::stringstream buf;
    buf << val;
    return string2string(trim(buf.str()), fieldLength, leftAlign, false);
}
//------------------------------------------------------------------------------

std::string double2string(const double val, const std::size_t fieldLength,
                          const std::size_t precision, const bool scientific,
                          const bool decimalPointAssumed,
                          const bool leftAlign)
{
    char str[fieldLength];
    double val1 = val;
    if (decimalPointAssumed)
    {
        double val3;
        val1 = modf(val, &val3);
    }
    sprintf(str, ("%" + int2string(fieldLength) + "." +
                  int2string(precision + (scientific ? 1 : 0)) +
                  (scientific ? "e" : "f")).c_str(),
            val1);
    std::string res(str);

    // Remove decimal point
    std::size_t pos = res.find(".");
    int n = 0;
    if (decimalPointAssumed && pos != std::string::npos && scientific)
    {
        n = -pos;
        res.replace(pos, 1, "");
    }
    else if (decimalPointAssumed && !scientific)
    {
        pos = res.find("0.");
        if (pos != std::string::npos)
            res.replace(pos, 2, "");
    }

    // Remove point from scientific format
    if (scientific)
    {
        std::size_t e_pos = res.find("e");
        std::string base = res.substr(0, e_pos);
        std::string a = res.substr(e_pos + 1, res.length() - e_pos - 1);
        std::size_t pos1 = base.find(".");
        if (pos1 != std::string::npos)
        {
            n = base.length() - pos1 - 1;
            base.replace(pos1, 1, "");
        }
        Node::ErrorCode error;
        int new_a = string2int(a, error) - n;
        if (string2double(base, error) == 0)
            new_a = 0;
        res = base + (new_a > 0 ? "+" : "-") + int2string(abs(new_a));
    }
    res = trim(res);

    // Correct "0." or "-0."
    if (res.substr(0, 2) == "0.")
        res = res.substr(1, res.length() - 1);
    else if (res.substr(0, 3) == "-0.")
        res = "-" + res.substr(2, res.length() - 2);

    return string2string(res, fieldLength, leftAlign, false);
}
//------------------------------------------------------------------------------

std::string string2string(const std::string &str,
                          const std::size_t fieldLength, const bool leftAlign,
                          const bool allow_cut_off)
{
    if (!fieldLength || str.length() == fieldLength)
        return str;

    if (str.length() > fieldLength)
        return (allow_cut_off ? str.substr(0, fieldLength) : str);

    std::string fill_str(fieldLength - str.length(), ' ');
    return (leftAlign ? str + fill_str : fill_str + str);
}
//------------------------------------------------------------------------------

std::string date2string(const double date, const std::size_t fieldLength,
                        const bool leftAlign)
{
    double dt = date;
    std::size_t year = UNIX_FIRST_YEAR;
    while (true)
    {
        bool leap = !(year % 4) && ((year % 100) || !(year % 400));
        std::time_t l = (leap ? 366 : 365) * 86400;
        if (dt < l)
            break;
        dt -= l;
        year++;
    }
    year -= year > 2000 ? 2000 : 1900;
    double res = year * 1000 + dt / 86400.0 + 1;

    std::string pref = year < 10 ? "0" : "";
    std::size_t length = year < 10 ? fieldLength - 1 : fieldLength;
    return (pref + double2string(res, length, fieldLength - 6,
                                 false, false,  leftAlign));
}
//------------------------------------------------------------------------------

int string2int(const std::string &str, Node::ErrorCode &error)
{
    std::string val = trim(str);
    // Validate string
    for (std::size_t i = 0; i < val.length(); i++)
    {
        if (!isdigit(val[i]) && !(i == 0 && (val[i] == '-' || val[i] == '+')))
        {
            error = Node::InvalidFormat;
            return 0;
        }
    }

    return atoi(val.c_str());
}
//------------------------------------------------------------------------------

double string2double(const std::string &str, Node::ErrorCode &error)
{
    std::string val = trim(str);
    // Validate string
    for (std::size_t i = 0; i < val.length(); i++)
    {
        bool valid = isdigit(val[i]);  // it is a digit
        valid =
            valid ||
            (i == 0 &&
             (val[i] == '-' ||
              val[i] ==
                  '+'));  // it is not a digit, but it is a sign at the start
        // it is not a gigit and not a sign at the start, but it is 'e' or 'E'
        valid = valid || (i > 0 && (val[i] == 'e' || val[i] == 'E') &&
                          (isdigit(val[i - 1]) || val[i - 1] == '.') &&
                          i < val.length() - 1);
        // it is not a gigit and not a sign at the start and not 'e' or 'E', but
        // it is a sign after 'e' or 'E'
        valid = valid || (i > 0 && (val[i] == '-' || val[i] == '+') &&
                          (val[i - 1] == 'e' || val[i - 1] == 'E') &&
                          i < val.length() - 1);
        // may be it is a decimal point?..
        valid = valid || (val[i] == '.');

        if (!valid)
        {
            error = Node::InvalidFormat;
            return 0;
        }
    }
    return atof(val.c_str());
}
//------------------------------------------------------------------------------

std::string trim(const std::string &str)
{
    std::string res(str);
    while (res.length() && res[0] == ' ')
        res = res.substr(1, res.length() - 1);

    while (res.length() && res[res.length() - 1] == ' ')
        res = res.substr(0, res.length() - 1);

    return res;
}
//------------------------------------------------------------------------------

char parseChar(const std::string *line, const std::size_t index,
               Node::ErrorCode &error)
{
    if (!line)
        return '\0';

    if (line->length() - 1 < index)
    {
        error = Node::TooShortString;
        return '\0';
    }

    return (*line)[index];
}
//------------------------------------------------------------------------------

std::string parseString(const std::string *line, const std::size_t start,
                        const std::size_t length, Node::ErrorCode &error)
{
    if (!line)
        return std::string();

    if (line->length() < start + length)
    {
        error = Node::TooShortString;
        return std::string();
    }

    return line->substr(start, length);
}
//------------------------------------------------------------------------------

int parseInt(const std::string *line, const std::size_t start,
             const std::size_t length, Node::ErrorCode &error)
{
    if (!line)
        return 0;

    if (line->length() < start + length)
    {
        error = Node::TooShortString;
        return 0;
    }

    return string2int(trim(line->substr(start, length)), error);
}
//------------------------------------------------------------------------------

double parseDouble(const std::string *line, const std::size_t start,
                   const std::size_t length, Node::ErrorCode &error,
                   const bool decimalPointAssumed)
{
    if (!line)
        return 0;

    if (line->length() < start + length)
    {
        error = Node::TooShortString;
        return 0;
    }

    std::string val = trim(line->substr(start, length));
    // Prepare string
    if (decimalPointAssumed)
    {
        if (val[0] == '-' || val[0] == '+')
            val = val.substr(0, 1) + "0." + val.substr(1, val.length() - 1);
        else
            val = "0." + val;
    }
    // -- 123-4 or 123+4 -> 123e-4 or 123e4 --
    std::size_t pos = val.rfind('-');
    if (pos != std::string::npos && pos && val[pos - 1] != 'e'
                                                       && val[pos - 1] != 'E')
    {
        val.replace(pos, 1, "e-");
    }
    pos = val.rfind('+');
    if (pos != std::string::npos && pos && val[pos - 1] != 'e'
                                                       && val[pos - 1] != 'E')
    {
        val.replace(pos, 1, "e+");
    }

    return string2double(val.c_str(), error);
}
//------------------------------------------------------------------------------

double string2date(const std::string &str, Node::ErrorCode &error)
{
    std::string str1(trim(str));
    // Validate
    if (str1.find('-') != std::string::npos)
    {
        error = Node::InvalidFormat;
        return 0;
    }

    // Year
    error = Node::NoError;
    int year = string2int(str1.substr(0, 2).c_str(), error);
    if (error != Node::NoError)
        return 0;

    year += (year < (UNIX_FIRST_YEAR - (UNIX_FIRST_YEAR / 100) * 100))
          ? 2000
          : 1900;

    double res = 0;
    for (int y = UNIX_FIRST_YEAR; y < year; y++)
    {
        // If current year is leap
        bool leap = !(y % 4) && ((y % 100) || !(y % 400));
        res += leap ? 366 : 365;
    }
    // Years -> seconds
    res *= 86400;
    // Additional part
    res +=
       (string2double(str1.substr(2, str1.length() - 2), error) - 1) * 86400;

    return res;
}
//------------------------------------------------------------------------------

int checksum(const std::string &str)
{
    int checksum = 0;
    for (std::size_t i = 0; i < str.length(); i++)
        checksum += isdigit(str[i]) ? atoi(str.substr(i, 1).c_str())
                                    : (str[i] == '-' ? 1 : 0);
    // Get the last digit
    checksum -= (checksum / 10) * 10;

    return checksum;
}
//------------------------------------------------------------------------------

double normalizeAngle(double angle)
{
    if (angle >= MAX_ANGLE)
        angle -= MAX_ANGLE * floor(angle / MAX_ANGLE);
    else if (angle < 0)
        angle += MAX_ANGLE * ceil(fabs(angle) / MAX_ANGLE);

    return angle;
}
//------------------------------------------------------------------------------

}  // namespace quicktle
