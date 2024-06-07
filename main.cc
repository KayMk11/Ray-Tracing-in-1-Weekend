#include "rtw.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

int main()
{
    // World
    hittable_list world;
    world.add(make_shared<sphere>(vec3(0, 0, -1), .5));
    world.add(make_shared<sphere>(vec3(0, -100.5f, -1), 100));

    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.render(world);
}