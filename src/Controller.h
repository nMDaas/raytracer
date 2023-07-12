#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>

class Controller
{
public:
    Controller();
    ~Controller();
    Controller (Controller &t) {
        std::cout << "CONTROLLER COPY CONSTRUCTOR CALLED" << std::endl;
    }
    void run();
private:
};

#endif