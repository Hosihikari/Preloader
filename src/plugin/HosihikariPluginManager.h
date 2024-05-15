#pragma once

#include <ll/api/plugin/Manifest.h>
#include <ll/api/plugin/PluginManager.h>
#include <string_view>

#include "HosihikariPlugin.h"

namespace hosihikari {

class HosihikariPluginManager : public ll::plugin::PluginManager {
public:
    HosihikariPluginManager();

    HosihikariPluginManager(const HosihikariPluginManager&)                    = delete;
    HosihikariPluginManager(HosihikariPluginManager&&)                         = delete;
    auto operator=(const HosihikariPluginManager&) -> HosihikariPluginManager& = delete;
    auto operator=(HosihikariPluginManager&&) -> HosihikariPluginManager&      = delete;

    ~HosihikariPluginManager() override = default;

private:
    ll::Expected<> load(ll::plugin::Manifest manifest) override;
    ll::Expected<> unload(std::string_view name) override;

private:
    static std::pair<PluginHandle::InteropArg, PluginHandle> loadPlugin(char const* path);

    using plugin_manager_method_fn =
        void(__stdcall*)(char const*, void**, PluginHandle::InteropArg*, PluginHandle::plugin_handle_callback_t*);

    static plugin_manager_method_fn mLoadPlugin;
    static bool                     mfptrInitialized;

public:
    static void initialize_methods();
};

} // namespace hosihikari