multiline_comment|/* $Id: kdebug.h,v 1.11 2000/06/04 06:23:53 anton Exp $&n; * kdebug.h:  Defines and definitions for debugging the Linux kernel&n; *            under various kernel debuggers.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_KDEBUG_H
DECL|macro|_SPARC_KDEBUG_H
mdefine_line|#define _SPARC_KDEBUG_H
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/vaddrs.h&gt;
multiline_comment|/* Breakpoints are enter through trap table entry 126.  So in sparc assembly&n; * if you want to drop into the debugger you do:&n; *&n; * t DEBUG_BP_TRAP&n; */
DECL|macro|DEBUG_BP_TRAP
mdefine_line|#define DEBUG_BP_TRAP     126
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* The debug vector is passed in %o1 at boot time.  It is a pointer to&n; * a structure in the debuggers address space.  Here is its format.&n; */
DECL|typedef|debugger_funct
r_typedef
r_int
r_int
(paren
op_star
id|debugger_funct
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|struct|kernel_debug
r_struct
id|kernel_debug
(brace
multiline_comment|/* First the entry point into the debugger.  You jump here&n;&t; * to give control over to the debugger.&n;&t; */
DECL|member|kdebug_entry
r_int
r_int
id|kdebug_entry
suffix:semicolon
DECL|member|kdebug_trapme
r_int
r_int
id|kdebug_trapme
suffix:semicolon
multiline_comment|/* Figure out later... */
multiline_comment|/* The following is the number of pages that the debugger has&n;&t; * taken from to total pool.&n;&t; */
DECL|member|kdebug_stolen_pages
r_int
r_int
op_star
id|kdebug_stolen_pages
suffix:semicolon
multiline_comment|/* Ok, after you remap yourself and/or change the trap table&n;&t; * from what you were left with at boot time you have to call&n;&t; * this synchronization function so the debugger can check out&n;&t; * what you have done.&n;&t; */
DECL|member|teach_debugger
id|debugger_funct
id|teach_debugger
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* I think that is it... */
r_extern
r_struct
id|kernel_debug
op_star
id|linux_dbvec
suffix:semicolon
multiline_comment|/* Use this macro in C-code to enter the debugger. */
DECL|function|sp_enter_debugger
r_extern
id|__inline__
r_void
id|sp_enter_debugger
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;jmpl %0, %%o7&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|linux_dbvec
)paren
suffix:colon
l_string|&quot;o7&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|SP_ENTER_DEBUGGER
mdefine_line|#define SP_ENTER_DEBUGGER do { &bslash;&n;&t;     if((linux_dbvec!=0) &amp;&amp; ((*(short *)linux_dbvec)!=-1)) &bslash;&n;&t;       sp_enter_debugger(); &bslash;&n;&t;&t;       } while(0)
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* Some nice offset defines for assembler code. */
DECL|macro|KDEBUG_ENTRY_OFF
mdefine_line|#define KDEBUG_ENTRY_OFF    0x0
DECL|macro|KDEBUG_DUNNO_OFF
mdefine_line|#define KDEBUG_DUNNO_OFF    0x4
DECL|macro|KDEBUG_DUNNO2_OFF
mdefine_line|#define KDEBUG_DUNNO2_OFF   0x8
DECL|macro|KDEBUG_TEACH_OFF
mdefine_line|#define KDEBUG_TEACH_OFF    0xc
macro_line|#endif /* !(_SPARC_KDEBUG_H) */
eof
