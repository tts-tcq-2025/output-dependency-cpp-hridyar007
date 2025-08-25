#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <iostream>

// Production code headers
char size(int cms);
int printColorMap();
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

// ========================
//  Stronger T-Shirt Tests
// ========================
TEST(TShirt, Size) {
    std::cout << "\nTshirt size test\n";
    EXPECT_EQ(size(37), 'S');
    EXPECT_EQ(size(38), 'M'); // BUG: will currently fail
    EXPECT_EQ(size(40), 'M');
    EXPECT_EQ(size(42), 'L'); // BUG: will currently fail
    EXPECT_EQ(size(43), 'L');
}

// ========================
//  Stronger Color Map Tests
// ========================
TEST(ColorMap, Print) {
    std::cout << "\nPrint color map test\n"; 

    // Capture output
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    int result = printColorMap();

    std::cout.rdbuf(oldCout); // restore
    std::string output = buffer.str();

    EXPECT_EQ(result, 25);
    // Check first mapping is correct (minor color should be Blue, not White)
    EXPECT_NE(output.find("0 | White | Blue"), std::string::npos); // BUG: will fail

    // Alignment check: "0 " should be followed by a space before '|'
    std::istringstream iss(output);
    std::string firstLine;
    std::getline(iss, firstLine);
    EXPECT_EQ(firstLine[2], ' '); // expecting single digit number aligned with space
}

// ========================
//  Stronger Weather Tests
// ========================
class HighPrecipLowWindStub : public WeatherSpace::IWeatherSensor {
public:
    double TemperatureInC() const override { return 26; }
    int Precipitation() const override { return 70; } // high precipitation
    int Humidity() const override { return 80; }
    int WindSpeedKMPH() const override { return 10; } // low wind speed
};

TEST(WeatherReport, HighPrecipitation) {
    std::cout << "\nWeather report test\n";
    HighPrecipLowWindStub sensor;
    std::string report = WeatherSpace::Report(sensor);
    std::cout << "Report: " << report << "\n";
    // BUG: code treats this as "Sunny Day", not "Rain"
    EXPECT_NE(report.find("rain"), std::string::npos);
}
