#include <rude/config.h>
#include "program5.h"
#include <fstream>
//delete
#include <iostream>

using namespace rude;

void parseConfigFile(std::string configFilename)
{
  parseResults[LOGFILE] = "cs3376dirmond.log";
  Config config;
  errorMessages = "";
  //Check if config file exists
  if(config.load(configFilename.c_str()))
    {
      //Check to see if parameters section exists 
      if(!config.setSection("Parameters", false))
	  {
	  errorMessages = "Error: No 'Parameters' Section\n";
	  return;      
	  }
	else
	  {
	    config.setSection("Parameters");
	    if(!config.exists("LogFile"))
	      {
		errorMessages += "Error: No 'LogFile' Definition\n";
	      }
	    else
	      {
		parseResults[LOGFILE] = config.getStringValue("LogFile");
	      }
	    //Check to see if verbose variable exists 
	    if(!config.exists("Verbose"))
	      {
		errorMessages += "Error: No 'Verbose' Definition\n";
	      }
	    else
	      {
		parseResults[VERBOSE] = boolToString(config.getBoolValue("Verbose"));

}
	    //Check if password variable exists
	    if(!config.exists("Password"))
              {
		errorMessages += "Error: No 'Password' Definition\n";
              }
            else
              {
                parseResults[PASSWORD] = config.getStringValue("LogFile");
              }
	    //Check if NumVersions variable exists
	    if(!config.exists("NumVersions"))
              {
		errorMessages += "Error: No 'NumVersions' Definition\n";
              }
            else
              {
                parseResults[NUMVERSIONS] = config.getStringValue("NumVersions");
	      } 
	    //Check if WatchDir variable exists
	    if(!config.exists("WatchDir"))
              {
		errorMessages += "Error: No 'WatchDir' Definition\n";
              }
            else
              {
                parseResults[WATCHDIR] = config.getStringValue("WatchDir");
	      } 
	  }
    }
  else
    {
         errorMessages += "Error: No Conf File\n";
        }
  //If logfile changed, open up new one
  if(parseResults[LOGFILE] != curLogFile)
    {
  logFile.open(parseResults[LOGFILE].c_str(), std::ios_base::app);
  //If verbose true, print out date of file opened
  if(parseResults[VERBOSE] == "1")
    {
      FILE* f = popen("date +\"%Y.%m.%d-%T\"", "r");
      char date[1024];
      fgets(date, 1024, f);
      pclose(f);
      logFile << "\n Session starting on: " << date << std::endl << std::flush;
    } 
 curLogFile = parseResults[LOGFILE];   
 } 
logFile << errorMessages << std::flush << std::endl;
}
