#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <stdio.h>

color ray_color(const ray *r)
{
	return (color){ {0,0,0} };
}

int main(void)
{
	float aspect_ratio = 16.0 / 9.0;
	int image_width = 400;

	int image_height = (int) ((double) image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	float focal_length = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * ((double) image_width / image_height);
	point3 camera_center = (point3){ {0, 0, 0} };

	vec3 viewport_u = (vec3){ viewport_width, 0, 0 };
	vec3 viewport_v = (vec3){ 0, -viewport_height, 0};

	vec3 pixel_delta_u = vec3_div(viewport_u, image_width);
	vec3 pixel_delta_v = vec3_div(viewport_v, image_height);

	point3 viewport_upper_left = vec3_sub(vec3_sub(camera_center, (vec3){0, 0, focal_length}),
										  vec3_add(vec3_div(viewport_u, 2), vec3_div(viewport_v, 2)));
	point3 pixel00_loc = vec3_add(viewport_upper_left, vec3_scale(vec3_add(pixel_delta_u, pixel_delta_v), 0.5));

	printf("P3\n%d %d\n255\n", image_width, image_height);
	
	for (int j = 0; j < image_height; j++)
	{
		fprintf(stderr, "\rLines remaining: %d ", (image_height - j));
		for (int i = 0; i < image_width; i++)
		{
			point3 pixel_center = vec3_add(vec3_add(pixel00_loc, vec3_scale(pixel_delta_u, i)), vec3_scale(pixel_delta_v, j));
			vec3 ray_direction = vec3_sub(pixel_center, camera_center);
			ray r = {camera_center, ray_direction};

			color pixel_color = ray_color(&	r);
			write_color(stdout, pixel_color);
		}
	}
	
	fprintf(stderr, "\nDone!\n");
	return 0;
}