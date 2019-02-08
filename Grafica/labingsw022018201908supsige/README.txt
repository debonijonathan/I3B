CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Troubleshooting
 * FAQ
 * Maintainers

INTRODUCTION
------------

NuGet is the package manager for .NET. The NuGet client tools provide the ability to produce and consume packages. 
The NuGet Gallery is the central package repository used by all package authors and consumers.
This document will show information on how to perform the tests in Windows and Linux

 * For a full description of nuGet:
   https://www.nuget.org/

REQUIREMENTS
------------

This module requires the following modules:

 * Visual Studio 2017 Enterprise(https://visualstudio.microsoft.com/it/vs/enterprise/)

 OR

 * Linux Command Line

INSTALLATION
------------
 
 * If doesn't work in windows, restore the nuget packages by going with the right button on the solution and click on 
   restore nuget packages

CONFIGURATION
-------------
 
 * To set the correct architecture go to 
   Test -> Test Settings -> Default Processor Architecture -> x64


TROUBLESHOOTING
---------------

 * If the test does not display, check the following:

   - Delete the folder "package" in the main directory of the projects, Restore the nuget packages 
     and set UnitTesting as a startup project

FAQ
---

Q: How to display the test status in Windows?

A: You need to go in Visual Studio to Test --> Window --> Explore Tests --> Run All


Q: How to display the test status in Linux?

A: You need to write in command line in the folder of UnitTesting --> ctest -v
 

Q: The test always fail?

A: You need to clean the solution, recompile solution and Run All

MAINTAINERS
-----------

Current maintainers:

 * Riccardo Biella 
 * Jonathan De Boni 
 * Cristian Spozio  


This project has been commissioned by:
 * SUPSI
   The University of Applied Sciences and Arts of Southern Switzerland 
   is one of the Universities of Applied Sciences of the Swiss Confederation.
   Visit http://www.supsi.ch/ for more information.

