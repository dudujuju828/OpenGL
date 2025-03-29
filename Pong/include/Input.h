
#pragma once

#include "Window.h"

#include <unordered_map>

enum class Key {
	W,
	A,
	S,
	D,
	Up,
	Down,
	Left,
	Right
};

class Input {
private:
	std::unordered_map<Key,bool> m_key_map;

public:
	Input();
	~Input();

	void pollEvents(const Window &window);

	bool isPressed(Key key) const;
};
