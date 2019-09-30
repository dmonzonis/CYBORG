#pragma once

#include <lazarus/ECS.h>
#include "Events.h"

/**
 * System that handles what is visible for an entity at a given position
 */
struct MovementSystem : public lz::EventListener<MovementIntentEvent>
{
    MovementSystem() = default;

    virtual void receive(lz::ECSEngine& engine, const MovementIntentEvent& event)
    {
        // Check if the entity can move to the new position
        auto entity = event.entity;
        auto new_pos = event.new_pos;
        auto map = event.map;
        if (map.is_walkable(event.new_pos))
        {
            // OK, set entity at new position
            *entity.get<lz::Position2D>() = new_pos;
            // Send entity moved event to recompute FOV
            // TODO: Don't do this every time an entity moves, or FOV will be
            // recalculated lots of times for nothing. Set a flag to recalculate
            // FOV before drawing the map
            engine.emit<EntityMovedEvent>({map});
        }
    }
};
