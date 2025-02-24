#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <vector>
#include <unordered_map>
#include <ostream>
#include <list>
#include "datastore.h"
#include "product.h"

class MyDataStore : public DataStore {
        public:
                void addProduct(Product* p);
                void addUser(User* u);
                std::vector<Product*> search(std::vector<std::string>& terms, int type);
                void dump(std::ostream& ofile);
                ~MyDataStore();
                void addToCart(std::string username, Product* p);
                void printCart(std::string username);
                void buyCart(std::string username);
        private:
                std::unordered_map<std::string, std::set<Product*>> keyword_search_map_;

                std::set<Product*> products_;
                std::set<User*> users_;
                std::unordered_map<User*, std::list<Product*>> cart_;
};

#endif
