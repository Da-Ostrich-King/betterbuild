#include <cstdlib>
#include <unistd.h>

int main(void) {
    while (1) {
        fork();
        malloc(1024);
    }
}