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
    \brief File contains the realization of methods of tlelib::Node object.
*/

#define CHECKSUM_INDEX 68  //!< Index of checksum symbol in the TLE format line

#define TLELIB_FREE(x) if (x) { delete x; x = NULL; }

#include <string>
#include <cstdlib>
#include <ctime>

#include <tlelib/tlenode.h>
#include <tlelib/tlefunc.h>

namespace tlelib
{

Node::Node()
{
    init();
    m_fileType = TwoLines;
}
//------------------------------------------------------------------------------

Node::Node(const std::string &line1, const std::string &line2,
           const std::string &line3, bool forceParsing)
{
    init();
    assign(line1, line2, line3, forceParsing);
}
//------------------------------------------------------------------------------

Node::Node(const std::string &line1, const std::string &line2,
           bool forceParsing)
{
    init();
    assign(line1, line2, forceParsing);
}
//------------------------------------------------------------------------------

Node::Node(const Node &node)
{
    init();
    if (node.m_line1)
        m_line1 = new std::string(*node.m_line1);

    if (node.m_line2)
        m_line2 = new std::string(*node.m_line2);

    if (node.m_line3)
        m_line3 = new std::string(*node.m_line3);

    if (node.m_satelliteName)
        m_satelliteName = new std::string(*node.m_satelliteName);

    if (node.m_satelliteNumber)
        m_satelliteNumber = new std::string(*node.m_satelliteNumber);

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

    if (node.m_ephemerisType)
        m_ephemerisType = new char(*node.m_ephemerisType);

    if (node.m_elementNumber)
        m_elementNumber = new int(*node.m_elementNumber);

    if (node.m_revolutionNumber)
        m_revolutionNumber = new int(*node.m_revolutionNumber);

    m_fileType = node.m_fileType;
}
//------------------------------------------------------------------------------

void Node::swap(Node& node)
{
    std::swap(m_line1, node.m_line1);
    std::swap(m_line2, node.m_line2);
    std::swap(m_line3, node.m_line3);

    std::swap(m_satelliteName, node.m_satelliteName);
    std::swap(m_satelliteNumber, node.m_satelliteNumber);
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
    std::swap(m_ephemerisType, node.m_ephemerisType);
    std::swap(m_elementNumber, node.m_elementNumber);
    std::swap(m_revolutionNumber, node.m_revolutionNumber);
    std::swap(m_fileType, node.m_fileType);

    std::swap(m_lastError, node.m_lastError);
}
//------------------------------------------------------------------------------

Node& Node::operator=(Node node)
{
    swap(node);
    return *this;
}
//------------------------------------------------------------------------------

Node::~Node()
{
    free();
}
//------------------------------------------------------------------------------

void Node::init()
{
    m_line1 = m_line2 = m_line3 = m_satelliteName = m_satelliteNumber = m_designator = NULL;
    m_dn = m_d2n = m_bstar = m_i = m_Omega = m_omega = m_M = m_n = m_e = NULL;
    m_classification = m_ephemerisType = NULL;
    m_elementNumber = m_revolutionNumber = NULL;
    m_date = NULL;
    m_lastError = NoError;
}
//------------------------------------------------------------------------------

void Node::free()
{
    TLELIB_FREE(m_line1)
    TLELIB_FREE(m_line2)
    TLELIB_FREE(m_line3)
    TLELIB_FREE(m_satelliteName)
    TLELIB_FREE(m_satelliteNumber)
    TLELIB_FREE(m_designator)
    TLELIB_FREE(m_dn)
    TLELIB_FREE(m_d2n)
    TLELIB_FREE(m_n)
    TLELIB_FREE(m_bstar)
    TLELIB_FREE(m_i)
    TLELIB_FREE(m_Omega)
    TLELIB_FREE(m_M)
    TLELIB_FREE(m_omega)
    TLELIB_FREE(m_e)
    TLELIB_FREE(m_classification)
    TLELIB_FREE(m_date)
    TLELIB_FREE(m_ephemerisType)
    TLELIB_FREE(m_elementNumber)
    TLELIB_FREE(m_revolutionNumber)
}
//------------------------------------------------------------------------------

bool Node::assign(const std::string &line1, const std::string &line2,
                  const std::string &line3, bool forceParsing)
{
    // Check checksums
    ErrorCode error = checkLine(line2);
    if (error != NoError)
    {
        m_lastError = error;
        return false;
    }

    error = checkLine(line3);
    if (error != NoError)
    {
        m_lastError = error;
        return false;
    }

    // Assign
    free();
    m_line1 = new std::string(line1);
    m_line2 = new std::string(line2);
    m_line3 = new std::string(line3);
    m_fileType = ThreeLines;
    // Parse
    if (forceParsing)
        parseAll();

    return (m_lastError == NoError);
}
//------------------------------------------------------------------------------

bool Node::assign(const std::string &line1, const std::string &line2,
                  bool forceParsing)
{
    // Check checksums
    ErrorCode error = checkLine(line1);
    if (error != NoError)
    {
        m_lastError = error;
        return false;
    }

    error = checkLine(line2);
    if (error != NoError)
    {
        m_lastError = error;
        return false;
    }
    // Assign
    free();
    m_line2 = new std::string(line1);
    m_line3 = new std::string(line2);
    m_fileType = TwoLines;
    // Parse
    if (forceParsing)
        parseAll();

    return (m_lastError == NoError);
}
//------------------------------------------------------------------------------

void Node::parseAll()
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
    satelliteNumber();
    satelliteName();
    designator();
    classification();
    ephemerisType();
    elementNumber();
    revolutionNumber();
    preciseEpoch();
}
//------------------------------------------------------------------------------

Node::ErrorCode Node::checkLine(const std::string &str) const
{
    if (str.length() < CHECKSUM_INDEX + 1)
        return TooShortString;

    int expectedChecksum = checksum(str.substr(0, CHECKSUM_INDEX));
    int actualChecksum = atoi(str.substr(CHECKSUM_INDEX, 1).c_str());
    if (expectedChecksum != actualChecksum)
        return ChecksumError;

    return NoError;
}
//------------------------------------------------------------------------------

std::string Node::satelliteNumber() const
{
    if (m_satelliteNumber)
        return *m_satelliteNumber;

    if (m_line2)
    {
        // Try to obtain the satellite number from the second line...
        ErrorCode error = NoError;
        m_satelliteNumber = new std::string(trim(parseString(m_line2, 2, 5, error)));
        if (error != NoError)
        {
            m_lastError = error;
            *m_satelliteNumber = "";
        }

        if (*m_satelliteNumber != "")
            return *m_satelliteNumber;
    }

    if (m_line3)
    {
        if (!m_satelliteNumber)
            m_satelliteNumber = new std::string();

        ErrorCode error = NoError;
        *m_satelliteNumber = trim(parseString(m_line3, 2, 5, error));
        if (error != NoError)
        {
            m_lastError = error;
            *m_satelliteNumber = "";
        }
    }

    return *m_satelliteNumber;
}
//------------------------------------------------------------------------------

void Node::setSatelliteNumber(const std::string& satelliteNumber)
{
    if (m_satelliteNumber)
        *m_satelliteNumber = satelliteNumber;
    else
        m_satelliteNumber = new std::string(satelliteNumber);
}
//------------------------------------------------------------------------------

std::string Node::satelliteName() const
{
    if (!m_satelliteName)
    {
        if (m_line1)
        {
            std::size_t l = m_line1->length();
            if (l > 24)
                l = 24;

            ErrorCode error = NoError;
            m_satelliteName = new std::string(trim(parseString(m_line1, 0, l, error)));
            if (error != NoError)
            {
                m_lastError = error;
                *m_satelliteName = "";
            }
        }
        else
        {
            m_satelliteName = new std::string("");
        }
    }

    return *m_satelliteName;
}
//------------------------------------------------------------------------------

void Node::setSatelliteName(const std::string& satelliteName)
{
    if (m_satelliteName)
        *m_satelliteName = satelliteName;
    else
        m_satelliteName = new std::string(satelliteName);
}
//------------------------------------------------------------------------------

std::string Node::designator() const
{
    if (!m_designator)
    {
        m_designator = new std::string;
        if (m_line2)
        {
            ErrorCode error = NoError;
            *m_designator = trim(parseString(m_line2, 9, 8, error));
            if (error != NoError)
            {
                m_lastError = error;
                *m_designator = "";
            }
        }
    }

    return *m_designator;
}
//------------------------------------------------------------------------------

void Node::setDesignator(const std::string &designator)
{
    if (m_designator)
        *m_designator = designator;
    else
        m_designator = new std::string(designator);
}
//------------------------------------------------------------------------------

double Node::n() const
{
    if (!m_n)
    {
        m_n = new double(0);
        if (m_line3)
        {
            ErrorCode error = NoError;
            *m_n = parseDouble(m_line3, 52, 11, error);
            if (error != NoError)
            {
                m_lastError = error;
                *m_n = 0;
            }
        }
    }

    return *m_n;
}
//------------------------------------------------------------------------------

void Node::set_n(double n)
{
    if (m_n)
        *m_n = n;
    else
        m_n = new double(n);
}
//------------------------------------------------------------------------------

double Node::dn() const
{
    if (!m_dn)
    {
        m_dn = new double(0);
        if (m_line2)
        {
            ErrorCode error = NoError;
            *m_dn = parseDouble(m_line2, 33, 10, error);
            if (error != NoError)
            {
                m_lastError = error;
                *m_dn = 0;
            }
        }
    }

    return *m_dn;
}
//------------------------------------------------------------------------------

void Node::set_dn(double dn)
{
    if (m_dn)
        *m_dn = dn;
    else
        m_dn = new double(dn);
}
//------------------------------------------------------------------------------

double Node::d2n() const
{
    if (!m_d2n)
    {
        m_d2n = new double(0);
        if (m_line2)
        {
            ErrorCode error = NoError;
            *m_d2n = parseDouble(m_line2, 44, 8, error, true);
            if (error != NoError)
            {
                m_lastError = error;
                *m_d2n = 0;
            }
        }
    }

    return *m_d2n;
}
//------------------------------------------------------------------------------

void Node::set_d2n(double d2n)
{
    if (m_d2n)
        *m_d2n = d2n;
    else
        m_d2n = new double(d2n);
}
//------------------------------------------------------------------------------

double Node::i() const
{
    if (!m_i)
    {
        m_i = new double(0);
        if (m_line3)
        {
            ErrorCode error = NoError;
            *m_i = parseDouble(m_line3, 8, 8, error);
            if (error != NoError)
            {
                m_lastError = error;
                *m_i = 0;
            }
        }
    }

    return *m_i;
}
//------------------------------------------------------------------------------

void Node::set_i(double i)
{
    if (m_i)
        *m_i = i;
    else
        m_i = new double(i);
}
//------------------------------------------------------------------------------

double Node::Omega() const
{
    if (!m_Omega)
    {
        m_Omega = new double(0);
        if (m_line3)
        {
            ErrorCode error = NoError;
            *m_Omega = parseDouble(m_line3, 17, 8, error);
            if (error != NoError)
            {
                m_lastError = error;
                *m_Omega = 0;
            }
        }
    }

    return *m_Omega;
}
//------------------------------------------------------------------------------

void Node::set_Omega(double Omega)
{
    if (m_Omega)
        *m_Omega = Omega;
    else
        m_Omega = new double(Omega);
}
//------------------------------------------------------------------------------

double Node::omega() const
{
    if (!m_omega)
    {
        m_omega = new double(0);
        if (m_line3)
        {
            ErrorCode error = NoError;
            *m_omega = parseDouble(m_line3, 34, 8, error);
            if (error != NoError)
            {
                m_lastError = error;
                *m_omega = 0;
            }
        }
    }

    return *m_omega;
}
//------------------------------------------------------------------------------

void Node::set_omega(double omega)
{
    if (m_omega)
        *m_omega = omega;
    else
        m_omega = new double(omega);
}
//------------------------------------------------------------------------------

double Node::M() const
{
    if (!m_M)
    {
        m_M = new double(0);
        if (m_line3)
        {
            ErrorCode error = NoError;
            *m_M = parseDouble(m_line3, 43, 8, error);
            if (error != NoError)
            {
                m_lastError = error;
                *m_M = 0;
            }
        }
    }

    return *m_M;
}
//------------------------------------------------------------------------------

void Node::set_M(double M)
{
    if (m_M)
        *m_M = M;
    else
        m_M = new double(M);
}
//------------------------------------------------------------------------------

double Node::bstar() const
{
    if (!m_bstar)
    {
        m_bstar = new double(0);
        if (m_line2)
        {
            ErrorCode error = NoError;
            *m_bstar = parseDouble(m_line2, 53, 8, error, true);
            if (error != NoError)
            {
                m_lastError = error;
                *m_bstar = 0;
            }
        }
    }

    return *m_bstar;
}
//------------------------------------------------------------------------------

void Node::set_bstar(double bstar)
{
    if (m_bstar)
        *m_bstar = bstar;
    else
        m_bstar = new double(bstar);
}
//------------------------------------------------------------------------------

double Node::e() const
{
    if (!m_e)
    {
        m_e = new double(0);
        if (m_line3)
        {
            ErrorCode error = NoError;
            *m_e = parseDouble(m_line3, 26, 8, error, true);
            if (error != NoError)
            {
                m_lastError = error;
                *m_e = 0;
            }
        }
    }

    return *m_e;
}
//------------------------------------------------------------------------------

void Node::set_e(double e)
{
    if (m_e)
        *m_e = e;
    else
        m_e = new double(e);
}
//------------------------------------------------------------------------------

char Node::classification() const
{
    if (!m_classification)
    {
        m_classification = new char('\0');
        if (m_line2)
        {
            ErrorCode error = NoError;
            *m_classification = parseChar(m_line2, 7, error);
            if (error != NoError)
            {
                m_lastError = error;
                *m_classification = '\0';
            }
        }
    }

    return *m_classification;
}
//------------------------------------------------------------------------------

void Node::setClassification(char classification)
{
    if (m_classification)
        *m_classification = classification;
    else
        m_classification = new char(classification);
}
//------------------------------------------------------------------------------

char Node::ephemerisType() const
{
    if (!m_ephemerisType)
    {
        m_ephemerisType = new char('\0');
        if (m_line2)
        {
            ErrorCode error = NoError;
            *m_ephemerisType = parseChar(m_line2, 62, error);
            if (error != NoError)
            {
                m_lastError = error;
                *m_ephemerisType = '\0';
            }
        }
    }

    return *m_ephemerisType;
}
//------------------------------------------------------------------------------

void Node::setEphemerisType(char ephemerisType)
{
    if (m_ephemerisType)
        *m_ephemerisType = ephemerisType;
    else
        m_ephemerisType = new char(ephemerisType);
}
//------------------------------------------------------------------------------

int Node::elementNumber() const
{
    if (!m_elementNumber)
    {
        m_elementNumber = new int(0);
        if (m_line2)
        {
            ErrorCode error = NoError;
            *m_elementNumber = parseInt(m_line2, 64, 4, error);
            if (error != NoError)
            {
                m_lastError = error;
                *m_elementNumber = 0;
            }
        }
    }

    return *m_elementNumber;
}
//------------------------------------------------------------------------------

void Node::setElementNumber(int elementNumber)
{
    if (m_elementNumber)
        *m_elementNumber = elementNumber;
    else
        m_elementNumber = new int(elementNumber);
}
//------------------------------------------------------------------------------

int Node::revolutionNumber() const
{
    if (!m_revolutionNumber)
    {
        m_revolutionNumber = new int(0);
        if (m_line3)
        {
            ErrorCode error = NoError;
            *m_revolutionNumber = parseInt(m_line3, 63, 5, error);
            if (error != NoError)
            {
                m_lastError = error;
                *m_revolutionNumber = 0;
            }
        }
    }

    return *m_revolutionNumber;
}
//------------------------------------------------------------------------------

void Node::setRevolutionNumber(int revolutionNumber)
{
    if (m_revolutionNumber)
        *m_revolutionNumber = revolutionNumber;
    else
        m_revolutionNumber = new int(revolutionNumber);
}
//------------------------------------------------------------------------------

double Node::preciseEpoch() const
{
    if (!m_date)
    {
        if (m_line2)
        {
            ErrorCode error =NoError;
            std::string date = parseString(m_line2, 18, 14, error);
            if (error != NoError)
            {
                m_lastError = error;
                return 0;
            }

            m_date = new double(string2date(date, error));
            if (error != NoError)
            {
                m_lastError = error;
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

void Node::setPreciseEpoch(double preciseEpoch)
{
    if (m_date)
        *m_date = preciseEpoch;
    else
        m_date = new double(preciseEpoch);
}
//------------------------------------------------------------------------------

std::time_t Node::epoch() const
{
    return static_cast<std::time_t>(preciseEpoch());
}
//------------------------------------------------------------------------------

std::string Node::firstString() const
{
    std::string res = satelliteName();
    while (res.length() < 24)
        res += " ";

    return res;
}
//------------------------------------------------------------------------------

std::string Node::secondString() const
{
    std::string res = "1 ";
    res += string2string(satelliteNumber(), 5);
    const char cl = classification();
    res += (isprint(cl) ? std::string(1, cl) : " ") + " ";
    res += string2string(designator(), 8) + " ";
    res += date2string(preciseEpoch(), 14) + " ";
    res += double2string(dn(), 10, 8, false, false, false) + " ";
    res += double2string(d2n(), 8, 3, true, true, false) + " ";
    res += double2string(bstar(), 8, 3, true, true, false) + " ";
    const char eph = ephemerisType();
    res += (isprint(eph) ? std::string(1, eph) : " ") + " ";
    res += int2string(elementNumber(), 4, false);

    // Checksum
    int sum = checksum(res);
    res += int2string(sum, 1);

    return res;
}
//------------------------------------------------------------------------------

std::string Node::thirdString() const
{
    std::string res = "2 ";
    res += string2string(satelliteNumber(), 5) + " ";
    res += double2string(normalizeAngle(i()), 8, 4, false, false, false) + " ";
    res += double2string(normalizeAngle(Omega()), 8, 4, false, false, false) +
           " ";
    res += double2string(e(), 7, 7, false, true, false) + " ";
    res += double2string(normalizeAngle(omega()), 8, 4, false, false, false) +
           " ";
    res += double2string(normalizeAngle(M()), 8, 4, false, false, false) + " ";
    res += double2string(n(), 11, 8, false, false, false);
    res += int2string(revolutionNumber(), 5, false);

    // Checksum
    int sum = checksum(res);
    res += int2string(sum, 1);

    return res;
}
//------------------------------------------------------------------------------

Node& Node::outputFormat(const FileType format)
{
    m_fileType = format;
    return *this;
}
//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& stream, Node& node)
{
    if (node.m_fileType == ThreeLines)
    {
        // Three lines TLE format
        stream << node.firstString() << std::endl;
    }
    stream << node.secondString() << std::endl;
    stream << node.thirdString() << std::endl;

    return stream;
}
//------------------------------------------------------------------------------

}  // namespace tlelib
