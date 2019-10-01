#pragma once

#include <lazarus/ECS.h>
#include <lazarus/FOV.h>
#include "Events.h"
#include "Components.h"

/**
 * System that handles what is visible for an entity at a given position
 */
struct VisibilitySystem : public lz::EventListener<EntityMovedEvent>
{
    VisibilitySystem(const lz::SquareGridMap &map, int range)
        : map(map)
        , range(range)
        , visible(map.get_width() * map.get_height(), false)
        , discovered(map.get_width() * map.get_height(), false)
    {
    }

    virtual void receive(lz::ECSEngine& engine, const EntityMovedEvent& event)
    {
        // Reset visibility
        std::fill(visible.begin(), visible.end(), false);

        // Get player entity
        auto player_entities = engine.entities_with_components<Player>();
        if (player_entities.size() > 1)
            throw std::runtime_error("There cannot be more than one player entity!");
        else if (player_entities.empty())
            return;  // No player, so don't process input
        
        const lz::Position2D &pos{*player_entities[0]->get<lz::Position2D>()};
        const lz::SquareGridMap &map{event.map};
        visible.resize(map.get_width() * map.get_height());
        std::fill(visible.begin(), visible.end(), false);
        auto visible_from_pos{lz::fov(pos, range, map, lz::FOV::Simple)};
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
