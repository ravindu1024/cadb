#include "deviceinfo.h"
#include "CommonDefines.h"
#include "CommandExec.h"
#include <cstdlib>

using namespace std;


std::vector<std::string> DeviceInformation::ExtractDevices(std::vector<std::string>& deviceList)
{
    std::vector<std::string> devices;


    for(unsigned int i = 1; i<deviceList.size(); i++)
    {
        if(deviceList[i].size() > 0)
        {
            devices.push_back(CommonDefines::split(deviceList[i])[0]);
        }
    }

    return devices;
}

string DeviceInformation::GetProperty(string deviceId, string property)
{
    string command = "adb -s " + deviceId + " shell getprop " + property;

    return CommandExec::Execute(command);
}

DeviceInfo DeviceInformation::GetDeviceInfo(string deviceId)
{
    DeviceInfo device;

    device.id = deviceId;

    device.brand = GetProperty(deviceId, "ro.product.manufacturer");
    device.model = GetProperty(deviceId, "ro.product.model");
    device.release = GetProperty(deviceId, "ro.build.version.release");
    device.sdk = atoi(GetProperty(deviceId, "ro.build.version.sdk").c_str());

    device.brand[0] = toupper(device.brand.c_str()[0]);

    return device;
}

vector<DeviceInfo> DeviceInformation::GetDeviceInfo(std::vector<string> &deviceList)
{
    vector<DeviceInfo> devices;

    vector<string>::iterator itr = deviceList.begin();

    for(; itr != deviceList.end(); itr++)
    {

        devices.push_back(GetDeviceInfo(*itr));
    }

    return devices;
}
