#ifndef LOGCATPARSER_H
#define LOGCATPARSER_H

#include <string>
#include <vector>
#include "CommonDefines.h"


class LogcatParser
{

private:

    virtual bool ParseLine(std::string strLine, LogData& logData) = 0;


public:
    LogcatParser()
    {

    }

    bool Parse(std::string strLine, LogData& logData)
    {
        return ParseLine(strLine, logData);
    }

};

#endif // LOGCATPARSER_H
