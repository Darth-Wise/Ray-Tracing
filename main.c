#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <math.h>
#include <stdio.h>

double hit_sphere(const point3 *center, double radius, const ray *r)
{
	vec3 oc = vec3_sub(*center, r->orig);
	double a = vec3_length_squared(r->dir);
	double h = dot(r->dir, oc);
	double c = vec3_length_squared(OC) - radius * radius;
	double discriminant = h*h - a*c;
	
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return ((h - sqrt(discriminant)) / a);
	}
}

color ray_color(const ray *r)
{
	double t = hit_sphere(&(point3){ {0, 0, -1} }, 0.5, r);
	if (t > 0.0)
	{
		vec3 N = vec3_unit(vec3_sub(ray_at(r, t), (vec3) { {0, 0, -1} }));
		return vec3_scale((color){ {vec3_x(N) + 1, vec3_y(N) + 1, vec3_z(N) + 1} }, 0.5);
	}

	vec3 unit_direction = vec3_unit(r->dir);
	double a = 0.5 * (vec3_y(unit_direction) + 1.0);

	color white = vec3_init(1.0, 1.0, 1.0);
	color blue = vec3_init(0.5, 0.7, 1.0);

	vec3 term1 = vec3_scale(white, (1.0 - a));
	vec3 term2 = vec3_scale(blue, a);

	return vec3_add(term1, term2);
} 

int main(void)
{
	float aspect_ratio = 16.0 / 9.0;
	int image_width = 2560;

	int image_height = (int) ((double) image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	float focal_length = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * ((double) image_width / image_height);
	point3 camera_center = (point3){ {0, 0, 0} };

	vec3 viewport_u = (vec3){ {viewport_width, 0, 0} };
	vec3 viewport_v = (vec3){ {0, -viewport_height, 0} };

	vec3 pixel_delta_u = vec3_div(viewport_u, image_width);
	vec3 pixel_delta_v = vec3_div(viewport_v, image_height);

	point3 viewport_upper_left = vec3_sub(vec3_sub(camera_center, (vec3){ {0, 0, focal_length} }),
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