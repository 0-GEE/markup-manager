#include "controller.h"
#include "tag.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
  Controller ctr;
  string cmd;
  string option;
  cout << "[Command?]" << endl;
  while (cin >> cmd) {
    if (cmd == "print") {
      ctr.print();
    } else if (cmd == "add") {
      cin >> option;
      ctr.addChild(option);
    } else if (cmd == "delete") {
      ctr.deleteCur();
    } else if (cmd == "parent") {
      ctr.parent();
    } else if (cmd == "up") {
      ctr.up();
    } else if (cmd == "id") {
      cin >> option;
      ctr.setId(option);
    } else if (cmd == "value") {
      cin >> option;
      ctr.setValue(option);
    } else if (cmd == "find") {
      cin >> option;
      ctr.findChild(option);
    } else if (cmd == "findId") {
      cin >> option;
      ctr.findChildId(option);
    } else if (cmd == "list") {
      ctr.list();
    } else if (cmd == "cut") {
      ctr.cut();
    } else if (cmd == "copy") {
      ctr.copy();
    } else if (cmd == "paste") {
      ctr.paste();
    } else if (cmd == "quit") {
      break;
    } else {
      cerr << "Invalid command." << endl;
    }
    cout << "[Command?]" << endl;
  }
}
