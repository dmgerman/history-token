multiline_comment|/*&n; *  cmu.c, Clock Mask Unit routines for the NEC VR4100 series.&n; *&n; *  Copyright (C) 2001-2002  MontaVista Software Inc.&n; *    Author: Yoichi Yuasa &lt;yyuasa@mvista.com or source@mvista.com&gt;&n; *  Copuright (C) 2003-2004  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * Changes:&n; *  MontaVista Software Inc. &lt;yyuasa@mvista.com&gt; or &lt;source@mvista.com&gt;&n; *  - New creation, NEC VR4122 and VR4131 are supported.&n; *  - Added support for NEC VR4111 and VR4121.&n; *&n; *  Yoichi Yuasa &lt;yuasa@hh.iij4u.or.jp&gt;&n; *  - Added support for NEC VR4133.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
DECL|macro|CMUCLKMSK_TYPE1
mdefine_line|#define CMUCLKMSK_TYPE1&t;KSEG1ADDR(0x0b000060)
DECL|macro|CMUCLKMSK_TYPE2
mdefine_line|#define CMUCLKMSK_TYPE2&t;KSEG1ADDR(0x0f000060)
DECL|macro|MSKPIU
mdefine_line|#define MSKPIU&t;&t;0x0001
DECL|macro|MSKSIU
mdefine_line|#define MSKSIU&t;&t;0x0002
DECL|macro|MSKAIU
mdefine_line|#define MSKAIU&t;&t;0x0004
DECL|macro|MSKKIU
mdefine_line|#define MSKKIU&t;&t;0x0008
DECL|macro|MSKFIR
mdefine_line|#define MSKFIR&t;&t;0x0010
DECL|macro|MSKDSIU
mdefine_line|#define MSKDSIU&t;0x0820
DECL|macro|MSKCSI
mdefine_line|#define MSKCSI&t;&t;0x0040
DECL|macro|MSKPCIU
mdefine_line|#define MSKPCIU&t;0x0080
DECL|macro|MSKSSIU
mdefine_line|#define MSKSSIU&t;0x0100
DECL|macro|MSKSHSP
mdefine_line|#define MSKSHSP&t;0x0200
DECL|macro|MSKFFIR
mdefine_line|#define MSKFFIR&t;0x0400
DECL|macro|MSKSCSI
mdefine_line|#define MSKSCSI&t;0x1000
DECL|macro|MSKPPCIU
mdefine_line|#define MSKPPCIU&t;0x2000
DECL|macro|CMUCLKMSK2
mdefine_line|#define CMUCLKMSK2&t;KSEG1ADDR(0x0f000064)
DECL|macro|MSKCEU
mdefine_line|#define MSKCEU&t;&t;0x0001
DECL|macro|MSKMAC0
mdefine_line|#define MSKMAC0&t;0x0002
DECL|macro|MSKMAC1
mdefine_line|#define MSKMAC1&t;0x0004
DECL|variable|cmu_base
r_static
r_uint32
id|cmu_base
suffix:semicolon
DECL|variable|cmuclkmsk
DECL|variable|cmuclkmsk2
r_static
r_uint16
id|cmuclkmsk
comma
id|cmuclkmsk2
suffix:semicolon
DECL|variable|cmu_lock
r_static
id|spinlock_t
id|cmu_lock
suffix:semicolon
DECL|macro|read_cmuclkmsk
mdefine_line|#define read_cmuclkmsk()&t;readw(cmu_base)
DECL|macro|read_cmuclkmsk2
mdefine_line|#define read_cmuclkmsk2()&t;readw(CMUCLKMSK2)
DECL|macro|write_cmuclkmsk
mdefine_line|#define write_cmuclkmsk()&t;writew(cmuclkmsk, cmu_base)
DECL|macro|write_cmuclkmsk2
mdefine_line|#define write_cmuclkmsk2()&t;writew(cmuclkmsk2, CMUCLKMSK2)
DECL|function|vr41xx_supply_clock
r_void
id|vr41xx_supply_clock
c_func
(paren
id|vr41xx_clock_t
id|clock
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|cmu_lock
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|clock
)paren
(brace
r_case
id|PIU_CLOCK
suffix:colon
id|cmuclkmsk
op_or_assign
id|MSKPIU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIU_CLOCK
suffix:colon
id|cmuclkmsk
op_or_assign
id|MSKSIU
op_or
id|MSKSSIU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AIU_CLOCK
suffix:colon
id|cmuclkmsk
op_or_assign
id|MSKAIU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KIU_CLOCK
suffix:colon
id|cmuclkmsk
op_or_assign
id|MSKKIU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FIR_CLOCK
suffix:colon
id|cmuclkmsk
op_or_assign
id|MSKFIR
op_or
id|MSKFFIR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DSIU_CLOCK
suffix:colon
r_if
c_cond
(paren
id|current_cpu_data.cputype
op_eq
id|CPU_VR4111
op_logical_or
id|current_cpu_data.cputype
op_eq
id|CPU_VR4121
)paren
id|cmuclkmsk
op_or_assign
id|MSKDSIU
suffix:semicolon
r_else
id|cmuclkmsk
op_or_assign
id|MSKSIU
op_or
id|MSKDSIU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CSI_CLOCK
suffix:colon
id|cmuclkmsk
op_or_assign
id|MSKCSI
op_or
id|MSKSCSI
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCIU_CLOCK
suffix:colon
id|cmuclkmsk
op_or_assign
id|MSKPCIU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HSP_CLOCK
suffix:colon
id|cmuclkmsk
op_or_assign
id|MSKSHSP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLOCK
suffix:colon
id|cmuclkmsk
op_or_assign
id|MSKPPCIU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CEU_CLOCK
suffix:colon
id|cmuclkmsk2
op_or_assign
id|MSKCEU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ETHER0_CLOCK
suffix:colon
id|cmuclkmsk2
op_or_assign
id|MSKMAC0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ETHER1_CLOCK
suffix:colon
id|cmuclkmsk2
op_or_assign
id|MSKMAC1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|clock
op_eq
id|CEU_CLOCK
op_logical_or
id|clock
op_eq
id|ETHER0_CLOCK
op_logical_or
id|clock
op_eq
id|ETHER1_CLOCK
)paren
id|write_cmuclkmsk2
c_func
(paren
)paren
suffix:semicolon
r_else
id|write_cmuclkmsk
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|cmu_lock
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_mask_clock
r_void
id|vr41xx_mask_clock
c_func
(paren
id|vr41xx_clock_t
id|clock
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|cmu_lock
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|clock
)paren
(brace
r_case
id|PIU_CLOCK
suffix:colon
id|cmuclkmsk
op_and_assign
op_complement
id|MSKPIU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIU_CLOCK
suffix:colon
r_if
c_cond
(paren
id|current_cpu_data.cputype
op_eq
id|CPU_VR4111
op_logical_or
id|current_cpu_data.cputype
op_eq
id|CPU_VR4121
)paren
(brace
id|cmuclkmsk
op_and_assign
op_complement
(paren
id|MSKSIU
op_or
id|MSKSSIU
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|cmuclkmsk
op_amp
id|MSKDSIU
)paren
id|cmuclkmsk
op_and_assign
op_complement
id|MSKSSIU
suffix:semicolon
r_else
id|cmuclkmsk
op_and_assign
op_complement
(paren
id|MSKSIU
op_or
id|MSKSSIU
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AIU_CLOCK
suffix:colon
id|cmuclkmsk
op_and_assign
op_complement
id|MSKAIU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KIU_CLOCK
suffix:colon
id|cmuclkmsk
op_and_assign
op_complement
id|MSKKIU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FIR_CLOCK
suffix:colon
id|cmuclkmsk
op_and_assign
op_complement
(paren
id|MSKFIR
op_or
id|MSKFFIR
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DSIU_CLOCK
suffix:colon
r_if
c_cond
(paren
id|current_cpu_data.cputype
op_eq
id|CPU_VR4111
op_logical_or
id|current_cpu_data.cputype
op_eq
id|CPU_VR4121
)paren
(brace
id|cmuclkmsk
op_and_assign
op_complement
id|MSKDSIU
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|cmuclkmsk
op_amp
id|MSKSIU
)paren
id|cmuclkmsk
op_and_assign
op_complement
id|MSKDSIU
suffix:semicolon
r_else
id|cmuclkmsk
op_and_assign
op_complement
(paren
id|MSKSIU
op_or
id|MSKDSIU
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CSI_CLOCK
suffix:colon
id|cmuclkmsk
op_and_assign
op_complement
(paren
id|MSKCSI
op_or
id|MSKSCSI
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCIU_CLOCK
suffix:colon
id|cmuclkmsk
op_and_assign
op_complement
id|MSKPCIU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HSP_CLOCK
suffix:colon
id|cmuclkmsk
op_and_assign
op_complement
id|MSKSHSP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLOCK
suffix:colon
id|cmuclkmsk
op_and_assign
op_complement
id|MSKPPCIU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CEU_CLOCK
suffix:colon
id|cmuclkmsk2
op_and_assign
op_complement
id|MSKCEU
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ETHER0_CLOCK
suffix:colon
id|cmuclkmsk2
op_and_assign
op_complement
id|MSKMAC0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ETHER1_CLOCK
suffix:colon
id|cmuclkmsk2
op_and_assign
op_complement
id|MSKMAC1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|clock
op_eq
id|CEU_CLOCK
op_logical_or
id|clock
op_eq
id|ETHER0_CLOCK
op_logical_or
id|clock
op_eq
id|ETHER1_CLOCK
)paren
id|write_cmuclkmsk2
c_func
(paren
)paren
suffix:semicolon
r_else
id|write_cmuclkmsk
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|cmu_lock
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_cmu_init
r_void
id|__init
id|vr41xx_cmu_init
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|current_cpu_data.cputype
)paren
(brace
r_case
id|CPU_VR4111
suffix:colon
r_case
id|CPU_VR4121
suffix:colon
id|cmu_base
op_assign
id|CMUCLKMSK_TYPE1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_VR4122
suffix:colon
r_case
id|CPU_VR4131
suffix:colon
id|cmu_base
op_assign
id|CMUCLKMSK_TYPE2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_VR4133
suffix:colon
id|cmu_base
op_assign
id|CMUCLKMSK_TYPE2
suffix:semicolon
id|cmuclkmsk2
op_assign
id|read_cmuclkmsk2
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Unexpected CPU of NEC VR4100 series&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cmuclkmsk
op_assign
id|read_cmuclkmsk
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|cmu_lock
)paren
suffix:semicolon
)brace
eof
