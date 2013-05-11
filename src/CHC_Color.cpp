#include "CHC_Color.h"

int CHC_Color::changeToRGB()
{
	//r g b
	return r * 0xff0000 + g * 0xff00 + b * 0xff;
}