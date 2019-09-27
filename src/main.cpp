#include "version.h"

#include <iostream>

#include <lazarus/Random.h>
#include <lazarus/common.h>
#include <lazarus/Graphics.h>

using namespace std;

int main(int argc, char const *argv[])
{
    DEBUG("Version %d.%d", PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR);
    
    // Test that random module is loaded and works
    lz::Random::seed();
    cout << lz::Random::roll(6, 2) << endl;
    
    // Test that graphics module is loaded and works
    lz::Window window(25, 20);
    window.renderLoop();

    return 0;
}
