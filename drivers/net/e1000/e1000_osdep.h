multiline_comment|/*******************************************************************************&n;&n;  This software program is available to you under a choice of one of two&n;  licenses. You may choose to be licensed under either the GNU General Public&n;  License 2.0, June 1991, available at http://www.fsf.org/copyleft/gpl.html,&n;  or the Intel BSD + Patent License, the text of which follows:&n;  &n;  Recipient has requested a license and Intel Corporation (&quot;Intel&quot;) is willing&n;  to grant a license for the software entitled Linux Base Driver for the&n;  Intel(R) PRO/1000 Family of Adapters (e1000) (the &quot;Software&quot;) being provided&n;  by Intel Corporation. The following definitions apply to this license:&n;  &n;  &quot;Licensed Patents&quot; means patent claims licensable by Intel Corporation which&n;  are necessarily infringed by the use of sale of the Software alone or when&n;  combined with the operating system referred to below.&n;  &n;  &quot;Recipient&quot; means the party to whom Intel delivers this Software.&n;  &n;  &quot;Licensee&quot; means Recipient and those third parties that receive a license to&n;  any operating system available under the GNU General Public License 2.0 or&n;  later.&n;  &n;  Copyright (c) 1999 - 2002 Intel Corporation.&n;  All rights reserved.&n;  &n;  The license is provided to Recipient and Recipient&squot;s Licensees under the&n;  following terms.&n;  &n;  Redistribution and use in source and binary forms of the Software, with or&n;  without modification, are permitted provided that the following conditions&n;  are met:&n;  &n;  Redistributions of source code of the Software may retain the above&n;  copyright notice, this list of conditions and the following disclaimer.&n;  &n;  Redistributions in binary form of the Software may reproduce the above&n;  copyright notice, this list of conditions and the following disclaimer in&n;  the documentation and/or materials provided with the distribution.&n;  &n;  Neither the name of Intel Corporation nor the names of its contributors&n;  shall be used to endorse or promote products derived from this Software&n;  without specific prior written permission.&n;  &n;  Intel hereby grants Recipient and Licensees a non-exclusive, worldwide,&n;  royalty-free patent license under Licensed Patents to make, use, sell, offer&n;  to sell, import and otherwise transfer the Software, if any, in source code&n;  and object code form. This license shall include changes to the Software&n;  that are error corrections or other minor changes to the Software that do&n;  not add functionality or features when the Software is incorporated in any&n;  version of an operating system that has been distributed under the GNU&n;  General Public License 2.0 or later. This patent license shall apply to the&n;  combination of the Software and any operating system licensed under the GNU&n;  General Public License 2.0 or later if, at the time Intel provides the&n;  Software to Recipient, such addition of the Software to the then publicly&n;  available versions of such operating systems available under the GNU General&n;  Public License 2.0 or later (whether in gold, beta or alpha form) causes&n;  such combination to be covered by the Licensed Patents. The patent license&n;  shall not apply to any other combinations which include the Software. NO&n;  hardware per se is licensed hereunder.&n;  &n;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS &quot;AS IS&quot;&n;  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n;  IMPLIED WARRANTIES OF MECHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n;  ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR IT CONTRIBUTORS BE LIABLE FOR ANY&n;  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES&n;  (INCLUDING, BUT NOT LIMITED, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;&n;  ANY LOSS OF USE; DATA, OR PROFITS; OR BUSINESS INTERUPTION) HOWEVER CAUSED&n;  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR&n;  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE&n;  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n;&n;*******************************************************************************/
multiline_comment|/* glue for the OS independant part of e1000 &n; * includes register access macros&n; */
macro_line|#ifndef _E1000_OSDEP_H_
DECL|macro|_E1000_OSDEP_H_
mdefine_line|#define _E1000_OSDEP_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
DECL|macro|usec_delay
mdefine_line|#define usec_delay(x) udelay(x)
macro_line|#ifndef msec_delay
DECL|macro|msec_delay
mdefine_line|#define msec_delay(x)&t;do { if(in_interrupt()) { &bslash;&n;&t;                &t;mdelay(x); &bslash;&n;&t;&t;&t;} else { &bslash;&n;&t;&t;&t;&t;set_current_state(TASK_UNINTERRUPTIBLE); &bslash;&n;&t;&t;&t;&t;schedule_timeout((x * HZ)/1000); &bslash;&n;&t;&t;&t;} } while(0)
macro_line|#endif
DECL|macro|PCI_COMMAND_REGISTER
mdefine_line|#define PCI_COMMAND_REGISTER   PCI_COMMAND
DECL|macro|CMD_MEM_WRT_INVALIDATE
mdefine_line|#define CMD_MEM_WRT_INVALIDATE PCI_COMMAND_INVALIDATE
r_typedef
r_enum
(brace
DECL|enumerator|FALSE
id|FALSE
op_assign
l_int|0
comma
DECL|enumerator|TRUE
id|TRUE
op_assign
l_int|1
DECL|typedef|boolean_t
)brace
id|boolean_t
suffix:semicolon
DECL|macro|ASSERT
mdefine_line|#define ASSERT(x)&t;if(!(x)) BUG()
DECL|macro|MSGOUT
mdefine_line|#define MSGOUT(S, A, B)&t;printk(KERN_DEBUG S &quot;&bslash;n&quot;, A, B)
macro_line|#if DBG
DECL|macro|DEBUGOUT
mdefine_line|#define DEBUGOUT(S)&t;&t;printk(KERN_DEBUG S &quot;&bslash;n&quot;)
DECL|macro|DEBUGOUT1
mdefine_line|#define DEBUGOUT1(S, A...)&t;printk(KERN_DEBUG S &quot;&bslash;n&quot;, A)
macro_line|#else
DECL|macro|DEBUGOUT
mdefine_line|#define DEBUGOUT(S)
DECL|macro|DEBUGOUT1
mdefine_line|#define DEBUGOUT1(S, A...)
macro_line|#endif
DECL|macro|DEBUGFUNC
mdefine_line|#define DEBUGFUNC(F) DEBUGOUT(F)
DECL|macro|DEBUGOUT2
mdefine_line|#define DEBUGOUT2 DEBUGOUT1
DECL|macro|DEBUGOUT3
mdefine_line|#define DEBUGOUT3 DEBUGOUT2
DECL|macro|DEBUGOUT7
mdefine_line|#define DEBUGOUT7 DEBUGOUT3
DECL|macro|E1000_WRITE_REG
mdefine_line|#define E1000_WRITE_REG(a, reg, value) ( &bslash;&n;    ((a)-&gt;mac_type &gt;= e1000_82543) ? &bslash;&n;        (writel((value), ((a)-&gt;hw_addr + E1000_##reg))) : &bslash;&n;        (writel((value), ((a)-&gt;hw_addr + E1000_82542_##reg))))
DECL|macro|E1000_READ_REG
mdefine_line|#define E1000_READ_REG(a, reg) ( &bslash;&n;    ((a)-&gt;mac_type &gt;= e1000_82543) ? &bslash;&n;        readl((a)-&gt;hw_addr + E1000_##reg) : &bslash;&n;        readl((a)-&gt;hw_addr + E1000_82542_##reg))
DECL|macro|E1000_WRITE_REG_ARRAY
mdefine_line|#define E1000_WRITE_REG_ARRAY(a, reg, offset, value) ( &bslash;&n;    ((a)-&gt;mac_type &gt;= e1000_82543) ? &bslash;&n;        writel((value), ((a)-&gt;hw_addr + E1000_##reg + ((offset) &lt;&lt; 2))) : &bslash;&n;        writel((value), ((a)-&gt;hw_addr + E1000_82542_##reg + ((offset) &lt;&lt; 2))))
DECL|macro|E1000_READ_REG_ARRAY
mdefine_line|#define E1000_READ_REG_ARRAY(a, reg, offset) ( &bslash;&n;    ((a)-&gt;mac_type &gt;= e1000_82543) ? &bslash;&n;        readl((a)-&gt;hw_addr + E1000_##reg + ((offset) &lt;&lt; 2)) : &bslash;&n;        readl((a)-&gt;hw_addr + E1000_82542_##reg + ((offset) &lt;&lt; 2)))
macro_line|#endif /* _E1000_OSDEP_H_ */
eof
