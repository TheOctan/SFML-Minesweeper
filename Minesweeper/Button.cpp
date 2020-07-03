#include "Button.hpp"

namespace Minesweeper
{
	Button::Button(const sf::Vector2f& size)
	:	box			(size),
		isClicked	(false),
		clickable	(true)
	{
		this->box.setFillColor(sf::Color::Transparent);
		this->box.setOutlineColor(sf::Color::White);
		this->box.setOutlineThickness(-1);

		this->index = this->Button::count;
		this->Button::count++;
	}

	void Button::Update(const sf::Vector2i& pos)
	{
		if (this->box.getGlobalBounds().contains(sf::Vector2f(pos) - this->getPosition()))
		{
			this->box.setFillColor(sf::Color(239, 228, 176, 150));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->box.setFillColor(sf::Color(249, 176, 166, 150));
				
				if (this->clickable)
				{
					this->isClicked = true;
					this->clickable = false;
				}
				else
				{
					this->isClicked = false;
				}
			}
			else
			{
				this->clickable = true;
			}
		}
		else
		{
			this->box.setFillColor(sf::Color::Transparent);
		}
	}

	const sf::Vector2f & Button::getSize() const
	{
		return this->box.getSize();
	}

	void Button::setColor(sf::Color color)
	{
		this->box.setFillColor(color);
	}

	void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.transform *= this->getTransform();

		target.draw(this->box, states);
	}

	int Button::count = 0;
}


