#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "Button.hpp"
#include "Container.hpp"
#include "Label.hpp"
#include "PlayerAction.hpp"
#include "State.hpp"

class SettingsState : public State
{
public:
	SettingsState(StateStack& stack, Context context);
	virtual void Draw();
	virtual bool Update(sf::Time dt);
	virtual bool HandleEvent(const sf::Event& event);

private:
	sf::Sprite m_background_sprite;
	GUI::Container m_gui_container;
	std::pair<PlayerAction, GUI::Button::Ptr> m_current_keybind_listen;

private:
	GUI::Label::Ptr CreateActionLabel(PlayerAction player_action) const;
	std::string KeyCodeToString(int keyCode) const;
};
