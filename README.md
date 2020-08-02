# rarbg_captcha_reader
Automatize captcha reading for the best known torrent site RarBG :)

#This repository is contains edge detection for rarbg captcha character.(written in c++)
#Chrome extension sources for captcha reading.(javascript) 
#Spring boot application sources for getting captcha as png format.
#And little implementation for binding c++ and java native interface.
#preview video is here too, to see how it works!

all codes could be in javascript language but it is a experimental project for hobby :)





# png library must be installed for cpp include
sudo apt-get install libpng-dev
# specify where library is // "pwd" command return location of terminal opened
export LD_LIBRARY_PATH=`pwd` # or can be specified in command
# creating '.h' file to implement for jni
javac -h . Hello.java # after that command Hello.h file is created, than this file must be imlemented in c/c++ file
#creating native c/c++ (shared) library for java file // must be specified path of jni.h of java include // this command below will create libhello.so library to load in java file
g++ -shared -o libhello.so hello.cpp -fPIC -I/usr/lib/java/jdk-12.0.2/include -I/usr/lib/java/jdk-12.0.2/include/linux -lpng
# run java program with specified library in jni // -Djava.library.path=`pwd` specifies to libary location that created  
java -Djava.library.path=`pwd` Hello

##All codes could be written in javascript but it is made for experimental hobby :) 
