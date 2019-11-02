#include "RenderSystem.h"
#include "MainWindow.h"

void RenderSystem::receive(lz::ECSEngine &engine,
                           const ResetCameraEvent &event)
{
    lz::Entity *player = event.player;
    Player *player_component = player->get<Player>();
    int tile_size = MainWindow::get_window().get_tileset()->get_tile_size();
    // Reset camera offset (set camera centered on player)
    player_component->camera_offset_x = player_component->camera_offset_y = 0.;
    // Reset zoom
    player_component->camera_zoom = 1.;
}

void RenderSystem::update(lz::ECSEngine &engine)
{
    // Get main camera
    lz::Window &window = MainWindow::get_window();
    if (!window.is_initialized())
        return;
    int range_x = window.get_width() / 2;
    int range_y = window.get_height() / 2;

    // Set view according to the camera position and zoom
    lz::Entity *player = engine.entities_with_components<Player>().front();
    lz::Position2D center = *player->get<lz::Position2D>();
    Player *player_component = player->get<Player>();
    // Player component holds the camera location and zoom
    // Without a camera, there's nothing to draw
    if (!player_component)
        return;

    int tile_size = window.get_tileset()->get_tile_size();
    // Set view to occupy all space in the window
    // TODO: Rework this when subwindows/layers are implemented
    sf::View view(sf::FloatRect(0, 0,
                                window.get_width() * tile_size,
                                window.get_height() * tile_size));
    view.setViewport(sf::FloatRect(0, 0, 1, 1));
    float center_x = center.x * tile_size + player_component->camera_offset_x;
    float center_y = center.y * tile_size + player_component->camera_offset_y;
    view.setCenter(center_x, center_y);
    view.zoom(player_component->camera_zoom);
    window.setView(view);
    int left = (view.getCenter().x - view.getSize().x / 2) / tile_size;
    int right = left + view.getSize().x / tile_size + tile_size;
    int top = (view.getCenter().y - view.getSize().y / 2) / tile_size;
    int bottom = top + view.getSize().y / tile_size + tile_size;

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
