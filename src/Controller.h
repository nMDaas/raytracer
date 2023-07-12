#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>

class Controller
{
public:
    Controller();
    ~Controller();

    /*
        to check for copy constructors
    */
    Controller (Controller &t) {
        std::cout << "CONTROLLER COPY CONSTRUCTOR CALLED" << std::endl;
    }

    void run();
private:
};

#endif