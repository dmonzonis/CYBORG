#include "Dungeon.h"
#include <lazarus/Random.h>

Dungeon::Dungeon()
{
}

Dungeon &Dungeon::instance()
{
    static Dungeon dungeon;
    return dungeon;
}

int Dungeon::generate_new_level(int width, int height)
{
    // TODO: Use an actual dungeon generator
    lz::SquareGridMap map(width, height);
    // Randomize walls. Each tile has a 20% prob of being wall
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            bool wall = lz::Random::one_in(5);
            if (!wall)
            {
                map.set_walkable(x, y, true);
                map.set_transparency(x, y, true);
            }
        }
    }

    // Add the level to the pool and return its position
    levels.push_back(map);

    // Update visibility and discovered vectors for this map
    visible.emplace_back(map.get_width() * map.get_height(), false);
    discovered.emplace_back(map.get_width() * map.get_height(), false);

    return levels.size() - 1;
}

lz::SquareGridMap &Dungeon::get_level(int level)
{
    // TODO: throw error if there is no level at the asked position
    return levels[level];
}

lz::SquareGridMap &Dungeon::get_level()
{
    return get_level(current_level);
}

void Dungeon::switch_level(int level)
{
    // TODO: Perform sanity check (level >= 0, level < levels.size())
    current_level = level;
}

bool Dungeon::is_visible(int level, int x, int y) const
{
    return visible[level][x + y * levels[level].get_width()];
}

bool Dungeon::is_visible(int x, int y) const
{
    return visible[current_level][x + y * levels[current_level].get_width()];
}

bool Dungeon::is_discovered(int level, int x, int y) const
{
    return discovered[level][x + y * levels[level].get_width()];
}

bool Dungeon::is_discovered(int x, int y) const
{
    return discovered[current_level][x + y * levels[current_level].get_width()];
}

void Dungeon::set_visibility(int level, std::vector<bool> &visibility)
{
    if (visibility.size() != visible[level].size())
        return;
    visible[level] = visibility;
}

void Dungeon::set_visibility(std::vector<bool> &visibility)
{
    if (visibility.size() != visible[current_level].size())
        return;
    visible[current_level] = visibility;
}

void Dungeon::set_discovered(int level, int x, int y, bool state)
{
    discovered[level][x + y * get_level(level).get_width()] = state;
}

void Dungeon::set_discovered(int x, int y, bool state)
{
    discovered[current_level][x + y * get_level().get_width()] = state;
}
