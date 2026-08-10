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
			double r = (double) j / (height - 1);
			double g = 1.0;
			double b = 1.0;
			
			int ir = (int) (255.999 * r);
			int ig = (int) (255.999 * g);
			int ib = (int) (255.999 * b);
			
			printf("%d %d %d\n", ir, ig, ib);
		}
	}
	
	fprintf(stderr, "\nDone!\n");
}