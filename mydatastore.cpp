#include <set>
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

        for (int i = 1; i < match_sets.size(); ++i) {
                result = set_function(result, match_sets[i]);
        }

        return std::vector<Product*>(result.begin(), result.end());
}

void MyDataStore::addUser(User* u) {
        users_.insert(u);
}

void MyDataStore::dump(std::ostream& ofile) {
        for (auto product : products_) {
                product->dump(ofile);
        }
}

