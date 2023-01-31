#include "file.h"

void	set_grid(char grid[9][9])
{
	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			grid[j][i] = ' ';
		}
	}
}

void	reset_grid(char grid[9][9])
{
	for (int j = 0; j < 9; j++)
		for (int i = 0; i < 9; i++)
			grid[j][i] = grid[j][i] == '.' ? ' ' : grid[j][i];
}

void	print(char grid[9][9])
{
	fprintf(stderr, "   |   |   \n");
	fprintf(stderr, " %c | %c | %c \n", grid[0][0], grid[0][1], grid[0][2]);
	fprintf(stderr, "---+---+---\n");
	fprintf(stderr, " %c | %c | %c \n", grid[1][0], grid[1][1], grid[1][2]);
	fprintf(stderr, "---+---+---\n");
	fprintf(stderr, " %c | %c | %c \n", grid[2][0], grid[2][1], grid[2][2]);
	fprintf(stderr, "   |   |   \n");
	fprintf(stderr, "\n");
}

void	make_move(char grid[9][9])
{
	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			if (grid[j][i] == '.')
			{
				printf("%d %d\n", j, i);
				grid[j][i] = 'o';
				return;
			}
		}
	}
}

int main()
{
	int		opp_row, opp_col;
	int		action_count;
	char	grid[9][9];

	set_grid(grid);
	while (1)
	{
		reset_grid(grid);
		scanf("%d%d", &opp_row, &opp_col);
		fprintf(stderr, "opp_row = %d, opp_col = %d\n", opp_row, opp_col);
		if (opp_row != -1 && opp_col != -1)
		{
			grid[opp_row][opp_col] = 'x';
			print(grid);
		}
		scanf("%d", &action_count);
		for (int i = 0; i < action_count; i++)
		{
			int row;
			int col;
			scanf("%d%d", &row, &col);
			grid[row][col] = '.';
		}
		make_move(grid);
		print(grid);
	}
	return 0;
}
