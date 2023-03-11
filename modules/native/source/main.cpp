#include "jarnax.hpp"
#include <csignal>

// Pretend we have have a hardware interrupt system here
void signal_handler(int sig) {
    signal(SIGINT, signal_handler);
    printf("SIGINT: %d\n", sig);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    // register signal handler for various emulated interrupts
    signal(SIGINT, signal_handler);
    // enter the reset entry point
    reset_entry();
    return 0;
}