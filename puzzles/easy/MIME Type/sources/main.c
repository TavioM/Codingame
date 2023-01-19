#include "file.h"

void	copy_type(char EXT[], char MT[], char *EXTcpy, char *MTcpy)
{
	for (int i = 0; i < 11; i++)
	{
		EXTcpy[i] = EXT[i];
		if (EXT[i] == 0)
			break;
	}
	for (int i = 0; i < 51; i++)
	{
		MTcpy[i] = MT[i];
		if (MT[i] == 0)
			break;
	}
}

t_list	*add_type(t_list *types, char EXT[], char MT[])
{
	t_type	*t;

	t = malloc(sizeof(t_type));
	t->EXT = malloc(sizeof(char) * 11);
	t->MT = malloc(sizeof(char) * 51);
	copy_type(EXT, MT, t->EXT, t->MT);
	if (!types)
		types = ft_lstnew(t);
	else
		types = ft_lstadd_back(types, ft_lstnew(t));
	return (types);
}

char	*extract_type(char str[])
{
	int	i = 0;

	while (str[i] && str[i] != '.')
		i++;
	if (!str[i])
		return (0);
	i++;
	return (strdup(str + i));
}

void	search_type(t_list *type, char str[])
{
	char	*ext;

	ext = extract_type(str);
	fprintf(stderr, "type = %s\n", ext);
	while (type)
	{
		if (strcmp((t_type *)(type->data)->EXT, ext) == 0)
			printf("%s\n", ((t_type *)type->data)->MT);
		type = type->next;
	}
}

int main()
{
	int N, Q;
	t_list	*types = 0;

	scanf("%d", &N);
	scanf("%d", &Q);
	for (int i = 0; i < N; i++) {
		char EXT[11];
		char MT[51];
		scanf("%s%s", EXT, MT); fgetc(stdin);
		types = add_type(types, EXT, MT);
		fprintf(stderr, "EXT = %s\n", ((t_type *)ft_lstlast(types)->data)->EXT);
	}
	for (int i = 0; i < Q; i++) {
		char FNAME[257];
		scanf("%[^\n]", FNAME); fgetc(stdin);
		search_type(types, FNAME);
	}

	printf("UNKNOWN\n");
	return 0;
}
