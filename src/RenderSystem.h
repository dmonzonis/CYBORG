#pragma once

#include <lazarus/ECS.h>
#include <lazarus/Graphics.h>
#include "Components.h"
#include "Dungeon.h"
#include "VisibilitySystem.h"

// TODO: Remove this
constexpr int FLOOR_IMG = 1;
constexpr int WALL_IMG = 2;

struct RenderSystem : public lz::Updateable
{
    RenderSystem(lz::Window &window)
        : window(window)
        , range_x(window.get_width() / 2)
        , range_y(window.get_height() / 2)
    {
    }

    virtual void update(lz::ECSEngine &engine)
    {
        // Acts like a camera or view centered on the player
        // TODO: Let player pan, zoom, etc the camera/view
        lz::Entity *player = engine.entities_with_components<Player>().front();
        lz::Position2D center = *player->get<lz::Position2D>();
        int left = center.x - range_x;
        int right = center.x + range_x;
        int top = center.y - range_y;
        int bottom = center.y + range_y;

        // Get current map
        Dungeon &dungeon = Dungeon::instance();
        lz::SquareGridMap &map = dungeon.get_level();

        // Render map
        sf::Color tile_color;
        // TODO: Draw camera subview, not the entire window
        for (int y = top; y < bottom; ++y)
        {
            for (int x = left; x < right; ++x)
            {
                if (!map.is_out_of_bounds(x, y))
                {
                    int map_tile = -1;
                    // TODO: Draw walls and explored tiles
                    if (dungeon.is_discovered(x, y))
                    {
                        map_tile = map.is_walkable(x, y) ? FLOOR_IMG : WALL_IMG;
                        if (dungeon.is_visible(x, y))
                            tile_color = sf::Color::White;
                        else
                            tile_color = sf::Color(20, 40, 190);
                    }

                    window.set_tile({x - left, y - top}, map_tile, tile_color);
                }
            }
        }

        // Render visible entities
        engine.apply_to_each<lz::Position2D, Renderable>(
            [&](lz::Entity *entity, lz::Position2D *pos, Renderable *rend)
            {
                // TODO: Use relative position
                // For now, we are assuming position on screen = position on map
                if (dungeon.is_visible(pos->x, pos->y))
                {
                    lz::Position2D pos_view{pos->x - left, pos->y - top};
                    window.set_tile(pos_view, rend->tile_id);
                }
            }
        );
    }

    lz::Window &window;

    // Tiles from the center that the camera will render in each direction
    unsigned range_x, range_y;
};