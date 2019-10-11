#include "MovementSystem.h"
#include "Components.h"
#include "Dungeon.h"

void MovementSystem::receive(lz::ECSEngine &engine,
                             const MovementIntentEvent &event)
{
    // Check if the entity can move to the new position
    auto entity = event.entity;
    auto new_pos = event.new_pos;
    auto map = Dungeon::instance().get_level();
    if (map.is_walkable(event.new_pos))
    {
        // OK, set entity at new position
        *entity.get<lz::Position2D>() = new_pos;
        // Send entity moved event to recompute FOV
        // TODO: Don't do this every time an entity moves, or FOV will be
        // recalculated lots of times for nothing. Set a flag to recalculate
        // FOV before drawing the map
        engine.emit<EntityMovedEvent>({});

        // If the player moved, it's the NPCs' turn, so execute AI
        if (entity.has<Player>())
            engine.emit<RefreshAI>({&entity});
    }
}
