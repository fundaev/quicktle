# QuickTle

**Version 2.0.0**

## 1 Summary

QuickTle library is created to be useful and fast tool for the following operations with TLE data sets:

* IO-operations with 2- and 3-lines TLE-files
* storing TLE data set
* searching for the nearest data to the given date and time
* converting TLE data to geocentric coordinates


## 2 Installation

To build and install QuickTle [cmake](http://www.cmake.org/) build system is used. Make sure that cmake v2.8 or later is installed create, unpack some temporary directory and type ```make``` and ```make install```:

    tar -xzvf quicktle-2.0.0-src.tar.gz
    cd quicktle-2.0.0
    mkdir build
    cd build
    make
    sudo make install
    

## 3 Quick start

QuickTle provides three classes for operating with TLE data: ```Node```, ```Stream``` and ```DataSet```. All of them are available in the ```quicktle``` namespace.

### 3.1 quicktle::Node

An object of ```quicktle::Node``` type stores the data about satellite position at some time moment. This data is provided by two lines (or three lines if the first one contains the satellite name) of TLE format.

There are two ways to manipulate with data, stored in an object of ```quicktle::Node``` type: to use the getters and setters for each orbit element (such as mean motion, eccentricity, mean anomaly etc.), and to assign the data via TLE strings using the corresponding constructor or ```assign``` method. Have a look at the first two samples in the "samples" directory for more details.

### 3.2 quicktle::Stream

The ```quicktle::Stream``` class is developed to simplify the reading TLE files. It provides the wrapper for ```std::istream``` class. You can find example of how to use it in the third sample in the "samples" directory.

### 3.3 quicktle::DataSet

If it is necessary to store the big volume of data about satellite positions and to search for the position, nearest to the given moment of time, it is convenient to use ```quicktle::DataSet``` class. Have a look at fourth sample in the "samples" directory.


## 4 Unit-testing

For unit-testing the Google C++ Testing Framework (a.k.a  [GoogleTest](http://code.google.com/p/googletest/))  is  used.  So  you  should install this framework to be able to build the unit-testing  program.  Make sure  also, that you defined the 'GTEST_DIR' environment variable in your system.
 
---

*Copyright &copy; 2011-2015 Sergei Fundaev*
