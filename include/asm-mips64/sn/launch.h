multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_LAUNCH_H
DECL|macro|_ASM_SN_LAUNCH_H
mdefine_line|#define _ASM_SN_LAUNCH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
multiline_comment|/*&n; * The launch data structure resides at a fixed place in each node&squot;s memory&n; * and is used to communicate between the master processor and the slave&n; * processors.&n; *&n; * The master stores launch parameters in the launch structure&n; * corresponding to a target processor that is in a slave loop, then sends&n; * an interrupt to the slave processor.  The slave calls the desired&n; * function, then returns to the slave loop.  The master may poll or wait&n; * for the slaves to finish.&n; *&n; * There is an array of launch structures, one per CPU on the node.  One&n; * interrupt level is used per local CPU.&n; */
DECL|macro|LAUNCH_MAGIC
mdefine_line|#define LAUNCH_MAGIC&t;&t;0xaddbead2addbead3
macro_line|#ifdef CONFIG_SGI_IP27
DECL|macro|LAUNCH_SIZEOF
mdefine_line|#define LAUNCH_SIZEOF&t;&t;0x100
DECL|macro|LAUNCH_PADSZ
mdefine_line|#define LAUNCH_PADSZ&t;&t;0xa0
macro_line|#endif
DECL|macro|LAUNCH_OFF_MAGIC
mdefine_line|#define LAUNCH_OFF_MAGIC&t;0x00&t;/* Struct offsets for assembly      */
DECL|macro|LAUNCH_OFF_BUSY
mdefine_line|#define LAUNCH_OFF_BUSY&t;&t;0x08
DECL|macro|LAUNCH_OFF_CALL
mdefine_line|#define LAUNCH_OFF_CALL&t;&t;0x10
DECL|macro|LAUNCH_OFF_CALLC
mdefine_line|#define LAUNCH_OFF_CALLC&t;0x18
DECL|macro|LAUNCH_OFF_CALLPARM
mdefine_line|#define LAUNCH_OFF_CALLPARM&t;0x20
DECL|macro|LAUNCH_OFF_STACK
mdefine_line|#define LAUNCH_OFF_STACK&t;0x28
DECL|macro|LAUNCH_OFF_GP
mdefine_line|#define LAUNCH_OFF_GP&t;&t;0x30
DECL|macro|LAUNCH_OFF_BEVUTLB
mdefine_line|#define LAUNCH_OFF_BEVUTLB&t;0x38
DECL|macro|LAUNCH_OFF_BEVNORMAL
mdefine_line|#define LAUNCH_OFF_BEVNORMAL&t;0x40
DECL|macro|LAUNCH_OFF_BEVECC
mdefine_line|#define LAUNCH_OFF_BEVECC&t;0x48
DECL|macro|LAUNCH_STATE_DONE
mdefine_line|#define LAUNCH_STATE_DONE&t;0&t;/* Return value of LAUNCH_POLL      */
DECL|macro|LAUNCH_STATE_SENT
mdefine_line|#define LAUNCH_STATE_SENT&t;1
DECL|macro|LAUNCH_STATE_RECD
mdefine_line|#define LAUNCH_STATE_RECD&t;2
multiline_comment|/*&n; * The launch routine is called only if the complement address is correct.&n; *&n; * Before control is transferred to a routine, the compliment address&n; * is zeroed (invalidated) to prevent an accidental call from a spurious&n; * interrupt.&n; *&n; * The slave_launch routine turns on the BUSY flag, and the slave loop&n; * clears the BUSY flag after control is returned to it.&n; */
macro_line|#ifdef _LANGUAGE_C
DECL|typedef|launch_state_t
r_typedef
r_int
id|launch_state_t
suffix:semicolon
DECL|typedef|launch_proc_t
r_typedef
r_void
(paren
op_star
id|launch_proc_t
)paren
(paren
id|u64
id|call_parm
)paren
suffix:semicolon
DECL|struct|launch_s
r_typedef
r_struct
id|launch_s
(brace
DECL|member|magic
r_volatile
id|u64
id|magic
suffix:semicolon
multiline_comment|/* Magic number                     */
DECL|member|busy
r_volatile
id|u64
id|busy
suffix:semicolon
multiline_comment|/* Slave currently active           */
DECL|member|call_addr
r_volatile
id|launch_proc_t
id|call_addr
suffix:semicolon
multiline_comment|/* Func. for slave to call  */
DECL|member|call_addr_c
r_volatile
id|u64
id|call_addr_c
suffix:semicolon
multiline_comment|/* 1&squot;s complement of call_addr*/
DECL|member|call_parm
r_volatile
id|u64
id|call_parm
suffix:semicolon
multiline_comment|/* Single parm passed to call*/
DECL|member|stack_addr
r_volatile
r_void
op_star
id|stack_addr
suffix:semicolon
multiline_comment|/* Stack pointer for slave function */
DECL|member|gp_addr
r_volatile
r_void
op_star
id|gp_addr
suffix:semicolon
multiline_comment|/* Global pointer for slave func.   */
DECL|member|bevutlb
r_volatile
r_char
op_star
id|bevutlb
suffix:semicolon
multiline_comment|/* Address of bev utlb ex handler   */
DECL|member|bevnormal
r_volatile
r_char
op_star
id|bevnormal
suffix:semicolon
multiline_comment|/*Address of bev normal ex handler */
DECL|member|bevecc
r_volatile
r_char
op_star
id|bevecc
suffix:semicolon
multiline_comment|/* Address of bev cache err handler */
DECL|member|pad
r_volatile
r_char
id|pad
(braket
l_int|160
)braket
suffix:semicolon
multiline_comment|/* Pad to LAUNCH_SIZEOF&t;    */
DECL|typedef|launch_t
)brace
id|launch_t
suffix:semicolon
multiline_comment|/*&n; * PROM entry points for launch routines are determined by IPxxprom/start.s&n; */
DECL|macro|LAUNCH_SLAVE
mdefine_line|#define LAUNCH_SLAVE&t;(*(void (*)(int nasid, int cpu, &bslash;&n;&t;&t;&t;&t;    launch_proc_t call_addr, &bslash;&n;&t;&t;&t;&t;    u64 call_parm, &bslash;&n;&t;&t;&t;&t;    void *stack_addr, &bslash;&n;&t;&t;&t;&t;    void *gp_addr)) &bslash;&n;&t;&t;&t; IP27PROM_LAUNCHSLAVE)
DECL|macro|LAUNCH_WAIT
mdefine_line|#define LAUNCH_WAIT&t;(*(void (*)(int nasid, int cpu, int timeout_msec)) &bslash;&n;&t;&t;&t; IP27PROM_WAITSLAVE)
DECL|macro|LAUNCH_POLL
mdefine_line|#define LAUNCH_POLL&t;(*(launch_state_t (*)(int nasid, int cpu)) &bslash;&n;&t;&t;&t; IP27PROM_POLLSLAVE)
DECL|macro|LAUNCH_LOOP
mdefine_line|#define LAUNCH_LOOP&t;(*(void (*)(void)) &bslash;&n;&t;&t;&t; IP27PROM_SLAVELOOP)
DECL|macro|LAUNCH_FLASH
mdefine_line|#define LAUNCH_FLASH&t;(*(void (*)(void)) &bslash;&n;&t;&t;&t; IP27PROM_FLASHLEDS)
macro_line|#ifdef _STANDALONE
id|launch_t
op_star
id|launch_get
c_func
(paren
r_int
id|nasid
comma
r_int
id|cpu
)paren
suffix:semicolon
id|launch_t
op_star
id|launch_get_current
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|launch_loop
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|launch_slave
c_func
(paren
r_int
id|nasid
comma
r_int
id|cpu
comma
id|launch_proc_t
id|call_addr
comma
id|__int64_t
id|call_parm
comma
r_void
op_star
id|stack_addr
comma
r_void
op_star
id|gp_addr
)paren
suffix:semicolon
r_int
id|launch_wait
c_func
(paren
r_int
id|nasid
comma
r_int
id|cpu
comma
r_int
id|timeout_msec
)paren
suffix:semicolon
id|launch_state_t
id|launch_poll
c_func
(paren
r_int
id|nasid
comma
r_int
id|cpu
)paren
suffix:semicolon
macro_line|#endif /* _STANDALONE */
macro_line|#endif /* _LANGUAGE_C */
macro_line|#endif /* _ASM_SN_LAUNCH_H */
eof
