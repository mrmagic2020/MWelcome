#include <ll/api/form/CustomForm.h>
#include <ll/api/i18n/I18n.h>

#include "Config.h"
#include "magic_enum.hpp"

namespace mwelcome::ui
{
using ll::i18n_literals::operator""_tr;

ll::form::CustomForm* createSettingsForm(const Config& config)
{
    const auto form = new ll::form::CustomForm();
    form->setTitle("ui.settings.title"_tr());

    form->appendDropdown(
        "type", "ui.settings.welcome_type"_tr(),
        std::vector<std::string>(magic_enum::enum_names<WelcomeType>().begin(),
                                 magic_enum::enum_names<WelcomeType>().end()),
        magic_enum::enum_integer(config.getType()));

    form->appendInput("toast_title", "ui.settings.toast_title"_tr(), {},
                      config.toast_title);
    form->appendInput("toast_content", "ui.settings.toast_content"_tr(), {},
                      config.toast_content);
    form->appendInput("msg_content", "ui.settings.msg_content"_tr(), {},
                      config.msg_content);

    return form;
}
}  // namespace mwelcome::ui