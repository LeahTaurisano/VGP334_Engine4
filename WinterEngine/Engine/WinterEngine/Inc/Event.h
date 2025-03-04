#pragma once

namespace WinterEngine
{
	enum class EventType
	{
		None,
		SpacePressed,
		EnterPressed
	};

	class Event
	{
	public:
		Event() = default;
		Event(EventType et) : mEventType(et) {}
		virtual ~Event() = default;

		EventType GetType() const { return mEventType; }

	private:
		EventType mEventType = EventType::None;
	};

	class SpacePressedEvent : public Event
	{
	public:
		SpacePressedEvent() : Event(EventType::SpacePressed) {}

		// id
		// time
		// animation name...
		//include anything relevant here
	};

	class EnterPressedEvent : public Event
	{
	public:
		EnterPressedEvent() : Event(EventType::EnterPressed) {}
	};
}