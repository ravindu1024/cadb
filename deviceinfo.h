#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include "CommonDefines.h"

typedef struct _deviceInfo
{
    std::string id;
    std::string brand;
    std::string model;
    std::string release;
    int sdk;

} DeviceInfo;

class DeviceInformation
{
public:

    static std::vector<std::string> ExtractDevices(std::vector<std::string>& deviceList);

    static std::string GetProperty(std::string deviceId, std::string property);

    static DeviceInfo GetDeviceInfo(std::string deviceId);

    static std::vector<DeviceInfo> GetDeviceInfo(std::vector<std::string>& deviceIds);
};

#endif // DEVICEINFO_H
