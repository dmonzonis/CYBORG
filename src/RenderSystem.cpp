#include "RenderSystem.h"
#include "MainWindow.h"

void RenderSystem::update(lz::ECSEngine &engine)
{
    // Get main camera
    lz::Window &window = MainWindow::get_window();
    if (!window.is_initialized())
        return;
    int range_x = window.get_width() / 2;
    int range_y = window.get_height() / 2;

    // Set camera centered on the player
    lz::Entity *player = engine.entities_with_components<Player>().front();
    lz::Position2D center = *player->get<lz::Position2D>();
    const lz::Tileset *tileset = window.get_tileset();
    int tile_size = tileset->get_tile_size();
    sf::View view(sf::FloatRect(0, 0,
                                window.get_width() * tile_size,
                                window.get_height() * tile_size));
    view.setViewport(sf::FloatRect(0, 0, 1, 1));
    view.setCenter(center.x * tile_size + tile_size / 2,
                   center.y * tile_size + tile_size / 2);
    window.setView(view);
    int left = (view.getCenter().x - view.getSize().x / 2) / tile_size;
    int right = left + view.getSize().x / tile_size;
    int top = (view.getCenter().y - view.getSize().y / 2) / tile_size;
    int bottom = top + view.getSize().y / tile_size;

    // Get current map
    Dungeon &dungeon = Dungeon::instance();
    lz::SquareGridMap &map = dungeon.get_level();

    // Render map
    sf::Color tile_color;
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

                // window.set_tile({x - left, y - top}, map_tile, tile_color);
                window.set_tile({x, y}, map_tile, tile_color);
            }
        }
    }

    // Render visible entities
    engine.apply_to_each<lz::Position2D, Renderable>(
        [&](lz::Entity *entity, lz::Position2D *pos, Renderable *rend) {
            if (dungeon.is_visible(pos->x, pos->y))
            {
                lz::Position2D pos_view{pos->x, pos->y};
                window.set_tile(pos_view, rend->tile_id);
            }
        });
}
