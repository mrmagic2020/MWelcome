#pragma once

#include <ll/api/form/CustomForm.h>

#include "Config.h"

namespace mwelcome::ui
{
ll::form::CustomForm* createSettingsForm(const Config& config);
}