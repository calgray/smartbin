#include <TinyGPS++.h>

class Neo6M
{
    TinyGPSPlus _gps;
public:
    /**
     * @brief Construct a new Neo-6M object
     * AXP192_LDO3 must be enabled if axp not provided
     */
    Neo6M();
    ~Neo6M();

    /**
     * @brief Reads the UART device into TinyGPS
     * and returns the result.
     * 
     * @return const TinyGPSPlus&
     */
    TinyGPSPlus& read();

    TinyGPSPlus& get();
};