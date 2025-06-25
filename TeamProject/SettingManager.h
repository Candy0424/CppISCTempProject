#pragma once
#include "NodeStyleConfig.h"
#include "Defines.h"
#include "PlayerNodeStyle.h"

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
    PlayerNodeStyle& GetPlayerStyle() { return playerStyle; }
    const PlayerNodeStyle& GetPlayerStyle() const { return playerStyle; }
    void SetPlayerStyle(const PlayerNodeStyle& style) { playerStyle = style; }
private:
    NodeStyleConfig config;
    PlayerNodeStyle playerStyle;
    SettingManager() = default;
    SettingManager(const SettingManager&) = delete;
    SettingManager& operator=(const SettingManager&) = delete;
    static SettingManager* instance;
};
