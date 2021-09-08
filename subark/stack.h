#ifndef _STACK_H_
#define _STACK_H_
template <class Type>
class Stack {
public:

  class Node { // class for stack node
  public:
    Type Data;
    Node * Link;
    Node(Type data = 0, Node * link = 0): Data(data), Link(link) { }
    ~Node(void) { }
  } * Top;

  Stack(void): Top(0) { }// constructor
  ~Stack(void) {
    Type Temp;
    while (Top) Delete(Temp);
  }

  void Add(const Type Data) {
    Node * Temp = new Node(Data, Top);// attach node
    Top = Temp;// update top
  }

  Type * Delete(Type & Data) {
    if (Top == 0)
      return 0;// return null pointer constant
    Node * Temp = Top;

    Data = Top->Data;// get data field of top node
    Top = Top->Link;// remove top node
    delete Temp;// free the node
    return & Data;// return pointer to data
  }

  void Delete() {
	if (Top == 0)
      return;// return null pointer constant
    Node * Temp = Top;

    Top = Top->Link;// remove top node
    delete Temp;// free the node
	return;
  }

};

#endif
