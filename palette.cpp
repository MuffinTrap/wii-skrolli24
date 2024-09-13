#include "palette.h"
#include <mgdl/mgdl-opengl.h>
#include <mgdl/mgdl-util.h>

// Linear interpolation
static float lerp(float t, float a, float b) {
    return a + t * (b - a);
}

static Col Black = {0.133f, 0.137f, 0.137f};
static Col Grey = {0.612f, 0.616f, 0.612f};
static Col White = {0.941f, 0.965f, 0.941f};
static Col Orange = {0.941f, 0.502f, 0.137f};
static Col SkyBlue = {162.0f/255.f, 213.0f/255.0f, 229.0f/255.0f};
static Col WallGreen = {235.0f/255.0f, 1.0f, 168.0f/255.0f};

const Col& GetColor(ColorName name)
{
	switch(name)
	{
		case BLACK: return Black;
			break;
		case GREY: return Grey;
			break;
		case WHITE: return White;
			break;
		case ORANGE: return Orange;
			break;
		case SKYBLUE: return SkyBlue;
			break;
		case WALLGREEN: return WallGreen;
			break;
		default: return White;
		break;
	};
}

void PaletteClearColor3f ( ColorName name )
{
	const Col &c = GetColor(name);
	glClearColor(c.r, c.g, c.b, 0.0f);
}

void PaletteColor3f ( ColorName name )
{
	const Col &c = GetColor(name);
	glColor3f(c.r, c.g, c.b);
}

void PaletteLerpColor3f(ColorName from, float t, ColorName to)
{
	t = gdl::clampF(t, 0.0f, 1.0f);
	const Col &a = GetColor(from);
	const Col &b = GetColor(to);
	glColor3f(
		lerp(t, a.r, b.r),
		lerp(t, a.g, b.g),
		lerp(t, a.b, b.b)
	);
}

void PaletteColor4f ( ColorName name, float alpha)
{
	const Col &c = GetColor(name);
	glColor4f(c.r, c.g, c.b, alpha);
}
