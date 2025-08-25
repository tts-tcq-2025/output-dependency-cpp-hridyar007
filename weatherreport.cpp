#include "helpers.h"

namespace WeatherSpace {
    // SensorStub for production/integration
    class SensorStub : public IWeatherSensor {
    public:
        int Humidity() const override { return 72; }
        int Precipitation() const override { return 70; }
        double TemperatureInC() const override { return 26; }
        int WindSpeedKMPH() const override { return 52; }
    };
}
