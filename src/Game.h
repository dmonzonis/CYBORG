#pragma once

#include <lazarus/ECS.h>

// Map dimensions
constexpr int MAP_WIDTH = 70;
constexpr int MAP_HEIGHT = 70;

// Tile IDs
// TODO: Remove this
constexpr int PLAYER_IMG = 0;
constexpr int MONSTER_IMG = 3;

void game_loop(lz::ECSEngine &engine);

int main(int argc, char const *argv[]);
