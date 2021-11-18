#pragma once
namespace sf
{
	class Sprite;
	class Text;
}

class Utility
{
public:
	static void CenterOrigin(sf::Sprite& sprite);
	static void CenterOrigin(sf::Text& text);
};

