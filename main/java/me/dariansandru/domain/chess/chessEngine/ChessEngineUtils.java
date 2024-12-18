package me.dariansandru.domain.chess.chessEngine;

import me.dariansandru.domain.chess.piece.Piece;
import me.dariansandru.domain.chess.piece.PieceColour;
import me.dariansandru.domain.validator.exception.ValidatorException;
import me.dariansandru.io.exception.InputException;
import me.dariansandru.round.ChessRound;
import me.dariansandru.utilities.ChessUtils;
import me.dariansandru.utilities.Pair;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class ChessEngineUtils {
    private static Piece[][] pieces;
    private static ChessRound chessRound;

    public void setChessRound(ChessRound chessRound) {
        ChessEngineUtils.chessRound = chessRound;
        pieces = chessRound.getPieces();
    }

    public List<Pair<Integer, Integer>> getPossibleCaptures(Piece piece, int row, int col) {
        List<Pair<Integer, Integer>> captures = new ArrayList<>();

        for (int newRow = 0; newRow < 8; newRow++) {
            for (int newCol = 0; newCol < 8; newCol++) {
                if (Objects.equals(pieces[newRow][newCol].getName(), "None")) continue;

                String move = piece.getRepresentation() + ChessUtils.getLetter(newCol) + (newRow + 1);
                if (piece.isLegalMove(chessRound, row, col, move)) captures.add(new Pair<>(newRow, newCol));
            }
        }

        return captures;
    }

    public int numberOfPossibleMoves(Piece piece, int row, int col) {
        int totalMoves = 0;

        for (int newRow = 0; newRow < 8; newRow++) {
            for (int newCol = 0; newCol < 8; newCol++) {
                if (newRow == row && newCol == col) continue;

                String move = piece.getRepresentation() + ChessUtils.getLetter(newCol) + (newRow + 1);
                if (piece.isLegalMove(chessRound, row, col, move)) {
                    totalMoves++;
                }
            }
        }

        return totalMoves;
    }


    public int numberOfPossibleCaptures(Piece piece, int row, int col) {
        int total = 0;

        for (int newRow = 0; newRow < 8; newRow++) {
            for (int newCol = 0; newCol < 8; newCol++) {
                if (Objects.equals(pieces[newRow][newCol].getName(), "None")) continue;

                String move = piece.getRepresentation() + ChessUtils.getLetter(newCol) + (newRow + 1);
                if (piece.isLegalMove(chessRound, row, col, move)) total++;
            }
        }

        return total;
    }

    public Pair<Integer, Integer> getKingLocation(PieceColour colour) {
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (Objects.equals(pieces[row][col].getName(), "King") && pieces[row][col].getColour() == colour) {
                    return new Pair<>(row, col);
                }
            }
        }

        return new Pair<>(-1, -1);
    }

    public boolean isKingAttacked(PieceColour colour) throws ValidatorException, InputException {
        int kingRow = getKingLocation(colour).getValue1();
        int kingCol = getKingLocation(colour).getValue2();

        return chessRound.isKingChecked(kingRow, kingCol, colour);
    }

    public boolean isOpenFile(int col) {
        for (int row = 0; row < 8; row++) {
            if (Objects.equals(pieces[row][col].getName(), "Pawn")) return true;
        }
        return false;
    }

}
