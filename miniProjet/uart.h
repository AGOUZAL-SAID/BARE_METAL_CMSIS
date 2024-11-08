#include <stdint.h>
typedef unsigned int size_t;
void uart_init(int baudrate);
void uart_putchar(uint8_t c);
uint8_t uart_getchar();
void uart_puts(const char *s);
void uart_gets(char *s, size_t size);
int uart_calculate (uint32_t n );