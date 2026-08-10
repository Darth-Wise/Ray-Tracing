#include "color.h"
#include "vec3.h"

#include <stdio.h>

int main(void)
{
	int width = 256;
	int height = 256;
	
	printf("P3\n%d %d\n255\n", width, height);
	
	for (int j = 0; j < height; j++)
	{
		fprintf(stderr, "\rLines remaining: %d ", (height - j));
		for (int i = 0; i < width; i++)
		{
			color pixel_color = vec3_init((double) i / (width - 1),
										  (double) j / (height - 1),
										  0.0);
			write_color(stdout, pixel_color);
		}
	}
	
	fprintf(stderr, "\nDone!\n");
	return 0;
}