#pragma once

#include <lazarus/ECS.h>
#include <lazarus/SquareGridMap.h>
#include "Components.h"
#include "Events.h"

/**
 * System that handles player input, i.e., key presses, mouse movement, etc.
 */
struct InputSystem : public lz::EventListener<KeyPressedEvent>
{
    InputSystem() = default;

    virtual void receive(lz::ECSEngine& engine, const KeyPressedEvent& event)
    {
        const lz::Event &key_event = event.key_event;
        // Get player entity
        auto player_entities = engine.entities_with_components<Player>();
        if (player_entities.size() != 1)
            throw std::runtime_error("There cannot be more than one player entity!");
        else if (player_entities.empty())
            return;  // No player, so don't process input

        lz::Entity &player = *player_entities[0];
        lz::Position2D new_pos = *player.get<lz::Position2D>();

        // Handle movement keys
        switch (key_event.key.code)
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
        }

        // Emit intent of the player to move
        // A different system will check if the player does move, if it hits an enemy,
        // a wall, etc
        engine.emit(MovementIntentEvent{player, new_pos, event.map});
    }
};