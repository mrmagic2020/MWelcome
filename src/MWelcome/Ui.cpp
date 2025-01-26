#include <ll/api/form/CustomForm.h>
#include <ll/api/form/ModalForm.h>
#include <ll/api/i18n/I18n.h>

#include "Config.h"
#include "magic_enum.hpp"

using ll::i18n_literals::operator""_tr;

ll::form::ModalForm* createSettingsSuccessFeedbackForm()
{
    const auto form = new ll::form::ModalForm();
    form->setTitle("ui.settings.modal.success.title"_tr());
    form->setContent("ui.settings.modal.success.content"_tr());
    form->setUpperButton("ui.settings.modal.success.upper_button"_tr());
    form->setLowerButton("ui.settings.modal.success.lower_button"_tr());
    return form;
}

ll::form::ModalForm* createSettingsFailureFeedbackForm()
{
    const auto form = new ll::form::ModalForm();
    form->setTitle("ui.settings.modal.failure.title"_tr());
    form->setContent("ui.settings.modal.failure.content"_tr());
    return form;
}

namespace mwelcome::ui
{

ll::form::CustomForm* createSettingsForm(const Config& config)
{
    const auto form = new ll::form::CustomForm();
    form->setTitle("ui.settings.title"_tr());

    form->appendToggle("send_to_all_players",
                       "ui.settings.send_to_all_players"_tr(),
                       config.send_to_all_players);
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

ll::form::ModalForm* createSettingsFeedbackForm(const bool success)
{
    if (success) return createSettingsSuccessFeedbackForm();
    return createSettingsFailureFeedbackForm();
}
}  // namespace mwelcome::ui