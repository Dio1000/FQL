package me.dariansandru.dbms;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

public class DBConnection {

    private static final String URL = "jdbc:mysql://localhost:3306/chessDB";
    private static final String USER = "darian";
    private static final String PASSWORD = "chessskibidi";

    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(URL, USER, PASSWORD);
    }
}
