multiline_comment|/* &n; * Generate definitions needed by assembly language modules.&n; * This code generates raw asm output which is post-processed to extract&n; * and format the required data.&n; *&n; *    Copyright (C) 2000-2001 John Marvin &lt;jsm at parisc-linux.org&gt;&n; *    Copyright (C) 2000 David Huggins-Daines &lt;dhd with pobox.org&gt;&n; *    Copyright (C) 2000 Sam Creasey &lt;sammy@sammy.net&gt;&n; *    Copyright (C) 2000 Grant Grundler &lt;grundler with parisc-linux.org&gt;&n; *    Copyright (C) 2001 Paul Bame &lt;bame at parisc-linux.org&gt;&n; *    Copyright (C) 2001 Richard Hirst &lt;rhirst at parisc-linux.org&gt;&n; *    Copyright (C) 2002 Randolph Chung &lt;tausq with parisc-linux.org&gt;&n; *    Copyright (C) 2003 James Bottomley &lt;jejb at parisc-linux.org&gt;&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/hardirq.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|DEFINE
mdefine_line|#define DEFINE(sym, val) &bslash;&n;&t;asm volatile(&quot;&bslash;n-&gt;&quot; #sym &quot; %0 &quot; #val : : &quot;i&quot; (val))
DECL|macro|BLANK
mdefine_line|#define BLANK() asm volatile(&quot;&bslash;n-&gt;&quot; : : )
macro_line|#ifdef __LP64__
DECL|macro|FRAME_SIZE
mdefine_line|#define FRAME_SIZE&t;128
macro_line|#else
DECL|macro|FRAME_SIZE
mdefine_line|#define FRAME_SIZE&t;64
macro_line|#endif
DECL|macro|align
mdefine_line|#define align(x,y) (((x)+FRAME_SIZE+(y)-1) - (((x)+(y)-1)%(y)))
DECL|function|main
r_int
id|main
c_func
(paren
r_void
)paren
(brace
id|DEFINE
c_func
(paren
id|TASK_THREAD_INFO
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread_info
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_STATE
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|state
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_FLAGS
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|flags
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_SIGPENDING
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|pending
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PTRACE
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|ptrace
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_MM
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|mm
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PERSONALITY
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|personality
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PID
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|pid
)paren
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_REGS
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_PSW
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR1
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR2
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR3
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|3
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR4
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|4
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR5
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR6
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|6
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR7
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|7
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR8
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|8
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR9
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|9
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR10
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|10
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR11
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|11
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR12
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|12
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR13
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|13
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR14
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|14
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR15
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|15
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR16
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|16
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR17
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|17
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR18
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|18
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR19
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|19
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR20
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|20
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR21
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|21
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR22
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|22
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR23
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|23
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR24
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|24
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR25
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|25
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR26
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|26
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR27
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|27
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR28
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|28
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR29
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|29
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR30
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|30
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_GR31
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.gr
(braket
l_int|31
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR0
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR1
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR2
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR3
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|3
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR4
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|4
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR5
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR6
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|6
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR7
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|7
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR8
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|8
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR9
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|9
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR10
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|10
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR11
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|11
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR12
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|12
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR13
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|13
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR14
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|14
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR15
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|15
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR16
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|16
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR17
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|17
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR18
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|18
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR19
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|19
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR20
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|20
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR21
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|21
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR22
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|22
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR23
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|23
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR24
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|24
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR25
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|25
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR26
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|26
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR27
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|27
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR28
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|28
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR29
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|29
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR30
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|30
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_FR31
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.fr
(braket
l_int|31
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_SR0
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.sr
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_SR1
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.sr
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_SR2
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.sr
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_SR3
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.sr
(braket
l_int|3
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_SR4
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.sr
(braket
l_int|4
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_SR5
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.sr
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_SR6
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.sr
(braket
l_int|6
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_SR7
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.sr
(braket
l_int|7
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_IASQ0
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.iasq
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_IASQ1
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.iasq
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_IAOQ0
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.iaoq
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_IAOQ1
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.iaoq
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_CR27
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.cr27
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_ORIG_R28
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.orig_r28
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_KSP
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.ksp
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_KPC
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.kpc
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_SAR
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.sar
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_IIR
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.iir
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_ISR
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.isr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_PT_IOR
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|thread.regs.ior
)paren
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_SZ
comma
r_sizeof
(paren
r_struct
id|task_struct
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TASK_SZ_ALGN
comma
id|align
c_func
(paren
r_sizeof
(paren
r_struct
id|task_struct
)paren
comma
l_int|64
)paren
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_PSW
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR1
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR2
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR3
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|3
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR4
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|4
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR5
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR6
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|6
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR7
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|7
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR8
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|8
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR9
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|9
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR10
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|10
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR11
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|11
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR12
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|12
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR13
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|13
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR14
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|14
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR15
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|15
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR16
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|16
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR17
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|17
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR18
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|18
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR19
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|19
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR20
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|20
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR21
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|21
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR22
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|22
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR23
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|23
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR24
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|24
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR25
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|25
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR26
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|26
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR27
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|27
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR28
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|28
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR29
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|29
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR30
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|30
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_GR31
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|gr
(braket
l_int|31
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR0
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR1
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR2
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR3
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|3
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR4
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|4
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR5
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR6
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|6
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR7
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|7
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR8
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|8
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR9
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|9
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR10
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|10
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR11
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|11
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR12
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|12
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR13
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|13
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR14
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|14
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR15
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|15
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR16
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|16
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR17
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|17
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR18
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|18
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR19
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|19
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR20
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|20
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR21
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|21
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR22
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|22
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR23
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|23
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR24
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|24
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR25
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|25
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR26
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|26
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR27
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|27
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR28
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|28
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR29
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|29
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR30
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|30
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_FR31
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|fr
(braket
l_int|31
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_SR0
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|sr
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_SR1
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|sr
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_SR2
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|sr
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_SR3
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|sr
(braket
l_int|3
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_SR4
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|sr
(braket
l_int|4
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_SR5
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|sr
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_SR6
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|sr
(braket
l_int|6
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_SR7
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|sr
(braket
l_int|7
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_IASQ0
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|iasq
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_IASQ1
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|iasq
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_IAOQ0
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|iaoq
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_IAOQ1
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|iaoq
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_CR27
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|cr27
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_ORIG_R28
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|orig_r28
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_KSP
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|ksp
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_KPC
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|kpc
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_SAR
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|sar
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_IIR
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|iir
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_ISR
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|isr
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_IOR
comma
m_offsetof
(paren
r_struct
id|pt_regs
comma
id|ior
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_SIZE
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PT_SZ_ALGN
comma
id|align
c_func
(paren
r_sizeof
(paren
r_struct
id|pt_regs
)paren
comma
l_int|64
)paren
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TI_TASK
comma
m_offsetof
(paren
r_struct
id|thread_info
comma
id|task
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TI_EXEC_DOMAIN
comma
m_offsetof
(paren
r_struct
id|thread_info
comma
id|exec_domain
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TI_FLAGS
comma
m_offsetof
(paren
r_struct
id|thread_info
comma
id|flags
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TI_CPU
comma
m_offsetof
(paren
r_struct
id|thread_info
comma
id|cpu
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TI_SEGMENT
comma
m_offsetof
(paren
r_struct
id|thread_info
comma
id|addr_limit
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TI_PRE_COUNT
comma
m_offsetof
(paren
r_struct
id|thread_info
comma
id|preempt_count
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_SZ
comma
r_sizeof
(paren
r_struct
id|thread_info
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|THREAD_SZ_ALGN
comma
id|align
c_func
(paren
r_sizeof
(paren
r_struct
id|thread_info
)paren
comma
l_int|64
)paren
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|IRQSTAT_SIRQ_PEND
comma
m_offsetof
(paren
id|irq_cpustat_t
comma
id|__softirq_pending
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|IRQSTAT_SZ
comma
r_sizeof
(paren
id|irq_cpustat_t
)paren
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ICACHE_BASE
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|ic_base
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ICACHE_STRIDE
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|ic_stride
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ICACHE_COUNT
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|ic_count
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ICACHE_LOOP
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|ic_loop
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DCACHE_BASE
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|dc_base
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DCACHE_STRIDE
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|dc_stride
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DCACHE_COUNT
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|dc_count
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DCACHE_LOOP
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|dc_loop
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ITLB_SID_BASE
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|it_sp_base
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ITLB_SID_STRIDE
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|it_sp_stride
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ITLB_SID_COUNT
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|it_sp_count
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ITLB_OFF_BASE
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|it_off_base
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ITLB_OFF_STRIDE
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|it_off_stride
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ITLB_OFF_COUNT
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|it_off_count
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ITLB_LOOP
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|it_loop
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DTLB_SID_BASE
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|dt_sp_base
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DTLB_SID_STRIDE
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|dt_sp_stride
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DTLB_SID_COUNT
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|dt_sp_count
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DTLB_OFF_BASE
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|dt_off_base
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DTLB_OFF_STRIDE
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|dt_off_stride
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DTLB_OFF_COUNT
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|dt_off_count
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|DTLB_LOOP
comma
m_offsetof
(paren
r_struct
id|pdc_cache_info
comma
id|dt_loop
)paren
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PA_BLOCKSTEP_BIT
comma
l_int|31
op_minus
id|PT_BLOCKSTEP_BIT
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|PA_SINGLESTEP_BIT
comma
l_int|31
op_minus
id|PT_SINGLESTEP_BIT
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASM_PMD_SHIFT
comma
id|PMD_SHIFT
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASM_PGDIR_SHIFT
comma
id|PGDIR_SHIFT
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASM_BITS_PER_PGD
comma
id|BITS_PER_PGD
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASM_BITS_PER_PMD
comma
id|BITS_PER_PMD
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASM_BITS_PER_PTE
comma
id|BITS_PER_PTE
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASM_PGD_PMD_OFFSET
comma
op_minus
(paren
id|PAGE_SIZE
op_lshift
id|PGD_ORDER
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASM_PMD_ENTRY
comma
(paren
(paren
id|PAGE_OFFSET
op_amp
id|PMD_MASK
)paren
op_rshift
id|PMD_SHIFT
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASM_PGD_ENTRY
comma
id|PAGE_OFFSET
op_rshift
id|PGDIR_SHIFT
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASM_PGD_ENTRY_SIZE
comma
id|PGD_ENTRY_SIZE
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASM_PMD_ENTRY_SIZE
comma
id|PMD_ENTRY_SIZE
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASM_PTE_ENTRY_SIZE
comma
id|PTE_ENTRY_SIZE
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASM_PT_INITIAL
comma
id|PT_INITIAL
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|ASM_PAGE_SIZE
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|BLANK
c_func
(paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|EXCDATA_IP
comma
m_offsetof
(paren
r_struct
id|exception_data
comma
id|fault_ip
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|EXCDATA_SPACE
comma
m_offsetof
(paren
r_struct
id|exception_data
comma
id|fault_space
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|EXCDATA_ADDR
comma
m_offsetof
(paren
r_struct
id|exception_data
comma
id|fault_addr
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
