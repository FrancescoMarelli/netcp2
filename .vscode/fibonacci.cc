#include <iostream>

int main() {

    int next = 0;
    int last = 1;
    int secondlast = 0;
    int limit = 10;
    int sum = 0;

    do {
        
        if(next % 2 == 0) {
            sum += next;
        }
        //std::cout << next << ", " << std::endl;
        secondlast = last;
        last = next;
        next = last + secondlast;
        
    } while (next < limit );
    std::cout << "SUM = " << sum << std::endl;





    return 0;
}