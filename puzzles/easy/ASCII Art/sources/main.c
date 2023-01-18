#include "file.h"

int		get_offset(char l)
{
	if (l >= 'a' && l <= 'z')
		return (l - 'a');
	else if (l >= 'A' && l <= 'Z')
		return (l - 'A');
	else
		return (26);
}

void	print_letter_line(char letter, char ROW[], int L)
{
	int	offset;

	offset = get_offset(letter);
	for (int i = 0; i < L; i++)
		printf("%c", ROW[(offset * L) + i]);
}

int		main()
{
	int		L, H;
	char	T[257];

	scanf("%d", &L);
	
	scanf("%d", &H);
	fgetc(stdin);
	
	scanf("%[^\n]", T);
	fgetc(stdin);

	for (int i = 0; i < H; i++)
	{
		char ROW[1025];
		scanf("%[^\n]", ROW);
		fgetc(stdin);
		for (int j = 0; T[j] != 0; j++)
			print_letter_line(T[j], ROW, L);
		printf("\n");
	}
}
