#include "InputSystem.h"
#include <lazarus/Graphics.h>
#include <lazarus/SquareGridMap.h>

#include "Components.h"

void InputSystem::receive(lz::ECSEngine &engine, const InputEvent &event)
{
    lz::Event inp_event = event.event;
    // Get player entity
    auto player_entities = engine.entities_with_components<Player>();
    if (player_entities.size() != 1)
        throw std::runtime_error("There cannot be more than one player entity!");
    else if (player_entities.empty())
        return;  // No player, so don't process input

    lz::Entity &player = *player_entities[0];

    switch (inp_event.type)
    {
    case sf::Event::KeyPressed:
        handle_keyboard_event(engine, player, inp_event);
        break;
    case sf::Event::MouseWheelScrolled:
        handle_mousewheel_event(player, inp_event);
        break;
    case sf::Event::MouseButtonPressed:
    case sf::Event::MouseButtonReleased:
        handle_mouse_click_event(player, inp_event);
        break;
    case sf::Event::MouseMoved:
        handle_mouse_movement_event(player, inp_event);
        break;
    }
}

void InputSystem::handle_keyboard_event(lz::ECSEngine &engine,
                                        lz::Entity &player,
                                        lz::Event &event)
{
    // TODO: Add key press to a queue and handle them all later to be
    // able to parse key combinations
    lz::Position2D new_pos = *player.get<lz::Position2D>();
    switch (event.key.code)
    {
    case sf::Keyboard::Left:
        --new_pos.x;
        break;
    case sf::Keyboard::Right:
        ++new_pos.x;
        break;
    case sf::Keyboard::Up:
        --new_pos.y;
        break;
    case sf::Keyboard::Down:
        ++new_pos.y;
        break;
    default:
        // Unhandled key, do not take an action
        return;
    }

    // Emit intent of the player to move
    // A different system will check if the player does move, if it hits an enemy,
    // a wall, etc
    engine.emit(MovementIntentEvent{player, new_pos});
}

void InputSystem::handle_mousewheel_event(lz::Entity &player, lz::Event &event)
{
    Player *player_component = player.get<Player>();
    if (!player_component)
        return;
    player_component->camera_zoom -= 0.2f * event.mouseWheelScroll.delta;
    // Set zoom limits
    if (player_component->camera_zoom > 5)
        player_component->camera_zoom = 5.;
    else if (player_component->camera_zoom < 0.5)
        player_component->camera_zoom = 0.5;
}

void InputSystem::handle_mouse_click_event(lz::Entity &player, lz::Event &event)
{
    Player *player_component = player.get<Player>();
    if (!player_component)
        return;

    sf::Event::MouseButtonEvent &mouse_button = event.mouseButton;
    if (event.type == sf::Event::MouseButtonPressed)
    {
        // Middle mouse button click: start panning
        if (mouse_button.button == sf::Mouse::Button::Middle)
        {
            panning = true;
            old_mouse_pos = sf::Vector2i(mouse_button.x, mouse_button.y);
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        // Middle mouse button release: stop panning
        if (mouse_button.button == sf::Mouse::Button::Middle)
            panning = false;
    }
}

void InputSystem::handle_mouse_movement_event(lz::Entity &player, lz::Event &event)
{
    Player *player_component = player.get<Player>();
    if (!player_component)
        return;

    sf::Event::MouseMoveEvent &mouse = event.mouseMove;
    if (panning)
    {
        // Pan the camera by the mouse movement amount
        const sf::Vector2i current_mouse_pos(mouse.x, mouse.y);
        const sf::Vector2i delta = current_mouse_pos - old_mouse_pos;
        int delta_x = delta.x, delta_y = delta.y;
        player_component->camera_offset_x -= delta_x;
        player_component->camera_offset_y -= delta_y;
        old_mouse_pos = current_mouse_pos;
    }
}
