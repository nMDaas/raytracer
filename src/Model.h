#ifndef __MODEL_H__
#define __MODEL_H__
#include <iostream> 

class Model 
{
public:
    Model();
    ~Model();
    Model (Model &t) {
        std::cout << "MODEL COPY CONSTRUCTOR CALLED" << std::endl;
    }
private:
};

#endif