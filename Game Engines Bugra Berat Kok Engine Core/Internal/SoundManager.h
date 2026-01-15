#pragma once
#include "Singleton.h"
#include <SDL_mixer.h>
#include <string>
#include <map>

class SoundManager : public Singleton<SoundManager>
{
    friend class Singleton<SoundManager>;

private:
    SoundManager();
    ~SoundManager();

    // Müzikler (uzun, loop eden)
    std::map<std::string, Mix_Music*> musics;

    // Ses efektleri (kısa, tekrar çalınabilir)
    std::map<std::string, Mix_Chunk*> sounds;

    float musicVolume;  // 0.0 - 1.0
    float sfxVolume;    // 0.0 - 1.0

public:
    // Başlatma (SDL_mixer init)
    bool Init();

    // Müzik yükleme
    bool LoadMusic(const std::string& id, const std::string& filePath);

    // Ses efekti yükleme
    bool LoadSound(const std::string& id, const std::string& filePath);

    // Müzik çalma
    void PlayMusic(const std::string& id, int loops = -1); // -1 = sonsuz loop
    void StopMusic();
    void PauseMusic();
    void ResumeMusic();

    // Ses efekti çalma
    void PlaySound(const std::string& id, int loops = 0); // 0 = bir kere

    // Volume kontrolü (0.0 - 1.0)
    void SetMusicVolume(float volume);
    void SetSFXVolume(float volume);
    float GetMusicVolume() const { return musicVolume; }
    float GetSFXVolume() const { return sfxVolume; }

    // Temizlik
    void UnloadMusic(const std::string& id);
    void UnloadSound(const std::string& id);
    void UnloadAll();
};