multiline_comment|/*&n; * Intel Multimedia Timer device interface&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2001-2002 Silicon Graphics, Inc.  All rights reserved.&n; *&n; * Helper file for the SN implementation of mmtimers&n; *&n; * 11/01/01 - jbarnes - initial revision&n; */
macro_line|#ifndef _SN_MMTIMER_PRIVATE_H
DECL|macro|RTC_BITS
mdefine_line|#define RTC_BITS 55 /* 55 bits for this implementation */
DECL|macro|NUM_COMPARATORS
mdefine_line|#define NUM_COMPARATORS 2 /* two comparison registers in SN1 */
multiline_comment|/*&n; * Check for an interrupt and clear the pending bit if&n; * one is waiting.&n; */
DECL|macro|MMTIMER_INT_PENDING
mdefine_line|#define MMTIMER_INT_PENDING(x) (x ? *(RTC_INT_PENDING_B_ADDR) : *(RTC_INT_PENDING_A_ADDR))
multiline_comment|/*&n; * Set interrupts on RTC &squot;x&squot; to &squot;v&squot; (true or false)&n; */
DECL|macro|MMTIMER_SET_INT
mdefine_line|#define MMTIMER_SET_INT(x,v) (x ? (*(RTC_INT_ENABLED_B_ADDR) = (unsigned long)(v)) : (*(RTC_INT_ENABLED_A_ADDR) = (unsigned long)(v)))
DECL|macro|MMTIMER_ENABLE_INT
mdefine_line|#define MMTIMER_ENABLE_INT(x) MMTIMER_SET_INT(x, 1)
DECL|macro|MMTIMER_DISABLE_INT
mdefine_line|#define MMTIMER_DISABLE_INT(x) MMTIMER_SET_INT(x, 0)
DECL|struct|mmtimer
r_typedef
r_struct
id|mmtimer
(brace
DECL|member|timer_lock
id|spinlock_t
id|timer_lock
suffix:semicolon
DECL|member|periodic
r_int
r_int
id|periodic
suffix:semicolon
DECL|member|signo
r_int
id|signo
suffix:semicolon
DECL|member|compare
r_volatile
r_int
r_int
op_star
id|compare
suffix:semicolon
DECL|member|process
r_struct
id|task_struct
op_star
id|process
suffix:semicolon
DECL|typedef|mmtimer_t
)brace
id|mmtimer_t
suffix:semicolon
macro_line|#endif /* _SN_LINUX_MMTIMER_PRIVATE_H */
eof
