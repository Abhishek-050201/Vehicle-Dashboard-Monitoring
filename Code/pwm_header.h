#include<LPC17xx.h>
#include<stdint.h>

#define PWM1 	LPC_PWM1
#define SPEED_LOCK		3000U

void pwm_init(void);
uint32_t pwm_conversion(uint32_t val);
int pwm_power(uint32_t speed);
