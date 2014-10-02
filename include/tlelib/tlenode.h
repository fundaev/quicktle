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
    \file tlenode.h
    \brief File contains the definition of tlelib::tle_node object
           - main object of TLELib library.
*/

#ifndef TLENODE_H
#define TLENODE_H

#include <string>
#include <ctime>
#include <iostream>

#include <tlelib/tlefunc.h>

namespace tlelib
{

/*!
    \brief TLE file format:
*/
enum tle_file_type
{
    two_lines,  //!< two-lines format
    three_lines //!< three-lines format
};

/*!
    \brief Main object of TLELib library. It represents the data, specified
           in the one measurement in TLE file.
*/
class tle_node
{
    std::string *m_line1, *m_line2, *m_line3;
    std::string *m_satName, *m_satNumber, *m_designator;
    double *m_dn, *m_d2n, *m_Bstar, *m_i, *m_Omega, *m_omega, *m_M, *m_n, *m_e, *m_date; 
    char *m_classification, *m_ephemerisType;
    int *m_elementNumber, *m_revolutionNumber;
    tle_file_type m_file_type;

protected:
    void init(); //!< Initialize members.
    void free(); //!< Delete members.
    void parse_all(); //!< Parse all parameters, presented in *(tle_node::m_line1), *(tle_node::m_line2) and *(tle_node::m_line3)
    /*!
        \brief Check whether the line checksum is valid.
               If the checksum is invalid, the tlelib::tle_checksum_error
               exception is generated.
    */
    void check_line(const std::string &str) const;

public:
    tle_node(); //!< Default constructor.
    /*!
        \brief Constructor
        \param line1 - first TLE line (satellite name)
        \param line2 - second TLE line ("1 ...")
        \param line3 - third TLE line ("2 ...")
        \param forceParsing - defines, if the data, specified in the given lines should be immediately parsed.
    */
    tle_node(const std::string& line1, const std::string& line2, const std::string& line3, bool forceParsing = false);

    /*!
        \brief Constructor
        \param line1 - second TLE line ("1 ...")
        \param line2 - third TLE line ("2 ...")
        \param forceParsing - defines, if the data, specified in the given lines should be immediately parsed.
    */
    tle_node(const std::string& line1, const std::string& line2, bool forceParsing = false);

    //! Copy constructor
    tle_node(const tle_node &node);

    virtual ~tle_node(); //!< Destructor.

    /*!
        \brief Assign the TLE lines to tlelib::tle_node object.
        \param line1 - first TLE line (satellite name)
        \param line2 - second TLE line ("1 ...")
        \param line3 - third TLE line ("2 ...")
        \param forceParsing - defines, if the data, specified in the given lines should be immediately parsed.
    */
    void assign(const std::string& line1, const std::string& line2, const std::string& line3, bool forceParsing = false);

    /*!
        \brief Assign the TLE lines to tlelib::tle_node object.
        \param line1 - second TLE line ("1 ...")
        \param line2 - third TLE line ("2 ...")
        \param forceParsing - defines, if the data, specified in the given lines should be immediately parsed.
    */
    void assign(const std::string& line1, const std::string& line2, bool forceParsing = false);

    /*!
        \brief Get/set the satellite number (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the std::string object, representing the satellite number.
    */
    std::string &sat_number();

    /*!
        \brief Get/set the satellite name, specified in the TLE file.
        \return The reference to the std::string object, representing the satellite name.
    */
    std::string &sat_name();

    /*!
        \brief Get/set the International Designator (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the std::string object, representing the international designator.
    */
    std::string &designator();

    /*!
        \brief Get/set the Mean Motion [Revs per day] (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the value of double type, representing the Mean Motion.
    */
    double &n();

    /*!
        \brief Get/set the First Time Derivative of the Mean Motion (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the value of double type, representing the First Time Derivative of the Mean Motion.
    */
    double &dn();

    /*!
        \brief Get/set the Second Time Derivative of the Mean Motion (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the value of double type, representing the Second Time Derivative of the Mean Motion.
    */
    double &d2n();

    /*!
        \brief Get/set the Inclination [Degrees] (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the value of double type, representing the Inclination.
    */
    double &i();

    /*!
        \brief Get/set the Right Ascension of the Ascending Node [Degrees] (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the value of double type, representing the Right Ascension of the Ascending Node.
    */
    double &Omega();

    /*!
        \brief Get/set the Argument of Perigee [Degrees] (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the value of double type, representing the Argument of Perigee.
    */
    double &omega();

    /*!
        \brief Get/set the Mean Anomaly [Degrees] (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the value of double type, representing the Mean Anomaly.
    */
    double &M();

    /*!
        \brief Get/set the BSTAR drag term (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the value of double type, representing the BSTAR drag term.
    */
    double &BSTAR();

    /*!
        \brief Get/set the Eccentricity [Degrees] (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the value of double type, representing the Eccentricity.
    */
    double &e();

    /*!
        \brief Get/set the Classification (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the value of 'char' type, representing the Classification.
    */
    char &classification();

    /*!
        \brief Get/set the Ephemeris type (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the value of 'char' type, representing the Ephemeris type.
    */
    char &ephemeris_type();

    /*!
        \brief Get/set the precise epoch (including the fractional part of seconds)
        \return The reference to the value of 'double' type, representing the epoch - 
                number of seconds from Jan 1, #UNIX_FIRST_YEAR.
    */
    double &precise_epoch();

    /*!
        \brief Get/set the epoch
        \return The reference to the value of 'std::time_t' type, representing the epoch -
                number of seconds from Jan 1, #UNIX_FIRST_YEAR.
    */
    std::time_t epoch();

    /*!
        \brief Get/set the Element number (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the value of 'int' type, representing the Element number.
    */
    int &element_number();

    /*!
        \brief Get/set the Revolution number [Revs] (see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
        \return The reference to the value of 'int' type, representing the Revolution number.
    */
    int &revolution_number();

    /*!
        \brief Convert this object to the first string of TLE format.
        \return First TLE string.
    */
    std::string first_string();

    /*!
        \brief Convert this object to the second string of TLE format.
        \return Second TLE string.
    */
    std::string second_string();

    /*!
        \brief Convert this object to the third string of TLE format.
        \return Third TLE string.
    */
    std::string third_string();

    /*!
        \brief Set output format: 2- or 3-lines
        \param format - output format: 2- or 3-lines
        \return Reference to itself.
    */
    tle_node &output_format(const tle_file_type format);

    /*!
        \brief Output function
        \param stream - Output stream
        \param node - The tle_node object
        \return Output stream
    */
    friend std::ostream &operator<<(std::ostream &stream, tle_node &node);
};

} // namespace

#endif // TLENODE_H
