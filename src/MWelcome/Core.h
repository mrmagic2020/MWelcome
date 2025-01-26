#pragma once

#include <ll/api/form/ModalForm.h>
#include <mc/world/actor/player/Player.h>

namespace mwelcome::core
{
void sendWelcomeMessage(Player& player,
                        std::optional<ll::form::ModalFormResult> res,
                        std::optional<ll::form::FormCancelReason>);
void sendGlobalWelcomeMessage(const std::string& playerName);
}  // namespace mwelcome::core