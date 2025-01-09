#include <ll/api/command/Command.h>
#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/form/CustomForm.h>
#include <ll/api/service/Bedrock.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/server/commands/CommandPermissionLevel.h>
#include <mc/world/actor/Actor.h>
#include <mc/world/actor/ActorType.h>

#include <stdexcept>
#include <string>

#include "Config.h"
#include "Ui.h"

namespace mwelcome::cmd
{
bool init()
{
    auto commandRegistry = ll::service::getCommandRegistry();
    if (!commandRegistry)
    {
        throw std::runtime_error("Failed to load command registry");
    }

    auto& command =
        ll::command::CommandRegistrar::getInstance().getOrCreateCommand(
            "mwelcome", "Configure MWelcome settings.",
            CommandPermissionLevel::GameDirectors);
    command.overload().execute([](CommandOrigin const& origin,
                                  CommandOutput& output) {
        auto* entity = origin.getEntity();
        if (entity == nullptr || !entity->isType(ActorType::Player))
        {
            output.error("This command can only be run by players.");
            return;
        }

        auto* player = static_cast<Player*>(entity);
        ll::form::CustomForm* form = ui::createSettingsForm(config::get());
        form->sendTo(*player, [](Player& player,
                                 ll::form::CustomFormResult const& res,
                                 ll::form::FormCancelReason reason) {
            if (reason.has_value() || !res.has_value())
            {
                return;
            }

            Config& config = config::get();
            for (auto& entry : res.value())
            {
                if (entry.first == "type")
                {
                    config.setType(std::get<std::string>(entry.second));
                }
                else if (entry.first == "toast_title")
                {
                    config.toast_title = std::get<std::string>(entry.second);
                }
                else if (entry.first == "toast_content")
                {
                    config.toast_content = std::get<std::string>(entry.second);
                }
                else if (entry.first == "msg_content")
                {
                    config.msg_content = std::get<std::string>(entry.second);
                }
            }
            if (config::set(config, true))
            {
                player.sendMessage(
                    "[MWelcome] §aSettings updated successfully.");
            }
            else
            {
                player.sendMessage("[MWelcome] §cFailed to update settings.");
            }
        });
    });

    return true;
}
}  // namespace mwelcome::cmd