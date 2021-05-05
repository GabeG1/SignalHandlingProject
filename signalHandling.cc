/*                                                                              
 *Filename        signalHandling.cc                                                       
 *Date            4/23/19                                           
 *Author          Gabriel Goldstein                                             
 *Email           gjg180000@utdallas.edu                                        
 *Course          CS 3377.502 Spring 2019                                       
 *Version         1.0                                                           
 *Copyright 2019, All Rights Reserved                                           
 *                                                                              
 *Description                                                                   
 *        Handle signals that the process receives                                                                      
 *      
 */


#include "program5.h"
#include <csignal>
#include <stdlib.h>
#include <iostream>

using namespace std;
void signalHandling(int num)
{
  //SIGINT and SIGTERM signals: exit process
  if(num == 2 || num == 15)
    {
      remove("cs3376dirmond.pid");
      signalMessage(num);     
 logFile.close();      
      exit(num);
    }
  //SIGHUP signal: reparse config file
  if(num == 1)
    {
      errorMessages = "";
      logFile << "Reparsing Config File" << endl << flush;
      parseConfigFile(parseResults[CONFIGFILE].c_str());
      if(curPassword != parseResults[PASSWORD])
	{
	  logFile << "WARNING: Cannot Change password." << endl << flush;
	}
      if(curWatchDir !=parseResults[WATCHDIR])
	{
          logFile<< "WARNING: Cannot Change WatchDir."<< endl<< flush;
        }
      parseMessages();
          }
}
