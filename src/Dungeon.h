#pragma once

#include <lazarus/SquareGridMap.h>

/**
 * Singleton that stores and manages the levels in the dungeon.
 */
class Dungeon
{
public:
    // Delete other constructors/copy operators
    Dungeon(const Dungeon &) = delete;
    Dungeon &operator=(const Dungeon &) = delete;
    Dungeon(Dungeon &&) = delete;
    Dungeon &operator=(Dungeon &&) = delete;

    /**
     * Get the singleton's instance.
     */
    static Dungeon &instance();

    /**
     * Generates a new level with the given dimensions and
     * adds it to the level pool.
     *
     * @return The new level's position in the pool.
     */
    int generate_new_level(int width, int height);

    /**
     * Gets the level at the given position in the pool.
     */
    lz::SquareGridMap &get_level(int level);

    /**
     * Gets the currently loaded level.
     */
    lz::SquareGridMap &get_level();

    /**
     * Switches the currently loaded level.
     */
    void switch_level(int level);

    bool is_visible(int level, int x, int y) const;
    bool is_visible(int x, int y) const;
    bool is_discovered(int level, int x, int y) const;
    bool is_discovered(int x, int y) const;
    void set_visibility(int level, std::vector<bool> &visibility);
    void set_visibility(std::vector<bool> &visibility);
    void set_discovered(int level, int x, int y, bool state);
    void set_discovered(int x, int y, bool state);

private:
    Dungeon();  // Disable instantiation outside of this class

private:
    std::vector<lz::SquareGridMap> levels;
    std::vector<std::vector<bool>> visible;
    std::vector<std::vector<bool>> discovered;
    int current_level = -1;  // Currently loaded level
};
