macro_line|#ifndef __LINUX_PREEMPT_H
DECL|macro|__LINUX_PREEMPT_H
mdefine_line|#define __LINUX_PREEMPT_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|preempt_count
mdefine_line|#define preempt_count() (current_thread_info()-&gt;preempt_count)
macro_line|#ifdef CONFIG_PREEMPT
r_extern
r_void
id|preempt_schedule
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|preempt_disable
mdefine_line|#define preempt_disable() &bslash;&n;do { &bslash;&n;&t;preempt_count()++; &bslash;&n;&t;barrier(); &bslash;&n;} while (0)
DECL|macro|preempt_enable_no_resched
mdefine_line|#define preempt_enable_no_resched() &bslash;&n;do { &bslash;&n;&t;preempt_count()--; &bslash;&n;&t;barrier(); &bslash;&n;} while (0)
DECL|macro|preempt_enable
mdefine_line|#define preempt_enable() &bslash;&n;do { &bslash;&n;&t;preempt_enable_no_resched(); &bslash;&n;&t;if (unlikely(test_thread_flag(TIF_NEED_RESCHED))) &bslash;&n;&t;&t;preempt_schedule(); &bslash;&n;} while (0)
DECL|macro|preempt_check_resched
mdefine_line|#define preempt_check_resched() &bslash;&n;do { &bslash;&n;&t;if (unlikely(test_thread_flag(TIF_NEED_RESCHED))) &bslash;&n;&t;&t;preempt_schedule(); &bslash;&n;} while (0)
macro_line|#else
DECL|macro|preempt_disable
mdefine_line|#define preempt_disable()&t;&t;do { } while (0)
DECL|macro|preempt_enable_no_resched
mdefine_line|#define preempt_enable_no_resched()&t;do {} while(0)
DECL|macro|preempt_enable
mdefine_line|#define preempt_enable()&t;&t;do { } while (0)
DECL|macro|preempt_check_resched
mdefine_line|#define preempt_check_resched()&t;&t;do { } while (0)
macro_line|#endif
macro_line|#endif /* __LINUX_PREEMPT_H */
eof
