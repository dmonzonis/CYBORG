#pragma once

#include <lazarus/ECS.h>
#include "Events.h"

/**
 * System that handles player input, i.e., key presses, mouse movement, etc.
 */
struct InputSystem : public lz::EventListener<KeyPressedEvent>
{
    virtual void receive(lz::ECSEngine& engine, const KeyPressedEvent& event);
};