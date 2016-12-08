#ifndef LOGCATPARSERPRE22_H
#define LOGCATPARSERPRE22_H

#include "Logcatparser.h"

using namespace std;

class LogcatParserPre22 : public LogcatParser
{
public:
    LogcatParserPre22()
        :LogcatParser()
    {
    }

    bool ParseLine(std::string strLine, LogData& logData)
    {
        cout << "pre 22" << endl;
        return false;

    }
};

#endif // LOGCATPARSERPRE22_H
