#ifndef __TAG_H__
#define __TAG_H__
#include <iostream>
#include <string>

class TagIterator;

class Tag {
  std::string type;
  std::string id;
  std::string value;
  Tag *parent;
  Tag **children;
  int childrenLength;
  int childrenCapacity;
  void swap(Tag &other);
  void resizeChildren();

public:
  // Normal constructor
  Tag(const std::string &type);

  // Copy constructor
  Tag(const Tag &other);
  // Move constructor
  Tag(Tag &&other);
  // Copy assignment operator
  Tag &operator=(const Tag &other);
  // Move assignment operator
  Tag &operator=(Tag &&other);
  // Destructor
  ~Tag();

  const std::string &getType() const;

  const std::string &getId() const;

  void setId(const std::string &_id);

  const std::string &getValue() const;

  void setValue(const std::string &_value);

  Tag *getParent() const;

  void setParent(Tag *_parent);

  // Prints this tag to out in the following format:
  // <type id='id' value='value'>
  //   ...children
  // </type>
  void print(std::ostream &out, int indentLevel = 0) const;

  void addChild(Tag *other);

  void removeChild(Tag *other);

  Tag *findChild(std::string &type);

  Tag *findChildId(std::string &id);

  TagIterator begin() const;

  TagIterator end() const;
  friend class TagIterator;
};

class TagIterator {
  Tag **t;
  explicit TagIterator(Tag **t);

public:
  Tag *operator*() const;

  TagIterator operator++();

  bool operator==(const TagIterator &other) const;

  bool operator!=(const TagIterator &other) const;
  friend class Tag;
};

std::ostream &operator<<(std::ostream &out, const Tag &tag);

#endif
