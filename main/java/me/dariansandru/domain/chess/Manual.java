package me.dariansandru.domain.chess;

import me.dariansandru.io.OutputDevice;
public abstract class Manual {

    public static void showRules(OutputDevice outputDevice){
        outputDevice.writeLine("In order to move a piece, please write the move in algebraic notation.");
        outputDevice.writeLine("Here are some things to remember:");
        outputDevice.writeLine();

        outputDevice.writeLine("1. Piece notations:");
        outputDevice.writeLine();
        outputDevice.writeLine("Piece    Code");
        outputDevice.writeLine("King     K");
        outputDevice.writeLine("Queen    Q");
        outputDevice.writeLine("Rook     R");
        outputDevice.writeLine("Bishop   B");
        outputDevice.writeLine("Knight   N");
        outputDevice.writeLine("Pawn     No letter");
        outputDevice.writeLine();

        outputDevice.writeLine("2. Square notations:");
        outputDevice.writeLine();
        outputDevice.writeLine("The rows are noted from 1 through 8");
        outputDevice.writeLine("The columns are noted from A through H");
        outputDevice.writeLine();

        outputDevice.writeLine("3. Move notation:");
        outputDevice.writeLine("In order to write a valid move, you need to");
        outputDevice.writeLine("concatenate the piece notation with the square notation");
        outputDevice.writeLine();
        outputDevice.writeLine("Examples: ");
        outputDevice.writeLine("e4 - Pawn to E4, no other pawn can go to E4");
        outputDevice.writeLine("so this is not ambiguous");
        outputDevice.writeLine("Nf3 - Knight to F3, no other knight can go to F3");
        outputDevice.writeLine("so this is not ambiguous");
        outputDevice.writeLine("Qg8 - Queen to G8, no other Queen can go to G8");
        outputDevice.writeLine("so this is not ambiguous");
        outputDevice.writeLine();

        outputDevice.writeLine("4. Optional Notations (You do not need to write these):");
        outputDevice.writeLine();
        outputDevice.writeLine("4.1 If the piece take another piece from that move, you can");
        outputDevice.writeLine("write it in the form 'Piece Notation' x 'Square' ");
        outputDevice.writeLine("Examples: ");
        outputDevice.writeLine("Bxc6, Bishop takes the piece on C6");
        outputDevice.writeLine("Qxh2, Queen takes the piece from H2");
        outputDevice.writeLine();
        outputDevice.writeLine("4.2 If the piece you move puts the king in check, you can");
        outputDevice.writeLine("write it in the form 'Piece Notation' 'Square' +");
        outputDevice.writeLine("Examples: ");
        outputDevice.writeLine("Nf7+, Knight to F7 and check the king");
        outputDevice.writeLine("h7+, Pawn to H6 and check the king");
        outputDevice.writeLine("Qxh7+, Queen takes the piece from H7 and checks the king");
        outputDevice.writeLine();
        outputDevice.writeLine("4.3 If the piece you move checkmates the king, you can");
        outputDevice.writeLine("write it in the form 'Piece Notation' 'Square' #");
        outputDevice.writeLine("Examples: ");
        outputDevice.writeLine("Qb8#, Queen to B8 checkmate");
        outputDevice.writeLine("Ra2#, Rook to A2 checkmate");
        outputDevice.writeLine("Nxa8#, Knight takes the piece from A8 checkmate");
        outputDevice.writeLine();

        outputDevice.writeLine("5. Special moves:");
        outputDevice.writeLine();
        outputDevice.writeLine("5.1 En passant");
        outputDevice.writeLine("If a pawn moves 2 squares ahead, and the square it reaches");
        outputDevice.writeLine("is on the same rank (row) and an adjacent file (column), then");
        outputDevice.writeLine("you can capture it using en passant. This is noted by appending");
        outputDevice.writeLine("e.p to the move.");
        outputDevice.writeLine("Example:");
        outputDevice.writeLine("bxa3 e.p, The pawn on the B file takes Pawn on A3 en passant.");
        outputDevice.writeLine();
        outputDevice.writeLine("5.2 Castling");
        outputDevice.writeLine("If the king and the Queen-side Rook (the Rook on the part of the King");
        outputDevice.writeLine("where the Queen is) have not moved during the game, and");
        outputDevice.writeLine("there are no pieces between the Rook and the King, you can do");
        outputDevice.writeLine("a move called Queen-side Castle, noted as O-O-O (also known as");
        outputDevice.writeLine("Long-side castle)");
        outputDevice.writeLine("If the king and the King-side Rook (the Rook closest to the King");
        outputDevice.writeLine("have not moved during the game, and there are no pieces");
        outputDevice.writeLine("between the Rook and the King, you can do a move called");
        outputDevice.writeLine("King-Side Castle, noted as O-O (also known as Short-side castle)");
        outputDevice.writeLine("What these moves entail is that the Rook moves 2 squares in the");
        outputDevice.writeLine("direction of the King, and the King jumps over the Rook, next to it.");
        outputDevice.writeLine();

        outputDevice.writeLine("Keep in mind, for this application you only need to write the piece");
        outputDevice.writeLine("and the square it moves to (Example: Qe4). If there is ambiguity (More than one");
        outputDevice.writeLine("piece of that type can move to that square), you will be asked to provide the correct piece.");
    }

}
