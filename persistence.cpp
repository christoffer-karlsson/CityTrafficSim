#include "persistence.h"

void persistence::SaveWorldMap(world *World)
{
	std::ofstream File;
	File.open(WorldSaveFile);

	if(!File.is_open())
	{
		SystemMessage("Error! Could not open file.");
		// TODO(Cristoffer): Handle file read error.
		return;
	}

	for(uint32 X = 0; X < World->GetWidth(); X++)
	{
		for(uint32 Y = 0; Y < World->GetHeight(); Y++)
		{
			File << "tile" << SPACE << X << SPACE << Y << SPACE;
			File << World->GetTile(X, Y).Type;
			File << NEWLINE;
		}
	}

	File.close();

	SystemMessage("World map saved.");
}

void persistence::LoadSavedWorldMap(world *World)
{
	std::string Word;

	std::ifstream File(WorldSaveFile);

	if(!File.is_open())
	{
		SystemMessage("Error! Could not open file.");
		// TODO(Cristoffer): Handle file read error.
		return;
	}

	while(std::getline(File, Word, SPACE))
	{
		if(Word == "tile")
		{
			std::string X, Y, TileType;

			std::getline(File, X, SPACE);
			std::getline(File, Y, SPACE);
			std::getline(File, TileType, NEWLINE);
			
			World->SetTile(std::stoi(X), std::stoi(Y), (tile_type)std::stoi(TileType));
		}
		else
		{
			std::string Trash;

			std::getline(File, Trash, NEWLINE);
		}
	}

	File.close();

	SystemMessage("World map loaded.");
}

obj_file persistence::LoadObjectFile(std::string Filename)
{
	std::string Word;

	obj_file Destination;

	std::ifstream File(OBJECT_FILES_DEFAULT_PATH + Filename);

	if(!File.is_open())
	{
		SystemMessage("Error! Could not open file.");
		// TODO(Cristoffer): Handle file read error.
		return Destination;
	}

	while(std::getline(File, Word, SPACE))
	{
		// NOTE(Cristoffer): Vertex position.
		if(Word == "v")
		{
			std::string X, Y, Z;

			std::getline(File, X, SPACE);
			std::getline(File, Y, SPACE);
			std::getline(File, Z, NEWLINE);

			Destination.Vertices.push_back(vec3(std::stof(X), std::stof(Y), std::stof(Z)));
		}
		else if(Word == "vn")
		{
			std::string X, Y, Z;

			std::getline(File, X, SPACE);
			std::getline(File, Y, SPACE);
			std::getline(File, Z, NEWLINE);

			Destination.Normals.push_back(vec3(std::stof(X), std::stof(Y), std::stof(Z)));
		}
		// NOTE(Cristoffer): Faces or indicies.
		// Ex: f 1/1/1 2/2/1 3/3/1
		// Means: Position / Texture coordinate / Normal
		else if(Word == "f")
		{
			std::string Line;

			std::string Position;
			std::string TextureCoordinate;
			std::string Normal;

			char CurrentChar = 0;

			std::getline(File, Line, NEWLINE);

			Line += NEWLINE;

			for(uint64 Index = 0;
				Index < Line.size();
				Index++)
			{
				while(!Line.empty())
				{
					CurrentChar = Line.at(Index);

					if(CurrentChar == '/')
					{
						Index++;
						break;
					}
					
					Index++;
					Position += CurrentChar;
				}

				while(!Line.empty())
				{
					CurrentChar = Line.at(Index);

					if(CurrentChar == '/')
					{
						Index++;
						break;
					}

					Index++;
					TextureCoordinate += CurrentChar;
				}

				while(!Line.empty())
				{
					CurrentChar = Line.at(Index);

					if(CurrentChar == SPACE || CurrentChar == NEWLINE)
					{
						break;
					}

					Index++;
					Normal += CurrentChar;
				}

				// NOTE(Cristoffer): -1 because .obj index start at 1, and c++ starts at 0.
				face Face;
				
				if(!Position.empty())
				{
					Face.Position = std::stoi(Position) - 1;
				}

				if(!TextureCoordinate.empty())
				{
					Face.TextureCoordinate = std::stoi(TextureCoordinate) - 1;
				}

				if(!Normal.empty())
				{
					Face.Normal = std::stoi(Normal) - 1;
				}
				
				Destination.FaceIndices.push_back(Face);

				Position.clear();
				TextureCoordinate.clear();
				Normal.clear();

				if(CurrentChar == NEWLINE)
				{
					break;
				}
			}
		}
		else
		{
			// NOTE(Cristoffer): If we don't recognize the line or don't use it.

			std::string Trash;

			std::getline(File, Trash, NEWLINE);
		}
	}

	File.close();

	return Destination;
}