macro_line|#ifndef __PPCDEBUG_H
DECL|macro|__PPCDEBUG_H
mdefine_line|#define __PPCDEBUG_H
multiline_comment|/********************************************************************&n; * Author: Adam Litke, IBM Corp&n; * (c) 2001&n; *&n; * This file contains definitions and macros for a runtime debugging&n; * system for ppc64 (This should also work on 32 bit with a few    &n; * adjustments.                                                   &n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; ********************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/udbg.h&gt;
macro_line|#include &lt;stdarg.h&gt;
DECL|macro|PPCDBG_BITVAL
mdefine_line|#define PPCDBG_BITVAL(X)     ((1UL)&lt;&lt;((unsigned long)(X)))
multiline_comment|/* Defined below are the bit positions of various debug flags in the&n; * debug_switch variable (defined in naca.h).&n; * -- When adding new values, please enter them into trace names below -- &n; *&n; * Values 62 &amp; 63 can be used to stress the hardware page table management&n; * code.  They must be set statically, any attempt to change them dynamically&n; * would be a very bad idea.&n; */
DECL|macro|PPCDBG_MMINIT
mdefine_line|#define PPCDBG_MMINIT        PPCDBG_BITVAL(0)
DECL|macro|PPCDBG_MM
mdefine_line|#define PPCDBG_MM            PPCDBG_BITVAL(1)
DECL|macro|PPCDBG_SYS32
mdefine_line|#define PPCDBG_SYS32         PPCDBG_BITVAL(2)
DECL|macro|PPCDBG_SYS32NI
mdefine_line|#define PPCDBG_SYS32NI       PPCDBG_BITVAL(3)
DECL|macro|PPCDBG_SYS32X
mdefine_line|#define PPCDBG_SYS32X&t;     PPCDBG_BITVAL(4)
DECL|macro|PPCDBG_SYS32M
mdefine_line|#define PPCDBG_SYS32M&t;     PPCDBG_BITVAL(5)
DECL|macro|PPCDBG_SYS64
mdefine_line|#define PPCDBG_SYS64         PPCDBG_BITVAL(6)
DECL|macro|PPCDBG_SYS64NI
mdefine_line|#define PPCDBG_SYS64NI       PPCDBG_BITVAL(7)
DECL|macro|PPCDBG_SYS64X
mdefine_line|#define PPCDBG_SYS64X&t;     PPCDBG_BITVAL(8)
DECL|macro|PPCDBG_SIGNAL
mdefine_line|#define PPCDBG_SIGNAL        PPCDBG_BITVAL(9)
DECL|macro|PPCDBG_SIGNALXMON
mdefine_line|#define PPCDBG_SIGNALXMON    PPCDBG_BITVAL(10)
DECL|macro|PPCDBG_BINFMT32
mdefine_line|#define PPCDBG_BINFMT32      PPCDBG_BITVAL(11)
DECL|macro|PPCDBG_BINFMT64
mdefine_line|#define PPCDBG_BINFMT64      PPCDBG_BITVAL(12)
DECL|macro|PPCDBG_BINFMTXMON
mdefine_line|#define PPCDBG_BINFMTXMON    PPCDBG_BITVAL(13)
DECL|macro|PPCDBG_BINFMT_32ADDR
mdefine_line|#define PPCDBG_BINFMT_32ADDR PPCDBG_BITVAL(14)
DECL|macro|PPCDBG_ALIGNFIXUP
mdefine_line|#define PPCDBG_ALIGNFIXUP    PPCDBG_BITVAL(15)
DECL|macro|PPCDBG_TCEINIT
mdefine_line|#define PPCDBG_TCEINIT       PPCDBG_BITVAL(16)
DECL|macro|PPCDBG_TCE
mdefine_line|#define PPCDBG_TCE           PPCDBG_BITVAL(17)
DECL|macro|PPCDBG_PHBINIT
mdefine_line|#define PPCDBG_PHBINIT       PPCDBG_BITVAL(18)
DECL|macro|PPCDBG_SMP
mdefine_line|#define PPCDBG_SMP           PPCDBG_BITVAL(19)
DECL|macro|PPCDBG_BOOT
mdefine_line|#define PPCDBG_BOOT          PPCDBG_BITVAL(20)
DECL|macro|PPCDBG_BUSWALK
mdefine_line|#define PPCDBG_BUSWALK       PPCDBG_BITVAL(21)
DECL|macro|PPCDBG_HTABSTRESS
mdefine_line|#define PPCDBG_HTABSTRESS    PPCDBG_BITVAL(62)
DECL|macro|PPCDBG_HTABSIZE
mdefine_line|#define PPCDBG_HTABSIZE      PPCDBG_BITVAL(63)
DECL|macro|PPCDBG_NONE
mdefine_line|#define PPCDBG_NONE          (0UL)
DECL|macro|PPCDBG_ALL
mdefine_line|#define PPCDBG_ALL           (0xffffffffUL)
multiline_comment|/* The default initial value for the debug switch */
DECL|macro|PPC_DEBUG_DEFAULT
mdefine_line|#define PPC_DEBUG_DEFAULT    0 
multiline_comment|/* #define PPC_DEBUG_DEFAULT    PPCDBG_ALL        */
DECL|macro|PPCDBG_NUM_FLAGS
mdefine_line|#define PPCDBG_NUM_FLAGS     64
macro_line|#ifdef WANT_PPCDBG_TAB
multiline_comment|/* A table of debug switch names to allow name lookup in xmon &n; * (and whoever else wants it.&n; */
DECL|variable|trace_names
r_char
op_star
id|trace_names
(braket
id|PPCDBG_NUM_FLAGS
)braket
op_assign
(brace
multiline_comment|/* Known debug names */
l_string|&quot;mminit&quot;
comma
l_string|&quot;mm&quot;
comma
l_string|&quot;syscall32&quot;
comma
l_string|&quot;syscall32_ni&quot;
comma
l_string|&quot;syscall32x&quot;
comma
l_string|&quot;syscall32m&quot;
comma
l_string|&quot;syscall64&quot;
comma
l_string|&quot;syscall64_ni&quot;
comma
l_string|&quot;syscall64x&quot;
comma
l_string|&quot;signal&quot;
comma
l_string|&quot;signal_xmon&quot;
comma
l_string|&quot;binfmt32&quot;
comma
l_string|&quot;binfmt64&quot;
comma
l_string|&quot;binfmt_xmon&quot;
comma
l_string|&quot;binfmt_32addr&quot;
comma
l_string|&quot;alignfixup&quot;
comma
l_string|&quot;tceinit&quot;
comma
l_string|&quot;tce&quot;
comma
l_string|&quot;phb_init&quot;
comma
l_string|&quot;smp&quot;
comma
l_string|&quot;boot&quot;
comma
l_string|&quot;buswalk&quot;
)brace
suffix:semicolon
macro_line|#else
r_extern
r_char
op_star
id|trace_names
(braket
l_int|64
)braket
suffix:semicolon
macro_line|#endif /* WANT_PPCDBG_TAB */
macro_line|#ifdef CONFIG_PPCDBG
multiline_comment|/* Macro to conditionally print debug based on debug_switch */
DECL|macro|PPCDBG
mdefine_line|#define PPCDBG(...) udbg_ppcdbg(__VA_ARGS__)
multiline_comment|/* Macro to conditionally call a debug routine based on debug_switch */
DECL|macro|PPCDBGCALL
mdefine_line|#define PPCDBGCALL(FLAGS,FUNCTION) ifppcdebug(FLAGS) FUNCTION
multiline_comment|/* Macros to test for debug states */
DECL|macro|ifppcdebug
mdefine_line|#define ifppcdebug(FLAGS) if (udbg_ifdebug(FLAGS))
DECL|macro|ppcdebugset
mdefine_line|#define ppcdebugset(FLAGS) (udbg_ifdebug(FLAGS))
DECL|macro|PPCDBG_BINFMT
mdefine_line|#define PPCDBG_BINFMT (test_thread_flag(TIF_32BIT) ? PPCDBG_BINFMT32 : PPCDBG_BINFMT64)
macro_line|#ifdef CONFIG_XMON
DECL|macro|PPCDBG_ENTER_DEBUGGER
mdefine_line|#define PPCDBG_ENTER_DEBUGGER() xmon(0)
DECL|macro|PPCDBG_ENTER_DEBUGGER_REGS
mdefine_line|#define PPCDBG_ENTER_DEBUGGER_REGS(X) xmon(X)
macro_line|#endif
macro_line|#else
DECL|macro|PPCDBG
mdefine_line|#define PPCDBG(...) do {;} while (0)
DECL|macro|PPCDBGCALL
mdefine_line|#define PPCDBGCALL(FLAGS,FUNCTION) do {;} while (0)
DECL|macro|ifppcdebug
mdefine_line|#define ifppcdebug(...) if (0)
DECL|macro|ppcdebugset
mdefine_line|#define ppcdebugset(FLAGS) (0)
macro_line|#endif /* CONFIG_PPCDBG */
macro_line|#ifndef PPCDBG_ENTER_DEBUGGER
DECL|macro|PPCDBG_ENTER_DEBUGGER
mdefine_line|#define PPCDBG_ENTER_DEBUGGER() do {;} while(0)
macro_line|#endif
macro_line|#ifndef PPCDBG_ENTER_DEBUGGER_REGS
DECL|macro|PPCDBG_ENTER_DEBUGGER_REGS
mdefine_line|#define PPCDBG_ENTER_DEBUGGER_REGS(A) do {;} while(0)
macro_line|#endif
macro_line|#endif /*__PPCDEBUG_H */
eof
