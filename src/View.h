#ifndef __VIEW_H__
#define __VIEW_H__

#include <iostream>

class View
{
    
public:
    View();
    ~View();

    /*
        to check for copy constructors
    */
    View (View &t) {
        std::cout << "VIEW COPY CONSTRUCTOR CALLED" << std::endl;
    }

private:
};

#endif