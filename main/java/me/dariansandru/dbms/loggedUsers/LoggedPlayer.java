package me.dariansandru.dbms.loggedUsers;

import me.dariansandru.domain.Player;

public class LoggedPlayer {

    private static Player loggedPlayer;

    private LoggedPlayer() {}

    public static Player getLoggedPlayer() {
        return loggedPlayer;
    }

    public static void setLoggedPlayer(Player player) {
        loggedPlayer = player;
    }

    public static void resetLoggedPlayer() {
        loggedPlayer = null;
    }
}
