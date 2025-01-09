#include <fmt/format.h>
#include <ll/api/Config.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/ListenerBase.h>
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/io/FileUtils.h>
#include <ll/api/mod/ModManagerRegistry.h>
#include <ll/api/mod/NativeMod.h>
#include <ll/api/mod/RegisterHelper.h>
#include <ll/api/service/Bedrock.h>
#include <mc/network/packet/TextPacket.h>
#include <mc/network/packet/TextPacketType.h>
#include <mc/network/packet/ToastRequestPacket.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/level/Level.h>

#include <format>

#include "Command.h"
#include "Config.h"
#include "MWelcome.h"

ll::event::ListenerPtr playerJoinEventListener;

namespace mwelcome
{
MyMod& MyMod::getInstance()
{
    static MyMod instance;
    return instance;
}

bool MyMod::load()
{
    auto& logger = getSelf().getLogger();
    logger.debug("Loading...");
    if (!config::init(getSelf()))
    {
        return false;
    }
    return true;
}

bool MyMod::enable()
{
    auto& logger = getSelf().getLogger();
    logger.debug("Starting up...");

    auto& eventBus = ll::event::EventBus::getInstance();

    playerJoinEventListener =
        eventBus.emplaceListener<ll::event::player::PlayerJoinEvent>(
            [&logger](ll::event::player::PlayerJoinEvent& e) {
                Player& player = e.self();
                const std::string& playerName = player.getRealName();

                TextPacket chat_pkt;
                const Config config = config::get();
                switch (config.getType())
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

    cmd::init();

    logger.info("Enabled!");
    return true;
}

bool MyMod::disable()
{
    auto& logger = getSelf().getLogger();
    logger.debug("Disabling...");
    auto& eventBus = ll::event::EventBus::getInstance();
    eventBus.removeListener(playerJoinEventListener);
    return true;
}

bool MyMod::unload()
{
    auto& logger = getSelf().getLogger();
    logger.debug("Unloading...");
    return true;
}

}  // namespace mwelcome

LL_REGISTER_MOD(mwelcome::MyMod, mwelcome::MyMod::getInstance());
