/*
  The bellow example demonstrates, how one may use the tle_node object.
*/

#include <iostream>
#include <ctime>
#include <tlelib/tlelib.h>

int main(int argc, char** argv)
{
    tlelib::tle_node node;              // create "empty" node

    node.set_sat_name("ISS");           // set satellite name
    node.set_sat_number("25544");       // NORAD number
    node.set_designator("98067A");      // International designator
    node.set_classification('U');       // classification
    node.set_precise_epoch(time(NULL)); // epoch
    node.set_i(51.5959);                // Inclination
    node.set_Omega(167.1152);           // Right Ascension of the Ascending Node
    node.set_e(0.0123861);              // Eccentricity
    node.set_omega(87.8179);            // Argument of Perigee
    node.set_M(273.5890);               // Mean Anomaly
    node.set_n(16.05002967);            // Mean Motion
    node.set_dn(0.00713053);            // First Time Derivative of the Mean Motion
    node.set_d2n(0.000011562);          // Second Time Derivative of Mean Motion 
    node.set_bstar(0.00034316);         // BSTAR drag term
    node.set_ephemeris_type('0');       // Ephemeris type
    node.set_element_number(5);         // Element number
    node.set_revolution_number(4);      // Revolution number at epoch

    // Output
    std::cout << node.sat_name() << " [" << node.sat_number() << " - " << node.designator() << "]" << std::endl;
    std::cout << node;

    // Increase the time and mean motion
    node.set_precise_epoch(node.precise_epoch() + 86400); // one day = 86400 seconds
    node.set_M(node.M() + node.n() * 1 * 360); // mean motion (revs per day) * 1 day * 360 degrees.
                                    // Note, that the values is used "as is": it may exceeds 360 and may be negitive: be accurate
    std::cout << "One day later:" << std::endl;
    std::cout << node;
}
