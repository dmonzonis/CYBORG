#pragma once

#include <lazarus/ECS.h>
#include <lazarus/Graphics.h>
#include <lazarus/SquareGridMap.h>
#include "Components.h"
#include "VisibilitySystem.h"

// TODO: Remove this
constexpr int FLOOR_IMG = 14;
constexpr int WALL_IMG = 3;

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
        const auto& visible = visibility_system.visible;
        // TODO: Draw camera subview, not the entire window
        for (int y = 0; y < window.get_height(); ++y)
        {
            for (int x = 0; x < window.get_width(); ++x)
            {
                int map_tile = -1;
                // TODO: Draw walls and explored tiles
                if (visible[x + y * window.get_width()])
                {
                    map_tile = FLOOR_IMG;
                }

                window.set_tile({x, y}, map_tile);
            }
        }

        // Render entities
        engine.apply_to_each<lz::Position2D, Renderable>(
            [&](lz::Entity *entity, lz::Position2D *pos, Renderable *rend)
            {
                // TODO: Use relative position
                // For now, we are assuming position on screen = position on map
                window.set_tile(*pos, rend->tile_id);
            }
        );
    }

    // TODO: Untie systems
    VisibilitySystem &visibility_system;
    lz::Window &window;
    const lz::SquareGridMap &map;
};