import java.util.Random;

class Square extends Thread {
    int x;

    Square(int n) {
        x = n;
    }

    public void run() {
        int sqr = x * x;
        System.out.println("Square of " + x + " = " + sqr);
    }
}

class Cube extends Thread {
    int x;

    Cube(int n) {
        x = n;
    }

    public void run() {
        int cub = x * x * x;
        System.out.println("Cube of " + x + " = " + cub);
    }
}

class RandomNumber extends Thread {
    public void run() {
        Random random = new Random();
        while (true) {
            int randomInteger = random.nextInt(100);
            System.out.println("\nRandom Integer generated : " +
                    randomInteger);
            if (randomInteger % 2 == 0) {
                Square square = new Square(randomInteger);
                square.start();
            } else {
                Cube cube = new Cube(randomInteger);
                cube.start();
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException ex) {
                System.out.println(ex);
            }
        }
    }
}

class program10 {
    public static void main(String args[]) {
        RandomNumber n = new RandomNumber();
        n.start();
    }
}