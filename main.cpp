#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>

#include "CommandExec.h"
#include "LogcatParserPre22.h"
#include "LogcatParserPost22.h"
#include "string.h"
#include "CommonDefines.h"
#include "deviceinfo.h"
#include "colors.h"

using namespace std;

void PrintHelp();
void PrintNoAdb();

using namespace std;

DeviceInfo selectedDevice;
string adb = "";

int main(int argc, char* argv[])
{


    /**Check for ADB on the system ****************************************************************
     */
    adb = CommandExec::Execute("which adb");
    if(adb.length() == 0)
        PrintNoAdb();

    if(argc == 1)
        PrintHelp();




    /** Check and get details of the attached devices *********************************************
     */
    vector<string> commandReply;
    vector<string> deviceIdList;
    vector<DeviceInfo> devices;

    CommandExec::Execute(adb + " devices", commandReply);
    deviceIdList = DeviceInformation::ExtractDevices(commandReply);
    CALC_TIME(
    devices = DeviceInformation::GetDeviceInfo(deviceIdList);)


    if(devices.size() > 1)
    {

        unsigned int selected = 0;

        while(selected < 1 || selected > devices.size())
        {
            cout<<"Multiple devices connected\n"<<endl;

            for(unsigned int i=0; i < devices.size(); i++)
            {
                DeviceInfo device = devices[i];
                //printf(ANSI_FORMAT_BOLD"%s %s"ANSI_FORMAT_CLEAR ANSI_TEXT_COLOR_CYAN"(Android %s, API %i)"ANSI_FORMAT_CLEAR"\n", device.brand.c_str(), device.model.c_str(), device.release.c_str(), device.sdk);
                printf(ANSI_TEXT_COLOR_CYAN ANSI_FORMAT_BOLD"\t\t%i. %s %s"ANSI_FORMAT_CLEAR"(Android %s, API %i)\n",(i+1), device.brand.c_str(), device.model.c_str(), device.release.c_str(), device.sdk);
            }

            cout<<"\n\tPlease select device: ";

            scanf("%i", &selected);
        }

        selectedDevice = devices[selected-1];

    }
    else if(devices.size() == 1)
    {
        selectedDevice = devices[0];
    }
    else
    {
        cout <<"No devices connected"<<endl;
        exit(0);
    }


    cout<<selectedDevice.brand<<" "<<selectedDevice.model<<" selected." <<endl;


    if(argc == 1)
    {
        PrintHelp();
    }
    else
    {
        //process "adb shell" commands
        if(strcmp(argv[1], "logcat") != 0)
        {
            cout<<"argc: " << argc<<", argv[1]: "<<argv[1]<<endl;
            if(argc > 1)
            {

                const char** argv2 = new const char*[argc + 3]; //3 for -s, deviceid and termination (char*)0
                argv2[0] = argv[0];
                argv2[1] = "-s";
                argv2[2] = selectedDevice.id.c_str();
                //argv2[3] = "shell";
                argv2[argc + 2] = (char*)0;



                for(int i=1; i<argc; i++)
                {
                    argv2[i+2] = argv[i];
                }



                for(int i=0; i<4; i++)
                    cout<<"argv2["<<i<<"]: "<<argv2[i]<<endl;

                cout<<endl;

                execv(adb.c_str(), (char**)argv2);
                //execl(CommonDefines::ADB.c_str(), "adb", "shell");
            }
        }
    }
    cout<<"unsupported command"<<endl;


    return 0;
}


void PrintHelp()
{
    cout <<"cadb (Custom Android Device Bridge) v1.0" <<endl;
    cout <<"https://www.github.com/ravindu1024/cadb\n" <<endl;
    cout <<"usage: " <<endl;
    cout <<"\tcadb [tool name] [..args]"<<endl;
    cout <<"example:"<<endl;
    cout <<"\tcadb shell"<<endl;
    cout <<"\tcadb shell ps"<<endl;
    cout <<"\tcadb shell getprop ro.build.version"<<endl;

    exit(0);
}

void PrintNoAdb()
{
    cout << "abd executable not found! Command \"which adb\" returned an empty string."<<endl;
    cout<<"Please add your Android sdk to the system PATH and try again" <<endl;

    exit(0);
}

