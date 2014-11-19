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
    \file tlenode.h
    \brief File contains the definition of tlelib::Node object
           - main object of TLELib library.
*/

#ifndef TLENODE_H
#define TLENODE_H

#include <string>
#include <ctime>
#include <iostream>

namespace tlelib
{

/*!
    \brief TLE file format:
*/
enum FileType
{
    TwoLines,  //!< two-lines format
    ThreeLines //!< three-lines format
};

/*!
    \brief Main object of TLELib library. It represents the data, specified
           in the one measurement in TLE file.
*/
class Node
{
public:
    //! Code of line parsing error
    enum ErrorCode
    {
        NoError = 0,     //!< There is no error
        TooShortString,  //!< String is too short
        ChecksumError,   //!< String has invalid checksum
        InvalidFormat    //!< Invalid format
    };

    Node(); //!< Default constructor.
    /*!
        \brief Constructor
        \param line1 - first TLE line (satellite name)
        \param line2 - second TLE line ("1 ...")
        \param line3 - third TLE line ("2 ...")
        \param forceParsing - defines, if the data, specified in the given
                              lines should be immediately parsed.
    */
    Node(const std::string &line1, const std::string &line2,
         const std::string &line3, bool forceParsing = false);
    /*!
        \brief Constructor
        \param line1 - second TLE line ("1 ...")
        \param line2 - third TLE line ("2 ...")
        \param forceParsing - defines, if the data, specified in the given
                              lines should be immediately parsed.
    */
    Node(const std::string &line1, const std::string &line2,
         bool forceParsing = false);
    //! Copy constructor
    Node(const Node &node);
    //! Destructor.
    virtual ~Node();
    /*!
        \brief Assign the TLE lines to tlelib::Node object.
        \param line1 - first TLE line (satellite name)
        \param line2 - second TLE line ("1 ...")
        \param line3 - third TLE line ("2 ...")
        \param forceParsing - defines, if the data, specified in the given
                              lines should be immediately parsed.
    */
    bool assign(const std::string &line1, const std::string &line2,
                const std::string &line3, bool forceParsing = false);
    /*!
        \brief Assign the TLE lines to tlelib::Node object.
        \param line1 - second TLE line ("1 ...")
        \param line2 - third TLE line ("2 ...")
        \param forceParsing - defines, if the data, specified in the given
                              lines should be immediately parsed.
    */
    bool assign(const std::string &line1, const std::string &line2,
                bool forceParsing = false);
    /*!
        Get the satellite number
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    std::string satelliteNumber() const;
    //! Set the satellite number
    void setSatelliteNumber(const std::string &satelliteNumber);
    //! Get the satellite name, specified in the TLE file.
    std::string satelliteName() const;
    //! Set the satellite name
    void setSatelliteName(const std::string &satelliteName);
    /*!
        Get the International Designator
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    std::string designator() const;
    //! Set the International Designator
    void setDesignator(const std::string &designator);
    /*!
        Get the Mean Motion [Revs per day] 
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    double n() const;
    //! Set the Mean Motion [Revs per day]
    void set_n(double n);
    /*!
        Get the First Time Derivative of the Mean Motion
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    double dn() const;
    //! Set the First Time Derivative of the Mean Motion
    void set_dn(double dn);
    /*!
        Get the Second Time Derivative of the Mean Motion
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    double d2n() const;
    //! Set the Second Time Derivative of the Mean Motion
    void set_d2n(double d2n);
    /*!
        Get the Inclination [Degrees]
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    double i() const;
    //! Set the Inclination [Degrees]
    void set_i(double i);
    /*!
        Get the Right Ascension of the Ascending Node [Degrees]
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    double Omega() const;
    //! Set the Right Ascension of the Ascending Node [Degrees]
    void set_Omega(double Omega);
    /*!
        Get the Argument of Perigee [Degrees]
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    double omega() const;
    //! Set the Argument of Perigee [Degrees]
    void set_omega(double omega);
    /*!
        Get the Mean Anomaly [Degrees]
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    double M() const;
    //! Set the Mean Anomaly [Degrees]
    void set_M(double M);
    /*!
        Get the BSTAR drag term
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    double bstar() const;
    //! Set the BSTAR drag term
    void set_bstar(double bstar);
    /*!
        Get the Eccentricity [Degrees]
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    double e() const;
    //! Set the Eccentricity [Degrees]
    void set_e(double e);
    /*!
        Get the Classification
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    char classification() const;
    //! Set the Classification
    void setClassification(char classification);
    /*!
        Get the Ephemeris type
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    char ephemerisType() const;
    //! Set the Ephemeris type
    void setEphemerisType(char ephemerisType);
    //! Get the precise epoch - number of seconds from Jan 1, #UNIX_FIRST_YEAR
    double preciseEpoch() const;
    //! Set the precise epoch (including the fractional part of seconds)
    void setPreciseEpoch(double preciseEpoch);
    //! Get the epoch - number of seconds from Jan 1, #UNIX_FIRST_YEAR.
    std::time_t epoch() const;
    /*!
        Get the Element number
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    int elementNumber() const;
    //! Set the Element number
    void setElementNumber(int elementNumber);
    /*!
        Get the Revolution number [Revs]
        \see http://celestrak.com/NORAD/documentation/tle-fmt.asp
    */
    int revolutionNumber() const;
    //! Set the Revolution number [Revs]
    void setRevolutionNumber(int revolutionNumber);
    //! Convert this object to the first string of TLE format.
    std::string firstString() const;
    //! Convert this object to the second string of TLE format.
    std::string secondString() const;
    //! Convert this object to the third string of TLE format.
    std::string thirdString() const;
    /*!
        \brief Set output format: 2- or 3-lines
        \param format - output format: 2- or 3-lines
        \return Reference to itself.
    */
    Node& outputFormat(const FileType format);
    /*!
        \brief Output function
        \param stream - Output stream
        \param node - The Node object
        \return Output stream
    */
    friend std::ostream& operator<<(std::ostream &stream, Node &node);
    //! Swaps the data of two Node objects
    void swap(Node &node);
    //! Get the code of last error
    ErrorCode lastError() const
    {
        return m_lastError;
    }

    Node& operator=(Node node);

protected:
    //! Initialize members.
    void init();
    //! Delete members.
    void free();
    /*!
        Parse all parameters, presented in *(Node::m_line1),
        *(Node::m_line2) and *(Node::m_line3)
    */
    void parseAll();
    //! Check whether the line checksum is valid
    ErrorCode checkLine(const std::string &str) const;

private:
    mutable std::string *m_line1;
    mutable std::string *m_line2;
    mutable std::string *m_line3;
    mutable std::string *m_satelliteName;
    mutable std::string *m_satelliteNumber;
    mutable std::string *m_designator;
    mutable double *m_dn;
    mutable double *m_d2n;
    mutable double *m_bstar;
    mutable double *m_i;
    mutable double *m_Omega;
    mutable double *m_omega;
    mutable double *m_M;
    mutable double *m_n;
    mutable double *m_e;
    mutable double *m_date; 
    mutable char *m_classification;
    mutable char *m_ephemerisType;
    mutable int *m_elementNumber;
    mutable int *m_revolutionNumber;
    FileType m_fileType;
    mutable ErrorCode m_lastError;
};

} // namespace

#endif // TLENODE_H
