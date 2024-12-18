package me.dariansandru.utilities;

/**
 * Basic Pair object used to store 2 objects.
 * @param <T1> First generic object.
 * @param <T2> Second generic object.
 */
public class Pair<T1, T2> {
    T1 value1;
    T2 value2;

    public Pair(T1 value1, T2 value2){
        this.value1 = value1;
        this.value2 = value2;
    }

    /**
     * Returns the first object.
     * @return First generic object.
     */
    public T1 getValue1() {
        return value1;
    }

    /**
     * Sets the first object.
     * @param value1 Generic object that is set as the first value.
     */
    public void setValue1(T1 value1) {
        this.value1 = value1;
    }

    /**
     * Gets the second object.
     * @return Second generic object.
     */
    public T2 getValue2() {
        return value2;
    }

    /**
     * Sets the second object.
     * @param value2 Generic object that is set as the second value.
     */
    public void setValue2(T2 value2) {
        this.value2 = value2;
    }
}
