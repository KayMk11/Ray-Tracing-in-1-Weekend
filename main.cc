#include "rtw.h"

#include "hittable.h"
#include "material.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

int main()
{
    // World
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(.5, .5, .5));
    world.add(make_shared<sphere>(vec3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_mat = random_float();
            vec3 center(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());
            if ((center - vec3(4, 0.2, 0)).length() > 0.9)
            {
                shared_ptr<material> sphere_material;
                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo = random_vec3() * random_vec3();
                    sphere_material = make_shared<lambertian>(albedo);
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo = random_vec3(0.5, 1);
                    auto fuzz = random_float(0, .5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                }
                else
                {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                }
                world.add(make_shared<sphere>(center, .2, sphere_material));
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(vec3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(.4, .2, .1));
    world.add(make_shared<sphere>(vec3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(.7, .6, .5), 0.0);
    world.add(make_shared<sphere>(vec3(4, 1, 0), 1.0, material3));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1280;
    cam.samples_per_pixel = 500;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = vec3(-13, 2, 3);
    cam.lookat = vec3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);

    cam.defocus_angle = .6;
    cam.focus_dist = 10.0;

    cam.render(world);
}