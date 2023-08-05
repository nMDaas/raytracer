#ifndef ___LIGHTLOCATION_H___
#define ___LIGHTLOCATION_H___

class LightLocation {
    public: 
    int position,ambient,diffuse;

    LightLocation() {
        position = ambient = diffuse = -1;
    }
};

#endif