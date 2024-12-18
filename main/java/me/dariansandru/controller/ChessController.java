package me.dariansandru.controller;

import me.dariansandru.domain.Player;
import me.dariansandru.domain.chess.piece.Piece;
import me.dariansandru.domain.chess.piece.PieceColour;
import me.dariansandru.domain.validator.exception.ValidatorException;
import me.dariansandru.round.ChessRound;
import me.dariansandru.io.exception.InputException;

import java.util.ArrayList;
import java.util.List;

/**
 * The user of this class can control the logic of a ChessRound.
 */
public class ChessController implements GameController {

    private int turn;
    private final List<String> turns;
    private final ChessRound chessRound;

    private final Player whitePiecesPlayer;
    private final Player blackPiecesPlayer;

    public ChessController(Player p1, Player p2) throws InputException {
        turns = new ArrayList<>();
        this.chessRound = new ChessRound(p1, p2);
        reset();

        whitePiecesPlayer = p1;
        blackPiecesPlayer = p2;
    }

    /**
     * Resets the current ChessRound.
     * @throws InputException Thrown when input validation fails.
     */
    @Override
    public void reset() throws InputException {
        chessRound.resetBoard();
        turn = 0;
        turns.clear();
    }

    /**
     * Used to start the logic of a ChessRound.
     * @param move Move that is passed by the GameRound.
     * @return Error string in case there is any, null otherwise.
     */
    @Override
    public String play(String move){
        PieceColour colour;

        if (turn % 2 == 0) {
            colour = PieceColour.WHITE;
        }
        else {
            colour = PieceColour.BLACK;
        }

        String errorMaybe = chessRound.handleMove(move, colour);
        if (errorMaybe == null) turn++;
        return errorMaybe;
    }

    /**
     * Used to access the moves of the current ChessRound.
     * @return List of strings containing the moves.
     */
    public List<String> getTurns(){
        return this.turns;
    }

    /**
     * Used to check the current turn in the current ChessRound.
     * @return Int representing the current move that is played.
     */
    public int getTurnCount(){
        return turn;
    }

    /**
     * Used to access the last move that was played.
     * @return String representing the last move.
     */
    public String getLastTurn(){
        return this.turns.get(turn - 1);
    }

    /**
     * Used to get the piece on a specific square.
     * @param row Row of the square the piece is on.
     * @param col Column of the square the piece is on.
     * @return Piece object on the specified square.
     */
    public Piece getPiece(int row, int col){
        return chessRound.getPiece(row, col);
    }

    /**
     * Adds a move to the turns list.
     * @param move Move that is added.
     */
    public void addTurn(String move){
        turns.add(move);
    }

    /**
     * Checks the state of the game.
     * @return True if the game has ended, false otherwise.
     * @throws ValidatorException Thrown when a move is not valid.
     * @throws InputException Thrown when input validation fails.
     */
    public boolean isGameFinished() throws ValidatorException, InputException {
        return chessRound.isCheckmate() || chessRound.isStalemate();
    }

    /**
     * Returns the Player with the white pieces.
     * @return White pieces player.
     */
    public Player getWhitePiecesPlayer(){
        return whitePiecesPlayer;
    }

    /**
     * Returns the Player with the black pieces.
     * @return Black pieces player.
     */
    public Player getBlackPiecesPlayer(){
        return blackPiecesPlayer;
    }

    /**
     * Gets the currently played ChessRound.
     * @return ChessRound that is being played.
     */
    public ChessRound getChessRound(){
        return chessRound;
    }

}
