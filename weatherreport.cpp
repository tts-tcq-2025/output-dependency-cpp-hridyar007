#include <string>
#include <iostream>

namespace WeatherSpace
{
    class IWeatherSensor {
    public:
        virtual double TemperatureInC() const = 0;
        virtual int Precipitation() const = 0;
        virtual int Humidity() const = 0;
        virtual int WindSpeedKMPH() const = 0;
    };

    class SensorStub : public IWeatherSensor {
    public:
        int Humidity() const override {
            return 72;
        }
        int Precipitation() const override {
            return 70;
        }
        double TemperatureInC() const override {
            return 26;
        }
        int WindSpeedKMPH() const override {
            return 52;
        }
    };

    std::string Report(const IWeatherSensor& sensor)
    {
        int precipitation = sensor.Precipitation();
        std::string report = "Sunny Day";

        if (sensor.TemperatureInC() > 25)
        {
            if (precipitation >= 20 && precipitation < 60)
                report = "Partly Cloudy";
            else if (sensor.WindSpeedKMPH() > 50)
                report = "Alert, Stormy with heavy rain";
        }
        return report;
    }
}
