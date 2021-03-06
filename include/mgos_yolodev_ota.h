#ifndef MGOS_YOLODEV_OTA
#define MGOS_YOLODEV_OTA

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include "common/mg_str.h"
#include "frozen.h"
#include "mgos_event.h"
#include "mgos_updater_common.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define YOLODEV_OTA_BASE MGOS_EVENT_BASE('Y', 'D', 'O')

/* In the comment, the type of `void *ev_data` is specified */
enum yolodev_ota_event {
  YOLODEV_OTA_REQUEST = YOLODEV_OTA_BASE, /* struct yolodev_ota_request */
};

/* ev_data for YOLODEV_OTA_REQUEST event. */
struct yolodev_ota_request {
  const char *uri;
  uint32_t crc32;
  bool handled;
  struct update_context *updater_context;
};

// API
bool yolodev_request_ota(const char *uri, uint32_t crc32);

// Init
bool mgos_yolodev_ota_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MGOS_YOLODEV_OTA */
