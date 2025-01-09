#include <ll/api/Config.h>
#include <ll/api/mod/NativeMod.h>

#include <filesystem>

#include "Config.h"

namespace mwelcome::config
{
Config _config;
std::filesystem::path _configPath;

bool init(ll::mod::NativeMod& mod)
{
    _configPath = mod.getConfigDir() / "config.json";
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
    if (!ll::config::loadConfig(_config, _configPath))
    {

        if (!ll::config::saveConfig(_config, _configPath))
        {
            return false;
        }
    }
    return true;
}
}  // namespace mwelcome::config
