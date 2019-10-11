#include "VisibilitySystem.h"

void VisibilitySystem::receive(lz::ECSEngine &engine,
                               const EntityMovedEvent &event)
{
    // Get current map
    Dungeon &dungeon = Dungeon::instance();
    lz::SquareGridMap &map = dungeon.get_level();

    // Start with all tiles invisible
    std::vector<bool> visible(map.get_width() * map.get_height(), false);

    // Get player entity
    auto player_entities = engine.entities_with_components<Player>();
    if (player_entities.size() > 1)
        throw std::runtime_error("There cannot be more than one player entity!");
    else if (player_entities.empty())
        return; // No player, so don't process input

    // Get FOV range from player component
    int range = player_entities[0]->get<Player>()->fov_range;

    const lz::Position2D &pos{*player_entities[0]->get<lz::Position2D>()};
    auto visible_from_pos{lz::fov(pos, range, map, lz::FOV::Simple)};
    for (auto visible_pos : visible_from_pos)
    {
        int x = visible_pos.x, y = visible_pos.y;
        int pos_vec = x + y * map.get_width();
        visible[pos_vec] = true;
        dungeon.set_discovered(x, y, true);
    }

    // Update visibility on the map
    dungeon.set_visibility(visible);
}