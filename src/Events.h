#pragma once

#include <lazarus/ECS.h>
#include <lazarus/Graphics/Window.h>

struct KeyPressedEvent
{
    const lz::Event &key_event;
};

// Issued when an entity wants to move to a different tile
struct MovementIntentEvent
{
    lz::Entity &entity;
    const lz::Position2D &new_pos;
};

struct EntityMovedEvent
{
};

struct RefreshAI
{
    lz::Entity *player;
};

struct ResetCameraEvent
{
    lz::Entity *player;
};
