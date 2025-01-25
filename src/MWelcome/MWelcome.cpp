#include <fmt/format.h>
#include <ll/api/Config.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/io/FileUtils.h>
#include <ll/api/mod/ModManagerRegistry.h>
#include <ll/api/mod/NativeMod.h>
#include <ll/api/mod/RegisterHelper.h>
#include <mc/network/packet/TextPacket.h>

#include "Command.h"
#include "Config.h"
#include "Event.h"
#include "MWelcome.h"

namespace mwelcome
{
MyMod& MyMod::getInstance()
{
    static MyMod instance;
    return instance;
}

bool MyMod::load() const
{
    const auto& logger = getSelf().getLogger();
    logger.debug("Loading...");
    if (!config::init())
    {
        return false;
    }
    return true;
}

bool MyMod::enable() const
{
    const auto& logger = getSelf().getLogger();
    logger.debug("Starting up...");

    event::init();
    cmd::init();

    logger.info("Enabled!");
    return true;
}

bool MyMod::disable() const
{
    const auto& logger = getSelf().getLogger();
    logger.debug("Disabling...");
    event::unreg();
    return true;
}

bool MyMod::unload() const
{
    const auto& logger = getSelf().getLogger();
    logger.debug("Unloading...");
    return true;
}

}  // namespace mwelcome

LL_REGISTER_MOD(mwelcome::MyMod, mwelcome::MyMod::getInstance());
