package me.dariansandru.controller;

import me.dariansandru.io.exception.InputException;

/**
 * Implementing this interface allows an object to
 * control the logic from a GameRound.
 */
public interface GameController {

    /**
     * Plays a round of the controlled game.
     * @param move Move that is passed by the GameRound.
     * @return Error string in case there is any, null otherwise.
     */
    String play(String move);

    /**
     * Resets the round of the controlled game.
     * @throws InputException Input validation failed.
     */
    void reset() throws InputException;
}
