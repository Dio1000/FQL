package me.dariansandru.domain.chess.piece;

import me.dariansandru.round.ChessRound;
import me.dariansandru.io.exception.InputException;
import me.dariansandru.utilities.ChessUtils;

import java.util.Objects;

public class Queen implements Piece {

    private final PieceColour colour;
    private String display = "Q";
    private final int points = 9;

    public Queen(PieceColour colour) throws InputException {
        this.colour = colour;
        setDisplay();
    }

    @Override
    public String getName() {
        return "Queen";
    }

    @Override
    public String getRepresentation() {
        return "Q";
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

        // Case 1 - Moves diagonally
        boolean diagonalMove = Math.abs(newRow - currentRow) == Math.abs(newCol - currentCol);

        // Case 2 - Moves on the row or column
        boolean rowColMove = (currentRow == newRow || currentCol == newCol);

        return (diagonalMove || rowColMove);
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
