#ifndef SYSTEMCMDCALLER_H
#define SYSTEMCMDCALLER_H
#include <string>
#include <array>
#include <bits/unique_ptr.h>
#include <iostream>

class SystemCmdCaller
{
public:
    SystemCmdCaller();
    virtual void RunCommand(const char* command);
    virtual void StoreOutput(std::string& result);
    virtual void DisplayOutput();
    virtual ~SystemCmdCaller();
    virtual std::string ReturnOutput();
private:
    std::string outputStore;
};

#endif // SYSTEMCMDCALLER_H
