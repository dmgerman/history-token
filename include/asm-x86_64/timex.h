multiline_comment|/*&n; * linux/include/asm-x86_64/timex.h&n; *&n; * x86-64 architecture timex specifications&n; */
macro_line|#ifndef _ASMx8664_TIMEX_H
DECL|macro|_ASMx8664_TIMEX_H
mdefine_line|#define _ASMx8664_TIMEX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/vsyscall.h&gt;
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;1193182 /* Underlying HZ */
DECL|macro|CLOCK_TICK_FACTOR
mdefine_line|#define CLOCK_TICK_FACTOR&t;20&t;/* Factor of both 1000000 and CLOCK_TICK_RATE */
DECL|macro|FINETUNE
mdefine_line|#define FINETUNE ((((((int)LATCH * HZ - CLOCK_TICK_RATE) &lt;&lt; SHIFT_HZ) * &bslash;&n;&t;(1000000/CLOCK_TICK_FACTOR) / (CLOCK_TICK_RATE/CLOCK_TICK_FACTOR)) &bslash;&n;&t;&t;&lt;&lt; (SHIFT_SCALE-SHIFT_HZ)) / HZ)
DECL|typedef|cycles_t
r_typedef
r_int
r_int
r_int
id|cycles_t
suffix:semicolon
r_extern
id|cycles_t
id|cacheflush_time
suffix:semicolon
DECL|function|get_cycles
r_static
r_inline
id|cycles_t
id|get_cycles
(paren
r_void
)paren
(brace
r_int
r_int
r_int
id|ret
suffix:semicolon
id|rdtscll
c_func
(paren
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_extern
r_int
r_int
id|cpu_khz
suffix:semicolon
multiline_comment|/*&n; * Documentation on HPET can be found at:&n; *      http://www.intel.com/ial/home/sp/pcmmspec.htm&n; *      ftp://download.intel.com/ial/home/sp/mmts098.pdf&n; */
DECL|macro|HPET_ID
mdefine_line|#define HPET_ID&t;&t;0x000
DECL|macro|HPET_PERIOD
mdefine_line|#define HPET_PERIOD&t;0x004
DECL|macro|HPET_CFG
mdefine_line|#define HPET_CFG&t;0x010
DECL|macro|HPET_STATUS
mdefine_line|#define HPET_STATUS&t;0x020
DECL|macro|HPET_COUNTER
mdefine_line|#define HPET_COUNTER&t;0x0f0
DECL|macro|HPET_T0_CFG
mdefine_line|#define HPET_T0_CFG&t;0x100
DECL|macro|HPET_T0_CMP
mdefine_line|#define HPET_T0_CMP&t;0x108
DECL|macro|HPET_T0_ROUTE
mdefine_line|#define HPET_T0_ROUTE&t;0x110
DECL|macro|HPET_ID_VENDOR
mdefine_line|#define HPET_ID_VENDOR&t;0xffff0000
DECL|macro|HPET_ID_LEGSUP
mdefine_line|#define HPET_ID_LEGSUP&t;0x00008000
DECL|macro|HPET_ID_NUMBER
mdefine_line|#define HPET_ID_NUMBER&t;0x00000f00
DECL|macro|HPET_ID_REV
mdefine_line|#define HPET_ID_REV&t;0x000000ff
DECL|macro|HPET_CFG_ENABLE
mdefine_line|#define HPET_CFG_ENABLE&t;0x001
DECL|macro|HPET_CFG_LEGACY
mdefine_line|#define HPET_CFG_LEGACY&t;0x002
DECL|macro|HPET_T0_ENABLE
mdefine_line|#define HPET_T0_ENABLE&t;&t;0x004
DECL|macro|HPET_T0_PERIODIC
mdefine_line|#define HPET_T0_PERIODIC&t;0x008
DECL|macro|HPET_T0_SETVAL
mdefine_line|#define HPET_T0_SETVAL&t;&t;0x040
DECL|macro|HPET_T0_32BIT
mdefine_line|#define HPET_T0_32BIT&t;&t;0x100
r_extern
r_struct
id|vxtime_data
id|vxtime
suffix:semicolon
macro_line|#endif
eof
