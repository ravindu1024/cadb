#ifndef LOGCATPARSERPOST22_H
#define LOGCATPARSERPOST22_H

#include "Logcatparser.h"

using namespace std;

class LogcatParserPost22 : public LogcatParser
{
public:
    LogcatParserPost22()
        :LogcatParser()
    {

    }

    bool ParseLine(std::string strLine, LogData& logData)
    {
        cout << "post 22" << endl;
    }
};

#endif // LOGCATPARSERPOST22_H
