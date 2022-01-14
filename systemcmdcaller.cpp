#include "systemcmdcaller.h"

//special thanks to guide I followed:
// https://techfortalk.co.uk/2020/12/23/how-to-invoke-linux-command-in-c-program-and-gather-data/

SystemCmdCaller::SystemCmdCaller()
{

}

void SystemCmdCaller::RunCommand(const char * command)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
    if(!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    StoreOutput(result);

}

void SystemCmdCaller::StoreOutput(std::string& result)
{
    outputStore = result;
}

void SystemCmdCaller::DisplayOutput()
{
    std::cout << outputStore << std::endl;
}

std::string SystemCmdCaller::ReturnOutput()
{
    std::cout << outputStore << std::endl;
    return outputStore;
}

SystemCmdCaller::~SystemCmdCaller()
{

}
