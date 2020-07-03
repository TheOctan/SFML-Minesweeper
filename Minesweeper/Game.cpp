#include "Game.hpp"
#include<iostream>

namespace Minesweeper
{
	Game::Game(sf::Texture & texture, sf::Vector2u sizeField, sf::Uint32 countMines)
		: sprite(texture),
		width(32),
		maxCountMines((sizeField.x * sizeField.y) / 2),
		countMines(countMines > maxCountMines ? maxCountMines : countMines),
		sizeField(sizeField),
		showGrid(sizeField.x + 2, IntVector(sizeField.y + 2, -2)),
		grid(sizeField.x + 2, IntVector(sizeField.y + 2, -2)),
		gameOver(false),
		gameWin(false)
	{
		this->Init();
	}

	void Game::Update(const sf::Vector2i & pos, sf::Mouse::Button button)
	{
		if (!this->gameOver && !this->gameWin)
		{
			int x = int((pos.x - this->getPosition().x) / this->width + 1);
			int y = int((pos.y - this->getPosition().y) / this->width + 1);

			if (x >= 1 && x <= sizeField.x && y >= 1 && y <= sizeField.y)
			{
				this->tile.x = x;
				this->tile.y = y;

				if (button == sf::Mouse::Left)
				{
					if (showGrid[tile.x][tile.y] != 11)
					{
						this->showGrid[tile.x][tile.y] = this->grid[tile.x][tile.y];
						this->fill(this->tile.x, this->tile.y);
					}
				}
				else if (button == sf::Mouse::Right)
				{
					if (this->showGrid[tile.x][tile.y] == 10 && this->countFlags < (int)this->countMines)
					{
						this->showGrid[tile.x][tile.y] = 11;
						this->countFlags++;
					}
					else if (this->showGrid[tile.x][tile.y] == 11)
					{
						this->showGrid[tile.x][tile.y] = 10;
						this->countFlags--;
					}
				}
			}
		}
	}

	void Game::Draw(sf::RenderWindow & window)
	{
		if (this->gameWin)
		{
			this->countFlags = this->countMines;
			for (int i = 1; i <= this->sizeField.x; i++)
			{
				for (int j = 1; j <= this->sizeField.y; j++)
				{
					if (this->grid[i][j] == 9) this->showGrid[i][j] = 11;
				}
			}
		}

		for (int i = 1; i <= this->sizeField.x; i++)
		{
			for (int j = 1; j <= this->sizeField.y; j++)
			{
				if (this->grid[i][j] == -1)
				{
					this->showGrid[i][j] = 0;
					this->grid[i][j] = 0;
				}
			}
		}

		this->uncover();

		int count = this->sizeField.x * this->sizeField.y - this->countMines;
		for (int i = 1; i <= this->sizeField.x; i++)
		{
			for (int j = 1; j <= this->sizeField.y; j++)
			{
				if (this->showGrid[i][j] != 10 && this->showGrid[i][j] != 11)
				{
					count--;
				}
			}
		}
		if (count == 0) this->gameWin = true;

		for (int i = 1; i <= sizeField.x; i++)
		{
			for (int j = 1; j <= sizeField.y; j++)
			{
				if (this->showGrid[tile.x][tile.y] == 9 && this->grid[i][j] == 9 && showGrid[i][j] != 11)
				{
					this->showGrid[i][j] = grid[i][j];
					this->gameOver = true;
				}

				this->sprite.setTextureRect(sf::IntRect(this->showGrid[i][j] * width, 0, width, width));
				this->sprite.setPosition(float(i*width - width), float(j*width - width));
				window.draw(this->sprite, this->getTransform());
			}
		}
	}

	void Game::Reset()
	{
		this->Init();
		this->gameOver = false;
		this->gameWin = false;
		this->countFlags = 0;
	}

	void Game::Init()
	{
		//заполнение видимого игрового пол€
		for (int i = 1; i <= sizeField.x; i++)
		{
			for (int j = 1; j <= sizeField.y; j++)
			{
				this->showGrid[i][j] = 10;
				this->grid[i][j] = 0;
			}
		}

		//генераци€ мин
		int count = this->countMines;
		do
		{
			int i = rand() % (this->sizeField.x - 1) + 1;
			int j = rand() % (this->sizeField.y - 1) + 1;

			if (this->grid[i][j] != 9)
			{
				this->grid[i][j] = 9;
				count--;
			}

		} while (count != 0);

		//подсчЄт мин вокруг каждой €чейки
		for (int i = 1; i <= sizeField.x; i++)
		{
			for (int j = 1; j <= sizeField.y; j++)
			{
				int count = 0;
				if (grid[i][j] == 9) continue;
				if (grid[i + 1][j] == 9) count++;
				if (grid[i][j + 1] == 9) count++;
				if (grid[i - 1][j] == 9) count++;
				if (grid[i][j - 1] == 9) count++;
				if (grid[i + 1][j + 1] == 9) count++;
				if (grid[i - 1][j - 1] == 9) count++;
				if (grid[i - 1][j + 1] == 9) count++;
				if (grid[i + 1][j - 1] == 9) count++;
				grid[i][j] = count;
			}
		}
	}

	void Game::fill(int x, int y)
	{
		if (showGrid[x][y] == 11) countFlags--;

		if (grid[x][y] == 0) grid[x][y] = -1;
		if (grid[x - 1][y] == 0) fill(x - 1, y);
		if (grid[x + 1][y] == 0) fill(x + 1, y);
		if (grid[x][y - 1] == 0) fill(x, y - 1);
		if (grid[x][y + 1] == 0) fill(x, y + 1);
	}

	void Game::uncover()
	{
		for (int i = 1; i <= sizeField.x; i++)
		{
			for (int j = 1; j <= sizeField.y; j++)
			{
				if (this->showGrid[i][j] == 0)
				{
					if (this->showGrid[i - 1][j - 1]	== 11)	countFlags--;
					if (this->showGrid[i][j - 1]		== 11)	countFlags--;
					if (this->showGrid[i + 1][j - 1]	== 11)	countFlags--;
					if (this->showGrid[i + 1][j]		== 11)	countFlags--;
					if (this->showGrid[i + 1][j + 1]	== 11)	countFlags--;
					if (this->showGrid[i][j + 1]		== 11)	countFlags--;
					if (this->showGrid[i - 1][j + 1]	== 11)	countFlags--;
					if (this->showGrid[i - 1][j]		== 11)	countFlags--;
					
					this->showGrid[i - 1][j - 1]	= this->grid[i - 1][j - 1];
					this->showGrid[i][j - 1]		= this->grid[i][j - 1];
					this->showGrid[i + 1][j - 1]	= this->grid[i + 1][j - 1];
					this->showGrid[i + 1][j]		= this->grid[i + 1][j];
					this->showGrid[i + 1][j + 1]	= this->grid[i + 1][j + 1];
					this->showGrid[i][j + 1]		= this->grid[i][j + 1];
					this->showGrid[i - 1][j + 1]	= this->grid[i - 1][j + 1];
					this->showGrid[i - 1][j]		= this->grid[i - 1][j];
				}
			}
		}
	}


}
