# CSEN 177 Assignment 1
Jack Landers, jlanders@scu.edu

# Results
In what order were the integers printed?

    Even though there were multiple threads consuming from the buffer, because the consumer function
    was a part of the cicular buffer class, the position in the buffer could be kept static across all 
    of the threads. This way the values were being read from the buffer in sequence. However, the lock
    was only used to stop the buffer from going out of bounds and as a result changing the size of the
    buffer and the number of consumers would affect how many elements were produced and consumed at 
    a time.

# Answer the following:
A. How many of each integer should you see printed?

    Because the values continued to increment as they were produced, and the threads were synchronized
    so that they didn't consume the same buffer element twice, each integer would only appear once.
    

B. In what order should you expect to see them printed? Why?

    With multi-threaded consumers you might expect to see the order of consumed elements to get
    muddled. But because in Java, we can share the position in the buffer across multiple threads,
    even while they are locked, the values can be printed in sequence.


C. Did your results differ from your answers in (1) and (2)? Why or why not?

    This was not the case before we introduced blocking in part 2. In part 1, I had many errors
    where the consumers would access the same element or would not consume from the buffer in sequence.