void led_init(void);

void led_g_on();
void led_g_off();

enum state{LED_OFF,LED_YELLOW,LED_BLUE} ;

void led(enum state comand);


void sleep(unsigned int time );