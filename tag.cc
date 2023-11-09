#include "tag.h"
using namespace std;

// utility helper functions ////////

string makeIndent(int indentLevel) {
  string retVal = "";
  for (int i = 0; i < indentLevel; ++i) {
    retVal += "  ";
  }
  return retVal;
}

void removeAtIndex(Tag **arr, int idx, int len) {
  for (int i = idx; i < len; ++i) {
    if (i == (len - 1)) {
      arr[i] = nullptr;
      break;
    }
    arr[i] = arr[i + 1];
  }
}

///////////////////////////////////

// begin Tag methods

// normal constructor
Tag::Tag(const string &type)
    : type{type}, id{""}, value{""}, parent{nullptr}, children{nullptr},
      childrenLength{0}, childrenCapacity{0} {}

// copy constructor
Tag::Tag(const Tag &other)
    : type{other.type}, id{other.id}, value{other.value},
      parent{
          other
              .parent}, // using other.parent for now. Change later if necessary
      children{nullptr}, childrenLength{other.childrenLength},
      childrenCapacity{other.childrenCapacity} {

  if (other.children != nullptr) {
    children = new Tag *[other.childrenCapacity];

    for (int i = 0; i < other.childrenLength; ++i) {
      // for each child, recursively call copy ctor to populate

      if (other.children[i] != nullptr)
        children[i] = new Tag{*other.children[i]};
    }

  } else {
    children = nullptr;
  }
}

void Tag::swap(Tag &other) {
  std::swap(type, other.type);
  std::swap(id, other.id);
  std::swap(value, other.value);
  std::swap(parent, other.parent);
  std::swap(children, other.children);
  std::swap(childrenLength, other.childrenLength);
  std::swap(childrenCapacity, other.childrenCapacity);
}

// move constructor
Tag::Tag(Tag &&other)
    : type{other.type}, id{other.id}, value{other.value}, parent{other.parent},
      children{other.children}, childrenLength{other.childrenLength},
      childrenCapacity{other.childrenCapacity} {
  other.parent = nullptr;
  other.children = nullptr;
}

// copy assignment operator
Tag &Tag::operator=(const Tag &other) {
  Tag tmp = other;
  this->swap(tmp);

  return *this;
}

// move assignment operator
Tag &Tag::operator=(Tag &&other) {
  this->swap(other);
  return *this;
}

// destructor
Tag::~Tag() {

  // destroy the heap allocated children
  if (children != nullptr) {
    for (int i = 0; i < childrenLength; ++i) {
      // destroy each heap alloc'd child in the array
      delete children[i];
    }

    // destroy the array itself
    delete[] children;
    children = nullptr;
  }

  parent = nullptr;
}

void Tag::resizeChildren() { // called whenever we intend to add a Tag
  if (children == nullptr) {
    // create the array
    children = new Tag *[1];
    childrenCapacity = 1;
    return;
  }

  if (childrenLength == childrenCapacity) {
    childrenCapacity *= 2;

    Tag **newArr = new Tag *[childrenCapacity];

    for (int i = 0; i < childrenLength; ++i) {
      newArr[i] = children[i];
      children[i] = nullptr;
    }

    delete[] children;
    children = newArr;
  }
}

const string &Tag::getType() const { return type; }

const string &Tag::getId() const { return id; }

void Tag::setId(const string &_id) { id = _id; }

const string &Tag::getValue() const { return value; }

void Tag::setValue(const string &_value) { value = _value; }

Tag *Tag::getParent() const { return parent; }

void Tag::setParent(Tag *_parent) { parent = _parent; }

void Tag::print(ostream &out, int indentLevel) const {
  string opening = makeIndent(indentLevel) + "<" + type;

  if (id != "")
    opening += " id='" + id + "'";
  if (value != "")
    opening += " value='" + value + "'";

  opening += ">";

  string closing = makeIndent(indentLevel) + "</" + type + ">";

  out << opening << endl;

  // recursively print all children
  for (int i = 0; i < childrenLength; ++i) {
    children[i]->print(out, indentLevel + 1);
  }

  out << closing << endl;
}

void Tag::addChild(Tag *other) {
  resizeChildren(); // does nothing if children does not need resizing

  children[childrenLength] = other;
  ++childrenLength;
}

void Tag::removeChild(Tag *other) {
  for (int i = 0; i < childrenLength; ++i) {
    if (children[i] == other) {
      removeAtIndex(children, i, childrenLength);
      --childrenLength;
      break;
    }
  }
}

Tag *Tag::findChild(string &type) {
  Tag *retVal = nullptr;
  for (int i = 0; i < childrenLength; ++i) {
    if (children[i]->type == type) {
      retVal = children[i];
      break;
    }
  }

  return retVal;
}

Tag *Tag::findChildId(string &id) {
  Tag *retVal = nullptr;
  for (int i = 0; i < childrenLength; ++i) {
    if (children[i]->id == id) {
      retVal = children[i];
      break;
    }
  }

  return retVal;
}

TagIterator Tag::begin() const { return TagIterator{children}; }

TagIterator Tag::end() const {
  Tag **thePtr = children + childrenLength;
  return TagIterator{thePtr};
}
// end Tag methods

// begin TagIterator methods

TagIterator::TagIterator(Tag **t) : t{t} {}

Tag *TagIterator::operator*() const { return *t; }

TagIterator TagIterator::operator++() {
  t = t + 1;
  return *this;
}

bool TagIterator::operator==(const TagIterator &other) const {
  return t == other.t;
}

bool TagIterator::operator!=(const TagIterator &other) const {
  return t != other.t;
}
// end TagIterator methods

ostream &operator<<(ostream &out, const Tag &tag) {
  tag.print(out);
  return out;
}
