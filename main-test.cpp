#include "gtest/gtest.h"
#include <sstream>
#include <string>
#include <iostream>

// Declarations from production code
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
    EXPECT_EQ(size(38), 'M'); // BUG: will fail
    EXPECT_EQ(size(40), 'M');
    EXPECT_EQ(size(42), 'L'); // BUG: will fail
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
    // Check first line alignment and correct mapping
    // BUG: Will fail because minor color uses wrong index
    EXPECT_NE(output.find("0 | White | Blue"), std::string::npos);
    // Optional extra check: column alignment
    std::istringstream iss(output);
    std::string firstLine;
    std::getline(iss, firstLine);
    EXPECT_EQ(firstLine[2], ' '); // expecting a space after single-digit numbers
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
    // BUG: Will fail because code doesn't handle this as rain
    EXPECT_NE(report.find("rain"), std::string::npos);
}

