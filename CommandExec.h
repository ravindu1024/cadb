#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <string.h>

class CommandExec
{

    public:

        static bool Execute(std::string command, std::vector<std::string>& output)
        {
            FILE* fp = popen(command.c_str(), "r");
            if(fp != NULL)
            {
                char line[10000] = "";

                while(fgets(line, sizeof(line), fp))
                {
                    if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
                    if(line[strlen(line)-1] == '\r') line[strlen(line)-1] = '\0';

                    output.push_back(std::string(line));
                }

                fclose(fp);
                return true;
            }

            return false;
        }

        static std::string Execute(std::string command)
        {
            FILE* fp = popen(command.c_str(), "r");
            if(fp != NULL)
            {
                char line[10000] = "";

                char* ch = fgets(line, sizeof(line), fp);

                if(ch != NULL)
                {
                    if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
                    if(line[strlen(line)-1] == '\r') line[strlen(line)-1] = '\0';
                }

                fclose(fp);

                return std::string(line);
            }

            return "";
        }
};



