#pragma once

#include <lazarus/AStarSearch.h>
#include <lazarus/ECS.h>
#include <lazarus/SquareGridMap.h>

#include "Components.h"
#include "Dungeon.h"
#include "Events.h"

#include <algorithm>

struct AISystem : public lz::EventListener<RefreshAI>
{
    virtual void receive(lz::ECSEngine &engine, const RefreshAI &event);
};
