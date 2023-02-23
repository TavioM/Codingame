#include "file.h"
#include <math.h>

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
	def->lon = atof(i + def->DEFIB);
	while ((def->DEFIB)[i] != ';')
		i++;
	i++;
	def->lat = atof(i + def->DEFIB);
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

	double user_lon = atof(LON);
	double user_lat = atof(LAT);
//	fprintf(stderr, "user lon: %f\n", user_lon);
//	fprintf(stderr, "user lat: %f\n", user_lat);

	float min_d = 214748;
	for (int i = 0; i < N; i++)
	{
		def = malloc(sizeof(t_defib));
		scanf("%[^\n]", def->DEFIB);
		extract_info(def);

//		double x = ((def->lon - user_lon) * cos((user_lat + def->lat) / 2));
//		double y = (def->lat - user_lat);
//		double d = sqrt((x * x) + (y * y));

		double	dlon = def->lon - user_lon;
		double	dlat = def->lat - user_lat;
		double	a = ((sin(dlat/2)) * (sin(dlat/2))) + cos(user_lat) * cos(def->lat) * ((sin(dlon/2)) * (sin(dlon/2)));
		double	c = 2 * atan2( sqrt(a), sqrt(1-a) );
		double	d = 6371 * c; //(where R is the radius of the Earth) 

		if (d < 1000)
		{
			fprintf(stderr, "Ulon = %f, Ulat = %f, ", user_lon, user_lat);
			fprintf(stderr, "lon = %f, lat = %f, ", def->lon, def->lat);
			fprintf(stderr, "d = %f, min = %f, ", d, min_d);
			fprintf(stderr, "name: %s\n", def->name);
		}
		if (d < min_d)
		{
			min_d = d;
			free(name);
			name = strdup(def->name);
			fprintf(stderr, "new name: %s\n", def->name);
		}
		free(def);

//		fprintf(stderr, "x = %f, y = %f, d = %f, name = %s, min_d = %f\n", x, y, d, def->name, min_d);

		fgetc(stdin);
	}
	printf("%s\n", name);
	return 0;
}
