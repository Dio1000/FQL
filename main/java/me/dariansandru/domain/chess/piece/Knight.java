package me.dariansandru.domain.chess.piece;

import me.dariansandru.round.ChessRound;
import me.dariansandru.io.exception.InputException;
import me.dariansandru.utilities.ChessUtils;

import java.util.Objects;

public class Knight implements Piece {

    private final PieceColour colour;
    private String display = "N";
    private final int points = 3;

    public Knight(PieceColour colour) throws InputException {
        this.colour = colour;
        setDisplay();
    }

    @Override
    public String getName() {
        return "Knight";
    }

    @Override
    public String getRepresentation() {
        return "N";
    }

    @Override
    public PieceColour getColour() {
        return colour;
    }

    @Override
    public boolean isLegalMove(ChessRound chessRound, int currentRow, int currentCol, String move) {
        Piece[][] pieces = chessRound.getPieces();

        int newRow = ChessUtils.getColRow(move).getValue2();
        int newCol = ChessUtils.getColRow(move).getValue1();

        // Case 0 - Illegal stay move / Illegal friend position
        if (currentRow == newRow && currentCol == newCol) return false;
        if (pieces[newRow][newCol].getColour() == pieces[currentRow][currentCol].getColour()) return false;

        // Case 1 - Right

        // Case 1.1 - Up right
        if (currentRow + 2 == newRow && currentCol + 1 == newCol) return true;

        // Case 1.2 - Right up
        if (currentRow + 1 == newRow && currentCol + 2 == newCol) return true;

        // Case 1.3 - Right down
        if (currentRow - 1 == newRow && currentCol + 2 == newCol) return true;

        // Case 1.4 - Down right
        if (currentRow - 2 == newRow && currentCol + 1 == newCol) return true;

        // Case 2 - Left

        // Case 2.1 - Up left
        if (currentRow + 2 == newRow && currentCol - 1 == newCol) return true;

        // Case 2.2 - Left up
        if (currentRow + 1 == newRow && currentCol - 2 == newCol) return true;

        // Case 2.3 - Left down
        if (currentRow - 1 == newRow && currentCol - 2 == newCol) return true;

        // Case 2.4 - Down left
        return currentRow - 2 == newRow && currentCol - 1 == newCol;

    }

    @Override
    public String getDisplay() {
        return display;
    }

    @Override
    public void setDisplay() throws InputException {
        String display = ChessUtils.getPieceDisplay(this.getName(), this.getColour());

        if (display.isEmpty() || Objects.equals(display, "Error")) return;
        this.display = ChessUtils.getPieceDisplay(this.getName(), this.getColour());
    }

    @Override
    public int getPoints() {
        return points;
    }

    @Override
    public int compareTo(Piece piece) {
        return Integer.compare(this.points, piece.getPoints());
    }
}
