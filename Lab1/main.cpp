#include <SFML/Graphics.hpp>
#include "TransformNode.h"

int main(int argc, char* argv)
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Purple");

	sf::CircleShape circleHead(10.0f);

	sf::RectangleShape leftForearm(sf::Vector2<float>(15.0f, 5.0f));
	sf::RectangleShape leftArm(sf::Vector2<float>(15.0f, 5.0f));

	sf::RectangleShape rightForearm(sf::Vector2<float>(15.0f, 5.0f));
	sf::RectangleShape rightArm(sf::Vector2<float>(15.0f, 5.0f));

	sf::RectangleShape neck(sf::Vector2<float>(10.0f, 2.0f));

	sf::RectangleShape body(sf::Vector2<float>(40.0f, 10.0f));

	circleHead.setFillColor(sf::Color::Yellow);

	leftForearm.setFillColor(sf::Color::Magenta);
	leftArm.setFillColor(sf::Color::Blue);

	rightForearm.setFillColor(sf::Color::Magenta);
	rightArm.setFillColor(sf::Color::Blue);

	neck.setFillColor(sf::Color::Red);
	body.setFillColor(sf::Color::Green);

	body.setOrigin(40.0f, 5.0f);
	body.setPosition(260.0f, 500.0f);
	body.setScale(4, 4);
	body.setRotation(90);

	sf::Vector2<float> leftArmPosition((0), (body.getLocalBounds().height));

	sf::Vector2<float> rightArmPosition((0), (0));

	sf::Vector2<float> neckPosition((0), (body.getLocalBounds().height / 2.0f));

	sf::Vector2<float> leftArmOrigin(0.0f, 2.5f);

	sf::Vector2<float> rightArmOrigin(0.0f, 2.5f);
	
	sf::Vector2<float> neckOrigin(0.0f, 2.5f);


	leftForearm.setOrigin(leftArmOrigin);
	leftArm.setOrigin(leftArmOrigin);

	rightForearm.setOrigin(rightArmOrigin);
	rightArm.setOrigin(rightArmOrigin);

	neck.setOrigin(neckOrigin);
	neck.setRotation(180);

	circleHead.setOrigin(circleHead.getRadius(), circleHead.getRadius()*2);


	leftForearm.setPosition(15.0f, 2.5f);
	leftArm.setPosition(leftArmPosition);

	neck.setPosition(neckPosition);

	circleHead.setPosition(10.0f, 2.0f);

	rightForearm.setPosition(15.0f, 2.5f);
	rightArm.setPosition(rightArmPosition);

	TransformNode head(&circleHead);
	TransformNode bodyN(&body);

	TransformNode leftForearmN(&leftForearm);
	TransformNode leftArmN(&leftArm);

	TransformNode rightForearmN(&rightForearm);
	TransformNode rightArmN(&rightArm);

	TransformNode neckN(&neck);
	TransformNode circleHeadN(&circleHead);

	leftArmN.AddChild(&leftForearmN);
	bodyN.AddChild(&leftArmN);
	//head.AddChild(&leftArmN);


	rightArmN.AddChild(&rightForearmN);
	bodyN.AddChild(&rightArmN);

	neckN.AddChild(&circleHeadN);
	bodyN.AddChild(&neckN);

	sf::Clock deltaTime;
	int direction = -1;
	while (window.isOpen())
	{
		float elaspedTime = deltaTime.restart().asSeconds();

		sf::Transform transform = circleHead.getTransform();
		
		sf::Event sfEvent;
		while (window.pollEvent(sfEvent))
		{
			if (sfEvent.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		float angleAmount = 90.0f;
		leftForearm.rotate(angleAmount * elaspedTime);
		leftArm.rotate(angleAmount * elaspedTime);

		rightForearm.rotate(angleAmount * elaspedTime * -1);
		rightArm.rotate(angleAmount * elaspedTime * -1 * 1.5);


		circleHead.rotate(angleAmount * elaspedTime * -1 * 1.5);

		if (body.getRotation() < 30 || body.getRotation() > 150)
		{
			direction *= -1;
		}

		body.rotate(angleAmount * elaspedTime * direction);
		
		window.clear(); // draw fullscreen graphic

		bodyN.Draw(&window);

		window.display();
	}

	return 0;
}