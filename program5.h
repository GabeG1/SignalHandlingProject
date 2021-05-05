/*                                                                              
 *Filename        program5.h                                                       
 *Date            4/23/19                                                  
 *Author          Gabriel Goldstein                                             
 *Email           gjg180000@utdallas.edu                                        
 *Course          CS 3377.502 Spring 2019                                       
 *Version         1.0                                                           
 *Copyright 2019, All Rights Reserved                                           
 *                                                                              
 *Description                                                                   
 *         Header file that contains basic variable declarations and function prototypes to be used later on                                                                     
 *      
 */


#ifndef PROGRAM5_H
#define PROGRAM5_H

#include <map>
#include <string>
#include <fstream>

//Create an enum that has the names of the flags as the variables              
enum argsEnum{DAEMON, CONFIGFILE, VERBOSE, LOGFILE, PASSWORD, NUMVERSIONS, WATCHDIR};
void parseConfigFile(std::string);
void cmdParser(int, char**);
void signalHandling(int);
void parseMessages();
void inotifyMessages(std::string, std::string);
void signalMessage(int);
void processControl(int);
extern std::string curLogFile;
extern std::string curPassword;
extern std::string curWatchDir;
std::string boolToString(bool);
extern std::map<argsEnum, std::string> parseResults;  
extern std::string errorMessages;
extern std::ofstream pidFile;
extern std::ofstream logFile;

#endif /* PROGRAM5_H */
