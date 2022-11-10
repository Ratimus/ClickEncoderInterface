// ------------------------------------------------------------------------
// ClickEncoderInterface.h
//
// Nov. 2022
// Ryan "Ratimus" Richardson
// ------------------------------------------------------------------------
#ifndef ClickEncoderInterface_h
#define ClickEncoderInterface_h

#include "Arduino.h"
#include <ClickEncoder.h>
#include <MagicButton.h>

extern ClickEncoder clickEncoder;

enum encEvnts
{
  Click,
  DblClick,
  Left,
  ShiftLeft,
  Right,
  ShiftRight,
  Press,
  ClickHold,
  Hold,
  NUM_ENC_EVNTS
};

// // Not yet implemented
// struct encoderMsg
// {
//   encEvnts evnt;
//   int8_t param;
//   inline encoderMsg(encEvnts evnt):
//     evnt(evnt),
//     param(-1)
//   {;}
  
//   inline encoderMsg(encEvnts evnt,int8_t p):
//     evnt(evnt),
//     param(p)
//   {;}

//   inline bool operator==(encEvnts n) const
//   {
//     return evnt==n;
//   }

//   inline operator encEvnts() const
//   {
//     return evnt;
//   }
// };


class ClickEncoderInterface
{
private:

  ClickEncoder &enc;      //associated hardware clickEncoder
  ButtonState  btnState;
  int8_t       sensivity;

  int oldPos;
  int pos;

  inline void update()
  {
    pos     += enc.getClicks();
    btnState = enc.getButton();
  }

public:

  // Constructor
  ClickEncoderInterface(ClickEncoder &rEnc, int sense);

  encEvnts getEvent(void);
  
  inline void setSensivity(int s) { sensivity = s; }

  void flush()
  {
    btnState = ButtonState::Open;
    enc.getClicks();
    enc.getButton();
    oldPos = pos;
  }
};

extern ClickEncoderInterface clickEnc;

#endif