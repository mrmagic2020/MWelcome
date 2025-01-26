#include "Core.h"

#include <ll/api/service/Bedrock.h>
#include <mc/network/packet/TextPacket.h>
#include <mc/network/packet/TextPacketType.h>
#include <mc/network/packet/ToastRequestPacket.h>
#include <mc/world/level/Level.h>

#include "Config.h"
#include "MWelcome.h"

namespace mwelcome::core
{
void sendWelcomeMessage(Player& player, const std::string& playerName)
{
    const auto&        logger = MyMod::getInstance().getSelf().getLogger();
    TextPacket         chat_pkt;
    ToastRequestPacket toast_pkt;

    switch (const Config config = config::get(); config.getType())
    {
        case WelcomeType::CHAT:
            chat_pkt.mType    = TextPacketType::SystemMessage;
            chat_pkt.mMessage = std::vformat(config.msg_content,
                                             std::make_format_args(playerName));
            player.sendNetworkPacket(chat_pkt);
            break;
        case WelcomeType::TIP:
            chat_pkt.mType    = TextPacketType::Tip;
            chat_pkt.mMessage = std::vformat(config.msg_content,
                                             std::make_format_args(playerName));
            player.sendNetworkPacket(chat_pkt);
            break;
        case WelcomeType::TOAST:
            toast_pkt.mTitle   = std::vformat(config.toast_title,
                                              std::make_format_args(playerName));
            toast_pkt.mContent = std::vformat(
                config.toast_content, std::make_format_args(playerName));
            player.sendNetworkPacket(toast_pkt);
            break;
        default:
            logger.error("Unknown welcome type: {}", config.type);
            break;
    }
}

void sendSingleWelcomeMessage(Player&                                  player,
                              std::optional<ll::form::ModalFormResult> res,
                              std::optional<ll::form::FormCancelReason>)
{
    if (res.has_value() && res.value().has_value() &&
            res.value().value() == ll::form::ModalFormSelectedButton::Lower ||
        res.has_value() && !res.value().has_value())
        return;
    sendWelcomeMessage(player, player.getRealName());
}

void sendGlobalWelcomeMessage(const std::string& playerName)
{
    const auto& logger = MyMod::getInstance().getSelf().getLogger();
    const auto& level  = ll::service::getLevel();
    if (!level.has_value())
    {
        logger.error("Failed to load ll::service::getLevel()");
        return;
    }
    level->forEachPlayer(
        [&](Player& player)
        {
            sendWelcomeMessage(player, playerName);
            return true;
        });
}

}  // namespace mwelcome::core