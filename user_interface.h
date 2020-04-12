#pragma once

#include "common.h"
#include "drawable.h"
#include "threading.h"
#include "mouse.h"
#include "global_device_info.h"
#include "math.h"

#include "external/SimpleMath.h"
#include "external/SpriteBatch.h"
#include "external/SpriteFont.h"

#include <string>
#include <vector>

#define MAX_UI_ELEMENTS 50
#define MAX_TEXT_ELEMENTS 25

enum class screen_anchor
{
	TOP_LEFT, TOP_MIDDLE, TOP_RIGHT,
	MIDDLE_LEFT, MIDDLE_MIDDLE, MIDDLE_RIGHT,
	BOTTOM_LEFT, BOTTOM_MIDDLE, BOTTOM_RIGHT,
	MOUSE,
};

struct text
{
	std::string String;
	vec4		Color;
	uint16		Size;
	real32		TextMeasurementWidth;
	real32		TextMeasurementHeight;
};

struct element
{
	screen_anchor Anchor;

	real32 Width;
	real32 Height;
	real32 OffsetX;
	real32 OffsetY;
	real32 Margin;
	real32 TextPositionX;
	real32 TextPositionY;
	vec4   BackgroundColor;
	
	bool AdjustWidthToText;
	bool AdjustHeightToText;
	bool IsHighlighted;
	bool IsHidden;

	text   *Text[MAX_TEXT_ELEMENTS];
	uint32 TextCount;

	std::string MegaString;

	~element()
	{
		for(uint32 Index = 0;
			Index < MAX_TEXT_ELEMENTS;
			Index++)
		{
			delete[] Text[Index];
		}
	}
};

struct ui_vertex
{
	vec3	Position;
	vec4	Color;
	real32	IsHighlighted = 0.0f;
};

class user_interface : public drawable
{
	private:

	std::unique_ptr<SpriteBatch> DXTKSpriteBatch;
	std::unique_ptr<SpriteFont> DXTKSpriteFont;

	std::vector<ui_vertex> Vertices;
	std::vector<uint32> Indices;

	element *Element[MAX_UI_ELEMENTS];
	uint32 ElementCount;

	bool CheckValidID(uint32 ElementID);
	bool CheckValidStringID(uint32 ElementID, uint32 StringID);
	void CalculateTextPositions();
	void CalculateVertices();

	public:

	work_id ThreadWorkID;

	user_interface();
	~user_interface();

	uint32 CreateElement(screen_anchor Anchor, real32 Width, real32 Height);
	void SetMargin(uint32 ElementID, real32 Margin);
	void SetOffset(uint32 ElementID, real32 OffsetX, real32 OffsetY);
	void SetBackgroundColor(uint32 ElementID, vec4 Color);
	void SetAdjustWidthToText(uint32 ElementID, bool Adjust);
	void SetAdjustHeightToText(uint32 ElementID, bool Adjust);
	void SetHighlight(uint32 ElementID, bool Set);
	void SetHidden(uint32 ElementID, bool Set);

	uint32 AddNewText(uint32 ElementID, std::string Text);
	void UpdateText(uint32 ElementID, uint32 TextID, std::string Text);
	void SetTextSize(uint32 ElementID, uint32 TextID, uint16 Size);
	void SetTextColor(uint32 ElementID, uint32 TextID, vec4 Color);

	uint32 GetElementCount();

	void BuildElements();

	void Draw(camera &Camera) override;
	void DrawStrings();
};