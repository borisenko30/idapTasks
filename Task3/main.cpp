//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <conio>
using namespace std;

#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused
/* every node has references for two child nodes and one parent reference to
** provide possibility to move backwards;
*/
struct node {
  string name, text, optionLeft, optionRight, optionParent;
  struct node *left, *right, *parent;
};

string tree[1000][7];
int nodesCount;

/* split a string into an array of 5 substrings
** these substrings should be delimited by # in the base string
*/
void tokenizeLine(string line, string *arr);
// construct a tree from the array recieved from file
node *buildTree(string Node, node *parent);
// returns nodes index by a specified name
int findNode(string s);
// run the game;
void launchGame(node *Node);
// show victory message
void showVictory();
// show game over message
void showGameOver();

int main(int argc, char* argv[])
{
/* Read data from file. It should be simple csv-file.
** But due to usage of comma in our text game we'll chose another delimiter.
** Let it be '#' symbol!
** Every line in the file represents one node of binary tree.
** It's format is following:
** Nodename#NodeText#NodeState#LeftNode#RightNode
** where NodeName can be "root" or "l" for left node, "r" for right node,
** "lrr" for the right node of the right node of the left node and so on.
** Naming convention in a file can be changed. But win/lose nodes must
** have names containing "win" or "lose" string.
*/
  ifstream file("story.hsv");
  string line;

  int i = 0;
  while (getline(file, line))
  {
    tokenizeLine(line, tree[i++]);
  }
  nodesCount = i;

  node *root;
  root = buildTree("root", NULL);
// Game Intro
  cout<<"    Welcome to the worst text game ever!"<<endl;
  cout<<"Since an author has a lack of imagination and literary talent it will be a short Fallout-like story."<<endl;
  cout<<"_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_"<<endl;
  cout<<"You woke up with a headache and try to remember yesterday's events..."<<endl;
  cout<<"You were escorting a trade caravan. On your way to New-Vegas you've been attacked by \
large group of raiders. (Yes, the caravan was robbed! :) )"<<endl;
  cout<<"No weapons, no food, no water, just a bit of iguana meat in your pocket..."<<endl;
  cout<<"You look around to understand what will be your next step."<<endl<<endl;
//-------------------------------------------------------------------------
  launchGame(root);
  getch();
  return 0;
}

void tokenizeLine(string line, string nodeInfo[7]) {
  int i = 0, j = 0;

  while(line[i]!='\0' && j < 7) {
    if (line[i] != '#') {
      nodeInfo[j]+=line[i++];
    } else {
      j++;
      i++;
    }
  }
}

node *buildTree(string baseNode, node *parent) {
  int i = findNode(baseNode);
  if (i >= 0) {
    node *p;
    p = new node;
    p->name = tree[i][0];
    p->text = tree[i][1];
    p->optionLeft = tree[i][2];
    p->optionRight = tree[i][3];
    p->optionParent = tree[i][4];
    if (parent != NULL) {
      p->parent = parent;
      if (parent->name == p->name) {
        return NULL; // a node can not be it's own parent!
      }
    }
    p->left = buildTree(tree[i][5], p);
    p->right = buildTree(tree[i][6], p);
    return p;
  }
  return NULL;
}

int findNode(string name) {
  for(int i=0; i < nodesCount; i++) {
    if (tree[i][0] == name) {
      return i;
    }
  }
  return -1;
}

void launchGame(node *Node) {
  int i = 0;
  if (Node == NULL) {
    return;// ignore non-existing nodes;
  }
  string option1 = Node->optionLeft;
  string option2 = Node->optionRight;
  string option3 = Node->optionParent;
  string state = Node->name;

  cout<<Node->text<<endl;
//check if we are in a win/lose node;
  if (state.find("win") != string::npos) {
    showVictory();
    return;
  }
  if (state.find("lose") != string::npos) {
    showGameOver();
    return;
  }
//output available options;
  if (option1 != "") {
    cout<<" -"<<++i<<"- "<<Node->optionLeft<<endl;
  }
  if (option2 != "") {
    cout<<" -"<<++i<<"- "<<Node->optionRight<<endl;
  }
  if (option3 != "") {
    cout<<" -"<<++i<<"- "<<Node->optionParent<<endl;
  }
  if (i == 0) {
    return; // if there are no options then quit
  }
//input option number between 1 and 3;
  char c;
  while (true) {
    c = getch();
    if (c >= '1' && c <= '0' + i) {
      break;
    } else {
      cout<<"input value should be between 1 and "<<i<<endl;
    }
  }
//move to the next node. Node choice depends on the option number;
  if (c == '1') {
    launchGame(Node->left);
  } else if (c == '2') {
    launchGame(Node->right);
  } else {
    launchGame(Node->parent);
  }

}
void showVictory() {
  cout<<"You've made it! It is about time to rest."<<endl;
  cout<<"VICTORY!!!"<<endl;
  cout<<"press any key to quit game";
}
void showGameOver() {
  cout<<"You've lost!"<<endl;
  cout<<"Game Over"<<endl;
  cout<<"press any key to quit game";
}


