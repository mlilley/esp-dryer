#include "ConfigStore.h"

const char* ConfigStore::NAMESPACE_NAME = "esp-dryer";
const char* ConfigStore::INITIALIZED_KEY = "INITIALIZED";

static char keybuf[50];

// NB: max key length is 15 chars
#define KEY_INITIALIZED   "INITIALIZED"
#define KEY_NUM_PROFILES  "NUM_PROFILES"
#define KEY_PROFILE_NAME  "P_%02d_NAME"
#define KEY_PROFILE_TEMP  "P_%02d_TEMP"
#define KEY_PROFILE_HOURS "P_%02d_HOURS"
#define KEY_PROFILE_STATE "P_%02d_STATE"

ConfigStore::ConfigStore() {
    m_numProfiles = 0;
}

void ConfigStore::load() {
    Preferences prefs;
    prefs.begin(NAMESPACE_NAME, false);

    if (!prefs.getBool(KEY_INITIALIZED, false)) {
        _initializeStore(&prefs);
    } else {
        m_numProfiles = prefs.getInt(KEY_NUM_PROFILES, 0);
        if (m_numProfiles > CONFIG_PROFILES_MAX) {
            m_numProfiles = CONFIG_PROFILES_MAX;
        }

        for (int i = 0; i < m_numProfiles; i++) {
            _readProfile(&prefs, i);
        }

        for (int i = m_numProfiles; i < CONFIG_PROFILES_MAX; i++) {
            _clearProfile(i, PROFILE_STATE_EMPTY_MASK | PROFILE_STATE_USER_MASK);
        }

        for (int i = 0; i < m_numProfiles; i++) {
            if (!_isProfileValid(i)) {
                _errorProfile(i);
            }
        }
    }

    prefs.end();
}

void ConfigStore::writeProfile(int index) {
    if (index < 0 || index >= CONFIG_PROFILES_MAX) {
        return;
    }

    Preferences prefs;
    prefs.begin(NAMESPACE_NAME, false);

    _writeProfile(&prefs, index);

    prefs.end();
}

int ConfigStore::getNumProfiles() {
    return m_numProfiles;
}

profile_t* ConfigStore::getProfile(int index) {
    if (index < 0 || index >= CONFIG_PROFILES_MAX) {
        return NULL;
    }
    return &m_profiles[index];
}

void ConfigStore::_initializeStore(Preferences* prefs) {
    prefs->clear();

    m_numProfiles = sizeof(PROFILES) / sizeof(profile_t);

    for (int i = 0; i < m_numProfiles; i++) {
        strcpy(m_profiles[i].name, PROFILES[i].name);
        m_profiles[i].temp = PROFILES[i].temp;
        m_profiles[i].hours = PROFILES[i].hours;
        m_profiles[i].state = PROFILES[i].state;
    }

    for (int i = m_numProfiles; i < CONFIG_PROFILES_MAX; i++) {
        _clearProfile(i, PROFILE_STATE_EMPTY_MASK | PROFILE_STATE_USER_MASK);
    }
    
    for (int i = 0; i < CONFIG_PROFILES_MAX; i++) {
        _writeProfile(prefs, i);
    }
    
    prefs->putBool(KEY_INITIALIZED, true);
    prefs->putInt(KEY_NUM_PROFILES, m_numProfiles);
}

void ConfigStore::_readProfile(Preferences* prefs, int index) {
    sprintf(keybuf, KEY_PROFILE_NAME, index);
    prefs->getString(keybuf, m_profiles[index].name, PROFILE_NAME_MAX + 1);

    sprintf(keybuf, KEY_PROFILE_TEMP, index);
    m_profiles[index].temp = prefs->getInt(keybuf, -1);

    sprintf(keybuf, KEY_PROFILE_HOURS, index);
    m_profiles[index].hours = prefs->getInt(keybuf, -1);

    sprintf(keybuf, KEY_PROFILE_STATE, index);
    m_profiles[index].state = prefs->getBool(keybuf, false);
}

void ConfigStore::_writeProfile(Preferences* prefs, int index) {
    sprintf(keybuf, KEY_PROFILE_NAME, index);
    prefs->putString(keybuf, m_profiles[index].name);

    sprintf(keybuf, KEY_PROFILE_TEMP, index);
    prefs->putInt(keybuf, m_profiles[index].temp);

    sprintf(keybuf, KEY_PROFILE_HOURS, index);
    prefs->putInt(keybuf, m_profiles[index].hours);

    sprintf(keybuf, KEY_PROFILE_STATE, index);
    prefs->putInt(keybuf, m_profiles[index].state);
}

void ConfigStore::_clearProfile(int index, int state) {
    strcpy(m_profiles[index].name, "");
    m_profiles[index].temp = TEMP_MIN;
    m_profiles[index].hours = HOURS_MIN;
    m_profiles[index].state = state;
}

void ConfigStore::_errorProfile(int index) {
    strcpy(m_profiles[index].name, "ERROR");
    m_profiles[index].temp = TEMP_MIN;
    m_profiles[index].hours = HOURS_MIN;
    m_profiles[index].state = m_profiles[index].state | PROFILE_STATE_ERROR_MASK;
}

bool ConfigStore::_isProfileValid(int index) {
    if (PROFILE_IS_ERROR(m_profiles[index]) || PROFILE_IS_EMPTY(m_profiles[index])) {
        return true; // dont care about the reset of the profile
    }
    int n = strnlen(m_profiles[index].name, PROFILE_NAME_MAX + 1);
    if (n == 0 || n == PROFILE_NAME_MAX + 1) {
        return false;
    }
    if (m_profiles[index].temp < TEMP_MIN || m_profiles[index].temp > TEMP_MAX) {
        return false;
    }
    if (m_profiles[index].hours < HOURS_MIN || m_profiles[index].hours > HOURS_MAX) {
        return false;
    }
    return true;
}
