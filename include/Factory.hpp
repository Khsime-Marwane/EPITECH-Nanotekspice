//
// Author: Marwane Khsime 
// Date: 2017-02-08 15:27:03 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-08 15:27:03
//

#ifndef _FACTORY_HPP_
# define _FACTORY_HPP_

#include <map>
#include <functional>
#include <utility>

#include "Errors.hpp"
#include "IComponent.hpp"

#include "False.hpp"
#include "True.hpp"
#include "Output.hpp"
#include "Input.hpp"
#include "C4071.hpp"

class   Factory {
    public:
        Factory();
        ~Factory();

        nts::IComponent *create(const std::string &);
    private:
        std::map<const std::string, std::function<nts::IComponent *(void)> > constructors;

        nts::IComponent *createFalse() const;
        nts::IComponent *createTrue() const;
        nts::IComponent *createInput() const;
        nts::IComponent *createOutput() const;
        nts::IComponent *createC4071() const;

};

#endif /* _FACTORY_HPP_ */