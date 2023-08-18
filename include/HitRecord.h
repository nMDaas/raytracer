#ifndef HITRECORD_H
#define HITRECORD_H

#include "glm/glm.hpp"
#include "Material.h"

// all vectors/positions are normalized and in the view coordinate system
typedef struct HitRecord {
    float t;
    glm::vec4 intersection_position; // in view coordinate system
    glm::vec4 intersection_normal; // in view coordinate system
    util::Material object_mat;
} HitRecord;

#endif