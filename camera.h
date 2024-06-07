#pragma once

#include "rtw.h"
#include "hittable.h"

class camera
{
public:
    double aspect_ratio = 1.0;
    int image_width = 100;
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
                vec3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                vec3 ray_direction = pixel_center - camera_center;
                ray r(camera_center, ray_direction);
                color px = ray_color(r, world);
                write_color(std::cout, px);
            }
        }
        std::clog << "Done." << std::endl;
    }

private:
    int image_height;
    vec3 camera_center;
    vec3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    void initialize()
    {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

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

    color ray_color(const ray &r, const hittable &world)
    {
        hitrecord record;
        if (world.hit(r, interval(0, infinity), record))
        {
            return 0.5 * (record.normal + color(1, 1, 1));
        }
        vec3 unitdir = unit(r.direction());
        auto a = 0.5f * (unitdir.y + 1.);
        return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5, 0.7, 1.0);
    }
};