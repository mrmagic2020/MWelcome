#pragma once

#include <ll/api/form/CustomForm.h>
#include <ll/api/form/ModalForm.h>

#include "Config.h"

namespace mwelcome::ui
{
ll::form::CustomForm* createSettingsForm(const Config& config);
ll::form::ModalForm*  createSettingsFeedbackForm(bool success);
}  // namespace mwelcome::ui