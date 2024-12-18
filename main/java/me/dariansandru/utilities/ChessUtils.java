package me.dariansandru.utilities;

import me.dariansandru.domain.Player;
import me.dariansandru.round.ChessRound;
import me.dariansandru.domain.chess.piece.Piece;
import me.dariansandru.domain.chess.piece.PieceColour;
import me.dariansandru.domain.chess.piece.*;
import me.dariansandru.io.InputDevice;
import me.dariansandru.io.OutputDevice;
import me.dariansandru.io.exception.InputException;

import java.io.File;
import java.util.*;

/**
 * Using this abstract class allows the user to use
 * a set of different functions related to the Chess game.
 */
public abstract class ChessUtils {

    public static InputDevice inputDevice = new InputDevice();
    public static OutputDevice outputDevice = new OutputDevice();

    /**
     * Gets the number of a certain character in alphabetic order.
     * @param chr char to get the number for
     * @return Integer representing the obtained number.
     */
    public static int getNumber(char chr){
        return chr - 'a';
    }

    /**
     * Gets the letter of a certain integer in alphabetic order.
     * @param num Integer to get the letter for.
     * @return String representing the obtained letter.
     */
    public static String getLetter(int num){
        return String.valueOf((char) ('a' + num));
    }

    /**
     * Checks that a piece representation that can be empty is valid in the game of Chess.
     * @param piece Piece representation (char) that is validated.
     * @return true if the piece is valid, false otherwise.
     */
    public static boolean isValidPiece(char piece){
        char[] validPieces = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'P', 'K', 'Q', 'R', 'B', 'N', ' '};

        for (char p : validPieces){
            if (Objects.equals(p, piece)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Checks that a piece representation that can be empty is valid in the game of Chess.
     * @param piece Piece representation (String) that is validated.
     * @return true if the piece is valid, false otherwise.
     */
    public static boolean isValidPiece(String piece){
        char[] validPieces = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'P', 'K', 'Q', 'R', 'B', 'N', ' '};
        char _piece = piece.charAt(0);

        for (char p : validPieces){
            if (Objects.equals(p, _piece)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Checks that a piece representation that cannot be empty is valid in the game of Chess.
     * @param piece Piece representation that is validated.
     * @return true if the piece is valid, false otherwise.
     */
    public static boolean isValidNonEmptyPiece(String piece){
        char[] validPieces = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'K', 'Q', 'R', 'B', 'N', 'P'};
        char _piece = piece.charAt(0);

        for (char p : validPieces){
            if (Objects.equals(p, _piece)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Used to convert chars row and col to valid integers.
     * @param col Column that is converted.
     * @param row Row that is converted.
     * @return Pair containing the valid input representation.
     */
    public static Pair<Integer, Integer> charsToMovePair(char col, char row){
        return new Pair<>(col - 'a', row - '1');
    }

    /**
     * Used to find the column and the row from a move.
     * @param move Move that you get the column and row for.
     * @return Pair containing the column and row.
     */
    public static Pair<Integer, Integer> getColRow(String move){
        if (move.length() == 2){
            return charsToMovePair(move.charAt(0), move.charAt(1));
        }

        else if (move.length() == 3){
            if (move.charAt(0) == 'x' || isValidPiece(move.charAt(0))){
                return charsToMovePair(move.charAt(1), move.charAt(2));
            }

            if (move.charAt(2) == '+' || move.charAt(2) == '#'){
                return charsToMovePair(move.charAt(0), move.charAt(1));
            }
        }

        else if (move.length() == 4){
            if (move.charAt(1) == 'x'){
                return charsToMovePair(move.charAt(2), move.charAt(3));
            }

            if (move.charAt(3) == '+' || move.charAt(3) == '#'){
                return charsToMovePair(move.charAt(1), move.charAt(2));
            }
        }

        else if (move.length() == 5){

        }

        return new Pair<>(-1, -1);
    }

    /**
     * Used to create a piece object.
     * @param representation The representation of the piece that is created.
     * @param pieceColour The colour of the piece that is created.
     * @return The piece object.
     * @throws InputException Thrown when input validation fails.
     */
    public static Piece getPiece(String representation, PieceColour pieceColour) throws InputException {
        return switch (representation) {
            case "", "P" -> new Pawn(pieceColour);
            case "B" -> new Bishop(pieceColour);
            case "K" -> new King(pieceColour);
            case "N" -> new Knight(pieceColour);
            case "Q" -> new Queen(pieceColour);
            case "R" -> new Rook(pieceColour);
            default -> new EmptyPiece();
        };
    }

    /**
     * Gets the display of a piece that was set in the chessPieceRepresentation.txt file.
     * @param piece Piece that you get the display for.
     * @param colour Colour of the piece.
     * @return String representing the display.
     * @throws InputException Thrown when the input validation fails.
     */
    public static String getPieceDisplay(String piece, PieceColour colour) throws InputException {
        String readFile = "files/chessPieceRepresentation.txt";
        List<String> list;

        if (new File(readFile).exists()){
            list = inputDevice.readFile(readFile);
        }
        else{
            return "Error";
        }

        for (String line : list){
            if (line.isEmpty()) continue;
            if (line.split(":").length != 2) continue;

            String details = line.split(":")[0].strip();
            String display = line.split(":")[1].strip();

            String pieceName = "EmptyPiece";
            String pieceColour = "None";

            if (!Objects.equals(details, "EmptyPiece")){
                pieceName = details.split("\\.")[1].strip();
                pieceColour = details.split("\\.")[0].strip();
            }

            if (Objects.equals(piece, "None") && Objects.equals(pieceColour, "None")) return display;
            if (Objects.equals(piece, pieceName) && Objects.equals(pieceColour, colour.toString())) return display;
        }

        return "Error";
    }

    /**
     * Used to find the Player with the highest Win / Loss ratio.
     * @param playerSet Set of the players.
     * @return Player that was found.
     */
    public static Player getHighestRatedPlayer(Set<Player> playerSet){
        Player highestRatedPlayer = null;

        for (Player player : playerSet){
            if (highestRatedPlayer == null){
                highestRatedPlayer = player;
            }
            else if (player.compareTo(highestRatedPlayer) > 0){
                highestRatedPlayer = player;
            }
        }

        return highestRatedPlayer;
    }

    /**
     * Used to find the Player with the lowest Win / Loss ratio.
     * @param playerSet Set of the players.
     * @return Player that was found.
     */
    public static Player getLowestRatedPlayer(Set<Player> playerSet){
        Player lowestRatedPlayer = null;

        for (Player player : playerSet){
            if (lowestRatedPlayer == null){
                lowestRatedPlayer = player;
            }
            else if (player.compareTo(lowestRatedPlayer) < 0){
                lowestRatedPlayer = player;
            }
        }

        return lowestRatedPlayer;
    }

    /**
     * Used to sort the players in-place by their Win / Loss ratio.
     * @param playerList List of the players.
     */
    public static void getPlayerRanking(List<Player> playerList){
        int length = playerList.size();

        for (int i = 0 ; i < length - 1 ; i++){
            int min_index = i;

            for (int j = i + 1; j < length ; j++){
                if (playerList.get(j).compareTo(playerList.get(min_index)) < 0) min_index = j;
            }

            Player swap = playerList.get(i);
            playerList.set(i, playerList.get(min_index));
            playerList.set(min_index, swap);
        }
    }

    /**
     * Gets the material points of a player.
     * @param chessRound ChessRound the players are using.
     * @param colour Colour of the pieces the player is using.
     * @return Int representing the material points.
     */
    public static int getColourMaterial(ChessRound chessRound, PieceColour colour){
        Piece[][] pieces = chessRound.getPieces();
        int totalPoints = 0;

        for (int row = 0 ; row < 8 ; row++){
            for (int col = 0 ; col < 8 ; col++){
                if (!Objects.equals(pieces[row][col].getName(), "King") &&
                    pieces[row][col].getColour() == colour)
                    totalPoints += pieces[row][col].getPoints();
            }
        }

        return totalPoints;
    }

    /**
     * Used to get the material advantage of a player.
     * @param chessRound ChessRound the players are using.
     * @param colour Colour of the pieces the player is using.
     * @return Int representing the material advantage.
     */
    public static int getColourMaterialAdvantage(ChessRound chessRound, PieceColour colour){
        int whitePiecePlayerPoints = getColourMaterial(chessRound, PieceColour.WHITE);
        int blackPiecePlayerPoints = getColourMaterial(chessRound, PieceColour.BLACK);

        if (colour == PieceColour.WHITE){
            return whitePiecePlayerPoints - blackPiecePlayerPoints;
        }
        else if (colour == PieceColour.BLACK){
            return blackPiecePlayerPoints - whitePiecePlayerPoints;
        }
        else{
            throw new IllegalArgumentException(colour.toString() + " is not a valid colour!");
        }
    }

    public static Pair<Integer, Integer> getKingLocation(ChessRound chessRound, PieceColour colour){
        Piece[][] pieces = chessRound.getPieces();

        for (int row = 0 ; row < 8 ; row++){
            for (int col = 0 ; col < 8 ; col++){
                if (Objects.equals(pieces[row][col].getName(), "King") &&
                    pieces[row][col].getColour() == colour) return new Pair<>(row, col);
            }
        }

        return new Pair<>(-1, -1);
    }

}
