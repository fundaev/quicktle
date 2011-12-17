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
    \file tlenode.cpp
    \brief File contains the realization of methods of tlelib::tle_node object.
*/

#define CHECKSUM_INDEX 68 //!< Index of checksum symbol in the TLE format line

#include <string>
#include <cstdlib>
#include <ctime>

#include <tlelib/tlenode.h>
#include <tlelib/tlefunc.h>
#include <tlelib/tleexception.h>

namespace tlelib
{

tle_node::tle_node()
{
    init();
    m_file_type = two_lines;
}
//------------------------------------------------------------------------------

tle_node::tle_node(const std::string& line1, const std::string& line2, const std::string& line3, bool forceParsing)
{
    init();
    assign(line1, line2, line3, forceParsing);
    m_file_type = three_lines;
}
//------------------------------------------------------------------------------

tle_node::tle_node(const std::string& line1, const std::string& line2, bool forceParsing)
{
    init();
    assign(line1, line2, forceParsing);
    m_file_type = two_lines;
}
//------------------------------------------------------------------------------

tle_node::~tle_node()
{
    free();
}
//------------------------------------------------------------------------------

void tle_node::init()
{
    m_line1 = m_line2 = m_line3 = m_satName = m_satNumber = m_designator = NULL;
    m_dn = m_d2n = m_Bstar = m_i = m_Omega = m_omega = m_M = m_n = m_e = NULL;
    m_classification = m_ephemerisType = NULL;
    m_elementNumber = m_revolutionNumber = NULL;
    m_date = NULL;
}
//------------------------------------------------------------------------------

void tle_node::free()
{
    if (m_line1) delete m_line1;
    if (m_line2) delete m_line2;
    if (m_line3) delete m_line3;
    if (m_satName) delete m_satName;
    if (m_satNumber) delete m_satNumber;
    if (m_designator) delete m_designator;
    if (m_dn) delete m_dn;
    if (m_d2n) delete m_d2n;
    if (m_n) delete m_n;
    if (m_Bstar) delete m_Bstar;
    if (m_i) delete m_i;
    if (m_Omega) delete m_Omega;
    if (m_M) delete m_M;
    if (m_omega) delete m_omega;
    if (m_e) delete m_e;
    if (m_classification) delete m_classification;
    if (m_date) delete m_date;
    if (m_ephemerisType) delete m_ephemerisType;
    if (m_elementNumber) delete m_elementNumber;
    if (m_revolutionNumber) delete m_revolutionNumber;
    init();
}
//------------------------------------------------------------------------------

void tle_node::assign(const std::string& line1, const std::string& line2, const std::string& line3, bool forceParsing)
{
    // Check checksums
    check_line(line2);
    check_line(line3);
    // Assign
    free();
    m_line1 = new std::string(line1);
    m_line2 = new std::string(line2);
    m_line3 = new std::string(line3);
    // Parse
    if (forceParsing) parse_all();
}
//------------------------------------------------------------------------------

void tle_node::assign(const std::string& line1, const std::string& line2, bool forceParsing)
{
    // Check checksums
    check_line(line1);
    check_line(line2);
    // Assign
    free();
    m_line2 = new std::string(line1);
    m_line3 = new std::string(line2);
    // Parse
    if (forceParsing) parse_all();
}
//------------------------------------------------------------------------------

void tle_node::parse_all()
{
    n(); dn(); d2n(); i(); Omega(); omega(); M(); e(); BSTAR();
    sat_number(); sat_name(); designator();
    classification(); ephemeris_type();
    element_number(); revolution_number();
    precise_epoch();
}
//------------------------------------------------------------------------------

void tle_node::check_line(const std::string &str) const
{
    if (str.length() < CHECKSUM_INDEX + 1)
        throw tle_too_short_string(str);

    int expected_checksum = checksum(str.substr(0, CHECKSUM_INDEX));
    int actual_checksum = atoi(str.substr(CHECKSUM_INDEX, 1).c_str());
    if (expected_checksum != actual_checksum)
        throw tle_checksum_error(str, expected_checksum, actual_checksum);
}
//------------------------------------------------------------------------------

std::string &tle_node::sat_number()
{
    if (!m_satNumber)
    {
        if (m_line2)
        {
            // Try to obtain the satellite number from the second line...
            m_satNumber = new std::string(trim(parseString(m_line2, 2, 5)));
            // or from third line
            if (*m_satNumber == "")
            {
                delete m_satNumber;
                m_satNumber = new std::string(trim(parseString(m_line3, 2, 5)));
            }
        }
        else
            {
                m_satNumber = new std::string("");
            }
    }
    return *m_satNumber;
}
//------------------------------------------------------------------------------

std::string &tle_node::sat_name()
{
    if (!m_satName)
    {
        if (m_line1)
        {
            std::size_t l = m_line1->length();
            if (l > 24) l = 24;
            m_satName = new std::string(trim(parseString(m_line1, 0, l)));
        }
        else
            m_satName = new std::string("");
    }

    return *m_satName;
}
//------------------------------------------------------------------------------

std::string &tle_node::designator()
{
    if (!m_designator)
    {
        m_designator = m_line2 ? new std::string(trim(parseString(m_line2, 9, 8))) : new std::string("");
    }

    return *m_designator;
}
//------------------------------------------------------------------------------

double &tle_node::n()
{
    if (!m_n)
    {
        m_n = m_line3 ? new double(parseDouble(m_line3, 52, 11)) : new double(0);
    }

    return *m_n;
}
//------------------------------------------------------------------------------

double &tle_node::dn()
{
    if (!m_dn)
    {
        m_dn = m_line2 ? new double(parseDouble(m_line2, 33, 10)) : new double(0);
    }

    return *m_dn;
}
//------------------------------------------------------------------------------

double &tle_node::d2n()
{
    if (!m_d2n)
    {
        m_d2n = m_line2 ? new double(parseDouble(m_line2, 44, 8, true)) : new double(0);
    }

    return *m_d2n;
}
//------------------------------------------------------------------------------

double &tle_node::i()
{
    if (!m_i)
    {
        m_i = m_line3 ? new double(parseDouble(m_line3, 8, 8)) : new double(0);
    }

    return *m_i;
}
//------------------------------------------------------------------------------

double &tle_node::Omega()
{
    if (!m_Omega)
    {
        m_Omega = m_line3 ? new double(parseDouble(m_line3, 17, 8)) : new double(0);
    }

    return *m_Omega;
}
//------------------------------------------------------------------------------

double &tle_node::omega()
{
    if (!m_omega)
    {
        m_omega = m_line3 ? new double(parseDouble(m_line3, 34, 8)) : new double(0);
    }

    return *m_omega;
}
//------------------------------------------------------------------------------

double &tle_node::M()
{
    if (!m_M)
    {
        m_M = m_line3 ? new double(parseDouble(m_line3, 43, 8)) : new double(0);
    }

    return *m_M;
}
//------------------------------------------------------------------------------

double &tle_node::BSTAR()
{
    if (!m_Bstar)
    {
        m_Bstar = m_line2 ? new double(parseDouble(m_line2, 53, 8, true)) : new double(0);
    }

    return *m_Bstar;
}
//------------------------------------------------------------------------------

double &tle_node::e()
{
    if (!m_e)
    {
        m_e = m_line3 ? new double(parseDouble(m_line3, 26, 7, true)) : new double(0);
    }

    return *m_e;
}
//------------------------------------------------------------------------------

char &tle_node::classification()
{
    if (!m_classification)
    {
        m_classification = m_line2 ? new char(parseChar(m_line2, 7)) : new char('\0');
    }

    return *m_classification;
}
//------------------------------------------------------------------------------

char &tle_node::ephemeris_type()
{
    if (!m_ephemerisType)
    {
        m_ephemerisType = m_line2 ? new char(parseChar(m_line2, 62)) : new char('\0');
    }

    return *m_ephemerisType;
}
//------------------------------------------------------------------------------

int &tle_node::element_number()
{
    if (!m_elementNumber)
    {
        m_elementNumber = m_line2 ? new int(parseInt(m_line2, 64, 4)) : new int(0);
    }

    return *m_elementNumber;
}
//------------------------------------------------------------------------------

int &tle_node::revolution_number()
{
    if (!m_revolutionNumber)
    {
        m_revolutionNumber = m_line3 ? new int(parseInt(m_line3, 63, 5)) : new int(0);
    }

    return *m_revolutionNumber;
}
//------------------------------------------------------------------------------

double &tle_node::precise_epoch()
{
    if (!m_date)
    {
        if (m_line2)
        {
            std::string date = parseString(m_line2, 18, 14);
            m_date = new double(string2date(date));
        }
        else
            {
                m_date = new double(0);
            }
    }

    return *m_date;
}
//------------------------------------------------------------------------------

std::time_t tle_node::epoch()
{
    return static_cast<std::time_t>(precise_epoch());
}
//------------------------------------------------------------------------------

std::string tle_node::first_string()
{
    std::string res = sat_name();
    while (res.length() < 24) res += " ";
    return res;
}
//------------------------------------------------------------------------------

std::string tle_node::second_string()
{
    std::string res = "1 ";
    res += string2string(sat_number(), 5);
    const char cl = classification();
    res += (isprint(cl) ? std::string(1, cl) : " ") + " ";
    res += string2string(designator(), 8) + " ";
    res += date2string(precise_epoch(), 14) + " ";
    res += double2string(dn(), 10, 8, false, false, false) + " ";
    res += double2string(d2n(), 8, 3, true, true, false) + " ";
    res += double2string(BSTAR(), 8, 3, true, true, false) + " ";
    const char eph = ephemeris_type();
    res += (isprint(eph) ? std::string(1, eph) : " ") + " ";
    res += int2string(element_number(), 4, false);

    // Checksum
    int sum = checksum(res);
    res += int2string(sum, 1);

    return res;
}
//------------------------------------------------------------------------------

std::string tle_node::third_string()
{
    std::string res = "2 ";
    res += string2string(sat_number(), 5) + " ";
    res += double2string(normalize_angle(i()), 8, 4, false, false, false) + " ";
    res += double2string(normalize_angle(Omega()), 8, 4, false, false, false) + " ";
    res += double2string(e(), 7, 7, false, true, false) + " ";
    res += double2string(normalize_angle(omega()), 8, 4, false, false, false) + " ";
    res += double2string(normalize_angle(M()), 8, 4, false, false, false) + " ";
    res += double2string(n(), 11, 8, false, false, false);
    res += int2string(revolution_number(), 5, false);

    // Checksum
    int sum = checksum(res);
    res += int2string(sum, 1);

    return res;
}
//------------------------------------------------------------------------------

tle_node &tle_node::output_format(const tle_file_type format)
{
    m_file_type = format;
    return *this;
}
//------------------------------------------------------------------------------

std::ostream &operator<<(std::ostream &stream, tle_node &node)
{
    if (node.m_file_type == three_lines)
    {
        // Three lines TLE format
        stream << node.first_string() << std::endl;
    }
    stream << node.second_string() << std::endl;
    stream << node.third_string() << std::endl;

    return stream;
}
//------------------------------------------------------------------------------

} // namespace tlelib
