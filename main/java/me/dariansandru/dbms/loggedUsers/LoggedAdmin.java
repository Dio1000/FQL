package me.dariansandru.dbms.loggedUsers;

import me.dariansandru.domain.Admin;

public class LoggedAdmin {

    private static Admin loggedAdmin;

    private LoggedAdmin() {}

    public static Admin getLoggedAdmin() {
        return loggedAdmin;
    }

    public static void setLoggedAdmin(Admin admin) {
        LoggedAdmin.loggedAdmin = admin;
    }

    public static void removeLoggedAdmin() {
        loggedAdmin = null;
    }
}
