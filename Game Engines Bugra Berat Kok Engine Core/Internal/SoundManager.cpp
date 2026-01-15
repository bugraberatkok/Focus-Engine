#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
    : musicVolume(0.5f), sfxVolume(0.7f)
{
}

SoundManager::~SoundManager()
{
    UnloadAll();
    Mix_CloseAudio();
    Mix_Quit();
}

bool SoundManager::Init()
{
    // SDL_mixer'ı başlat
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
        return false;
    }

    // Kaç kanal kullanacağımızı ayarla (eşzamanlı ses sayısı)
    Mix_AllocateChannels(16);

    std::cout << "SoundManager initialized successfully!" << std::endl;
    return true;
}

bool SoundManager::LoadMusic(const std::string& id, const std::string& filePath)
{
    // Zaten yüklüyse döndür
    auto it = musics.find(id);
    if (it != musics.end())
    {
        std::cout << "Music already loaded: " << id << std::endl;
        return true;
    }

    Mix_Music* music = Mix_LoadMUS(filePath.c_str());

    if (!music)
    {
        std::cerr << "Failed to load music: " << filePath
            << " | Error: " << Mix_GetError() << std::endl;
        return false;
    }

    musics[id] = music;
    std::cout << "Music loaded: " << id << " (" << filePath << ")" << std::endl;
    return true;
}

bool SoundManager::LoadSound(const std::string& id, const std::string& filePath)
{
    // Zaten yüklüyse döndür
    auto it = sounds.find(id);
    if (it != sounds.end())
    {
        std::cout << "Sound already loaded: " << id << std::endl;
        return true;
    }

    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());

    if (!sound)
    {
        std::cerr << "Failed to load sound: " << filePath
            << " | Error: " << Mix_GetError() << std::endl;
        return false;
    }

    sounds[id] = sound;
    std::cout << "Sound loaded: " << id << " (" << filePath << ")" << std::endl;
    return true;
}

void SoundManager::PlayMusic(const std::string& id, int loops)
{
    auto it = musics.find(id);
    if (it == musics.end())
    {
        std::cerr << "Music not found: " << id << std::endl;
        return;
    }

    if (Mix_PlayMusic(it->second, loops) == -1)
    {
        std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
    }
}

void SoundManager::StopMusic()
{
    Mix_HaltMusic();
}

void SoundManager::PauseMusic()
{
    Mix_PauseMusic();
}

void SoundManager::ResumeMusic()
{
    Mix_ResumeMusic();
}

void SoundManager::PlaySound(const std::string& id, int loops)
{
    auto it = sounds.find(id);
    if (it == sounds.end())
    {
        std::cerr << "Sound not found: " << id << std::endl;
        return;
    }

    // -1 = herhangi bir boş kanalda çal
    if (Mix_PlayChannel(-1, it->second, loops) == -1)
    {
        std::cerr << "Failed to play sound: " << Mix_GetError() << std::endl;
    }
}

void SoundManager::SetMusicVolume(float volume)
{
    musicVolume = volume;
    if (musicVolume < 0.0f) musicVolume = 0.0f;
    if (musicVolume > 1.0f) musicVolume = 1.0f;

    // SDL_mixer volume range: 0-128
    Mix_VolumeMusic(static_cast<int>(musicVolume * MIX_MAX_VOLUME));
}

void SoundManager::SetSFXVolume(float volume)
{
    sfxVolume = volume;
    if (sfxVolume < 0.0f) sfxVolume = 0.0f;
    if (sfxVolume > 1.0f) sfxVolume = 1.0f;

    // Tüm sound chunk'lar için volume ayarla
    for (auto& pair : sounds)
    {
        Mix_VolumeChunk(pair.second, static_cast<int>(sfxVolume * MIX_MAX_VOLUME));
    }
}

void SoundManager::UnloadMusic(const std::string& id)
{
    auto it = musics.find(id);
    if (it != musics.end())
    {
        Mix_FreeMusic(it->second);
        musics.erase(it);
    }
}

void SoundManager::UnloadSound(const std::string& id)
{
    auto it = sounds.find(id);
    if (it != sounds.end())
    {
        Mix_FreeChunk(it->second);
        sounds.erase(it);
    }
}

void SoundManager::UnloadAll()
{
    // Tüm müzikleri temizle
    for (auto& pair : musics)
    {
        Mix_FreeMusic(pair.second);
    }
    musics.clear();

    // Tüm sesleri temizle
    for (auto& pair : sounds)
    {
        Mix_FreeChunk(pair.second);
    }
    sounds.clear();

    std::cout << "All sounds and music unloaded." << std::endl;
}