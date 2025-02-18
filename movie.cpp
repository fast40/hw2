#include <iostream>
#include "movie.h"
#include "util.h"

Movie::Movie(const std::string name, double price, int qty, std::string genre, std::string rating) : Product("movie", name, price, qty), genre_(genre),  rating_(rating) {}

std::set<std::string> Movie::keywords() const {
        return parseStringToWords(name_ + genre_ + rating_);
}

std::string Movie::displayString() const {
        std::string result; 

        result += name_ + "\n";
        result += "Genre: " + genre_ + "Rating: " + rating_ + "\n";
        result += std::to_string(price_) + std::to_string(qty_) + "left.\n";  // probably have to deal with the price being a ton of digits

        return result;
}

void Movie::dump(std::ostream& os) const {
        os << category_ << std::endl;
        os << name_ << std::endl;
        os << price_ << std::endl;
        os << qty_ << std::endl;
        os << genre_ << std::endl;
        os << rating_ << std::endl;
}
