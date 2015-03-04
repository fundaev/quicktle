/*
  The bellow example demonstrates, how one may use the Node object.
*/

#include <iostream>
#include <ctime>
#include <tlelib.h>

int main(int argc, char** argv)
{
    quicktle::Node node;              // create "empty" node

    node.setSatelliteName("ISS");    // set satellite name
    node.setSatelliteNumber("25544");// NORAD number
    node.setDesignator("98067A");    // International designator
    node.setClassification('U');     // classification
    node.setPreciseEpoch(time(NULL));// epoch
    node.set_i(51.5959);             // Inclination
    node.set_Omega(167.1152);        // Right Ascension of the Ascending Node
    node.set_e(0.0123861);           // Eccentricity
    node.set_omega(87.8179);         // Argument of Perigee
    node.set_M(273.5890);            // Mean Anomaly
    node.set_n(16.05002967);         // Mean Motion
    node.set_dn(0.00713053);         // First Time Derivative of the Mean Motion
    node.set_d2n(0.000011562);       // Second Time Derivative of Mean Motion 
    node.set_bstar(0.00034316);      // BSTAR drag term
    node.setEphemerisType('0');      // Ephemeris type
    node.setElementNumber(5);        // Element number
    node.setRevolutionNumber(4);     // Revolution number at epoch

    // Output
    std::cout << node.satelliteName()
              << " [" << node.satelliteNumber()
              << " - " << node.designator() << "]" << std::endl;
    std::cout << node;

    // Increase the time and mean motion
    node.setPreciseEpoch(node.preciseEpoch() + 86400);// 1 day = 86400 seconds
    // mean motion (revs per day) * 1 day * 360 degrees.
    // Note, that the values is used "as is":
    // it may exceeds 360 and may be negitive: be accurate
    node.set_M(node.M() + node.n() * 1 * 360);
    std::cout << "One day later:" << std::endl;
    std::cout << node;

    return 0;
}
