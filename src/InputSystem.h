#pragma once

#include <lazarus/ECS.h>
#include "Events.h"

/**
 * System that handles player input, i.e., key presses, mouse movement, etc.
 */
struct InputSystem : public lz::EventListener<InputEvent>
{
    virtual void receive(lz::ECSEngine &engine, const InputEvent &event);

    /**
     * Handles keyboard input.
     */
    void handle_keyboard_event(lz::ECSEngine &engine,
                               lz::Entity &player,
                               lz::Event &event);

    /**
     * Handles mousewheel scrolling.
     */
    void handle_mousewheel_event(lz::Entity &player,
                                 lz::Event &event);
};
