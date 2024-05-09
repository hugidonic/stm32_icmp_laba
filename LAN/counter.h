#ifndef _COUNTER_H
#define	_COUNTER_H

extern uint32_t tick_count;
extern uint32_t second_count;

#define gettc()		tick_count
#define rtime()		second_count

void counter_init();

#endif /*_COUNTER_H*/
