#pragma once

#include "rtw.h"
#include "hittable.h"

class camera
{
public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;

    void render(const hittable &world)
    {
        initialize();
        // Render
        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++)
        {
            std::clog << "Scanlines remaining: " << image_height - j << std::endl;
            for (int i = 0; i < image_width; i++)
            {
                color px(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++)
                {
                    ray r = get_ray(i, j);
                    px += ray_color(r, max_depth, world);
                }
                write_color(std::cout, pixel_sample_scale * px);
            }
        }
        std::clog << "Done." << std::endl;
    }

private:
    int image_height;
    float pixel_sample_scale;
    vec3 camera_center;
    vec3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    void initialize()
    {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_sample_scale = 1.0 / samples_per_pixel;

        camera_center = vec3(0, 0, 0);

        float focal_length = 1.0f;
        float viewport_height = 2.0f;
        float viewport_width = viewport_height * (float(image_width) / image_height);

        vec3 viewport_u(viewport_width, 0, 0);
        vec3 viewport_v(0, -viewport_height, 0);

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + .5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j) const
    {
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc +
                            ((i + offset.x) * pixel_delta_u) +
                            ((j + offset.y) * pixel_delta_v);
        auto ray_origin = camera_center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const
    {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_float() - 0.5, random_float() - 0.5, 0);
    }

    color ray_color(const ray &r, int depth, const hittable &world)
    {
        if (depth <= 0)
            return color(0, 0, 0);
        hitrecord record;
        if (world.hit(r, interval(0.001, infinity), record))
        {

            // vec3 direction = record.normal + random_unit_vector();
            vec3 direction = record.normal + random_on_hemisphere(record.normal);
            return 0.5f * ray_color(ray(record.position, direction), depth - 1, world);
            // return 0.5 * (record.normal + color(1, 1, 1));
        }
        vec3 unitdir = unit(r.direction());
        auto a = 0.5f * (unitdir.y + 1.);
        return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5, 0.7, 1.0);
    }
};