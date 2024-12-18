package me.dariansandru.domain.chess.piece;

public enum PieceColour {
    WHITE, BLACK, NONE;

    public String toString(){
        return switch (this) {
            case WHITE -> "WHITE";
            case BLACK -> "BLACK";
            default -> "NONE";
        };
    }
}
