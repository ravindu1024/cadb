#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

#include <string>
#include <vector>

typedef struct _logData
{
    int pid;
    std::string tag;
    std::string line;

    _logData()
        : pid(0),
          tag(""),
          line("")
    {

    }

    _logData(int _pid, std::string _tag, std::string _line)
    {
        pid = _pid;
        tag = _tag;
        line = _line;
    }
} LogData;

typedef struct _deviceInfo
{
    std::string adb;
    std::string device;

    _deviceInfo(std::string _adb)
        :adb(_adb), device("")
    {

    }

} DeviceInfo;

class CommonDefines
{
public:
    static void ExtractDevices(std::vector<std::string>& deviceList)
    {
        std::vector<std::string>::iterator itr = deviceList.begin();
        deviceList.erase(itr);

        for(int i = 0; i<deviceList.size(); i++)
        {
            const char* device = deviceList[i].c_str();

        }
    }

};


#endif // COMMONDEFINES_H
