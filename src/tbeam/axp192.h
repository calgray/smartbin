
#include <axp20x.h>

class Axp192
{
    AXP20X_Class _axp;
public:
    Axp192();
    ~Axp192();

    AXP20X_Class& getimpl() { return _axp; }
};