#include "MenuState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceHolder.hpp"
#include "Button.hpp"

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
{
	const sf::Texture& texture = context.textures->Get(Textures::kTitleScreen);
	m_background_sprite.setTexture(texture);

	const auto play_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	play_button->setPosition(100.f, 250.f);
	play_button->SetText("Play");
	play_button->SetCallback([this]()
	{
		RequestStackPop();
		RequestStackPush(StateID::kGame);
	});

	const auto settings_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	settings_button->setPosition(100.f, 300.f);
	settings_button->SetText("Settings");
	settings_button->SetCallback([this]()
	{
		RequestStackPush(StateID::kSettings);
	});

	const auto exit_button = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	exit_button->setPosition(100.f, 350.f);
	exit_button->SetText("Exit");
	exit_button->SetCallback([this]()
	{
		RequestStackPop();
	});

	m_gui_container.Pack(play_button);
	m_gui_container.Pack(settings_button);
	m_gui_container.Pack(exit_button);
}

void MenuState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());
	window.draw(m_background_sprite);
	window.draw(m_gui_container);
	
}

bool MenuState::Update(sf::Time dt)
{
	return true;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
	m_gui_container.HandleEvent(event);
	return false;
}

