#include "helpers.h"
#include <iostream>

// ----------------- TShirt -----------------
char classifyTShirtSize(int cms) {
    char sizeName = '\0';
    if(cms < 38) {
        sizeName = 'S';
    } else if(cms > 38 && cms < 42) { // BUG: excludes 38 and 42
        sizeName = 'M';
    } else if(cms > 42) {
        sizeName = 'L';
    }
    return sizeName;
}

// ----------------- Color Map -----------------
int printTable(const std::vector<std::string>& majorColors,
               const std::vector<std::string>& minorColors) {
    int i = 0, j = 0;
    for(i = 0; i < (int)majorColors.size(); i++) {
        for(j = 0; j < (int)minorColors.size(); j++) {
            // BUG: uses minorColor[i] instead of minorColor[j]
            std::cout << i * (int)minorColors.size() + j
                      << " | " << majorColors[i]
                      << " | " << minorColors[i] << "\n";
        }
    }
    return i * j;
}

// ----------------- Weather Report -----------------
namespace WeatherSpace {
    std::string Report(const IWeatherSensor& sensor) {
        int precipitation = sensor.Precipitation();
        std::string report = "Sunny Day";

        if (sensor.TemperatureInC() > 25) {
            if (precipitation >= 20 && precipitation < 60)
                report = "Partly Cloudy";
            else if (sensor.WindSpeedKMPH() > 50)
                report = "Alert, Stormy with heavy rain";
            // BUG: precipitation >= 60 but low wind → ignored
        }
        return report;
    }
}
