multiline_comment|/*******************************************************************************&n;&n;  &n;  Copyright(c) 1999 - 2003 Intel Corporation. All rights reserved.&n;  &n;  This program is free software; you can redistribute it and/or modify it &n;  under the terms of the GNU General Public License as published by the Free &n;  Software Foundation; either version 2 of the License, or (at your option) &n;  any later version.&n;  &n;  This program is distributed in the hope that it will be useful, but WITHOUT &n;  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or &n;  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for &n;  more details.&n;  &n;  You should have received a copy of the GNU General Public License along with&n;  this program; if not, write to the Free Software Foundation, Inc., 59 &n;  Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n;  &n;  The full GNU General Public License is included in this distribution in the&n;  file called LICENSE.&n;  &n;  Contact Information:&n;  Linux NICS &lt;linux.nics@intel.com&gt;&n;  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497&n;*******************************************************************************/
multiline_comment|/* glue for the OS independant part of ixgb &n; * includes register access macros&n; */
macro_line|#ifndef IXGB_OSDEP_H
DECL|macro|IXGB_OSDEP_H
mdefine_line|#define IXGB_OSDEP_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/* FIXME: eliminate me */
DECL|macro|msec_delay
mdefine_line|#define msec_delay(x)&t;do { if(in_interrupt()) { &bslash;&n;&t;                &t;mdelay(x); &bslash;&n;&t;&t;&t;} else { &bslash;&n;&t;&t;&t;&t;set_current_state(TASK_UNINTERRUPTIBLE); &bslash;&n;&t;&t;&t;&t;schedule_timeout((x * HZ)/1000); &bslash;&n;&t;&t;&t;} } while(0)
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
DECL|macro|MSGOUT
mdefine_line|#define MSGOUT(S, A, B)&t;printk(KERN_DEBUG S &quot;&bslash;n&quot;, A, B)
macro_line|#if DBG
DECL|macro|ASSERT
mdefine_line|#define ASSERT(x)&t;if(!(x)) BUG()
DECL|macro|DEBUGOUT
mdefine_line|#define DEBUGOUT(S)&t;&t;printk(KERN_ERR S &quot;&bslash;n&quot;)
DECL|macro|DEBUGOUT1
mdefine_line|#define DEBUGOUT1(S, A...)&t;printk(KERN_ERR S &quot;&bslash;n&quot;, A)
macro_line|#else
DECL|macro|ASSERT
mdefine_line|#define ASSERT(x)
DECL|macro|DEBUGOUT
mdefine_line|#define DEBUGOUT(S)
DECL|macro|DEBUGOUT1
mdefine_line|#define DEBUGOUT1(S, A...)
macro_line|#endif
DECL|macro|DEBUGOUT2
mdefine_line|#define DEBUGOUT2 DEBUGOUT1
DECL|macro|DEBUGOUT3
mdefine_line|#define DEBUGOUT3 DEBUGOUT1
DECL|macro|DEBUGOUT7
mdefine_line|#define DEBUGOUT7 DEBUGOUT1
DECL|macro|DEBUGFUNC
mdefine_line|#define DEBUGFUNC(F)        DEBUGOUT(F)
DECL|macro|IXGB_WRITE_REG
mdefine_line|#define IXGB_WRITE_REG(a, reg, value) ( &bslash;&n;    writel((value), ((a)-&gt;hw_addr + IXGB_##reg)))
DECL|macro|IXGB_READ_REG
mdefine_line|#define IXGB_READ_REG(a, reg) ( &bslash;&n;    readl((a)-&gt;hw_addr + IXGB_##reg))
DECL|macro|IXGB_WRITE_REG_ARRAY
mdefine_line|#define IXGB_WRITE_REG_ARRAY(a, reg, offset, value) ( &bslash;&n;    writel((value), ((a)-&gt;hw_addr + IXGB_##reg + ((offset) &lt;&lt; 2))))
DECL|macro|IXGB_READ_REG_ARRAY
mdefine_line|#define IXGB_READ_REG_ARRAY(a, reg, offset) ( &bslash;&n;    readl((a)-&gt;hw_addr + IXGB_##reg + ((offset) &lt;&lt; 2)))
macro_line|#endif&t;&t;&t;&t;/* IXGB_OSDEP_H */
eof
