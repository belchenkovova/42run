#pragma once

#include "UI/namespace.h"

#include "UI/rectangle/rectangle.h"

class				UI::font::symbol :
						public UI::rectangle::rectangle
{
	friend class	UI::font::font;
	friend class	UI::font::renderer;
	friend class	UI::font::reader;

public :
					symbol(FT_Face &face);
					~symbol() = default;
private :

	shared<font>	font;

	ivec2			size;
	ivec2			bearing;
	int				advance;
};


