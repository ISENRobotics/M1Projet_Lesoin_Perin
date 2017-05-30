# M1Projet_Lesoin_Perin

Author : Steven LESOIN, Alexandre PERIN

M1 PROJECT ISEN BREST 2017 : 

USB Missile Launcher using webcams for tracking a red target 

The system has been developped on virtual machine
The virtual machine used is XUbuntu 14.04 which is available in the source file

Link to the github repository : https://github.com/ISENRobotics/M1Projet_Lesoin_Perin

This is a C++ project

The project is using following librairies : 
-OpenCV
-libusb

They are already installed on the virtual machine

The projet has been developped on Eclipse

You will find the Eclipse's project on the virtual machine in the repository /home/isen/workspace/MissileLauncherFinal

The librairies are already link in the Eclipse's project

we advice you to compile the project with Eclipse cause there is no makefile writted and there is many different file to compile.   

The system is using 4 external devices 

2 webcams , servo-controler(Pololu Micro Maestro 6 channel), USB Missile Launcher

/!\ BE CAREFUL /!\ 

To use the system you have to plug them in and select them in the virtual machine's device list IN A SPECIFIC ORDER !!!!

1- left's webcam
2- right's webcam 
3- USB Missile Launcher
4- Servo controler 

To excecute the project :

- > Open a terminal 
 
- > You have to be super user to excecute the program 

- > Password : isen29 

- > Don't forget to turn ON the Missile Launcher

- > Go to the following repository : /home/isen/workspace/MissileLauncherFinal/Debug 

- > In the repository the name of the excecutable is : ./MissileLauncherFinal

If there is no ./MissileLauncherFinal, it's because the compilation failed 

If you see the error "select timeout" on the terminal, that's means the system didn't manage to connect himself to the webcam
In this case you should unplug and replug all devices (don't forget to keep the order)  

If the excecutable starts but the system doesn't work, you likely missed one of the previous step. 
