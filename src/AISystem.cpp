#include "AISystem.h"

void AISystem::receive(lz::ECSEngine &engine, const RefreshAI &event)
{
    auto npcs = engine.entities_with_components<AI>();
    for (lz::Entity *npc : npcs)
    {
        AIBehaviour behaviour = npc->get<AI>()->behaviour;
        switch (behaviour)
        {
        case AIBehaviour::Follow:
        {
            // TODO: move to a different function
            // TODO: assert npc->has<lz::Position2D>()
            // Follow player entity, if it exists, until adjacent
            lz::Entity *player = event.player;
            if (!player)
                break;
            lz::Position2D pos = *npc->get<lz::Position2D>();
            lz::Position2D player_pos = *player->get<lz::Position2D>();

            // Get current map
            lz::SquareGridMap &map = Dungeon::instance().get_level();

            lz::AStarSearch<lz::Position2D, lz::SquareGridMap> astar_search(
                map, pos, player_pos);
            astar_search.execute();
            if (astar_search.get_state() != lz::SearchState::SUCCESS)
                // No path to player, do nothing
                break;
            auto path = astar_search.getPath();
            if (path.empty())
            {
                // NPC is ON TOP of the player... this should not happen
            }
            else if (path.size() == 1)
            {
                // NPC is adjacent to player
                // TODO: Attack!!
            }
            else
            {
                // Move towards player
                engine.emit<MovementIntentEvent>({*npc, path.front()});
            }
        }
        break;

        default:
            // Do nothing
            break;
        }
    }
}
