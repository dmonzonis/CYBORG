#pragma once

#include <lazarus/ECS.h>
#include <lazarus/Graphics.h>
#include "Components.h"
#include "Dungeon.h"
#include "VisibilitySystem.h"

// TODO: Remove this
constexpr int FLOOR_IMG = 1;
constexpr int WALL_IMG = 2;

struct RenderSystem : public lz::EventListener<ResetCameraEvent>, public lz::Updateable
{
    virtual void receive(lz::ECSEngine &engine, const ResetCameraEvent &event);

    virtual void update(lz::ECSEngine &engine);

    // Tiles from the center that the camera will render in each direction
    unsigned range_x, range_y;
};