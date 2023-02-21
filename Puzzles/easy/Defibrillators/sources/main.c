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
	fprintf(stderr, "name: %s\n", def->name);
	fprintf(stderr, "lon: %f\n", def->lon);
	fprintf(stderr, "lat: %f\n", def->lat);
//	fprintf(stderr, "def: %s\n", def->DEFIB);
}

int main()
{
	int		N;
	char	LON[51];
	char	LAT[51];
	t_list	*lst = 0;
	t_list	*tmp;
	t_defib	*def;

	(void)lst;
	(void)tmp;
	scanf("%s", LON);
	scanf("%s", LAT);
	scanf("%d", &N);
	fgetc(stdin);
	fprintf(stderr, "user lon: %s\n", LON);
	fprintf(stderr, "user lat: %s\n", LAT);
	for (int i = 0; i < N; i++)
	{
		def = malloc(sizeof(t_defib));
		scanf("%[^\n]", def->DEFIB);
		extract_info(def);

		fgetc(stdin);
	}
	printf("answer test\n");
	return 0;
}
