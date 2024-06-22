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
    auto material_ground = make_shared<lambertian>(color(.8, .8, .0));
    auto material_center = make_shared<lambertian>(color(.1, .2, .5));
    auto material_left = make_shared<dielectric>(1.5);
    auto material_bubble = make_shared<dielectric>(1. / 1.5);
    auto material_right = make_shared<metal>(color(.8, .6, .2), 1.0);
    world.add(make_shared<sphere>(vec3(0, -100.5f, -1), 100, material_ground));
    world.add(make_shared<sphere>(vec3(0, 0, -1.2), .5, material_center));
    world.add(make_shared<sphere>(vec3(-1.0, 0, -1.0), .5, material_left));
    world.add(make_shared<sphere>(vec3(-1.0, 0, -1.0), .4, material_bubble));
    world.add(make_shared<sphere>(vec3(1.0, 0, -1.0), .5, material_right));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.render(world);
}