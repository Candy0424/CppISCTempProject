#pragma once
#include <Windows.h>
#include <string>

// 오픈
bool OpenMciDevice(LPCWSTR _deviceType, LPCWSTR _name, UINT& _deviceid);

// 닫기
void CloseMciDevice(UINT& _deviceId);

enum class SOUNDID
{
    BGM, EXPLOSION, END
};

struct SoundEntry
{
    //LPCWSTR path;     // 파일 경로
    std::wstring path; // 파일 경로
    int     volume;  // 볼륨 (0~1000)  
    UINT    deviceId; // MCI 장치 ID (초기값 0)
};

// 재생
void PlayMciDevice(UINT _deviceid, bool repeat = false);

// 초기화
bool InitAllSounds();
// 재생
void PlaySoundID(SOUNDID _id, bool _repeat = false);
// 릴리즈 
void ReleaseAllSounds();