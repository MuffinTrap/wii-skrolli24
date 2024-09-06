// sync data implementation
#ifdef SYNC_PLAYER
#include "rocket/track.h"
static track_key effect_active_keys[] = {{ 0, 0.000000, KEY_STEP}, { 8, 1.000000, KEY_STEP}, { 24, 2.000000, KEY_STEP}, };
const sync_track effect_active = { "effect_active", effect_active_keys,3};
static track_key item_visible_keys[] = {{ 0, -1.000000, KEY_STEP}, { 24, 1.000000, KEY_STEP}, };
const sync_track item_visible = { "item_visible", item_visible_keys,2};
static track_key camera_X_keys[] = {{ 0, 0.000000, KEY_STEP}, };
const sync_track camera_X = { "camera:X", camera_X_keys,1};
static track_key camera_Y_keys[] = {{ 0, 0.000000, KEY_STEP}, { 8, 0.000000, KEY_STEP}, };
const sync_track camera_Y = { "camera:Y", camera_Y_keys,2};
static track_key camera_Z_keys[] = {{ 0, 0.800000, KEY_STEP}, { 8, 0.000000, KEY_STEP}, };
const sync_track camera_Z = { "camera:Z", camera_Z_keys,2};
static track_key camera_rotX_keys[] = {{ 8, 0.000000, KEY_STEP}, };
const sync_track camera_rotX = { "camera:rotX", camera_rotX_keys,1};
static track_key camera_rotY_keys[] = {{ 8, 0.000000, KEY_STEP}, { 16, 0.000000, KEY_STEP}, };
const sync_track camera_rotY = { "camera:rotY", camera_rotY_keys,2};
static track_key camera_rotZ_keys[] = {{ 8, 0.000000, KEY_STEP}, };
const sync_track camera_rotZ = { "camera:rotZ", camera_rotZ_keys,1};
static track_key item_X_keys[] = {{ 0, 0.000000, KEY_STEP}, };
const sync_track item_X = { "item:X", item_X_keys,1};
static track_key item_Y_keys[] = {{ 0, -2.000000, KEY_STEP}, };
const sync_track item_Y = { "item:Y", item_Y_keys,1};
static track_key item_Z_keys[] = {{ 0, -8.000000, KEY_STEP}, };
const sync_track item_Z = { "item:Z", item_Z_keys,1};
static track_key item_rotX_keys[] = {{ 0, 0.000000, KEY_STEP}, };
const sync_track item_rotX = { "item:rotX", item_rotX_keys,1};
static track_key item_rotY_keys[] = {{ 0, 0.000000, KEY_STEP}, { 24, 0.000000, KEY_LINEAR}, { 40, 360.000000, KEY_STEP}, };
const sync_track item_rotY = { "item:rotY", item_rotY_keys,3};
static track_key item_rotZ_keys[] = {{ 0, 0.000000, KEY_STEP}, { 8, 0.000000, KEY_STEP}, };
const sync_track item_rotZ = { "item:rotZ", item_rotZ_keys,2};
static track_key item_scale_keys[] = {{ 0, 1.000000, KEY_STEP}, { 3, 0.010000, KEY_LINEAR}, { 15, 0.800000, KEY_STEP}, { 24, 0.000000, KEY_LINEAR}, { 40, 1.000000, KEY_STEP}, };
const sync_track item_scale = { "item:scale", item_scale_keys,5};
static track_key house_X_keys[] = {{ 0, 0.000000, KEY_LINEAR}, { 16, -10.000000, KEY_LINEAR}, { 21, -30.000000, KEY_STEP}, };
const sync_track house_X = { "house:X", house_X_keys,3};
static track_key house_Y_keys[] = {{ 0, 20.000000, KEY_STEP}, };
const sync_track house_Y = { "house:Y", house_Y_keys,1};
static track_key house_Z_keys[] = {{ 0, -50.000000, KEY_LINEAR}, { 8, -50.000000, KEY_LINEAR}, { 16, -40.000000, KEY_LINEAR}, { 21, -20.000000, KEY_STEP}, };
const sync_track house_Z = { "house:Z", house_Z_keys,4};
static track_key house_scale_keys[] = {{ 0, 120.000000, KEY_STEP}, { 10, 120.000000, KEY_STEP}, };
const sync_track house_scale = { "house:scale", house_scale_keys,2};
static track_key room_X_keys[] = {{ 0, 0.000000, KEY_STEP}, { 24, 10.000000, KEY_LINEAR}, { 40, -10.000000, KEY_STEP}, };
const sync_track room_X = { "room:X", room_X_keys,3};
static track_key room_Y_keys[] = {{ 0, -30.000000, KEY_STEP}, };
const sync_track room_Y = { "room:Y", room_Y_keys,1};
static track_key room_Z_keys[] = {{ 0, -30.000000, KEY_STEP}, };
const sync_track room_Z = { "room:Z", room_Z_keys,1};
static track_key room_scale_keys[] = {{ 0, 120.000000, KEY_LINEAR}, };
const sync_track room_scale = { "room:scale", room_scale_keys,1};
static track_key fade_A_keys[] = {};
const sync_track fade_A = { "fade_A", fade_A_keys,0};
#endif
 // SYNC_PLAYER