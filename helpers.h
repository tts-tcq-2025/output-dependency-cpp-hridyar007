#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <vector>

// Range classification
char classifyTShirtSize(int cms);

// Color map printer
int printTable(const std::vector<std::string>& majorColors,
               const std::vector<std::string>& minorColors);

// Weather report
namespace WeatherSpace {
    class IWeatherSensor {
    public:
        virtual double TemperatureInC() const = 0;
        virtual int Precipitation() const = 0;
        virtual int Humidity() const = 0;
        virtual int WindSpeedKMPH() const = 0;
    };
    std::string Report(const IWeatherSensor& sensor);
}

#endif
