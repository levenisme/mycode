#include "node.h"

Node * buildTree(uint64_t * counts) {
  priority_queue_t pq;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  Node * top1 = NULL;
  Node * top2 = NULL;
  while (pq.size() > 1) {
    top1 = pq.top();
    pq.pop();
    top2 = pq.top();
    pq.pop();
    pq.push(new Node(top1, top2));
  }
  return pq.top();

  //WRITE ME!
}
