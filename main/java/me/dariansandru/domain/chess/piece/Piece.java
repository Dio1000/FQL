package me.dariansandru.domain.chess.piece;

import me.dariansandru.round.ChessRound;
import me.dariansandru.io.exception.InputException;

public interface Piece extends Comparable<Piece> {

    String getName();

    String getRepresentation();

    PieceColour getColour();

    boolean isLegalMove(ChessRound chessRound, int currentRow, int currentCol, String move);

    String getDisplay();

    int getPoints();

    void setDisplay() throws InputException;

}
