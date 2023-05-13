#include "pch.h"

#define _ARRAYSIZE(_ARR) ((int)(sizeof(_ARR) / sizeof(*(_ARR))))

void Console::log(const char* text, ...)
{
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, _ARRAYSIZE(buf), text, args);
	buf[_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	__log(buf);
}

void Console::warn(const char* text, ...) {
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, _ARRAYSIZE(buf), text, args);
	buf[_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	__warn(buf);
}

void Console::err(const char* text, ...) {
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, _ARRAYSIZE(buf), text, args);
	buf[_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	__err(buf);
}

void Console::dbg(const char* text, ...) {
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, _ARRAYSIZE(buf), text, args);
	buf[_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	__dbg(buf);
}

void Console::info(const char* text, ...) {
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, _ARRAYSIZE(buf), text, args);
	buf[_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);

	__info(buf);
}

float GameObject::getDistance(GameObject* other)
{
	return other ? getPosition().distance(other->getPosition()) : 0.f;
}

float GameObject::getDistance(const Vec3& pos)
{
	return getPosition().distance(pos);
}

