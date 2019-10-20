#include "Game.h"

#include "version.h"

#include <lazarus/Graphics.h>
#include "VisibilitySystem.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "MovementSystem.h"
#include "AISystem.h"
#include "Components.h"
#include "Dungeon.h"
#include "MainWindow.h"

// TODO: Move abstract game loop logic to lazarus
void game_loop(lz::ECSEngine &engine)
{
    lz::Window &window = MainWindow::get_window();
    while (window.isOpen())
    {
        // Process events
        lz::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case lz::Event::Closed:
                window.close();
                break;
            // The rest of the events are handled by the InputSystem
            default:
                engine.emit(InputEvent{event});
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
    player.add_component<Player>(10);
    engine.add_entity(player);

    // Add some NPCs
    lz::Entity npc;
    npc.add_component<lz::Position2D>(MAP_WIDTH / 2 - 15, MAP_HEIGHT / 2 - 15);
    npc.add_component<Renderable>(MONSTER_IMG);
    npc.add_component<AI>(AIBehaviour::Follow);
    engine.add_entity(npc);

    // Create map with one big room where the player can walk freely
    Dungeon &dungeon = Dungeon::instance();
    int level = dungeon.generate_new_level(MAP_WIDTH, MAP_HEIGHT);
    dungeon.switch_level(level);
    lz::SquareGridMap &map = dungeon.get_level();
    
    // Player position is always floor
    map.set_walkable(MAP_WIDTH / 2, MAP_HEIGHT / 2, true);
    map.set_transparency(MAP_WIDTH / 2, MAP_HEIGHT / 2, true);

    // Load tileset and initialize the main window
    lz::Tileset tileset;
    tileset.load("../res/test_tileset_48x48.png");
    MainWindow::get_window().init(tileset, 19, 19, "CYBORG - A Lazarus game");

    // Create and subscribe the systems as event listeners
    engine.add_system<VisibilitySystem, EntityMovedEvent>();
    engine.add_system<InputSystem, InputEvent>();
    engine.add_system<MovementSystem, MovementIntentEvent>();
    engine.add_system<AISystem, RefreshAI>();
    engine.add_system<RenderSystem, ResetCameraEvent>();
    // Set render system to update every tick
    engine.add_updateable<RenderSystem>();

    // Emit a first event so that the FOV is computed on game start
    engine.emit<EntityMovedEvent>({});
    // Reset camera
    engine.emit<ResetCameraEvent>({&player});

    game_loop(engine);

    return 0;
}
