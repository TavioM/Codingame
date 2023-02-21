#include "file.h"

void	extract_info(t_defib *def)
{
	int i = 0;
	int j = 0;

	while ((def->DEFIB)[i] != ';')
		i++;
	i++;
	while ((def->DEFIB)[i] != ';')
	{
		def->name[j] = def->DEFIB[i];
		i++;
		j++;
	}
	i++;
	def->name[j] = 0;
	while ((def->DEFIB)[i] != ';')
		i++;
	i++;
	while ((def->DEFIB)[i] != ';')
		i++;
	i++;
	for (int k = 0; def->DEFIB[i + k]; k++)
	{
		if (def->DEFIB[i + k] == ',')
			def->DEFIB[i + k] = '.';
	}
	def->lon = atof(i + (def->DEFIB));
	while ((def->DEFIB)[i] != ';')
		i++;
	i++;
	def->lat = atof(i + (def->DEFIB));
//	fprintf(stderr, "name: %s\n", def->name);
//	fprintf(stderr, "lon: %f\n", def->lon);
//	fprintf(stderr, "lat: %f\n", def->lat);
//	fprintf(stderr, "def: %s\n", def->DEFIB);
}

int main()
{
	int		N;
	char	LON[51];
	char	LAT[51];
	char	*name = 0;
	t_defib	*def;

	scanf("%s", LON);
	scanf("%s", LAT);
	scanf("%d", &N);
	fgetc(stdin);

	float user_lat = atof(LAT);
	float user_lon = atof(LON);
//	fprintf(stderr, "user lon: %f\n", user_lon);
//	fprintf(stderr, "user lat: %f\n", user_lat);

	float min_d = 2147483647;
	for (int i = 0; i < N; i++)
	{
		def = malloc(sizeof(t_defib));
		scanf("%[^\n]", def->DEFIB);
		extract_info(def);

		float x = (def->lon - user_lon) * cos((user_lat + def->lat) / 2);
		float y = def->lat - user_lat;

		float d = sqrt(pow(x, 2) + pow(y, 2)) * 6371;

		if (d < min_d)
		{
			min_d = d;
			free(name);
			name = strdup(def->name);
		}

//		fprintf(stderr, "x = %f, y = %f, d = %f, name = %s, min_d = %f\n", x, y, d, def->name, min_d);

		fgetc(stdin);
	}
	printf("%s\n", name);
	return 0;
}
