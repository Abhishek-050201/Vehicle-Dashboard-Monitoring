#include<LPC17xx.h>
#include<stdint.h>

#define P 		LPC_GPIO0
#define RS 		(1<<10)
#define EN 		(1<<11)
#define LCD 	(0xFF << 15)

void lcd_init(void);
void delay_lcd(uint32_t ms);
void lcd_cmd(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_str(char *s);
