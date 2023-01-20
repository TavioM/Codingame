#include "file.h"

void	copy_type(char EXT[], char MT[], char *EXTcpy, char *MTcpy)
{
	for (int i = 0; i < 11; i++)
	{
		EXTcpy[i] = tolower(EXT[i]);
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
	int		i = 0;
	char	*tmp;

	while (str[i] != '\0')
		i++;
	while (i && str[i] != '.')
		i--;
	if (i < 0)
	{
//		fprintf(stderr, "returned 0, str = %s\n", str);
		return (0);
	}
	i++;
	tmp = strdup(str + i);
	i = 0;
	while (tmp[i])
	{
		tmp[i] = tolower(tmp[i]);
		i++;
	}
//	fprintf(stderr, "found filetype |%s| from |%s|\n", tmp, str);
	return (tmp);
}

void	search_type(t_list *type, char str[])
{
	char	*ext;

	ext = extract_type(str);
//	fprintf(stderr, "type = %s\n", ext);
	if (!ext)
	{
		printf("UNKNOWN\n");
		return;
	}
	while (type)
	{
		if (strcmp(((t_type *)(type->data))->EXT, ext) == 0)
		{
			printf("%s\n", ((t_type *)(type->data))->MT);
//			fprintf(stderr, "MT = %s, EXT = %s\n", ((t_type *)(type->data))->MT, ((t_type *)(type->data))->EXT);
			return;
		}
		type = type->next;
	}
	printf("UNKNOWN\n");
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
//		fprintf(stderr, "SCAN: %s %s\n", EXT, MT);
		types = add_type(types, EXT, MT);
//		fprintf(stderr, "EXT = %s\n", ((t_type *)ft_lstlast(types)->data)->EXT);
	}
	for (int i = 0; i < Q; i++) {
		char FNAME[257];
		scanf("%[^\n]", FNAME); fgetc(stdin);
//		fprintf(stderr, "SCAN: %s\n", FNAME);
		search_type(types, FNAME);
	}
	return 0;
}
