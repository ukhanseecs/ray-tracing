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
        double fuzz;  // Fuzziness factor for the metal material

    public:
        metal(const color& albedo, double fuzz) 
            : albedo(albedo), fuzz(fuzz < 1 ? fuzz :1) {}

        bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered)
        const override {
            // Reflect the incoming ray direction around the normal
            Vector3D reflected = reflect(r_in.getDirection(), rec.normal);
            // Add fuzziness to the reflected direction
            reflected = unit_vec(reflected) + (fuzz * random_unit_vector());
            // Create a new ray with the reflected direction
            scattered = Ray(rec.p, reflected);
            // Set the attenuation color
            attenuation = albedo;
            // Check if the scattered ray is in the same hemisphere as the normal
            return (dot(scattered.getDirection(), rec.normal) > 0); 
        }
    
};


class dielectric : public material {
    private:
        double refractive_index;
    public:
        dielectric(double refractive_index) : refractive_index(refractive_index) {}

        bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered)
        const override {
            attenuation = color(1.0, 1.0, 1.0);
            // Calculate the refraction ratio based on the front face of the hit record
            double refraction_ratio = rec.front_face ? (1.0 / refractive_index) : refractive_index;

            Vector3D unit_direction = unit_vec(r_in.getDirection());
            double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            Vector3D direction;

            if (cannot_refract) {
                direction = reflect(unit_direction, rec.normal);
            } else {
                // Refract the ray
                direction = refract(unit_direction, rec.normal, refraction_ratio);
            }
            scattered = Ray(rec.p, direction);
            return true;
        }

};

#endif
