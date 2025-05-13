#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "vec3.h"

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
            auto scatter_direction = rec.normal + random_unit_vector();

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


class metal : public material {
    private:
        color albedo; // Albedo (reflective color) of the material

    public:
        metal(const color& albedo) : albedo(albedo) {}

        bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered)
        const override {
            Vector3D reflected = reflect(r_in.getDirection(), rec.normal);
            scattered = Ray(rec.p, reflected);
            attenuation = albedo;
            return true;
        }
    
};

#endif
