multiline_comment|/* &n; * ppc-stub.c:  KGDB support for the Linux kernel.&n; *&n; * adapted from arch/sparc/kernel/sparc-stub.c for the PowerPC&n; * some stuff borrowed from Paul Mackerras&squot; xmon&n; * Copyright (C) 1998 Michael AK Tesch (tesch@cs.wisc.edu)&n; *&n; * Modifications to run under Linux&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *&n; * This file originally came from the gdb sources, and the&n; * copyright notices have been retained below.&n; */
multiline_comment|/****************************************************************************&n;&n;&t;&t;THIS SOFTWARE IS NOT COPYRIGHTED&n;&n;   HP offers the following for use in the public domain.  HP makes no&n;   warranty with regard to the software or its performance and the&n;   user accepts the software &quot;AS IS&quot; with all faults.&n;&n;   HP DISCLAIMS ANY WARRANTIES, EXPRESS OR IMPLIED, WITH REGARD&n;   TO THIS SOFTWARE INCLUDING BUT NOT LIMITED TO THE WARRANTIES&n;   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.&n;&n;****************************************************************************/
multiline_comment|/****************************************************************************&n; *  Header: remcom.c,v 1.34 91/03/09 12:29:49 glenne Exp $&n; *&n; *  Module name: remcom.c $&n; *  Revision: 1.34 $&n; *  Date: 91/03/09 12:29:49 $&n; *  Contributor:     Lake Stevens Instrument Division$&n; *&n; *  Description:     low level support for gdb debugger. $&n; *&n; *  Considerations:  only works on target hardware $&n; *&n; *  Written by:      Glenn Engel $&n; *  ModuleState:     Experimental $&n; *&n; *  NOTES:           See Below $&n; *&n; *  Modified for SPARC by Stu Grossman, Cygnus Support.&n; *&n; *  This code has been extensively tested on the Fujitsu SPARClite demo board.&n; *&n; *  To enable debugger support, two things need to happen.  One, a&n; *  call to set_debug_traps() is necessary in order to allow any breakpoints&n; *  or error conditions to be properly intercepted and reported to gdb.&n; *  Two, a breakpoint needs to be generated to begin communication.  This&n; *  is most easily accomplished by a call to breakpoint().  Breakpoint()&n; *  simulates a breakpoint by executing a trap #1.&n; *&n; *************&n; *&n; *    The following gdb commands are supported:&n; *&n; * command          function                               Return value&n; *&n; *    g             return the value of the CPU registers  hex data or ENN&n; *    G             set the value of the CPU registers     OK or ENN&n; *    qOffsets      Get section offsets.  Reply is Text=xxx;Data=yyy;Bss=zzz&n; *&n; *    mAA..AA,LLLL  Read LLLL bytes at address AA..AA      hex data or ENN&n; *    MAA..AA,LLLL: Write LLLL bytes at address AA.AA      OK or ENN&n; *&n; *    c             Resume at current address              SNN   ( signal NN)&n; *    cAA..AA       Continue at address AA..AA             SNN&n; *&n; *    s             Step one instruction                   SNN&n; *    sAA..AA       Step one instruction from AA..AA       SNN&n; *&n; *    k             kill&n; *&n; *    ?             What was the last sigval ?             SNN   (signal NN)&n; *&n; *    bBB..BB&t;    Set baud rate to BB..BB&t;&t;   OK or BNN, then sets&n; *&t;&t;&t;&t;&t;&t;&t;   baud rate&n; *&n; * All commands and responses are sent with a packet which includes a&n; * checksum.  A packet consists of&n; *&n; * $&lt;packet info&gt;#&lt;checksum&gt;.&n; *&n; * where&n; * &lt;packet info&gt; :: &lt;characters representing the command or response&gt;&n; * &lt;checksum&gt;    :: &lt;two hex digits computed as modulo 256 sum of &lt;packetinfo&gt;&gt;&n; *&n; * When a packet is received, it is first acknowledged with either &squot;+&squot; or &squot;-&squot;.&n; * &squot;+&squot; indicates a successful transfer.  &squot;-&squot; indicates a failed transfer.&n; *&n; * Example:&n; *&n; * Host:                  Reply:&n; * $m0,10#2a               +$00010203040506070809101112131415#42&n; *&n; ****************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
r_void
id|breakinst
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * BUFMAX defines the maximum number of characters in inbound/outbound buffers&n; * at least NUMREGBYTES*2 are needed for register packets&n; */
DECL|macro|BUFMAX
mdefine_line|#define BUFMAX 2048
DECL|variable|remcomInBuffer
r_static
r_char
id|remcomInBuffer
(braket
id|BUFMAX
)braket
suffix:semicolon
DECL|variable|remcomOutBuffer
r_static
r_char
id|remcomOutBuffer
(braket
id|BUFMAX
)braket
suffix:semicolon
DECL|variable|initialized
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
DECL|variable|kgdb_active
r_static
r_int
id|kgdb_active
op_assign
l_int|0
suffix:semicolon
DECL|variable|kgdb_started
r_static
r_int
id|kgdb_started
op_assign
l_int|0
suffix:semicolon
DECL|variable|fault_jmp_buf
r_static
id|u_int
id|fault_jmp_buf
(braket
l_int|100
)braket
suffix:semicolon
DECL|variable|kdebug
r_static
r_int
id|kdebug
suffix:semicolon
DECL|variable|hexchars
r_static
r_const
r_char
id|hexchars
(braket
)braket
op_assign
l_string|&quot;0123456789abcdef&quot;
suffix:semicolon
multiline_comment|/* Place where we save old trap entries for restoration - sparc*/
multiline_comment|/* struct tt_entry kgdb_savettable[256]; */
multiline_comment|/* typedef void (*trapfunc_t)(void); */
macro_line|#if 0
multiline_comment|/* Install an exception handler for kgdb */
r_static
r_void
id|exceptionHandler
c_func
(paren
r_int
id|tnum
comma
r_int
r_int
op_star
id|tfunc
)paren
(brace
multiline_comment|/* We are dorking with a live trap table, all irqs off */
)brace
macro_line|#endif
r_int
DECL|function|kgdb_setjmp
id|kgdb_setjmp
c_func
(paren
r_int
op_star
id|buf
)paren
(brace
id|asm
(paren
l_string|&quot;mflr 0; stw 0,0(%0);&quot;
l_string|&quot;stw 1,4(%0); stw 2,8(%0);&quot;
l_string|&quot;mfcr 0; stw 0,12(%0);&quot;
l_string|&quot;stmw 13,16(%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|buf
)paren
)paren
suffix:semicolon
multiline_comment|/* XXX should save fp regs as well */
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|kgdb_longjmp
id|kgdb_longjmp
c_func
(paren
r_int
op_star
id|buf
comma
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|val
op_eq
l_int|0
)paren
id|val
op_assign
l_int|1
suffix:semicolon
id|asm
(paren
l_string|&quot;lmw 13,16(%0);&quot;
l_string|&quot;lwz 0,12(%0); mtcrf 0x38,0;&quot;
l_string|&quot;lwz 0,0(%0); lwz 1,4(%0); lwz 2,8(%0);&quot;
l_string|&quot;mtlr 0; mr 3,%1&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|buf
)paren
comma
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert ch from a hex digit to an int */
r_static
r_int
DECL|function|hex
id|hex
c_func
(paren
r_int
r_char
id|ch
)paren
(brace
r_if
c_cond
(paren
id|ch
op_ge
l_char|&squot;a&squot;
op_logical_and
id|ch
op_le
l_char|&squot;f&squot;
)paren
r_return
id|ch
op_minus
l_char|&squot;a&squot;
op_plus
l_int|10
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_ge
l_char|&squot;0&squot;
op_logical_and
id|ch
op_le
l_char|&squot;9&squot;
)paren
r_return
id|ch
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_ge
l_char|&squot;A&squot;
op_logical_and
id|ch
op_le
l_char|&squot;F&squot;
)paren
r_return
id|ch
op_minus
l_char|&squot;A&squot;
op_plus
l_int|10
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Convert the memory pointed to by mem into hex, placing result in buf.&n; * Return a pointer to the last char put in buf (null), in case of mem fault,&n; * return 0.&n; */
r_static
r_int
r_char
op_star
DECL|function|mem2hex
id|mem2hex
c_func
(paren
r_char
op_star
id|mem
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_char
id|ch
suffix:semicolon
r_if
c_cond
(paren
id|kgdb_setjmp
c_func
(paren
(paren
r_int
op_star
)paren
id|fault_jmp_buf
)paren
op_eq
l_int|0
)paren
(brace
id|debugger_fault_handler
op_assign
id|kgdb_fault_handler
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
)paren
(brace
id|ch
op_assign
op_star
id|mem
op_increment
suffix:semicolon
op_star
id|buf
op_increment
op_assign
id|hexchars
(braket
id|ch
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|buf
op_increment
op_assign
id|hexchars
(braket
id|ch
op_amp
l_int|0xf
)braket
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* error condition */
)brace
id|debugger_fault_handler
op_assign
l_int|0
suffix:semicolon
op_star
id|buf
op_assign
l_int|0
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/* convert the hex array pointed to by buf into binary to be placed in mem&n; * return a pointer to the character AFTER the last byte written.&n;*/
r_static
r_char
op_star
DECL|function|hex2mem
id|hex2mem
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|mem
comma
r_int
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
id|ch
suffix:semicolon
r_if
c_cond
(paren
id|kgdb_setjmp
c_func
(paren
(paren
r_int
op_star
)paren
id|fault_jmp_buf
)paren
op_eq
l_int|0
)paren
(brace
id|debugger_fault_handler
op_assign
id|kgdb_fault_handler
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ch
op_assign
id|hex
c_func
(paren
op_star
id|buf
op_increment
)paren
op_lshift
l_int|4
suffix:semicolon
id|ch
op_or_assign
id|hex
c_func
(paren
op_star
id|buf
op_increment
)paren
suffix:semicolon
op_star
id|mem
op_increment
op_assign
id|ch
suffix:semicolon
)brace
id|flush_icache_range
c_func
(paren
(paren
r_int
)paren
id|mem
comma
(paren
r_int
)paren
id|mem
op_plus
id|count
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* error condition */
)brace
id|debugger_fault_handler
op_assign
l_int|0
suffix:semicolon
r_return
id|mem
suffix:semicolon
)brace
multiline_comment|/*&n; * While we find nice hex chars, build an int.&n; * Return number of chars processed.&n; */
r_static
r_int
DECL|function|hexToInt
id|hexToInt
c_func
(paren
r_char
op_star
op_star
id|ptr
comma
r_int
op_star
id|intValue
)paren
(brace
r_int
id|numChars
op_assign
l_int|0
suffix:semicolon
r_int
id|hexValue
suffix:semicolon
op_star
id|intValue
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|kgdb_setjmp
c_func
(paren
(paren
r_int
op_star
)paren
id|fault_jmp_buf
)paren
op_eq
l_int|0
)paren
(brace
id|debugger_fault_handler
op_assign
id|kgdb_fault_handler
suffix:semicolon
r_while
c_loop
(paren
op_star
op_star
id|ptr
)paren
(brace
id|hexValue
op_assign
id|hex
c_func
(paren
op_star
op_star
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hexValue
OL
l_int|0
)paren
r_break
suffix:semicolon
op_star
id|intValue
op_assign
(paren
op_star
id|intValue
op_lshift
l_int|4
)paren
op_or
id|hexValue
suffix:semicolon
id|numChars
op_increment
suffix:semicolon
(paren
op_star
id|ptr
)paren
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* error condition */
)brace
id|debugger_fault_handler
op_assign
l_int|0
suffix:semicolon
r_return
(paren
id|numChars
)paren
suffix:semicolon
)brace
multiline_comment|/* scan for the sequence $&lt;data&gt;#&lt;checksum&gt;     */
r_static
r_void
DECL|function|getpacket
id|getpacket
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_int
r_char
id|checksum
suffix:semicolon
r_int
r_char
id|xmitcsum
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
r_char
id|ch
suffix:semicolon
r_do
(brace
multiline_comment|/* wait around for the start character, ignore all other&n;&t;&t; * characters */
r_while
c_loop
(paren
(paren
id|ch
op_assign
(paren
id|getDebugChar
c_func
(paren
)paren
op_amp
l_int|0x7f
)paren
)paren
op_ne
l_char|&squot;$&squot;
)paren
suffix:semicolon
id|checksum
op_assign
l_int|0
suffix:semicolon
id|xmitcsum
op_assign
op_minus
l_int|1
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* now, read until a # or end of buffer is found */
r_while
c_loop
(paren
id|count
OL
id|BUFMAX
)paren
(brace
id|ch
op_assign
id|getDebugChar
c_func
(paren
)paren
op_amp
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;#&squot;
)paren
r_break
suffix:semicolon
id|checksum
op_assign
id|checksum
op_plus
id|ch
suffix:semicolon
id|buffer
(braket
id|count
)braket
op_assign
id|ch
suffix:semicolon
id|count
op_assign
id|count
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_ge
id|BUFMAX
)paren
r_continue
suffix:semicolon
id|buffer
(braket
id|count
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;#&squot;
)paren
(brace
id|xmitcsum
op_assign
id|hex
c_func
(paren
id|getDebugChar
c_func
(paren
)paren
op_amp
l_int|0x7f
)paren
op_lshift
l_int|4
suffix:semicolon
id|xmitcsum
op_or_assign
id|hex
c_func
(paren
id|getDebugChar
c_func
(paren
)paren
op_amp
l_int|0x7f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|checksum
op_ne
id|xmitcsum
)paren
id|putDebugChar
c_func
(paren
l_char|&squot;-&squot;
)paren
suffix:semicolon
multiline_comment|/* failed checksum */
r_else
(brace
id|putDebugChar
c_func
(paren
l_char|&squot;+&squot;
)paren
suffix:semicolon
multiline_comment|/* successful transfer */
multiline_comment|/* if a sequence char is present, reply the ID */
r_if
c_cond
(paren
id|buffer
(braket
l_int|2
)braket
op_eq
l_char|&squot;:&squot;
)paren
(brace
id|putDebugChar
c_func
(paren
id|buffer
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|putDebugChar
c_func
(paren
id|buffer
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* remove sequence chars from buffer */
id|count
op_assign
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|3
suffix:semicolon
id|i
op_le
id|count
suffix:semicolon
id|i
op_increment
)paren
id|buffer
(braket
id|i
op_minus
l_int|3
)braket
op_assign
id|buffer
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
)brace
)brace
r_while
c_loop
(paren
id|checksum
op_ne
id|xmitcsum
)paren
suffix:semicolon
)brace
multiline_comment|/* send the packet in buffer.  */
DECL|function|putpacket
r_static
r_void
id|putpacket
c_func
(paren
r_int
r_char
op_star
id|buffer
)paren
(brace
r_int
r_char
id|checksum
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
r_char
id|ch
comma
id|recv
suffix:semicolon
multiline_comment|/*  $&lt;packet info&gt;#&lt;checksum&gt;. */
r_do
(brace
id|putDebugChar
c_func
(paren
l_char|&squot;$&squot;
)paren
suffix:semicolon
id|checksum
op_assign
l_int|0
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ch
op_assign
id|buffer
(braket
id|count
)braket
)paren
)paren
(brace
id|putDebugChar
c_func
(paren
id|ch
)paren
suffix:semicolon
id|checksum
op_add_assign
id|ch
suffix:semicolon
id|count
op_add_assign
l_int|1
suffix:semicolon
)brace
id|putDebugChar
c_func
(paren
l_char|&squot;#&squot;
)paren
suffix:semicolon
id|putDebugChar
c_func
(paren
id|hexchars
(braket
id|checksum
op_rshift
l_int|4
)braket
)paren
suffix:semicolon
id|putDebugChar
c_func
(paren
id|hexchars
(braket
id|checksum
op_amp
l_int|0xf
)braket
)paren
suffix:semicolon
id|recv
op_assign
id|getDebugChar
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|recv
op_amp
l_int|0x7f
)paren
op_ne
l_char|&squot;+&squot;
)paren
suffix:semicolon
)brace
DECL|function|kgdb_flush_cache_all
r_static
r_void
id|kgdb_flush_cache_all
c_func
(paren
r_void
)paren
(brace
id|flush_instruction_cache
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Set up exception handlers for tracing and breakpoints&n; * [could be called kgdb_init()]&n; */
DECL|function|set_debug_traps
r_void
id|set_debug_traps
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0
r_int
r_char
id|c
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* In case GDB is started before us, ack any packets (presumably&n;&t; * &quot;$?#xx&quot;) sitting there.&n;&t; *&n;&t; * I&squot;ve found this code causes more problems than it solves,&n;&t; * so that&squot;s why it&squot;s commented out.  GDB seems to work fine&n;&t; * now starting either before or after the kernel   -bwb&n;&t; */
r_while
c_loop
(paren
(paren
id|c
op_assign
id|getDebugChar
c_func
(paren
)paren
)paren
op_ne
l_char|&squot;$&squot;
)paren
(brace
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|c
op_assign
id|getDebugChar
c_func
(paren
)paren
)paren
op_ne
l_char|&squot;#&squot;
)paren
(brace
suffix:semicolon
)brace
id|c
op_assign
id|getDebugChar
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* eat first csum byte */
id|c
op_assign
id|getDebugChar
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* eat second csum byte */
id|putDebugChar
c_func
(paren
l_char|&squot;+&squot;
)paren
suffix:semicolon
multiline_comment|/* ack it */
macro_line|#endif
id|debugger
op_assign
id|kgdb
suffix:semicolon
id|debugger_bpt
op_assign
id|kgdb_bpt
suffix:semicolon
id|debugger_sstep
op_assign
id|kgdb_sstep
suffix:semicolon
id|debugger_iabr_match
op_assign
id|kgdb_iabr_match
suffix:semicolon
id|debugger_dabr_match
op_assign
id|kgdb_dabr_match
suffix:semicolon
id|initialized
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|kgdb_fault_handler
r_static
r_void
id|kgdb_fault_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|kgdb_longjmp
c_func
(paren
(paren
r_int
op_star
)paren
id|fault_jmp_buf
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|kgdb_bpt
r_int
id|kgdb_bpt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|handle_exception
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|kgdb_sstep
r_int
id|kgdb_sstep
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|handle_exception
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|kgdb
r_void
id|kgdb
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|handle_exception
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
DECL|function|kgdb_iabr_match
r_int
id|kgdb_iabr_match
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kgdb doesn&squot;t support iabr, what?!?&bslash;n&quot;
)paren
suffix:semicolon
id|handle_exception
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|kgdb_dabr_match
r_int
id|kgdb_dabr_match
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;kgdb doesn&squot;t support dabr, what?!?&bslash;n&quot;
)paren
suffix:semicolon
id|handle_exception
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Convert the SPARC hardware trap type code to a unix signal number. */
multiline_comment|/*&n; * This table contains the mapping between PowerPC hardware trap types, and&n; * signals, which are primarily what GDB understands.&n; */
DECL|struct|hard_trap_info
r_static
r_struct
id|hard_trap_info
(brace
DECL|member|tt
r_int
r_int
id|tt
suffix:semicolon
multiline_comment|/* Trap type code for powerpc */
DECL|member|signo
r_int
r_char
id|signo
suffix:semicolon
multiline_comment|/* Signal that we map this trap into */
DECL|variable|hard_trap_info
)brace
id|hard_trap_info
(braket
)braket
op_assign
(brace
(brace
l_int|0x200
comma
id|SIGSEGV
)brace
comma
multiline_comment|/* machine check */
(brace
l_int|0x300
comma
id|SIGSEGV
)brace
comma
multiline_comment|/* address error (store) */
(brace
l_int|0x400
comma
id|SIGBUS
)brace
comma
multiline_comment|/* instruction bus error */
(brace
l_int|0x500
comma
id|SIGINT
)brace
comma
multiline_comment|/* interrupt */
(brace
l_int|0x600
comma
id|SIGBUS
)brace
comma
multiline_comment|/* alingment */
(brace
l_int|0x700
comma
id|SIGTRAP
)brace
comma
multiline_comment|/* breakpoint trap */
(brace
l_int|0x800
comma
id|SIGFPE
)brace
comma
multiline_comment|/* fpu unavail */
(brace
l_int|0x900
comma
id|SIGALRM
)brace
comma
multiline_comment|/* decrementer */
(brace
l_int|0xa00
comma
id|SIGILL
)brace
comma
multiline_comment|/* reserved */
(brace
l_int|0xb00
comma
id|SIGILL
)brace
comma
multiline_comment|/* reserved */
(brace
l_int|0xc00
comma
id|SIGCHLD
)brace
comma
multiline_comment|/* syscall */
(brace
l_int|0xd00
comma
id|SIGTRAP
)brace
comma
multiline_comment|/* single-step/watch */
(brace
l_int|0xe00
comma
id|SIGFPE
)brace
comma
multiline_comment|/* fp assist */
(brace
l_int|0
comma
l_int|0
)brace
multiline_comment|/* Must be last */
)brace
suffix:semicolon
DECL|function|computeSignal
r_static
r_int
id|computeSignal
c_func
(paren
r_int
r_int
id|tt
)paren
(brace
r_struct
id|hard_trap_info
op_star
id|ht
suffix:semicolon
r_for
c_loop
(paren
id|ht
op_assign
id|hard_trap_info
suffix:semicolon
id|ht-&gt;tt
op_logical_and
id|ht-&gt;signo
suffix:semicolon
id|ht
op_increment
)paren
r_if
c_cond
(paren
id|ht-&gt;tt
op_eq
id|tt
)paren
r_return
id|ht-&gt;signo
suffix:semicolon
r_return
id|SIGHUP
suffix:semicolon
multiline_comment|/* default for things we don&squot;t know about */
)brace
DECL|macro|PC_REGNUM
mdefine_line|#define PC_REGNUM 64
DECL|macro|SP_REGNUM
mdefine_line|#define SP_REGNUM 1
multiline_comment|/*&n; * This function does all command processing for interfacing to gdb.&n; */
r_static
r_void
DECL|function|handle_exception
id|handle_exception
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|sigval
suffix:semicolon
r_int
id|addr
suffix:semicolon
r_int
id|length
suffix:semicolon
r_char
op_star
id|ptr
suffix:semicolon
r_int
r_int
id|msr
suffix:semicolon
r_if
c_cond
(paren
id|debugger_fault_handler
)paren
(brace
id|debugger_fault_handler
c_func
(paren
id|regs
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;kgdb longjump failed!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kgdb_active
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;interrupt while in kgdb, returning&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|kgdb_active
op_assign
l_int|1
suffix:semicolon
id|kgdb_started
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef KGDB_DEBUG
id|printk
c_func
(paren
l_string|&quot;kgdb: entering handle_exception; trap [0x%x]&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|regs-&gt;trap
)paren
suffix:semicolon
macro_line|#endif
id|kgdb_interruptible
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|msr
op_assign
id|get_msr
c_func
(paren
)paren
suffix:semicolon
id|set_msr
c_func
(paren
id|msr
op_amp
op_complement
id|MSR_EE
)paren
suffix:semicolon
multiline_comment|/* disable interrupts */
r_if
c_cond
(paren
id|regs-&gt;nip
op_eq
(paren
r_int
r_int
)paren
id|breakinst
)paren
(brace
multiline_comment|/* Skip over breakpoint trap insn */
id|regs-&gt;nip
op_add_assign
l_int|4
suffix:semicolon
)brace
multiline_comment|/* reply to host that an exception has occurred */
id|sigval
op_assign
id|computeSignal
c_func
(paren
id|regs-&gt;trap
)paren
suffix:semicolon
id|ptr
op_assign
id|remcomOutBuffer
suffix:semicolon
macro_line|#if 0
op_star
id|ptr
op_increment
op_assign
l_char|&squot;S&squot;
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|sigval
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|sigval
op_amp
l_int|0xf
)braket
suffix:semicolon
macro_line|#else
op_star
id|ptr
op_increment
op_assign
l_char|&squot;T&squot;
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|sigval
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|sigval
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|PC_REGNUM
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|PC_REGNUM
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;:&squot;
suffix:semicolon
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|regs-&gt;nip
comma
id|ptr
comma
l_int|4
)paren
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;;&squot;
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|SP_REGNUM
op_rshift
l_int|4
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|hexchars
(braket
id|SP_REGNUM
op_amp
l_int|0xf
)braket
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;:&squot;
suffix:semicolon
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
(paren
r_char
op_star
)paren
op_amp
id|regs
)paren
op_plus
id|SP_REGNUM
op_star
l_int|4
comma
id|ptr
comma
l_int|4
)paren
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
l_char|&squot;;&squot;
suffix:semicolon
macro_line|#endif
op_star
id|ptr
op_increment
op_assign
l_int|0
suffix:semicolon
id|putpacket
c_func
(paren
id|remcomOutBuffer
)paren
suffix:semicolon
multiline_comment|/* XXX We may want to add some features dealing with poking the&n;&t; * XXX page tables, ... (look at sparc-stub.c for more info)&n;&t; * XXX also required hacking to the gdb sources directly...&n;&t; */
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|remcomOutBuffer
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|getpacket
c_func
(paren
id|remcomInBuffer
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|remcomInBuffer
(braket
l_int|0
)braket
)paren
(brace
r_case
l_char|&squot;?&squot;
suffix:colon
multiline_comment|/* report most recent signal */
id|remcomOutBuffer
(braket
l_int|0
)braket
op_assign
l_char|&squot;S&squot;
suffix:semicolon
id|remcomOutBuffer
(braket
l_int|1
)braket
op_assign
id|hexchars
(braket
id|sigval
op_rshift
l_int|4
)braket
suffix:semicolon
id|remcomOutBuffer
(braket
l_int|2
)braket
op_assign
id|hexchars
(braket
id|sigval
op_amp
l_int|0xf
)braket
suffix:semicolon
id|remcomOutBuffer
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if 0
r_case
l_char|&squot;q&squot;
suffix:colon
multiline_comment|/* this screws up gdb for some reason...*/
(brace
r_extern
r_int
id|_start
comma
id|sdata
comma
id|__bss_start
suffix:semicolon
id|ptr
op_assign
op_amp
id|remcomInBuffer
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|ptr
comma
l_string|&quot;Offsets&quot;
comma
l_int|7
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|ptr
op_assign
id|remcomOutBuffer
suffix:semicolon
id|sprintf
c_func
(paren
id|ptr
comma
l_string|&quot;Text=%8.8x;Data=%8.8x;Bss=%8.8x&quot;
comma
op_amp
id|_start
comma
op_amp
id|sdata
comma
op_amp
id|__bss_start
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
r_case
l_char|&squot;d&squot;
suffix:colon
multiline_comment|/* toggle debug flag */
id|kdebug
op_xor_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;g&squot;
suffix:colon
multiline_comment|/* return the value of the CPU registers.&n;&t;&t;&t;&t; * some of them are non-PowerPC names :(&n;&t;&t;&t;&t; * they are stored in gdb like:&n;&t;&t;&t;&t; * struct {&n;&t;&t;&t;&t; *     u32 gpr[32];&n;&t;&t;&t;&t; *     f64 fpr[32];&n;&t;&t;&t;&t; *     u32 pc, ps, cnd, lr; (ps=msr)&n;&t;&t;&t;&t; *     u32 cnt, xer, mq;&n;&t;&t;&t;&t; * }&n;&t;&t;&t;&t; */
(brace
r_int
id|i
suffix:semicolon
id|ptr
op_assign
id|remcomOutBuffer
suffix:semicolon
multiline_comment|/* General Purpose Regs */
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
id|regs
comma
id|ptr
comma
l_int|32
op_star
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Floating Point Regs - FIXME */
multiline_comment|/*ptr = mem2hex((char *), ptr, 32 * 8);*/
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
l_int|32
op_star
l_int|8
op_star
l_int|2
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* 2chars/byte */
id|ptr
(braket
id|i
)braket
op_assign
l_char|&squot;0&squot;
suffix:semicolon
)brace
id|ptr
op_add_assign
l_int|32
op_star
l_int|8
op_star
l_int|2
suffix:semicolon
multiline_comment|/* pc, msr, cr, lr, ctr, xer, (mq is unused) */
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|regs-&gt;nip
comma
id|ptr
comma
l_int|4
)paren
suffix:semicolon
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|regs-&gt;msr
comma
id|ptr
comma
l_int|4
)paren
suffix:semicolon
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|regs-&gt;ccr
comma
id|ptr
comma
l_int|4
)paren
suffix:semicolon
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|regs-&gt;link
comma
id|ptr
comma
l_int|4
)paren
suffix:semicolon
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|regs-&gt;ctr
comma
id|ptr
comma
l_int|4
)paren
suffix:semicolon
id|ptr
op_assign
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|regs-&gt;xer
comma
id|ptr
comma
l_int|4
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;G&squot;
suffix:colon
multiline_comment|/* set the value of the CPU registers */
(brace
id|ptr
op_assign
op_amp
id|remcomInBuffer
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * If the stack pointer has moved, you should pray.&n;&t;&t;&t; * (cause only god can help you).&n;&t;&t;&t; */
multiline_comment|/* General Purpose Regs */
id|hex2mem
c_func
(paren
id|ptr
comma
(paren
r_char
op_star
)paren
id|regs
comma
l_int|32
op_star
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Floating Point Regs - FIXME?? */
multiline_comment|/*ptr = hex2mem(ptr, ??, 32 * 8);*/
id|ptr
op_add_assign
l_int|32
op_star
l_int|8
op_star
l_int|2
suffix:semicolon
multiline_comment|/* pc, msr, cr, lr, ctr, xer, (mq is unused) */
id|ptr
op_assign
id|hex2mem
c_func
(paren
id|ptr
comma
(paren
r_char
op_star
)paren
op_amp
id|regs-&gt;nip
comma
l_int|4
)paren
suffix:semicolon
id|ptr
op_assign
id|hex2mem
c_func
(paren
id|ptr
comma
(paren
r_char
op_star
)paren
op_amp
id|regs-&gt;msr
comma
l_int|4
)paren
suffix:semicolon
id|ptr
op_assign
id|hex2mem
c_func
(paren
id|ptr
comma
(paren
r_char
op_star
)paren
op_amp
id|regs-&gt;ccr
comma
l_int|4
)paren
suffix:semicolon
id|ptr
op_assign
id|hex2mem
c_func
(paren
id|ptr
comma
(paren
r_char
op_star
)paren
op_amp
id|regs-&gt;link
comma
l_int|4
)paren
suffix:semicolon
id|ptr
op_assign
id|hex2mem
c_func
(paren
id|ptr
comma
(paren
r_char
op_star
)paren
op_amp
id|regs-&gt;ctr
comma
l_int|4
)paren
suffix:semicolon
id|ptr
op_assign
id|hex2mem
c_func
(paren
id|ptr
comma
(paren
r_char
op_star
)paren
op_amp
id|regs-&gt;xer
comma
l_int|4
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|remcomOutBuffer
comma
l_string|&quot;OK&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;H&squot;
suffix:colon
multiline_comment|/* don&squot;t do anything, yet, just acknowledge */
id|hexToInt
c_func
(paren
op_amp
id|ptr
comma
op_amp
id|addr
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|remcomOutBuffer
comma
l_string|&quot;OK&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;m&squot;
suffix:colon
multiline_comment|/* mAA..AA,LLLL  Read LLLL bytes at address AA..AA */
multiline_comment|/* Try to read %x,%x.  */
id|ptr
op_assign
op_amp
id|remcomInBuffer
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hexToInt
c_func
(paren
op_amp
id|ptr
comma
op_amp
id|addr
)paren
op_logical_and
op_star
id|ptr
op_increment
op_eq
l_char|&squot;,&squot;
op_logical_and
id|hexToInt
c_func
(paren
op_amp
id|ptr
comma
op_amp
id|length
)paren
)paren
(brace
r_if
c_cond
(paren
id|mem2hex
c_func
(paren
(paren
r_char
op_star
)paren
id|addr
comma
id|remcomOutBuffer
comma
id|length
)paren
)paren
r_break
suffix:semicolon
id|strcpy
(paren
id|remcomOutBuffer
comma
l_string|&quot;E03&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|remcomOutBuffer
comma
l_string|&quot;E01&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;M&squot;
suffix:colon
multiline_comment|/* MAA..AA,LLLL: Write LLLL bytes at address AA.AA return OK */
multiline_comment|/* Try to read &squot;%x,%x:&squot;.  */
id|ptr
op_assign
op_amp
id|remcomInBuffer
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hexToInt
c_func
(paren
op_amp
id|ptr
comma
op_amp
id|addr
)paren
op_logical_and
op_star
id|ptr
op_increment
op_eq
l_char|&squot;,&squot;
op_logical_and
id|hexToInt
c_func
(paren
op_amp
id|ptr
comma
op_amp
id|length
)paren
op_logical_and
op_star
id|ptr
op_increment
op_eq
l_char|&squot;:&squot;
)paren
(brace
r_if
c_cond
(paren
id|hex2mem
c_func
(paren
id|ptr
comma
(paren
r_char
op_star
)paren
id|addr
comma
id|length
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|remcomOutBuffer
comma
l_string|&quot;OK&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|remcomOutBuffer
comma
l_string|&quot;E03&quot;
)paren
suffix:semicolon
)brace
id|flush_icache_range
c_func
(paren
id|addr
comma
id|addr
op_plus
id|length
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|remcomOutBuffer
comma
l_string|&quot;E02&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_char|&squot;k&squot;
suffix:colon
multiline_comment|/* kill the program, actually just continue */
r_case
l_char|&squot;c&squot;
suffix:colon
multiline_comment|/* cAA..AA  Continue; address AA..AA optional */
multiline_comment|/* try to read optional parameter, pc unchanged if no parm */
id|ptr
op_assign
op_amp
id|remcomInBuffer
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hexToInt
c_func
(paren
op_amp
id|ptr
comma
op_amp
id|addr
)paren
)paren
(brace
id|regs-&gt;nip
op_assign
id|addr
suffix:semicolon
)brace
multiline_comment|/* Need to flush the instruction cache here, as we may have deposited a&n; * breakpoint, and the icache probably has no way of knowing that a data ref to&n; * some location may have changed something that is in the instruction cache.&n; */
id|kgdb_flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|set_msr
c_func
(paren
id|msr
)paren
suffix:semicolon
id|kgdb_interruptible
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|kgdb_active
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|kgdb_flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|regs-&gt;msr
op_or_assign
id|MSR_SE
suffix:semicolon
macro_line|#if 0
id|set_msr
c_func
(paren
id|msr
op_or
id|MSR_SE
)paren
suffix:semicolon
macro_line|#endif
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|kgdb_active
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
r_case
l_char|&squot;r&squot;
suffix:colon
multiline_comment|/* Reset (if user process..exit ???)*/
id|panic
c_func
(paren
l_string|&quot;kgdb reset.&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* switch */
r_if
c_cond
(paren
id|remcomOutBuffer
(braket
l_int|0
)braket
op_logical_and
id|kdebug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;remcomInBuffer: %s&bslash;n&quot;
comma
id|remcomInBuffer
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;remcomOutBuffer: %s&bslash;n&quot;
comma
id|remcomOutBuffer
)paren
suffix:semicolon
)brace
multiline_comment|/* reply to the request */
id|putpacket
c_func
(paren
id|remcomOutBuffer
)paren
suffix:semicolon
)brace
multiline_comment|/* while(1) */
)brace
multiline_comment|/* This function will generate a breakpoint exception.  It is used at the&n;   beginning of a program to sync up with a debugger and can be used&n;   otherwise as a quick means to stop program execution and &quot;break&quot; into&n;   the debugger. */
r_void
DECL|function|breakpoint
id|breakpoint
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|initialized
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;breakpoint() called b4 kgdb init&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|asm
c_func
(paren
"&quot;"
dot
id|globl
id|breakinst
id|breakinst
suffix:colon
dot
r_int
l_int|0x7d821008
"&quot;"
)paren
suffix:semicolon
)brace
multiline_comment|/* Output string in GDB O-packet format if GDB has connected. If nothing&n;   output, returns 0 (caller must then handle output). */
r_int
DECL|function|kgdb_output_string
id|kgdb_output_string
(paren
r_const
r_char
op_star
id|s
comma
r_int
r_int
id|count
)paren
(brace
r_char
id|buffer
(braket
l_int|512
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kgdb_started
)paren
r_return
l_int|0
suffix:semicolon
id|count
op_assign
(paren
id|count
op_le
(paren
r_sizeof
(paren
id|buffer
)paren
op_div
l_int|2
op_minus
l_int|2
)paren
)paren
ques
c_cond
id|count
suffix:colon
(paren
r_sizeof
(paren
id|buffer
)paren
op_div
l_int|2
op_minus
l_int|2
)paren
suffix:semicolon
id|buffer
(braket
l_int|0
)braket
op_assign
l_char|&squot;O&squot;
suffix:semicolon
id|mem2hex
(paren
id|s
comma
op_amp
id|buffer
(braket
l_int|1
)braket
comma
id|count
)paren
suffix:semicolon
id|putpacket
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
