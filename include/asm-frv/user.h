multiline_comment|/* user.h: FR-V core file format stuff&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_USER_H
DECL|macro|_ASM_USER_H
mdefine_line|#define _ASM_USER_H
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/registers.h&gt;
multiline_comment|/* Core file format: The core file is written in such a way that gdb&n; * can understand it and provide useful information to the user (under&n; * linux we use the &squot;trad-core&squot; bfd).  There are quite a number of&n; * obstacles to being able to view the contents of the floating point&n; * registers, and until these are solved you will not be able to view&n; * the contents of them.  Actually, you can read in the core file and&n; * look at the contents of the user struct to find out what the&n; * floating point registers contain.&n; *&n; * The actual file contents are as follows:&n; * UPAGE:&n; *   1 page consisting of a user struct that tells gdb what is present&n; *   in the file.  Directly after this is a copy of the task_struct,&n; *   which is currently not used by gdb, but it may come in useful at&n; *   some point.  All of the registers are stored as part of the&n; *   upage.  The upage should always be only one page.&n; *&n; * DATA:&n; *   The data area is stored.  We use current-&gt;end_text to&n; *   current-&gt;brk to pick up all of the user variables, plus any&n; *   memory that may have been malloced.  No attempt is made to&n; *   determine if a page is demand-zero or if a page is totally&n; *   unused, we just cover the entire range.  All of the addresses are&n; *   rounded in such a way that an integral number of pages is&n; *   written.&n; *&n; * STACK:&n; *   We need the stack information in order to get a meaningful&n; *   backtrace.  We need to write the data from (esp) to&n; *   current-&gt;start_stack, so we round each of these off in order to&n; *   be able to write an integer number of pages.  The minimum core&n; *   file size is 3 pages, or 12288 bytes.&n; */
multiline_comment|/* When the kernel dumps core, it starts by dumping the user struct -&n; * this will be used by gdb to figure out where the data and stack segments&n; *  are within the file, and what virtual addresses to use.&n; */
DECL|struct|user
r_struct
id|user
(brace
multiline_comment|/* We start with the registers, to mimic the way that &quot;memory&quot; is returned&n;&t; * from the ptrace(3,...) function.  */
DECL|member|regs
r_struct
id|user_context
id|regs
suffix:semicolon
multiline_comment|/* The rest of this junk is to help gdb figure out what goes where */
DECL|member|u_tsize
r_int
r_int
id|u_tsize
suffix:semicolon
multiline_comment|/* Text segment size (pages). */
DECL|member|u_dsize
r_int
r_int
id|u_dsize
suffix:semicolon
multiline_comment|/* Data segment size (pages). */
DECL|member|u_ssize
r_int
r_int
id|u_ssize
suffix:semicolon
multiline_comment|/* Stack segment size (pages). */
DECL|member|start_code
r_int
r_int
id|start_code
suffix:semicolon
multiline_comment|/* Starting virtual address of text. */
DECL|member|start_stack
r_int
r_int
id|start_stack
suffix:semicolon
multiline_comment|/* Starting virtual address of stack area.&n;&t;&t;&t;&t;&t;&t; * This is actually the bottom of the stack,&n;&t;&t;&t;&t;&t;&t; * the top of the stack is always found in the&n;&t;&t;&t;&t;&t;&t; * esp register.  */
DECL|member|signal
r_int
r_int
id|signal
suffix:semicolon
multiline_comment|/* Signal that caused the core dump. */
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* To uniquely identify a core file */
DECL|member|u_comm
r_char
id|u_comm
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* User command that was responsible */
)brace
suffix:semicolon
DECL|macro|NBPG
mdefine_line|#define NBPG&t;&t;&t;PAGE_SIZE
DECL|macro|UPAGES
mdefine_line|#define UPAGES&t;&t;&t;1
DECL|macro|HOST_TEXT_START_ADDR
mdefine_line|#define HOST_TEXT_START_ADDR&t;(u.start_code)
DECL|macro|HOST_STACK_END_ADDR
mdefine_line|#define HOST_STACK_END_ADDR&t;(u.start_stack + u.u_ssize * NBPG)
macro_line|#endif
eof
