#include "Config.h"

#include <ll/api/Config.h>
#include <ll/api/mod/NativeMod.h>

#include <filesystem>

#include "MWelcome.h"

namespace mwelcome::config
{
Config                _config;
std::filesystem::path _configPath;

bool init()
{
    _configPath = MyMod::getInstance().getSelf().getConfigDir() / "config.json";
    return load();
}

Config& get() { return _config; }

bool set(const Config& config, bool save)
{
    _config = config;
    if (save)
    {
        return ll::config::saveConfig(_config, _configPath);
    }
    return true;
}

bool load()
{
    const auto& logger = MyMod::getInstance().getSelf().getLogger();
    if (!ll::config::loadConfig(_config, _configPath))
    {
        logger.info("Config file not found at '{}', creating default config.",
                    _configPath.string());
        if (!ll::config::saveConfig(_config, _configPath))
        {
            logger.fatal("Failed to save default config to '{}'.",
                         _configPath.string());
            return false;
        }
    }
    logger.debug("Config loaded from '{}'.", _configPath.string());
    return true;
}
}  // namespace mwelcome::config
