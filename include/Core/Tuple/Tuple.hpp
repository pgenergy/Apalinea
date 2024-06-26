#ifndef APALINEA_CORE_TUPLE_TUPLE_HPP
#define APALINEA_CORE_TUPLE_TUPLE_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include "Core/Tuple/Entry/Entry.hpp"

namespace Apalinea::Core::Tuple {
    class Tuple {
    public:
        using ItemName = std::string;

        Tuple() = default;

        Tuple(Tuple &&other)
        noexcept: vItems(std::move(other.vItems)) {
        }

        Tuple(const Tuple& other) {
            vItems = other.vItems;
        }

        virtual ~Tuple() = default;

        Tuple& operator=(Tuple&& other) noexcept {
            vItems = std::move(other.vItems);
            return *this;
        }

        Tuple& operator=(const Tuple& other) = default;

        void moveItems(Tuple &&other) {
            this->vItems.merge(other.vItems);
            other.vItems.clear();
        }

        void removeItem(const ItemName& name) {
            this->vItems.erase(name);
        }

        void removeItem(ItemName&& name) {
            this->vItems.erase(name);
        }

        [[maybe_unused]] void addItem(const ItemName& name, Core::Tuple::Entry&& item) {
            this->vItems.emplace(name,std::move(item));
        }

        void addItem(ItemName&& name, Core::Tuple::Entry&& item) {
            this->vItems.emplace(std::move(name),std::move(item));
        }

        [[maybe_unused]] void updateItem(const ItemName& name, Core::Tuple::Entry&& item) {
            this->vItems.insert_or_assign(name,std::move(item));
        }

        [[maybe_unused]] void updateItem(ItemName&& name, Core::Tuple::Entry&& item) {
            this->vItems.insert_or_assign(std::move(name),std::move(item));
        }

        [[maybe_unused]] void updateItemName(const ItemName& oldName, const ItemName& newName) {
            if(this->vItems.find(oldName) != this->vItems.end() && this->vItems.find(newName) == this->vItems.end()/*this->vItems.contains(oldName) && !this->vItems.contains(newName)*/){
                this->vItems.insert({newName,std::move(this->vItems.at(oldName))});
                this->vItems.erase(oldName);
            }
        }

        [[maybe_unused]] void updateItemName(ItemName&& oldName, ItemName&& newName) {
            if(this->vItems.find(oldName) != this->vItems.end() && this->vItems.find(newName) == this->vItems.end()/*this->vItems.contains(oldName) && !this->vItems.contains(newName)*/){
                this->vItems.insert({std::move(newName),std::move(this->vItems.at(oldName))});
                this->vItems.erase(oldName);
            }
        }

        const Core::Tuple::Entry& getEntry(const ItemName& name) {
            if(this->vItems.find(name) != this->vItems.end()/*this->vItems.contains(name)*/) {
                return this->vItems.at(name);
            }
            throw std::runtime_error("No DepItem was found with that name!");
        }

        template<typename T>
        const T& getItem(const ItemName& name) {
            if(this->vItems.find(name) != this->vItems.end()/*this->vItems.contains(name)*/) {
                return this->vItems.at(name).get<T>();
            }
            throw std::runtime_error("No DepItem was found with that name!");
        }

        [[nodiscard]] const std::unordered_map<std::string, Core::Tuple::Entry> &getItems() const {
            return this->vItems;
        }

        bool containsItem(const ItemName& name) const {
            return this->vItems.find(name) != this->vItems.end()/*this->vItems.contains(name)*/;
        }

        void clear() {
            this->vItems.clear();
        }

    private:
        std::unordered_map<ItemName, Core::Tuple::Entry> vItems;
    };
} // Apalinea::Core::Tuple

#endif //APALINEA_CORE_TUPLE_TUPLE_HPP
