multiline_comment|/*&n; * bt878.c: part of the driver for the Pinnacle PCTV Sat DVB PCI card&n; *&n; * Copyright (C) 2002 Peter Hettkamp &lt;peter.hettkamp@t-online.de&gt;&n; *&n; * large parts based on the bttv driver&n; * Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@thp.uni-koeln.de)&n; *                        &amp; Marcus Metzler (mocm@thp.uni-koeln.de)&n; * (c) 1999,2000 Gerd Knorr &lt;kraxel@goldbach.in-berlin.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; * &n;&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n;&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; * Or, point your browser to http://www.gnu.org/copyleft/gpl.html&n; * &n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;dmxdev.h&quot;
macro_line|#include &quot;dvbdev.h&quot;
macro_line|#include &quot;bt878.h&quot;
macro_line|#include &quot;dst-bt878.h&quot;
multiline_comment|/**************************************/
multiline_comment|/* Miscellaneous utility  definitions */
multiline_comment|/**************************************/
DECL|variable|bt878_verbose
r_static
r_int
r_int
id|bt878_verbose
op_assign
l_int|1
suffix:semicolon
DECL|variable|bt878_debug
r_static
r_int
r_int
id|bt878_debug
suffix:semicolon
id|module_param_named
c_func
(paren
id|verbose
comma
id|bt878_verbose
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|bt878_verbose
comma
l_string|&quot;verbose startup messages, default is 1 (yes)&quot;
)paren
suffix:semicolon
id|module_param_named
c_func
(paren
id|debug
comma
id|bt878_debug
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|bt878_debug
comma
l_string|&quot;Turn on/off debugging (default:off).&quot;
)paren
suffix:semicolon
DECL|variable|bt878_num
r_int
id|bt878_num
suffix:semicolon
DECL|variable|bt878
r_struct
id|bt878
id|bt878
(braket
id|BT878_MAX
)braket
suffix:semicolon
DECL|variable|bt878_debug
id|EXPORT_SYMBOL
c_func
(paren
id|bt878_debug
)paren
suffix:semicolon
DECL|variable|bt878_verbose
id|EXPORT_SYMBOL
c_func
(paren
id|bt878_verbose
)paren
suffix:semicolon
DECL|variable|bt878_num
id|EXPORT_SYMBOL
c_func
(paren
id|bt878_num
)paren
suffix:semicolon
DECL|variable|bt878
id|EXPORT_SYMBOL
c_func
(paren
id|bt878
)paren
suffix:semicolon
DECL|macro|btwrite
mdefine_line|#define btwrite(dat,adr)    bmtwrite((dat), (bt-&gt;bt878_mem+(adr)))
DECL|macro|btread
mdefine_line|#define btread(adr)         bmtread(bt-&gt;bt878_mem+(adr))
DECL|macro|btand
mdefine_line|#define btand(dat,adr)      btwrite((dat) &amp; btread(adr), adr)
DECL|macro|btor
mdefine_line|#define btor(dat,adr)       btwrite((dat) | btread(adr), adr)
DECL|macro|btaor
mdefine_line|#define btaor(dat,mask,adr) btwrite((dat) | ((mask) &amp; btread(adr)), adr)
macro_line|#if defined(dprintk)
DECL|macro|dprintk
macro_line|#undef dprintk
macro_line|#endif
DECL|macro|dprintk
mdefine_line|#define dprintk if(bt878_debug) printk
DECL|function|bt878_mem_free
r_static
r_void
id|bt878_mem_free
c_func
(paren
r_struct
id|bt878
op_star
id|bt
)paren
(brace
r_if
c_cond
(paren
id|bt-&gt;buf_cpu
)paren
(brace
id|pci_free_consistent
c_func
(paren
id|bt-&gt;dev
comma
id|bt-&gt;buf_size
comma
id|bt-&gt;buf_cpu
comma
id|bt-&gt;buf_dma
)paren
suffix:semicolon
id|bt-&gt;buf_cpu
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bt-&gt;risc_cpu
)paren
(brace
id|pci_free_consistent
c_func
(paren
id|bt-&gt;dev
comma
id|bt-&gt;risc_size
comma
id|bt-&gt;risc_cpu
comma
id|bt-&gt;risc_dma
)paren
suffix:semicolon
id|bt-&gt;risc_cpu
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|bt878_mem_alloc
r_static
r_int
id|bt878_mem_alloc
c_func
(paren
r_struct
id|bt878
op_star
id|bt
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bt-&gt;buf_cpu
)paren
(brace
id|bt-&gt;buf_size
op_assign
l_int|128
op_star
l_int|1024
suffix:semicolon
id|bt-&gt;buf_cpu
op_assign
id|pci_alloc_consistent
c_func
(paren
id|bt-&gt;dev
comma
id|bt-&gt;buf_size
comma
op_amp
id|bt-&gt;buf_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bt-&gt;buf_cpu
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|bt-&gt;buf_cpu
comma
l_int|0
comma
id|bt-&gt;buf_size
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|bt-&gt;risc_cpu
)paren
(brace
id|bt-&gt;risc_size
op_assign
id|PAGE_SIZE
suffix:semicolon
id|bt-&gt;risc_cpu
op_assign
id|pci_alloc_consistent
c_func
(paren
id|bt-&gt;dev
comma
id|bt-&gt;risc_size
comma
op_amp
id|bt-&gt;risc_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bt-&gt;risc_cpu
)paren
(brace
id|bt878_mem_free
c_func
(paren
id|bt
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|bt-&gt;risc_cpu
comma
l_int|0
comma
id|bt-&gt;risc_size
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* RISC instructions */
DECL|macro|RISC_WRITE
mdefine_line|#define RISC_WRITE        &t;(0x01 &lt;&lt; 28)
DECL|macro|RISC_JUMP
mdefine_line|#define RISC_JUMP         &t;(0x07 &lt;&lt; 28)
DECL|macro|RISC_SYNC
mdefine_line|#define RISC_SYNC         &t;(0x08 &lt;&lt; 28)
multiline_comment|/* RISC bits */
DECL|macro|RISC_WR_SOL
mdefine_line|#define RISC_WR_SOL       &t;(1 &lt;&lt; 27)
DECL|macro|RISC_WR_EOL
mdefine_line|#define RISC_WR_EOL       &t;(1 &lt;&lt; 26)
DECL|macro|RISC_IRQ
mdefine_line|#define RISC_IRQ          &t;(1 &lt;&lt; 24)
DECL|macro|RISC_STATUS
mdefine_line|#define RISC_STATUS(status)&t;((((~status) &amp; 0x0F) &lt;&lt; 20) | ((status &amp; 0x0F) &lt;&lt; 16))
DECL|macro|RISC_SYNC_RESYNC
mdefine_line|#define RISC_SYNC_RESYNC  &t;(1 &lt;&lt; 15)
DECL|macro|RISC_SYNC_FM1
mdefine_line|#define RISC_SYNC_FM1     &t;0x06
DECL|macro|RISC_SYNC_VRO
mdefine_line|#define RISC_SYNC_VRO     &t;0x0C
DECL|macro|RISC_FLUSH
mdefine_line|#define RISC_FLUSH()&t;&t;bt-&gt;risc_pos = 0
DECL|macro|RISC_INSTR
mdefine_line|#define RISC_INSTR(instr) &t;bt-&gt;risc_cpu[bt-&gt;risc_pos++] = cpu_to_le32(instr)
DECL|function|bt878_make_risc
r_static
r_int
id|bt878_make_risc
c_func
(paren
r_struct
id|bt878
op_star
id|bt
)paren
(brace
id|bt-&gt;block_bytes
op_assign
id|bt-&gt;buf_size
op_rshift
l_int|4
suffix:semicolon
id|bt-&gt;block_count
op_assign
l_int|1
op_lshift
l_int|4
suffix:semicolon
id|bt-&gt;line_bytes
op_assign
id|bt-&gt;block_bytes
suffix:semicolon
id|bt-&gt;line_count
op_assign
id|bt-&gt;block_count
suffix:semicolon
r_while
c_loop
(paren
id|bt-&gt;line_bytes
OG
l_int|4095
)paren
(brace
id|bt-&gt;line_bytes
op_rshift_assign
l_int|1
suffix:semicolon
id|bt-&gt;line_count
op_lshift_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bt-&gt;line_count
OG
l_int|255
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bt878: buffer size error!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bt878_risc_program
r_static
r_void
id|bt878_risc_program
c_func
(paren
r_struct
id|bt878
op_star
id|bt
comma
id|u32
id|op_sync_orin
)paren
(brace
id|u32
id|buf_pos
op_assign
l_int|0
suffix:semicolon
id|u32
id|line
suffix:semicolon
id|RISC_FLUSH
c_func
(paren
)paren
suffix:semicolon
id|RISC_INSTR
c_func
(paren
id|RISC_SYNC
op_or
id|RISC_SYNC_FM1
op_or
id|op_sync_orin
)paren
suffix:semicolon
id|RISC_INSTR
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;bt878: risc len lines %u, bytes per line %u&bslash;n&quot;
comma
id|bt-&gt;line_count
comma
id|bt-&gt;line_bytes
)paren
suffix:semicolon
r_for
c_loop
(paren
id|line
op_assign
l_int|0
suffix:semicolon
id|line
OL
id|bt-&gt;line_count
suffix:semicolon
id|line
op_increment
)paren
(brace
singleline_comment|// At the beginning of every block we issue an IRQ with previous (finished) block number set
r_if
c_cond
(paren
op_logical_neg
(paren
id|buf_pos
op_mod
id|bt-&gt;block_bytes
)paren
)paren
id|RISC_INSTR
c_func
(paren
id|RISC_WRITE
op_or
id|RISC_WR_SOL
op_or
id|RISC_WR_EOL
op_or
id|RISC_IRQ
op_or
id|RISC_STATUS
c_func
(paren
(paren
(paren
id|buf_pos
op_div
id|bt-&gt;block_bytes
)paren
op_plus
(paren
id|bt-&gt;block_count
op_minus
l_int|1
)paren
)paren
op_mod
id|bt-&gt;block_count
)paren
op_or
id|bt
op_member_access_from_pointer
id|line_bytes
)paren
suffix:semicolon
r_else
id|RISC_INSTR
c_func
(paren
id|RISC_WRITE
op_or
id|RISC_WR_SOL
op_or
id|RISC_WR_EOL
op_or
id|bt-&gt;line_bytes
)paren
suffix:semicolon
id|RISC_INSTR
c_func
(paren
id|bt-&gt;buf_dma
op_plus
id|buf_pos
)paren
suffix:semicolon
id|buf_pos
op_add_assign
id|bt-&gt;line_bytes
suffix:semicolon
)brace
id|RISC_INSTR
c_func
(paren
id|RISC_SYNC
op_or
id|op_sync_orin
op_or
id|RISC_SYNC_VRO
)paren
suffix:semicolon
id|RISC_INSTR
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|RISC_INSTR
c_func
(paren
id|RISC_JUMP
)paren
suffix:semicolon
id|RISC_INSTR
c_func
(paren
id|bt-&gt;risc_dma
)paren
suffix:semicolon
id|btwrite
c_func
(paren
(paren
id|bt-&gt;line_count
op_lshift
l_int|16
)paren
op_or
id|bt-&gt;line_bytes
comma
id|BT878_APACK_LEN
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************/
multiline_comment|/* Start/Stop grabbing funcs */
multiline_comment|/*****************************/
DECL|function|bt878_start
r_void
id|bt878_start
c_func
(paren
r_struct
id|bt878
op_star
id|bt
comma
id|u32
id|controlreg
comma
id|u32
id|op_sync_orin
comma
id|u32
id|irq_err_ignore
)paren
(brace
id|u32
id|int_mask
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;bt878 debug: bt878_start (ctl=%8.8x)&bslash;n&quot;
comma
id|controlreg
)paren
suffix:semicolon
multiline_comment|/* complete the writing of the risc dma program now we have&n;&t; * the card specifics&n;&t; */
id|bt878_risc_program
c_func
(paren
id|bt
comma
id|op_sync_orin
)paren
suffix:semicolon
id|controlreg
op_and_assign
op_complement
l_int|0x1f
suffix:semicolon
id|controlreg
op_or_assign
l_int|0x1b
suffix:semicolon
id|btwrite
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|bt-&gt;risc_dma
)paren
comma
id|BT878_ARISC_START
)paren
suffix:semicolon
multiline_comment|/* original int mask had :&n;&t; *    6    2    8    4    0&n;&t; * 1111 1111 1000 0000 0000&n;&t; * SCERR|OCERR|PABORT|RIPERR|FDSR|FTRGT|FBUS|RISCI&n;&t; * Hacked for DST to:&n;&t; * SCERR | OCERR | FDSR | FTRGT | FBUS | RISCI&n;&t; */
id|int_mask
op_assign
id|BT878_ASCERR
op_or
id|BT878_AOCERR
op_or
id|BT878_APABORT
op_or
id|BT878_ARIPERR
op_or
id|BT878_APPERR
op_or
id|BT878_AFDSR
op_or
id|BT878_AFTRGT
op_or
id|BT878_AFBUS
op_or
id|BT878_ARISCI
suffix:semicolon
multiline_comment|/* ignore pesky bits */
id|int_mask
op_and_assign
op_complement
id|irq_err_ignore
suffix:semicolon
id|btwrite
c_func
(paren
id|int_mask
comma
id|BT878_AINT_MASK
)paren
suffix:semicolon
id|btwrite
c_func
(paren
id|controlreg
comma
id|BT878_AGPIO_DMA_CTL
)paren
suffix:semicolon
)brace
DECL|function|bt878_stop
r_void
id|bt878_stop
c_func
(paren
r_struct
id|bt878
op_star
id|bt
)paren
(brace
id|u32
id|stat
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;bt878 debug: bt878_stop&bslash;n&quot;
)paren
suffix:semicolon
id|btwrite
c_func
(paren
l_int|0
comma
id|BT878_AINT_MASK
)paren
suffix:semicolon
id|btand
c_func
(paren
op_complement
l_int|0x13
comma
id|BT878_AGPIO_DMA_CTL
)paren
suffix:semicolon
r_do
(brace
id|stat
op_assign
id|btread
c_func
(paren
id|BT878_AINT_STAT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|stat
op_amp
id|BT878_ARISC_EN
)paren
)paren
r_break
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OL
l_int|500
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;bt878(%d) debug: bt878_stop, i=%d, stat=0x%8.8x&bslash;n&quot;
comma
id|bt-&gt;nr
comma
id|i
comma
id|stat
)paren
suffix:semicolon
)brace
DECL|variable|bt878_start
id|EXPORT_SYMBOL
c_func
(paren
id|bt878_start
)paren
suffix:semicolon
DECL|variable|bt878_stop
id|EXPORT_SYMBOL
c_func
(paren
id|bt878_stop
)paren
suffix:semicolon
multiline_comment|/*****************************/
multiline_comment|/* Interrupt service routine */
multiline_comment|/*****************************/
DECL|function|bt878_irq
r_static
id|irqreturn_t
id|bt878_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u32
id|stat
comma
id|astat
comma
id|mask
suffix:semicolon
r_int
id|count
suffix:semicolon
r_struct
id|bt878
op_star
id|bt
suffix:semicolon
id|bt
op_assign
(paren
r_struct
id|bt878
op_star
)paren
id|dev_id
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|stat
op_assign
id|btread
c_func
(paren
id|BT878_AINT_STAT
)paren
suffix:semicolon
id|mask
op_assign
id|btread
c_func
(paren
id|BT878_AINT_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|astat
op_assign
(paren
id|stat
op_amp
id|mask
)paren
)paren
)paren
r_return
id|IRQ_NONE
suffix:semicolon
multiline_comment|/* this interrupt is not for me */
multiline_comment|/*&t;&t;dprintk(&quot;bt878(%d) debug: irq count %d, stat 0x%8.8x, mask 0x%8.8x&bslash;n&quot;,bt-&gt;nr,count,stat,mask); */
id|btwrite
c_func
(paren
id|astat
comma
id|BT878_AINT_STAT
)paren
suffix:semicolon
multiline_comment|/* try to clear interupt condition */
r_if
c_cond
(paren
id|astat
op_amp
(paren
id|BT878_ASCERR
op_or
id|BT878_AOCERR
)paren
)paren
(brace
r_if
c_cond
(paren
id|bt878_verbose
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bt878(%d): irq%s%s risc_pc=%08x&bslash;n&quot;
comma
id|bt-&gt;nr
comma
(paren
id|astat
op_amp
id|BT878_ASCERR
)paren
ques
c_cond
l_string|&quot; SCERR&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|astat
op_amp
id|BT878_AOCERR
)paren
ques
c_cond
l_string|&quot; OCERR&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|btread
c_func
(paren
id|BT878_ARISC_PC
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|astat
op_amp
(paren
id|BT878_APABORT
op_or
id|BT878_ARIPERR
op_or
id|BT878_APPERR
)paren
)paren
(brace
r_if
c_cond
(paren
id|bt878_verbose
)paren
(brace
id|printk
(paren
l_string|&quot;bt878(%d): irq%s%s%s risc_pc=%08x&bslash;n&quot;
comma
id|bt-&gt;nr
comma
(paren
id|astat
op_amp
id|BT878_APABORT
)paren
ques
c_cond
l_string|&quot; PABORT&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|astat
op_amp
id|BT878_ARIPERR
)paren
ques
c_cond
l_string|&quot; RIPERR&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|astat
op_amp
id|BT878_APPERR
)paren
ques
c_cond
l_string|&quot; PPERR&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|btread
c_func
(paren
id|BT878_ARISC_PC
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|astat
op_amp
(paren
id|BT878_AFDSR
op_or
id|BT878_AFTRGT
op_or
id|BT878_AFBUS
)paren
)paren
(brace
r_if
c_cond
(paren
id|bt878_verbose
)paren
(brace
id|printk
(paren
l_string|&quot;bt878(%d): irq%s%s%s risc_pc=%08x&bslash;n&quot;
comma
id|bt-&gt;nr
comma
(paren
id|astat
op_amp
id|BT878_AFDSR
)paren
ques
c_cond
l_string|&quot; FDSR&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|astat
op_amp
id|BT878_AFTRGT
)paren
ques
c_cond
l_string|&quot; FTRGT&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|astat
op_amp
id|BT878_AFBUS
)paren
ques
c_cond
l_string|&quot; FBUS&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|btread
c_func
(paren
id|BT878_ARISC_PC
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|astat
op_amp
id|BT878_ARISCI
)paren
(brace
id|bt-&gt;finished_block
op_assign
(paren
id|stat
op_amp
id|BT878_ARISCS
)paren
op_rshift
l_int|28
suffix:semicolon
id|tasklet_schedule
c_func
(paren
op_amp
id|bt-&gt;tasklet
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|20
)paren
(brace
id|btwrite
c_func
(paren
l_int|0
comma
id|BT878_AINT_MASK
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;bt878(%d): IRQ lockup, cleared int mask&bslash;n&quot;
comma
id|bt-&gt;nr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_int
DECL|function|bt878_device_control
id|bt878_device_control
c_func
(paren
r_struct
id|bt878
op_star
id|bt
comma
r_int
r_int
id|cmd
comma
r_union
id|dst_gpio_packet
op_star
id|mp
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|down_interruptible
(paren
op_amp
id|bt-&gt;gpio_lock
)paren
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
multiline_comment|/* special gpio signal */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|DST_IG_ENABLE
suffix:colon
singleline_comment|// dprintk(&quot;dvb_bt8xx: dst enable mask 0x%02x enb 0x%02x &bslash;n&quot;, mp-&gt;dstg.enb.mask, mp-&gt;dstg.enb.enable);
id|retval
op_assign
id|bttv_gpio_enable
c_func
(paren
id|bt-&gt;bttv_nr
comma
id|mp-&gt;enb.mask
comma
id|mp-&gt;enb.enable
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DST_IG_WRITE
suffix:colon
singleline_comment|// dprintk(&quot;dvb_bt8xx: dst write gpio mask 0x%02x out 0x%02x&bslash;n&quot;, mp-&gt;dstg.outp.mask, mp-&gt;dstg.outp.highvals);
id|retval
op_assign
id|bttv_write_gpio
c_func
(paren
id|bt-&gt;bttv_nr
comma
id|mp-&gt;outp.mask
comma
id|mp-&gt;outp.highvals
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DST_IG_READ
suffix:colon
multiline_comment|/* read */
id|retval
op_assign
id|bttv_read_gpio
c_func
(paren
id|bt-&gt;bttv_nr
comma
op_amp
id|mp-&gt;rd.value
)paren
suffix:semicolon
singleline_comment|// dprintk(&quot;dvb_bt8xx: dst read gpio 0x%02x&bslash;n&quot;, (unsigned)mp-&gt;dstg.rd.value);
r_break
suffix:semicolon
r_case
id|DST_IG_TS
suffix:colon
multiline_comment|/* Set packet size */
id|bt-&gt;TS_Size
op_assign
id|mp-&gt;psize
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|bt-&gt;gpio_lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|bt878_device_control
id|EXPORT_SYMBOL
c_func
(paren
id|bt878_device_control
)paren
suffix:semicolon
DECL|function|bt878_find_by_i2c_adap
r_struct
id|bt878
op_star
id|bt878_find_by_i2c_adap
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
r_int
r_int
id|card_nr
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;bt878 find by dvb adap: checking &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|adapter-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|card_nr
op_assign
l_int|0
suffix:semicolon
id|card_nr
OL
id|bt878_num
suffix:semicolon
id|card_nr
op_increment
)paren
(brace
r_if
c_cond
(paren
id|bt878
(braket
id|card_nr
)braket
dot
id|adapter
op_eq
id|adapter
)paren
r_return
op_amp
id|bt878
(braket
id|card_nr
)braket
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;bt878 find by dvb adap: NOT found &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|adapter-&gt;name
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|bt878_find_by_i2c_adap
id|EXPORT_SYMBOL
c_func
(paren
id|bt878_find_by_i2c_adap
)paren
suffix:semicolon
multiline_comment|/***********************/
multiline_comment|/* PCI device handling */
multiline_comment|/***********************/
DECL|function|bt878_probe
r_static
r_int
id|__devinit
id|bt878_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|pci_id
)paren
(brace
r_int
id|result
suffix:semicolon
r_int
r_char
id|lat
suffix:semicolon
r_struct
id|bt878
op_star
id|bt
suffix:semicolon
macro_line|#if defined(__powerpc__)
r_int
r_int
id|cmd
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;bt878: Bt878 AUDIO function found (%d).&bslash;n&quot;
comma
id|bt878_num
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|bt
op_assign
op_amp
id|bt878
(braket
id|bt878_num
)braket
suffix:semicolon
id|bt-&gt;dev
op_assign
id|dev
suffix:semicolon
id|bt-&gt;nr
op_assign
id|bt878_num
suffix:semicolon
id|bt-&gt;shutdown
op_assign
l_int|0
suffix:semicolon
id|bt-&gt;id
op_assign
id|dev-&gt;device
suffix:semicolon
id|bt-&gt;irq
op_assign
id|dev-&gt;irq
suffix:semicolon
id|bt-&gt;bt878_adr
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
id|pci_resource_len
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
l_string|&quot;bt878&quot;
)paren
)paren
(brace
id|result
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|fail0
suffix:semicolon
)brace
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_CLASS_REVISION
comma
op_amp
id|bt-&gt;revision
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
op_amp
id|lat
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;bt878(%d): Bt%x (rev %d) at %02x:%02x.%x, &quot;
comma
id|bt878_num
comma
id|bt-&gt;id
comma
id|bt-&gt;revision
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irq: %d, latency: %d, memory: 0x%lx&bslash;n&quot;
comma
id|bt-&gt;irq
comma
id|lat
comma
id|bt-&gt;bt878_adr
)paren
suffix:semicolon
macro_line|#if defined(__powerpc__)
multiline_comment|/* on OpenFirmware machines (PowerMac at least), PCI memory cycle */
multiline_comment|/* response on cards with no firmware is not enabled by OF */
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|cmd
op_assign
(paren
id|cmd
op_or
id|PCI_COMMAND_MEMORY
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __sparc__
id|bt-&gt;bt878_mem
op_assign
(paren
r_int
r_char
op_star
)paren
id|bt-&gt;bt878_adr
suffix:semicolon
macro_line|#else
id|bt-&gt;bt878_mem
op_assign
id|ioremap
c_func
(paren
id|bt-&gt;bt878_adr
comma
l_int|0x1000
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* clear interrupt mask */
id|btwrite
c_func
(paren
l_int|0
comma
id|BT848_INT_MASK
)paren
suffix:semicolon
id|result
op_assign
id|request_irq
c_func
(paren
id|bt-&gt;irq
comma
id|bt878_irq
comma
id|SA_SHIRQ
op_or
id|SA_INTERRUPT
comma
l_string|&quot;bt878&quot;
comma
(paren
r_void
op_star
)paren
id|bt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|EINVAL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;bt878(%d): Bad irq number or handler&bslash;n&quot;
comma
id|bt878_num
)paren
suffix:semicolon
r_goto
id|fail1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|EBUSY
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;bt878(%d): IRQ %d busy, change your PnP config in BIOS&bslash;n&quot;
comma
id|bt878_num
comma
id|bt-&gt;irq
)paren
suffix:semicolon
r_goto
id|fail1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_goto
id|fail1
suffix:semicolon
id|pci_set_master
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|dev
comma
id|bt
)paren
suffix:semicolon
multiline_comment|/*        if(init_bt878(btv) &lt; 0) {&n;                bt878_remove(dev);&n;                return -EIO;&n;        }&n;*/
r_if
c_cond
(paren
(paren
id|result
op_assign
id|bt878_mem_alloc
c_func
(paren
id|bt
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bt878: failed to allocate memory!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail2
suffix:semicolon
)brace
id|bt878_make_risc
c_func
(paren
id|bt
)paren
suffix:semicolon
id|btwrite
c_func
(paren
l_int|0
comma
id|BT878_AINT_MASK
)paren
suffix:semicolon
id|bt878_num
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail2
suffix:colon
id|free_irq
c_func
(paren
id|bt-&gt;irq
comma
id|bt
)paren
suffix:semicolon
id|fail1
suffix:colon
id|release_mem_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|bt-&gt;dev
comma
l_int|0
)paren
comma
id|pci_resource_len
c_func
(paren
id|bt-&gt;dev
comma
l_int|0
)paren
)paren
suffix:semicolon
id|fail0
suffix:colon
id|pci_disable_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|bt878_remove
r_static
r_void
id|__devexit
id|bt878_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci_dev
)paren
(brace
id|u8
id|command
suffix:semicolon
r_struct
id|bt878
op_star
id|bt
op_assign
id|pci_get_drvdata
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bt878_verbose
)paren
id|printk
c_func
(paren
l_string|&quot;bt878(%d): unloading&bslash;n&quot;
comma
id|bt-&gt;nr
)paren
suffix:semicolon
multiline_comment|/* turn off all capturing, DMA and IRQs */
id|btand
c_func
(paren
op_complement
l_int|0x13
comma
id|BT878_AGPIO_DMA_CTL
)paren
suffix:semicolon
multiline_comment|/* first disable interrupts before unmapping the memory! */
id|btwrite
c_func
(paren
l_int|0
comma
id|BT878_AINT_MASK
)paren
suffix:semicolon
id|btwrite
c_func
(paren
op_complement
l_int|0U
comma
id|BT878_AINT_STAT
)paren
suffix:semicolon
multiline_comment|/* disable PCI bus-mastering */
id|pci_read_config_byte
c_func
(paren
id|bt-&gt;dev
comma
id|PCI_COMMAND
comma
op_amp
id|command
)paren
suffix:semicolon
multiline_comment|/* Should this be &amp;=~ ?? */
id|command
op_and_assign
op_complement
id|PCI_COMMAND_MASTER
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|bt-&gt;dev
comma
id|PCI_COMMAND
comma
id|command
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|bt-&gt;irq
comma
id|bt
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;bt878_mem: 0x%p.&bslash;n&quot;
comma
id|bt-&gt;bt878_mem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bt-&gt;bt878_mem
)paren
id|iounmap
c_func
(paren
id|bt-&gt;bt878_mem
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|bt-&gt;dev
comma
l_int|0
)paren
comma
id|pci_resource_len
c_func
(paren
id|bt-&gt;dev
comma
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/* wake up any waiting processes&n;&t;   because shutdown flag is set, no new processes (in this queue)&n;&t;   are expected&n;&t; */
id|bt-&gt;shutdown
op_assign
l_int|1
suffix:semicolon
id|bt878_mem_free
c_func
(paren
id|bt
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pci_dev
comma
l_int|NULL
)paren
suffix:semicolon
id|pci_disable_device
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|bt878_pci_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_VENDOR_ID_BROOKTREE
comma
id|PCI_DEVICE_ID_BROOKTREE_878
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|bt878_pci_tbl
)paren
suffix:semicolon
DECL|variable|bt878_pci_driver
r_static
r_struct
id|pci_driver
id|bt878_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;bt878&quot;
comma
dot
id|id_table
op_assign
id|bt878_pci_tbl
comma
dot
id|probe
op_assign
id|bt878_probe
comma
dot
id|remove
op_assign
id|bt878_remove
comma
)brace
suffix:semicolon
DECL|variable|bt878_pci_driver_registered
r_static
r_int
id|bt878_pci_driver_registered
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This will be used later by dvb-bt8xx to only use the audio&n; * dma of certain cards */
DECL|function|bt878_find_audio_dma
r_int
id|bt878_find_audio_dma
c_func
(paren
r_void
)paren
(brace
singleline_comment|// pci_register_driver(&amp;bt878_pci_driver);
id|bt878_pci_driver_registered
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|bt878_find_audio_dma
id|EXPORT_SYMBOL
c_func
(paren
id|bt878_find_audio_dma
)paren
suffix:semicolon
multiline_comment|/*******************************/
multiline_comment|/* Module management functions */
multiline_comment|/*******************************/
DECL|function|bt878_init_module
r_int
id|bt878_init_module
c_func
(paren
r_void
)paren
(brace
id|bt878_num
op_assign
l_int|0
suffix:semicolon
id|bt878_pci_driver_registered
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;bt878: AUDIO driver version %d.%d.%d loaded&bslash;n&quot;
comma
(paren
id|BT878_VERSION_CODE
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
comma
(paren
id|BT878_VERSION_CODE
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|BT878_VERSION_CODE
op_amp
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/*&n;        bt878_check_chipset();&n;*/
multiline_comment|/* later we register inside of bt878_find_audio_dma&n;&t; * because we may want to ignore certain cards */
id|bt878_pci_driver_registered
op_assign
l_int|1
suffix:semicolon
r_return
id|pci_module_init
c_func
(paren
op_amp
id|bt878_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|bt878_cleanup_module
r_void
id|bt878_cleanup_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|bt878_pci_driver_registered
)paren
(brace
id|bt878_pci_driver_registered
op_assign
l_int|0
suffix:semicolon
id|pci_unregister_driver
c_func
(paren
op_amp
id|bt878_pci_driver
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|variable|bt878_init_module
id|EXPORT_SYMBOL
c_func
(paren
id|bt878_init_module
)paren
suffix:semicolon
DECL|variable|bt878_cleanup_module
id|EXPORT_SYMBOL
c_func
(paren
id|bt878_cleanup_module
)paren
suffix:semicolon
DECL|variable|bt878_init_module
id|module_init
c_func
(paren
id|bt878_init_module
)paren
suffix:semicolon
DECL|variable|bt878_cleanup_module
id|module_exit
c_func
(paren
id|bt878_cleanup_module
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
