#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>

#include "CommandExec.h"
#include "LogcatParserPre22.h"
#include "LogcatParserPost22.h"
#include "string.h"
#include "CommonDefines.h"

using namespace std;

void PrintHelp();
void PrintNoAdb();

using namespace std;



int main(int argc, char* argv[])
{

    string adb = CommandExec::Execute("which adb");
    if(adb.length() == 0)
        PrintNoAdb();

    //cout<<"device adb path: "<<CommonDefines::ADB <<endl;


    DeviceInfo deviceInfo(adb);


    vector<string> devices;
    CommandExec::Execute(deviceInfo.adb + " devices", devices);
    CommonDefines::ExtractDevices(devices);

    for(int i=0; i<devices.size(); i++)
        cout<<"device: "<<devices[i]<<endl;




    if(argc == 1)
    {
        PrintHelp();
    }
    else
    {
        //process "adb shell" commands
        if(strcmp(argv[1], "shell") == 0)
        {
            if(argc > 1)
            {
                int ret = execv(deviceInfo.adb.c_str(), argv);
                //execl(CommonDefines::ADB.c_str(), "adb", "shell");
                if(ret < 0)
                    cout <<"errno: "<<errno<<endl;
            }
        }
    }
    cout<<"argc: " << argc<<", argv[1]: "<<argv[1]<<endl;


    return 0;
}


void PrintHelp()
{
    cout <<"cadb (Custom Android Device Bridge) v1.0" <<endl;
    cout <<"https://www.github.com/ravindu1024/cadb\n" <<endl;
    cout <<"usage: " <<endl;
    cout <<"\tcadb [tool name] [..args]"<<endl;

    exit(0);
}

void PrintNoAdb()
{
    cout << "abd executable not found! Command \"which adb\" returned an empty string."<<endl;
    cout<<"Please add your Android sdk to the system PATH and try again" <<endl;

    exit(0);
}

