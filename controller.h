#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include "tag.h"
#include <iostream>
#include <string>

class Controller {
  Tag *doc;
  Tag *cur;
  Tag *clip;
  void printCurrent();
  bool canMove();

public:
  Controller();
  ~Controller();
  void print();
  void addChild(std::string option);
  void deleteCur();
  void parent();
  void up();
  void setId(std::string option);
  void setValue(std::string option);
  void findChild(std::string option);
  void findChildId(std::string option);
  void list();
  void cut();
  void copy();
  void paste();
};

#endif
