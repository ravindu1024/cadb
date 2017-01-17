#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>

#include "CommandExec.h"
#include "string.h"
#include "CommonDefines.h"
#include "deviceinfo.h"
#include "colors.h"


using namespace std;


void                CheckAdbInPath();
vector<DeviceInfo>  GetAttachedDevices();
void                PrintDeviceMenu(vector<DeviceInfo>& devices);
void                ExecuteAdbCommand(int argc, char *argv[]);
void                PrintHelp();
void                PrintNoAdb();

DeviceInfo          selectedDevice;
string              adb = "";


int main(int argc, char* argv[])
{

    if(argc == 1)
        PrintHelp();


    CheckAdbInPath();


    vector<DeviceInfo> devices = GetAttachedDevices();


    if(devices.size() > 1)
    {

        unsigned int selected = 0;

        while(selected < 1 || selected > devices.size())
        {
            PrintDeviceMenu(devices);

            int n = scanf("%i", &selected);

            if(n > 1)
                selected = 0;
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


    cout<<"\n"<<selectedDevice.model<<" selected.\n" <<endl;


    ExecuteAdbCommand(argc, argv);


    return 0;
}


void CheckAdbInPath()
{
    adb = CommandExec::Execute("which adb");

    if(adb.length() == 0)
        PrintNoAdb();
}

vector<DeviceInfo> GetAttachedDevices()
{
    vector<string> commandReply;
    vector<string> deviceIdList;

    CommandExec::Execute(adb + " devices", commandReply);
    deviceIdList = DeviceInformation::ExtractDevices(commandReply);

    return DeviceInformation::GetDeviceInfo(deviceIdList);
}

void PrintDeviceMenu(vector<DeviceInfo>& devices)
{
    cout<<"Multiple devices connected\n"<<endl;

    for(unsigned int i=0; i < devices.size(); i++)
    {
        DeviceInfo device = devices[i];
        printf(ANSI_TEXT_COLOR_CYAN ANSI_FORMAT_BOLD"\t\t%i. %s %s"ANSI_FORMAT_CLEAR"(Android %s, API %i)\n",(i+1), device.brand.c_str(), device.model.c_str(), device.release.c_str(), device.sdk);
    }

    cout<<"\n\t\tPlease select device: ";
}

void ExecuteAdbCommand(int argc, char* argv[])
{
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


        execv(adb.c_str(), (char**)argv2);
    }

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
    cout << "adb executable not found in $PATH. Command \"which adb\" returned an empty string."<<endl;
    cout<<"Please add your Android sdk to the system PATH and try again" <<endl;

    exit(0);
}

