 /*
missilecommand.
 */

#include <Arduboy2.h>

Arduboy2 arduboy;

const unsigned int FRAME_RATE = 40; // Frame rate in frames per second

int iteration;
int x;
int y;
int x0;
int x1;
int dx;
int dy;
int xi;
int yi;
int d;

void setup()
{
  arduboy.begin();
  arduboy.setFrameRate(FRAME_RATE);
  arduboy.initRandomSeed();
}

void setup_high(void)
{
    xi = 1;
    if (dx < 0)
    {
      xi = -1;
      dx = -dx;
    }
    d = 2 * dx - dy;
}

void setup_low(void)
{
    yi = 1;
    if (dy < 0)
    {
      yi = -1;
      dy = -dy;
    }
    d = 2 * dy - dx;
}

void plot_high(void)
{
  if (d > 0)
  {
    x = x + xi;
    d = d - 2 * dy;
  }
  d = d + 2 * dx;
  y++;
}

void plot_low(void)
{
  if (d > 0)
  {
    y = y + yi;
    d = d - 2 * dx;
  }
  d = d + 2 * dy;
  if (dx > 0)
    x++;
  else
    x--;
}

void loop()
{
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  switch (iteration)
  {
  case 0:
    arduboy.clear();
    arduboy.setCursor(20, 30);
    arduboy.print(F("missile command"));
    iteration++;
    break;
  case 1:
//    x0 = random(0, 127);
//    x1 = random(0, 127);
x0 = 127; x1 = 20; // fix this case
//x0=0;x1=120;
    dx = x1 - x0;
    dy = 63;
    x = x0;
    y = 0;
    if (abs(dx) <= 63)
      setup_high();
    else
      setup_low();
    iteration++;
    break;
  default:
    if (y < 60)
    {
      arduboy.drawPixel(x, y, 1);      
      if (abs(dx) <= 63)
        plot_high();
      else
        plot_low();
    }
    else
    {
      iteration = 1;
    }
    break;   
  }

  arduboy.display();
}
