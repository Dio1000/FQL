package me.dariansandru.domain;

public class Player implements Comparable<Player> {

    private String username;
    private String email;
    private String password;

    private int rating;
    private int wins;
    private int losses;
    private float winLossRatio;

    public Player(){
        setWinLossRatio();
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public int getRating() {
        return rating;
    }

    public void setRating(int rating) {
        this.rating = rating;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setWinLossRatio(float winLossRatio) {
        this.winLossRatio = winLossRatio;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public int getWins() {
        return wins;
    }

    public void setWins(int wins) {
        this.wins = wins;
    }

    public int getLosses() {
        return losses;
    }

    public void setLosses(int losses) {
        this.losses = losses;
    }

    public float getWinLossRatio() {
        return winLossRatio;
    }

    public void setWinLossRatio() {
        if (this.wins + this.losses == 0) this.winLossRatio = 0;
        else this.winLossRatio = (float) ((100 * wins) / (wins + losses));
    }

    @Override
    public int compareTo(Player other) {
        if (this.winLossRatio != other.winLossRatio)
            return Float.compare(this.winLossRatio, other.winLossRatio);
        else {
            return Integer.compare(this.wins, other.wins);
        }
    }
}
