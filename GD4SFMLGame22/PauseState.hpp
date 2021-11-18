#pragma once
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);
	virtual void Draw() override;
	virtual bool Update(sf::Time dt) override;
	virtual bool HandleEvent(const sf::Event& event) override;
	void UpdateOptionText();

private:
	enum Options
	{
		kResume,
		kExit_Game
	};

private:
	std::vector<sf::Text> m_options;
	std::size_t m_options_index;
};

