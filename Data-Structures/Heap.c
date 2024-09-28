void heapify(T A[1 .. n], i){

  while (i <= n){
  
    int largest = i, lc = 2*i, rc =lc + 1;
    if (lc <= n && A[lc] > A[largest]){
      largest = 1c;}
    if (rc <= n && A[rc] > A[largest]){
      largest = rc;}
    if (largest == i){
      break;}
    swap(A[i], A[largest]);
    i = largest;
    
  }
} 
void makeheap(T A[1 .. n]){
  
  for (int i = n/2; i >= 1; -- i){
    heapify(A[1 .. n], i);}
}
void heap_sort(T A[1 .. n]){
  
  makeheap(A[1 .. n]);
  for (int s = n; s > 1; -- s){
    swap(A[1], A[s]); heapify(A[1 .. s-1], 1); }
}
