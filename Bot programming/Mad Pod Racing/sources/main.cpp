#include "madPodRacing.hpp"

int main()
{
	int thrust = 100;
	bool boost = true;
	Pod pod;

    for (int turn = 0; ; turn++)
	{
        int x;
        int y;
        int next_x; // x position of the next check point
        int next_y; // y position of the next check point
        int next_dist; // distance to the next checkpoint
        int next_angle; // angle between your pod orientation and the direction of the next checkpoint
		std::cin >> x >> y >> next_x >> next_y >> next_dist >> next_angle; std::cin.ignore();
        int opponent_x;
        int opponent_y;
		std::cin >> opponent_x >> opponent_y; std::cin.ignore();
		
		pod.prev_x = pod.x;
		pod.prev_y = pod.y;
		pod.x = x;
		pod.y = y;

		int speed_x = pod.prev_x - pod.x;
		int speed_y = pod.prev_y - pod.y;

		std::cerr << "speed x: " << speed_x << ", speed y: " << speed_y << std::endl;

		if (std::abs(next_angle) > 70)
			thrust = 0;
		if (boost && next_dist > 6000 && std::abs(next_angle) <= 1)
		{
			boost = false;
			std::cout << next_x << " " << next_y << " BOOST" << std::endl;
		}
		else
		{
			if (thrust && next_angle * 120 > next_dist)
				thrust -= next_angle;
			std::cout << next_x << " " << next_y << " " << thrust << std::endl;
		}
        std::cerr << "x = " << x;
        std::cerr << ", y = " << y << std::endl;
        std::cerr << "next_x = " << next_x;
        std::cerr << ", next_y = " << next_y << std::endl;
        std::cerr << "dist = " << next_dist;
        std::cerr << ", angle = " << next_angle << std::endl;

		thrust = 100;
    }
}
