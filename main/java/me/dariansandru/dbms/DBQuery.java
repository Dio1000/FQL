package me.dariansandru.dbms;

import me.dariansandru.domain.Admin;
import me.dariansandru.domain.Player;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class DBQuery {
    public static void fetchPlayers() {
        String querySQL = "SELECT * FROM players";

        try (Connection connection = DBConnection.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(querySQL);
             ResultSet resultSet = preparedStatement.executeQuery()) {

            while (resultSet.next()) {
                int playerId = resultSet.getInt("player_id");
                String username = resultSet.getString("username");
                String email = resultSet.getString("email");
                int rating = resultSet.getInt("rating");

                System.out.printf("Player ID: %d, Username: %s, Email: %s, Rating: %d%n",
                        playerId, username, email, rating);
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static List<String> getDataByUsername(String _username) {
        String querySQL = "SELECT * FROM players WHERE username = ?";
        List<String> resultList = new ArrayList<>();

        try (Connection connection = DBConnection.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(querySQL)) {

            preparedStatement.setString(1, _username);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    String playerId = String.valueOf(resultSet.getInt("player_id"));
                    String username = resultSet.getString("username");
                    String email = resultSet.getString("email");
                    String password = resultSet.getString("password");
                    String rating = String.valueOf(resultSet.getInt("rating"));

                    resultList.add(playerId);
                    resultList.add(username);
                    resultList.add(email);
                    resultList.add(password);
                    resultList.add(rating);
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return resultList;
    }

    public static List<String> getAdminDataByUsername(String _username) {
        String querySQL = "SELECT * FROM admins WHERE username = ?";
        List<String> resultList = new ArrayList<>();

        try (Connection connection = DBConnection.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(querySQL)) {

            preparedStatement.setString(1, _username);

            try (ResultSet resultSet = preparedStatement.executeQuery()) {
                while (resultSet.next()) {
                    String adminID = String.valueOf(resultSet.getInt("admin_id"));
                    String username = resultSet.getString("username");
                    String email = resultSet.getString("email");
                    String password = resultSet.getString("password");

                    resultList.add(adminID);
                    resultList.add(username);
                    resultList.add(email);
                    resultList.add(password);
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return resultList;
    }


    public static void setPlayerData(Player loggedPlayer, List<String> loggedPlayerData){
        loggedPlayer.setUsername(loggedPlayerData.get(1));
        loggedPlayer.setEmail(loggedPlayerData.get(2));
        loggedPlayer.setPassword(loggedPlayerData.get(3));
        loggedPlayer.setRating(Integer.parseInt(loggedPlayerData.get(4)));
    }

    public static void setAdminData(Admin loggedAdmin, List<String> loggedAdminData){
        loggedAdmin.setUsername(loggedAdminData.get(1));
        loggedAdmin.setEmail(loggedAdminData.get(2));
        loggedAdmin.setPassword(loggedAdminData.get(3));
    }

    public static List<String> getAllUsernames(){
        String querySQL = "SELECT username FROM players";
        List<String> resultList = new ArrayList<>();

        try (Connection connection = DBConnection.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(querySQL);
             ResultSet resultSet = preparedStatement.executeQuery()) {

            while (resultSet.next()) {
                resultList.add(resultSet.getString("username"));
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return resultList;
    }

    public static List<String> getAllAdminUsernames(){
        String querySQL = "SELECT username FROM admins";
        List<String> resultList = new ArrayList<>();

        try (Connection connection = DBConnection.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(querySQL);
             ResultSet resultSet = preparedStatement.executeQuery()) {

            while (resultSet.next()) {
                resultList.add(resultSet.getString("username"));
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return resultList;
    }
}
