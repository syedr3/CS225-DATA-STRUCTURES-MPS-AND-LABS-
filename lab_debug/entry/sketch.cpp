#include "sketchify.h"

/**
 * A simple wrapper function that invokes sketchify on files in the current
 * directory. Input is read from`in.png` and the resulting image is written
 * to `out.png`.
 */
int main() {
    // If you get PNG Decoder error, it is because there is no PNG named "in.png".
    // Copy a sample image (or your own) from the tests folder into your build directory.
    sketchify("in.png", "out.png");
    return 0;
}
