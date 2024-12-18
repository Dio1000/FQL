package me.dariansandru.ui.gui.playerGUI;

import me.dariansandru.dbms.DBQuery;
import me.dariansandru.dbms.loggedUsers.LoggedPlayer;
import me.dariansandru.domain.Player;
import me.dariansandru.ui.guiController.NavigationController;

import javax.swing.*;
import java.awt.*;
import java.util.List;
import java.util.Objects;

public class LoginPageGUI {

    private JFrame frame;

    public LoginPageGUI() {
        drawGUI();
    }

    public JFrame getFrame() {
        return frame;
    }

    JLabel usernameLabel;
    JTextField usernameField;

    JLabel passwordLabel;
    JPasswordField passwordField;

    public void drawGUI() {
        frame = new JFrame("Login Page");
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setSize(400, 300);
        frame.setLayout(new BorderLayout());

        JLabel titleLabel = new JLabel("Login to Chess App", SwingConstants.CENTER);
        titleLabel.setFont(new Font("Arial", Font.BOLD, 20));
        frame.add(titleLabel, BorderLayout.NORTH);

        JPanel formPanel = new JPanel(new GridLayout(3, 2, 10, 10));
        formPanel.setBorder(BorderFactory.createEmptyBorder(20, 50, 20, 50));

        usernameLabel = new JLabel("Username:");
        usernameField = new JTextField();

        passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        formPanel.add(usernameLabel);
        formPanel.add(usernameField);
        formPanel.add(passwordLabel);
        formPanel.add(passwordField);

        frame.add(formPanel, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new FlowLayout());
        JButton loginButton = new JButton("Login");
        JButton backButton = new JButton("Back");

        loginButton.addActionListener(e -> loginValidation());
        backButton.addActionListener(e -> frame.dispose());

        buttonPanel.add(loginButton);
        buttonPanel.add(backButton);

        frame.add(buttonPanel, BorderLayout.SOUTH);

        frame.setVisible(true);
    }

    private void loginValidation() {
        String username = usernameField.getText();
        String password = String.valueOf(passwordField.getPassword());

        if (username.isEmpty()) {
            JOptionPane.showMessageDialog(null, "You must provide your username!", "Input Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        if (password.isEmpty()) {
            JOptionPane.showMessageDialog(null, "You must provide your password!", "Input Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        List<String> usernames = DBQuery.getAllUsernames();
        if (!usernames.contains(username)) {
            JOptionPane.showMessageDialog(null, "Could not find username!", "Login Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        String correctPassword = DBQuery.getDataByUsername(username).get(3);
        if (!Objects.equals(password, correctPassword)) {
            JOptionPane.showMessageDialog(null, "Your password is incorrect!", "Login Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        Player loggedPlayer = new Player();
        List<String> loggedPlayerData = DBQuery.getDataByUsername(username);
        DBQuery.setPlayerData(loggedPlayer, loggedPlayerData);

        JOptionPane.showMessageDialog(null, "Login successful!", "Success", JOptionPane.INFORMATION_MESSAGE);
        LoggedPlayer.setLoggedPlayer(loggedPlayer);

        NavigationController.navigateToMainPage();
    }


}
