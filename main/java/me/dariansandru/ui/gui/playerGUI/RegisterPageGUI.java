package me.dariansandru.ui.gui.playerGUI;

import me.dariansandru.dbms.DBUpdater;

import javax.swing.*;
import java.awt.*;

public class RegisterPageGUI {

    private JFrame frame;

    public RegisterPageGUI() {
        drawGUI();
    }

    public JFrame getFrame() {
        return frame;
    }

    JLabel usernameLabel;
    JTextField usernameField;

    JLabel emailLabel;
    JTextField emailField;

    JLabel passwordLabel;
    JPasswordField passwordField;

    JLabel confirmPasswordLabel;
    JPasswordField confirmPasswordField;

    public void drawGUI() {
        frame = new JFrame("Register Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 400);
        frame.setLayout(new BorderLayout());

        JLabel titleLabel = new JLabel("Register for Chess App", SwingConstants.CENTER);
        titleLabel.setFont(new Font("Arial", Font.BOLD, 20));
        frame.add(titleLabel, BorderLayout.NORTH);
        
        JPanel formPanel = new JPanel(new GridLayout(4, 2, 10, 10));
        formPanel.setBorder(BorderFactory.createEmptyBorder(20, 50, 20, 50));

        usernameLabel = new JLabel("Username:");
        usernameField = new JTextField();

        emailLabel = new JLabel("Email:");
        emailField = new JTextField();

        passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        formPanel.add(usernameLabel);
        formPanel.add(usernameField);
        formPanel.add(emailLabel);
        formPanel.add(emailField);
        formPanel.add(passwordLabel);
        formPanel.add(passwordField);
        formPanel.add(confirmPasswordLabel);
        formPanel.add(confirmPasswordField);

        frame.add(formPanel, BorderLayout.CENTER);
        
        JPanel buttonPanel = new JPanel(new FlowLayout());
        JButton registerButton = new JButton("Register");
        JButton backButton = new JButton("Back");

        registerButton.addActionListener(e -> registerValidation());
        backButton.addActionListener(e -> frame.dispose()); 

        buttonPanel.add(registerButton);
        buttonPanel.add(backButton);

        frame.add(buttonPanel, BorderLayout.SOUTH);

        frame.setVisible(true);
    }

    private void registerValidation() {
        String username = usernameField.getText();
        String email = emailField.getText();
        String password = String.valueOf(passwordField.getPassword());
        String confirmPassword = String.valueOf(confirmPasswordField.getPassword());

        if (username.isEmpty()){
            JOptionPane.showMessageDialog(null, "You must provide your username!", "Input Error", JOptionPane.ERROR_MESSAGE);
            resetTextFields();
            return;
        }

        if (email.isEmpty()){
            JOptionPane.showMessageDialog(null, "You must provide your email!", "Input Error", JOptionPane.ERROR_MESSAGE);
            resetTextFields();
            return;
        }

        if (password.isEmpty()){
            JOptionPane.showMessageDialog(null, "You must provide your password!", "Input Error", JOptionPane.ERROR_MESSAGE);
            resetTextFields();
            return;
        }

        if (confirmPassword.isEmpty()){
            JOptionPane.showMessageDialog(null, "You must confirm your password!", "Input Error", JOptionPane.ERROR_MESSAGE);
            resetTextFields();
            return;
        }

        String[] emailParts = email.split("@");
        if (emailParts.length != 2){
            JOptionPane.showMessageDialog(null, "You must provide a valid email!", "Input Error", JOptionPane.ERROR_MESSAGE);
            resetTextFields();
            return;
        }

        String[] emailParts2 = emailParts[1].split("\\.");
        if (emailParts2.length != 2){
            JOptionPane.showMessageDialog(null, "You must provide a valid email!", "Input Error", JOptionPane.ERROR_MESSAGE);
            resetTextFields();
            return;
        }

        if (password.length() < 8){
            JOptionPane.showMessageDialog(null, "The length of the password must be at least 8 characters!", "Input Error", JOptionPane.ERROR_MESSAGE);
            resetTextFields();
            return;
        }

        DBUpdater.insertPlayer(username, email, password, 1000);
        JOptionPane.showMessageDialog(null, "Register successful!", "Success", JOptionPane.INFORMATION_MESSAGE);
        frame.dispose();
    }

    private void resetTextFields() {
        usernameField.setText("");
        emailField.setText("");
        passwordField.setText("");
        confirmPasswordField.setText("");
    }
}
