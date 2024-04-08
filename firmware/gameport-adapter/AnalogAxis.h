// This file is part of Necroware's GamePort adapter firmware.
// Copyright (C) 2021 Necroware
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <Arduino.h>

/// Class to read analog axis.
///
/// Usually PC joystick axes are specified to have 100 Ohm resistance, but
/// many analog joysticks have old, bad, or just wrong resistors. This ends
/// up in incorrect positions and is especially bad for games, which don't
/// have calibration features. This class takes care of this issue and
/// applies automatic calibration on every read.
template <int ID>
class AnalogAxis {
public:
  /// Constructor.
  ///
  /// The initial state of the joystick is considered as middle
  /// which is used for autocalibration.
  AnalogAxis() {
    pinMode(ID, INPUT);
    m_mid = analogRead(ID);
    last_value = m_mid;
    m_min = m_mid - 100;
    m_max = m_mid + 100;
  }

  /// Gets the axis state.
  ///
  /// This function automatically recalculates the outer limits and
  /// readjusts the position of the joystick.
  /// @returns a value between 0 and 1023
  uint16_t get() {
    auto value = analogRead(ID);
    // for (int i=0; i<3; i++){
    //   delayMicroseconds(100);
    //   value = (value + analogRead(ID) )/2;
    // }
    
    if (value < m_min) {
      m_min = value;
    } else if (value > m_max) {
      m_max = value;
    }

    // if (ID == A1){
      


    // }
   
    // if (abs(last_value-value)>15){
    //   // if (abs(last_value-value)>70){

    //   //   last_value = last_value * 0.7 + value * 0.3;

      

    //     last_value = last_value * 0.7 + value * 0.3;

      // }
      
      // if (abs(last_value-value)>1){
        // last_value = last_value - sgn(last_value-value);
      // }

    // }
    // if(ID==A0){
    //   Serial.println(value);
    //   delay(50);
    // }

    if (ID != A2){
    if (value < m_mid) {
    //   return map(value, m_min, m_mid, 0, 511);
    // }else{
    // return map(value, m_mid, m_max, 512, 1023);
    // }
          return map(value, m_min, m_mid, 1023, 512);
    }else{
    return map(value, m_mid, m_max, 511, 0);
    }
    }else{

    if (value < m_mid) {
      return map(value, m_min, m_mid, 1023, 512);
    }else{
    return map(value, m_mid, m_max, 511, 0);
    }
    }

  }

  // static inline int8_t sgn(int val) {
  // if (val < 0) return -1;
  // if (val==0) return 0;
  // return 1;
// }

private:
  int m_mid;
  int m_min;
  int m_max;
  int last_value;
};
