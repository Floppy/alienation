#include <stdio.h>
#include <math.h>

int main()
{
	float v1[3], v2[3];
	bool quit = false;
	float x, y, z;
	float length;
	float ans;
	int imp;

	do
	{
		printf ("Enter vector to calculate against:\n");
		printf ("1.....Up\n");
		printf ("2.....Right\n");
		printf ("3.....Ahead\n");
		scanf("%d", &imp);

		if (imp == 1)
		{
			v1[0] = 0.0f;
			v1[1] = 1.0f;
			v1[2] = 0.0f;
		}
		else
		{
			if (imp == 2)
			{
				v1[0] = 1.0f;
				v1[1] = 0.0f;
				v1[2] = 0.0f;
			}
			else
			{
				if (imp == 3)
				{
					v1[0] = 0.0f;
					v1[1] = 0.0f;
					v1[2] = -1.0f;
				}
				else
				{
					quit = true;
				}
			}
		}

		if (! quit)
		{

			printf ("Enter x value to calculate");
			scanf ("%f", &x);

			printf ("Enter y value to calculate");
			scanf ("%f", &y);

			printf ("Enter z value to calculate");
			scanf ("%f", &z);

			length = (float)sqrt(x*x + y*y + z*z);
			v2[0] = x / length;
			v2[1] = y / length;
			v2[2] = z / length;

			ans = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	
			printf ("%.5f", ans);
		}
	}
	while (!quit);
	return 1;
}