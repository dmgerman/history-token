multiline_comment|/* $Id: obio.h,v 1.4 1998/03/09 14:04:55 jj Exp $&n; * obio.h:  Some useful locations in 0xFXXXXXXXX PA obio space on sun4d.&n; *&n; * Copyright (C) 1997 Jakub Jelinek &lt;jj@sunsite.mff.cuni.cz&gt;&n; */
macro_line|#ifndef _SPARC_OBIO_H
DECL|macro|_SPARC_OBIO_H
mdefine_line|#define _SPARC_OBIO_H
macro_line|#include &lt;asm/asi.h&gt;
multiline_comment|/* This weird monster likes to use the very upper parts of&n;   36bit PA for these things :) */
multiline_comment|/* CSR space (for each XDBUS)&n; *  ------------------------------------------------------------------------&n; *  |   0xFE  |   DEVID    |                | XDBUS ID |                   |&n; *  ------------------------------------------------------------------------&n; *  35      28 27        20 19            10 9        8 7                 0&n; */
DECL|macro|CSR_BASE_ADDR
mdefine_line|#define CSR_BASE_ADDR&t;&t;0xe0000000
DECL|macro|CSR_CPU_SHIFT
mdefine_line|#define CSR_CPU_SHIFT&t;&t;(32 - 4 - 5)
DECL|macro|CSR_XDBUS_SHIFT
mdefine_line|#define CSR_XDBUS_SHIFT&t;&t;8
DECL|macro|CSR_BASE
mdefine_line|#define CSR_BASE(cpu) (((CSR_BASE_ADDR &gt;&gt; CSR_CPU_SHIFT) + cpu) &lt;&lt; CSR_CPU_SHIFT)
multiline_comment|/* ECSR space (not for each XDBUS)&n; *  ------------------------------------------------------------------------&n; *  |   0xF  | DEVID[7:1] |                &t;&t;&t;           |&n; *  ------------------------------------------------------------------------&n; *  35     32 31        25 24                 &t;&t;&t;&t;  0&n; */
DECL|macro|ECSR_BASE_ADDR
mdefine_line|#define ECSR_BASE_ADDR&t;&t;0x00000000
DECL|macro|ECSR_CPU_SHIFT
mdefine_line|#define ECSR_CPU_SHIFT&t;&t;(32 - 5)
DECL|macro|ECSR_DEV_SHIFT
mdefine_line|#define ECSR_DEV_SHIFT&t;&t;(32 - 8)
DECL|macro|ECSR_BASE
mdefine_line|#define ECSR_BASE(cpu) ((cpu) &lt;&lt; ECSR_CPU_SHIFT)
DECL|macro|ECSR_DEV_BASE
mdefine_line|#define ECSR_DEV_BASE(devid) ((devid) &lt;&lt; ECSR_DEV_SHIFT) 
multiline_comment|/* Bus Watcher */
DECL|macro|BW_LOCAL_BASE
mdefine_line|#define BW_LOCAL_BASE&t;&t;0xfff00000
DECL|macro|BW_CID
mdefine_line|#define BW_CID&t;&t;&t;0x00000000
DECL|macro|BW_DBUS_CTRL
mdefine_line|#define BW_DBUS_CTRL&t;&t;0x00000008
DECL|macro|BW_DBUS_DATA
mdefine_line|#define BW_DBUS_DATA&t;&t;0x00000010
DECL|macro|BW_CTRL
mdefine_line|#define BW_CTRL&t;&t;&t;0x00001000
DECL|macro|BW_INTR_TABLE
mdefine_line|#define BW_INTR_TABLE&t;&t;0x00001040
DECL|macro|BW_INTR_TABLE_CLEAR
mdefine_line|#define BW_INTR_TABLE_CLEAR&t;0x00001080
DECL|macro|BW_PRESCALER
mdefine_line|#define BW_PRESCALER&t;&t;0x000010c0
DECL|macro|BW_PTIMER_LIMIT
mdefine_line|#define BW_PTIMER_LIMIT&t;&t;0x00002000
DECL|macro|BW_PTIMER_COUNTER2
mdefine_line|#define BW_PTIMER_COUNTER2&t;0x00002004
DECL|macro|BW_PTIMER_NDLIMIT
mdefine_line|#define BW_PTIMER_NDLIMIT&t;0x00002008
DECL|macro|BW_PTIMER_CTRL
mdefine_line|#define BW_PTIMER_CTRL&t;&t;0x0000200c
DECL|macro|BW_PTIMER_COUNTER
mdefine_line|#define BW_PTIMER_COUNTER&t;0x00002010
DECL|macro|BW_TIMER_LIMIT
mdefine_line|#define BW_TIMER_LIMIT&t;&t;0x00003000
DECL|macro|BW_TIMER_COUNTER2
mdefine_line|#define BW_TIMER_COUNTER2&t;0x00003004
DECL|macro|BW_TIMER_NDLIMIT
mdefine_line|#define BW_TIMER_NDLIMIT&t;0x00003008
DECL|macro|BW_TIMER_CTRL
mdefine_line|#define BW_TIMER_CTRL&t;&t;0x0000300c
DECL|macro|BW_TIMER_COUNTER
mdefine_line|#define BW_TIMER_COUNTER&t;0x00003010
multiline_comment|/* BW Control */
DECL|macro|BW_CTRL_USER_TIMER
mdefine_line|#define BW_CTRL_USER_TIMER&t;0x00000004&t;/* Is User Timer Free run enabled */
multiline_comment|/* Boot Bus */
DECL|macro|BB_LOCAL_BASE
mdefine_line|#define BB_LOCAL_BASE&t;&t;0xf0000000
DECL|macro|BB_STAT1
mdefine_line|#define BB_STAT1&t;&t;0x00100000
DECL|macro|BB_STAT2
mdefine_line|#define BB_STAT2&t;&t;0x00120000
DECL|macro|BB_STAT3
mdefine_line|#define BB_STAT3&t;&t;0x00140000
DECL|macro|BB_LEDS
mdefine_line|#define BB_LEDS&t;&t;&t;0x002e0000
multiline_comment|/* Bits in BB_STAT2 */
DECL|macro|BB_STAT2_AC_INTR
mdefine_line|#define BB_STAT2_AC_INTR&t;0x04&t;/* Aiee! 5ms and power is gone... */
DECL|macro|BB_STAT2_TMP_INTR
mdefine_line|#define BB_STAT2_TMP_INTR&t;0x10&t;/* My Penguins are burning. Are you able to smell it? */
DECL|macro|BB_STAT2_FAN_INTR
mdefine_line|#define BB_STAT2_FAN_INTR&t;0x20&t;/* My fan refuses to work */
DECL|macro|BB_STAT2_PWR_INTR
mdefine_line|#define BB_STAT2_PWR_INTR&t;0x40&t;/* On SC2000, one of the two ACs died. Ok, we go on... */
DECL|macro|BB_STAT2_MASK
mdefine_line|#define BB_STAT2_MASK&t;&t;(BB_STAT2_AC_INTR|BB_STAT2_TMP_INTR|BB_STAT2_FAN_INTR|BB_STAT2_PWR_INTR)
multiline_comment|/* Cache Controller */
DECL|macro|CC_BASE
mdefine_line|#define CC_BASE&t;&t;0x1F00000
DECL|macro|CC_DATSTREAM
mdefine_line|#define CC_DATSTREAM&t;0x1F00000  /* Data stream register */
DECL|macro|CC_DATSIZE
mdefine_line|#define CC_DATSIZE&t;0x1F0003F  /* Size */
DECL|macro|CC_SRCSTREAM
mdefine_line|#define CC_SRCSTREAM&t;0x1F00100  /* Source stream register */
DECL|macro|CC_DESSTREAM
mdefine_line|#define CC_DESSTREAM&t;0x1F00200  /* Destination stream register */
DECL|macro|CC_RMCOUNT
mdefine_line|#define CC_RMCOUNT&t;0x1F00300  /* Count of references and misses */
DECL|macro|CC_IPEN
mdefine_line|#define CC_IPEN&t;&t;0x1F00406  /* Pending Interrupts */
DECL|macro|CC_IMSK
mdefine_line|#define CC_IMSK&t;&t;0x1F00506  /* Interrupt Mask */
DECL|macro|CC_ICLR
mdefine_line|#define CC_ICLR&t;&t;0x1F00606  /* Clear pending Interrupts */
DECL|macro|CC_IGEN
mdefine_line|#define CC_IGEN&t;&t;0x1F00704  /* Generate Interrupt register */
DECL|macro|CC_STEST
mdefine_line|#define CC_STEST&t;0x1F00804  /* Internal self-test */
DECL|macro|CC_CREG
mdefine_line|#define CC_CREG&t;&t;0x1F00A04  /* Control register */
DECL|macro|CC_SREG
mdefine_line|#define CC_SREG&t;&t;0x1F00B00  /* Status register */
DECL|macro|CC_RREG
mdefine_line|#define CC_RREG&t;&t;0x1F00C04  /* Reset register */
DECL|macro|CC_EREG
mdefine_line|#define CC_EREG&t;&t;0x1F00E00  /* Error code register */
DECL|macro|CC_CID
mdefine_line|#define CC_CID&t;&t;0x1F00F04  /* Component ID */
macro_line|#ifndef __ASSEMBLY__
DECL|function|bw_get_intr_mask
r_extern
id|__inline__
r_int
id|bw_get_intr_mask
c_func
(paren
r_int
id|sbus_level
)paren
(brace
r_int
id|mask
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;lduha [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|BW_LOCAL_BASE
op_plus
id|BW_INTR_TABLE
op_plus
(paren
id|sbus_level
op_lshift
l_int|3
)paren
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|bw_clear_intr_mask
r_extern
id|__inline__
r_void
id|bw_clear_intr_mask
c_func
(paren
r_int
id|sbus_level
comma
r_int
id|mask
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;stha %0, [%1] %2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|BW_LOCAL_BASE
op_plus
id|BW_INTR_TABLE_CLEAR
op_plus
(paren
id|sbus_level
op_lshift
l_int|3
)paren
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
)brace
DECL|function|bw_get_prof_limit
r_extern
id|__inline__
r_int
id|bw_get_prof_limit
c_func
(paren
r_int
id|cpu
)paren
(brace
r_int
id|limit
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;lda [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|limit
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|CSR_BASE
c_func
(paren
id|cpu
)paren
op_plus
id|BW_PTIMER_LIMIT
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
r_return
id|limit
suffix:semicolon
)brace
DECL|function|bw_set_prof_limit
r_extern
id|__inline__
r_void
id|bw_set_prof_limit
c_func
(paren
r_int
id|cpu
comma
r_int
id|limit
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;sta %0, [%1] %2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|limit
)paren
comma
l_string|&quot;r&quot;
(paren
id|CSR_BASE
c_func
(paren
id|cpu
)paren
op_plus
id|BW_PTIMER_LIMIT
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
)brace
DECL|function|bw_get_ctrl
r_extern
id|__inline__
r_int
id|bw_get_ctrl
c_func
(paren
r_int
id|cpu
)paren
(brace
r_int
id|ctrl
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;lda [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ctrl
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|CSR_BASE
c_func
(paren
id|cpu
)paren
op_plus
id|BW_CTRL
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
r_return
id|ctrl
suffix:semicolon
)brace
DECL|function|bw_set_ctrl
r_extern
id|__inline__
r_void
id|bw_set_ctrl
c_func
(paren
r_int
id|cpu
comma
r_int
id|ctrl
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;sta %0, [%1] %2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|ctrl
)paren
comma
l_string|&quot;r&quot;
(paren
id|CSR_BASE
c_func
(paren
id|cpu
)paren
op_plus
id|BW_CTRL
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
)brace
r_extern
r_int
r_char
id|cpu_leds
(braket
l_int|32
)braket
suffix:semicolon
DECL|function|show_leds
r_extern
id|__inline__
r_void
id|show_leds
c_func
(paren
r_int
id|cpuid
)paren
(brace
id|cpuid
op_and_assign
l_int|0x1e
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;stba %0, [%1] %2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
id|cpu_leds
(braket
id|cpuid
)braket
op_lshift
l_int|4
)paren
op_or
id|cpu_leds
(braket
id|cpuid
op_plus
l_int|1
)braket
)paren
comma
l_string|&quot;r&quot;
(paren
id|ECSR_BASE
c_func
(paren
id|cpuid
)paren
op_or
id|BB_LEDS
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
)brace
DECL|function|cc_get_ipen
r_extern
id|__inline__
r_int
id|cc_get_ipen
c_func
(paren
r_void
)paren
(brace
r_int
id|pending
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;lduha [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|pending
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|CC_IPEN
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MXCC
)paren
)paren
suffix:semicolon
r_return
id|pending
suffix:semicolon
)brace
DECL|function|cc_set_iclr
r_extern
id|__inline__
r_void
id|cc_set_iclr
c_func
(paren
r_int
id|clear
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;stha %0, [%1] %2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|clear
)paren
comma
l_string|&quot;r&quot;
(paren
id|CC_ICLR
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MXCC
)paren
)paren
suffix:semicolon
)brace
DECL|function|cc_get_imsk
r_extern
id|__inline__
r_int
id|cc_get_imsk
c_func
(paren
r_void
)paren
(brace
r_int
id|mask
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;lduha [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|CC_IMSK
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MXCC
)paren
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|cc_set_imsk
r_extern
id|__inline__
r_void
id|cc_set_imsk
c_func
(paren
r_int
id|mask
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;stha %0, [%1] %2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|CC_IMSK
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MXCC
)paren
)paren
suffix:semicolon
)brace
DECL|function|cc_get_imsk_other
r_extern
id|__inline__
r_int
id|cc_get_imsk_other
c_func
(paren
r_int
id|cpuid
)paren
(brace
r_int
id|mask
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;lduha [%1] %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ECSR_BASE
c_func
(paren
id|cpuid
)paren
op_or
id|CC_IMSK
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|cc_set_imsk_other
r_extern
id|__inline__
r_void
id|cc_set_imsk_other
c_func
(paren
r_int
id|cpuid
comma
r_int
id|mask
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;stha %0, [%1] %2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|mask
)paren
comma
l_string|&quot;r&quot;
(paren
id|ECSR_BASE
c_func
(paren
id|cpuid
)paren
op_or
id|CC_IMSK
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_CTL
)paren
)paren
suffix:semicolon
)brace
DECL|function|cc_set_igen
r_extern
id|__inline__
r_void
id|cc_set_igen
c_func
(paren
r_int
id|gen
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;sta %0, [%1] %2&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|gen
)paren
comma
l_string|&quot;r&quot;
(paren
id|CC_IGEN
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_MXCC
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* +-------+-------------+-----------+------------------------------------+&n; * | bcast |  devid      |   sid     |              levels mask           |&n; * +-------+-------------+-----------+------------------------------------+&n; *  31      30         23 22       15 14                                 0&n; */
DECL|macro|IGEN_MESSAGE
mdefine_line|#define IGEN_MESSAGE(bcast, devid, sid, levels) &bslash;&n;&t;(((bcast) &lt;&lt; 31) | ((devid) &lt;&lt; 23) | ((sid) &lt;&lt; 15) | (levels))
DECL|function|sun4d_send_ipi
r_extern
id|__inline__
r_void
id|sun4d_send_ipi
c_func
(paren
r_int
id|cpu
comma
r_int
id|level
)paren
(brace
id|cc_set_igen
c_func
(paren
id|IGEN_MESSAGE
c_func
(paren
l_int|0
comma
id|cpu
op_lshift
l_int|3
comma
l_int|6
op_plus
(paren
(paren
id|level
op_rshift
l_int|1
)paren
op_amp
l_int|7
)paren
comma
l_int|1
op_lshift
(paren
id|level
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* !(_SPARC_OBIO_H) */
eof
