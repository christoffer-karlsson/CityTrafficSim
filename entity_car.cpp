#include "entity_car.h"

bool entity_car::CheckIfTileIsRoad(uint32 PositionX, uint32 PositionZ)
{
	uint32 TileID = World.GetTileID({ PositionX, 0, PositionZ });
	tile_type TileType = World.GetTileType(TileID);
	if(TileType == tile_type::ROAD_X ||
		TileType == tile_type::ROAD_Z)
	{
		return true;
	}
	return false;
}

entity_car::entity_car(uint32 ID, vec3 Position)
{
	this->Drawable = render_manager::GetDrawableCars();

	real32 R = static_cast <real32> (rand()) / static_cast <real32> (RAND_MAX);
	real32 G = static_cast <real32> (rand()) / static_cast <real32> (RAND_MAX);
	real32 B = static_cast <real32> (rand()) / static_cast <real32> (RAND_MAX);

	this->Color = vec4(R, G, B, 1.0f);

	SetID(ID);
	SetCollidable(0);
	SetSimulated(1);
	SetAlive(1);

	std::random_device rd2;
	std::mt19937 eng2(rd2());
	std::uniform_real_distribution<> distr2(0.0f, 360.0f);

	Angle = distr2(eng2);

	WorldModel->Position = Position;
	WorldModel->Rotation.y = 180.0f;
	WorldModel->Scale = vec3(0.25f, 0.25f, 0.25f);

	WorldModel->Update();
}

void entity_car::Update()
{
	vec3 Position = WorldModel->Position;

	uint32 TileID = World.GetTileID({ (uint32)Position.x, 0, (uint32)Position.z });
	tile_type TileType = World.GetTileType(TileID);

	if(TileType == tile_type::ROAD_X)
	{
		CrossRoadDecisionMade = false;

		// See where in the tile the car is.
		real32 PositionInTile = Position.z - (real32)((uint32)Position.z);

		// Left or right lane.
		if(PositionInTile < 0.5f)
		{
			WorldModel->Rotation.y = AngleWest;
			WorldModel->Position.x += timing::GetFrameTimeDeltaSeconds() * Speed;
		}
		else
		{
			WorldModel->Rotation.y = AngleEast;
			WorldModel->Position.x -= timing::GetFrameTimeDeltaSeconds() * Speed;
		}
		 
	}
	else if(TileType == tile_type::ROAD_Z)
	{
		CrossRoadDecisionMade = false;

		real32 PositionInTileX = Position.x - (real32)((uint32)Position.x);

		// Left or right lane.
		if(PositionInTileX < 0.5f)
		{
			WorldModel->Rotation.y = AngleSouth;
			WorldModel->Position.z -= timing::GetFrameTimeDeltaSeconds() * Speed;
		}
		else
		{
			WorldModel->Rotation.y = AngleNorth;
			WorldModel->Position.z += timing::GetFrameTimeDeltaSeconds() * Speed;
		}
	}
	else if(TileType == tile_type::CROSSROAD && !CrossRoadDecisionMade)
	{
		uint32 OptionsCount = 0;
		turn_dir ViableTurnOptions[3];

		bool CarInSW = false;
		bool CarInSE = false;
		bool CarInNW = false;
		bool CarInNE = false;
		bool LeftTurnViable = false;
		bool RightTurnViable = false;
		bool ForwardViable = false;
		bool TurnBack = false;

		uint32 TileID;
		tile_type TileType;

		// Subtract the truncated position valuees, so we get the value 
		// where the car is within the tile.
		real32 PositionInTileX = Position.x - (real32)((uint32)Position.x);
		real32 PositionInTileZ = Position.z - (real32)((uint32)Position.z);

		// Check the possible tiles that can be driven to.
		if(PositionInTileX < 0.5f && PositionInTileZ < 0.5f)
		{
			// Car is in the SW corner of the tile.
			LeftTurnViable = CheckIfTileIsRoad((uint32)Position.x, (uint32)Position.z + 1);
			RightTurnViable = CheckIfTileIsRoad((uint32)Position.x, (uint32)Position.z - 1);
			ForwardViable = CheckIfTileIsRoad((uint32)Position.x + 1, (uint32)Position.z);
			CarInSW = true;
		}
		else if(PositionInTileX > 0.5f && PositionInTileZ < 0.5f)
		{
			// Car is in SE corner of the tile.
			LeftTurnViable = CheckIfTileIsRoad((uint32)Position.x - 1, (uint32)Position.z);
			RightTurnViable = CheckIfTileIsRoad((uint32)Position.x + 1, (uint32)Position.z);
			ForwardViable = CheckIfTileIsRoad((uint32)Position.x, (uint32)Position.z + 1);
			CarInSE = true;
		}
		else if(PositionInTileX < 0.5f && PositionInTileZ > 0.5f)
		{
			// Car is in NW corner of the tile.
			LeftTurnViable = CheckIfTileIsRoad((uint32)Position.x + 1, (uint32)Position.z);
			RightTurnViable = CheckIfTileIsRoad((uint32)Position.x - 1, (uint32)Position.z);
			ForwardViable = CheckIfTileIsRoad((uint32)Position.x, (uint32)Position.z - 1);
			CarInNW = true;
		}
		else if(PositionInTileX > 0.5f && PositionInTileZ > 0.5f)
		{
			// Car is in NE corner of the tile.
			LeftTurnViable = CheckIfTileIsRoad((uint32)Position.x, (uint32)Position.z - 1);
			RightTurnViable = CheckIfTileIsRoad((uint32)Position.x, (uint32)Position.z + 1);
			ForwardViable = CheckIfTileIsRoad((uint32)Position.x - 1, (uint32)Position.z);
			CarInNE = true;
		}

		if(LeftTurnViable)
		{
			ViableTurnOptions[OptionsCount] = turn_left;
			OptionsCount++;
		}
		if(RightTurnViable)
		{
			ViableTurnOptions[OptionsCount] = turn_right;
			OptionsCount++;
		}
		if(ForwardViable)
		{
			ViableTurnOptions[OptionsCount] = forward;
			OptionsCount++;
		}
		if(!LeftTurnViable && !RightTurnViable && !ForwardViable)
		{
			TurnBack = true;
		}

		if(TurnBack)
		{
			// Truncate the value first to get the tile coordinate.
			real32 TilePositionX = (real32)((uint32)Position.x);
			real32 TilePositionZ = (real32)((uint32)Position.z);

			// Set waypoint in the beginning of next tile.
			if(CarInSW) Waypoint = vec3(TilePositionX - 0.05f, 0.0f, TilePositionZ + 0.75f);
			if(CarInSE) Waypoint = vec3(TilePositionX + 0.25f, 0.0f, TilePositionZ - 0.05f);
			if(CarInNW) Waypoint = vec3(TilePositionX + 0.75f, 0.0f, TilePositionZ + 1.05f);
			if(CarInNE) Waypoint = vec3(TilePositionX + 1.05f, 0.0f, TilePositionZ + 0.25f);
		}
		else
		{
			// Randomly decide where the car will turn from the viable options.
			std::random_device RandomDevice;
			std::mt19937 Eng3(RandomDevice());
			std::uniform_int_distribution<> Distribution(0, OptionsCount-1);

			uint32 RandomOptionIndex = Distribution(Eng3);

			turn_dir TurnDirectionDecision = ViableTurnOptions[RandomOptionIndex];

			if(TurnDirectionDecision == turn_left)
			{
				// Truncate the value first to get the tile coordinate.
				real32 TilePositionX = (real32)((uint32)Position.x);
				real32 TilePositionZ = (real32)((uint32)Position.z);

				// Set waypoint in the beginning of next tile.
				if(CarInSW) Waypoint = vec3(TilePositionX + 0.75f, 0.0f, TilePositionZ + 1.05f);
				if(CarInSE) Waypoint = vec3(TilePositionX - 0.05f, 0.0f, TilePositionZ + 0.75f);
				if(CarInNW) Waypoint = vec3(TilePositionX + 1.05f, 0.0f, TilePositionZ + 0.25f);
				if(CarInNE) Waypoint = vec3(TilePositionX + 0.25f, 0.0f, TilePositionZ - 0.05f);
			}
			else if(TurnDirectionDecision == turn_right)
			{
				// Truncate the value first to get the tile coordinate.
				real32 TilePositionX = (real32)((uint32)Position.x);
				real32 TilePositionZ = (real32)((uint32)Position.z);

				// Set waypoint in the beginning of next tile.
				if(CarInSW) Waypoint = vec3(TilePositionX + 0.25f, 0.0f, TilePositionZ - 0.05f);
				if(CarInSE) Waypoint = vec3(TilePositionX + 1.05f, 0.0f, TilePositionZ + 0.25f);
				if(CarInNW) Waypoint = vec3(TilePositionX - 0.05f, 0.0f, TilePositionZ + 0.75f);
				if(CarInNE) Waypoint = vec3(TilePositionX + 0.75f, 0.0f, TilePositionZ + 1.05f);
			}
			else if(TurnDirectionDecision == forward)
			{
				// Truncate the value first to get the tile coordinate.
				real32 TilePositionX = (real32)((uint32)Position.x);
				real32 TilePositionZ = (real32)((uint32)Position.z);

				// Set waypoint in the beginning of next tile.
				if(CarInSW) Waypoint = vec3(TilePositionX + 1.05f, 0.0f, TilePositionZ + 0.25f);
				if(CarInSE) Waypoint = vec3(TilePositionX + 0.75f, 0.0f, TilePositionZ + 1.05f);
				if(CarInNW) Waypoint = vec3(TilePositionX + 0.25f, 0.0f, TilePositionZ - 0.05f);
				if(CarInNE) Waypoint = vec3(TilePositionX - 0.05f, 0.0f, TilePositionZ + 0.75f);
			}
		}

		CrossRoadDecisionMade = true;
	}
	else if(TileType == tile_type::CROSSROAD && CrossRoadDecisionMade)
	{
		// TODO: Make a smooth transition to waypoint.
		WorldModel->Position = Waypoint;
	}
	else if(TileType == tile_type::GRASS)
	{
		SetAlive(false);
		return;
	}
	else
	{
		// TODO: Handle the case where the car has ended up in a bad spot.
	}

	// Destroy entity if outside world bounds.
	if(	WorldModel->Position.z > World.GetWidthZ() || 
		WorldModel->Position.z < 0 || 
		WorldModel->Position.x > World.GetWidthX() || 
		WorldModel->Position.x < 0)
	{
		SetAlive(false);
		return;
	}

	WorldModel->Update();

	Drawable->PushInstance(WorldModel->GetMatrix(), Color);
}