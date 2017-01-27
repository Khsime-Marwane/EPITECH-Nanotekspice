#include "Circuit.hh"

Circuit::Circuit(int id)
{
  this->_id = id;
}

Circuit::~Circuit(){}

void    Circuit::addComponent(Component new_comp)
{
  this->_comps.push_back(new_comp);
}

void    Circuit::delComponent(std::string name, std::string type)
{
  if (this->_comps.size() > 0)
    {
      for(std::vector<Component>::iterator it = this->_comps.begin(); it != this->_comps.end(); ++it)
        {
          if (name == it->getName() && type == it->getType())
            {
              this->_comps.erase(it);
              break;
            }
        }
    }
}

int   Circuit::getId()
{
  return (this->_id);
}