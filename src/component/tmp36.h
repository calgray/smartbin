#pragma once

class TMP36
{
    int _tmp;
public:
    TMP36(int tmp)
    : _tmp(tmp)
    {
        pinMode(_tmp, INPUT);
    }

    ~TMP36()
    {

    }

    /**
     * @brief Reads the current temperature in degrees celcius
     * 
     * @return float
     */
    float read()
    {
        uint32_t mv = analogReadMilliVolts(_tmp);

        // TMP36 operates between -40*C to 125*C
        // 750mV == 25*C, 10mV/*C
        // 500mV == 0*C
        return (mv - 500) / 10.0;
    }
};

// CREATE TABLE `smartbin`.`temperature` (
//   `id` INT NOT NULL AUTO_INCREMENT,
//   `device_id` INT NOT NULL,
//   `temp_celcius` INT NULL,
//   PRIMARY KEY (`id`),
//   UNIQUE INDEX `id_UNIQUE` (`id` ASC) VISIBLE);
