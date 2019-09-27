#include "main.hpp"
#include <stdio.h>
#include <thread>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Scheduler *test = new Scheduler();

void createProcess(string instructions, int number)
{
    Process *p = new Process();
    istringstream f(instructions);
    for (string line; getline(f, line);)
    {
        if (line.find("Name:") != string::npos)
        {
            string name = line.substr(line.find(":") + 1);
            cout << "Name: " + name << endl;
            p->setName(name);
        }
        else if (line.find("Total runtime:") != string::npos)
        {
            string runtime = line.substr(line.find(":") + 1);
            cout << "Runtime: " + runtime << endl;
            p->setCycles(stoi(runtime));
        }
        else if (line.find("Memory:") != string::npos)
        {
            string memory = line.substr(line.find(":") + 1);
            cout << "Memory: " + memory << endl;
            p->setMemoryReq(stoi(memory));
        }
        else
        {
            if (line.length > 0)
            {
              if (line == "EXE")
              {
                  break;
              }
                p->addInstruction(line);
            }
        }
    }
    // for (int i = 0; i < number; i++)
    // {
    //    test->addNewProcess(p);
    // }
    
}

void loadFileThread()
{
    string buf;
    string programFileBuf;
    printf("Please enter a Program file name\n");
    getline(cin, buf);
    ifstream programFile(buf);
    if (!programFile)
    {
        printf("file error\n");
        return;
    }
    bool isValid = false;
    for (string line; getline(programFile, line);)
    {
        programFileBuf += line + "\n";
        if (line == "EXE")
        {
            isValid = true;
        }
    }

    if (isValid)
    {
        printf("Please enter the number of processes you would like to create from this program: ");
        getline(cin, buf);
        createProcess(programFileBuf, stoi(buf));
    }
    else
    {
        printf("Invalid Program file\n");
        return;
    }

    programFile.close();
}

char *parseCommand(char *cmd)
{
    char *out = (char *)malloc(sizeof(char) * 256);
    memset(out, 0, 256);
    if (!strcmp("load\n", cmd))
    {
        thread thread(loadFileThread);
        thread.join();
        return out;
    }
    else if (!strcmp("clear\n", cmd))
    {
        system("cls");
        return out;
    }
    strcpy(out, "Command Not Found \"Help\" to see all commands\n\0");
    return out;
}

int main(int argc, char **argv)
{
    char buf[256];
    while (1)
    {
        printf("OS Simulator: ");
        fgets(buf, 256, stdin);
        printf("%s", parseCommand(buf));
    }
}