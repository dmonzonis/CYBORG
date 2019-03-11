#include "version.h"

#include <iostream>

#include <lazarus/rng.h>
#include <lazarus/common.h>
#include <lazarus/graphics.h>

using namespace std;

int main(int argc, char const *argv[])
{
    DEBUG("Version %d.%d", PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR);
    
    // Test that random module is loaded and works
    Random::Seed();
    cout << Random::rng(0, 2) << endl;
    
    // Test that graphics module is loaded and works
    Graphics::WindowLoop();

    return 0;
}
