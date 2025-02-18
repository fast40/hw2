#include <iostream>
#include "book.h"
#include "util.h"

Book::Book(const std::string name, double price, int qty, std::string isbn, std::string author) : Product("book", name, price, qty), isbn_(isbn),  author_(author) {}

std::set<std::string> Book::keywords() const {
        std::set<std::string> result = parseStringToWords(name_ + author_);
        result.insert(isbn_);

        return result;
}

std::string Book::displayString() const {
        std::string result; 

        result += name_ + "\n";
        result += "Author: " + author_ + "ISBN: " + isbn_ + "\n";
        result += std::to_string(price_) + std::to_string(qty_) + "left.\n";  // probably have to deal with the price being a ton of digits

        return result;
}

void Book::dump(std::ostream& os) const {
        os << category_ << std::endl;
        os << name_ << std::endl;
        os << price_ << std::endl;
        os << qty_ << std::endl;
        os << isbn_ << std::endl;
        os << author_ << std::endl;
}
