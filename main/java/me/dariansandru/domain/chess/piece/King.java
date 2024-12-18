package me.dariansandru.domain.chess.piece;

import me.dariansandru.round.ChessRound;
import me.dariansandru.io.exception.InputException;
import me.dariansandru.utilities.ChessUtils;

import java.util.Objects;

public class King implements Piece {

    private final PieceColour colour;
    private String display = "K";
    private final int points = 1000;

    public King(PieceColour colour) throws InputException {
        this.colour = colour;
        setDisplay();
    }

    @Override
    public String getName() {
        return "King";
    }

    @Override
    public String getRepresentation() {
        return "K";
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

        // Case 1 - Move one position
        return (Math.abs(currentCol - newCol) <= 1 && Math.abs(currentRow - newRow) <= 1);
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
