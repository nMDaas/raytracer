#include "Controller.h"
#include <iostream> 

Controller::Controller() {
   std::cout << "copy constructor called" << std::endl;
}

Controller::~Controller()
{

}

void Controller::run()
{
    std::cout << "testing controller run method" << std::endl;
}