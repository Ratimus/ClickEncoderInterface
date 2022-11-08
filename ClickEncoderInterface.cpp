#include "ClickEncoderInterface.h"

constexpr auto ENC_A  = 2;
constexpr auto ENC_B  = 3;
constexpr auto ENC_SW = 12;

ClickEncoder clickEncoder(ENC_A, ENC_B, ENC_SW);
ClickEncoderInterface rotor(clickEncoder, 2);


// Constructor
ClickEncoderInterface :: ClickEncoderInterface(ClickEncoder &rEnc, int sense):
  enc(rEnc),
  sensivity(sense),
  oldPos(0),
  pos(0),
  btn(ClickEncoder::Open)
  {
    pos = enc.getValue();
  }


int ClickEncoderInterface :: peek(void)
{
  update();
  if (btn == ClickEncoder::Clicked)
  {
    btn = ClickEncoder::Open;
    return static_cast<int>(enterCmd);
  }

  //////////////// DOUBLECLICK ////////////////
  if (btn == ClickEncoder::DoubleClicked)
  {
    btn = ClickEncoder::Open;
    return static_cast<int>(escCmd);
  }

  int d = pos - oldPos;

  if (btn == ClickEncoder::Pressed || btn == ClickEncoder::Held)
  {
    btn = ClickEncoder::Open;

    //////////////// ENCODER DOWN ////////////////
    if (d <= -sensivity)
    {
      return static_cast<int>(downCmd);
    }
    
    //////////////// ENCODER UP ////////////////
    if (d >= sensivity)
    {
      return static_cast<int>(upCmd);
    }
  }

  btn = ClickEncoder::Open;

  //////////////// ENCODER RIGHT ////////////////
  if (d <= -sensivity)
  {
    return static_cast<int>(rightCmd);
  }

  //////////////// ENCODER LEFT ////////////////
  if (d >= sensivity)
  {
    return static_cast<int>(leftCmd);
  }

  return static_cast<int>(noCmd);
}
  