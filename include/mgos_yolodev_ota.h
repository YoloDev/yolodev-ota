#ifndef MGOS_YOLODEV_OTA
#define MGOS_YOLODEV_OTA

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include "common/mg_str.h"
#include "frozen.h"
#include "mgos_event.h"

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
  char *location;
  uint32_t crc32;
  void *updater_context;
};

// Init
bool mgos_yolodev_ota_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MGOS_YOLODEV_OTA */
