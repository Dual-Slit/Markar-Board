***************************************************************************************************************************************************
# Markar-Board
It is an OpenCV C++ project 

Project Name : Markar Board
Written By : Ashutosh


This code need Microsoft Visual Stdio for good results

some settings need to be done in Microsoft Visual Stdio
  1.Nevigate Project Properties 
   ==> VC++ Directories --> Include Directories --> add your <opencv\buil\include> path
   ==> VC++ Directories --> Library Directories --> add your <opencv\buil\x64\vc16\lib> path
   ==> linker --> input --> additional dependencies --> <debugger file name>

While running/compilation of code
   ==> Since this code takes input from your webcam, if single webcam is attached then no need to change otherwise chnage web cam ID (line no 13)

This program works fine for Green and Purple Colour, if you need more colour add/remove then in myColors vector(line no 20) add its HSV minimum and maximum values and add corresponding color in myColorValues vector (line no 24)

***************************************************************************************************************************************************
