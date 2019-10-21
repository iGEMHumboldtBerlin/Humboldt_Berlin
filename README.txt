README

The openPBR is a low-cost, easy to assemble and reliable option to cultivate phototrophic organisms. We have developed it as an open-source platform to operate as you need it. It comes in several setups, from nine cultivation vessels to three flat panels with a minimum width of 15 mm and up to a volume of 190 ml. It provides users with the ability to measure optical density at wavelengths from 400 nm to 800 nm, online and provides a .csv file output. All parts are openly available and even gas supply is exactly adjustable through a rotameter, depending on the needs of your organism and setup. We want to offer scientists a simple and versatile cultivation platform.

################

Design and development by Paul Herrmann

The openPBR is controlled by one single Arduino script, which enables by varying 9 variables full control of all parameters. 
These variables are for light, pumping time (one for each pump), interval of measurement and wished OD of dilution.
To get the output of the openPBR the free serial log program PuTTY: https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html



User manual:

The current code on _v0.1 is for 3 sensors. 

1. Start the Arduino IDE open the openPBR_control
2. Select the COM of the Arduino
3. Choose your settings:

For the light color and intensity set the value between 0 and 255 in line 91 for the according color.

brightnessWhite = 150;
brightnessRed = 150;
brightnessGreen = 150;
brightnessBlue = 150; 

To adjust the interval of measurement change:

const long interval = 10*60*1000; // 10 minutes x 60 sec * 1000 milli 

To adjust the run time of the pumps set the value in line 100 from 

const int pumpTime = 5000; // time the pump is running

The value for the OD that starts the pumping can be set for every chamber starting at line 383. (example OD 1 [a.u.] = 0.95v on Vout of opt101. Divide 1024 by 5 volt times the Vout value you want to dilute the culture by)
 
4. Upload the code to the Arduino
5. Start PuTTy and Select the COM of the Arduino
6. Choose the output file folder and and give your .csv a name.
7. Start PuTTy logging.
8. Close PuTTy and the values are stored in the .csv file.


How to convert the values into OD, see Calibration openPBR DIY step by step on GitHub.

For help contact: igemberl@hu-berlin.de 

