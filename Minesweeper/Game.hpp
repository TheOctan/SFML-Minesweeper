#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include<SFML/Graphics.hpp>

namespace Minesweeper
{
	typedef std::vector<int>		IntVector;
	typedef std::vector<IntVector>	IntMatrix;

	class Game : public sf::Transformable
	{
	public:
		Game(
			sf::Texture&	texture,
			sf::Vector2u	sizeField	= sf::Vector2u(10, 10), 
			sf::Uint32		countMines	= 10
		);

		void Update(const sf::Vector2i& pos, sf::Mouse::Button button);
		void Draw(sf::RenderWindow& window);
		void Reset();

		//Акссессоры
		inline const bool	isGameOver()	const { return this->gameOver;  }
		inline const bool	isGameWin()		const { return this->gameWin;	}
		inline const int	getFlags()		const { return this->countMines - this->countFlags; }

	private:
		void Init();
		void fill(int x, int y);
		void uncover();

	private:
		sf::Sprite		sprite;						//спрайт
		sf::Vector2i	sizeField;					//размер игрового поля
		sf::Vector2i	tile;						//номер плитки

		sf::Int32		width;						//ширина плитки
		sf::Uint32		maxCountMines;				//максимальное количество мин
		sf::Uint32		countMines;					//количество мин

		sf::Int32		countFlags;					//количество флагов

		IntMatrix		grid;						//скрытая сетка
		IntMatrix		showGrid;					//сетка для отрисовки

		bool			gameOver;					//статус проигрыша игры
		bool			gameWin;					//статус выигрыша игры
	};

} // namespace Minesweeper

#endif // !GAME_HPP
