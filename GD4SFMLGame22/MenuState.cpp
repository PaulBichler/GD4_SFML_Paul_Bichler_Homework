#include "MenuState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceHolder.hpp"
#include "Utility.hpp"

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context),
	m_options_index(0)
{
	const sf::Texture& texture = context.textures->Get(Textures::kTitleScreen);
	sf::Font& font = context.fonts->Get(Fonts::kMain);

	m_background_sprite.setTexture(texture);

	//A simple menu
	sf::Text play_option;
	play_option.setFont(font);
	play_option.setString("Play");
	Utility::CenterOrigin(play_option);
	play_option.setPosition(context.window->getView().getSize() / 2.f);
	m_options.emplace_back(play_option);

	sf::Text exit_option;
	exit_option.setFont(font);
	exit_option.setString("Exit");
	Utility::CenterOrigin(exit_option);
	exit_option.setPosition(play_option.getPosition() + sf::Vector2f(0, 30.f));
	m_options.emplace_back(exit_option);

	UpdateOptionText();
}

void MenuState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());
	window.draw(m_background_sprite);

	for (const sf::Text& text : m_options)
	{
		window.draw(text);
	}
}

bool MenuState::Update(sf::Time dt)
{
	return false;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if(event.key.code == sf::Keyboard::Return)
	{
		if(m_options_index == Options::Play)
		{
			RequestStackPop();
			RequestStackPush(StateID::kGame);
		}
		else if(m_options_index == Options::Exit)
		{
			RequestStackPop();
		}
	}
	else if (event.key.code == sf::Keyboard::Up)
	{
		m_options_index = (m_options_index == 0) ? m_options.size() - 1 : m_options_index - 1;
		UpdateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		m_options_index = (m_options_index == m_options.size() - 1) ? 0 : m_options_index + 1;
		UpdateOptionText();
	}

	return false;
}

void MenuState::UpdateOptionText()
{
	if (m_options.empty())
		return;

	for(sf::Text& text : m_options)
	{
		text.setFillColor(sf::Color::White);
	}

	m_options[m_options_index].setFillColor(sf::Color::Red);
}
