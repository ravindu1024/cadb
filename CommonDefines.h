#ifndef COMMONDEFINES_H
#define COMMONDEFINES_H

#include <string>
#include <vector>
#include <sstream>
#include <istream>
#include <iterator>
#include <time.h>
#include <sys/time.h>

#define CALC_TIME(statement) {\
                                timeval t1, t2;\
                                gettimeofday(&t1, NULL);\
                                statement;\
                                gettimeofday(&t2, NULL);\
                                long seconds  = t2.tv_sec  - t1.tv_sec;\
                                long useconds = t2.tv_usec - t1.tv_usec;\
                                long time = ((seconds) * 1000 + useconds/1000.0) + 0.5;\
                                printf("execution time: %ld ms\n", time);\
                             }

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


class CommonDefines
{
public:
    static std::vector<std::string> split(std::string const &input)
    {
        std::istringstream buffer(input);
        std::vector<std::string> ret;

        std::copy(std::istream_iterator<std::string>(buffer),
                  std::istream_iterator<std::string>(),
                  std::back_inserter(ret));
        return ret;
    }

};


#endif // COMMONDEFINES_H
