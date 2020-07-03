//Minesweeper_main.cpp
//

#include<SFML/Graphics.hpp>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<iostream>

#include"Game.hpp"
#include"Button.hpp"
#include"Timer.h"

using namespace sf;
using namespace std;
using namespace Minesweeper;

int main()
{
	srand(unsigned(time(NULL)));

	RenderWindow window(VideoMode(320, 420), "Minesweeper", Style::Close);

	Image icon;
	icon.loadFromFile("images/Minesweeper.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Texture texture;
	texture.loadFromFile("images/tiles.jpg");

	Font font;
	font.loadFromFile("Fonts/digifaw.TTF");

	//=============================================//
	RectangleShape menu(Vector2f(320.f, 100.f));
	menu.setFillColor(Color(192, 192, 192));
	menu.setOutlineColor(Color(128, 128, 128));
	menu.setOutlineThickness(-3);
	//=============================================//

	//=============================================//
	RectangleShape box(Vector2f(100, 60));
	box.setFillColor(sf::Color::Black);
	box.setPosition(20, 20);

	Text flags("0", font, 50);
	flags.setFillColor(Color::Red);	
	flags.setPosition(20, 20);
	//=============================================//

	Timer timer(font);
	timer.setPosition(200, 20);

	Button button(Vector2f(60, 60));
	button.setPosition(130, 20);

	Game game(texture, Vector2u(10, 10), 10);
	game.setPosition(0, 100);
	
	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				game.Update(pos, event.mouseButton.button);
				if(!game.isGameOver() && !game.isGameWin()) timer.Start();
			}

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Space)
					game.Reset();
		}

		button.Update(pos);
		timer.Update();

		flags.setString(std::to_string(game.getFlags()));

		if (button.clicked())
		{
			timer.Stop();
			timer.Restart();
			game.Reset();
		}

		if (game.isGameOver())
		{
			timer.Stop();
			button.setColor(Color::Red);
		}
		else if (game.isGameWin())
		{
			timer.Stop();
			button.setColor(Color::Green);
		}
		
		window.clear();
		
		window.draw(menu);
		window.draw(button);
		window.draw(timer);
		window.draw(box);
		window.draw(flags);
		
		game.Draw(window);

		window.display();

	}

	return 0;
}