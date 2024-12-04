class CircularBuffer {
    private final int[] buffer;
    private int pos = 0;
    private int count = 0;
    private final Object lock = new Object();

    public CircularBuffer(int size) {
        buffer = new int[size];
    }

    public void produce(int value) throws InterruptedException {
        synchronized (lock) {
            while (count == buffer.length) { // Buffer is full
                lock.wait();
            }
            buffer[(pos + count) % buffer.length] = value;
            count++;
            System.out.println("Produced: " + value);
            lock.notifyAll(); // Signal not full
        }
    }

    public void consume() throws InterruptedException {
        synchronized (lock) {
            while (count == 0) { // Buffer is empty
                lock.wait();
            }
            int value = buffer[pos];
            pos = (pos + 1) % buffer.length;
            count--;
            System.out.println("Consumed: " + value);
            lock.notifyAll(); // Signal not empty
        }
    }
}

class Producer implements Runnable {       // Producer Entry point function
    private final CircularBuffer buffer;

    public Producer(CircularBuffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        int value = 0;
        try {
            while (true) {
                buffer.produce(value++);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

class Consumer implements Runnable {    // Consumer Entry point function
    private final CircularBuffer buffer;

    public Consumer(CircularBuffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        try {
            while (true) {
                buffer.consume();
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

public class ProducerConsumer {
    public static void main(String[] args) {

        int size = 25;
        int numConsumers;
        numConsumers = Integer.parseInt(args[0]);
        CircularBuffer buffer = new CircularBuffer(size);

        Thread producerThread = new Thread(new Producer(buffer));
        producerThread.start();


        Thread[] consumerThreads = new Thread[numConsumers];
        for (int i = 0; i < numConsumers; i++) {
            consumerThreads[i] = new Thread(new Consumer(buffer));
            consumerThreads[i].start();
        }

        try {
            producerThread.join();
            for (Thread consumerThread : consumerThreads) {
                consumerThread.join();
            }
        } catch (InterruptedException e) {
            System.out.println("Thread Exception: "+ e.getMessage());
        }
    }
}
