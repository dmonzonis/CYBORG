#pragma once

// Empty component to identify the player
struct Player
{
};

struct Renderable
{
    Renderable(int tile_id) : tile_id(tile_id)
    {
    }
    int tile_id;
};
