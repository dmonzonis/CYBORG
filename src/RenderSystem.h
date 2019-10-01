#pragma once

#include <lazarus/ECS.h>
#include <lazarus/Graphics.h>
#include <lazarus/SquareGridMap.h>
#include "Components.h"
#include "VisibilitySystem.h"

// TODO: Remove this
constexpr int FLOOR_IMG = 1;
constexpr int WALL_IMG = 2;

struct RenderSystem : public lz::Updateable
{
    RenderSystem(lz::Window &window,
                 lz::SquareGridMap &map,
                 VisibilitySystem &visibility_system)
        : window(window)
        , map(map)
        , visibility_system(visibility_system)
    {
    }

    virtual void update(lz::ECSEngine &engine)
    {
        // Render map
        sf::Color tile_color;
        // TODO: Draw camera subview, not the entire window
        for (int y = 0; y < window.get_height(); ++y)
        {
            for (int x = 0; x < window.get_width(); ++x)
            {
                int map_tile = -1;
                // TODO: Draw walls and explored tiles
                int pos_vec = x + y * window.get_width();
                if (visibility_system.discovered[pos_vec])
                {
                    map_tile = map.is_walkable(x, y) ? FLOOR_IMG : WALL_IMG;
                    if (visibility_system.visible[pos_vec])
                        tile_color = sf::Color::White;
                    else
                        tile_color = sf::Color(20, 40, 190);
                }

                window.set_tile({x, y}, map_tile, tile_color);
            }
        }

        // Render visible entities
        engine.apply_to_each<lz::Position2D, Renderable>(
            [&](lz::Entity *entity, lz::Position2D *pos, Renderable *rend)
            {
                // TODO: Use relative position
                // For now, we are assuming position on screen = position on map
                int pos_vec = pos->x + pos->y * map.get_width();
                if (visibility_system.visible[pos_vec])
                    window.set_tile(*pos, rend->tile_id);
            }
        );
    }

    // TODO: Untie systems
    VisibilitySystem &visibility_system;
    lz::Window &window;
    const lz::SquareGridMap &map;
};