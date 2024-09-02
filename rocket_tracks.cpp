// sync data implementation
#ifdef SYNC_PLAYER
#include "../rocket/track.h"
static track_key clear_r_keys[] = {{ 0, 0.000000, KEY_LINEAR}, { 16, 1.000000, KEY_STEP}, };
const sync_track clear_r = { "clear_r", clear_r_keys,2};
#endif
 // SYNC_PLAYER