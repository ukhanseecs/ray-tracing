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


class lambertian : public material {
    private:
        color albedo; // Albedo (diffuse color) of the material
    public:
        lambertian(const color& albedo) : albedo(albedo) {}

        // Scatter function for Lambertian material
        bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered)
        const override {
            auto scatter_direction = rec.normal + Vector3D::random_unit_vector();
            scattered = Ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

};

#endif
