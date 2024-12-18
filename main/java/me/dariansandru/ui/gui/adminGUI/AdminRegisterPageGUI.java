package me.dariansandru.ui.gui.adminGUI;

import me.dariansandru.dbms.DBQuery;
import me.dariansandru.dbms.DBUpdater;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class AdminRegisterPageGUI {

    private JFrame frame;

    public AdminRegisterPageGUI() {
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

    JCheckBox banPermissionCheckBox;
    JCheckBox modifyRatingPermissionCheckBox;
    JCheckBox reportHackerPermissionCheckBox;

    public void drawGUI() {
        frame = new JFrame("Admin Register Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 500);
        frame.setLayout(new BorderLayout());

        JLabel titleLabel = new JLabel("Register Admin for Chess App", SwingConstants.CENTER);
        titleLabel.setFont(new Font("Arial", Font.BOLD, 20));
        frame.add(titleLabel, BorderLayout.NORTH);

        JPanel formPanel = new JPanel(new GridLayout(7, 2, 10, 10));
        formPanel.setBorder(BorderFactory.createEmptyBorder(20, 50, 20, 50));

        usernameLabel = new JLabel("Username:");
        usernameField = new JTextField();

        emailLabel = new JLabel("Email:");
        emailField = new JTextField();

        passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        confirmPasswordLabel = new JLabel("Confirm Password:");
        confirmPasswordField = new JPasswordField();

        banPermissionCheckBox = new JCheckBox("Ban Permission");
        modifyRatingPermissionCheckBox = new JCheckBox("Modify Rating Permission");
        reportHackerPermissionCheckBox = new JCheckBox("Report Hacker Permission");

        formPanel.add(usernameLabel);
        formPanel.add(usernameField);
        formPanel.add(emailLabel);
        formPanel.add(emailField);
        formPanel.add(passwordLabel);
        formPanel.add(passwordField);
        formPanel.add(confirmPasswordLabel);
        formPanel.add(confirmPasswordField);

        formPanel.add(new JLabel("Select Permissions:"));
        JPanel checkBoxPanel = new JPanel(new GridLayout(3, 1));
        checkBoxPanel.add(banPermissionCheckBox);
        checkBoxPanel.add(modifyRatingPermissionCheckBox);
        checkBoxPanel.add(reportHackerPermissionCheckBox);
        formPanel.add(checkBoxPanel);

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
        List<String> permissions = new ArrayList<>();

        if (banPermissionCheckBox.isSelected()) {
            permissions.add("Ban Permission");
        }
        if (modifyRatingPermissionCheckBox.isSelected()) {
            permissions.add("Modify Rating Permission");
        }
        if (reportHackerPermissionCheckBox.isSelected()) {
            permissions.add("Report Hacker Permission");
        }

        if (username.isEmpty()) {
            JOptionPane.showMessageDialog(null, "You must provide your username!", "Input Error", JOptionPane.ERROR_MESSAGE);
            resetTextFields();
            return;
        }

        if (email.isEmpty()) {
            JOptionPane.showMessageDialog(null, "You must provide your email!", "Input Error", JOptionPane.ERROR_MESSAGE);
            resetTextFields();
            return;
        }

        if (password.isEmpty()) {
            JOptionPane.showMessageDialog(null, "You must provide your password!", "Input Error", JOptionPane.ERROR_MESSAGE);
            resetTextFields();
            return;
        }

        if (confirmPassword.isEmpty()) {
            JOptionPane.showMessageDialog(null, "You must confirm your password!", "Input Error", JOptionPane.ERROR_MESSAGE);
            resetTextFields();
            return;
        }

        if (!password.equals(confirmPassword)) {
            JOptionPane.showMessageDialog(null, "Passwords do not match!", "Input Error", JOptionPane.ERROR_MESSAGE);
            resetTextFields();
            return;
        }

        if (password.length() < 8) {
            JOptionPane.showMessageDialog(null, "The length of the password must be at least 8 characters!", "Input Error", JOptionPane.ERROR_MESSAGE);
            resetTextFields();
            return;
        }

        DBUpdater.insertAdmin(username, email, password, permissions);
        DBUpdater.insertPermissions(Integer.parseInt(DBQuery.getAdminDataByUsername(username).get(0)), permissions);
        JOptionPane.showMessageDialog(null, "Admin Register successful!", "Success", JOptionPane.INFORMATION_MESSAGE);
        frame.dispose();
    }

    private void resetTextFields() {
        usernameField.setText("");
        emailField.setText("");
        passwordField.setText("");
        confirmPasswordField.setText("");
        banPermissionCheckBox.setSelected(false);
        modifyRatingPermissionCheckBox.setSelected(false);
        reportHackerPermissionCheckBox.setSelected(false);
    }
}
