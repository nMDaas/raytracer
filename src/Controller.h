#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include "model.h"

class Controller
{
public:
    Controller(Model& m);
    ~Controller();

    /*
        to check for copy constructors
    */
    Controller (Controller &t) {
        std::cout << "CONTROLLER COPY CONSTRUCTOR CALLED" << std::endl;
    }

    void run();

private:
    Model model;
};

#endif