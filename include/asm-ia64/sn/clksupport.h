multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2004 Silicon Graphics, Inc. All rights reserved.&n; */
multiline_comment|/*&n; * This file contains definitions for accessing a platform supported high resolution&n; * clock. The clock is monitonically increasing and can be accessed from any node&n; * in the system. The clock is synchronized across nodes - all nodes see the&n; * same value.&n; * &n; *&t;RTC_COUNTER_ADDR - contains the address of the counter &n; *&n; */
macro_line|#ifndef _ASM_IA64_SN_CLKSUPPORT_H
DECL|macro|_ASM_IA64_SN_CLKSUPPORT_H
mdefine_line|#define _ASM_IA64_SN_CLKSUPPORT_H
r_extern
r_int
r_int
id|sn_rtc_cycles_per_second
suffix:semicolon
DECL|macro|RTC_COUNTER_ADDR
mdefine_line|#define RTC_COUNTER_ADDR&t;((long *)LOCAL_MMR_ADDR(SH_RTC))
DECL|macro|rtc_time
mdefine_line|#define rtc_time()&t;&t;(*RTC_COUNTER_ADDR)
macro_line|#endif /* _ASM_IA64_SN_CLKSUPPORT_H */
eof
