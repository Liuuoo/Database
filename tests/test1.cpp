#include<iostream>
#include"../include/interface/parser.h"
#include"../include/interface/command.h"
#include"../include/common/my_time.h"
int main()
{
    while(1)
    {
        std::string sentence;
        std::getline(std::cin,sentence);
        try
        {
            parser p(sentence);
            Command cmd = p.getCmd();
            std::cout << cmd; // 输出命令的详细信息
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}