#pragma once

#include <lazarus/ECS.h>

#include "Events.h"

/**
 * System that handles what is visible for an entity at a given position
 */
struct MovementSystem : public lz::EventListener<MovementIntentEvent>
{
    virtual void receive(lz::ECSEngine &engine, const MovementIntentEvent &event);
};
