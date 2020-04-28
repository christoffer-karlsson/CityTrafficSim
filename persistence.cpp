#include "persistence.h"

bool32 persistence::SaveWorldMap()
{
	std::ofstream File;
	File.open(WorldSaveFile);

	if(!File.is_open())
	{
		// TODO(Cristoffer): Handle file read error.
		return 0;
	}

	for(uint32 X = 0; X < World.GetWidthX(); X++)
	{
		for(uint32 Z = 0; Z < World.GetWidthZ(); Z++)
		{
			File << "tile" << SPACE << X << SPACE << 0 << SPACE << Z << SPACE;
			File << World.GetTileID(vec3u(X, 0, Z));
			File << NEWLINE;
		}
	}

	File.close();

	return 1;
}

bool32 persistence::LoadSavedWorldMap()
{
	std::string Word;

	std::ifstream File(WorldSaveFile);

	if(!File.is_open())
	{
		// TODO(Cristoffer): Handle file read error.
		return 0;
	}

	while(std::getline(File, Word, SPACE))
	{
		if(Word == "tile")
		{
			std::string X, Y, Z, TileType;

			std::getline(File, X, SPACE);
			std::getline(File, Y, SPACE);
			std::getline(File, Z, SPACE);
			std::getline(File, TileType, NEWLINE);

			World.SetTile(vec3u(std::stoi(X), std::stoi(Y), std::stoi(Z)), World.GetTileType(std::stoi(TileType)));
		}
		else
		{
			std::string Trash;

			std::getline(File, Trash, NEWLINE);
		}
	}

	File.close();

	return 1;
}

obj_file persistence::LoadObjectFile(std::string Filename)
{
	std::string Word;

	obj_file Destination;

	std::ifstream File(OBJECT_FILES_DEFAULT_PATH + Filename);

	if(!File.is_open())
	{
		// TODO(Cristoffer): Handle file read error.
		return Destination;
	}

	while(std::getline(File, Word, SPACE))
	{
		// NOTE(Cristoffer): Vertex position.
		if(Word == "v")
		{
			std::string x, y, z;

			std::getline(File, x, SPACE);
			std::getline(File, y, SPACE);
			std::getline(File, z, NEWLINE);

			Destination.Vertices.push_back(vec3(std::stof(x), std::stof(y), std::stof(z)));
		}
		// NOTE(Cristoffer): Normal positions.
		else if(Word == "vn")
		{
			std::string x, y, z;

			std::getline(File, x, SPACE);
			std::getline(File, y, SPACE);
			std::getline(File, z, NEWLINE);

			Destination.Normals.push_back(vec3(std::stof(x), std::stof(y), std::stof(z)));
		}
		// NOTE(Cristoffer): Texture UV position;
		else if(Word == "vt")
		{
			std::string x, y, z;

			std::getline(File, x, SPACE);
			std::getline(File, y, SPACE);
			std::getline(File, z, NEWLINE);

			Destination.TextureUVs.push_back(vec3(std::stof(x), std::stof(y), std::stof(z)));
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

				// NOTE(Cristoffer): -1 because .obj format index start at 1, and c++ starts at 0.
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