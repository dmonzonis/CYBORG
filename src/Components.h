#pragma once

// Component that identifies the player
struct Player
{
    Player(int fov_range)
        : fov_range(fov_range)
    {
    }
    int fov_range;
    float camera_offset_x, camera_offset_y;
    float camera_zoom = 1.;
};

// Entities that have a tile associated and will be rendered by the render system
struct Renderable
{
    Renderable(int tile_id)
        : tile_id(tile_id)
    {
    }
    int tile_id;
};

// Different AI behaviours
enum class AIBehaviour
{
    Follow
};

// Entities that use an AI behaviour, i.e., are controlled by the machine
struct AI
{
    AI(AIBehaviour behaviour)
        : behaviour(behaviour)
    {
    }
    AIBehaviour behaviour;
};
