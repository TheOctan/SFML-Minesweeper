#pragma once

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include<SFML\Graphics.hpp>
#include<string>
#include<iostream>

namespace Minesweeper
{
	class Button : public sf::Drawable, public sf::Transformable	//����� ������ (����������� �� Drawable - �������� �� ���������, Trnsformable - �������� �� �������������)
	{
	public:
		Button(const sf::Vector2f& size = sf::Vector2f(100, 30));

		void Update(const sf::Vector2i& pos);							//����� ����������
		const sf::Vector2f& getSize() const;							//����� ��������� ������ ������
		void setColor(sf::Color color);

		//Accessors
		inline const int&	getIndex()	const { return this->index; }		//��������, ������������ ������
		inline const bool&	clicked()	const { return this->isClicked; }	//��������, ������������ ������ �������

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;		//����� ���������

	private:
		static int			count;				//���������� ������
		bool				isClicked;			//��������, ������ �� ������
		bool				clickable;			//��������, ����������� �� ������

		sf::RectangleShape	box;				//�����
		sf::Int32			index;				//������
	};

} // namespace Minesweeper

#endif // !BUTTON_HPP

