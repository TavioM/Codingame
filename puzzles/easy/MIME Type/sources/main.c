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
	t_list	*new;
	t_list	*cpy;
	char	*tmp;

	t = malloc(sizeof(t_type));
	t->EXT = malloc(sizeof(char) * 11);
	t->MT = malloc(sizeof(char) * 51);
	copy_type(EXT, MT, t->EXT, t->MT);
	new = ft_lstnew(t);
	if (!types)
	{
		types = ft_lstnew(t);
		return (types);
	}
	cpy = types;
	tmp = ((t_type *)types->data)->EXT;
	while (strcmp(tmp, t->EXT) > 0)
	{
		if (types->next == 0)
		{
			types->next = new;
			new->prev = types;
			return (cpy);
		}
		types = types->next;
		tmp = ((t_type *)types->data)->EXT;
	}
	if (types != cpy)
	{
		new->next = types;
		new->prev = types->prev;
		types->prev = new;
		new->prev->next = new;
		return (cpy);
	}
	else
	{
		new->next = types;
		new->prev = 0;
		types->prev = new;
		return (new);
	}
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
		return (0);
	i++;
	tmp = malloc(sizeof(char) * strlen(str + i + 1));
	str = str + i;
	i = 0;
	while (*str)
		*(tmp + i++) = tolower(*str++);
	*(tmp + i) = 0;
	return (tmp);
}

void	search_type(t_list *type, char str[])
{
	char	*ext;

	ext = extract_type(str);
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
			return;
		}
		if (strcmp(((t_type *)(type->data))->EXT, ext) < 0)
		{
			printf("UNKNOWN\n");
			return;
		}
		type = type->next;
	}
	printf("UNKNOWN\n");
}

int main()
{
	int N, Q;
	clock_t	start, end;
	float	sec;
	t_list	*types = 0;

	scanf("%d", &N);
	scanf("%d", &Q);
	start = clock();
	for (int i = 0; i < N; i++) {
		char EXT[11];
		char MT[51];
		scanf("%s%s", EXT, MT); fgetc(stdin);
		types = add_type(types, EXT, MT);
	}
	end = clock();
	sec = (float)(end - start) / CLOCKS_PER_SEC;
	fprintf(stderr, "time elapsed = %f\n", sec);
	for (int i = 0; i < Q; i++) {
		char FNAME[258];
		scanf("%[^\n]", FNAME); fgetc(stdin);
		search_type(types, FNAME);
	}
	end = clock();
	sec = (float)(end - start) / CLOCKS_PER_SEC;
	fprintf(stderr, "time elapsed = %f\n", sec);
	return 0;
}
