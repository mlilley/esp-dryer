#ifndef __CONFIG_STORE_H__
#define __CONFIG_STORE_H__

#include "common.h"
#include "profile.h"
#include <Preferences.h>

#define CONFIG_PROFILES_MAX 30

static const profile_t PROFILES[] = {
    { "PLA",           45,  60, 0 },
    { "PETG",          60,  60, 0 },
    { "ABS",           70,  60, 0 },
    { "ASA",           80,  60, 0 },
    { "TPU",           45,  40, 0 },
    { "Nylon",         80,  60, 0 },
    { "PolyCarbonate", 80, 100, 0 },
};

class ConfigStore {
    protected:
        static const char* NAMESPACE_NAME;
        static const char* INITIALIZED_KEY;

    protected:
        profile_t m_profiles[CONFIG_PROFILES_MAX];
        int m_numProfiles;

    protected:
        void _initializeStore(Preferences* prefs);
        void _readProfile(Preferences* prefs, int index);
        void _writeProfile(Preferences* prefs, int index);
        void _clearProfile(int index, int state);
        void _errorProfile(int index);
        bool _isProfileValid(int index);

    public:
        ConfigStore();
        void load();
        void writeProfile(int index);
        int getNumProfiles();
        profile_t* getProfile(int index);
};

#endif