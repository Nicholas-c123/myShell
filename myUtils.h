#ifndef MYUTILS_H
#define MYUTILS_H

#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>
void checkBuildins(int& continueFlag, std::vector<const char*> args){
    if (!args[0]){
        continueFlag = 1;
        return;
    }
    if (std::string(args[0]) == "exit"){
        exit(0);
        std::cout << "Bye Bye!";
    }
    else if (std::string(args[0]) == "cd"){ // change directory built-in command
        chdir(args[1]); //third param non-zero means overwrite 
        continueFlag = 1;
    }
}


#endif // !MYUTILS_H
