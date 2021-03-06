#include "Aircraft.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "ResourceHolder.hpp"


Textures ToTextureID(AircraftType type)
{
	switch(type)
	{
	case AircraftType::kEagle:
		return Textures::kEagle;
	case AircraftType::kRaptor:
		return Textures::kRaptor;
	}
	return Textures::kEagle;
}

Aircraft::Aircraft(AircraftType type, const TextureHolder& textures):m_type(type), m_sprite(textures.Get(ToTextureID(type)))
{
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

unsigned Aircraft::GetCategory() const
{
	switch(m_type)
	{
	case AircraftType::kEagle:
		return Category::kPlayerAircraft;
	default:
		return Category::kEnemyAircraft;

	}
}
