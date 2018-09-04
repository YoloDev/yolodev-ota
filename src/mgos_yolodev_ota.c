#include "mgos_yolodev_ota.h"
#include "common/cs_dbg.h"
#include "mgos_event.h"
#include "mgos_updater_common.h"
#include <stdio.h>
#include <string.h>

static void result_cb(struct update_context *ctx) {
  if (ctx->ota_state == MGOS_OTA_STATE_SUCCESS && is_reboot_required(ctx)) {
    mgos_system_restart();
  } else if (ctx->ota_state == MGOS_OTA_STATE_ERROR ||
             ctx->ota_state == MGOS_OTA_STATE_SUCCESS) {
    updater_context_free(ctx);
  }
}

bool yolodev_request_ota(const char *uri_orig, uint32_t crc32) {
  struct update_context *context = updater_context_get_current();
  if (context != NULL) {
    LOG(LL_INFO, ("We are already in the middle of an OTA update, update is "
                  "ignored, and will be updated next time."));
    return false;
  }

  context = updater_context_create(10 * 60 * 1000 /* 10 min */);
  context->result_cb = result_cb;

  size_t uri_size =
      sizeof(char) * (strlen(uri_orig) + 1); // including 0 byte at end
  char *uri = malloc(uri_size);
  memcpy(uri, uri_orig, uri_size);

  struct yolodev_ota_request *ev_data =
      malloc(sizeof(struct yolodev_ota_request));
  ev_data->crc32 = crc32;
  ev_data->uri = uri;
  ev_data->handled = false;
  ev_data->updater_context = context;
  mgos_event_trigger(YOLODEV_OTA_REQUEST, ev_data);
  bool handled = ev_data->handled;
  if (!handled) {
    LOG(LL_INFO, ("OTA request for \"%s\" was not handled, are you missing a "
                  "handler library?",
                  uri));
  }
  free(uri);
  free(ev_data);

  return handled;
}

bool mgos_yolodev_ota_init(void) { return true; }
