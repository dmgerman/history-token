macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_H83007) || defined(CONFIG_H83068) || defined(CONFIG_H8S2678)
DECL|macro|H8300_TIMER_COUNT_DATA
mdefine_line|#define H8300_TIMER_COUNT_DATA CONFIG_CPU_CLOCK*10/8192
DECL|macro|H8300_TIMER_FREQ
mdefine_line|#define H8300_TIMER_FREQ CONFIG_CPU_CLOCK*1000/8192
macro_line|#endif
macro_line|#if defined(H8_3002) || defined(CONFIG_H83048)
DECL|macro|H8300_TIMER_COUNT_DATA
mdefine_line|#define H8300_TIMER_COUNT_DATA  CONFIG_CPU_CLOCK*10/8
DECL|macro|H8300_TIMER_FREQ
mdefine_line|#define H8300_TIMER_FREQ CONFIG_CPU_CLOCK*1000/8
macro_line|#endif
macro_line|#if !defined(H8300_TIMER_COUNT_DATA)
macro_line|#error illigal configuration
macro_line|#endif
eof
