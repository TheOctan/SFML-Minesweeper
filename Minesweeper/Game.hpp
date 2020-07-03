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

		//����������
		inline const bool	isGameOver()	const { return this->gameOver;  }
		inline const bool	isGameWin()		const { return this->gameWin;	}
		inline const int	getFlags()		const { return this->countMines - this->countFlags; }

	private:
		void Init();
		void fill(int x, int y);
		void uncover();

	private:
		sf::Sprite		sprite;						//������
		sf::Vector2i	sizeField;					//������ �������� ����
		sf::Vector2i	tile;						//����� ������

		sf::Int32		width;						//������ ������
		sf::Uint32		maxCountMines;				//������������ ���������� ���
		sf::Uint32		countMines;					//���������� ���

		sf::Int32		countFlags;					//���������� ������

		IntMatrix		grid;						//������� �����
		IntMatrix		showGrid;					//����� ��� ���������

		bool			gameOver;					//������ ��������� ����
		bool			gameWin;					//������ �������� ����
	};

} // namespace Minesweeper

#endif // !GAME_HPP
