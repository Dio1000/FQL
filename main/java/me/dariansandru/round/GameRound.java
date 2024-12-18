package me.dariansandru.round;

import me.dariansandru.io.exception.InputException;

/**
 * Implementing this interface allows an object to store and set
 * pieces on a board.
 */
public interface GameRound {

    /**
     * Resets the board of the game.
     * @throws InputException Thrown when input validation fails.
     */
    public void resetBoard() throws InputException;

    /**
     * Sets the pieces.
     * @throws InputException Thrown when input validation fails.
     */
    public void setPieceLocation() throws InputException;
}
