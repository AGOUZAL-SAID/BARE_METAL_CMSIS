#include <stdint.h>
// Global variables
uint32_t *a;
uint32_t *b;
uint32_t *c;
__attribute__((naked)) void f() {
*a += *c;
*b += *c;
}
