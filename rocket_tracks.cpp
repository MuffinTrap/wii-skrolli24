// sync data implementation
#ifdef SYNC_PLAYER
#include "../rocket/track.h"
static track_key effect_active_keys[] = {{ 0, 0.000000, KEY_STEP}, { 8, 2.000000, KEY_STEP}, };
const sync_track effect_active = { "effect_active", effect_active_keys,2};
static track_key item_visible_keys[] = {};
const sync_track item_visible = { "item_visible", item_visible_keys,0};
static track_key camera_rotX_keys[] = {};
const sync_track camera_rotX = { "camera:rotX", camera_rotX_keys,0};
static track_key camera_rotY_keys[] = {};
const sync_track camera_rotY = { "camera:rotY", camera_rotY_keys,0};
static track_key camera_rotZ_keys[] = {};
const sync_track camera_rotZ = { "camera:rotZ", camera_rotZ_keys,0};
static track_key camera_X_keys[] = {{ 0, 0.000000, KEY_STEP}, };
const sync_track camera_X = { "camera:X", camera_X_keys,1};
static track_key camera_Y_keys[] = {{ 0, 0.000000, KEY_STEP}, { 8, 0.000000, KEY_STEP}, };
const sync_track camera_Y = { "camera:Y", camera_Y_keys,2};
static track_key camera_Z_keys[] = {{ 0, 0.800000, KEY_STEP}, { 8, 0.000000, KEY_STEP}, };
const sync_track camera_Z = { "camera:Z", camera_Z_keys,2};
static track_key fade_A_keys[] = {};
const sync_track fade_A = { "fade_A", fade_A_keys,0};
#endif
 // SYNC_PLAYER