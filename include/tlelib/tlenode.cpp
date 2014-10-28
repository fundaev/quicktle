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
    \file tlenode.cpp
    \brief File contains the realization of methods of tlelib::tle_node object.
*/

#define CHECKSUM_INDEX 68  //!< Index of checksum symbol in the TLE format line

#include <string>
#include <cstdlib>
#include <ctime>

#include <tlelib/tlenode.h>
#include <tlelib/tlefunc.h>

namespace tlelib
{
tle_node::tle_node()
{
    init();
    m_file_type = two_lines;
}
//------------------------------------------------------------------------------

tle_node::tle_node(const std::string& line1, const std::string& line2,
                   const std::string& line3, bool forceParsing)
{
    init();
    assign(line1, line2, line3, forceParsing);
}
//------------------------------------------------------------------------------

tle_node::tle_node(const std::string& line1, const std::string& line2,
                   bool forceParsing)
{
    init();
    assign(line1, line2, forceParsing);
}
//------------------------------------------------------------------------------

tle_node::tle_node(const tle_node& node)
{
    init();
    if (node.m_line1)
        m_line1 = new std::string(*node.m_line1);

    if (node.m_line2)
        m_line2 = new std::string(*node.m_line2);

    if (node.m_line3)
        m_line3 = new std::string(*node.m_line3);

    if (node.m_satName)
        m_satName = new std::string(*node.m_satName);

    if (node.m_satNumber)
        m_satNumber = new std::string(*node.m_satNumber);

    if (node.m_designator)
        m_designator = new std::string(*node.m_designator);

    if (node.m_dn)
        m_dn = new double(*node.m_dn);

    if (node.m_d2n)
        m_d2n = new double(*node.m_d2n);

    if (node.m_bstar)
        m_bstar = new double(*node.m_bstar);

    if (node.m_i)
        m_i = new double(*node.m_i);

    if (node.m_Omega)
        m_Omega = new double(*node.m_Omega);

    if (node.m_omega)
        m_omega = new double(*node.m_omega);

    if (node.m_M)
        m_M = new double(*node.m_M);

    if (node.m_n)
        m_n = new double(*node.m_n);

    if (node.m_e)
        m_e = new double(*node.m_e);

    if (node.m_date)
        m_date = new double(*node.m_date);

    if (node.m_classification)
        m_classification = new char(*node.m_classification);

    if (node.m_ephemeris_type)
        m_ephemeris_type = new char(*node.m_ephemeris_type);

    if (node.m_element_number)
        m_element_number = new int(*node.m_element_number);

    if (node.m_revolution_number)
        m_revolution_number = new int(*node.m_revolution_number);

    m_file_type = node.m_file_type;
}
//------------------------------------------------------------------------------

void tle_node::swap(tle_node& node)
{
    std::swap(m_line1, node.m_line1);
    std::swap(m_line2, node.m_line2);
    std::swap(m_line3, node.m_line3);

    std::swap(m_satName, node.m_satName);
    std::swap(m_satNumber, node.m_satNumber);
    std::swap(m_designator, node.m_designator);

    std::swap(m_dn, node.m_dn);
    std::swap(m_d2n, node.m_d2n);
    std::swap(m_bstar, node.m_bstar);
    std::swap(m_i, node.m_i);
    std::swap(m_Omega, node.m_Omega);
    std::swap(m_omega, node.m_omega);
    std::swap(m_M, node.m_M);
    std::swap(m_n, node.m_n);
    std::swap(m_e, node.m_e);
    std::swap(m_date, node.m_date);
    std::swap(m_classification, node.m_classification);
    std::swap(m_ephemeris_type, node.m_ephemeris_type);
    std::swap(m_element_number, node.m_element_number);
    std::swap(m_revolution_number, node.m_revolution_number);
    std::swap(m_file_type, node.m_file_type);

    std::swap(m_last_error, node.m_last_error);
}
//------------------------------------------------------------------------------

tle_node& tle_node::operator=(tle_node node)
{
    swap(node);
    return *this;
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
    m_dn = m_d2n = m_bstar = m_i = m_Omega = m_omega = m_M = m_n = m_e = NULL;
    m_classification = m_ephemeris_type = NULL;
    m_element_number = m_revolution_number = NULL;
    m_date = NULL;
    m_last_error = no_error;
}
//------------------------------------------------------------------------------

void tle_node::free()
{
    if (m_line1)
        delete m_line1;
    if (m_line2)
        delete m_line2;
    if (m_line3)
        delete m_line3;
    if (m_satName)
        delete m_satName;
    if (m_satNumber)
        delete m_satNumber;
    if (m_designator)
        delete m_designator;
    if (m_dn)
        delete m_dn;
    if (m_d2n)
        delete m_d2n;
    if (m_n)
        delete m_n;
    if (m_bstar)
        delete m_bstar;
    if (m_i)
        delete m_i;
    if (m_Omega)
        delete m_Omega;
    if (m_M)
        delete m_M;
    if (m_omega)
        delete m_omega;
    if (m_e)
        delete m_e;
    if (m_classification)
        delete m_classification;
    if (m_date)
        delete m_date;
    if (m_ephemeris_type)
        delete m_ephemeris_type;
    if (m_element_number)
        delete m_element_number;
    if (m_revolution_number)
        delete m_revolution_number;
    init();
}
//------------------------------------------------------------------------------

bool tle_node::assign(const std::string& line1, const std::string& line2,
                      const std::string& line3, bool forceParsing)
{
    // Check checksums
    error_code error = check_line(line2);
    if (error != no_error)
    {
        m_last_error = error;
        return false;
    }

    error = check_line(line3);
    if (error != no_error)
    {
        m_last_error = error;
        return false;
    }

    // Assign
    free();
    m_line1 = new std::string(line1);
    m_line2 = new std::string(line2);
    m_line3 = new std::string(line3);
    m_file_type = three_lines;
    // Parse
    if (forceParsing)
        parse_all();

    return (m_last_error == no_error);
}
//------------------------------------------------------------------------------

bool tle_node::assign(const std::string& line1, const std::string& line2,
                      bool forceParsing)
{
    // Check checksums
    error_code error = check_line(line1);
    if (error != no_error)
    {
        m_last_error = error;
        return false;
    }

    error = check_line(line2);
    if (error != no_error)
    {
        m_last_error = error;
        return false;
    }
    // Assign
    free();
    m_line2 = new std::string(line1);
    m_line3 = new std::string(line2);
    m_file_type = two_lines;
    // Parse
    if (forceParsing)
        parse_all();

    return (m_last_error == no_error);
}
//------------------------------------------------------------------------------

void tle_node::parse_all()
{
    n();
    dn();
    d2n();
    i();
    Omega();
    omega();
    M();
    e();
    bstar();
    sat_number();
    sat_name();
    designator();
    classification();
    ephemeris_type();
    element_number();
    revolution_number();
    precise_epoch();
}
//------------------------------------------------------------------------------

tle_node::error_code tle_node::check_line(const std::string &str) const
{
    if (str.length() < CHECKSUM_INDEX + 1)
        return too_short_string;

    int expected_checksum = checksum(str.substr(0, CHECKSUM_INDEX));
    int actual_checksum = atoi(str.substr(CHECKSUM_INDEX, 1).c_str());
    if (expected_checksum != actual_checksum)
        return checksum_error;

    return no_error;
}
//------------------------------------------------------------------------------

std::string tle_node::sat_number() const
{
    if (m_satNumber)
        return *m_satNumber;

    if (m_line2)
    {
        // Try to obtain the satellite number from the second line...
        error_code error = no_error;
        m_satNumber = new std::string(trim(parseString(m_line2, 2, 5, error)));
        if (error != no_error)
        {
            m_last_error = error;
            *m_satNumber = "";
        }

        if (*m_satNumber != "")
            return *m_satNumber;
    }

    if (m_line3)
    {
        if (!m_satNumber)
            m_satNumber = new std::string();

        error_code error = no_error;
        *m_satNumber = trim(parseString(m_line3, 2, 5, error));
        if (error != no_error)
        {
            m_last_error = error;
            *m_satNumber = "";
        }
    }

    return *m_satNumber;
}
//------------------------------------------------------------------------------

void tle_node::set_sat_number(const std::string& sat_number)
{
    if (m_satNumber)
        *m_satNumber = sat_number;
    else
        m_satNumber = new std::string(sat_number);
}
//------------------------------------------------------------------------------

std::string tle_node::sat_name() const
{
    if (!m_satName)
    {
        if (m_line1)
        {
            std::size_t l = m_line1->length();
            if (l > 24)
                l = 24;

            error_code error = no_error;
            m_satName = new std::string(trim(parseString(m_line1, 0, l, error)));
            if (error != no_error)
            {
                m_last_error = error;
                *m_satName = "";
            }
        }
        else
        {
            m_satName = new std::string("");
        }
    }

    return *m_satName;
}
//------------------------------------------------------------------------------

void tle_node::set_sat_name(const std::string& sat_name)
{
    if (m_satName)
        *m_satName = sat_name;
    else
        m_satName = new std::string(sat_name);
}
//------------------------------------------------------------------------------

std::string tle_node::designator() const
{
    if (!m_designator)
    {
        m_designator = new std::string;
        if (m_line2)
        {
            error_code error = no_error;
            *m_designator = trim(parseString(m_line2, 9, 8, error));
            if (error != no_error)
            {
                m_last_error = error;
                *m_designator = "";
            }
        }
    }

    return *m_designator;
}
//------------------------------------------------------------------------------

void tle_node::set_designator(const std::string& designator)
{
    if (m_designator)
        *m_designator = designator;
    else
        m_designator = new std::string(designator);
}
//------------------------------------------------------------------------------

double tle_node::n() const
{
    if (!m_n)
    {
        m_n = new double(0);
        if (m_line3)
        {
            error_code error = no_error;
            *m_n = parseDouble(m_line3, 52, 11, error);
            if (error != no_error)
            {
                m_last_error = error;
                *m_n = 0;
            }
        }
    }

    return *m_n;
}
//------------------------------------------------------------------------------

void tle_node::set_n(double n)
{
    if (m_n)
        *m_n = n;
    else
        m_n = new double(n);
}
//------------------------------------------------------------------------------

double tle_node::dn() const
{
    if (!m_dn)
    {
        m_dn = new double(0);
        if (m_line2)
        {
            error_code error = no_error;
            *m_dn = parseDouble(m_line2, 33, 10, error);
            if (error != no_error)
            {
                m_last_error = error;
                *m_dn = 0;
            }
        }
    }

    return *m_dn;
}
//------------------------------------------------------------------------------

void tle_node::set_dn(double dn)
{
    if (m_dn)
        *m_dn = dn;
    else
        m_dn = new double(dn);
}
//------------------------------------------------------------------------------

double tle_node::d2n() const
{
    if (!m_d2n)
    {
        m_d2n = new double(0);
        if (m_line2)
        {
            error_code error = no_error;
            *m_d2n = parseDouble(m_line2, 44, 8, error, true);
            if (error != no_error)
            {
                m_last_error = error;
                *m_d2n = 0;
            }
        }
    }

    return *m_d2n;
}
//------------------------------------------------------------------------------

void tle_node::set_d2n(double d2n)
{
    if (m_d2n)
        *m_d2n = d2n;
    else
        m_d2n = new double(d2n);
}
//------------------------------------------------------------------------------

double tle_node::i() const
{
    if (!m_i)
    {
        m_i = new double(0);
        if (m_line3)
        {
            error_code error = no_error;
            *m_i = parseDouble(m_line3, 8, 8, error);
            if (error != no_error)
            {
                m_last_error = error;
                *m_i = 0;
            }
        }
    }

    return *m_i;
}
//------------------------------------------------------------------------------

void tle_node::set_i(double i)
{
    if (m_i)
        *m_i = i;
    else
        m_i = new double(i);
}
//------------------------------------------------------------------------------

double tle_node::Omega() const
{
    if (!m_Omega)
    {
        m_Omega = new double(0);
        if (m_line3)
        {
            error_code error = no_error;
            *m_Omega = parseDouble(m_line3, 17, 8, error);
            if (error != no_error)
            {
                m_last_error = error;
                *m_Omega = 0;
            }
        }
    }

    return *m_Omega;
}
//------------------------------------------------------------------------------

void tle_node::set_Omega(double Omega)
{
    if (m_Omega)
        *m_Omega = Omega;
    else
        m_Omega = new double(Omega);
}
//------------------------------------------------------------------------------

double tle_node::omega() const
{
    if (!m_omega)
    {
        m_omega = new double(0);
        if (m_line3)
        {
            error_code error = no_error;
            *m_omega = parseDouble(m_line3, 34, 8, error);
            if (error != no_error)
            {
                m_last_error = error;
                *m_omega = 0;
            }
        }
    }

    return *m_omega;
}
//------------------------------------------------------------------------------

void tle_node::set_omega(double omega)
{
    if (m_omega)
        *m_omega = omega;
    else
        m_omega = new double(omega);
}
//------------------------------------------------------------------------------

double tle_node::M() const
{
    if (!m_M)
    {
        m_M = new double(0);
        if (m_line3)
        {
            error_code error = no_error;
            *m_M = parseDouble(m_line3, 43, 8, error);
            if (error != no_error)
            {
                m_last_error = error;
                *m_M = 0;
            }
        }
    }

    return *m_M;
}
//------------------------------------------------------------------------------

void tle_node::set_M(double M)
{
    if (m_M)
        *m_M = M;
    else
        m_M = new double(M);
}
//------------------------------------------------------------------------------

double tle_node::bstar() const
{
    if (!m_bstar)
    {
        m_bstar = new double(0);
        if (m_line2)
        {
            error_code error = no_error;
            *m_bstar = parseDouble(m_line2, 53, 8, error, true);
            if (error != no_error)
            {
                m_last_error = error;
                *m_bstar = 0;
            }
        }
    }

    return *m_bstar;
}
//------------------------------------------------------------------------------

void tle_node::set_bstar(double bstar)
{
    if (m_bstar)
        *m_bstar = bstar;
    else
        m_bstar = new double(bstar);
}
//------------------------------------------------------------------------------

double tle_node::e() const
{
    if (!m_e)
    {
        m_e = new double(0);
        if (m_line3)
        {
            error_code error = no_error;
            *m_e = parseDouble(m_line3, 26, 8, error, true);
            if (error != no_error)
            {
                m_last_error = error;
                *m_e = 0;
            }
        }
    }

    return *m_e;
}
//------------------------------------------------------------------------------

void tle_node::set_e(double e)
{
    if (m_e)
        *m_e = e;
    else
        m_e = new double(e);
}
//------------------------------------------------------------------------------

char tle_node::classification() const
{
    if (!m_classification)
    {
        m_classification = new char('\0');
        if (m_line2)
        {
            error_code error = no_error;
            *m_classification = parseChar(m_line2, 7, error);
            if (error != no_error)
            {
                m_last_error = error;
                *m_classification = '\0';
            }
        }
    }

    return *m_classification;
}
//------------------------------------------------------------------------------

void tle_node::set_classification(char classification)
{
    if (m_classification)
        *m_classification = classification;
    else
        m_classification = new char(classification);
}
//------------------------------------------------------------------------------

char tle_node::ephemeris_type() const
{
    if (!m_ephemeris_type)
    {
        m_ephemeris_type = new char('\0');
        if (m_line2)
        {
            error_code error = no_error;
            *m_ephemeris_type = parseChar(m_line2, 62, error);
            if (error != no_error)
            {
                m_last_error = error;
                *m_ephemeris_type = '\0';
            }
        }
    }

    return *m_ephemeris_type;
}
//------------------------------------------------------------------------------

void tle_node::set_ephemeris_type(char ephemeris_type)
{
    if (m_ephemeris_type)
        *m_ephemeris_type = ephemeris_type;
    else
        m_ephemeris_type = new char(ephemeris_type);
}
//------------------------------------------------------------------------------

int tle_node::element_number() const
{
    if (!m_element_number)
    {
        m_element_number = new int(0);
        if (m_line2)
        {
            error_code error = no_error;
            *m_element_number = parseInt(m_line2, 64, 4, error);
            if (error != no_error)
            {
                m_last_error = error;
                *m_element_number = 0;
            }
        }
    }

    return *m_element_number;
}
//------------------------------------------------------------------------------

void tle_node::set_element_number(int element_number)
{
    if (m_element_number)
        *m_element_number = element_number;
    else
        m_element_number = new int(element_number);
}
//------------------------------------------------------------------------------

int tle_node::revolution_number() const
{
    if (!m_revolution_number)
    {
        m_revolution_number = new int(0);
        if (m_line3)
        {
            error_code error = no_error;
            *m_revolution_number = parseInt(m_line3, 63, 5, error);
            if (error != no_error)
            {
                m_last_error = error;
                *m_revolution_number = 0;
            }
        }
    }

    return *m_revolution_number;
}
//------------------------------------------------------------------------------

void tle_node::set_revolution_number(int revolution_number)
{
    if (m_revolution_number)
        *m_revolution_number = revolution_number;
    else
        m_revolution_number = new int(revolution_number);
}
//------------------------------------------------------------------------------

double tle_node::precise_epoch() const
{
    if (!m_date)
    {
        if (m_line2)
        {
            error_code error =no_error;
            std::string date = parseString(m_line2, 18, 14, error);
            if (error != no_error)
            {
                m_last_error = error;
                return 0;
            }

            m_date = new double(string2date(date, error));
            if (error != no_error)
            {
                m_last_error = error;
                *m_date = 0;
            }
        }
        else
        {
            m_date = new double(0);
        }
    }

    return *m_date;
}
//------------------------------------------------------------------------------

void tle_node::set_precise_epoch(double precise_epoch)
{
    if (m_date)
        *m_date = precise_epoch;
    else
        m_date = new double(precise_epoch);
}
//------------------------------------------------------------------------------

std::time_t tle_node::epoch() const
{
    return static_cast<std::time_t>(precise_epoch());
}
//------------------------------------------------------------------------------

std::string tle_node::first_string() const
{
    std::string res = sat_name();
    while (res.length() < 24)
        res += " ";

    return res;
}
//------------------------------------------------------------------------------

std::string tle_node::second_string() const
{
    std::string res = "1 ";
    res += string2string(sat_number(), 5);
    const char cl = classification();
    res += (isprint(cl) ? std::string(1, cl) : " ") + " ";
    res += string2string(designator(), 8) + " ";
    res += date2string(precise_epoch(), 14) + " ";
    res += double2string(dn(), 10, 8, false, false, false) + " ";
    res += double2string(d2n(), 8, 3, true, true, false) + " ";
    res += double2string(bstar(), 8, 3, true, true, false) + " ";
    const char eph = ephemeris_type();
    res += (isprint(eph) ? std::string(1, eph) : " ") + " ";
    res += int2string(element_number(), 4, false);

    // Checksum
    int sum = checksum(res);
    res += int2string(sum, 1);

    return res;
}
//------------------------------------------------------------------------------

std::string tle_node::third_string() const
{
    std::string res = "2 ";
    res += string2string(sat_number(), 5) + " ";
    res += double2string(normalize_angle(i()), 8, 4, false, false, false) + " ";
    res += double2string(normalize_angle(Omega()), 8, 4, false, false, false) +
           " ";
    res += double2string(e(), 7, 7, false, true, false) + " ";
    res += double2string(normalize_angle(omega()), 8, 4, false, false, false) +
           " ";
    res += double2string(normalize_angle(M()), 8, 4, false, false, false) + " ";
    res += double2string(n(), 11, 8, false, false, false);
    res += int2string(revolution_number(), 5, false);

    // Checksum
    int sum = checksum(res);
    res += int2string(sum, 1);

    return res;
}
//------------------------------------------------------------------------------

tle_node& tle_node::output_format(const tle_file_type format)
{
    m_file_type = format;
    return *this;
}
//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& stream, tle_node& node)
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

}  // namespace tlelib
