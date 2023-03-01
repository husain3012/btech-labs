abstract class Shape {
    public int x, y;

    abstract void printArea();
}

class Rectangle extends Shape {

    public void printArea() {
        System.out.println("Area of Rectangle: " + (x * y));
    }

    public Rectangle(int length, int breadth) {
        this.x = length;
        this.y = breadth;
    }
}

class Circle extends Shape {
    public Circle(int radius) {
        this.x = radius;
        this.y = radius;
    }

    public void printArea() {
        System.out.println("Area of Circle: " + (Math.PI * x * x));
    }

}

class Triangle extends Shape {
    public Triangle(int base, int height) {
        this.x = base;
        this.y = height;
    }

    public void printArea() {
        System.out.println("Area of Triangle: " + (0.5 * x * y));
    }
}

class program9 {
    static Thread t = Thread.currentThread();

    public static void main(String[] args) {
        System.out.println(t);

        Rectangle r = new Rectangle(10, 20);
        r.printArea();

        Circle c = new Circle(10);

        c.printArea();

        Triangle t = new Triangle(10, 20);

        t.printArea();
    }
}