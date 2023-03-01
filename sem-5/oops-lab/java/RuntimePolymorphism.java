class Shape {
    public void draw() {
        System.out.println("✍️\tDraws a shape");
    }

    public void erase() {
        System.out.println("✂️\tDeletes a shape");
    }
}

class Circle extends Shape {
    @Override
    public void draw() {
        System.out.println("🟢\tDrawing circle");
    }

    @Override
    public void erase() {
        System.out.println("🔴\tErasing circle");
    }
}

class Square extends Shape {
    @Override
    public void draw() {
        System.out.println("🟩\tDrawing square");
    }

    @Override
    public void erase() {
        System.out.println("🟥\tErasing square");
    }
}

public class RuntimePolymorphism {

    public static void main(String[] args) {
        Shape c = new Circle();
        Shape s = new Square();
        Shape sh = new Shape();
        System.out.println("==============Circle==============");
        c.draw();
        c.erase();


        System.out.println("==============Square==============");
        s.draw();
        s.erase();
        System.out.println("==============Shape==============");
        sh.draw();
        sh.erase();

    }

}
