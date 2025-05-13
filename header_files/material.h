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
            // Generate a random direction on the hemisphere around the normal
            auto scatter_direction = rec.normal + Vector3D::random_unit_vector();

            if (scatter_direction.near_zero()) {
                // If the scatter direction is near zero, use the normal as the scatter direction
                scatter_direction = rec.normal;
            }

            // Create a new ray with the scatter direction and set the attenuation color
            scattered = Ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

};

#endif
