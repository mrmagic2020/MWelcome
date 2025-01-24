#include "Event.h"

#include <ll/api/event/EventBus.h>
#include <ll/api/event/ListenerBase.h>
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <mc/network/packet/TextPacket.h>
#include <mc/network/packet/TextPacketType.h>
#include <mc/network/packet/ToastRequestPacket.h>
#include <mc/world/actor/player/Player.h>

#include "Config.h"
#include "MWelcome.h"

ll::event::ListenerPtr playerJoinEventListener;

namespace mwelcome::event
{
bool init()
{
    auto& logger = MyMod::getInstance().getSelf().getLogger();
    auto& eventBus = ll::event::EventBus::getInstance();

    playerJoinEventListener =
        eventBus.emplaceListener<ll::event::player::PlayerJoinEvent>(
            [&logger](const ll::event::player::PlayerJoinEvent& e)
            {
                const Player& player = e.self();
                const std::string& playerName = player.getRealName();

                TextPacket chat_pkt;
                switch (const Config config = config::get(); config.getType())
                {
                    case WelcomeType::CHAT:
                        chat_pkt.mType = TextPacketType::SystemMessage;
                        chat_pkt.mMessage =
                            std::vformat(config.msg_content,
                                         std::make_format_args(playerName));
                        player.sendNetworkPacket(chat_pkt);
                        break;
                    case WelcomeType::TIP:
                        chat_pkt.mType = TextPacketType::Tip;
                        chat_pkt.mMessage =
                            std::vformat(config.msg_content,
                                         std::make_format_args(playerName));
                        player.sendNetworkPacket(chat_pkt);
                        break;
                    case WelcomeType::TOAST:
                    {
                        ToastRequestPacket toast_pkt(
                            std::vformat(config.toast_title,
                                         std::make_format_args(playerName)),
                            std::vformat(config.toast_content,
                                         std::make_format_args(playerName)));
                        player.sendNetworkPacket(toast_pkt);
                        break;
                    }
                    default:
                        logger.error("Unknown welcome type: {}", config.type);
                        break;
                }
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