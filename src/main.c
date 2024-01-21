#include <clock/clock.h>
#include <stdio.h>

void _stdlib_init() {}

int main() {
    clock_init();
    clock_loop();
    clock_exit();
    return 0;
}
