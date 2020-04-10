#include "global_data_collector.h"

real32 global_data_collector::CurrentlyPickedTileX = 0.0f;
real32 global_data_collector::CurrentlyPickedTileY = 0.0f;

bool *global_data_collector::ThreadIsWorking = nullptr;