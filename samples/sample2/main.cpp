/*
  The bellow example demonstrates, how one may use the tle_node object.
*/

#include <iostream>
#include <string>
#include <tlelib/tlelib.h>

int main(int argc, char** argv)
{
    std::string line1 = "ISS                     ";
    std::string line2 = "1 25544U 98067A   98325.70495433 -.00030123  11429-4 -58797-4 0   131";
    std::string line3 = "2 25544  51.5959 160.7754 0074891  99.0987 261.5489 15.92210234   236";

    // create tle_node on basis of TLE lines
    tlelib::tle_node node1(line1, line2, line3);
    tlelib::tle_node node2(line2, line3); // use 2 lines only as usual TLE file

    // Output in default format
    std::cout << "Node #1:" << std::endl << node1;
    std::cout << "Node #2:" << std::endl << node2;
}
