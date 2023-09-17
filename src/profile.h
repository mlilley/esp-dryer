#ifndef __PROFILE_H__
#define __PROFILE_H__

#define PROFILE_NAME_MAX 14

typedef struct profile_t {
    char name[PROFILE_NAME_MAX + 1];
    int temp;
    int hours;
    int state;
} profile_t;

#define PROFILE_STATE_EMPTY_MASK 0b001
#define PROFILE_STATE_ERROR_MASK 0b010
#define PROFILE_STATE_USER_MASK  0b100

#define PROFILE_IS_EMPTY(profile) ((profile.state & PROFILE_STATE_EMPTY_MASK) > 0)
#define PROFILE_IS_ERROR(profile) ((profile.state & PROFILE_STATE_ERROR_MASK) > 0)
#define PROFILE_IS_USER(profile)  ((profile.state & PROFILE_STATE_USER_MASK) > 0)

#endif