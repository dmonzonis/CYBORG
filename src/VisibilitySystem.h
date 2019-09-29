#pragma once

#include <lazarus/ECS.h>
#include <lazarus/FOV.h>
#include "Events.h"

/**
 * System that handles what is visible for an entity at a given position
 */
struct VisibilitySystem : public lz::EventListener<PlayerMovedEvent>
{
    VisibilitySystem(const lz::SquareGridMap &map, int range)
        : map(map)
        , range(range)
        , visible(map.get_width() * map.get_height(), false)
        , discovered(map.get_width() * map.get_height(), false)
    {
    }

    virtual void receive(lz::ECSEngine& engine, const PlayerMovedEvent& event)
    {
        // Reset visibility
        std::fill(visible.begin(), visible.end(), false);

        const lz::Position2D &pos{event.player_pos};
        const lz::SquareGridMap &map{event.map};
        visible.resize(map.get_width() * map.get_height());
        std::fill(visible.begin(), visible.end(), false);
        auto visible_from_pos{lz::simple_fov(pos, range, map)};
        for (auto visible_pos : visible_from_pos)
        {
            int x = visible_pos.x, y = visible_pos.y;
            int pos_vec = x + y * map.get_width();
            visible[pos_vec] = true;
            discovered[pos_vec] = true;
        }
    }

    const lz::SquareGridMap &map;
    int range;
    std::vector<bool> visible;
    std::vector<bool> discovered;
};
