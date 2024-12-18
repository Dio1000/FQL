package me.dariansandru.ui.gui.adminGUI;

import me.dariansandru.domain.Admin;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class AdminMainPageGUI extends JFrame {

    private final JFrame frame = new JFrame("Admin Main Page");

    private final JButton controllerButton = new JButton("Controller");
    private final JButton loginButton = new JButton("Login");
    private final JButton registerButton = new JButton("Register");
    private final JButton exitButton = new JButton("Exit");

    private JLabel loggedAdminLabel = new JLabel("Login", SwingConstants.CENTER);

    private Admin loggedAdmin = null;

    public JFrame getFrame() {
        return frame;
    }

    public void setAdmin(Admin admin) {
        loggedAdmin = admin;
    }

    public void updateLoggedAdmin() {
        if (loggedAdmin == null)
            loggedAdminLabel.setText("You are not logged in yet!");
        else
            loggedAdminLabel.setText("Welcome " + loggedAdmin.getUsername());
    }

    public void drawGUI() {
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 400); 
        frame.setLayout(new BorderLayout());

        JLabel placeholderLabel = new JLabel("Chess Administration", SwingConstants.CENTER);
        placeholderLabel.setFont(new Font("Arial", Font.BOLD, 24));
        placeholderLabel.setForeground(Color.BLUE);
        frame.add(placeholderLabel, BorderLayout.NORTH);

        updateLoggedAdmin();

        loggedAdminLabel.setFont(new Font("Arial", Font.PLAIN, 16));
        loggedAdminLabel.setForeground(Color.DARK_GRAY);
        frame.add(loggedAdminLabel, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.Y_AXIS));
        buttonPanel.setAlignmentX(Component.CENTER_ALIGNMENT);

        styleButton(controllerButton);
        styleButton(loginButton);
        styleButton(registerButton);
        styleButton(exitButton);

        buttonPanel.add(Box.createRigidArea(new Dimension(0, 20)));
        buttonPanel.add(controllerButton);
        buttonPanel.add(Box.createRigidArea(new Dimension(0, 10)));
        buttonPanel.add(loginButton);
        buttonPanel.add(Box.createRigidArea(new Dimension(0, 10)));
        buttonPanel.add(registerButton);
        buttonPanel.add(Box.createRigidArea(new Dimension(0, 10)));
        buttonPanel.add(exitButton);

        frame.add(buttonPanel, BorderLayout.SOUTH);
        frame.setVisible(true);
    }

    private void styleButton(JButton button) {
        button.setFont(new Font("Arial", Font.PLAIN, 14));
        button.setPreferredSize(new Dimension(200, 40));
        button.setBackground(Color.LIGHT_GRAY);
        button.setFocusPainted(false);
        button.setAlignmentX(Component.CENTER_ALIGNMENT);
    }

    public void setLoginButtonAction(ActionListener action) {
        loginButton.addActionListener(action);
    }

    public void setRegisterButtonAction(ActionListener action) {
        registerButton.addActionListener(action);
    }

    public void setControllerButton(ActionListener action) {
        controllerButton.addActionListener(action);
    }

    public void setExitButtonAction(ActionListener action) {
        exitButton.addActionListener(action);
    }
}
