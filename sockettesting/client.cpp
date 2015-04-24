#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <vector>

using namespace std;

int main(){
	sf::IpAddress ip = sf::IpAddress("localhost"); // localhost
	sf::TcpSocket socket;
	bool done = false;
	std::string id;
	std::string text = "";

	std::cout << "Enter your ID: ";
	std::cin >> id;

	socket.connect(ip,2050);

	sf::RenderWindow window(sf::VideoMode(800,600,32), "Chat");
	std::vector<sf::Text> chat;

	sf::Packet packet;
	packet << id;
	socket.send(packet);
	socket.setBlocking(false);

	window.setTitle(id);

	sf::Font font;
	font.loadFromFile("MontereyFLF.ttf");

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			switch(event.type){
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if(event.key.code == sf::Keyboard::Escape)
						window.close();
					else if (event.key.code == sf::Keyboard::Return){
						sf::Packet packet;
						packet << id + ": " + text;
						socket.send(packet);
						sf::Text displayText(text,font, 40);
						displayText.setColor(sf::Color::Green);
						chat.push_back(displayText);
						text = "";
					}
					break;
				case sf::Event::TextEntered:
					text += event.text.unicode;
					break;
				default:
					break;
			}
		}
		sf::Packet packet;
		socket.receive(packet);

		std::string temptext;
		if(packet >> temptext){
			sf::Text displayText(temptext, font, 40);
			displayText.setColor(sf::Color::Blue);
			chat.push_back(displayText);
		}

		int i = 0;
		for(i;i < chat.size(); ++i){
			chat[i].setPosition(0,i*40);
			window.draw(chat[i]);
		}

		sf::Text drawText(text, font, 20);
		drawText.setColor(sf::Color::Red);
		drawText.setPosition(0,i*40);
		window.draw(drawText);

		window.display();
		window.clear();
	}
}