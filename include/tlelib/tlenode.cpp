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

#define CHECKSUM_INDEX 68

#include <string>
#include <cstdlib>
#include <ctime>

#include <tlelib/tlenode.h>
#include <tlelib/tlefunc.h>
#include <tlelib/tleexception.h>

using namespace tlelib;

TleNode::TleNode()
{
    init();
}
//------------------------------------------------------------------------------

TleNode::TleNode(const std::string& line1, const std::string& line2, const std::string& line3, bool forceParsing)
{
    init();
    assign(line1, line2, line3, forceParsing);
}
//------------------------------------------------------------------------------

TleNode::TleNode(const std::string& line1, const std::string& line2, bool forceParsing)
{
    init();
    assign(line1, line2, forceParsing);
}
//------------------------------------------------------------------------------

TleNode::~TleNode()
{
    free();
}
//------------------------------------------------------------------------------

void TleNode::init()
{
    m_line1 = m_line2 = m_line3 = m_satName = m_satNumber = m_designator = NULL;
    m_dn = m_d2n = m_Bstar = m_i = m_Omega = m_omega = m_M = m_n = m_e = NULL;
    m_classification = m_ephemerisType = NULL;
    m_elementNumber = m_revolutionNumber = NULL;
    m_date = NULL;
}
//------------------------------------------------------------------------------

void TleNode::free()
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

void TleNode::assign(const std::string& line1, const std::string& line2, const std::string& line3, bool forceParsing)
{
    // Check checksums
    checkLine(line2);
    checkLine(line3);
    // Assign
    free();
    m_line1 = new std::string(line1);
    m_line2 = new std::string(line2);
    m_line3 = new std::string(line3);
    // Parse
    if (forceParsing) parseAll();
}
//------------------------------------------------------------------------------

void TleNode::assign(const std::string& line1, const std::string& line2, bool forceParsing)
{
    // Check checksums
    checkLine(line1);
    checkLine(line2);
    // Assign
    free();
    m_line2 = new std::string(line1);
    m_line3 = new std::string(line2);
    // Parse
    if (forceParsing) parseAll();
}
//------------------------------------------------------------------------------

void TleNode::parseAll()
{
    n(); dn(); d2n(); i(); Omega(); omega(); M(); e(); BSTAR();
    satNumber(); satName(); designator();
    classification(); ephemerisType();
    elementNumber(); revolutionNumber();
    preciseEpoch();
}
//------------------------------------------------------------------------------

void TleNode::checkLine(const std::string &str) const
{
    if (str.length() < CHECKSUM_INDEX + 1)
        throw tle_too_short_string(str);

    int expected_checksum = checksum(str.substr(0, CHECKSUM_INDEX));
    int actual_checksum = atoi(str.substr(CHECKSUM_INDEX, 1).c_str());
    if (expected_checksum != actual_checksum)
        throw tle_checksum_error(str, expected_checksum, actual_checksum);
}
//------------------------------------------------------------------------------

std::string &TleNode::satNumber()
{
    if (!m_satNumber)
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
    return *m_satNumber;
}
//------------------------------------------------------------------------------

std::string &TleNode::satName()
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

std::string &TleNode::designator()
{
    if (!m_designator)
    {
        m_designator = new std::string(trim(parseString(m_line2, 9, 8)));
    }

    return *m_designator;
}
//------------------------------------------------------------------------------

double &TleNode::n()
{
    if (!m_n)
    {
        m_n = new double(parseDouble(m_line3, 52, 11));
    }

    return *m_n;
}
//------------------------------------------------------------------------------

double &TleNode::dn()
{
    if (!m_dn)
    {
        m_dn = new double(parseDouble(m_line2, 33, 10));
    }

    return *m_dn;
}
//------------------------------------------------------------------------------

double &TleNode::d2n()
{
    if (!m_d2n)
    {
        m_d2n = new double(parseDouble(m_line2, 44, 8, true));
    }

    return *m_d2n;
}
//------------------------------------------------------------------------------

double &TleNode::i()
{
    if (!m_i)
    {
        m_i = new double(parseDouble(m_line3, 8, 8));
    }

    return *m_i;
}
//------------------------------------------------------------------------------

double &TleNode::Omega()
{
    if (!m_Omega)
    {
        m_Omega = new double(parseDouble(m_line3, 17, 8));
    }

    return *m_Omega;
}
//------------------------------------------------------------------------------

double &TleNode::omega()
{
    if (!m_omega)
    {
        m_omega = new double(parseDouble(m_line3, 34, 8));
    }

    return *m_omega;
}
//------------------------------------------------------------------------------

double &TleNode::M()
{
    if (!m_M)
    {
        m_M = new double(parseDouble(m_line3, 43, 8));
    }

    return *m_M;
}
//------------------------------------------------------------------------------

double &TleNode::BSTAR()
{
    if (!m_Bstar)
    {
        m_Bstar = new double(parseDouble(m_line2, 53, 8, true));
    }

    return *m_Bstar;
}
//------------------------------------------------------------------------------

double &TleNode::e()
{
    if (!m_e)
    {
        m_e = new double(parseDouble(m_line3, 26, 7, true));
    }

    return *m_e;
}
//------------------------------------------------------------------------------

char &TleNode::classification()
{
    if (!m_classification)
    {
        m_classification = new char(parseChar(m_line2, 7));
    }

    return *m_classification;
}
//------------------------------------------------------------------------------

char &TleNode::ephemerisType()
{
    if (!m_ephemerisType)
    {
        m_ephemerisType = new char(parseChar(m_line2, 62));
    }

    return *m_ephemerisType;
}
//------------------------------------------------------------------------------

int &TleNode::elementNumber()
{
    if (!m_elementNumber)
    {
        m_elementNumber = new int(parseInt(m_line2, 64, 4));
    }

    return *m_elementNumber;
}
//------------------------------------------------------------------------------

int &TleNode::revolutionNumber()
{
    if (!m_revolutionNumber)
    {
        m_revolutionNumber = new int(parseInt(m_line3, 63, 5));
    }

    return *m_revolutionNumber;
}
//------------------------------------------------------------------------------

double &TleNode::preciseEpoch()
{
    if (!m_date)
    {
        std::string date = parseString(m_line2, 18, 14);
        m_date = new double(string2date(date));
    }

    return *m_date;
}
//------------------------------------------------------------------------------

std::time_t TleNode::epoch()
{
    /*if (!m_epoch)
    {
        std::string date = parseString(m_line2, 18, 14);
        m_epoch = new std::time_t(stringToUNIXDate(date));
    }

    return *m_epoch;*/
    return static_cast<std::time_t>(preciseEpoch());
}
//------------------------------------------------------------------------------

std::string TleNode::getFirstString()
{
    std::string res = satName();
    while (res.length() < 24) res += " ";
    return res;
}
//------------------------------------------------------------------------------

std::string TleNode::getSecondString()
{
    std::string res = "1 ";
    res += string2string(satNumber(), 5);
    const char cl = classification();
    res += (isprint(cl) ? std::string(1, cl) : " ") + " ";
    res += string2string(designator(), 8) + " ";
    res += date2string(preciseEpoch(), 14) + " ";
    res += double2string(dn(), 10, 8, false, false, false) + " ";
    res += double2string(d2n(), 8, 3, true, true, false) + " ";
    res += double2string(BSTAR(), 8, 3, true, true, false) + " ";
    const char eph = ephemerisType();
    res += (isprint(eph) ? std::string(1, eph) : " ") + " ";
    res += int2string(elementNumber(), 4, false);

    // Checksum
    int sum = checksum(res);
    res += int2string(sum, 1);

    return res;
}
//------------------------------------------------------------------------------

std::string TleNode::getThirdString()
{
    std::string res = "2 ";
    res += string2string(satNumber(), 5) + " ";
    res += double2string(i(), 8, 4, false, false, false) + " ";
    res += double2string(Omega(), 8, 4, false, false, false) + " ";
    res += double2string(e(), 7, 7, false, true, false) + " ";
    res += double2string(omega(), 8, 4, false, false, false) + " ";
    res += double2string(M(), 8, 4, false, false, false) + " ";
    res += double2string(n(), 11, 8, false, false, false);
    res += int2string(revolutionNumber(), 5, false);

    // Checksum
    int sum = checksum(res);
    res += int2string(sum, 1);

    return res;
}
//------------------------------------------------------------------------------
