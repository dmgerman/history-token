multiline_comment|/*&n; * Machine dependent access functions for RTC registers.&n; */
macro_line|#ifndef _ASM_MC146818RTC_H
DECL|macro|_ASM_MC146818RTC_H
mdefine_line|#define _ASM_MC146818RTC_H
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#ifndef RTC_PORT
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(0x70 + (x))
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;1&t;/* RTC operates in binary mode */
macro_line|#endif
macro_line|#ifdef __HAVE_ARCH_CMPXCHG
multiline_comment|/*&n; * This lock provides nmi access to the CMOS/RTC registers.  It has some&n; * special properties.  It is owned by a CPU and stores the index register&n; * currently being accessed (if owned).  The idea here is that it works&n; * like a normal lock (normally).  However, in an NMI, the NMI code will&n; * first check to see if its CPU owns the lock, meaning that the NMI&n; * interrupted during the read/write of the device.  If it does, it goes ahead&n; * and performs the access and then restores the index register.  If it does&n; * not, it locks normally.&n; *&n; * Note that since we are working with NMIs, we need this lock even in&n; * a non-SMP machine just to mark that the lock is owned.&n; *&n; * This only works with compare-and-swap.  There is no other way to&n; * atomically claim the lock and set the owner.&n; */
macro_line|#include &lt;linux/smp.h&gt;
r_extern
r_volatile
r_int
r_int
id|cmos_lock
suffix:semicolon
multiline_comment|/*&n; * All of these below must be called with interrupts off, preempt&n; * disabled, etc.&n; */
DECL|function|lock_cmos
r_static
r_inline
r_void
id|lock_cmos
c_func
(paren
r_int
r_char
id|reg
)paren
(brace
r_int
r_int
r_new
suffix:semicolon
r_new
op_assign
(paren
(paren
id|smp_processor_id
c_func
(paren
)paren
op_plus
l_int|1
)paren
op_lshift
l_int|8
)paren
op_or
id|reg
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|cmos_lock
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|__cmpxchg
c_func
(paren
op_amp
id|cmos_lock
comma
l_int|0
comma
r_new
comma
r_sizeof
(paren
id|cmos_lock
)paren
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
)brace
)brace
DECL|function|unlock_cmos
r_static
r_inline
r_void
id|unlock_cmos
c_func
(paren
r_void
)paren
(brace
id|cmos_lock
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|do_i_have_lock_cmos
r_static
r_inline
r_int
id|do_i_have_lock_cmos
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|cmos_lock
op_rshift
l_int|8
)paren
op_eq
(paren
id|smp_processor_id
c_func
(paren
)paren
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|current_lock_cmos_reg
r_static
r_inline
r_int
r_char
id|current_lock_cmos_reg
c_func
(paren
r_void
)paren
(brace
r_return
id|cmos_lock
op_amp
l_int|0xff
suffix:semicolon
)brace
DECL|macro|lock_cmos_prefix
mdefine_line|#define lock_cmos_prefix(reg) &bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long cmos_flags;&t;&bslash;&n;&t;&t;local_irq_save(cmos_flags);&t;&bslash;&n;&t;&t;lock_cmos(reg)
DECL|macro|lock_cmos_suffix
mdefine_line|#define lock_cmos_suffix(reg) &bslash;&n;&t;&t;unlock_cmos();&t;&t;&t;&bslash;&n;&t;&t;local_irq_restore(cmos_flags);&t;&bslash;&n;&t;} while (0)
macro_line|#else
DECL|macro|lock_cmos_prefix
mdefine_line|#define lock_cmos_prefix(reg) do {} while (0)
DECL|macro|lock_cmos_suffix
mdefine_line|#define lock_cmos_suffix(reg) do {} while (0)
DECL|macro|lock_cmos
mdefine_line|#define lock_cmos(reg)
DECL|macro|unlock_cmos
mdefine_line|#define unlock_cmos()
DECL|macro|do_i_have_lock_cmos
mdefine_line|#define do_i_have_lock_cmos() 0
DECL|macro|current_lock_cmos_reg
mdefine_line|#define current_lock_cmos_reg() 0
macro_line|#endif
multiline_comment|/*&n; * The yet supported machines all access the RTC index register via&n; * an ISA port access but the way to access the date register differs ...&n; */
DECL|macro|CMOS_READ
mdefine_line|#define CMOS_READ(addr) rtc_cmos_read(addr)
DECL|macro|CMOS_WRITE
mdefine_line|#define CMOS_WRITE(val, addr) rtc_cmos_write(val, addr)
r_int
r_char
id|rtc_cmos_read
c_func
(paren
r_int
r_char
id|addr
)paren
suffix:semicolon
r_void
id|rtc_cmos_write
c_func
(paren
r_int
r_char
id|val
comma
r_int
r_char
id|addr
)paren
suffix:semicolon
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ 8
macro_line|#endif /* _ASM_MC146818RTC_H */
eof
