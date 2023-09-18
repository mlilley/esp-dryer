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
#define KEY_TEMPUNITS     "TEMP_UNITS"

ConfigStore::ConfigStore() {
    m_loaded = false;
}

void ConfigStore::load() {
    Preferences prefs;
    prefs.begin(NAMESPACE_NAME, false);
    _initializeRom(&prefs, false);
    _readRom(&prefs);
    prefs.end();
    m_loaded = true;
}

void ConfigStore::reset() {
    Preferences prefs;
    prefs.begin(NAMESPACE_NAME, false);
    _initializeRom(&prefs, true);
    _readRom(&prefs);
    prefs.end();
    m_loaded = true;
}

int ConfigStore::getTempUnits() {
    if (!m_loaded) {
        load();
    }
    return m_tempUnits;
}

int ConfigStore::getNumProfiles() {
    if (!m_loaded) {
        load();
    }
    return m_nProfiles;
}

const profile_t* ConfigStore::getProfile(int index) {
    if (!m_loaded) {
        load();
    }
    if (index < 0 || index >= m_nProfiles) {
        return &DEF_ZERO_PROFILE;
    }
    // DONT CHANGE RESULT
    return &m_profiles[index];
}

void ConfigStore::setTempUnits(int value) {
    if (!m_loaded) {
        load();
    }
    if (value == 0 || value == 1) {
        m_tempUnits = value;
    }
}

void ConfigStore::setProfile(int index, profile_t* profile) {
    if (!m_loaded) {
        load();
    }
    if (index >= 0 && index < m_nProfiles) {
        strcpy(m_profiles[index].name, profile->name);
        m_profiles[index].temp = profile->temp;
        m_profiles[index].hours = profile->hours;
        m_profiles[index].state = profile->state;
    }
}

void ConfigStore::persistTempUnits() {
    if (!m_loaded) { // necessary if setTempUnits was not called
        load();
    } 
    Preferences prefs;
    prefs.begin(NAMESPACE_NAME, false);
    _writeTempUnits(&prefs, m_tempUnits);
    prefs.end();
}

void ConfigStore::persistProfile(int index) {
    if (!m_loaded) { // necessary if setProfile was not called
        load();
    }
    if (index < 0 || index >= CONFIG_PROFILES_MAX) {
        return;
    }
    Preferences prefs;
    prefs.begin(NAMESPACE_NAME, false);
    _writeProfile(&prefs, index, &m_profiles[index]);
    prefs.end();
}

void ConfigStore::resetProfile(int index) {
    if (!m_loaded) { 
        load();
    }
    if (index < 0 || index >= m_nProfiles) {
        return;
    }
    if (index < 0 || index >= sizeof(DEF_PROFILES) / sizeof(profile_t)) {
        return;
    }
    Preferences prefs;
    prefs.begin(NAMESPACE_NAME, false);
    _writeProfile(&prefs, index, &DEF_PROFILES[index]);
    _safeReadProfile(&prefs, index);
    prefs.end();
}

void ConfigStore::dump() {
    Serial.print("CONFIG:\n");
    Serial.printf("  TempUnits: %d\n", m_tempUnits);
    Serial.printf("  NumProfiles: %d\n", m_nProfiles);
    for (int i = 0; i < m_nProfiles; i++) {
        Serial.printf("  Profile %d:\n", i);
        Serial.printf("    Name: %s\n", m_profiles[i].name);
        Serial.printf("    Temp: %d\n", m_profiles[i].temp);
        Serial.printf("    Hours: %d\n", m_profiles[i].hours);
        Serial.printf("    State: %d\n", m_profiles[i].state);
    }
}

// ---

void ConfigStore::_initializeRom(Preferences* prefs, bool force) {
    if (!prefs->getBool(KEY_INITIALIZED) || force) {
        prefs->putBool(KEY_INITIALIZED, true);
        _writeTempUnits(prefs, DEF_TEMP_UNITS);
        _writeProfiles(prefs, DEF_PROFILES, sizeof(DEF_PROFILES) / sizeof(profile_t));
    }
}

void ConfigStore::_writeTempUnits(Preferences* prefs, int value) {
    prefs->putInt(KEY_TEMPUNITS, value);
}

void ConfigStore::_writeProfiles(Preferences* prefs, const profile_t profiles[], int nProfiles) {
    prefs->putInt(KEY_NUM_PROFILES, nProfiles);
    for (int i = 0; i < nProfiles; i++) {
        _writeProfile(prefs, i, &profiles[i]);
    }
    for (int i = nProfiles; i < CONFIG_PROFILES_MAX; i++) {
        _writeProfile(prefs, i, &DEF_ZERO_PROFILE);
    }
}

void ConfigStore::_writeProfile(Preferences* prefs, int index, const profile_t* profile) {
    sprintf(keybuf, KEY_PROFILE_NAME, index);
    prefs->putString(keybuf, profile->name);
    sprintf(keybuf, KEY_PROFILE_TEMP, index);
    prefs->putInt(keybuf, profile->temp);
    sprintf(keybuf, KEY_PROFILE_HOURS, index);
    prefs->putInt(keybuf, profile->hours);
    sprintf(keybuf, KEY_PROFILE_STATE, index);
    prefs->putInt(keybuf, profile->state);
}

void ConfigStore::_readRom(Preferences* prefs) {
    _safeReadTempUnits(prefs);
    _safeReadProfiles(prefs);
}

void ConfigStore::_safeReadTempUnits(Preferences* prefs) {
    m_tempUnits = prefs->getInt(KEY_TEMPUNITS, 0);
    if (m_tempUnits != 0 && m_tempUnits != 1) {
        m_tempUnits = 0;
    }
}

void ConfigStore::_safeReadProfiles(Preferences* prefs) {
    m_nProfiles = prefs->getInt(KEY_NUM_PROFILES, 0);
    if (m_nProfiles > CONFIG_PROFILES_MAX) {
        m_nProfiles = CONFIG_PROFILES_MAX;
    }
    for (int i = 0; i < CONFIG_PROFILES_MAX; i++) {
        _safeReadProfile(prefs, i);
    }
}

void ConfigStore::_safeReadProfile(Preferences* prefs, int index) {
    sprintf(keybuf, KEY_PROFILE_NAME, index);
    prefs->getString(keybuf, m_profiles[index].name, PROFILE_NAME_MAX + 1);
    sprintf(keybuf, KEY_PROFILE_TEMP, index);
    m_profiles[index].temp = prefs->getInt(keybuf, -1);
    sprintf(keybuf, KEY_PROFILE_HOURS, index);
    m_profiles[index].hours = prefs->getInt(keybuf, -1);
    sprintf(keybuf, KEY_PROFILE_STATE, index);
    m_profiles[index].state = prefs->getBool(keybuf, false);

    int n = strnlen(m_profiles[index].name, PROFILE_NAME_MAX + 1);
    if (n == PROFILE_NAME_MAX + 1) {
        _errorProfile(index);
        return;
    }
    if (m_profiles[index].temp < TEMP_MIN || m_profiles[index].temp > TEMP_MAX) {
        _errorProfile(index);
        return;
    }
    if (m_profiles[index].hours < HOURS_MIN || m_profiles[index].hours > HOURS_MAX) {
        _errorProfile(index);
        return;
    }
}

void ConfigStore::_errorProfile(int index) {
    strcpy(m_profiles[index].name, "ERROR");
    m_profiles[index].temp = TEMP_MIN;
    m_profiles[index].hours = HOURS_MIN;
    m_profiles[index].state = m_profiles[index].state | PROFILE_STATE_ERROR_MASK;
}
