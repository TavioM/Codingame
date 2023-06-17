#include "tronBattle.hpp"

void	print_grid(std::map<int, std::map<int, bool>> grid)
{
	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < 30; i++)
		{
			std::cerr << grid[i][j] << " ";
		}
		std::cerr << std::endl;
	}
	
}

//void	fill_info(std::vector <std::shared_ptr <std::vector <std::pair <int, int>>>> &players, int x0, int y0, int xn, int yn)
void	fill_info(std::vector <std::pair <int, int>> &player, int x0, int y0, int xn, int yn)
{
	player.push_back(std::make_pair(xn, yn));
/*	for (int i = 0; i < (int)players.size(); i++)
	{
		if (players[i][0].first == x0 && players[i][0].second == y0)
			players[i].push_back(std::make_pair(xn, yn));
	}*/
}

void	print_path(std::vector<std::pair<int, int>> &player)
{
	for (int i = 0; i < (int)player.size(); i++)
	{
		std::cerr << "(" << player[i].first << ":" << player[i].second << ") ";
	}
	std::cerr << std::endl;
}

int main()
{
	std::vector<std::pair<int, int>> self;
	std::vector<std::pair<int, int>> player2;
//	std::vector<int> player3;
//	std::vector<int> player4;

//	std::vector <std::vector <std::pair <int, int>>> players;
//	players.push_back(&self);
//	players.push_back(&player2);

	std::map<int, std::map<int, bool>> grid;
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			grid[i][j] = false;
		}
	}

	for (int turn = 0; ; turn++)
	{
		int n; // total number of players (2 to 4).
		int p; // your player number (0 to 3).
		std::cin >> n >> p; std::cin.ignore();
//		std::cerr << "n: " << n << ", p:" << p << std::endl;
		for (int i = 0; i < n; i++) {
			int x0; // lightcycle X coordinate at start(or -1)
			int y0; // lightcycle Y coordinate at start(or -1)
			int xn; // starting X coordinate of lightcycle (can be the same as X0 if you play before this player)
			int yn; // starting Y coordinate of lightcycle (can be the same as Y0 if you play before this player)
			std::cin >> x0 >> y0 >> xn >> yn; std::cin.ignore();

			grid[x0][y0] = true;
			grid[xn][yn] = true;

			std::cerr << "x0: " << x0 << ", ";
			std::cerr << "y0: " << y0 << ", ";
			std::cerr << "xn: " << xn << ", ";
			std::cerr << "yn: " << yn << std::endl;
			if (i == p)
				fill_info(self, x0, y0, xn, yn);
			else
				fill_info(player2, x0, y0, xn, yn);
		}

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;
		print_grid(grid);
		print_path(self);
		int x, y;
		x = self[turn].first;
		y = self[turn].second;
		if (y != 0 && !grid[x][y - 1])
			std::cout << "UP" << std::endl;
		else if (y != 19 && !grid[x][y + 1])
			std::cout << "DOWN" << std::endl;
		else if (x != 0 && !grid[x - 1][y])
			std::cout << "LEFT" << std::endl;
		else if (x != 29 && !grid[x + 1][y])
			std::cout << "RIGHT" << std::endl;
		else
			std::cout << "RIGHT" << std::endl;
	}
}
