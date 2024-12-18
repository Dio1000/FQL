package me.dariansandru.ui.guiController.playerGUIController;

import me.dariansandru.controller.ChessController;
import me.dariansandru.dbms.loggedUsers.LoggedPlayer;
import me.dariansandru.domain.Player;
import me.dariansandru.io.InputDevice;
import me.dariansandru.io.OutputDevice;
import me.dariansandru.io.exception.InputException;
import me.dariansandru.ui.consoleUI.ChessConsoleUI;
import me.dariansandru.ui.gui.playerGUI.MainPageGUI;
import me.dariansandru.ui.gui.playerGUI.LoginPageGUI;
import me.dariansandru.ui.gui.playerGUI.RegisterPageGUI;
import me.dariansandru.ui.guiController.NavigationController;

import javax.swing.*;

public class MainPageGUIController {

    private MainPageGUI mainPageGUI;

    public MainPageGUIController(MainPageGUI mainPageGUI) {
        this.mainPageGUI = mainPageGUI;
    }

    public void setMainPageGUI(MainPageGUI mainPageGUI) {
        this.mainPageGUI = mainPageGUI;
    }

    public void run() {
        mainPageGUI.drawGUI();
        mainPageGUI.updateLoggedPlayer();

        mainPageGUI.setLoginButtonAction(e -> {
            if (LoggedPlayer.getLoggedPlayer() != null) {
                JOptionPane.showMessageDialog(null, "You are already logged in!", "Success", JOptionPane.INFORMATION_MESSAGE);
                return;
            }
            LoginPageGUI loginPage = new LoginPageGUI();
            NavigationController.navigateTo(loginPage.getFrame());
        });

        mainPageGUI.setRegisterButtonAction(e -> {
            if (LoggedPlayer.getLoggedPlayer() != null) {
                JOptionPane.showMessageDialog(null, "You are already logged in!", "Success", JOptionPane.INFORMATION_MESSAGE);
                return;
            }
            RegisterPageGUI registerPage = new RegisterPageGUI();
            NavigationController.navigateTo(registerPage.getFrame());
        });

        mainPageGUI.setPlayButtonAction(e -> {
            InputDevice inputDevice = new InputDevice();
            OutputDevice outputDevice = new OutputDevice();

            Player p1 = new Player();
            Player p2 = new Player();

            ChessController chessController;
            try {
                chessController = new ChessController(p1, p2);
            } catch (InputException ex) {
                throw new RuntimeException(ex);
            }
            ChessConsoleUI chessConsoleUI = new ChessConsoleUI(inputDevice, outputDevice, chessController);
            ChessGUIController guiController = new ChessGUIController(chessConsoleUI);
            guiController.run();
        });
    }
}
