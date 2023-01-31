#include "file.h"

void	set_grid(char grid[3][3][3][3])
{
	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			GRID(i, j) = ' ';
		}
	}
}

void	reset_grid(char grid[3][3][3][3])
{
	for (int j = 0; j < 9; j++)
		for (int i = 0; i < 9; i++)
			GRID(i, j) = GRID(i, j) == '.' ? ' ' : GRID(i, j);
}

void	print(char grid[3][3][3][3])
{
	fprintf(stderr, "   |   |   \n""   |   |   \n""   |   |   \n");
	fprintf(stderr, " %c | %c | %c \n", GRID(0, 0), GRID(1, 0), GRID(2, 0));
	fprintf(stderr, "---+---+---\n");
	fprintf(stderr, " %c | %c | %c \n", GRID(0, 1), GRID(1, 1), GRID(2, 1));
	fprintf(stderr, "---+---+---\n");
	fprintf(stderr, " %c | %c | %c \n", GRID(0, 2), GRID(1, 2), GRID(2, 2));
	fprintf(stderr, "   |   |   \n");
	fprintf(stderr, "\n");
}

void	make_move(char grid[3][3][3][3])
{
	if (GRID(8, 8) == '.')
	{
		printf("8 8\n");
		return;
	}
	if (GRID(8, 4) == '.')
	{
		printf("8 4\n");
		return;
	}
	if (GRID(8, 0) == '.')
	{
		printf("8 0\n");
		return;
	}
	if (GRID(4, 8) == '.')
	{
		printf("4 8\n");
		return;
	}
	if (GRID(4, 4) == '.')
	{
		printf("4 4\n");
		return;
	}
	if (GRID(4, 0) == '.')
	{
		printf("4 0\n");
		return;
	}
	if (GRID(0, 8) == '.')
	{
		printf("0 8\n");
		return;
	}
	if (GRID(0, 4) == '.')
	{
		printf("0 4\n");
		return;
	}
	if (GRID(0, 0) == '.')
	{
		printf("0 0\n");
		return;
	}
	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			if (GRID(i, j) == '.')
			{
				printf("%d %d\n", i, j);
				GRID(i, j) = 'o';
				return;
			}
		}
	}
}

int main()
{
	int		opp_row, opp_col;
	int		action_count;
	char	grid[3][3][3][3];

	set_grid(grid);
	while (1)
	{
		reset_grid(grid);
		scanf("%d%d", &opp_row, &opp_col);
		fprintf(stderr, "opp_row = %d, opp_col = %d\n", opp_row, opp_col);
		if (opp_row != -1 && opp_col != -1)
		{
			GRID(opp_row, opp_col) = 'x';
			print(grid);
		}
		scanf("%d", &action_count);
		for (int i = 0; i < action_count; i++)
		{
			int row;
			int col;
			scanf("%d%d", &row, &col);
			GRID(row, col) = '.';
		}
		make_move(grid);
		print(grid);
	}
	return 0;
}
