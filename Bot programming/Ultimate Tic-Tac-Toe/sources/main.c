#include "file.h"

void	set_grid(char grid[3][3])
{
	grid[0][0] = ' ';
	grid[0][1] = ' ';
	grid[0][2] = ' ';
	grid[1][0] = ' ';
	grid[1][1] = ' ';
	grid[1][2] = ' ';
	grid[2][0] = ' ';
	grid[2][1] = ' ';
	grid[2][2] = ' ';
}

void	reset_grid(char grid[3][3])
{
	grid[0][0] = grid[0][0] == '.' ? ' ' : grid[0][0];
	grid[0][1] = grid[0][1] == '.' ? ' ' : grid[0][1];
	grid[0][2] = grid[0][2] == '.' ? ' ' : grid[0][2];
	grid[1][0] = grid[1][0] == '.' ? ' ' : grid[1][0];
	grid[1][1] = grid[1][1] == '.' ? ' ' : grid[1][1];
	grid[1][2] = grid[1][2] == '.' ? ' ' : grid[1][2];
	grid[2][0] = grid[2][0] == '.' ? ' ' : grid[2][0];
	grid[2][1] = grid[2][1] == '.' ? ' ' : grid[2][1];
	grid[2][2] = grid[2][2] == '.' ? ' ' : grid[2][2];
}

void	print(char grid[3][3])
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

void	make_move(char grid[3][3])
{
	if (grid[1][1] == '.')
	{
		printf("1 1\n");
		return;
	}
	if (grid[2][0] == '.')
	{
		printf("2 0\n");
		return;
	}
	if (grid[0][2] == '.')
	{
		printf("0 2\n");
		return;
	}
	if (grid[2][2] == '.')
	{
		printf("2 2\n");
		return;
	}
	if (grid[0][0] == '.')
	{
		printf("0 0\n");
		return;
	}

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
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
	char	grid[3][3];

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
