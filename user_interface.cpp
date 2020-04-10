#include "user_interface.h"

bool user_interface::CheckValidID(uint32 ElementID)
{
	bool Result = true;

	if(ElementID > MAX_UI_ELEMENTS || ElementID < 0)
	{
		Result = false;
	}

	// TODO(Cristoffer): Debug message.

	return Result;
}

bool user_interface::CheckValidStringID(uint32 ElementID, uint32 TextID)
{
	bool Result = true;

	if(ElementID > MAX_UI_ELEMENTS || ElementID < 0)
	{
		Result = false;
	}

	if(Result)
	{
		if(TextID > MAX_TEXT_ELEMENTS || TextID < 0)
		{
			Result = false;
		}
	}

	// TODO(Cristoffer): Debug message.

	return Result;
}

user_interface::user_interface() :
	ElementCount(0)
{
	ThreadWorkID = threading::GetInstance().GenerateUniqueWorkID();

	// NOTE(Cristoffer): Pre-allocate everything with reasonable default values,
	// so that everything looks decent even if nothing is changed.

	for(uint32 ElementID = 0; ElementID < MAX_UI_ELEMENTS; ElementID++)
	{
		Element[ElementID] = new element;
		Element[ElementID]->Anchor = TOP_LEFT;
		Element[ElementID]->Width = 0.0f;
		Element[ElementID]->Height = 0.0f;
		Element[ElementID]->BackgroundColor = { 9.0f, 9.0f, 9.0f, 0.8f };
		Element[ElementID]->TextPositionX = Element[ElementID]->OffsetX + Element[ElementID]->Margin;
		Element[ElementID]->TextPositionY = Element[ElementID]->OffsetY + Element[ElementID]->Margin;
		
		Element[ElementID]->Margin = 0.0f;
		Element[ElementID]->OffsetX = 0.0f;
		Element[ElementID]->OffsetY = 0.0f;
		Element[ElementID]->TextCount = 0;
		Element[ElementID]->AdjustWidthToText = false;
		Element[ElementID]->AdjustHeightToText = true;
		Element[ElementID]->IsHighlighted = false;
		Element[ElementID]->IsHidden = false;

		Element[ElementID]->MegaString.clear();

		for(uint32 TextID = 0; TextID < MAX_TEXT_ELEMENTS; TextID++)
		{
			Element[ElementID]->Text[TextID] = new text;

			Element[ElementID]->Text[TextID]->String = "NULL";
			Element[ElementID]->Text[TextID]->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
			Element[ElementID]->Text[TextID]->Size = 12;
			Element[ElementID]->Text[TextID]->TextMeasurementWidth = 0.0f;
			Element[ElementID]->Text[TextID]->TextMeasurementHeight = 0.0f;
		}
	}

	DXTKSpriteBatch = std::make_unique<SpriteBatch>(global_device_info::Context);
	DXTKSpriteFont = std::make_unique<SpriteFont>(global_device_info::Device, L"data/bahnschrift_12.spritefont");

	// NOTE(Cristoffer): Pre-allocate gpu memory since we have a fixed amount of UI to update
	// every frame.

	uint32 QuadCount = 0;

	for(uint32 ID = 0; ID < MAX_UI_ELEMENTS; ID++)
	{
		ui_vertex Vertex[4];

		Vertices.push_back(Vertex[0]);
		Vertices.push_back(Vertex[1]);
		Vertices.push_back(Vertex[2]);
		Vertices.push_back(Vertex[3]);

		QuadCount++;
	}

	for(uint32 Index = 0; Index < QuadCount; Index++)
	{
		Indices.push_back(0 + (Index * 4));
		Indices.push_back(1 + (Index * 4));
		Indices.push_back(2 + (Index * 4));
		Indices.push_back(1 + (Index * 4));
		Indices.push_back(3 + (Index * 4));
		Indices.push_back(2 + (Index * 4));
	}

	Shader = new shader(L"user_interface_vs.cso", L"user_interface_ps.cso");
	Shader->AddInputElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT);
	Shader->AddInputElement("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	Shader->AddInputElement("ISHIGHLIGHTED", DXGI_FORMAT_R32_FLOAT);
	Shader->CommitInputElements();

	VertexBuffer = new vertex_buffer(Vertices.data(), sizeof(ui_vertex), (uint32)Vertices.size(), DYNAMIC);
	VertexBuffer->AddIndexBuffer(Indices.data(), sizeof(uint16), (uint32)Indices.size());

	ConstantBuffer = nullptr;
	Texture = nullptr;
}

user_interface::~user_interface()
{
	delete[] *Element;
}

uint32 user_interface::CreateElement(SCREEN_ANCHOR Anchor, real32 Width, real32 Height)
{
	uint32 ID = ElementCount;

	if(ID + 1 > MAX_UI_ELEMENTS)
	{
		return ID;
	}

	ElementCount++;

	Element[ID]->Anchor = Anchor;
	Element[ID]->Width = Width;
	Element[ID]->Height = Height;

	return ID;
}

uint32 user_interface::AddNewText(uint32 ElementID, std::string Text)
{
	uint32 TextID = Element[ElementID]->TextCount;

	if(TextID + 1 > MAX_TEXT_ELEMENTS)
	{
		return TextID;
	}

	Element[ElementID]->TextCount++;

	Element[ElementID]->Text[TextID]->String = Text;

	// NOTE(Cristoffer): Since newline is measured as zero height, need to adjust it here, so it
	// gets accounted for when adjusting element heights.
	if(Text.at(0) == '\n')
	{
		Element[ElementID]->Text[TextID]->TextMeasurementWidth = 0.0f;
		Element[ElementID]->Text[TextID]->TextMeasurementHeight = XMVectorGetY(DXTKSpriteFont->MeasureString("n"));

		return TextID;
	}

	Element[ElementID]->Text[TextID]->TextMeasurementWidth = XMVectorGetX(DXTKSpriteFont->MeasureString(Text.c_str()));
	Element[ElementID]->Text[TextID]->TextMeasurementHeight = XMVectorGetY(DXTKSpriteFont->MeasureString(Text.c_str()));
	
	return TextID;
}

void user_interface::UpdateText(uint32 ElementID, uint32 TextID, std::string Text)
{
	if(!CheckValidStringID(ElementID, TextID)) return;

	Element[ElementID]->Text[TextID]->TextMeasurementWidth = XMVectorGetX(DXTKSpriteFont->MeasureString(Text.c_str()));
	Element[ElementID]->Text[TextID]->TextMeasurementHeight = XMVectorGetY(DXTKSpriteFont->MeasureString(Text.c_str()));

	Element[ElementID]->Text[TextID]->String = Text;
}

void user_interface::SetMargin(uint32 ElementID, real32 Margin)
{
	if(!CheckValidID(ElementID)) return;

	Element[ElementID]->Margin = Margin;
}

void user_interface::SetOffset(uint32 ElementID, real32 OffsetX, real32 OffsetY)
{
	if(!CheckValidID(ElementID)) return;

	Element[ElementID]->OffsetX = OffsetX;
	Element[ElementID]->OffsetY = OffsetY;
}

void user_interface::SetTextSize(uint32 ElementID, uint32 TextID, uint16 Size)
{
	if(!CheckValidID(ElementID)) return;

	Element[ElementID]->Text[TextID]->Size = Size;
}

void user_interface::SetTextColor(uint32 ElementID, uint32 TextID, color Color)
{
	if(!CheckValidID(ElementID)) return;

	Element[ElementID]->Text[TextID]->Color = Color;
}

void user_interface::SetBackgroundColor(uint32 ElementID, color Color)
{
	if(!CheckValidID(ElementID)) return;

	Element[ElementID]->BackgroundColor = Color;
}

void user_interface::SetAdjustWidthToText(uint32 ElementID, bool Adjust)
{
	if(!CheckValidID(ElementID)) return;

	Element[ElementID]->AdjustWidthToText = Adjust;
}

void user_interface::SetAdjustHeightToText(uint32 ElementID, bool Adjust)
{
	if(!CheckValidID(ElementID)) return;

	Element[ElementID]->AdjustHeightToText = Adjust;
}

void user_interface::SetHighlight(uint32 ElementID, bool Set)
{
	if(!CheckValidID(ElementID)) return;

	Element[ElementID]->IsHighlighted = Set;
}

void user_interface::SetHidden(uint32 ElementID, bool Set)
{
	if(!CheckValidID(ElementID)) return;

	Element[ElementID]->IsHidden = Set;
}

uint32 user_interface::GetElementCount()
{
	return ElementCount;
}

void user_interface::CalculateTextPositions()
{
	// NOTE(Cristoffer): Calculate all the text position and adjust the elements.
	for(uint32 EID = 0; EID < ElementCount; EID++)
	{
		// NOTE(Cristoffer): No point in processing the text if hidden.
		if(Element[EID]->IsHidden)
		{
			Element[EID]->MegaString.clear();
			continue;
		}

		// NOTE(Cristoffer): Calculate if line breaks are needed to fit in the element below.
		real32 ElementWidth = Element[EID]->Width - (2.0f * Element[EID]->Margin);
		real32 ElementHeight = Element[EID]->Height - (2.0f * Element[EID]->Margin);

		real32 NewHeight = 0.0f;
		real32 LongestStringWidth = 0.0f;

		Element[EID]->MegaString.clear();

		std::vector<std::string> Lines;

		for(uint32 TID = 0;
			TID < Element[EID]->TextCount;
			TID++)
		{
			std::string String = Element[EID]->Text[TID]->String;

			real32 StringWidth = Element[EID]->Text[TID]->TextMeasurementWidth;
			real32 StringHeight = Element[EID]->Text[TID]->TextMeasurementHeight;

			// NOTE(Cristoffer): If the string can't fit into the element, rearrange the string,
			// and put new lines where needed.
			if(StringWidth < ElementWidth)
			{
				NewHeight += StringHeight;
				Lines.push_back(String);
			}
			else if(StringWidth > ElementWidth && !Element[EID]->AdjustWidthToText)
			{
				std::string NewString;
				std::string Word;

				for(uint32 Index = 0;
					Index < String.size();
					Index++)
				{
					// NOTE(Cristoffer): Look at every character until we reach space.
					// Then measure current word and see if we need to line break.
					if(!isspace(String.at(Index)))
					{
						Word += String.at(Index);
					}
					else
					{
						real32 NewStringWidth = XMVectorGetX(DXTKSpriteFont->MeasureString(NewString.c_str()));
						real32 WordWidth = XMVectorGetX(DXTKSpriteFont->MeasureString(Word.c_str()));

						if(NewStringWidth + WordWidth < ElementWidth)
						{
							NewString += Word + ' ';
							Word.clear();
						}
						else
						{
							NewHeight += StringHeight;

							Lines.push_back(NewString);
							NewString.clear();

							NewString += Word + ' ';
							Word.clear();
						}
					}
				}

				NewHeight += StringHeight;

				NewString += Word + ' ';
				Lines.push_back(NewString);
			}
			else
			{
				// NOTE(Cristoffer): If stretching in width is allowed, just store all text
				// and measure which line is the longest.
				real32 StringWidth = XMVectorGetX(DXTKSpriteFont->MeasureString(String.c_str()));

				if(StringWidth > LongestStringWidth)
				{
					LongestStringWidth = StringWidth;
				}

				NewHeight += StringHeight;
				Lines.push_back(String);
			}
		}

		for(uint32 Index = 0;
			Index < Lines.size();
			Index++)
		{
			if(Lines.at(Index).at(0) == '\n')
			{
				Element[EID]->MegaString += Lines.at(Index);
			}
			else
			{
				Element[EID]->MegaString += Lines.at(Index) + '\n';
			}
		}

		if(NewHeight > ElementHeight)
		{
			Element[EID]->Height = NewHeight + (2.0f * Element[EID]->Margin);
		}

		if(Element[EID]->AdjustWidthToText)
		{
			Element[EID]->Width = LongestStringWidth + (2.0f * Element[EID]->Margin);
		}
	}

	// NOTE(Cristoffer): Calculate the actual screen position of text depending on anchors and offsets.
	for(uint32 EID = 0; EID < ElementCount; EID++)
	{
		real32 OffsetX = Element[EID]->OffsetX + Element[EID]->Margin;
		real32 OffsetY = Element[EID]->OffsetY + Element[EID]->Margin;
		real32 ScreenWidth = global_device_info::FrameBufferWidth;
		real32 ScreenHeight = global_device_info::FrameBufferHeight;
		real32 Width = Element[EID]->Width;
		real32 Height = Element[EID]->Height;

		if(Element[EID]->Anchor == TOP_MIDDLE)
		{
			Element[EID]->TextPositionX = (ScreenWidth / 2.0f) - (Width / 2.0f) + OffsetX;
			Element[EID]->TextPositionY = OffsetY;
		}
		else if(Element[EID]->Anchor == TOP_RIGHT)
		{
			Element[EID]->TextPositionX = ScreenWidth - Width;
			Element[EID]->TextPositionY = OffsetY;
		}
		else if(Element[EID]->Anchor == BOTTOM_LEFT)
		{
			real32 TextHeight = Element[EID]->Text[0]->TextMeasurementHeight;

			Element[EID]->TextPositionX = OffsetX;
			Element[EID]->TextPositionY = ScreenHeight - OffsetY - Height + TextHeight;
		}
		else if(Element[EID]->Anchor == BOTTOM_MIDDLE)
		{
			real32 TextHeight = Element[EID]->Text[0]->TextMeasurementHeight;

			Element[EID]->TextPositionX = (ScreenWidth / 2.0f) - (Width / 2.0f) + OffsetX;
			Element[EID]->TextPositionY = ScreenHeight - OffsetY - Height + TextHeight;
		}
		else if(Element[EID]->Anchor == BOTTOM_RIGHT)
		{
			real32 TextHeight = Element[EID]->Text[0]->TextMeasurementHeight;

			Element[EID]->TextPositionX = ScreenWidth - Width;
			Element[EID]->TextPositionY = ScreenHeight - OffsetY - Height + TextHeight;
		}
		else if(Element[EID]->Anchor == MIDDLE_LEFT)
		{
			real32 TextHeight = Element[EID]->Text[0]->TextMeasurementHeight;

			Element[EID]->TextPositionX = OffsetX;
			Element[EID]->TextPositionY = (ScreenHeight / 2.0f) - (Height / 2.0f) - OffsetX + TextHeight;
		}
		else if(Element[EID]->Anchor == MIDDLE_MIDDLE)
		{
			Element[EID]->TextPositionX = (ScreenWidth / 2.0f) - (Width / 2.0f) + OffsetX;
			Element[EID]->TextPositionY = (ScreenHeight / 2.0f) - (Height / 2.0f) + OffsetX;
		}
		else if(Element[EID]->Anchor == MIDDLE_RIGHT)
		{
			real32 TextHeight = Element[EID]->Text[0]->TextMeasurementHeight;

			Element[EID]->TextPositionX = ScreenWidth - Width;
			Element[EID]->TextPositionY = (ScreenHeight / 2.0f) - (Height / 2.0f) - OffsetX + TextHeight;
		}
		else if(Element[EID]->Anchor == MOUSE)
		{
			Element[EID]->TextPositionX = OffsetX + GetMouseX();
			Element[EID]->TextPositionY = OffsetY + GetMouseY();
		}
		else
		{
			Element[EID]->TextPositionX = OffsetX;
			Element[EID]->TextPositionY = OffsetY;
		}
	}
}

void user_interface::CalculateVertices()
{
	uint32 QuadCount = 0;

	for(uint32 ID = 0; ID < ElementCount; ID++)
	{
		ui_vertex Vertex[4];

		real32 ScreenWidth = global_device_info::FrameBufferWidth;
		real32 ScreenHeight = global_device_info::FrameBufferHeight;

		real32 Width = Element[ID]->Width;
		real32 Height = Element[ID]->Height;

		if(Element[ID]->IsHighlighted)
		{
			Vertex[0].IsHighlighted = 1.0f;
			Vertex[1].IsHighlighted = 1.0f;
			Vertex[2].IsHighlighted = 1.0f;
			Vertex[3].IsHighlighted = 1.0f;
		}
		else
		{
			Vertex[0].IsHighlighted = 0.0f;
			Vertex[1].IsHighlighted = 0.0f;
			Vertex[2].IsHighlighted = 0.0f;
			Vertex[3].IsHighlighted = 0.0f;
		}

		if(Element[ID]->IsHidden)
		{
			Vertex[0].Color = { 0.0f, 0.0f, 0.0f, 0.0f };
			Vertex[1].Color = { 0.0f, 0.0f, 0.0f, 0.0f };
			Vertex[2].Color = { 0.0f, 0.0f, 0.0f, 0.0f };
			Vertex[3].Color = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
		else
		{
			Vertex[0].Color = Element[ID]->BackgroundColor;
			Vertex[1].Color = Element[ID]->BackgroundColor;
			Vertex[2].Color = Element[ID]->BackgroundColor;
			Vertex[3].Color = Element[ID]->BackgroundColor;
		}

		real32 OffsetX;
		real32 OffsetY;
		real32 LeftX;
		real32 RightX;
		real32 TopY;
		real32 BottomY;

		// NOTE(Cristoffer): Convert from screen space into -1:1 space depending on given anchor.
		if(Element[ID]->Anchor == TOP_MIDDLE)
		{
			OffsetX = (2.0f * Element[ID]->OffsetX) / ScreenWidth;
			OffsetY = -(2.0f * Element[ID]->OffsetY) / ScreenHeight;

			LeftX = -1.0f * (Width / (ScreenWidth));
			RightX = Width / ScreenWidth;
			TopY = 1.0f;
			BottomY = 1.0f - (2.0f * Height) / ScreenHeight;
		}
		else if(Element[ID]->Anchor == TOP_RIGHT)
		{
			OffsetX = -1.0f * (2.0f * Element[ID]->OffsetX) / ScreenWidth;
			OffsetY = -(2.0f * Element[ID]->OffsetY) / ScreenHeight;

			LeftX = -1.0f * (2.0f * Width / ScreenWidth) + 1.0f;
			RightX = 1.0f;
			TopY = 1.0f;
			BottomY = 1.0f - (2.0f * Height) / ScreenHeight;
		}
		else if(Element[ID]->Anchor == BOTTOM_LEFT)
		{
			OffsetX = (2.0f * Element[ID]->OffsetX) / ScreenWidth;
			OffsetY = (2.0f * Element[ID]->OffsetY) / ScreenHeight;

			LeftX = -1.0f;
			RightX = (2.0f * Width) / ScreenWidth - 1.0f;
			TopY = (2.0f * Height) / ScreenHeight - 1.0f;
			BottomY = -1.0f;
		}
		else if(Element[ID]->Anchor == BOTTOM_MIDDLE)
		{
			OffsetX = (2.0f * Element[ID]->OffsetX) / ScreenWidth;
			OffsetY = (2.0f * Element[ID]->OffsetY) / ScreenHeight;

			LeftX = -1.0f * (Width / (ScreenWidth));
			RightX = Width / ScreenWidth;
			TopY = (2.0f * Height) / ScreenHeight - 1.0f;
			BottomY = -1.0f;
		}
		else if(Element[ID]->Anchor == BOTTOM_RIGHT)
		{
			OffsetX = -(2.0f * Element[ID]->OffsetX) / ScreenWidth;
			OffsetY = (2.0f * Element[ID]->OffsetY) / ScreenHeight;

			LeftX = -1.0f * (2.0f * Width / ScreenWidth) + 1.0f;
			RightX = 1.0f;
			TopY = (2.0f * Height) / ScreenHeight - 1.0f;
			BottomY = -1.0f;
		}
		else if(Element[ID]->Anchor == MIDDLE_LEFT)
		{
			OffsetX = (2.0f * Element[ID]->OffsetX) / ScreenWidth;
			OffsetY = (2.0f * Element[ID]->OffsetY) / ScreenHeight;

			LeftX = -1.0f;
			RightX = (2.0f * Width) / ScreenWidth - 1.0f;
			TopY = Height / ScreenHeight;
			BottomY = -1.0f * (Height / (ScreenHeight));
		}
		else if(Element[ID]->Anchor == MIDDLE_MIDDLE)
		{
			OffsetX = (2.0f * Element[ID]->OffsetX) / ScreenWidth;
			OffsetY = (2.0f * Element[ID]->OffsetY) / ScreenHeight;

			LeftX = -1.0f * (Width / (ScreenWidth));
			RightX = Width / ScreenWidth;
			TopY = Height / ScreenHeight;
			BottomY = -1.0f * (Height / (ScreenHeight));
		}
		else if(Element[ID]->Anchor == MIDDLE_RIGHT)
		{
			OffsetX = -(2.0f * Element[ID]->OffsetX) / ScreenWidth;
			OffsetY = (2.0f * Element[ID]->OffsetY) / ScreenHeight;

			LeftX = -1.0f * (2.0f * Width / ScreenWidth) + 1.0f;
			RightX = 1.0f;
			TopY = Height / ScreenHeight;
			BottomY = -1.0f * (Height / (ScreenHeight));
		}
		else if(Element[ID]->Anchor == MOUSE)
		{
			real32 MouseX = 1.0f * (2.0f * GetMouseX() / ScreenWidth);
			real32 MouseY = -(2.0f * GetMouseY()) / ScreenHeight;

			OffsetX = (2.0f * Element[ID]->OffsetX) / ScreenWidth;
			OffsetY = -(2.0f * Element[ID]->OffsetY) / ScreenHeight;

			LeftX = -1.0f + MouseX;
			RightX = (2.0f * Width) / ScreenWidth - 1.0f + MouseX;
			TopY = 1.0f + MouseY;
			BottomY = 1.0f - (2.0f * Height) / ScreenHeight + MouseY;
		}
		else
		{
			OffsetX = (2.0f * Element[ID]->OffsetX) / ScreenWidth;
			OffsetY = -(2.0f * Element[ID]->OffsetY) / ScreenHeight;

			LeftX = -1.0f;
			RightX = (2.0f * Width) / ScreenWidth - 1.0f;
			TopY = 1.0f;
			BottomY = 1.0f - (2.0f * Height) / ScreenHeight;
		}

		Vertex[0].Position.X = LeftX + OffsetX;
		Vertex[0].Position.Y = BottomY + OffsetY;

		Vertex[1].Position.X = LeftX + OffsetX;
		Vertex[1].Position.Y = TopY + OffsetY;

		Vertex[2].Position.X = RightX + OffsetX;
		Vertex[2].Position.Y = BottomY + OffsetY;

		Vertex[3].Position.X = RightX + OffsetX;
		Vertex[3].Position.Y = TopY + OffsetY;

		Vertices.at((ID * 4) + 0) = Vertex[0];
		Vertices.at((ID * 4) + 1) = Vertex[1];
		Vertices.at((ID * 4) + 2) = Vertex[2];
		Vertices.at((ID * 4) + 3) = Vertex[3];

		QuadCount++;
	}
}

void user_interface::BuildElements()
{
	if(USE_MULTI_THREADING)
	{
		if(threading::GetInstance().WorkDone(ThreadWorkID))
		{
			threading::GetInstance().AddBackgroundWork(ThreadWorkID, [&]
			{
				// NOTE(Cristoffer): Updates all the interface elements.
				// Calculates new vertex positions based on text, since the text
				// may stretch out elements etc.
				CalculateTextPositions();
				CalculateVertices();

				UpdateDraw = true;
			});
		}
	}
	else
	{
		CalculateTextPositions();
		CalculateVertices();
	}
}

void user_interface::Draw(camera &Camera)
{
	if(UpdateDraw)
	{
		VertexBuffer->UpdateDynamicBuffer(Vertices.data(), sizeof(ui_vertex), (uint32)Vertices.size());
		UpdateDraw = false;
	}
	

	VertexBuffer->Bind();
	Shader->Bind();

	global_device_info::Context->DrawIndexed(VertexBuffer->GetIndexCount(), 0, 0);
}

void user_interface::DrawStrings()
{
	// NOTE(Cristoffer): Since all calculations are already done, this should be really
	// fast now, iterate through the data.

	DXTKSpriteBatch->Begin();

	for(uint32 ID = 0; ID < ElementCount; ID++)
	{
		XMVECTOR Color = Colors::White;
		
		DXTKSpriteFont->DrawString(DXTKSpriteBatch.get(), Element[ID]->MegaString.c_str(), XMFLOAT2(Element[ID]->TextPositionX, Element[ID]->TextPositionY), Color);
	}

	DXTKSpriteBatch->End();
}