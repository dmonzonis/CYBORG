#include "version.h"

#include <lazarus/common.h>
#include <lazarus/Graphics.h>
#include <lazarus/FOV.h>
#include <lazarus/Random.h>
#include "VisibilitySystem.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "MovementSystem.h"
#include "Components.h"

using namespace std;

// Map dimensions
constexpr int MAP_WIDTH = 60;
constexpr int MAP_HEIGHT = 40;

// Tile IDs
// TODO: Remove this
constexpr int PLAYER_IMG = 0;

// TODO: Move abstract game loop logic to lazarus
void game_loop(lz::ECSEngine &engine, lz::Window &window, lz::SquareGridMap &map)
{
    while (window.is_open())
    {
        // Process events
        lz::Event event;
        while (window.poll_event(event))
        {
            switch (event.type)
            {
            case lz::Event::Closed:
                window.close();
                break;
            case lz::Event::KeyPressed:
                // TODO: Add key press to a queue and handle them all later to be
                // able to parse key combinations
                engine.emit(KeyPressedEvent{event, map});
                break;
            }
        }

        // Update all systems that require updating
        engine.update();

        // Render window
        window.render();
    }
}

int main(int argc, char const *argv[])
{
    DEBUG("Version %d.%d", PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR);

    // Create engine
    lz::ECSEngine engine;

    // Create player entity and set it at the center
    lz::Entity player;
    player.add_component<lz::Position2D>(MAP_WIDTH / 2, MAP_HEIGHT / 2);
    player.add_component<Renderable>(PLAYER_IMG);
    player.add_component<Player>();
    engine.add_entity(player);

    // Create map with one big room where the player can walk freely
    lz::SquareGridMap map(MAP_WIDTH, MAP_HEIGHT);
    // Randomize walls. Each tile has a 20% prob of being wall
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            bool wall = lz::Random::one_in(5);
            if (!wall)
            {
                map.set_walkable(x, y, true);
                map.set_transparency(x, y, true);
            }
        }
    }
    
    // Player position is always floor
    map.set_walkable(MAP_WIDTH / 2, MAP_HEIGHT / 2, true);
    map.set_transparency(MAP_WIDTH / 2, MAP_HEIGHT / 2, true);

    // Create display window and load tileset
    lz::Window window(MAP_WIDTH, MAP_HEIGHT);
    window.load_tileset("../res/test_tileset.png", 24);

    // Create systems and subscribe them
    VisibilitySystem visibility_system(map, 10);
    InputSystem input_system;
    MovementSystem movement_system;
    RenderSystem render_system(window, map, visibility_system);
    // Subscribe the systems as event listeners
    engine.subscribe<EntityMovedEvent>(&visibility_system);
    engine.subscribe<KeyPressedEvent>(&input_system);
    engine.subscribe<MovementIntentEvent>(&movement_system);
    // Set render system to update every tick
    engine.register_updateable(&render_system);

    // Emit a first event so that the FOV is computed on game start
    engine.emit<EntityMovedEvent>({map});

    // TODO: Store current map in engine, or somewhere more accessible for events
    game_loop(engine, window, map);

    return 0;
}
