/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Minimal shim kept for backward compatibility. Historically this file
 * provided weak helper symbols used by the core to query Wi‑Fi failure
 * counters when the Wi‑Fi implementation was not linked in. The core
 * now calls per‑device virtual methods instead, so these helpers are
 * no longer referenced for new builds. We keep them to avoid breaking
 * any out‑of‑tree users that might still rely on the symbols.
 */

#include "src/core/nm-default-daemon.h"
#include "wifi/nm-device-wifi.h"

#include "nm-device.h"

/* Forward declarations to avoid pulling heavy public headers into this shim.
 * The shim only needs the types for function signatures. The real
 * implementations live in the wifi plugin and will be linked in when
 * the plugin objects are included in the final binary. */
typedef struct _NMDevice NMDevice;
typedef struct _NMDeviceWifi NMDeviceWifi;

/* Log a single warning if any shim function is ever used at runtime. */
static gboolean shim_warned = FALSE;

#if defined(__GNUC__)
#define NM_SHIM_WEAK __attribute__((weak))
#else
#define NM_SHIM_WEAK
#endif

/* Clear the wifi device all-connection-failures counter. No-op fallback
 * that is still referenced from core code paths when Wi‑Fi support is
 * not built. The Wi‑Fi plugin provides a real implementation.
 */
void
nm_device_wifi_clear_all_connection_failure_count(NMDeviceWifi *device) NM_SHIM_WEAK
{
    (void) device;
    if (!shim_warned) {
        shim_warned = TRUE;
        nm_log_warn(LOGD_WIFI,
                    "wifi shim used: nm_device_wifi_clear_all_connection_failure_count is a no-op");
    }
    /* no-op */
}
