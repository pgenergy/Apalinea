#ifndef APALINEA_EXTRAS_MEMORY_DEFAULTCREATOR_HPP
#define APALINEA_EXTRAS_MEMORY_DEFAULTCREATOR_HPP

#include <new>
#include "Extras/Memory/ICreator.hpp"

namespace Apalinea::Extras::Memory {
    template <typename Type>
    class DefaultCreator : public ICreator<Type> {
    public:
        Type* create(std::size_t size) override {
            if(size > 1) {
                auto pointer = new Type[size];
                if(pointer) {
                    return pointer;
                }
            } else {
                auto pointer = new Type;
                if(pointer) {
                    return pointer;
                }
            }
            throw std::bad_alloc();
        }

        void destroy(Type* ptr, CreatorArgument arg) override {
            if(arg == CreatorArgument::SINGLE) {
                delete ptr;
            } else {
                delete[] ptr;
            }
        }
    };
} // Apalinea::Extras::Memory

#endif //APALINEA_EXTRAS_MEMORY_DEFAULTCREATOR_HPP
