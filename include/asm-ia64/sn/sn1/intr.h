multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_SN1_INTR_H
DECL|macro|_ASM_IA64_SN_SN1_INTR_H
mdefine_line|#define _ASM_IA64_SN_SN1_INTR_H
multiline_comment|/* Subnode wildcard */
DECL|macro|SUBNODE_ANY
mdefine_line|#define SUBNODE_ANY&t;&t;(-1)
multiline_comment|/* Number of interrupt levels associated with each interrupt register. */
DECL|macro|N_INTPEND_BITS
mdefine_line|#define N_INTPEND_BITS&t;&t;64
DECL|macro|INT_PEND0_BASELVL
mdefine_line|#define INT_PEND0_BASELVL&t;0
DECL|macro|INT_PEND1_BASELVL
mdefine_line|#define INT_PEND1_BASELVL&t;64
DECL|macro|N_INTPENDJUNK_BITS
mdefine_line|#define&t;N_INTPENDJUNK_BITS&t;8
DECL|macro|INTPENDJUNK_CLRBIT
mdefine_line|#define&t;INTPENDJUNK_CLRBIT&t;0x80
macro_line|#include &lt;asm/sn/intr_public.h&gt;
macro_line|#include &lt;asm/sn/driver.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalk.h&gt;
macro_line|#include &lt;asm/sn/hack.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|macro|II_NAMELEN
mdefine_line|#define II_NAMELEN&t;24
multiline_comment|/*&n; * Dispatch table entry - contains information needed to call an interrupt&n; * routine.&n; */
DECL|struct|intr_vector_s
r_typedef
r_struct
id|intr_vector_s
(brace
DECL|member|iv_func
id|intr_func_t
id|iv_func
suffix:semicolon
multiline_comment|/* Interrupt handler function */
DECL|member|iv_prefunc
id|intr_func_t
id|iv_prefunc
suffix:semicolon
multiline_comment|/* Interrupt handler prologue func */
DECL|member|iv_arg
r_void
op_star
id|iv_arg
suffix:semicolon
multiline_comment|/* Argument to pass to handler */
DECL|member|iv_mustruncpu
id|cpuid_t
id|iv_mustruncpu
suffix:semicolon
multiline_comment|/* Where we must run. */
DECL|typedef|intr_vector_t
)brace
id|intr_vector_t
suffix:semicolon
multiline_comment|/* Interrupt information table. */
DECL|struct|intr_info_s
r_typedef
r_struct
id|intr_info_s
(brace
DECL|member|ii_setfunc
id|xtalk_intr_setfunc_t
id|ii_setfunc
suffix:semicolon
multiline_comment|/* Function to set the interrupt&n;&t;&t;&t;&t;&t;&t; * destination and level register.&n;&t;&t;&t;&t;&t;&t; * It returns 0 (success) or an&n;&t;&t;&t;&t;&t;&t; * error code.&n;&t;&t;&t;&t;&t;&t; */
DECL|member|ii_cookie
r_void
op_star
id|ii_cookie
suffix:semicolon
multiline_comment|/* arg passed to setfunc */
DECL|member|ii_owner_dev
id|devfs_handle_t
id|ii_owner_dev
suffix:semicolon
multiline_comment|/* device that owns this intr */
DECL|member|ii_name
r_char
id|ii_name
(braket
id|II_NAMELEN
)braket
suffix:semicolon
multiline_comment|/* Name of this intr. */
DECL|member|ii_flags
r_int
id|ii_flags
suffix:semicolon
multiline_comment|/* informational flags */
DECL|typedef|intr_info_t
)brace
id|intr_info_t
suffix:semicolon
DECL|macro|THD_CREATED
mdefine_line|#define THD_CREATED&t;0x00000001&t;/*&n;&t;&t;&t;&t;&t; * We&squot;ve created a thread for this&n;&t;&t;&t;&t;&t; * interrupt.&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n; * Bits for ii_flags:&n; */
DECL|macro|II_UNRESERVE
mdefine_line|#define II_UNRESERVE&t;0
DECL|macro|II_RESERVE
mdefine_line|#define II_RESERVE&t;1&t;&t;/* Interrupt reserved. &t;&t;&t;*/
DECL|macro|II_INUSE
mdefine_line|#define II_INUSE&t;2&t;&t;/* Interrupt connected &t;&t;&t;*/
DECL|macro|II_ERRORINT
mdefine_line|#define II_ERRORINT&t;4&t;&t;/* INterrupt is an error condition &t;*/
DECL|macro|II_THREADED
mdefine_line|#define II_THREADED&t;8&t;&t;/* Interrupt handler is threaded.&t;*/
multiline_comment|/*&n; * Interrupt level wildcard&n; */
DECL|macro|INTRCONNECT_ANYBIT
mdefine_line|#define INTRCONNECT_ANYBIT&t;(-1)
multiline_comment|/*&n; * This structure holds information needed both to call and to maintain&n; * interrupts.  The two are in separate arrays for the locality benefits.&n; * Since there&squot;s only one set of vectors per hub chip (but more than one&n; * CPU, the lock to change the vector tables must be here rather than in&n; * the PDA.&n; */
DECL|struct|intr_vecblk_s
r_typedef
r_struct
id|intr_vecblk_s
(brace
DECL|member|vectors
id|intr_vector_t
id|vectors
(braket
id|N_INTPEND_BITS
)braket
suffix:semicolon
multiline_comment|/* information needed to&n;&t;&t;&t;&t;&t;&t;     call an intr routine. */
DECL|member|info
id|intr_info_t
id|info
(braket
id|N_INTPEND_BITS
)braket
suffix:semicolon
multiline_comment|/* information needed only&n;&t;&t;&t;&t;&t;&t;     to maintain interrupts. */
DECL|member|vector_lock
id|spinlock_t
id|vector_lock
suffix:semicolon
multiline_comment|/* Lock for this and the&n;&t;&t;&t;&t;&t;&t;     masks in the PDA. */
DECL|member|vector_spl
id|splfunc_t
id|vector_spl
suffix:semicolon
multiline_comment|/* vector_lock req&squot;d spl */
DECL|member|vector_state
r_int
id|vector_state
suffix:semicolon
multiline_comment|/* Initialized to zero.&n;&t;&t;&t;&t;&t;&t;     Set to INTR_INITED&n;&t;&t;&t;&t;&t;&t;     by hubintr_init.&n;&t;&t;&t;&t;&t;&t;   */
DECL|member|vector_count
r_int
id|vector_count
suffix:semicolon
multiline_comment|/* Number of vectors&n;&t;&t;&t;&t;&t;&t;   * reserved.&n;&t;&t;&t;&t;&t;&t;   */
DECL|member|cpu_count
r_int
id|cpu_count
(braket
id|CPUS_PER_SUBNODE
)braket
suffix:semicolon
multiline_comment|/* How many interrupts are&n;&t;&t;&t;&t;&t;&t;   * connected to each CPU&n;&t;&t;&t;&t;&t;&t;   */
DECL|member|ithreads_enabled
r_int
id|ithreads_enabled
suffix:semicolon
multiline_comment|/* Are interrupt threads&n;&t;&t;&t;&t;&t;&t;   * initialized on this node.&n;&t;&t;&t;&t;&t;&t;   * and block?&n;&t;&t;&t;&t;&t;&t;   */
DECL|typedef|intr_vecblk_t
)brace
id|intr_vecblk_t
suffix:semicolon
multiline_comment|/* Possible values for vector_state: */
DECL|macro|VECTOR_UNINITED
mdefine_line|#define VECTOR_UNINITED&t;0
DECL|macro|VECTOR_INITED
mdefine_line|#define VECTOR_INITED&t;1
DECL|macro|VECTOR_SET
mdefine_line|#define VECTOR_SET&t;2
DECL|macro|hub_intrvect0
mdefine_line|#define hub_intrvect0&t;private.p_intmasks.dispatch0-&gt;vectors
DECL|macro|hub_intrvect1
mdefine_line|#define hub_intrvect1&t;private.p_intmasks.dispatch1-&gt;vectors
DECL|macro|hub_intrinfo0
mdefine_line|#define hub_intrinfo0&t;private.p_intmasks.dispatch0-&gt;info
DECL|macro|hub_intrinfo1
mdefine_line|#define hub_intrinfo1&t;private.p_intmasks.dispatch1-&gt;info
multiline_comment|/*&n; * Macros to manipulate the interrupt register on the calling hub chip.&n; */
DECL|macro|LOCAL_HUB_SEND_INTR
mdefine_line|#define LOCAL_HUB_SEND_INTR(_level)&t;LOCAL_HUB_S(PI_INT_PEND_MOD, &bslash;&n;&t;&t;&t;&t;&t;&t;    (0x100|(_level)))
DECL|macro|REMOTE_HUB_PI_SEND_INTR
mdefine_line|#define REMOTE_HUB_PI_SEND_INTR(_hub, _sn, _level) &bslash;&n;&t;&t;REMOTE_HUB_PI_S((_hub), _sn, PI_INT_PEND_MOD, (0x100|(_level)))
DECL|macro|REMOTE_CPU_SEND_INTR
mdefine_line|#define REMOTE_CPU_SEND_INTR(_cpuid, _level) &t;&t;&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_PI_S(cpuid_to_nasid(_cpuid),&t;&t;&t;&t;&bslash;&n;&t;&t;&t;SUBNODE(cpuid_to_slice(_cpuid)),&t;&t;&t;&t;&bslash;&n;&t;&t;&t;PI_INT_PEND_MOD, (0x100|(_level)))
multiline_comment|/*&n; * When clearing the interrupt, make sure this clear does make it &n; * to the hub. Otherwise we could end up losing interrupts.&n; * We do an uncached load of the int_pend0 register to ensure this.&n; */
DECL|macro|LOCAL_HUB_CLR_INTR
mdefine_line|#define LOCAL_HUB_CLR_INTR(_level)&t;  &bslash;&n;                LOCAL_HUB_S(PI_INT_PEND_MOD, (_level)),&t;&bslash;&n;                LOCAL_HUB_L(PI_INT_PEND0)
DECL|macro|REMOTE_HUB_PI_CLR_INTR
mdefine_line|#define REMOTE_HUB_PI_CLR_INTR(_hub, _sn, _level) &bslash;&n;&t;&t;REMOTE_HUB_PI_S((_hub), (_sn), PI_INT_PEND_MOD, (_level)),&t;&bslash;&n;                REMOTE_HUB_PI_L((_hub), (_sn), PI_INT_PEND0)
multiline_comment|/* Special support for use by gfx driver only.  Supports special gfx hub interrupt. */
r_extern
r_void
id|install_gfxintr
c_func
(paren
id|cpuid_t
id|cpu
comma
id|ilvl_t
id|swlevel
comma
id|intr_func_t
id|intr_func
comma
r_void
op_star
id|intr_arg
)paren
suffix:semicolon
r_void
id|setrtvector
c_func
(paren
id|intr_func_t
id|func
)paren
suffix:semicolon
multiline_comment|/*&n; * Interrupt blocking&n; */
r_extern
r_void
id|intr_block_bit
c_func
(paren
id|cpuid_t
id|cpu
comma
r_int
id|bit
)paren
suffix:semicolon
r_extern
r_void
id|intr_unblock_bit
c_func
(paren
id|cpuid_t
id|cpu
comma
r_int
id|bit
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * Hard-coded interrupt levels:&n; */
multiline_comment|/*&n; *&t;L0 = SW1&n; *&t;L1 = SW2&n; *&t;L2 = INT_PEND0&n; *&t;L3 = INT_PEND1&n; *&t;L4 = RTC&n; *&t;L5 = Profiling Timer&n; *&t;L6 = Hub Errors&n; *&t;L7 = Count/Compare (T5 counters)&n; */
multiline_comment|/* INT_PEND0 hard-coded bits. */
macro_line|#ifdef DEBUG_INTR_TSTAMP
multiline_comment|/* hard coded interrupt level for interrupt latency test interrupt */
DECL|macro|CPU_INTRLAT_B
mdefine_line|#define&t;CPU_INTRLAT_B&t;62
DECL|macro|CPU_INTRLAT_A
mdefine_line|#define&t;CPU_INTRLAT_A&t;61
macro_line|#endif
multiline_comment|/* Hardcoded bits required by software. */
DECL|macro|MSC_MESG_INTR
mdefine_line|#define MSC_MESG_INTR&t;9
DECL|macro|CPU_ACTION_B
mdefine_line|#define CPU_ACTION_B&t;8
DECL|macro|CPU_ACTION_A
mdefine_line|#define CPU_ACTION_A&t;7
multiline_comment|/* These are determined by hardware: */
DECL|macro|CC_PEND_B
mdefine_line|#define CC_PEND_B&t;6
DECL|macro|CC_PEND_A
mdefine_line|#define CC_PEND_A&t;5
DECL|macro|UART_INTR
mdefine_line|#define UART_INTR&t;4
DECL|macro|PG_MIG_INTR
mdefine_line|#define PG_MIG_INTR&t;3
DECL|macro|GFX_INTR_B
mdefine_line|#define GFX_INTR_B&t;2
DECL|macro|GFX_INTR_A
mdefine_line|#define GFX_INTR_A&t;1
DECL|macro|RESERVED_INTR
mdefine_line|#define RESERVED_INTR&t;0
multiline_comment|/* INT_PEND1 hard-coded bits: */
DECL|macro|MSC_PANIC_INTR
mdefine_line|#define MSC_PANIC_INTR&t;63
DECL|macro|NI_ERROR_INTR
mdefine_line|#define NI_ERROR_INTR&t;62
DECL|macro|MD_COR_ERR_INTR
mdefine_line|#define MD_COR_ERR_INTR&t;61
DECL|macro|COR_ERR_INTR_B
mdefine_line|#define COR_ERR_INTR_B&t;60
DECL|macro|COR_ERR_INTR_A
mdefine_line|#define COR_ERR_INTR_A&t;59
DECL|macro|CLK_ERR_INTR
mdefine_line|#define CLK_ERR_INTR&t;58
DECL|macro|NACK_INT_B
macro_line|# define NACK_INT_B&t;57
DECL|macro|NACK_INT_A
macro_line|# define NACK_INT_A&t;56
DECL|macro|LB_ERROR
macro_line|# define LB_ERROR&t;55
DECL|macro|XB_ERROR
macro_line|# define XB_ERROR&t;54
DECL|macro|BRIDGE_ERROR_INTR
mdefine_line|#define BRIDGE_ERROR_INTR 53&t;/* Setup by PROM to catch Bridge Errors */
DECL|macro|IP27_INTR_0
mdefine_line|#define IP27_INTR_0&t;52&t;/* Reserved for PROM use */
DECL|macro|IP27_INTR_1
mdefine_line|#define IP27_INTR_1&t;51&t;/*   (do not use in Kernel) */
DECL|macro|IP27_INTR_2
mdefine_line|#define IP27_INTR_2&t;50
DECL|macro|IP27_INTR_3
mdefine_line|#define IP27_INTR_3&t;49
DECL|macro|IP27_INTR_4
mdefine_line|#define IP27_INTR_4&t;48
DECL|macro|IP27_INTR_5
mdefine_line|#define IP27_INTR_5&t;47
DECL|macro|IP27_INTR_6
mdefine_line|#define IP27_INTR_6&t;46
DECL|macro|IP27_INTR_7
mdefine_line|#define IP27_INTR_7&t;45
DECL|macro|TLB_INTR_B
mdefine_line|#define&t;TLB_INTR_B&t;44&t;/* used for tlb flush random */
DECL|macro|TLB_INTR_A
mdefine_line|#define&t;TLB_INTR_A&t;43
DECL|macro|LLP_PFAIL_INTR_B
mdefine_line|#define LLP_PFAIL_INTR_B 42&t;/* see ml/SN/SN0/sysctlr.c */
DECL|macro|LLP_PFAIL_INTR_A
mdefine_line|#define LLP_PFAIL_INTR_A 41
DECL|macro|NI_BRDCAST_ERR_B
mdefine_line|#define NI_BRDCAST_ERR_B 40
DECL|macro|NI_BRDCAST_ERR_A
mdefine_line|#define NI_BRDCAST_ERR_A 39
DECL|macro|IO_ERROR_INTR
macro_line|# define IO_ERROR_INTR&t;38&t;/* set up by prom */
DECL|macro|DEBUG_INTR_B
macro_line|# define DEBUG_INTR_B&t;37&t;/* used by symmon to stop all cpus */
DECL|macro|DEBUG_INTR_A
macro_line|# define DEBUG_INTR_A&t;36
singleline_comment|// These aren&squot;t strictly accurate or complete.  See the
singleline_comment|// Synergy Spec. for details.
DECL|macro|SGI_UART_IRQ
mdefine_line|#define SGI_UART_IRQ&t;(65)
DECL|macro|SGI_HUB_ERROR_IRQ
mdefine_line|#define SGI_HUB_ERROR_IRQ&t;(182)
macro_line|#endif /* _ASM_IA64_SN_SN1_INTR_H */
eof
