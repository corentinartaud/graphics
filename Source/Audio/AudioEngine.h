//
//  AudioEngine.h
//  COMP371_Project
//
//  Created by Corentin Artaud on 2019-08-09.
//  Copyright © 2019 Concordia. All rights reserved.
//

#ifndef AudioEngine_h
#define AudioEngine_h

// irrKlang cross platform sound library
#include <irrKlang.h>
/* NOTE FOR MAC USERS:
 If the app doesn't link/run and you receive the following error:
 > dyld: Library not loaded: /usr/local/lib/libirrklang.dylib
 > Referenced from: yourapplication
 > Reason: image not found' in the
 Do the following:
 1. Copy ../ThirdParty/irrKlang/lib/osx/libirrklang.dylib
 2. Paste into /usr/local/lib
*/


#include <glm/glm.hpp>

#include <string>

// manages all audio-related functionality
class AudioEngine {
public:
    // constructor / destructor
    AudioEngine();
    ~AudioEngine();
    
    // plays a sound with/out loop and at a volume (set to full volume if not given)
    void Play(std::string name, bool loop = false, float volume = 1.0f, bool startRandom = false);
    // stops playing a sound
    void Stop(std::string name);
    // stops playing all sounds
    void StopAll();
    // checks if sound is playing
    bool IsPlaying(std::string name);
    
    // pre-loads sound-files
    void Load();
    
private:
    // the 3rd party's audio engine API reference point
    irrklang::ISoundEngine *mAudioEngine;
};


#endif /* AudioEngine_h */
