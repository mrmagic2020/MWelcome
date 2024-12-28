#include <fmt/format.h>
#include <ll/api/Config.h>
#include <ll/api/command/Command.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/data/KeyValueDB.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/ListenerBase.h>
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/event/player/PlayerUseItemEvent.h>
#include <ll/api/form/ModalForm.h>
#include <ll/api/io/FileUtils.h>
#include <ll/api/mod/ModManagerRegistry.h>
#include <ll/api/mod/NativeMod.h>
#include <ll/api/service/Bedrock.h>
#include <mc/entity/utilities/ActorType.h>
#include <mc/network/packet/ToastRequestPacket.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/server/commands/CommandPermissionLevel.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/item/registry/ItemStack.h>

#include <format>
#include <memory>

// #include "Config.h"
#include "MWelcome.h"
#include "ll/api/mod/RegisterHelper.h"

ll::event::ListenerPtr playerJoinEventListener;

namespace mwelcome
{
static std::unique_ptr<MyMod> instance;

MyMod& MyMod::getInstance() { return *instance; }

bool MyMod::load()
{
    auto& logger = getSelf().getLogger();
    logger.info("Loading...");
    // Code for loading the mod goes here.
    return true;
}

bool MyMod::enable()
{
    auto& logger = getSelf().getLogger();
    logger.info("Starting up...");

    // Register the event listener.
    auto& eventBus = ll::event::EventBus::getInstance();

    // Subscribe to the PlayerJoinEvent.
    playerJoinEventListener =
        eventBus.emplaceListener<ll::event::player::PlayerJoinEvent>(
            [](ll::event::player::PlayerJoinEvent& e) {
                // Show a welcome message to the player.
                auto& player = e.self();
                ToastRequestPacket pkt = ToastRequestPacket(
                    std::format("Welcome, {}!", player.getRealName()),
                    "Enjoy your time in the Pinnalce~");
                player.sendNetworkPacket(pkt);
            });

    return true;
}

bool MyMod::disable()
{
    getSelf().getLogger().debug("Disabling...");
    // Code for disabling the mod goes here.
    return true;
}

}  // namespace mwelcome

LL_REGISTER_MOD(mwelcome::MyMod, mwelcome::instance);
