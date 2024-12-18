package me.dariansandru.ui.guiController;

import me.dariansandru.ui.gui.adminGUI.AdminMainPageGUI;
import me.dariansandru.ui.gui.playerGUI.MainPageGUI;
import me.dariansandru.ui.guiController.adminGUIController.AdminMainPageGUIController;
import me.dariansandru.ui.guiController.playerGUIController.MainPageGUIController;

import javax.swing.*;

public class NavigationController {

    private static JFrame currentFrame;

    private static MainPageGUI mainPageGUI;
    private static MainPageGUIController mainPageGUIController;

    private static AdminMainPageGUI adminMainPageGUI;
    private static AdminMainPageGUIController adminMainPageGUIController;

    public static void setup(MainPageGUIController mainPageGUIController, MainPageGUI mainPageGUI) {
        NavigationController.mainPageGUIController = mainPageGUIController;
        NavigationController.mainPageGUI = mainPageGUI;
        NavigationController.mainPageGUIController.setMainPageGUI(mainPageGUI);
        NavigationController.mainPageGUIController.run();
    }

    public static void setup(AdminMainPageGUIController adminMainPageGUIController, AdminMainPageGUI adminMainPageGUI) {
        NavigationController.adminMainPageGUIController = adminMainPageGUIController;
        NavigationController.adminMainPageGUI = adminMainPageGUI;
        NavigationController.adminMainPageGUIController.setAdminMainPageGUI(adminMainPageGUI);
        NavigationController.adminMainPageGUIController.run();
    }

    public static void setCurrentFrame(JFrame frame) {
        if (currentFrame != null) {
            currentFrame.dispose();
        }
        currentFrame = frame;
    }

    public static void navigateTo(JFrame newFrame) {
        setCurrentFrame(newFrame);
        newFrame.setVisible(true);
    }

    public static void navigateToMainPage() {
        if (mainPageGUI != null) {
            navigateTo(mainPageGUI.getFrame());
            mainPageGUI.updateLoggedPlayer();
        }
    }

    public static void navigateToAdminMainPage() {
        if (adminMainPageGUI != null) {
            navigateTo(adminMainPageGUI.getFrame());
            adminMainPageGUI.updateLoggedAdmin();
        }
    }
}
