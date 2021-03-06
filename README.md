# PackagED

This repository holds the documentation and code for the assignment in the Course COP290 (Design Practices). The aim is to develop a software package for Engineering Drawing.

## Aim

The package is supposed to have the following functionalities:
   1. We should be able to interactively input or read from a file either i) an isometric drawing and a 3D object model or ii) projections on to any cross section.
   2. Given the 3D model description we should be able to generate projections on to any cross section or cutting plane.
   3. Given two or more projections we should be able to interactively recover the 3D description and produce an isometric drawing from any view direction. 

## Structure

The package structure for the software package is as follows:  
PackagED  
  |  
  |-> bin  
  |-> build  
  |-> doc  
  |-> include  
  |-> lib  
  |-> src  
  |-> test  


Following is a description of the above-mentioned directories:
   1. **bin** - All the object files, obtained after build shall be kept in this folder.
   2. **build** - All executables are supposed to be kept in this folder.
   3. **doc** - All doxygen generated html pages and other documentations relating to the project are supposed to be kept in this folder. To view the doxygen generated document without cloning the repository, see this link  
   http://htmlpreview.github.io/?https://github.com/DivyanshuSaxena/PackagED/blob/master/doc/html/index.html or  
   http://www.cse.iitd.ac.in/~cs1160315/PackageED/ (preferably chose above link, this link is unlikely to updated whereas above link fetches the data in realtime from the repo).
   4. **include** - All header files to be included in the project are kept in this folder.
   5. **lib** - This folder contains all external libraries required for the software.
   6. **src** - This folder is supposed to contain all source files (.cpp) written in C++ are to be kept here.
   7. **test** - This folder shall be host to all test files written for debugging and testing the software package .   

## Dependencies

The project makes use of the GTKmm libraries for C++ and OpenScad for stl file generation and rendering.
Hence these packages are needed to be installed before running the software package.
As of now the software is only tested on Ubuntu.
Use the following command:
```
sudo apt-get install libgtkmm-3.0-dev openscad 
```
The above command installs the requisite packages. Now the software package can be built and used.

## Usage

Enter the project directory and run the following command
```
make
```
Then cd into the build folder and run the following
```
./main
```
If you want to run the software with input files, when prompted chose the text file(some test files are in test folder).

## Documentation

The documentation for the current software package is available in the form of webpages. The index.html in doc/html lists the main page. Thereafter, the pages are linked together.
## Screenshots

When the gui opens window like this would appear  
![alt](http://www.cse.iitd.ac.in/~cs1160315/PackageED/images/1.png)  

If the user clicks on Project 3D Object on a Plane and say the user choses the input file PackageED/test/pyramidoverpyramid3dto2d.txt a window showing the 3d representation of the selected file like below would appear  
![alt](http://www.cse.iitd.ac.in/~cs1160315/PackageED/images/5.png)  

If the window is closed the projection like below would appear in the gui  
![alt](http://www.cse.iitd.ac.in/~cs1160315/PackageED/images/6.png)  

Else if the user clicks on Construct Wireframe Orthographic Views and say the user choses the input file PackageED/test/cutcube2dto3d.txt a window showing the 3d object made from the orthographic projections of the selected input file like below would appear  
![alt](http://www.cse.iitd.ac.in/~cs1160315/PackageED/images/2.png)  

If the window is closed the object like below would appear in the gui  
![alt](http://www.cse.iitd.ac.in/~cs1160315/PackageED/images/4.png)  
