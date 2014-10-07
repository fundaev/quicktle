/*
  The bellow example demonstrates, how one can initialize the tle_node
  objects on basis of the TLE strings and how one can print them.
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
    // Note: the tle_node object does not parse these
    // lines when it is initialized (but checks the checksum).
    // To enforce the parsing use the last parameter as true, i.e.:
    //     tlelib::tle_node node1(line1, line2, line3, true);
    //     tlelib::tle_node node2(line2, line3, true);
    tlelib::tle_node node1(line1, line2, line3);
    tlelib::tle_node node2(line2, line3); // use 2 lines only as usual TLE file

    // Output in default format
    std::cout << "Node #1:" << std::endl << node1;
    std::cout << "Node #2:" << std::endl << node2;

    std::cout << "-------------------" << std::endl << std::endl;

    // Set 3-lines output frmat for both objects:
    node1.output_format(tlelib::three_lines);
    node2.output_format(tlelib::three_lines);
    std::cout << "Node #1:" << std::endl << node1;
    std::cout << "Node #2:" << std::endl << node2;

    std::cout << "-------------------" << std::endl << std::endl;

    // Set the 2-lines output format.
    // The output_format method returns the reference to the same object.
    // As a result one may set the format and output the node in the same line,
    // as it is presented bellow.
    std::cout << "Node #1:" << std::endl << node1.output_format(tlelib::two_lines);
    std::cout << "Node #2:" << std::endl << node2.output_format(tlelib::two_lines);

    std::cout << "-------------------" << std::endl << std::endl;

    // How to add the first line into the node2 object?
    // There are 2 ways:
    // 1. Set the sat_name property:
    node2.set_sat_name("ISS (manually set)");
    // Check how it's printed now:
    std::cout << node2.output_format(tlelib::three_lines);

    // 2. Alternatively one may re-assign the lines by 'assign' method:
    node2.assign(line1, line2, line3);
    std::cout << node2; // now we set 3 lines, and the output format is automatically set to 'tlelib::three_lines'
}
