#include "Event.h"

#include <ll/api/event/EventBus.h>
#include <ll/api/event/ListenerBase.h>
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <mc/world/actor/player/Player.h>

#include "Config.h"
#include "Core.h"
#include "MWelcome.h"

ll::event::ListenerPtr playerJoinEventListener;

namespace mwelcome::event
{
bool init()
{
    const auto& logger   = MyMod::getInstance().getSelf().getLogger();
    auto&       eventBus = ll::event::EventBus::getInstance();

    playerJoinEventListener =
        eventBus.emplaceListener<ll::event::player::PlayerJoinEvent>(
            [](const ll::event::player::PlayerJoinEvent& e)
            {
                if (const Config& config = config::get();
                    config.send_to_all_players)
                    core::sendGlobalWelcomeMessage(e.self().getRealName());
                else core::sendSingleWelcomeMessage(e.self());
            });

    logger.debug("Event registered.");
    return true;
}

bool unreg()
{
    auto& eventBus = ll::event::EventBus::getInstance();
    eventBus.removeListener(playerJoinEventListener);
    return true;
}
}  // namespace mwelcome::event