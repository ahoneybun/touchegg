/**
 * Copyright 2011 - 2020 José Expósito <jose.exposito89@gmail.com>
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 3 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GESTURE_GATHERER_LIBINPUT_DEVICE_HANDLER_H_
#define GESTURE_GATHERER_LIBINPUT_DEVICE_HANDLER_H_

#include <memory>

#include "gesture-controller/gesture-controller-delegate.h"
#include "gesture-gatherer/libinput-handler.h"
#include "gesture/gesture-direction.h"

/**
 * Class to handle libinput devices:
 * https://wayland.freedesktop.org/libinput/doc/latest/api/group__device.html
 */
class LininputDeviceHandler : public LininputHandler {
 public:
  LininputDeviceHandler(GestureControllerDelegate *gestureController,
                        double threshold, double animationFinishThreshold)
      : LininputHandler(gestureController),
        threshold(threshold),
        animationFinishThreshold(animationFinishThreshold) {}

  /**
   * Called on startup for each device and every time a device is added.
   * Print useful information and calculates LibinputDeviceInfo.
   */
  void handleDeviceAdded(struct libinput_event *event) const;

 private:
  double threshold = -1;
  double animationFinishThreshold = -1;

  /**
   * Calculates LibinputDeviceInfo on touchpads.
   *
   * Calculating optimal "threshold" and "animation_finish_threshold" is really
   * complicated on touchpads with DPI < 1000, that's why this values are
   * configurable. However this methods works with the bast majority of devices
   * out there.
   */
  void calculateTouchpadThreshold(double widthMm, double heightMm,
                                  LibinputDeviceInfo *outInfo) const;

  /**
   * Calculates LibinputDeviceInfo on touchscreens.
   */
  void calculateTouchscreenThreshold(double widthMm, double heightMm,
                                     LibinputDeviceInfo *outInfo) const;
};
#endif  // GESTURE_GATHERER_LIBINPUT_DEVICE_HANDLER_H_
