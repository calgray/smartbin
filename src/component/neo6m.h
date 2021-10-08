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
     * @brief Reads the UART Serial into TinyGPS
     * until unavailable and returns the result.
     * 
     * @return const TinyGPSPlus&
     */
    TinyGPSPlus& read();

    /**
     * @brief Reads the UART Serial for a given time window
     * and returns the result.
     * 
     * @param ms 
     * @return TinyGPSPlus& 
     */
    TinyGPSPlus& read(unsigned long ms);

    TinyGPSPlus& get();

    void reset();
};