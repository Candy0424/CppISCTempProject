#pragma once
#include <Windows.h>
#include <string>

// ����
bool OpenMciDevice(LPCWSTR _deviceType, LPCWSTR _name, UINT& _deviceid);

// �ݱ�
void CloseMciDevice(UINT& _deviceId);

enum class SOUNDID
{
    BGM, EXPLOSION, END
};

struct SoundEntry
{
    //LPCWSTR path;     // ���� ���
    std::wstring path; // ���� ���
    int     volume;  // ���� (0~1000)  
    UINT    deviceId; // MCI ��ġ ID (�ʱⰪ 0)
};

// ���
void PlayMciDevice(UINT _deviceid, bool repeat = false);

// �ʱ�ȭ
bool InitAllSounds();
// ���
void PlaySoundID(SOUNDID _id, bool _repeat = false);
// ������ 
void ReleaseAllSounds();