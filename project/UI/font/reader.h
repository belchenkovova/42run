#pragma once

#include "UI/namespace.h"

#include "UI/font/font.h"
#include "UI/font/manager.h"

class				UI::font::reader
{
public :
					reader() = default;
	virtual			~reader() = default;

protected :

//					Font
	[[nodiscard]]
	shared<symbol>	find_symbol(const shared<UI::font::font> &font, char task) const
	{
		return (font->find_symbol(task));
	}

//					Symbol
	[[nodiscard]]
	ivec2			size(const shared<UI::font::symbol> &symbol) const
	{
		return (symbol->size);
	}

	[[nodiscard]]
	ivec2			bearing(const shared<UI::font::symbol> &symbol) const
	{
		return (symbol->bearing);
	}

	[[nodiscard]]
	int				advance(const shared<UI::font::symbol> &symbol) const
	{
		return (symbol->advance);
	}

	[[nodiscard]]
	auto			instance(const shared<UI::font::symbol> &symbol) const
	{
		return (symbol->instance);
	}
};


