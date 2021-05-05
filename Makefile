 #                                                                              
 #Filename        Makefile                                                       
 #Date            4/23/19                                                        
 #Author          Gabriel Goldstein                                             
 #Email           gjg180000@utdallas.edu                                        
 #Course          CS 3377.502 Spring 2019                                       
 #Version         1.0                                                           
 #Copyright 2019, All Rights Reserved                                           
 #                                                                              
 #Description                                                                   
 #        Compile the various source files to make an executable                                                                      
 #   



OBJS = program5.o signalHandling.o loggingFunctions.o processControl.o
SRCS = program5.cc signalHandling.cc loggingFunctions.cc processControl.cc

.PHONY: all clean

all: program5

clean: 
	rm *~ program5 $(OBJS) parseCommandLine.o parseConfigFile.o \#*

#Create executable using the libraries and object files
program5: $(OBJS) parseCommandLine.o parseConfigFile.o
	g++ -o program5 $(OBJS) parseConfigFile.o -L/home/011/g/gj/gjg180000/RudeConfig/lib/rude -lrudeconfig parseCommandLine.o 

#Compile source file
$(OBJS): $(SRCS) program5.h
	g++ -Wall -Werror -std=c++11 -c $(SRCS)
#Direct preprocessor to rudeconfig file
parseConfigFile.o: parseConfigFile.cc program5.h
	g++ -c -Wall -Werror parseConfigFile.cc -I /home/011/g/gj/gjg180000/RudeConfig/include

#Direct preprocessor to include files
parseCommandLine.o: parseCommandLine.cc program5.h
	g++ -Wall -Werror -I ~/include/include -c parseCommandLine.cc
