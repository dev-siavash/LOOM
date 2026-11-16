/**
 * @file ShuttleShed.h
 * @brief Frame phases.
 */
#ifndef SHED_H
#define SHED_H

namespace LOOM
{
    /**
     * @brief Frame phase a shuttle runs in, in execution order.
     *
     * Built-in shuttles: Input (PreUpdate, -1), Audio (PreUpdate, 0), UI (PostUpdate, -1), Physics (PostUpdate, 0),
     * text cache (Render, -1), rendering (Render, 0).
     */
    enum ShuttleShed
    {
        /** @brief Before game logic (input, audio). */
        PreUpdate,
        /** @brief Game logic. */
        Update,
        /** @brief After game logic (UI state, physics). */
        PostUpdate,
        /** @brief Drawing; the frame is presented at the end of the built-in render shuttle. */
        Render,
        /** @brief After the frame is presented. */
        PostRender
    };
}

#endif