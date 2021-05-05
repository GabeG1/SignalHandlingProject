/*                                                                              
 *Filename        parseCommandLine.cc                                                       
 *Date            4/23/19                                          
 *Author          Gabriel Goldstein                                             
 *Email           gjg180000@utdallas.edu                                        
 *Course          CS 3377.502 Spring 2019                                       
 *Version         1.0                                                           
 *Copyright 2019, All Rights Reserved                                           
 *                                                                              
 *Description                                                                   
 *          Parse command line to determine if/what flags are present                                                                    
 *      
 */



#include <tclap/CmdLine.h>
#include <string>
#include "program5.h"

using namespace std;

void cmdParser(int argc, char* argv[])
{
  try{
    TCLAP::CmdLine cmd(" cs3376dirmond Directory Monitor Daemon", ' ',"1.0");
    //Create daemon switcharg
    TCLAP::SwitchArg daemonArg("d","daemon", "Run in daemon mode (forks to run as a daemon). ", cmd, false);
    //Create optional configfilearg
    TCLAP::UnlabeledValueArg<string> configFileArg("configFile", "The name of the configuration file.", false, "cs3376dirmond.conf", "config filename", false);
    cmd.add(configFileArg);
    cmd.parse(argc, argv);
    parseResults[DAEMON] = boolToString(daemonArg.getValue());
    parseResults[CONFIGFILE] = configFileArg.getValue();
  }

    catch(TCLAP::ArgException &e)
      {
	cerr << "error: " << e.error() << "for arg" << e.argId() << endl;
      }
}

string boolToString(bool b)
{

  //If the boolean is true, return 1                                            
  if(b == true)
    {
      return "1";
    }
  //If the boolean is false, return 0                                           
  else
    {
      return "0";
    }

}
