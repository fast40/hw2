#include <iostream>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string name, double price, int qty, std::string size, std::string brand) : Product("clothing", name, price, qty), size_(size),  brand_(brand) {}

std::set<std::string> Clothing::keywords() const {
        return parseStringToWords(name_ + " " + brand_);
}

std::string Clothing::displayString() const {
        std::string result; 

        result += name_ + "\n";
        result += "Size: " + size_ + " Brand: " + brand_ + "\n";
        result += std::to_string(int(price_) ) + "." + std::to_string(int(price_ * 100) % 100) + " ";
        result += std::to_string(qty_) + " left.\n";

        return result;
}

void Clothing::dump(std::ostream& os) const {
        os << category_ << std::endl;
        os << name_ << std::endl;
        os << price_ << std::endl;
        os << qty_ << std::endl;
        os << size_ << std::endl;
        os << brand_ << std::endl;
}
