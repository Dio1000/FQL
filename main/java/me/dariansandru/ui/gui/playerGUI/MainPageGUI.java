package me.dariansandru.ui.gui.playerGUI;

import me.dariansandru.dbms.loggedUsers.LoggedPlayer;
import me.dariansandru.domain.Player;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class MainPageGUI extends JFrame{

    private JFrame frame;

    private JButton loginButton;
    private JButton registerButton;
    private JButton playButton;
    private JLabel messageLabel;

    private Player loggedPlayer = LoggedPlayer.getLoggedPlayer();

    public JFrame getFrame() {
        return frame;
    }

    public Player getPlayer(){
        return loggedPlayer;
    }

    public void setPlayer(Player newPlayer){
        loggedPlayer = newPlayer;
    }

    public void updateLoggedPlayer(){
        if (loggedPlayer == null) messageLabel.setText("You are not logged in!");
        else messageLabel.setText("Welcome " + loggedPlayer.getUsername());
    }

    public void drawGUI() {
        frame = new JFrame("Chess Page");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);
        frame.setLayout(new BorderLayout());

        JLabel placeholderLabel = new JLabel("ChessPlaceholder", SwingConstants.CENTER);
        placeholderLabel.setFont(new Font("Arial", Font.BOLD, 20));
        frame.add(placeholderLabel, BorderLayout.NORTH);

        if (messageLabel == null) messageLabel = new JLabel("You are not logged in!", SwingConstants.CENTER);
        updateLoggedPlayer();

        messageLabel.setFont(new Font("Arial", Font.PLAIN, 14));
        frame.add(messageLabel, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.Y_AXIS));
        buttonPanel.setAlignmentX(Component.CENTER_ALIGNMENT);

        loginButton = new JButton("Login");
        registerButton = new JButton("Register");
        playButton = new JButton("Play");

        loginButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        registerButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        playButton.setAlignmentX(Component.CENTER_ALIGNMENT);

        buttonPanel.add(Box.createRigidArea(new Dimension(0, 10)));
        buttonPanel.add(playButton);
        buttonPanel.add(Box.createRigidArea(new Dimension(0, 10)));
        buttonPanel.add(loginButton);
        buttonPanel.add(Box.createRigidArea(new Dimension(0, 10)));
        buttonPanel.add(registerButton);

        frame.add(buttonPanel, BorderLayout.SOUTH);

        frame.setVisible(true);
    }

    public void setLoginButtonAction(ActionListener action) {
        loginButton.addActionListener(action);
    }

    public void setRegisterButtonAction(ActionListener action) {
        registerButton.addActionListener(action);
    }

    public void setPlayButtonAction(ActionListener action) {
        playButton.addActionListener(action);
    }
}
