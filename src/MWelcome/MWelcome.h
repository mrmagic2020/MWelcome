#pragma once

#include "ll/api/mod/NativeMod.h"

namespace mwelcome
{

class MyMod
{
public:
    static MyMod& getInstance();

    MyMod() : mSelf(*ll::mod::NativeMod::current()) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    /// @return True if the mod is loaded successfully.
    bool load() const;

    /// @return True if the mod is enabled successfully.
    bool enable() const;

    /// @return True if the mod is disabled successfully.
    bool disable() const;

    /// @return True if the mod is unloaded successfully.
    bool unload() const;

private:
    ll::mod::NativeMod& mSelf;
};

}  // namespace mwelcome
