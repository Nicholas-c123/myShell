#include <stdio.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <algorithm>
#include <myUtils.h>

int main() {
    std::cout << "welcome to Nicholas' shell" << std::endl;
    const char *PS1 = getenv("PS1") ? getenv("PS1") : "Nicholas' shell $ ";
    std::string buffer;
    while (std::cout << PS1, std::getline(std::cin, buffer)) {
        std::istringstream ss{buffer};
        std::vector<const char*> args;    
        std::string token;
        while (ss >> token && !token.empty()){
            args.push_back((new std::string(token))->c_str());
        }
        args.push_back((char*)0);
        
        int continueFlag = 0;
        checkBuildins(continueFlag, args);
        if (continueFlag) continue;

        pid_t pid = fork();
        if (pid < 0)
            perror("error! cannot fork");
        if (pid == 0) { // child process
            // std::cout << args[0] << " " << args[1] << std::endl;
            execvp(args[0], const_cast<char * const *>(&args[0]));
            perror("error! cannot exec");
            exit(EXIT_FAILURE);
        } else {
            pid = wait(nullptr); // parent process
        }
    }
    return 0;
}
