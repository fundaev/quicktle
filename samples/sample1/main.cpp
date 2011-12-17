/*
  The bellow example demonstrates, how one may use the tle_node object.
*/

#include <iostream>
#include <ctime>
#include <tlelib/tlelib.h>

int main(int argc, char** argv)
{
    tlelib::tle_node node;              // create "empty" node

    node.sat_name() = "ISS";            // set satellite name
    node.sat_number() = "25544";        // NORAD number
    node.designator() = "98067A";       // International designator
    node.classification() = 'U';        // classification
    node.precise_epoch() = time(NULL);  // epoch
    node.i() = 51.5959;                 // Inclination
    node.Omega() =  167.1152;           // Right Ascension of the Ascending Node
    node.e() = 0.0123861;               // Eccentricity
    node.omega() = 87.8179;             // Argument of Perigee
    node.M() = 273.5890;                // Mean Anomaly
    node.n() = 16.05002967;             // Mean Motion
    node.dn() = 0.00713053;             // First Time Derivative of the Mean Motion
    node.d2n() = 0.000011562;           // Second Time Derivative of Mean Motion 
    node.BSTAR() = 0.00034316;          // BSTAR drag term
    node.ephemeris_type() = '0';        // Ephemeris type
    node.element_number() = 5;          // Element number
    node.revolution_number() = 4;       // Revolution number at epoch

    // Output
    std::cout << node.sat_name() << " [" << node.sat_number() << " - " << node.designator() << "]" << std::endl;
    std::cout << node;

    // Increase the time and mean motion
    node.precise_epoch() += 86400; // one day = 86400 seconds
    node.M() += node.n() * 1 * 360; // mean motion (revs per day) * 1 day * 360 degrees.
                                    // Note, that the values is used "as is": it may exceeds 360 and may be negitive: be accurate
    std::cout << "One day later:" << std::endl;
    std::cout << node;
}
