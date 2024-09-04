#pragma once

enum ColorName
{
	BLACK,
	GREY,
	WHITE,
	ORANGE
};

struct Col
{
	float r,g,b;
};

const Col& GetColor(ColorName name);
void PaletteClearColor3f(ColorName name);
void PaletteColor3f(ColorName name);
void PaletteLerpColor3f(ColorName from, float t, ColorName to);
void PaletteColor4f(ColorName name, float alpha);
