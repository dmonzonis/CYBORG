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
    RenderSystem(lz::Window &window);

    virtual void update(lz::ECSEngine &engine);

    lz::Window &window;

    // Tiles from the center that the camera will render in each direction
    unsigned range_x, range_y;
};