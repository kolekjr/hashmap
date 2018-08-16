#include <iostream>
#include <string>

#include "hashmap.h"

unsigned MAX_TABLE_SIZE = 101;

struct hashCode
{
    unsigned operator()(unsigned key)
    {
        return (key * key + 17);
    }
};

int main()
{
    OHashMap<unsigned, std::string, hashCode> map(MAX_TABLE_SIZE);

    map.insert(1, "First");
    map.insert(22, "Second");
 
    std::string result = map.get(11);

    std::cout << "Result:" << result << std::endl;


    return 0;
}