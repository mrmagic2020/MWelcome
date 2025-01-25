#include "i18n.h"

#include <ll/api/i18n/I18n.h>

#include "Config.h"
#include "MWelcome.h"

namespace mwelcome::i18n
{
bool init()
{
    const auto& logger = MyMod::getInstance().getSelf().getLogger();

    const auto res = ll::i18n::getInstance().load(
        MyMod::getInstance().getSelf().getLangDir());
    if (!res)
    {
        logger.error("Failed to load i18n.");
        return false;
    }

    logger.debug("i18n loaded.");
    return true;
}
}  // namespace mwelcome::i18n