# QuickTle

**Version 2.0.0**

##Summary

QuickTle library is created to be usefull and fast tool for the following operations with TLE data sets:

* IO-operations with 2- and 3-lines TLE-files
* storing TLE data set
* searching for the nearest data to the given date and time
* converting TLE data to geocentric coordinates

## Samples

In the 'samples' directory you can find several examples,   demonstrating  how  to  use  the  QuickTle library.  You can  see  also the 'samples/Makefile', demonstrating  how  one  can  build  a  project with
 QuickTle library.

## Unit-testing

For unit-testing the  Google C++ Testing Framework (a.k.a  [GoogleTest](http://code.google.com/p/googletest/))  is  used.  So  you  should install this framework to be able to build the unit-testing  program.  Make sure  also, that you defined the 'GTEST_DIR' environment variable in your system. When  GoogleTest is  installed,  built and the environment variable is set, you can  build the  testing program by this command in the QuickTle directory:

> make build-test
 
---

**Copyright &copy; 2011-2015 Sergei Fundaev**
