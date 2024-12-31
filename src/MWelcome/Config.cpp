#include "Config.h"
#include "ll/api/Config.h"
#include "ll/api/mod/NativeMod.h"

namespace mwelcome::configuration
{
bool init(ll::mod::NativeMod& mod, Config& config)
{
    auto& logger = mod.getLogger();
    const auto& configPath = mod.getConfigDir() / "config.json";
    if (!ll::config::loadConfig(config, configPath))
    {
        logger.warn("Cannot load configurations from {}", configPath);
        logger.info("Generating default configurations");

        if (!ll::config::saveConfig(config, configPath))
        {
            logger.error("Cannot save default configurations to {}",
                         configPath);
            return false;
        }
    }
    return true;
}
}  // namespace mwelcome::config
