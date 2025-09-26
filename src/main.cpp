#include "sl.h"
#include "screen.h"

void setBackColor(colorsName colorName)
{
	
	//slSetBackColor[]
	//colors[]
}

int main()
{
	// set up our window and a few resources we need
	slWindow(screen::height, screen::width, screen::windowName.c_str(), screen::isFullScreen);

	while (!slShouldClose())
	{
		
		//const Rgba red = colors[colorsName::RED];
		//slSetBackColor(red.r, red);


		// smaller subtext
		slSetFontSize(14);
		slText(200, 220, "Sprites, text, sound, input, and more!");
		slLine(48, 210, 352, 210);

		slRender();
	}


	slClose();
	return 0;
}