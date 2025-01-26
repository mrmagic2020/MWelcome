#pragma once

#include <magic_enum.hpp>
#include <string>

enum class WelcomeType
{
    CHAT,
    TIP,
    TOAST,

    None
};

struct Config
{
    int         version             = 2;
    bool        send_to_all_players = false;
    std::string type                = "toast";
    std::string toast_title         = "§lWelcome to the §bServer§r§l!§r";
    std::string toast_content       = "Enjoy your stay, §o§6{}§r!";
    std::string msg_content         = "§lWelcome to the §bServer§r, §o§6{}§r!";

    [[nodiscard]] WelcomeType getType() const
    {
        if (type == "chat") return WelcomeType::CHAT;
        if (type == "tip") return WelcomeType::TIP;
        if (type == "toast") return WelcomeType::TOAST;
        return WelcomeType::None;
    }

    void setType(const WelcomeType _type)
    {
        switch (_type)
        {
            case WelcomeType::CHAT:
                type = "chat";
                break;
            case WelcomeType::TIP:
                type = "tip";
                break;
            case WelcomeType::TOAST:
            default:
                type = "toast";
                break;
        }
    }

    void setType(const std::string& _type)
    {
        const WelcomeType t =
            magic_enum::enum_cast<WelcomeType>(_type).value_or(
                WelcomeType::TOAST);
        setType(t);
    }
};

namespace mwelcome::config
{
bool    init();
Config& get();
bool    set(const Config& config, bool save = true);
bool    load();
}  // namespace mwelcome::config