#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
        std::set<T> result;

        auto pointer1 = s1.begin();
        auto pointer2 = s2.begin();

        while (pointer1 != s1.end() && pointer2 != s2.end()) {
                if (*pointer1 == *pointer2) {
                        result.insert(*pointer1);
                        ++pointer1;
                        ++pointer2;
                }
                else if (*pointer1 > *pointer2) {
                        ++pointer2;
                }
                else {
                        ++pointer1;
                }
        }

        return result;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
        std::set<T> result;

        typename std::set<T>::iterator pointer1 = s1.begin();
        typename std::set<T>::iterator pointer2 = s2.begin();

        while (pointer1 != s1.end() && pointer2 != s2.end()) {
                if (*pointer1 == *pointer2) {
                        result.insert(*pointer1);
                        ++pointer1;
                        ++pointer2;
                }
                else if (*pointer1 > *pointer2) {
                        result.insert(*pointer2);
                        ++pointer2;
                }
                else {
                        result.insert(*pointer1);
                        ++pointer1;
                }
        }

        result.insert(pointer1, s1.end());
        result.insert(pointer2, s2.end());

        return result;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
