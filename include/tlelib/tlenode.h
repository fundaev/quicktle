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
    \brief File contains the definition of tlelib::tle_node object
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
public:
    //! Code of line parsing error
    enum error_code
    {
        no_error = 0,     //!< There is no error
        too_short_string, //!< String is too short
        checksum_error,   //!< String has invalid checksum
        invalid_format    //!< Invalid format
    };

    tle_node(); //!< Default constructor.
    /*!
        \brief Constructor
        \param line1 - first TLE line (satellite name)
        \param line2 - second TLE line ("1 ...")
        \param line3 - third TLE line ("2 ...")
        \param forceParsing - defines, if the data, specified in the given
                              lines should be immediately parsed.
    */
    tle_node(const std::string &line1, const std::string &line2,
             const std::string &line3, bool forceParsing = false);
    /*!
        \brief Constructor
        \param line1 - second TLE line ("1 ...")
        \param line2 - third TLE line ("2 ...")
        \param forceParsing - defines, if the data, specified in the given
                              lines should be immediately parsed.
    */
    tle_node(const std::string &line1, const std::string &line2,
             bool forceParsing = false);
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
    bool assign(const std::string& line1, const std::string& line2, const std::string& line3, bool forceParsing = false);
    /*!
        \brief Assign the TLE lines to tlelib::tle_node object.
        \param line1 - second TLE line ("1 ...")
        \param line2 - third TLE line ("2 ...")
        \param forceParsing - defines, if the data, specified in the given lines should be immediately parsed.
    */
    bool assign(const std::string& line1, const std::string& line2, bool forceParsing = false);
    //! Get the satellite number (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    std::string sat_number() const;
    //! Set the satellite number (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_sat_number(const std::string &sat_number);
    //! Get the satellite name, specified in the TLE file.
    std::string sat_name() const;
    //! Set the satellite name
    void set_sat_name(const std::string &sat_name);
    //! Get the International Designator (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    std::string designator() const;
    //! Set the International Designator (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_designator(const std::string &designator);
    //! Get the Mean Motion [Revs per day] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    double n() const;
    //! Set the Mean Motion [Revs per day] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_n(double n);
    //! Get the First Time Derivative of the Mean Motion (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    double dn() const;
    //! Set the First Time Derivative of the Mean Motion (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_dn(double dn);
    //! Get the Second Time Derivative of the Mean Motion (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    double d2n() const;
    //! Set the Second Time Derivative of the Mean Motion (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_d2n(double d2n);
    //! Get the Inclination [Degrees] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    double i() const;
    //! Set the Inclination [Degrees] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_i(double i);
    //! Get the Right Ascension of the Ascending Node [Degrees] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    double Omega() const;
    //! Set the Right Ascension of the Ascending Node [Degrees] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_Omega(double Omega);
    //! Get the Argument of Perigee [Degrees] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    double omega() const;
    //! Set the Argument of Perigee [Degrees] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_omega(double omega);
    //! Get the Mean Anomaly [Degrees] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    double M() const;
    //! Set the Mean Anomaly [Degrees] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_M(double M);
    //! Get the BSTAR drag term (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    double bstar() const;
    //! Set the BSTAR drag term (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_bstar(double bstar);
    //! Get the Eccentricity [Degrees] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    double e() const;
    //! Set the Eccentricity [Degrees] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_e(double e);
    //! Get the Classification (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    char classification() const;
    //! Set the Classification (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_classification(char classification);
    //! Get the Ephemeris type (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    char ephemeris_type() const;
    //! Set the Ephemeris type (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_ephemeris_type(char ephemeris_type);
    //! Get the precise epoch - number of seconds from Jan 1, #UNIX_FIRST_YEAR.
    double precise_epoch() const;
    //! Set the precise epoch (including the fractional part of seconds)
    void set_precise_epoch(double precise_epoch);
    //! Get the epoch - number of seconds from Jan 1, #UNIX_FIRST_YEAR.
    std::time_t epoch() const;
    //! Get the Element number (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    int element_number() const;
    //! Set the Element number (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_element_number(int element_number);
    //! Get the Revolution number [Revs] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    int revolution_number() const;
    //! Set the Revolution number [Revs] (\see http://celestrak.com/NORAD/documentation/tle-fmt.asp)
    void set_revolution_number(int revolution_number);
    //! Convert this object to the first string of TLE format.
    std::string first_string() const;
    //! Convert this object to the second string of TLE format.
    std::string second_string() const;
    //! Convert this object to the third string of TLE format.
    std::string third_string() const;
    /*!
        \brief Set output format: 2- or 3-lines
        \param format - output format: 2- or 3-lines
        \return Reference to itself.
    */
    tle_node& output_format(const tle_file_type format);
    /*!
        \brief Output function
        \param stream - Output stream
        \param node - The tle_node object
        \return Output stream
    */
    friend std::ostream& operator<<(std::ostream &stream, tle_node &node);
    //! Swaps the data of two tle_node objects
    void swap(tle_node &node);
    tle_node& operator=(tle_node node);

protected:
    void init(); //!< Initialize members.
    void free(); //!< Delete members.
    void parse_all(); //!< Parse all parameters, presented in *(tle_node::m_line1), *(tle_node::m_line2) and *(tle_node::m_line3)
    /*!
        \brief Check whether the line checksum is valid.
               If the checksum is invalid, the tlelib::tle_checksum_error
               exception is generated.
    */
    error_code check_line(const std::string &str) const;

private:
    mutable std::string *m_line1;
    mutable std::string *m_line2;
    mutable std::string *m_line3;
    mutable std::string *m_satName;
    mutable std::string *m_satNumber;
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
    mutable char *m_ephemeris_type;
    mutable int *m_element_number;
    mutable int *m_revolution_number;
    tle_file_type m_file_type;
    mutable error_code m_last_error;
};

} // namespace

#endif // TLENODE_H
