#include "file.h"

void	extract_info(t_defib *def)
{
	int i = 0;
	int j = 0;

	while ((def->DEFIB)[i])
	{
		i++;
		j = i + j;
	}
}

int main()
{
	int		N;
	char	LON[51];
	char	LAT[51];
	t_list	*lst = 0;
	t_list	*tmp;
	t_defib	*def;
	
	scanf("%s", LON);
	scanf("%s", LAT);
	scanf("%d", &N);
	fgetc(stdin);
	fprintf(stderr, "%s\n", LON);
	fprintf(stderr, "%s\n", LAT);
	fprintf(stderr, "%d\n", N);
	for (int i = 0; i < N; i++)
	{
		def = malloc(sizeof(t_defib));
		scanf("%[^\n]", def->DEFIB);
		extract_info(def);

		fgetc(stdin);
	}
	printf("answer\n");
	return 0;
}
