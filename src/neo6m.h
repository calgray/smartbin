#include <TinyGPS++.h>

class Neo6M
{
    TinyGPSPlus _gps;
public:
    Neo6M();
    ~Neo6M();

    /**
     * @brief Reads the UART device into TinyGPS
     * and returns the result.
     * 
     * @return const TinyGPSPlus* 
     */
    const TinyGPSPlus& read();

    const TinyGPSPlus& get();
};