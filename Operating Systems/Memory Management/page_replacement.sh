#!/bin/bash
make;
echo "---------FIFO----------"
cat testInput.txt | ./fifo 10
echo "---------END FIFO----------"
echo
echo "---------LRU----------"
cat testInput.txt | ./lru 10
echo "---------END LRU----------"
echo
echo "---------SECOND CHANCE----------"
cat testInput.txt | ./sec_chance 10
echo "---------END SECOND CHANCE----------"

echo "FIFO 10K Test with cache size = 10, 50, 100, 250, 500"
cat accessesForReport.txt | ./FIFO 10 | wc -l
cat accessesForReport.txt | ./FIFO 50 | wc -l
cat accessesForReport.txt | ./FIFO 100 | wc -l
cat accessesForReport.txt | ./FIFO 250 | wc -l
cat accessesForReport.txt | ./FIFO 500 | wc -l
echo
echo "LRU 10K Test with cache size = 10, 50, 100, 250, 500"
cat accessesForReport.txt | ./LRU 10 | wc -l
cat accessesForReport.txt | ./LRU 50 | wc -l
cat accessesForReport.txt | ./LRU 100 | wc -l
cat accessesForReport.txt | ./LRU 250 | wc -l
cat accessesForReport.txt | ./LRU 500 | wc -l
echo
echo "Second Chance 10K Test with cache size = 10, 50, 100, 250, 500"
cat accessesForReport.txt | ./SEC_CHANCE 10 | wc -l
cat accessesForReport.txt | ./SEC_CHANCE 50 | wc -l
cat accessesForReport.txt | ./SEC_CHANCE 100 | wc -l
cat accessesForReport.txt | ./SEC_CHANCE 250 | wc -l
cat accessesForReport.txt | ./SEC_CHANCE 500 | wc -l
echo
make clean;
echo
