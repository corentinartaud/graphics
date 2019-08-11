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

// Manages all audio-related functionality and abstracts from OS-specific commands.
class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();
    
    // plays a sound with or without loop and a given volume
    void PlaySound(std::string name, bool loop = false, float volume = 1.0f, bool startRandom = false);
     // plays a sound with or without loop and a give volume at a given location; volume will be reduced at range
    void PlaySoundLocation(std::string name, glm::vec2 location, bool loop = false, float volume = 1.0f, bool startRandom = false);
    // stops playing a sound
    void StopSound(std::string name);
    // stops playing all sounds
    void StopAll();
    
    // defines the position of the player for 2D/3D positional audio
    void SetPlayerPosition(glm::vec2 position);
    
    // pre-loads sound-files
    void Load();
    
private:
    // the 3rd party's audio engine API reference point
    irrklang::ISoundEngine *mAudioEngine;
};


#endif /* AudioEngine_h */
