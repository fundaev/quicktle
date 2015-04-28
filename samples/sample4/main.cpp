/*
  Example bellow demonstrates, how top read
  the TLE files by Stream object.
  We will read two files:
      * mir.tle      - 2-lines format file
      * stations.tle - 3-lines format
  and output the first several nodes in console.
*/

#include <ctime>
#include <iostream>
#include <fstream>
#include <quicktle/stream.h>
#include <quicktle/dataset.h>

using namespace std;

int main(int argc, char** argv)
{
    fstream f("mir.tle");
    quicktle::Stream tle(f, quicktle::TwoLines);
    quicktle::DataSet nodes;
    while (tle)
        tle >> nodes;
    f.close();

    const quicktle::Node &node = nodes.nearestNode(std::time(0));
    std::cout << node;

    return 0;
}
