#pragma once

#ifndef TIMER_HPP
#define TIMER_HPP

#include<SFML/Graphics.hpp>
#include<string>

namespace Minesweeper
{
	class Timer : public sf::Drawable, public sf::Transformable
	{
	public:
		Timer(sf::Font& font);

		void Start();
		void Stop();
		void Restart();
		void Update();

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Clock			clock;
		sf::Text			textTime;
		sf::RectangleShape	box;
		sf::Uint32			time;
		
		bool				isUpdate;
	};

} // namespace Minesweeper

#endif // !TIMER_HPP


