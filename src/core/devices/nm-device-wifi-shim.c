/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Minimal shim to satisfy link-time references when the wifi plugin
 * static objects aren't pulled into the final NetworkManager binary.
 * These implementations intentionally provide safe no-op / zero
 * semantics. When the wifi plugin is linked into the final binary
 * the plugin-provided implementations will be used instead (they
 * have the same symbol names), so this shim is a build-time bridge.
 */

#include "devices/nm-device.h"
#include "devices/wifi/nm-device-wifi.h"
#include "nm-logging.h"

/* Log a single warning if any shim function is ever used at runtime. */
static gboolean shim_warned = FALSE;

/* Return number of recent connection failures for this device.
 * If device is a wifi device we would prefer to use the wifi
 * implementation, but that lives in the wifi plugin static library.
 * To avoid introducing a hard dependency here we provide a safe
 * fallback that returns 0.
 */
guint32
_nm_device_get_failures_for_device(NMDevice *device)
{
    /* If desired, we could try to call an exported wifi helper here,
     * but that would reintroduce the unresolved-symbol problem when
     * the wifi static library is not linked. Return 0 as a safe default.
     */
    (void) device;
    if (!shim_warned) {
        shim_warned = TRUE;
        nm_log_warn(LOGD_WIFI,
                    "wifi shim used: returning safe default for _nm_device_get_failures_for_device");
    }
    return 0;
}

/* Return total number of connection failures for this device (all time).
 * Fallback returns 0.
 */
guint64
_nm_device_get_all_failures_for_device(NMDevice *device)
{
    (void) device;
    if (!shim_warned) {
        shim_warned = TRUE;
        nm_log_warn(LOGD_WIFI,
                    "wifi shim used: returning safe default for _nm_device_get_all_failures_for_device");
    }
    return 0;
}

/* Clear the wifi device all-connection-failures counter. No-op fallback. */
void
nm_device_wifi_clear_all_connection_failure_count(NMDeviceWifi *device)
{
    (void) device;
    if (!shim_warned) {
        shim_warned = TRUE;
        nm_log_warn(LOGD_WIFI,
                    "wifi shim used: nm_device_wifi_clear_all_connection_failure_count is a no-op");
    }
    /* no-op */
}
