#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"


class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);
	virtual void Draw() override;
	virtual bool Update(sf::Time dt) override;
	virtual bool HandleEvent(const sf::Event& event) override;
	void UpdateOptionText();

private:
	enum Options
	{
		Play,
		Exit
	};

private:
	sf::Sprite m_background_sprite;
	std::vector<sf::Text> m_options;
	std::size_t m_options_index;


};

