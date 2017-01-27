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
  state         _value;

 public:
  Component(std::string = "");
  ~Component();

  std::string   getName() const;
  state         getValue() const;

  void  setName(const std::string&);
  void  setValue(const state &);
};

#endif