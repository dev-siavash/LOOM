#include "InputState.h"
#include "InternalShuttles.h"
#include "InternalFunctions.h"

using namespace LOOM::InternalUtilities;

namespace LOOM::Shuttles
{
    void InputShuttle(entt::registry& frame, Fibers::InputState& inputState, std::function<void(void)> terminateCallback)
    {
        inputState.prevKeyStates = inputState.keyStates;
        for (size_t i = 0; i < 3; i++)
            inputState.prevMouseButtonStates[i] = inputState.mouseButtonStates[i];

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                terminateCallback();
                break;
            case SDL_KEYDOWN:
                inputState.keyStates[ScancodeToKeyCode(event.key.keysym.scancode)] = true;
                break;
            case SDL_KEYUP:
                inputState.keyStates[ScancodeToKeyCode(event.key.keysym.scancode)] = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                inputState.mouseButtonStates[event.button.button - 1] = true;
                break;
            case SDL_MOUSEBUTTONUP:
                inputState.mouseButtonStates[event.button.button - 1] = false;
                break;
            default:
                break;
            }
        }
    }
}