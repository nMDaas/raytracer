#ifndef __BOX_H__
#define __BOX_H__

class Box {
public:
    Box();
    ~Box();

    // to check for copy constructors
    Box (Box &t);

};

#endif