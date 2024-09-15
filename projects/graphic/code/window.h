

#pragma once

namespace Display {
    class Window {
    public:
        Window() = default;       // Default constructor
        ~Window() = default;      // Destructor

        bool Open() {
            // Simulate window opening. Normally, you would use a library like GLFW/SDL here.
            return true;
        }

        void Update() {
            // Placeholder for window update logic (e.g., polling events)
        }

        void SwapBuffers() {
            // Placeholder for swapping buffers (usually handled by an API like OpenGL/GLFW)
        }

        void Close() {
            // Placeholder for closing the window
        }

        bool IsOpen() {
            // Return true to simulate an open window, should change to false when closing
            return true;
        }
    };
}
