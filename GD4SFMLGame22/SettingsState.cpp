#include "SettingsState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Button.hpp"
#include "Label.hpp"
#include "Player.hpp"
#include "ResourceHolder.hpp"
#include "StateStack.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
{
	const sf::Texture& texture = context.textures->Get(Textures::kTitleScreen);
	m_background_sprite.setTexture(texture);

	const Player& player = *context.player;
	float startY = 150.f;

	for (int i = 0; i < static_cast<int>(PlayerAction::kActionCount); i++)
	{
		auto action = static_cast<PlayerAction>(i);
		auto actionLabel = CreateActionLabel(action);
		actionLabel->setPosition(50.f, startY);
		auto assignButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
		assignButton->SetText(KeyCodeToString(player.GetAssignedKey(action)));
		assignButton->setPosition(200.f, startY);
		assignButton->SetToggle(true);
		assignButton->SetCallback([this, action, assignButton]()
		{
				m_current_keybind_listen.first = action;
				m_current_keybind_listen.second = assignButton;
		});

		m_gui_container.Pack(actionLabel);
		m_gui_container.Pack(assignButton);

		startY += 50.f;
	}
}

void SettingsState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());
	window.draw(m_background_sprite);
	window.draw(m_gui_container);
}

bool SettingsState::Update(sf::Time dt)
{
	return false;
}

bool SettingsState::HandleEvent(const sf::Event& event)
{
	if(event.type == sf::Event::KeyReleased)
	{
		if (m_current_keybind_listen.second != nullptr)
		{
			if (event.key.code != sf::Keyboard::Escape && event.key.code != sf::Keyboard::Enter)
			{
				GetContext().player->AssignKey(m_current_keybind_listen.first, event.key.code);
				m_current_keybind_listen.second->SetText(KeyCodeToString(event.key.code));
			}

			m_current_keybind_listen.second->Deactivate();
			m_current_keybind_listen.second = nullptr;

			return false;
		}

		if(event.key.code == sf::Keyboard::Escape)
		{
			RequestStackPop();
		}
	}

	m_gui_container.HandleEvent(event);
	return false;
}

GUI::Label::Ptr SettingsState::CreateActionLabel(PlayerAction player_action) const
{
	switch (player_action)
	{
	case PlayerAction::kMoveDown:
		return std::make_shared<GUI::Label>("Move Down", *GetContext().fonts);
	case PlayerAction::kMoveUp:
		return std::make_shared<GUI::Label>("Move Up", *GetContext().fonts);
	case PlayerAction::kMoveLeft:
		return std::make_shared<GUI::Label>("Move Left", *GetContext().fonts);
	case PlayerAction::kMoveRight:
		return std::make_shared<GUI::Label>("Move Right", *GetContext().fonts);
	default:
		return nullptr;
	}
}

std::string SettingsState::KeyCodeToString(int keyCode) const
{
	if (keyCode >= sf::Keyboard::A && keyCode <= sf::Keyboard::Z)
	{
		const char chr = static_cast<char>(keyCode - sf::Keyboard::A + 'a');
		return std::string(1, chr);
	}

	return std::to_string(keyCode);
}
