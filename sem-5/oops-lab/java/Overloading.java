class Operation {
    public static int add(int a, int b) {
        return a + b;
    }

    public static String add(String a, String b) {
        return a + b;
    }
}

public class Overloading {
    public static void main(String[] args) {
        System.out.println(Operation.add(1, 2));
        System.out.println(Operation.add("Hello", "World"));
    }
}
