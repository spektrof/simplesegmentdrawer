#pragma once

#include <glm/glm.hpp>

enum EventType
{
	NONE,
	NEWSEGMENT,
	NEWWIDTHORUNIT
};

struct Request
{
	EventType _event;
	glm::vec2 first, second;
	float width;
	int units;
	Request(const EventType e = EventType(0), const glm::vec2& f = glm::vec2(0,0), const glm::vec2& s = glm::vec2(0, 0), const float& w = 4.0f, const int& u = 1 ) : _event(e), first(f), second(s),width(w),units(u) {}
};