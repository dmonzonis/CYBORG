#pragma once

#include <lazarus/ECS.h>
#include <SFML/Graphics.hpp>
#include "Events.h"

/**
 * System that handles player input, i.e., key presses, mouse movement, etc.
 */
class InputSystem : public lz::EventListener<InputEvent>
{
public:
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

    /**
     * Handles mouse clicks.
     */
    void handle_mouse_click_event(lz::Entity &player,
                                  lz::Event &event);

    /**
     * Handles mouse movement.
     */
    void handle_mouse_movement_event(lz::Entity &player,
                                     lz::Event &event);
private:
    bool panning = false;
    sf::Vector2i old_mouse_pos;
};
