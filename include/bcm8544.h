#ifndef BCM8544_h
#define BCM8544_h

void bcm8544_init();
void goto_xy(int x, int y);
void write(char *message);
void write_at(int x, int y, char *message);
void clear_screen();

#endif
