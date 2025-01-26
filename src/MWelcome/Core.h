#pragma once

#include <ll/api/form/ModalForm.h>
#include <mc/world/actor/player/Player.h>

namespace mwelcome::core
{
void sendSingleWelcomeMessage(
    Player& player, std::optional<ll::form::ModalFormResult> res = std::nullopt,
    std::optional<ll::form::FormCancelReason> = std::nullopt);
void sendGlobalWelcomeMessage(const std::string& playerName);
}  // namespace mwelcome::core