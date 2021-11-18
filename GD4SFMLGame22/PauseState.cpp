#include "PauseState.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context),
	m_options_index(0)
{
	const sf::Font& font = context.fonts->Get(Fonts::kMain);

	//A simple Pause menu
	sf::Text resume_option;
	resume_option.setFont(font);
	resume_option.setString("Resume");
	Utility::CenterOrigin(resume_option);
	resume_option.setPosition(context.window->getView().getSize() / 2.f);
	m_options.emplace_back(resume_option);

	sf::Text exit_option;
	exit_option.setFont(font);
	exit_option.setString("Exit To Main Menu");
	Utility::CenterOrigin(exit_option);
	exit_option.setPosition(resume_option.getPosition() + sf::Vector2f(0, 30.f));
	m_options.emplace_back(exit_option);

	UpdateOptionText();
}

void PauseState::Draw()
{
	sf::RenderWindow& window = *GetContext().window;
	window.setView(window.getDefaultView());

	for (const sf::Text& text : m_options)
		window.draw(text);
}

bool PauseState::Update(sf::Time dt)
{
	return false;
}

bool PauseState::HandleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (m_options_index == Options::kResume)
		{
			RequestStackPop();
		}
		else if (m_options_index == Options::kExit_Game)
		{
			//two pops because game state need to be popped too
			RequestStackPop();
			RequestStackPop();
			RequestStackPush(StateID::kMenu);
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

void PauseState::UpdateOptionText()
{
	if (m_options.empty())
		return;

	for (sf::Text& text : m_options)
	{
		text.setFillColor(sf::Color::White);
	}

	m_options[m_options_index].setFillColor(sf::Color::Red);
}
