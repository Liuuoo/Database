#pragma once
#include <vector>
#include "../interface/command.h"

class Node 
{
private:
    Command command;
    std::vector<Node*> forward; // forward指针数组，指向不同层级的下一个节点
public:
    Node(const Command& cmd) : command(cmd) {}
};