multiline_comment|/*&n; * PAL &amp; SAL emulation.&n; *&n; * Copyright (C) 1998-2001 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * For the HP simulator, this file gets include in boot/bootloader.c.&n; * For SoftSDV, this file gets included in sys_softsdv.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_PCI
macro_line|# include &lt;linux/pci.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/efi.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pal.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
DECL|macro|MB
mdefine_line|#define MB&t;(1024*1024UL)
DECL|macro|SIMPLE_MEMMAP
mdefine_line|#define SIMPLE_MEMMAP&t;1
macro_line|#if SIMPLE_MEMMAP
DECL|macro|NUM_MEM_DESCS
macro_line|# define NUM_MEM_DESCS&t;4
macro_line|#else
DECL|macro|NUM_MEM_DESCS
macro_line|# define NUM_MEM_DESCS&t;16
macro_line|#endif
DECL|variable|fw_mem
r_static
r_char
id|fw_mem
(braket
(paren
r_sizeof
(paren
r_struct
id|ia64_boot_param
)paren
op_plus
r_sizeof
(paren
id|efi_system_table_t
)paren
op_plus
r_sizeof
(paren
id|efi_runtime_services_t
)paren
op_plus
l_int|1
op_star
r_sizeof
(paren
id|efi_config_table_t
)paren
op_plus
r_sizeof
(paren
r_struct
id|ia64_sal_systab
)paren
op_plus
r_sizeof
(paren
r_struct
id|ia64_sal_desc_entry_point
)paren
op_plus
id|NUM_MEM_DESCS
op_star
(paren
r_sizeof
(paren
id|efi_memory_desc_t
)paren
)paren
op_plus
l_int|1024
)paren
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_IA64_HP_SIM) || defined(CONFIG_IA64_GENERIC)
multiline_comment|/* Simulator system calls: */
DECL|macro|SSC_EXIT
mdefine_line|#define SSC_EXIT&t;66
multiline_comment|/*&n; * Simulator system call.&n; */
r_static
r_int
DECL|function|ssc
id|ssc
(paren
r_int
id|arg0
comma
r_int
id|arg1
comma
r_int
id|arg2
comma
r_int
id|arg3
comma
r_int
id|nr
)paren
(brace
r_register
r_int
id|r8
id|asm
(paren
l_string|&quot;r8&quot;
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mov r15=%1&bslash;n&bslash;t&quot;
l_string|&quot;break 0x80001&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|r8
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|nr
)paren
comma
l_string|&quot;r&quot;
(paren
id|arg0
)paren
comma
l_string|&quot;r&quot;
(paren
id|arg1
)paren
comma
l_string|&quot;r&quot;
(paren
id|arg2
)paren
comma
l_string|&quot;r&quot;
(paren
id|arg3
)paren
)paren
suffix:semicolon
r_return
id|r8
suffix:semicolon
)brace
DECL|macro|SECS_PER_HOUR
mdefine_line|#define SECS_PER_HOUR   (60 * 60)
DECL|macro|SECS_PER_DAY
mdefine_line|#define SECS_PER_DAY    (SECS_PER_HOUR * 24)
multiline_comment|/* Compute the `struct tm&squot; representation of *T,&n;   offset OFFSET seconds east of UTC,&n;   and store year, yday, mon, mday, wday, hour, min, sec into *TP.&n;   Return nonzero if successful.  */
r_int
DECL|function|offtime
id|offtime
(paren
r_int
r_int
id|t
comma
id|efi_time_t
op_star
id|tp
)paren
(brace
r_const
r_int
r_int
r_int
id|__mon_yday
(braket
l_int|2
)braket
(braket
l_int|13
)braket
op_assign
(brace
multiline_comment|/* Normal years.  */
(brace
l_int|0
comma
l_int|31
comma
l_int|59
comma
l_int|90
comma
l_int|120
comma
l_int|151
comma
l_int|181
comma
l_int|212
comma
l_int|243
comma
l_int|273
comma
l_int|304
comma
l_int|334
comma
l_int|365
)brace
comma
multiline_comment|/* Leap years.  */
(brace
l_int|0
comma
l_int|31
comma
l_int|60
comma
l_int|91
comma
l_int|121
comma
l_int|152
comma
l_int|182
comma
l_int|213
comma
l_int|244
comma
l_int|274
comma
l_int|305
comma
l_int|335
comma
l_int|366
)brace
)brace
suffix:semicolon
r_int
r_int
id|days
comma
id|rem
comma
id|y
suffix:semicolon
r_const
r_int
r_int
r_int
op_star
id|ip
suffix:semicolon
id|days
op_assign
id|t
op_div
id|SECS_PER_DAY
suffix:semicolon
id|rem
op_assign
id|t
op_mod
id|SECS_PER_DAY
suffix:semicolon
r_while
c_loop
(paren
id|rem
OL
l_int|0
)paren
(brace
id|rem
op_add_assign
id|SECS_PER_DAY
suffix:semicolon
op_decrement
id|days
suffix:semicolon
)brace
r_while
c_loop
(paren
id|rem
op_ge
id|SECS_PER_DAY
)paren
(brace
id|rem
op_sub_assign
id|SECS_PER_DAY
suffix:semicolon
op_increment
id|days
suffix:semicolon
)brace
id|tp-&gt;hour
op_assign
id|rem
op_div
id|SECS_PER_HOUR
suffix:semicolon
id|rem
op_mod_assign
id|SECS_PER_HOUR
suffix:semicolon
id|tp-&gt;minute
op_assign
id|rem
op_div
l_int|60
suffix:semicolon
id|tp-&gt;second
op_assign
id|rem
op_mod
l_int|60
suffix:semicolon
multiline_comment|/* January 1, 1970 was a Thursday.  */
id|y
op_assign
l_int|1970
suffix:semicolon
DECL|macro|DIV
macro_line|#&t;define DIV(a, b) ((a) / (b) - ((a) % (b) &lt; 0))
DECL|macro|LEAPS_THRU_END_OF
macro_line|#&t;define LEAPS_THRU_END_OF(y) (DIV (y, 4) - DIV (y, 100) + DIV (y, 400))
DECL|macro|__isleap
macro_line|#&t;define __isleap(year) &bslash;&n;&t;  ((year) % 4 == 0 &amp;&amp; ((year) % 100 != 0 || (year) % 400 == 0))
r_while
c_loop
(paren
id|days
OL
l_int|0
op_logical_or
id|days
op_ge
(paren
id|__isleap
(paren
id|y
)paren
ques
c_cond
l_int|366
suffix:colon
l_int|365
)paren
)paren
(brace
multiline_comment|/* Guess a corrected year, assuming 365 days per year.  */
r_int
r_int
id|yg
op_assign
id|y
op_plus
id|days
op_div
l_int|365
op_minus
(paren
id|days
op_mod
l_int|365
OL
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Adjust DAYS and Y to match the guessed year.  */
id|days
op_sub_assign
(paren
(paren
id|yg
op_minus
id|y
)paren
op_star
l_int|365
op_plus
id|LEAPS_THRU_END_OF
(paren
id|yg
op_minus
l_int|1
)paren
op_minus
id|LEAPS_THRU_END_OF
(paren
id|y
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|y
op_assign
id|yg
suffix:semicolon
)brace
id|tp-&gt;year
op_assign
id|y
suffix:semicolon
id|ip
op_assign
id|__mon_yday
(braket
id|__isleap
c_func
(paren
id|y
)paren
)braket
suffix:semicolon
r_for
c_loop
(paren
id|y
op_assign
l_int|11
suffix:semicolon
id|days
OL
(paren
r_int
r_int
)paren
id|ip
(braket
id|y
)braket
suffix:semicolon
op_decrement
id|y
)paren
r_continue
suffix:semicolon
id|days
op_sub_assign
id|ip
(braket
id|y
)braket
suffix:semicolon
id|tp-&gt;month
op_assign
id|y
op_plus
l_int|1
suffix:semicolon
id|tp-&gt;day
op_assign
id|days
op_plus
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_IA64_HP_SIM */
multiline_comment|/*&n; * Very ugly, but we need this in the simulator only.  Once we run on&n; * real hw, this can all go away.&n; */
r_extern
r_void
id|pal_emulator_static
(paren
r_void
)paren
suffix:semicolon
id|asm
(paren
l_string|&quot;&t;.proc pal_emulator_static&bslash;n&quot;
l_string|&quot;pal_emulator_static:&quot;
l_string|&quot;&t;mov r8=-1&bslash;n&quot;
l_string|&quot;&t;mov r9=256&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;cmp.gtu p6,p7=r9,r28&t;&t;/* r28 &lt;= 255? */&bslash;n&quot;
l_string|&quot;(p6)&t;br.cond.sptk.few static&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;mov r9=512&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;cmp.gtu p6,p7=r9,r28&bslash;n&quot;
l_string|&quot;(p6)&t;br.cond.sptk.few stacked&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;static:&t;cmp.eq p6,p7=6,r28&t;&t;/* PAL_PTCE_INFO */&bslash;n&quot;
l_string|&quot;(p7)&t;br.cond.sptk.few 1f&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;mov r8=0&t;&t;&t;/* status = 0 */&bslash;n&quot;
l_string|&quot;&t;movl r9=0x100000000&t;&t;/* tc.base */&bslash;n&quot;
l_string|&quot;&t;movl r10=0x0000000200000003&t;/* count[0], count[1] */&bslash;n&quot;
l_string|&quot;&t;movl r11=0x1000000000002000&t;/* stride[0], stride[1] */&bslash;n&quot;
l_string|&quot;&t;br.cond.sptk.few rp&bslash;n&quot;
l_string|&quot;1:&t;cmp.eq p6,p7=14,r28&t;&t;/* PAL_FREQ_RATIOS */&bslash;n&quot;
l_string|&quot;(p7)&t;br.cond.sptk.few 1f&bslash;n&quot;
l_string|&quot;&t;mov r8=0&t;&t;&t;/* status = 0 */&bslash;n&quot;
l_string|&quot;&t;movl r9 =0x100000064&t;&t;/* proc_ratio (1/100) */&bslash;n&quot;
l_string|&quot;&t;movl r10=0x100000100&t;&t;/* bus_ratio&lt;&lt;32 (1/256) */&bslash;n&quot;
l_string|&quot;&t;movl r11=0x100000064&t;&t;/* itc_ratio&lt;&lt;32 (1/100) */&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;1:&t;cmp.eq p6,p7=19,r28&t;&t;/* PAL_RSE_INFO */&bslash;n&quot;
l_string|&quot;(p7)&t;br.cond.sptk.few 1f&bslash;n&quot;
l_string|&quot;&t;mov r8=0&t;&t;&t;/* status = 0 */&bslash;n&quot;
l_string|&quot;&t;mov r9=96&t;&t;&t;/* num phys stacked */&bslash;n&quot;
l_string|&quot;&t;mov r10=0&t;&t;&t;/* hints */&bslash;n&quot;
l_string|&quot;&t;mov r11=0&bslash;n&quot;
l_string|&quot;&t;br.cond.sptk.few rp&bslash;n&quot;
l_string|&quot;1:&t;cmp.eq p6,p7=1,r28&t;&t;/* PAL_CACHE_FLUSH */&bslash;n&quot;
l_string|&quot;(p7)&t;br.cond.sptk.few 1f&bslash;n&quot;
l_string|&quot;&t;mov r9=ar.lc&bslash;n&quot;
l_string|&quot;&t;movl r8=524288&t;&t;&t;/* flush 512k million cache lines (16MB) */&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;mov ar.lc=r8&bslash;n&quot;
l_string|&quot;&t;movl r8=0xe000000000000000&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;.loop:&t;fc r8&bslash;n&quot;
l_string|&quot;&t;add r8=32,r8&bslash;n&quot;
l_string|&quot;&t;br.cloop.sptk.few .loop&bslash;n&quot;
l_string|&quot;&t;sync.i&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;srlz.i&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;mov ar.lc=r9&bslash;n&quot;
l_string|&quot;&t;mov r8=r0&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;1:&t;cmp.eq p6,p7=15,r28&t;&t;/* PAL_PERF_MON_INFO */&bslash;n&quot;
l_string|&quot;(p7)&t;br.cond.sptk.few 1f&bslash;n&quot;
l_string|&quot;&t;mov r8=0&t;&t;&t;/* status = 0 */&bslash;n&quot;
l_string|&quot;&t;movl r9 =0x12082004&t;&t;/* generic=4 width=32 retired=8 cycles=18 */&bslash;n&quot;
l_string|&quot;&t;mov r10=0&t;&t;&t;/* reserved */&bslash;n&quot;
l_string|&quot;&t;mov r11=0&t;&t;&t;/* reserved */&bslash;n&quot;
l_string|&quot;&t;mov r16=0xffff&t;&t;&t;/* implemented PMC */&bslash;n&quot;
l_string|&quot;&t;mov r17=0xffff&t;&t;&t;/* implemented PMD */&bslash;n&quot;
l_string|&quot;&t;add r18=8,r29&t;&t;&t;/* second index */&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;st8 [r29]=r16,16&t;&t;/* store implemented PMC */&bslash;n&quot;
l_string|&quot;&t;st8 [r18]=r0,16&t;&t;&t;/* clear remaining bits  */&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;st8 [r29]=r0,16&t;&t;&t;/* store implemented PMC */&bslash;n&quot;
l_string|&quot;&t;st8 [r18]=r0,16&t;&t;&t;/* clear remaining bits  */&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;st8 [r29]=r17,16&t;&t;/* store implemented PMD */&bslash;n&quot;
l_string|&quot;&t;st8 [r18]=r0,16&t;&t;&t;/* clear remaining bits  */&bslash;n&quot;
l_string|&quot;&t;mov r16=0xf0&t;&t;&t;/* cycles count capable PMC */&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;st8 [r29]=r0,16&t;&t;&t;/* store implemented PMC */&bslash;n&quot;
l_string|&quot;&t;st8 [r18]=r0,16&t;&t;&t;/* clear remaining bits  */&bslash;n&quot;
l_string|&quot;&t;mov r17=0x10&t;&t;&t;/* retired bundles capable PMC */&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;st8 [r29]=r16,16&t;&t;/* store cycles capable */&bslash;n&quot;
l_string|&quot;&t;st8 [r18]=r0,16&t;&t;&t;/* clear remaining bits  */&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;st8 [r29]=r0,16&t;&t;&t;/* store implemented PMC */&bslash;n&quot;
l_string|&quot;&t;st8 [r18]=r0,16&t;&t;&t;/* clear remaining bits  */&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;st8 [r29]=r17,16&t;&t;/* store retired bundle capable */&bslash;n&quot;
l_string|&quot;&t;st8 [r18]=r0,16&t;&t;&t;/* clear remaining bits  */&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;&t;st8 [r29]=r0,16&t;&t;&t;/* store implemented PMC */&bslash;n&quot;
l_string|&quot;&t;st8 [r18]=r0,16&t;&t;&t;/* clear remaining bits  */&bslash;n&quot;
l_string|&quot;&t;;;&bslash;n&quot;
l_string|&quot;1:&t;br.cond.sptk.few rp&bslash;n&quot;
l_string|&quot;stacked:&bslash;n&quot;
l_string|&quot;&t;br.ret.sptk.few rp&bslash;n&quot;
l_string|&quot;&t;.endp pal_emulator_static&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Macro to emulate SAL call using legacy IN and OUT calls to CF8, CFC etc.. */
DECL|macro|BUILD_CMD
mdefine_line|#define BUILD_CMD(addr)&t;&t;((0x80000000 | (addr)) &amp; ~3)
DECL|macro|REG_OFFSET
mdefine_line|#define REG_OFFSET(addr)&t;(0x00000000000000FF &amp; (addr))
DECL|macro|DEVICE_FUNCTION
mdefine_line|#define DEVICE_FUNCTION(addr)&t;(0x000000000000FF00 &amp; (addr))
DECL|macro|BUS_NUMBER
mdefine_line|#define BUS_NUMBER(addr)&t;(0x0000000000FF0000 &amp; (addr))
r_static
id|efi_status_t
DECL|function|efi_get_time
id|efi_get_time
(paren
id|efi_time_t
op_star
id|tm
comma
id|efi_time_cap_t
op_star
id|tc
)paren
(brace
macro_line|#if defined(CONFIG_IA64_HP_SIM) || defined(CONFIG_IA64_GENERIC)
r_struct
(brace
r_int
id|tv_sec
suffix:semicolon
multiline_comment|/* must be 32bits to work */
r_int
id|tv_usec
suffix:semicolon
)brace
id|tv32bits
suffix:semicolon
id|ssc
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|tv32bits
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_GET_TOD
)paren
suffix:semicolon
id|memset
c_func
(paren
id|tm
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|tm
)paren
)paren
suffix:semicolon
id|offtime
c_func
(paren
id|tv32bits.tv_sec
comma
id|tm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tc
)paren
id|memset
c_func
(paren
id|tc
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|tc
)paren
)paren
suffix:semicolon
macro_line|#else
macro_line|#&t;error Not implemented yet...
macro_line|#endif
r_return
id|EFI_SUCCESS
suffix:semicolon
)brace
r_static
r_void
DECL|function|efi_reset_system
id|efi_reset_system
(paren
r_int
id|reset_type
comma
id|efi_status_t
id|status
comma
r_int
r_int
id|data_size
comma
id|efi_char16_t
op_star
id|data
)paren
(brace
macro_line|#if defined(CONFIG_IA64_HP_SIM) || defined(CONFIG_IA64_GENERIC)
id|ssc
c_func
(paren
id|status
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|SSC_EXIT
)paren
suffix:semicolon
macro_line|#else
macro_line|#&t;error Not implemented yet...
macro_line|#endif
)brace
r_static
id|efi_status_t
DECL|function|efi_unimplemented
id|efi_unimplemented
(paren
r_void
)paren
(brace
r_return
id|EFI_UNSUPPORTED
suffix:semicolon
)brace
r_static
r_int
DECL|function|sal_emulator
id|sal_emulator
(paren
r_int
id|index
comma
r_int
r_int
id|in1
comma
r_int
r_int
id|in2
comma
r_int
r_int
id|in3
comma
r_int
r_int
id|in4
comma
r_int
r_int
id|in5
comma
r_int
r_int
id|in6
comma
r_int
r_int
id|in7
)paren
(brace
r_register
r_int
id|r9
id|asm
(paren
l_string|&quot;r9&quot;
)paren
op_assign
l_int|0
suffix:semicolon
r_register
r_int
id|r10
id|asm
(paren
l_string|&quot;r10&quot;
)paren
op_assign
l_int|0
suffix:semicolon
r_register
r_int
id|r11
id|asm
(paren
l_string|&quot;r11&quot;
)paren
op_assign
l_int|0
suffix:semicolon
r_int
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t do a &quot;switch&quot; here since that gives us code that&n;&t; * isn&squot;t self-relocatable.&n;&t; */
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|index
op_eq
id|SAL_FREQ_BASE
)paren
(brace
r_switch
c_cond
(paren
id|in1
)paren
(brace
r_case
id|SAL_FREQ_BASE_PLATFORM
suffix:colon
id|r9
op_assign
l_int|200000000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SAL_FREQ_BASE_INTERVAL_TIMER
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Is this supposed to be the cr.itc frequency&n;&t;&t;&t; * or something platform specific?  The SAL&n;&t;&t;&t; * doc ain&squot;t exactly clear on this...&n;&t;&t;&t; */
id|r9
op_assign
l_int|700000000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SAL_FREQ_BASE_REALTIME_CLOCK
suffix:colon
id|r9
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|index
op_eq
id|SAL_SET_VECTORS
)paren
(brace
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|index
op_eq
id|SAL_GET_STATE_INFO
)paren
(brace
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|index
op_eq
id|SAL_GET_STATE_INFO_SIZE
)paren
(brace
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|index
op_eq
id|SAL_CLEAR_STATE_INFO
)paren
(brace
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|index
op_eq
id|SAL_MC_RENDEZ
)paren
(brace
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|index
op_eq
id|SAL_MC_SET_PARAMS
)paren
(brace
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|index
op_eq
id|SAL_CACHE_FLUSH
)paren
(brace
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|index
op_eq
id|SAL_CACHE_INIT
)paren
(brace
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
)brace
r_else
r_if
c_cond
(paren
id|index
op_eq
id|SAL_PCI_CONFIG_READ
)paren
(brace
multiline_comment|/*&n;&t;&t; * in1 contains the PCI configuration address and in2&n;&t;&t; * the size of the read.  The value that is read is&n;&t;&t; * returned via the general register r9.&n;&t;&t; */
id|outl
c_func
(paren
id|BUILD_CMD
c_func
(paren
id|in1
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in2
op_eq
l_int|1
)paren
multiline_comment|/* Reading byte  */
id|r9
op_assign
id|inb
c_func
(paren
l_int|0xCFC
op_plus
(paren
(paren
id|REG_OFFSET
c_func
(paren
id|in1
)paren
op_amp
l_int|3
)paren
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|in2
op_eq
l_int|2
)paren
multiline_comment|/* Reading word  */
id|r9
op_assign
id|inw
c_func
(paren
l_int|0xCFC
op_plus
(paren
(paren
id|REG_OFFSET
c_func
(paren
id|in1
)paren
op_amp
l_int|2
)paren
)paren
)paren
suffix:semicolon
r_else
multiline_comment|/* Reading dword */
id|r9
op_assign
id|inl
c_func
(paren
l_int|0xCFC
)paren
suffix:semicolon
id|status
op_assign
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|index
op_eq
id|SAL_PCI_CONFIG_WRITE
)paren
(brace
multiline_comment|/*&n;&t;&t; * in1 contains the PCI configuration address, in2 the&n;&t;&t; * size of the write, and in3 the actual value to be&n;&t;&t; * written out.&n;&t;&t; */
id|outl
c_func
(paren
id|BUILD_CMD
c_func
(paren
id|in1
)paren
comma
l_int|0xCF8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in2
op_eq
l_int|1
)paren
multiline_comment|/* Writing byte  */
id|outb
c_func
(paren
id|in3
comma
l_int|0xCFC
op_plus
(paren
(paren
id|REG_OFFSET
c_func
(paren
id|in1
)paren
op_amp
l_int|3
)paren
)paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|in2
op_eq
l_int|2
)paren
multiline_comment|/* Writing word  */
id|outw
c_func
(paren
id|in3
comma
l_int|0xCFC
op_plus
(paren
(paren
id|REG_OFFSET
c_func
(paren
id|in1
)paren
op_amp
l_int|2
)paren
)paren
)paren
suffix:semicolon
r_else
multiline_comment|/* Writing dword */
id|outl
c_func
(paren
id|in3
comma
l_int|0xCFC
)paren
suffix:semicolon
id|status
op_assign
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
macro_line|#endif /* CONFIG_PCI */
)brace
r_else
r_if
c_cond
(paren
id|index
op_eq
id|SAL_UPDATE_PAL
)paren
(brace
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|asm
r_volatile
(paren
l_string|&quot;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|r9
)paren
comma
l_string|&quot;r&quot;
(paren
id|r10
)paren
comma
l_string|&quot;r&quot;
(paren
id|r11
)paren
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * This is here to work around a bug in egcs-1.1.1b that causes the&n; * compiler to crash (seems like a bug in the new alias analysis code.&n; */
r_void
op_star
DECL|function|id
id|id
(paren
r_int
id|addr
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
)brace
r_struct
id|ia64_boot_param
op_star
DECL|function|sys_fw_init
id|sys_fw_init
(paren
r_const
r_char
op_star
id|args
comma
r_int
id|arglen
)paren
(brace
id|efi_system_table_t
op_star
id|efi_systab
suffix:semicolon
id|efi_runtime_services_t
op_star
id|efi_runtime
suffix:semicolon
id|efi_config_table_t
op_star
id|efi_tables
suffix:semicolon
r_struct
id|ia64_sal_systab
op_star
id|sal_systab
suffix:semicolon
id|efi_memory_desc_t
op_star
id|efi_memmap
comma
op_star
id|md
suffix:semicolon
r_int
r_int
op_star
id|pal_desc
comma
op_star
id|sal_desc
suffix:semicolon
r_struct
id|ia64_sal_desc_entry_point
op_star
id|sal_ed
suffix:semicolon
r_struct
id|ia64_boot_param
op_star
id|bp
suffix:semicolon
r_int
r_char
id|checksum
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|cp
comma
op_star
id|cmd_line
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
DECL|macro|MAKE_MD
macro_line|#&t;define MAKE_MD(typ, attr, start, end)&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;md = efi_memmap + i++;&t;&t;&t;&bslash;&n;&t;&t;md-&gt;type = typ;&t;&t;&t;&t;&bslash;&n;&t;&t;md-&gt;pad = 0;&t;&t;&t;&t;&bslash;&n;&t;&t;md-&gt;phys_addr = start;&t;&t;&t;&bslash;&n;&t;&t;md-&gt;virt_addr = 0;&t;&t;&t;&bslash;&n;&t;&t;md-&gt;num_pages = (end - start) &gt;&gt; 12;&t;&bslash;&n;&t;&t;md-&gt;attribute = attr;&t;&t;&t;&bslash;&n;&t;} while (0)
id|memset
c_func
(paren
id|fw_mem
comma
l_int|0
comma
r_sizeof
(paren
id|fw_mem
)paren
)paren
suffix:semicolon
id|pal_desc
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|pal_emulator_static
suffix:semicolon
id|sal_desc
op_assign
(paren
r_int
r_int
op_star
)paren
op_amp
id|sal_emulator
suffix:semicolon
id|cp
op_assign
id|fw_mem
suffix:semicolon
id|efi_systab
op_assign
(paren
r_void
op_star
)paren
id|cp
suffix:semicolon
id|cp
op_add_assign
r_sizeof
(paren
op_star
id|efi_systab
)paren
suffix:semicolon
id|efi_runtime
op_assign
(paren
r_void
op_star
)paren
id|cp
suffix:semicolon
id|cp
op_add_assign
r_sizeof
(paren
op_star
id|efi_runtime
)paren
suffix:semicolon
id|efi_tables
op_assign
(paren
r_void
op_star
)paren
id|cp
suffix:semicolon
id|cp
op_add_assign
r_sizeof
(paren
op_star
id|efi_tables
)paren
suffix:semicolon
id|sal_systab
op_assign
(paren
r_void
op_star
)paren
id|cp
suffix:semicolon
id|cp
op_add_assign
r_sizeof
(paren
op_star
id|sal_systab
)paren
suffix:semicolon
id|sal_ed
op_assign
(paren
r_void
op_star
)paren
id|cp
suffix:semicolon
id|cp
op_add_assign
r_sizeof
(paren
op_star
id|sal_ed
)paren
suffix:semicolon
id|efi_memmap
op_assign
(paren
r_void
op_star
)paren
id|cp
suffix:semicolon
id|cp
op_add_assign
id|NUM_MEM_DESCS
op_star
r_sizeof
(paren
op_star
id|efi_memmap
)paren
suffix:semicolon
id|bp
op_assign
(paren
r_void
op_star
)paren
id|cp
suffix:semicolon
id|cp
op_add_assign
r_sizeof
(paren
op_star
id|bp
)paren
suffix:semicolon
id|cmd_line
op_assign
(paren
r_void
op_star
)paren
id|cp
suffix:semicolon
r_if
c_cond
(paren
id|args
)paren
(brace
r_if
c_cond
(paren
id|arglen
op_ge
l_int|1024
)paren
id|arglen
op_assign
l_int|1023
suffix:semicolon
id|memcpy
c_func
(paren
id|cmd_line
comma
id|args
comma
id|arglen
)paren
suffix:semicolon
)brace
r_else
(brace
id|arglen
op_assign
l_int|0
suffix:semicolon
)brace
id|cmd_line
(braket
id|arglen
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|memset
c_func
(paren
id|efi_systab
comma
l_int|0
comma
r_sizeof
(paren
id|efi_systab
)paren
)paren
suffix:semicolon
id|efi_systab-&gt;hdr.signature
op_assign
id|EFI_SYSTEM_TABLE_SIGNATURE
suffix:semicolon
id|efi_systab-&gt;hdr.revision
op_assign
id|EFI_SYSTEM_TABLE_REVISION
suffix:semicolon
id|efi_systab-&gt;hdr.headersize
op_assign
r_sizeof
(paren
id|efi_systab-&gt;hdr
)paren
suffix:semicolon
id|efi_systab-&gt;fw_vendor
op_assign
id|__pa
c_func
(paren
l_string|&quot;H&bslash;0e&bslash;0w&bslash;0l&bslash;0e&bslash;0t&bslash;0t&bslash;0-&bslash;0P&bslash;0a&bslash;0c&bslash;0k&bslash;0a&bslash;0r&bslash;0d&bslash;0&bslash;0&quot;
)paren
suffix:semicolon
id|efi_systab-&gt;fw_revision
op_assign
l_int|1
suffix:semicolon
id|efi_systab-&gt;runtime
op_assign
id|__pa
c_func
(paren
id|efi_runtime
)paren
suffix:semicolon
id|efi_systab-&gt;nr_tables
op_assign
l_int|1
suffix:semicolon
id|efi_systab-&gt;tables
op_assign
id|__pa
c_func
(paren
id|efi_tables
)paren
suffix:semicolon
id|efi_runtime-&gt;hdr.signature
op_assign
id|EFI_RUNTIME_SERVICES_SIGNATURE
suffix:semicolon
id|efi_runtime-&gt;hdr.revision
op_assign
id|EFI_RUNTIME_SERVICES_REVISION
suffix:semicolon
id|efi_runtime-&gt;hdr.headersize
op_assign
r_sizeof
(paren
id|efi_runtime-&gt;hdr
)paren
suffix:semicolon
id|efi_runtime-&gt;get_time
op_assign
id|__pa
c_func
(paren
op_amp
id|efi_get_time
)paren
suffix:semicolon
id|efi_runtime-&gt;set_time
op_assign
id|__pa
c_func
(paren
op_amp
id|efi_unimplemented
)paren
suffix:semicolon
id|efi_runtime-&gt;get_wakeup_time
op_assign
id|__pa
c_func
(paren
op_amp
id|efi_unimplemented
)paren
suffix:semicolon
id|efi_runtime-&gt;set_wakeup_time
op_assign
id|__pa
c_func
(paren
op_amp
id|efi_unimplemented
)paren
suffix:semicolon
id|efi_runtime-&gt;set_virtual_address_map
op_assign
id|__pa
c_func
(paren
op_amp
id|efi_unimplemented
)paren
suffix:semicolon
id|efi_runtime-&gt;get_variable
op_assign
id|__pa
c_func
(paren
op_amp
id|efi_unimplemented
)paren
suffix:semicolon
id|efi_runtime-&gt;get_next_variable
op_assign
id|__pa
c_func
(paren
op_amp
id|efi_unimplemented
)paren
suffix:semicolon
id|efi_runtime-&gt;set_variable
op_assign
id|__pa
c_func
(paren
op_amp
id|efi_unimplemented
)paren
suffix:semicolon
id|efi_runtime-&gt;get_next_high_mono_count
op_assign
id|__pa
c_func
(paren
op_amp
id|efi_unimplemented
)paren
suffix:semicolon
id|efi_runtime-&gt;reset_system
op_assign
id|__pa
c_func
(paren
op_amp
id|efi_reset_system
)paren
suffix:semicolon
id|efi_tables-&gt;guid
op_assign
id|SAL_SYSTEM_TABLE_GUID
suffix:semicolon
id|efi_tables-&gt;table
op_assign
id|__pa
c_func
(paren
id|sal_systab
)paren
suffix:semicolon
multiline_comment|/* fill in the SAL system table: */
id|memcpy
c_func
(paren
id|sal_systab-&gt;signature
comma
l_string|&quot;SST_&quot;
comma
l_int|4
)paren
suffix:semicolon
id|sal_systab-&gt;size
op_assign
r_sizeof
(paren
op_star
id|sal_systab
)paren
suffix:semicolon
id|sal_systab-&gt;sal_rev_minor
op_assign
l_int|1
suffix:semicolon
id|sal_systab-&gt;sal_rev_major
op_assign
l_int|0
suffix:semicolon
id|sal_systab-&gt;entry_count
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_GENERIC
id|strcpy
c_func
(paren
id|sal_systab-&gt;oem_id
comma
l_string|&quot;Generic&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|sal_systab-&gt;product_id
comma
l_string|&quot;IA-64 system&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_IA64_HP_SIM
id|strcpy
c_func
(paren
id|sal_systab-&gt;oem_id
comma
l_string|&quot;Hewlett-Packard&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|sal_systab-&gt;product_id
comma
l_string|&quot;HP-simulator&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_IA64_SDV
id|strcpy
c_func
(paren
id|sal_systab-&gt;oem_id
comma
l_string|&quot;Intel&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|sal_systab-&gt;product_id
comma
l_string|&quot;SDV&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* fill in an entry point: */
id|sal_ed-&gt;type
op_assign
id|SAL_DESC_ENTRY_POINT
suffix:semicolon
id|sal_ed-&gt;pal_proc
op_assign
id|__pa
c_func
(paren
id|pal_desc
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|sal_ed-&gt;sal_proc
op_assign
id|__pa
c_func
(paren
id|sal_desc
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|sal_ed-&gt;gp
op_assign
id|__pa
c_func
(paren
id|sal_desc
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cp
op_assign
(paren
r_char
op_star
)paren
id|sal_systab
suffix:semicolon
id|cp
OL
(paren
r_char
op_star
)paren
id|efi_memmap
suffix:semicolon
op_increment
id|cp
)paren
id|checksum
op_add_assign
op_star
id|cp
suffix:semicolon
id|sal_systab-&gt;checksum
op_assign
op_minus
id|checksum
suffix:semicolon
macro_line|#if SIMPLE_MEMMAP
multiline_comment|/* simulate free memory at physical address zero */
id|MAKE_MD
c_func
(paren
id|EFI_BOOT_SERVICES_DATA
comma
id|EFI_MEMORY_WB
comma
l_int|0
op_star
id|MB
comma
l_int|1
op_star
id|MB
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
id|EFI_PAL_CODE
comma
id|EFI_MEMORY_WB
comma
l_int|1
op_star
id|MB
comma
l_int|2
op_star
id|MB
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
id|EFI_CONVENTIONAL_MEMORY
comma
id|EFI_MEMORY_WB
comma
l_int|2
op_star
id|MB
comma
l_int|130
op_star
id|MB
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
id|EFI_CONVENTIONAL_MEMORY
comma
id|EFI_MEMORY_WB
comma
l_int|4096
op_star
id|MB
comma
l_int|4128
op_star
id|MB
)paren
suffix:semicolon
macro_line|#else
id|MAKE_MD
c_func
(paren
l_int|4
comma
l_int|0x9
comma
l_int|0x0000000000000000
comma
l_int|0x0000000000001000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|7
comma
l_int|0x9
comma
l_int|0x0000000000001000
comma
l_int|0x000000000008a000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|4
comma
l_int|0x9
comma
l_int|0x000000000008a000
comma
l_int|0x00000000000a0000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|5
comma
l_int|0x8000000000000009
comma
l_int|0x00000000000c0000
comma
l_int|0x0000000000100000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|7
comma
l_int|0x9
comma
l_int|0x0000000000100000
comma
l_int|0x0000000004400000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|2
comma
l_int|0x9
comma
l_int|0x0000000004400000
comma
l_int|0x0000000004be5000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|7
comma
l_int|0x9
comma
l_int|0x0000000004be5000
comma
l_int|0x000000007f77e000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|6
comma
l_int|0x8000000000000009
comma
l_int|0x000000007f77e000
comma
l_int|0x000000007fb94000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|6
comma
l_int|0x8000000000000009
comma
l_int|0x000000007fb94000
comma
l_int|0x000000007fb95000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|6
comma
l_int|0x8000000000000009
comma
l_int|0x000000007fb95000
comma
l_int|0x000000007fc00000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|13
comma
l_int|0x8000000000000009
comma
l_int|0x000000007fc00000
comma
l_int|0x000000007fc3a000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|7
comma
l_int|0x9
comma
l_int|0x000000007fc3a000
comma
l_int|0x000000007fea0000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|5
comma
l_int|0x8000000000000009
comma
l_int|0x000000007fea0000
comma
l_int|0x000000007fea8000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|7
comma
l_int|0x9
comma
l_int|0x000000007fea8000
comma
l_int|0x000000007feab000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|5
comma
l_int|0x8000000000000009
comma
l_int|0x000000007feab000
comma
l_int|0x000000007ffff000
)paren
suffix:semicolon
id|MAKE_MD
c_func
(paren
l_int|7
comma
l_int|0x9
comma
l_int|0x00000000ff400000
comma
l_int|0x0000000104000000
)paren
suffix:semicolon
macro_line|#endif
id|bp-&gt;efi_systab
op_assign
id|__pa
c_func
(paren
op_amp
id|fw_mem
)paren
suffix:semicolon
id|bp-&gt;efi_memmap
op_assign
id|__pa
c_func
(paren
id|efi_memmap
)paren
suffix:semicolon
id|bp-&gt;efi_memmap_size
op_assign
id|NUM_MEM_DESCS
op_star
r_sizeof
(paren
id|efi_memory_desc_t
)paren
suffix:semicolon
id|bp-&gt;efi_memdesc_size
op_assign
r_sizeof
(paren
id|efi_memory_desc_t
)paren
suffix:semicolon
id|bp-&gt;efi_memdesc_version
op_assign
l_int|1
suffix:semicolon
id|bp-&gt;command_line
op_assign
id|__pa
c_func
(paren
id|cmd_line
)paren
suffix:semicolon
id|bp-&gt;console_info.num_cols
op_assign
l_int|80
suffix:semicolon
id|bp-&gt;console_info.num_rows
op_assign
l_int|25
suffix:semicolon
id|bp-&gt;console_info.orig_x
op_assign
l_int|0
suffix:semicolon
id|bp-&gt;console_info.orig_y
op_assign
l_int|24
suffix:semicolon
id|bp-&gt;fpswa
op_assign
l_int|0
suffix:semicolon
r_return
id|bp
suffix:semicolon
)brace
eof
