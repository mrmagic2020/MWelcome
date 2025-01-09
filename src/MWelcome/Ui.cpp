#include <ll/api/form/CustomForm.h>

#include "Config.h"
#include "magic_enum.hpp"

namespace mwelcome::ui
{
ll::form::CustomForm* createSettingsForm(Config& config)
{
    ll::form::CustomForm* form = new ll::form::CustomForm();
    form->setTitle("MWelcome Settings");

    form->appendDropdown(
        "type", "Welcome Type",
        std::vector<std::string>(magic_enum::enum_names<WelcomeType>().begin(),
                                 magic_enum::enum_names<WelcomeType>().end()),
        magic_enum::enum_integer(config.getType()));

    form->appendInput("toast_title", "Toast Title", {}, config.toast_title);
    form->appendInput("toast_content", "Toast Content", {},
                      config.toast_content);
    form->appendInput("msg_content", "Message Content", {}, config.msg_content);

    return form;
}
}  // namespace mwelcome::ui