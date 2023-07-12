#include "Controller.h"
#include <iostream> 

Controller::Controller(Model& m) {
    model = m;
}

Controller::~Controller()
{

}

void Controller::run()
{
    std::cout << "testing controller run method" << std::endl;
}