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
    auto& logger   = MyMod::getInstance().getSelf().getLogger();
    auto& eventBus = ll::event::EventBus::getInstance();

    playerJoinEventListener =
        eventBus.emplaceListener<ll::event::player::PlayerJoinEvent>(
            [](const ll::event::player::PlayerJoinEvent& e)
            {
                core::sendWelcomeMessage(e.self(), std::nullopt, std::nullopt);
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