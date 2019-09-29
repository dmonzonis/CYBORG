#pragma once

#include <lazarus/ECS.h>
#include <lazarus/SquareGridMap.h>

struct KeyPressedEvent
{
    const lz::Event &key_event;
    const lz::SquareGridMap &map;
};

struct PlayerMovedEvent
{
    const lz::Position2D &player_pos;
    const lz::SquareGridMap &map;
};
