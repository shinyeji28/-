#include<SFML/Graphics.hpp>
#include<time.h>
#include<iostream>
#define msize 20
using namespace sf;

int pixcel = 32;
int map[msize][msize];
int smap[msize][msize];
int x, y;
int total = (msize - 2) * (msize - 2);
int count = 0;
int bomb_c = 0;
int flag_c = 0;
int flag = 0;
int succ = 0;

void map_maker()
{
	map[3][6] = 9;
	map[14][3] = 9;
	map[17][14] = 9;
	map[13][5] = 9;
	map[5][2] = 9;



	for (int i = 1; i <= msize - 2; i++)
	{
		for (int j = 1; j <= msize - 2; j++)
		{
			smap[i][j] = 10;
			if (rand() % 7 == 0)
			{
				map[i][j] = 9;
			bomb_c++;
			}
			else map[i][j] = 0;
		}
	}

	for (int i = 1; i <= msize - 2; i++)
	{
		for (int j = 1; j <= msize - 2; j++)
		{
			int cnt = 0;
			if (map[i][j] == 9) continue;
			if (map[i + 1][j] == 9)cnt++;
			if (map[i][j + 1] == 9)cnt++;
			if (map[i - 1][j] == 9)cnt++;
			if (map[i][j - 1] == 9)cnt++;
			if (map[i + 1][j + 1] == 9)cnt++;
			if (map[i - 1][j - 1] == 9)cnt++;
			if (map[i - 1][j + 1] == 9)cnt++;
			if (map[i + 1][j - 1] == 9)cnt++;
			map[i][j] = cnt;
		}
	}
}
void check(int _x, int _y)
{
	if (smap[_x][_y] == 11)
	{
		return;
	}
	if (map[_x][_y] == 0 and smap[_x][_y] == 10 and _x >= 1 and _x <= msize - 2 and _y >= 1 and _y <= msize - 2)
	{
		smap[_x][_y] = map[_x][_y];
		count++;

		check(_x + 1, _y);
		check(_x, _y + 1);
		check(_x - 1, _y);
		check(_x, _y - 1);
	}
	if (map[_x][_y] >= 1 and map[_x][_y] <= 8 and smap[_x][_y] == 10)
	{
		smap[_x][_y] = map[_x][_y];
		count++;
		return;
	}
}
int main()
{
	srand(time(0));

	map_maker();

	for (int i = 1; i < msize - 1; i++)
	{
		for (int j = 1; j < msize - 1; j++)
		{
			std::cout << map[j][i] << " ";
		}
		std::cout << std::endl;
	}

	RenderWindow window(VideoMode(650, 750), "Minesweeper");

	Texture t;
	t.loadFromFile("tiles.jpg");
	Sprite s(t);
	Texture t1;
	t1.loadFromFile("success.jpg");
	Sprite s1(t1); 
	Texture t2;
	t2.loadFromFile("fail.jpg");
	Sprite s2(t2);


	while (window.isOpen())
	{


		Event e;
		while (window.pollEvent(e))
		{
			Vector2i pos = Mouse::getPosition(window);
			x = pos.x / pixcel;
			y = pos.y / pixcel;

			if (e.type == Event::Closed)
			{
				window.close();
			}
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					if (smap[x][y]==10)
					{
						if (map[x][y] == 0)
						{
							check(x, y);
						}
						else
						{
							smap[x][y] = map[x][y];
							count++;
						}
					}
				}
				else if (e.key.code == Mouse::Right)
				{
					if (smap[x][y] == 10)
					{
						smap[x][y] = 11;
						flag_c++;
					}
					else if (smap[x][y] == 11)
					{
						smap[x][y] = 10;
						flag_c--;
					}
				}
			}
			else
			{
				continue;
			}
		}

		if (succ == 0)
		{
			window.clear(Color::White);
		}


		for (int i = 1; i <= msize - 2; i++)
		{
			for (int j = 1; j <= msize - 2; j++)
			{
				if (smap[x][y] == 9)
				{
					smap[i][j] = map[i][j];
					if (flag == 0)
					{
						std::cout << "!!! 실 패 !!!" << std::endl;
						s2.setPosition(9 * pixcel, 20*pixcel);
						flag = 1;

					}
				}
				s.setTextureRect(IntRect(smap[i][j] * pixcel, 0, pixcel, pixcel));
				s.setPosition(i * pixcel, j * pixcel);
				
				window.draw(s);

			}
		}
		if ((total - count) == bomb_c and flag_c == bomb_c)
		{
			std::cout << "!!! 성 공 !!!" << std::endl;

			s1.setPosition(9 * pixcel, 20*pixcel);
			window.draw(s1);
			succ = 1;

		}
		if (flag == 1)
		{
			window.draw(s2);
		}
		window.display();
	}
	return 0;
}