#include "Forms/Forms.h"
#include "Screen/Screen.h"

namespace Forms
{
	bool isCollidingWithRectangle(Circle circle, Rectangle rect)
	{
		if (circle.position.x - circle.radius > rect.position.x + rect.width / 2 ||
			circle.position.x + circle.radius < rect.position.x - rect.width / 2 ||
			circle.position.y - circle.radius > rect.position.y + rect.height / 2 ||
			circle.position.y + circle.radius < rect.position.y - rect.height / 2)
		{
			return false;
		}
		return true;
	}

	Math::Vector2 getHowMuchEntered(Circle circle, Rectangle rect)
	{
		Math::Vector2 entered{ 0,0 };

		if (circle.position.x < rect.position.x - rect.width / 2)
		{
			entered.x -= (circle.position.x + circle.radius) - (rect.position.x - rect.width / 2);
		}
		if (circle.position.x > rect.position.x + rect.width / 2)
		{
			entered.x += (rect.position.x + rect.width / 2) - (circle.position.x - circle.radius);
		}
		if (circle.position.y < rect.position.y - rect.height / 2)
		{
			entered.y -= (circle.position.y + circle.radius) - (rect.position.y - rect.height / 2);
		}
		if (circle.position.y > rect.position.y + rect.height / 2)
		{
			entered.y += (rect.position.y + rect.height / 2) - (circle.position.y - circle.radius);
		}

		return entered;
	}

	Math::Vector2 getHowMuchLeft(Circle body, Rectangle playableArea)
	{
		Math::Vector2 left{ 0,0 };

		if (body.position.x + body.radius >= playableArea.position.x + playableArea.width / 2)
		{
			left.x -= (body.position.x + body.radius) - (playableArea.position.x + playableArea.width / 2);
		}
		else if (body.position.x - body.radius <= playableArea.position.x - playableArea.width / 2)
		{
			left.x += -((playableArea.position.x - playableArea.width / 2) - body.position.x - body.radius);
		}
		else if (body.position.y + body.radius >= playableArea.position.y + playableArea.height / 2)
		{
			left.y -= (body.position.y + body.radius) - (playableArea.position.y + playableArea.height / 2);
		}
		else if (body.position.y - body.radius <= playableArea.position.y - playableArea.height / 2)
		{
			left.y += -((playableArea.position.y - playableArea.height / 2)-body.position.y - body.radius);
		}

		return left;
	}
	
	Math::Vector2 getHowMuchLeft(Rectangle body, Rectangle playableArea)
	{
		Math::Vector2 left{};

		if (body.position.x + body.width/2 >= playableArea.position.x + playableArea.width / 2)
		{
			left.x -= (body.position.x + body.width/2) - (playableArea.position.x + playableArea.width / 2);
		}
		else if (body.position.x - body.width/2 <= playableArea.position.x - playableArea.width / 2)
		{
			left.x += -((playableArea.position.x - playableArea.width / 2) - body.position.x - body.width/2);
		}

		return left;
	}

	bool isInsideRectangle(Math::Vector2 point, Rectangle rectangle)
	{
		if (point.x < rectangle.position.x - rectangle.width / 2
			|| point.x > rectangle.position.x + rectangle.width / 2
			|| point.y < rectangle.position.y - rectangle.height / 2
			|| point.y > rectangle.position.y + rectangle.height / 2)
		{
			return false;
		}

		return true;
	}

	void place(Forms::Circle& body, Math::Vector2 pos)
	{
		body.position = pos;
	}
}