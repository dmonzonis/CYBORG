#pragma once

#include <lazarus/ECS.h>
#include <lazarus/FOV.h>
#include "Events.h"

/**
 * System that handles what is visible for an entity at a given position
 */
struct VisibilitySystem : public lz::EventListener<PlayerMovedEvent>
{
    virtual void receive(lz::ECSEngine& engine, const PlayerMovedEvent& event)
    {
        // TODO: remember dimensions from map and use those if map has not changed
        visible.clear();
        const lz::Position2D &pos{event.player_pos};
        const lz::SquareGridMap &map{event.map};
        visible.resize(map.get_width() * map.get_height());
        std::fill(visible.begin(), visible.end(), false);
        auto visible_from_pos{lz::simple_fov(pos, 5, map)};
        for (auto visible_pos : visible_from_pos)
        {
            int x = visible_pos.x, y = visible_pos.y;
            visible[x + y * map.get_width()] = true;
        }
    }

    std::vector<bool> visible;
    // std::vector<bool> discovered;
};
