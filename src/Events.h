#pragma once

#include <lazarus/ECS.h>
#include <lazarus/SquareGridMap.h>

struct KeyPressedEvent
{
    const lz::Event &key_event;
    const lz::SquareGridMap &map;
};

// Issued when an entity wants to move to a different tile
struct MovementIntentEvent
{
    lz::Entity &entity;
    const lz::Position2D &new_pos;
    const lz::SquareGridMap &map;
};

struct EntityMovedEvent
{
    const lz::SquareGridMap &map;
};
