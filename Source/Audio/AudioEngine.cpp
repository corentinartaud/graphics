//
//  AudioEngine.cpp
//  COMP371_Framework
//
//  Created by Corentin Artaud on 2019-08-09.
//  Copyright © 2019 Concordia. All rights reserved.
//

#include "AudioEngine.h"
#include <iostream>

AudioEngine::AudioEngine() {
    mAudioEngine = irrklang::createIrrKlangDevice();
    mAudioEngine->setDefault3DSoundMinDistance(15.0f);
    mAudioEngine->setRolloffFactor(0.1f);
}

AudioEngine::~AudioEngine() {
    delete mAudioEngine;
}

void AudioEngine::PlaySound(std::string name, bool loop, float volume, bool startRandom) {
    if (loop && mAudioEngine->isCurrentlyPlaying(mAudioEngine->getSoundSource(name.c_str())))
        return;
    irrklang::ISound *sound = mAudioEngine->play2D(name.c_str(), loop, true);
    if (sound) {
        // if start random, start audio at random buffer offset
        if (startRandom)
            sound->setPlayPosition(rand() % (sound->getPlayLength() - 1));
        sound->setVolume(volume);
        sound->setIsPaused(false);
    }
}

void AudioEngine::PlaySoundLocation(std::string name, glm::vec2 location, bool loop, float volume, bool startRandom) {
    irrklang::ISound *sound = mAudioEngine->play3D(name.c_str(),irrklang::vec3df(location.x, location.y, 0.0), loop, true);
    if (sound) {
        // if start random, start audio at random buffer offset
        if (startRandom)
            sound->setPlayPosition(rand() % (sound->getPlayLength() - 1));
        sound->setVolume(volume);
        sound->setIsPaused(false);
    }

}

void AudioEngine::StopSound(std::string name) {
    mAudioEngine->removeSoundSource(name.c_str());
}

void AudioEngine::StopAll() {
    mAudioEngine->stopAllSounds();
}

void AudioEngine::SetPlayerPosition(glm::vec2 position) {
    mAudioEngine->setListenerPosition(irrklang::vec3df(position.x, position.y, 0.0f), irrklang::vec3df(0.0f, 0.0f, 0.0f));
}

void AudioEngine::Load() {
    mAudioEngine->addSoundSourceFromFile("Sounds/caketown.wav", irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
}
