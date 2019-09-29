#pragma once

#include <lazarus/ECS.h>
#include <lazarus/SquareGridMap.h>
#include "Events.h"

/**
 * System that handles player input, i.e., key presses, mouse movement, etc.
 */
struct InputSystem : public lz::EventListener<KeyPressedEvent>
{
    virtual void receive(lz::ECSEngine& engine, const KeyPressedEvent& event)
    {
        const lz::Event &key_event = event.key_event;
        // Get player position
        if (player_id == -1)
            return;
        lz::Entity *player = engine.get_entity(player_id);
        if (!player)
            return;
        lz::Position2D &player_pos = *player->get<lz::Position2D>();
        lz::Position2D new_pos = player_pos;

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

        // Move player to the new position
        // TODO: Check out of bounds, obstacles, etc
        player_pos = new_pos;
        
        // Emit player movement event to recalculate FOV
        engine.emit(PlayerMovedEvent{player_pos, event.map});
    }

    lz::Identifier player_id = -1;
};