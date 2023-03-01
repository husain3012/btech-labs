class Base {

    // Constructor of super class
    Base() {
        System.out.println(
                "Base Class Constructor Called ");
    }
}

// Sub class
class Derived extends Base {

    Derived() {

        System.out.println(
                "Derived Class Constructor Called ");
    }
}

// =====
class Constructor {

    public static void main(String[] args) {

        new Derived();
    }
}