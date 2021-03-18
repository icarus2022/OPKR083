#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "common/params.h"
#include "ui.hpp"


bool control_button_clicked1(int touch_x, int touch_y) {
  if (touch_x >= 1585 && touch_x <= 1725) {
    if (touch_y >= 905 && touch_y <= 1045) {
      return true;
    }
  }
  return false;
}

bool control_button_screenshot(int touch_x, int touch_y) {
  if (touch_x >= 0 && touch_x <= 150) {
    if (touch_y >= 465 && touch_y <= 615) {
      return true;
    }
  }
  return false;
}

bool latcontrol( UIState *s, int touch_x, int touch_y ) {

  bool touched = false;

  if ((control_button_clicked1(touch_x,touch_y)) && (s->status != STATUS_OFFROAD) && (s->limit_set_speed == 0) && (s->sidebar_collapsed == true)) {
    Params().write_db_value("LimitSetSpeed", "1", 1);
    //system("su -c 'am start -n com.gmd.hidesoftkeys/com.gmd.hidesoftkeys.MainActivity'");
    system("su -c 'am start --activity-task-on-home com.skt.tmap.ku/com.skt.tmap.activity.TmapNaviActivity'");
    s->sound->play(AudibleAlert::CHIME_WARNING1);
    touched = true;
  }

  if ((control_button_screenshot(touch_x,touch_y)) && (s->status != STATUS_OFFROAD)) {
    Params().write_db_value("LimitSetSpeed", "0", 1);
    system("su -c 'am start --activity-task-on-home ai.comma.plus.offroad/.MainActivity'");
    s->sound->play(AudibleAlert::CHIME_WARNING1);
    touched = true;
  }

  return touched;
}