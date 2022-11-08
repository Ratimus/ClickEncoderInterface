// Oct. 2022
// Ryan Richardson
// Work in progress
// based on "ClickEncoderIn.h" by Rui Azevedo


#ifndef ClickEncoderInterface_h
#define ClickEncoderInterface_h

#include "Arduino.h"
#include <ClickEncoder.h>

extern ClickEncoder clickEncoder;

enum encCmds
{
  noCmd=0,
  escCmd,
  enterCmd,
  upCmd,
  downCmd,
  leftCmd,
  rightCmd
  // idxCmd,
  // selCmd,
  // scrlUpCmd,
  // scrlDownCmd
};

// Not yet implemented
struct encoderMsg
{
  encCmds cmd;
  int8_t param;
  inline encoderMsg(encCmds cmd):
    cmd(cmd),
    param(-1)
  {;}
  
  inline encoderMsg(encCmds cmd,int8_t p):
    cmd(cmd),
    param(p)
  {;}

  inline bool operator==(encCmds n) const
  {
    return cmd==n;
  }

  inline operator encCmds() const
  {
    return cmd;
  }
};


class ClickEncoderInterface
{
public:
  ClickEncoder &enc; //associated hardware clickEncoder
  ClickEncoder::Button btn;
  int8_t sensivity;
  int oldPos;
  int pos;

  // Constructor
  ClickEncoderInterface(ClickEncoder &rEnc, int sense);
  
  inline void setSensivity(int s)
  {
    sensivity = s;
  }

  inline void update()
  {
    pos += enc.getValue();

    if (btn == ClickEncoder::Open)//do not override previous input
    {
      btn = enc.getButton();
    }
  }


  int peek(void);
  
  int available(void)
  {
    return peek() != static_cast<int>(noCmd);
  }

  int read()
  {
    int ch = peek();
    btn = ClickEncoder::Open;
    if (ch == static_cast<int>(upCmd))
    {
      oldPos += sensivity;
    }
    else if (ch == static_cast<int>(downCmd))
    {
      oldPos -= sensivity;
    }

    return ch;
  }

  void flush()
  {
    btn = ClickEncoder::Open;//2017 clear current key
    update();
    oldPos = pos;
  }

  size_t write(uint8_t v)
  {
    oldPos = v;
    return 1;
  }
};

extern ClickEncoderInterface rotor;

#endif
