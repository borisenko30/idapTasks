//---------------------------------------------------------------------------
#include <iostream>
#include <conio>

//---------------------------------------------------------------------------

using namespace std;
const int MAX_LENGTH = 1000;// max array length in Stack structure;

/*
** Stack structure consists of a 'next' pointer(*next) and an array of integers.
** MyStack contains whole structure size data and a 'head' pointer(*chunk).
*/
class MyStack {
private:
  int size;
  int stackCount;
  class Stack {
    friend class MyStack;
    Stack *next;
    int arr[MAX_LENGTH];
  } *chunk;
public:
  MyStack() {
    size = 0;
    stackCount = 0;
    chunk = new Stack();
    chunk->next = NULL;
  }
  int getSize() {
    return size + stackCount * MAX_LENGTH;
  }
  void push(int x) {
    if (size < MAX_LENGTH) {
      chunk->arr[size++] = x;
    } else {
      Stack *newChunk = new Stack();
      stackCount++;
      size = 0;
      newChunk->arr[size++] = x;
      newChunk->next = chunk;
      chunk = newChunk;
    }
  }
  int pop() {
    if (size > 1) {
      chunk->arr[--size] = 0;
      return chunk->arr[size];
    } else if (size == 1 && stackCount > 0) {
      size = MAX_LENGTH;
      stackCount--;
      chunk->arr[0] = 0;
      int res = chunk->arr[0];
      Stack *temp = chunk->next;
      delete chunk;
      chunk = temp;
      return res;
    } else {
      int res = chunk->arr[--size];
      size = 0;
      chunk->arr[size] = 0;
      return res;
    }
  }
};

int main(int argc, char* argv[])
{
  MyStack *s = new MyStack();

  cout<<"Stack size: "<<s->getSize()<<endl;
  for(int i = 0; i < 10; i++) {
    s->push(i);
  }
  cout<<"10 elements added"<<endl;

  cout<<"Stack size: "<<s->getSize()<<endl;
  for(int i = 0; i < 6; i++) {
    s->pop();
  }
  cout<<"6 elements deleted"<<endl;

  cout<<"Stack size: "<<s->getSize()<<endl;
  for(int i = 0; i < 5000000; i++) {
    s->push(i);
  }
  cout<<"5 million elements added"<<endl;

  cout<<"Stack size: "<<s->getSize()<<endl;
  for(int i = 0; i < 4300000; i++) {
    s->pop();
  }
  cout<<"4.3 million elements deleted"<<endl;
  cout<<"Stack size: "<<s->getSize()<<endl;

  delete s;
  getch();
  return 0;
}
