#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <iostream>

class   Component {
  enum    state
  {
    TRUE,
    FALSE,
    UNDEFINED
  };

  std::string   _name;
  std::string   _type;
  state         _value;

 public:
  Component(std::string = "", std::string = "");
  ~Component();

  std::string   getName() const;
  std::string   getType() const;
  state         getValue() const;

  void  setValue(const state &);
};

#endif