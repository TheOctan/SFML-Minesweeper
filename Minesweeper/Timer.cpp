#include "Timer.h"

namespace Minesweeper
{
	Timer::Timer(sf::Font & font)
	:	textTime	("0", font, 50),
		box			(sf::Vector2f(100,60)),
		time		(0),
		isUpdate	(false)
	{
		this->box.setFillColor(sf::Color::Black);
		
		this->textTime.setFillColor(sf::Color::Red);
	}

	void Timer::Start()
	{
		if(!this->isUpdate) this->clock.restart();
		this->isUpdate = true;	
	}

	void Timer::Stop()
	{
		this->isUpdate = false;
	}

	void Timer::Restart()
	{
		this->time = 0;
		this->textTime.setString(std::to_string(this->time));
	}

	void Timer::Update()
	{
		if (this->isUpdate)
		{
			this->time = (sf::Uint32)this->clock.getElapsedTime().asSeconds();
			if (this->time > 999) this->time = 0;
			this->textTime.setString(std::to_string(this->time));
		}
			
	}

	void Timer::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.transform *= this->getTransform();

		target.draw(this->box, states);
		target.draw(this->textTime, states);
	}

}
