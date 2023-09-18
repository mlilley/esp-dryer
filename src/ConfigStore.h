#ifndef __CONFIG_STORE_H__
#define __CONFIG_STORE_H__

#include "common.h"
#include "profile.h"
#include <Preferences.h>

#define CONFIG_PROFILES_MAX 30

static const int DEF_TEMP_UNITS = 0;
static const profile_t DEF_PROFILES[] = {
    { "PLA",           45,  60, 0 },
    { "PETG",          60,  60, 0 },
    { "ABS",           70,  60, 0 },
    { "ASA",           80,  60, 0 },
    { "TPU",           45,  40, 0 },
    { "Nylon",         80,  60, 0 },
    { "PolyCarbonate", 80, 100, 0 },
    { "User 1",        45,  60, PROFILE_STATE_USER_MASK },
    { "User 2",        45,  60, PROFILE_STATE_USER_MASK },
    { "User 3",        45,  60, PROFILE_STATE_USER_MASK },
};
static const profile_t DEF_ZERO_PROFILE = { "", TEMP_MIN, HOURS_MIN, 0 };

class ConfigStore {
    protected:
        static const char* NAMESPACE_NAME;
        static const char* INITIALIZED_KEY;

    protected:
        bool m_loaded;
        profile_t m_profiles[CONFIG_PROFILES_MAX];
        int m_nProfiles;
        int m_tempUnits;

    protected:
        void _initializeRom(Preferences* prefs, bool force);
        void _writeTempUnits(Preferences* prefs, int value);
        void _writeProfiles(Preferences* prefs, const profile_t profiles[], int nProfiles);
        void _writeProfile(Preferences* prefs, int index, const profile_t* profile);

        void _readRom(Preferences* prefs);
        void _safeReadTempUnits(Preferences* prefs);
        void _safeReadProfiles(Preferences* prefs);
        void _safeReadProfile(Preferences* prefs, int index);
        void _errorProfile(int index);

    public:
        ConfigStore();
        void load();
        void reset();

        int getTempUnits();
        int getNumProfiles();
        const profile_t* getProfile(int index);

        void setTempUnits(int value);
        void setProfile(int index, profile_t* profile);

        void persistTempUnits();
        void persistProfile(int index);

        void resetProfile(int index);

        void dump();
};

#endif