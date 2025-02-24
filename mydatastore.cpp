#include <set>
#include <stdexcept>
#include "mydatastore.h"
#include "util.h"


void MyDataStore::addProduct(Product* p) {
        products_.insert(p);

        for (const std::string& keyword : p->keywords()) {
                std::set<Product*> matches = keyword_search_map_[keyword];

                if (std::find(matches.begin(), matches.end(), p) == matches.end()) {
                        keyword_search_map_[keyword].insert(p);
                }
        }
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
        std::vector<std::set<Product*>> match_sets;

        for (std::string& term : terms) {
                if (keyword_search_map_.find(term) != keyword_search_map_.end()) {
                        match_sets.push_back(keyword_search_map_[term]);
                }
        }

        if (match_sets.empty()) {
                return std::vector<Product*>();
        }
        else if (match_sets.size() == 1) {
                return std::vector<Product*>(match_sets[0].begin(), match_sets[0].end());
        }

        auto set_function = type == 0 ? setIntersection<Product*> : setUnion<Product*>;

        std::set<Product*> result = match_sets[0];

        for (std::size_t i = 1; i < match_sets.size(); ++i) {
                result = set_function(result, match_sets[i]);
        }

        return std::vector<Product*>(result.begin(), result.end());
}

void MyDataStore::addUser(User* u) {
        users_.insert(u);
}

void MyDataStore::dump(std::ostream& ofile) {
        ofile << "<products>" << std::endl;

        for (auto product : products_) {
                product->dump(ofile);
        }

        ofile <<"</products>" << std::endl;

        ofile << "<users>" << std::endl;

        for (auto user : users_) {
                user->dump(ofile);
        }

        ofile << "</users>";
}

void MyDataStore::addToCart(std::string username, Product* p) {
        username = convToLower(username);

        for (auto user : users_) {
                if (convToLower(user->getName()) == username) {
                        cart_[user].push_back(p);
                        return;
                }
        }

        throw std::invalid_argument("Invalid username");
}

void MyDataStore::printCart(std::string username) {
        for (auto user : users_) {
                if (convToLower(user->getName()) == username) {
                        int item_number = 1;
                        for (auto item : cart_[user]) {
                                std::cout << "Item " << item_number++ << std::endl;
                                std::cout << item->displayString() << std::endl;
                        }

                        return;
                }
        }

        throw std::invalid_argument("Invalid username");
}

void MyDataStore::buyCart(std::string username) {
        for (auto user : users_) {
                if (convToLower(user->getName()) == username) {
                        auto it = cart_[user].begin();

                        while (it != cart_[user].end()) {
                                if ((*it)->getQty() > 0 && user->getBalance() >= (*it)->getPrice()) {
                                        (*it)->subtractQty(1);
                                        user->deductAmount((*it)->getPrice());
                                        it = cart_[user].erase(it);
                                }
                                else {
                                        it++;
                                }
                        }

                        return;
                }
        }

        throw std::invalid_argument("Invalid username");
}

MyDataStore::~MyDataStore() {
        for (auto product : products_) {
                delete product;
        }

        for (auto user : users_) {
                delete user;
        }
}
