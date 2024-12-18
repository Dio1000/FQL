package me.dariansandru.ui.guiController.playerGUIController;

import me.dariansandru.controller.ChessController;
import me.dariansandru.domain.chess.chessEngine.ChessEngine;
import me.dariansandru.domain.chess.piece.PieceColour;
import me.dariansandru.domain.validator.exception.ValidatorException;
import me.dariansandru.io.exception.InputException;
import me.dariansandru.round.ChessRound;
import me.dariansandru.ui.consoleUI.ChessConsoleUI;
import me.dariansandru.ui.gui.playerGUI.ChessGUI;

import javax.swing.*;
import java.awt.*;

public class ChessGUIController {

    private final ChessRound chessRound;
    private final ChessEngine chessEngine;
    private int turnCounter;

    private static class EvaluationBar extends JPanel {
        private int whitePercentage = 250;

        public void setWhitePercentage(int percentage) {
            this.whitePercentage = Math.max(0, Math.min(percentage, 500));
            repaint();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            int width = getWidth();
            int height = getHeight();

            g.setColor(Color.WHITE);
            g.fillRect(0, 0, (width * whitePercentage) / 500, height);

            g.setColor(Color.BLACK);
            g.fillRect((width * whitePercentage) / 500, 0, width - (width * whitePercentage) / 500, height);
        }
    }

    public ChessGUIController(ChessConsoleUI chessConsoleUI) {
        ChessController chessController = chessConsoleUI.getChessController();
        this.chessRound = chessController.getChessRound();
        this.chessEngine = new ChessEngine();
        chessEngine.setChessRound(chessRound);
    }

    public void run() {
        JFrame frame = new JFrame("Chess GUI");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(1200, 700);

        ChessGUI chessPanel = new ChessGUI(chessRound);

        JPanel rightPanel = new JPanel();
        rightPanel.setBackground(Color.LIGHT_GRAY);
        rightPanel.setLayout(new BorderLayout());

        JLabel instructionLabel = new JLabel("Insert move (White's turn):");
        JTextField moveInput = new JTextField();
        JButton submitButton = new JButton("Submit");
        JButton resetButton = new JButton("Reset Game");
        JLabel error = new JLabel();

        EvaluationBar evaluationBar = new EvaluationBar();
        evaluationBar.setPreferredSize(new Dimension(200, 30));

        Font smallFont = new Font("Arial", Font.PLAIN, 14);
        instructionLabel.setFont(smallFont);
        moveInput.setFont(smallFont);
        submitButton.setFont(smallFont);
        resetButton.setFont(smallFont);
        error.setFont(smallFont);

        moveInput.setPreferredSize(new Dimension(instructionLabel.getPreferredSize().width, 20));
        submitButton.setPreferredSize(new Dimension(80, 30));
        resetButton.setPreferredSize(new Dimension(100, 30));

        JPanel inputPanel = new JPanel();
        inputPanel.setLayout(new GridLayout(6, 1, 2, 2));
        inputPanel.setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));

        inputPanel.add(instructionLabel);
        inputPanel.add(moveInput);
        inputPanel.add(submitButton);
        inputPanel.add(resetButton);
        inputPanel.add(evaluationBar);
        inputPanel.add(error);

        rightPanel.add(inputPanel, BorderLayout.CENTER);

        submitButton.addActionListener(e -> {
            try {
                String move = moveInput.getText();
                PieceColour currentColour = (turnCounter % 2 == 0) ? PieceColour.WHITE : PieceColour.BLACK;
                PieceColour nextColour = (turnCounter % 2 == 0) ? PieceColour.BLACK : PieceColour.WHITE;

                if (!chessRound.checkMovePiece(move, currentColour)) {
                    error.setText("Invalid move");
                    return;
                }

                System.out.println("Move is valid: " + move);
                var startLocation = chessRound.getStartLocation(move, currentColour);
                chessRound.movePiece(move, currentColour);
                chessPanel.updateBoard(move, currentColour, startLocation);
                turnCounter++;

                instructionLabel.setText("Insert move (" + (nextColour == PieceColour.WHITE ? "White's turn" : "Black's turn") + "):");

                int evaluation = chessRound.computeAdvantage();

                int whitePercentage = (int) Math.round((evaluation + 500.0) / 2.0);
                evaluationBar.setWhitePercentage(whitePercentage);

                if (chessRound.isCheckmate(nextColour)) {
                    String winner = (turnCounter % 2 == 0) ? "Black" : "White";
                    JOptionPane.showMessageDialog(frame, winner + " won by checkmate!", "Game Over", JOptionPane.INFORMATION_MESSAGE);

                    turnCounter = 0;
                    chessRound.resetBoard();
                    chessPanel.drawBoard();
                    moveInput.setText("");
                    error.setText("");
                    instructionLabel.setText("Insert move (White's turn):");
                    evaluationBar.setWhitePercentage(250); // Reset bar to neutral
                }

                moveInput.setText("");
                error.setText("");

            } catch (ValidatorException | InputException ex) {
                throw new RuntimeException(ex);
            }
        });

        resetButton.addActionListener(e -> {
            try {
                chessRound.resetBoard();
            } catch (InputException ex) {
                throw new RuntimeException(ex);
            }
            chessPanel.drawBoard();
            turnCounter = 0;
            instructionLabel.setText("Insert move (White's turn):");
            evaluationBar.setWhitePercentage(250);
            moveInput.setText("");
            error.setText("");
        });

        frame.setLayout(new BorderLayout());
        frame.add(chessPanel, BorderLayout.WEST);
        frame.add(rightPanel, BorderLayout.CENTER);

        frame.setVisible(true);
    }
}
