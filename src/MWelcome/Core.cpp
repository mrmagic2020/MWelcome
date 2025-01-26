#include "Core.h"

#include <mc/network/packet/TextPacket.h>
#include <mc/network/packet/TextPacketType.h>
#include <mc/network/packet/ToastRequestPacket.h>

#include "Config.h"
#include "MWelcome.h"

namespace mwelcome::core
{
void sendWelcomeMessage(Player&                                  player,
                        std::optional<ll::form::ModalFormResult> res,
                        std::optional<ll::form::FormCancelReason>)
{
    if (res.has_value() && res.value().has_value() &&
            res.value().value() == ll::form::ModalFormSelectedButton::Lower ||
        res.has_value() && !res.value().has_value())
        return;

    const auto&       logger     = MyMod::getInstance().getSelf().getLogger();
    const std::string playerName = player.getRealName();
    TextPacket        chat_pkt;

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
}

}  // namespace mwelcome::core