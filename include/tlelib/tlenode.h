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

#ifndef TLENODE_H
#define TLENODE_H

#include <string>
#include <ctime>

#include <tlelib/tlefunc.h>

namespace tlelib
{

class TleNode
{
    std::string *m_line1, *m_line2, *m_line3;
    std::string *m_satName, *m_satNumber, *m_designator;
    double *m_dn, *m_d2n, *m_Bstar, *m_i, *m_Omega, *m_omega, *m_M, *m_n, *m_e, *m_date; 
    char *m_classification, *m_ephemerisType;
    int *m_elementNumber, *m_revolutionNumber;

protected:
    void init();
    void free();
    void parseAll();
    void checkLine(const std::string &str) const;

public:
    TleNode();
    TleNode(const std::string& line1, const std::string& line2, const std::string& line3, bool forceParsing = false);
    TleNode(const std::string& line1, const std::string& line2, bool forceParsing = false);
    virtual ~TleNode();
    void assign(const std::string& line1, const std::string& line2, const std::string& line3, bool forceParsing = false);
    void assign(const std::string& line1, const std::string& line2, bool forceParsing = false);
    std::string &satNumber();
    std::string &satName();
    std::string &designator();
    double &n();
    double &dn();
    double &d2n();
    double &i();
    double &Omega();
    double &omega();
    double &M();
    double &BSTAR();
    double &e();
    char &classification();
    char &ephemerisType();
    double &preciseEpoch();
    std::time_t epoch();
    int &elementNumber();
    int &revolutionNumber();
    std::string getFirstString();
    std::string getSecondString();
    std::string getThirdString();
};

} // namespace

#endif // TLENODE_H
