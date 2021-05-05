/*                                                                              
 *Filename        program5.cc                                                       
 *Date            4/23/19                                                 
 *Author          Gabriel Goldstein                                             
 *Email           gjg180000@utdallas.edu                                        
 *Course          CS 3377.502 Spring 2019                                       
 *Version         1.0                                                           
 *Copyright 2019, All Rights Reserved                                           
 *                                                                              
 *Description                                                                   
 *                                                                              
 *     Parse files needed to determine if running in daemon mode and creata child process if needed 
 */

#include "program5.h"
#include <fstream>
#include <cctype>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <csignal>
#include <stdlib.h> 

using namespace std;


map<argsEnum, string> parseResults;
ofstream pidFile;
string errorMessages;
ofstream logFile;
string curLogFile;
string curPassword;
string curWatchDir;
int main(int argc, char* argv[])
{
  //cout statements explain what's occurring
  cout << "Parsing Command Line" << endl;
  cmdParser(argc, argv);
  cout << "Done" << endl;
  cout << "Parsing config File " << endl;
  ifstream configFile(parseResults[CONFIGFILE].c_str());
  parseConfigFile(parseResults[CONFIGFILE].c_str()); 
  curPassword = parseResults[PASSWORD];
  curWatchDir = parseResults[WATCHDIR];
  //Switch from couts to logfile 
 logFile  << "Config File has been successfully parsed." << endl << flush;
 
 //Call loggingfunctions to log to file about what has been parsed
parseMessages();
//Check if running in daemon mode  
if(parseResults[DAEMON] == "1"){
    logFile << "Creating Child Process" << endl << flush;
    //Creating child process using fork
pid_t pid = fork();

//If child process is running
if(pid == 0)
   {
     struct stat st;
     //See if another process is running. If so, shut down
     if(stat("cs3376dirmond.pid", &st) == 0)
       {
	 logFile << "Daemon already running. Shutting down process " + to_string(getpid()) + "\n" << endl<< flush;
	 exit(-1);
       }
     //Write pid to pid file
     pidFile.open("cs3376dirmond.pid");
     pidFile << getpid()  << "\n";
     pidFile.close();
     processControl(getpid());
   }
     }
//Running parent process
  else
    {
      logFile << "Running parent Process " << endl << flush;
      processControl(getpid());
    }
  configFile.close();
  return 0;
}
