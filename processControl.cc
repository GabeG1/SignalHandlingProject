/*                                                                              
 *Filename        processControl.cc                                                       
 *Date            4/23/19                                           
 *Author          Gabriel Goldstein                                             
 *Email           gjg180000@utdallas.edu                                        
 *Course          CS 3377.502 Spring 2019                                       
 *Version         1.0                                                           
 *Copyright 2019, All Rights Reserved                                           
 *                                                                              
 *Description                                                                   
 *      Use inotify to watch the directory and write asny modifications to .versions subdirectory                                                                        
 *      
 */


#include "program5.h"
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sys/inotify.h>
#include <stdio.h>

using namespace std;

void processControl(int pid)
{
  struct stat st;
     signal(SIGHUP, signalHandling);
     signal(SIGINT, signalHandling);
     signal(SIGTERM, signalHandling);

  string subDir = parseResults[WATCHDIR] + "/.versions";
  if(stat(subDir.c_str(), &st) == -1)
    {
      mkdir(subDir.c_str(), S_IRWXU);
    }
  int fd = inotify_init ();
  inotify_add_watch (fd, parseResults[WATCHDIR].c_str(), IN_MODIFY);

  char buffer[1024];
  while(true)
    {
      // if(parseResults[VERBOSE] == "1")
      //	{
	  //	  logFile << "Sleeping... waiting for file to be modified" << flush << endl;
	  //	}
      sleep(2);
       read(fd, buffer, 1024);
      // int count = 0;
      // while(count < len)
      //	{
	  struct inotify_event *event = (struct inotify_event *) &buffer[0];
	  if(event->len && event->name != parseResults[LOGFILE])
	    {
	      FILE* f = popen("date +\"%Y.%m.%d-%T\"", "r");
	      char date[1024];
	      fgets(date, 1024, f); 
	      inotifyMessages(std::string(event->name),std::string(event->name) +"." + std::string(date)); 	
	      string command = "cp " + std::string(event->name) + " .versions/" + std::string(event->name) + "." + date;
	      system(command.c_str());

	    }
	  // count += (sizeof(struct inotify_event) + event->len);	
	  //}

    }
}
