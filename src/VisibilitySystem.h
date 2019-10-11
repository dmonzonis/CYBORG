#pragma once

#include <lazarus/ECS.h>
#include <lazarus/FOV.h>
#include "Components.h"
#include "Dungeon.h"
#include "Events.h"

/**
 * System that handles what is visible for an entity at a given position
 */
struct VisibilitySystem : public lz::EventListener<EntityMovedEvent>
{
    VisibilitySystem(int range);

    virtual void receive(lz::ECSEngine& engine, const EntityMovedEvent& event);
    

    int range;
};
