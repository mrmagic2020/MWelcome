#include <ll/api/command/Command.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/form/CustomForm.h>
#include <ll/api/i18n/I18n.h>
#include <ll/api/service/Bedrock.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/server/commands/CommandPermissionLevel.h>
#include <mc/world/actor/Actor.h>
#include <mc/world/actor/ActorType.h>

#include <string>

#include "Config.h"
#include "Core.h"
#include "MWelcome.h"
#include "Ui.h"

namespace mwelcome::cmd
{
using ll::i18n_literals::operator""_tr;

bool init()
{
    const auto& logger = MyMod::getInstance().getSelf().getLogger();
    if (const auto commandRegistry = ll::service::getCommandRegistry();
        !commandRegistry)
    {
        logger.error("Failed to get command registry.");
        return false;
    }

    auto& command =
        ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
            "mwelcome", "command.mwelcome.description"_tr(),
            CommandPermissionLevel::GameDirectors);
    command.overload().execute(
        [](CommandOrigin const& origin, CommandOutput& output)
        {
            auto* entity = origin.getEntity();
            if (entity == nullptr || !entity->isType(ActorType::Player))
            {
                output.error("This command can only be run by players.");
                return;
            }

            auto*                 player = static_cast<Player*>(entity);
            ll::form::CustomForm* form = ui::createSettingsForm(config::get());
            form->sendTo(
                *player,
                [](Player& _player, ll::form::CustomFormResult const& res,
                   const ll::form::FormCancelReason reason)
                {
                    if (reason.has_value() || !res.has_value())
                    {
                        return;
                    }

                    Config& config = config::get();
                    for (const auto& [key, val] : res.value())
                    {
                        if (key == "type")
                        {
                            config.setType(std::get<std::string>(val));
                        }
                        else if (key == "toast_title")
                        {
                            config.toast_title = std::get<std::string>(val);
                        }
                        else if (key == "toast_content")
                        {
                            config.toast_content = std::get<std::string>(val);
                        }
                        else if (key == "msg_content")
                        {
                            config.msg_content = std::get<std::string>(val);
                        }
                    }
                    if (config::set(config, true))

                        ui::createSettingsFeedbackForm(true)->sendTo(
                            _player, core::sendWelcomeMessage);

                    else ui::createSettingsFeedbackForm(false)->sendTo(_player);
                });
        });

    logger.debug("Command registered.");
    return true;
}
}  // namespace mwelcome::cmd