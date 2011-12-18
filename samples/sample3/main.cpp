/*
  The bellow example demonstrates, how top read
  the TLE files by tle_stream object.
  We will read two files:
      * mir.tle      - 2-lines format file
      * stations.tle - 3-lines format
  and output the first several nodes in console.
*/

#include <iostream>
#include <fstream>
#include <tlelib/tlelib.h>

using namespace std;

int main(int argc, char** argv)
{
    // === READ mir.tle FILE ===

    // First of all, we should create the file stream
    // to read the file: ifstream or fstream
    fstream f("sample3/mir.tle");

    // Create the tle_stream object on basis of existing inout stream.
    // Generally speaking, we can use any object of istream class.
    tlelib::tle_stream tle(f, tlelib::two_lines);
    while (tle) // it is more accurate, than 'while (f)'
    {
        tlelib::tle_node node;
        tle >> node;
        cout << node;
    }
    f.close();


    std::cout << "----------------------8<---------------------8<----------------------" << std::endl;

    // === READ stations.tle FILE ===
    f.open("sample3/stations.tle");
    tlelib::tle_stream tle1(f, tlelib::three_lines);
    while (tle1)
    {
        tlelib::tle_node node;
        tle1 >> node;
        cout << node;
    }
    f.close();
}
