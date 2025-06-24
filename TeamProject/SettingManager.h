#pragma once
#include "NodeStyleConfig.h"
#include "Defines.h"

class SettingManager
{
public:
    static SettingManager* GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new SettingManager();
        }
        return instance;
    }
    static void DestroyInstance()
    {
        SAFE_DELETE(instance);
    }
    NodeStyleConfig& GetConfig() { return config; }
    const NodeStyleConfig& GetConfig() const { return config; }
private:
    NodeStyleConfig config;
    SettingManager() = default;
    SettingManager(const SettingManager&) = delete;
    SettingManager& operator=(const SettingManager&) = delete;
    static SettingManager* instance;
};
