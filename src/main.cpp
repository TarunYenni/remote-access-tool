#include "screen_capture.h"
#include <iostream>

int main() {
    ScreenCapture capture;

    for (int i = 0; i < 10; i++) {
        if (capture.CaptureFrame()) {
            std::cout << "Frame captured: " << i + 1 << std::endl;
        }
        Sleep(100); // Small delay between captures
    }

    return 0;
}