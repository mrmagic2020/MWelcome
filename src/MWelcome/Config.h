#include <string>

#include "ll/api/mod/NativeMod.h"

enum class WelcomeType
{
    CHAT,
    TIP,
    TOAST,

    None
};

struct Config
{
    int version = 1;
    std::string type = "toast";
    std::string toast_title = "§lWelcome to the §bPinnacle§r§l!§r";
    std::string toast_content = "Enjoy your stay, §o§6{}§r!";
    std::string msg_content = "§lWelcome to the §bPinnacle§r, §o§6{}§r!";

    [[nodiscard]] WelcomeType getType()
    {
        if (type == "chat") return WelcomeType::CHAT;
        if (type == "tip") return WelcomeType::TIP;
        if (type == "toast") return WelcomeType::TOAST;
        return WelcomeType::None;
    }
};

namespace mwelcome::configuration
{
bool init(ll::mod::NativeMod& mod, Config& config);
}  // namespace mwelcome::configuration