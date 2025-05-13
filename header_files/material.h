#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
  public:
    virtual ~material() = default;

    virtual bool scatter(
        const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered
    ) const {
        return false;
    }
};

#endif
