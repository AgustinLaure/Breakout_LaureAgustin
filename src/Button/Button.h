#pragma once
#include "Text/Text.h"
#include "Forms/Forms.h"

namespace Button
{
	const float onHoverOpacity = 0.3f;
	const float onSelectOpacity = 0.5f;

	struct Button
	{
		Text::Text text;
		Forms::Rectangle area;
		bool isPressed = false;
	};
}

