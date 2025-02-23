#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <vector>
#include <unordered_map>
#include <ostream>
#include "datastore.h"
#include "product.h"

class MyDataStore : public DataStore {
        public:
                void addProduct(Product* p);
                void addUser(User* u);
                std::vector<Product*> search(std::vector<std::string>& terms, int type);
                void dump(std::ostream& ofile);
        private:
                std::unordered_map<std::string, std::set<Product*>> keyword_search_map_;

                std::set<Product*> products_;
                std::set<User*> users_;
};

#endif
