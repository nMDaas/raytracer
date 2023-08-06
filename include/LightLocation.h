#ifndef ___LIGHTLOCATION_H___
#define ___LIGHTLOCATION_H___

class LightLocation {
    public: 
    int position,ambient,diffuse,specular;

    LightLocation() {
        position = ambient = diffuse = specular = -1;
    }
};

#endif