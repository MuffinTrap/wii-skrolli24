// sync data implementation
#ifdef SYNC_PLAYER
#include "rocket/track.h"
static track_key effect_active_keys[] = {{ 0, 0.000000, KEY_STEP}, { 8, 1.000000, KEY_STEP}, { 24, 1.000000, KEY_STEP}, };
const sync_track effect_active = { "effect_active", effect_active_keys,3};
static track_key item_visible_keys[] = {{ 0, -1.000000, KEY_STEP}, { 24, 1.000000, KEY_STEP}, { 40, 2.000000, KEY_STEP}, { 56, 3.000000, KEY_STEP}, { 72, 4.000000, KEY_STEP}, };
const sync_track item_visible = { "item_visible", item_visible_keys,5};
static track_key image_visible_keys[] = {{ 0, 0.000000, KEY_STEP}, { 24, 1.000000, KEY_STEP}, };
const sync_track image_visible = { "image_visible", image_visible_keys,2};
static track_key camera_X_keys[] = {{ 0, 0.000000, KEY_STEP}, };
const sync_track camera_X = { "camera:X", camera_X_keys,1};
static track_key camera_Y_keys[] = {{ 0, 0.000000, KEY_STEP}, { 8, 0.000000, KEY_STEP}, };
const sync_track camera_Y = { "camera:Y", camera_Y_keys,2};
static track_key camera_Z_keys[] = {{ 0, 0.800000, KEY_STEP}, { 8, 0.000000, KEY_STEP}, };
const sync_track camera_Z = { "camera:Z", camera_Z_keys,2};
static track_key camera_rotX_keys[] = {{ 0, 0.000000, KEY_STEP}, { 8, 0.000000, KEY_STEP}, };
const sync_track camera_rotX = { "camera:rotX", camera_rotX_keys,2};
static track_key camera_rotY_keys[] = {{ 0, 0.000000, KEY_STEP}, { 8, 0.000000, KEY_STEP}, { 16, 0.000000, KEY_STEP}, };
const sync_track camera_rotY = { "camera:rotY", camera_rotY_keys,3};
static track_key camera_rotZ_keys[] = {{ 0, 0.000000, KEY_STEP}, { 8, 0.000000, KEY_STEP}, };
const sync_track camera_rotZ = { "camera:rotZ", camera_rotZ_keys,2};
static track_key item_X_keys[] = {{ 0, 0.000000, KEY_STEP}, { 24, 0.000000, KEY_STEP}, };
const sync_track item_X = { "item:X", item_X_keys,2};
static track_key item_Y_keys[] = {{ 0, -2.000000, KEY_STEP}, { 24, 0.000000, KEY_STEP}, { 40, -10.000000, KEY_STEP}, { 56, 1.000000, KEY_STEP}, { 72, -1.000000, KEY_STEP}, };
const sync_track item_Y = { "item:Y", item_Y_keys,5};
static track_key item_Z_keys[] = {{ 0, -8.000000, KEY_STEP}, { 24, -30.000000, KEY_STEP}, };
const sync_track item_Z = { "item:Z", item_Z_keys,2};
static track_key item_rotX_keys[] = {{ 0, 0.000000, KEY_STEP}, { 24, 90.000000, KEY_LINEAR}, { 40, 0.000000, KEY_STEP}, { 72, 0.000000, KEY_STEP}, };
const sync_track item_rotX = { "item:rotX", item_rotX_keys,4};
static track_key item_rotY_keys[] = {{ 0, 0.000000, KEY_STEP}, { 24, 0.000000, KEY_LINEAR}, { 39, 180.000000, KEY_STEP}, { 40, 0.000000, KEY_LINEAR}, { 55, 180.000000, KEY_STEP}, { 56, 0.000000, KEY_LINEAR}, { 71, 180.000000, KEY_STEP}, { 72, 0.000000, KEY_LINEAR}, { 88, 180.000000, KEY_STEP}, };
const sync_track item_rotY = { "item:rotY", item_rotY_keys,9};
static track_key item_rotZ_keys[] = {{ 0, 0.000000, KEY_STEP}, { 8, 0.000000, KEY_STEP}, { 24, 0.000000, KEY_STEP}, { 72, 0.000000, KEY_STEP}, };
const sync_track item_rotZ = { "item:rotZ", item_rotZ_keys,4};
static track_key item_scale_keys[] = {{ 0, 1.000000, KEY_STEP}, { 3, 0.010000, KEY_LINEAR}, { 15, 0.800000, KEY_STEP}, { 24, 0.200000, KEY_STEP}, { 40, 0.700000, KEY_STEP}, { 56, 0.200000, KEY_STEP}, { 72, 0.250000, KEY_STEP}, };
const sync_track item_scale = { "item:scale", item_scale_keys,7};
static track_key image_X_keys[] = {{ 0, 0.000000, KEY_STEP}, };
const sync_track image_X = { "image:X", image_X_keys,1};
static track_key image_Y_keys[] = {{ 0, 20.000000, KEY_STEP}, { 24, -40.000000, KEY_STEP}, };
const sync_track image_Y = { "image:Y", image_Y_keys,2};
static track_key image_Z_keys[] = {{ 0, -50.000000, KEY_STEP}, };
const sync_track image_Z = { "image:Z", image_Z_keys,1};
static track_key image_scale_keys[] = {{ 0, 120.000000, KEY_STEP}, { 24, 160.000000, KEY_STEP}, };
const sync_track image_scale = { "image:scale", image_scale_keys,2};
static track_key fade_A_keys[] = {};
const sync_track fade_A = { "fade_A", fade_A_keys,0};
#endif
 // SYNC_PLAYER