#include "StateStack.hpp"

#include <cassert>

StateStack::StateStack(const State::Context context)
	: m_context(context)
{
}

void StateStack::Update(const sf::Time dt)
{
	for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
	{
		if(!(*itr)->Update(dt))
		{
			break;
		}
	}

	ApplyPendingChanges();
}

void StateStack::Draw()
{
	for (const State::Ptr& state : m_stack)
	{
		state->Draw();
	}
}

void StateStack::HandleEvent(const sf::Event& event)
{
	for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
	{
		if (!(*itr)->HandleEvent(event))
		{
			break;
		}
	}

	ApplyPendingChanges();
}

void StateStack::PushState(StateID state_id)
{
	m_pending_list.emplace_back(Action::Push, state_id);
}

void StateStack::PopState()
{
	m_pending_list.emplace_back(Action::Pop);
}

void StateStack::ClearStates()
{
	m_pending_list.emplace_back(Action::Clear);
}

bool StateStack::IsEmpty() const
{
	return m_stack.empty();
}

State::Ptr StateStack::CreateState(const StateID state_id)
{
	const auto found = m_state_factory.find(state_id);
	assert(found != m_state_factory.end());
	return found->second();
}

void StateStack::ApplyPendingChanges()
{
	for (const PendingChange change : m_pending_list)
	{
		switch (change.action)
		{
		case Action::Push:
			m_stack.emplace_back(CreateState(change.state_id));
			break;
		case Action::Pop:
			m_stack.pop_back();
			break;
		case Action::Clear:
			m_stack.clear();
			break;
		}
	}

	m_pending_list.clear();
}

StateStack::PendingChange::PendingChange(const Action action, const StateID state_id)
	: action(action),
	state_id(state_id)
{
}
