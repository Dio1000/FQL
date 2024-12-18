package me.dariansandru.ui.consoleUI;

import me.dariansandru.domain.validator.exception.ValidatorException;
import me.dariansandru.io.InputDevice;
import me.dariansandru.io.OutputDevice;
import me.dariansandru.io.exception.InputException;
import me.dariansandru.io.exception.OutputException;

/**
 * Implementing this interface allows an object to be displayed and
 * interact with the user through input / output.
 */
public interface ConsoleUI {

    /**
     * Gets the OutputDevice the Console uses.
     * @return OutputDevice that is used.
     */
    OutputDevice getOutputDevice();

    /**
     * Gets the InputDevice the Console uses.
     * @return InputDevice that is used.
     */
    InputDevice getInputDevice();

    /**
     * Displays the game and allows for input / output.
     * @throws InputException Thrown when input validation fails.
     * @throws OutputException Thrown when output validation fails.
     * @throws ValidatorException Thrown when validator fails.
     */
    void show() throws InputException, OutputException, ValidatorException;
}
