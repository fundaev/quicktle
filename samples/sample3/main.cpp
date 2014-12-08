/*
  The bellow example demonstrates, how top read
  the TLE files by Stream object.
  We will read two files:
      * mir.tle      - 2-lines format file
      * stations.tle - 3-lines format
  and output the first several nodes in console.
*/

#include <iostream>
#include <fstream>
#include <tlelib.h>

using namespace std;

int main(int argc, char** argv)
{
    // === READ mir.tle FILE ===

    // First of all, we should create the file stream
    // to read the file: ifstream or fstream
    fstream f("mir.tle");

    // Create the Stream object on basis of existing inout stream.
    // Generally speaking, we can use any object of istream class.
    tlelib::Stream tle(f, tlelib::TwoLines);
    while (tle) // it is more accurate, than 'while (f)'
    {
        tlelib::Node node;
        tle >> node;
        cout << node;
    }
    f.close();


    std::cout << "----------------------8<----------"
                 "-----------8<----------------------" << std::endl;

    // === READ stations.tle FILE ===
    f.open("stations.tle");
    tlelib::Stream tle1(f, tlelib::ThreeLines);
    while (tle1)
    {
        tlelib::Node node;
        tle1 >> node;
        cout << node;
    }
    f.close();

    return 0;
}
