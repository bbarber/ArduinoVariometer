
#ifndef Vario_h
#define Vario_h

class Vario
{
  public:
    void setup();
    float getRelativeAltitude();
  private:
    float getPressure();
    float getTemperature();
    float getAltitude();
    float getAltitudeAvg();
};

#endif


