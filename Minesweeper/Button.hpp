#pragma once

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include<SFML\Graphics.hpp>
#include<string>
#include<iostream>

namespace Minesweeper
{
	class Button : public sf::Drawable, public sf::Transformable	//класс кнопка (наследуется от Drawable - отвечает за отрисовку, Trnsformable - отвечает за трансформацию)
	{
	public:
		Button(const sf::Vector2f& size = sf::Vector2f(100, 30));

		void Update(const sf::Vector2i& pos);							//метод обновления
		const sf::Vector2f& getSize() const;							//метод получения размеа кнопки
		void setColor(sf::Color color);

		//Accessors
		inline const int&	getIndex()	const { return this->index; }		//аксессор, возвращающий индекс
		inline const bool&	clicked()	const { return this->isClicked; }	//аксессор, возвращаюший статус нажатия

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;		//метод отрисовки

	private:
		static int			count;				//количество кнопок
		bool				isClicked;			//отвечает, нажата ли кнопка
		bool				clickable;			//отвечает, кликабельна ли кнопка

		sf::RectangleShape	box;				//рамка
		sf::Int32			index;				//индекс
	};

} // namespace Minesweeper

#endif // !BUTTON_HPP

