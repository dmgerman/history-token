multiline_comment|/*&n;    saa7146.o - driver for generic saa7146-based hardware&n;&n;    Copyright (C) 1998-2003 Michael Hunold &lt;michael@mihu.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#include &lt;media/saa7146.h&gt;
multiline_comment|/* global variables */
DECL|variable|saa7146_devices
r_struct
id|list_head
id|saa7146_devices
suffix:semicolon
DECL|variable|saa7146_devices_lock
r_struct
id|semaphore
id|saa7146_devices_lock
suffix:semicolon
DECL|variable|initialized
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
DECL|variable|saa7146_num
r_static
r_int
id|saa7146_num
op_assign
l_int|0
suffix:semicolon
DECL|variable|saa7146_debug
r_int
r_int
id|saa7146_debug
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|saa7146_debug
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|saa7146_debug
comma
l_string|&quot;debug level (default: 0)&quot;
)paren
suffix:semicolon
macro_line|#if 0
r_static
r_void
id|dump_registers
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|INFO
c_func
(paren
(paren
l_string|&quot; @ %li jiffies:&bslash;n&quot;
comma
id|jiffies
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|0x148
suffix:semicolon
id|i
op_add_assign
l_int|4
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;0x%03x: 0x%08x&bslash;n&quot;
comma
id|i
comma
id|saa7146_read
c_func
(paren
id|dev
comma
id|i
)paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/****************************************************************************&n; * gpio and debi helper functions&n; ****************************************************************************/
multiline_comment|/* write &quot;data&quot; to the gpio-pin &quot;pin&quot; -- unused */
DECL|function|saa7146_set_gpio
r_void
id|saa7146_set_gpio
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
id|u8
id|pin
comma
id|u8
id|data
)paren
(brace
id|u32
id|value
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* sanity check */
r_if
c_cond
(paren
id|pin
OG
l_int|3
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* read old register contents */
id|value
op_assign
id|saa7146_read
c_func
(paren
id|dev
comma
id|GPIO_CTRL
)paren
suffix:semicolon
id|value
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
(paren
l_int|8
op_star
id|pin
)paren
)paren
suffix:semicolon
id|value
op_or_assign
(paren
id|data
op_lshift
(paren
l_int|8
op_star
id|pin
)paren
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|GPIO_CTRL
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/* This DEBI code is based on the saa7146 Stradis driver by Nathan Laredo */
DECL|function|saa7146_wait_for_debi_done
r_int
id|saa7146_wait_for_debi_done
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_int
id|nobusyloop
)paren
(brace
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/* wait for registers to be programmed */
id|start
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|saa7146_read
c_func
(paren
id|dev
comma
id|MC2
)paren
op_amp
l_int|2
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|start
op_plus
id|HZ
op_div
l_int|20
)paren
)paren
(brace
id|DEB_S
c_func
(paren
(paren
l_string|&quot;timed out while waiting for registers getting programmed&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nobusyloop
)paren
id|msleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* wait for transfer to complete */
id|start
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|saa7146_read
c_func
(paren
id|dev
comma
id|PSR
)paren
op_amp
id|SPCI_DEBI_S
)paren
)paren
r_break
suffix:semicolon
id|saa7146_read
c_func
(paren
id|dev
comma
id|MC2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|start
op_plus
id|HZ
op_div
l_int|4
)paren
)paren
(brace
id|DEB_S
c_func
(paren
(paren
l_string|&quot;timed out while waiting for transfer completion&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nobusyloop
)paren
id|msleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; * general helper functions&n; ****************************************************************************/
multiline_comment|/* this is videobuf_vmalloc_to_sg() from video-buf.c&n;   make sure virt has been allocated with vmalloc_32(), otherwise the BUG()&n;   may be triggered on highmem machines */
DECL|function|vmalloc_to_sg
r_static
r_struct
id|scatterlist
op_star
id|vmalloc_to_sg
c_func
(paren
r_int
r_char
op_star
id|virt
comma
r_int
id|nr_pages
)paren
(brace
r_struct
id|scatterlist
op_star
id|sglist
suffix:semicolon
r_struct
id|page
op_star
id|pg
suffix:semicolon
r_int
id|i
suffix:semicolon
id|sglist
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|scatterlist
)paren
op_star
id|nr_pages
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|sglist
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|sglist
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|scatterlist
)paren
op_star
id|nr_pages
)paren
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
id|nr_pages
suffix:semicolon
id|i
op_increment
comma
id|virt
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|pg
op_assign
id|vmalloc_to_page
c_func
(paren
id|virt
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|pg
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
id|PageHighMem
c_func
(paren
id|pg
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|sglist
(braket
id|i
)braket
dot
id|page
op_assign
id|pg
suffix:semicolon
id|sglist
(braket
id|i
)braket
dot
id|length
op_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_return
id|sglist
suffix:semicolon
id|err
suffix:colon
id|kfree
c_func
(paren
id|sglist
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/********************************************************************************/
multiline_comment|/* common page table functions */
DECL|function|saa7146_vmalloc_build_pgtable
r_char
op_star
id|saa7146_vmalloc_build_pgtable
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
id|length
comma
r_struct
id|saa7146_pgtable
op_star
id|pt
)paren
(brace
r_int
id|pages
op_assign
(paren
id|length
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
suffix:semicolon
r_char
op_star
id|mem
op_assign
id|vmalloc_32
c_func
(paren
id|length
)paren
suffix:semicolon
r_int
id|slen
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|mem
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pt-&gt;slist
op_assign
id|vmalloc_to_sg
c_func
(paren
id|mem
comma
id|pages
)paren
)paren
)paren
(brace
id|vfree
c_func
(paren
id|mem
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|saa7146_pgtable_alloc
c_func
(paren
id|pci
comma
id|pt
)paren
)paren
(brace
id|kfree
c_func
(paren
id|pt-&gt;slist
)paren
suffix:semicolon
id|pt-&gt;slist
op_assign
l_int|NULL
suffix:semicolon
id|vfree
c_func
(paren
id|mem
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|slen
op_assign
id|pci_map_sg
c_func
(paren
id|pci
comma
id|pt-&gt;slist
comma
id|pages
comma
id|PCI_DMA_FROMDEVICE
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|saa7146_pgtable_build_single
c_func
(paren
id|pci
comma
id|pt
comma
id|pt-&gt;slist
comma
id|slen
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|mem
suffix:semicolon
)brace
DECL|function|saa7146_pgtable_free
r_void
id|saa7146_pgtable_free
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|saa7146_pgtable
op_star
id|pt
)paren
(brace
r_if
c_cond
(paren
l_int|NULL
op_eq
id|pt-&gt;cpu
)paren
r_return
suffix:semicolon
id|pci_free_consistent
c_func
(paren
id|pci
comma
id|pt-&gt;size
comma
id|pt-&gt;cpu
comma
id|pt-&gt;dma
)paren
suffix:semicolon
id|pt-&gt;cpu
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_ne
id|pt-&gt;slist
)paren
(brace
id|kfree
c_func
(paren
id|pt-&gt;slist
)paren
suffix:semicolon
id|pt-&gt;slist
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|saa7146_pgtable_alloc
r_int
id|saa7146_pgtable_alloc
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|saa7146_pgtable
op_star
id|pt
)paren
(brace
id|u32
op_star
id|cpu
suffix:semicolon
id|dma_addr_t
id|dma_addr
suffix:semicolon
id|cpu
op_assign
id|pci_alloc_consistent
c_func
(paren
id|pci
comma
id|PAGE_SIZE
comma
op_amp
id|dma_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|cpu
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|pt-&gt;size
op_assign
id|PAGE_SIZE
suffix:semicolon
id|pt-&gt;cpu
op_assign
id|cpu
suffix:semicolon
id|pt-&gt;dma
op_assign
id|dma_addr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7146_pgtable_build_single
r_int
id|saa7146_pgtable_build_single
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|saa7146_pgtable
op_star
id|pt
comma
r_struct
id|scatterlist
op_star
id|list
comma
r_int
id|sglen
)paren
(brace
id|u32
op_star
id|ptr
comma
id|fill
suffix:semicolon
r_int
id|nr_pages
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|p
suffix:semicolon
id|BUG_ON
c_func
(paren
l_int|0
op_eq
id|sglen
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|list-&gt;offset
OG
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* if we have a user buffer, the first page may not be&n;&t;   aligned to a page boundary. */
id|pt-&gt;offset
op_assign
id|list-&gt;offset
suffix:semicolon
id|ptr
op_assign
id|pt-&gt;cpu
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
id|sglen
suffix:semicolon
id|i
op_increment
comma
id|list
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t;printk(&quot;i:%d, adr:0x%08x, len:%d, offset:%d&bslash;n&quot;, i,sg_dma_address(list), sg_dma_len(list), list-&gt;offset);&n;*/
r_for
c_loop
(paren
id|p
op_assign
l_int|0
suffix:semicolon
id|p
op_star
l_int|4096
OL
id|list-&gt;length
suffix:semicolon
id|p
op_increment
comma
id|ptr
op_increment
)paren
(brace
op_star
id|ptr
op_assign
id|cpu_to_le32
c_func
(paren
id|sg_dma_address
c_func
(paren
id|list
)paren
op_plus
id|p
op_star
l_int|4096
)paren
suffix:semicolon
id|nr_pages
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/* safety; fill the page table up with the last valid page */
id|fill
op_assign
op_star
(paren
id|ptr
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nr_pages
suffix:semicolon
id|i
OL
l_int|1024
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
id|ptr
op_increment
op_assign
id|fill
suffix:semicolon
)brace
multiline_comment|/*&n;&t;ptr = pt-&gt;cpu;&n;&t;printk(&quot;offset: %d&bslash;n&quot;,pt-&gt;offset);&n;&t;for(i=0;i&lt;5;i++) {&n;&t;&t;printk(&quot;ptr1 %d: 0x%08x&bslash;n&quot;,i,ptr[i]);&n;&t;}&n;*/
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/********************************************************************************/
multiline_comment|/* gpio functions */
DECL|function|saa7146_setgpio
r_void
id|saa7146_setgpio
c_func
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_int
id|port
comma
id|u32
id|data
)paren
(brace
id|u32
id|val
op_assign
l_int|0
suffix:semicolon
id|val
op_assign
id|saa7146_read
c_func
(paren
id|dev
comma
id|GPIO_CTRL
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
l_int|0xff
op_lshift
(paren
l_int|8
op_star
(paren
id|port
)paren
)paren
)paren
suffix:semicolon
id|val
op_or_assign
(paren
id|data
)paren
op_lshift
(paren
l_int|8
op_star
(paren
id|port
)paren
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|GPIO_CTRL
comma
id|val
)paren
suffix:semicolon
)brace
multiline_comment|/********************************************************************************/
multiline_comment|/* interrupt handler */
DECL|function|interrupt_hw
r_static
id|irqreturn_t
id|interrupt_hw
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
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|dev_id
suffix:semicolon
id|u32
id|isr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* read out the interrupt status register */
id|isr
op_assign
id|saa7146_read
c_func
(paren
id|dev
comma
id|ISR
)paren
suffix:semicolon
multiline_comment|/* is this our interrupt? */
r_if
c_cond
(paren
l_int|0
op_eq
id|isr
)paren
(brace
multiline_comment|/* nope, some other device */
r_return
id|IRQ_NONE
suffix:semicolon
)brace
id|saa7146_write
c_func
(paren
id|dev
comma
id|ISR
comma
id|isr
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|dev-&gt;ext
)paren
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|dev-&gt;ext-&gt;irq_mask
op_amp
id|isr
)paren
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ne
id|dev-&gt;ext-&gt;irq_func
)paren
(brace
id|dev-&gt;ext
op_member_access_from_pointer
id|irq_func
c_func
(paren
id|dev
comma
op_amp
id|isr
)paren
suffix:semicolon
)brace
id|isr
op_and_assign
op_complement
id|dev-&gt;ext-&gt;irq_mask
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|isr
op_amp
(paren
id|MASK_27
)paren
)paren
)paren
(brace
id|DEB_INT
c_func
(paren
(paren
l_string|&quot;irq: RPS0 (0x%08x).&bslash;n&quot;
comma
id|isr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|dev-&gt;vv_data
op_logical_and
l_int|0
op_ne
id|dev-&gt;vv_callback
)paren
(brace
id|dev
op_member_access_from_pointer
id|vv_callback
c_func
(paren
id|dev
comma
id|isr
)paren
suffix:semicolon
)brace
id|isr
op_and_assign
op_complement
id|MASK_27
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|isr
op_amp
(paren
id|MASK_28
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ne
id|dev-&gt;vv_data
op_logical_and
l_int|0
op_ne
id|dev-&gt;vv_callback
)paren
(brace
id|dev
op_member_access_from_pointer
id|vv_callback
c_func
(paren
id|dev
comma
id|isr
)paren
suffix:semicolon
)brace
id|isr
op_and_assign
op_complement
id|MASK_28
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|isr
op_amp
(paren
id|MASK_16
op_or
id|MASK_17
)paren
)paren
)paren
(brace
id|u32
id|status
op_assign
id|saa7146_read
c_func
(paren
id|dev
comma
id|I2C_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
l_int|0x3
op_eq
(paren
id|status
op_amp
l_int|0x3
)paren
)paren
op_logical_or
(paren
l_int|0
op_eq
(paren
id|status
op_amp
l_int|0x1
)paren
)paren
)paren
(brace
id|SAA7146_IER_DISABLE
c_func
(paren
id|dev
comma
id|MASK_16
op_or
id|MASK_17
)paren
suffix:semicolon
multiline_comment|/* only wake up if we expect something */
r_if
c_cond
(paren
l_int|0
op_ne
id|dev-&gt;i2c_op
)paren
(brace
id|u32
id|psr
op_assign
(paren
id|saa7146_read
c_func
(paren
id|dev
comma
id|PSR
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0x2
suffix:semicolon
id|u32
id|ssr
op_assign
(paren
id|saa7146_read
c_func
(paren
id|dev
comma
id|SSR
)paren
op_rshift
l_int|17
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;irq: i2c, status: 0x%08x, psr:0x%02x, ssr:0x%02x).&bslash;n&quot;
comma
id|status
comma
id|psr
comma
id|ssr
)paren
)paren
suffix:semicolon
id|dev-&gt;i2c_op
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|dev-&gt;i2c_wq
)paren
suffix:semicolon
)brace
r_else
(brace
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;unexpected irq: i2c, status: 0x%08x, isr %#x&bslash;n&quot;
comma
id|status
comma
id|isr
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|DEB_I2C
c_func
(paren
(paren
l_string|&quot;unhandled irq: i2c, status: 0x%08x, isr %#x&bslash;n&quot;
comma
id|status
comma
id|isr
)paren
)paren
suffix:semicolon
)brace
id|isr
op_and_assign
op_complement
(paren
id|MASK_16
op_or
id|MASK_17
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_ne
id|isr
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;warning: interrupt enabled, but not handled properly.(0x%08x)&bslash;n&quot;
comma
id|isr
)paren
)paren
suffix:semicolon
id|ERR
c_func
(paren
(paren
l_string|&quot;disabling interrupt source(s)!&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|SAA7146_IER_DISABLE
c_func
(paren
id|dev
comma
id|isr
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*********************************************************************************/
multiline_comment|/* configuration-functions                                                       */
DECL|function|saa7146_init_one
r_static
r_int
id|saa7146_init_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_struct
id|saa7146_pci_extension_data
op_star
id|pci_ext
op_assign
(paren
r_struct
id|saa7146_pci_extension_data
op_star
)paren
id|ent-&gt;driver_data
suffix:semicolon
r_struct
id|saa7146_extension
op_star
id|ext
op_assign
id|pci_ext-&gt;ext
suffix:semicolon
r_struct
id|saa7146_dev
op_star
id|dev
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|saa7146_dev
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;out of memory.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* clear out mem for sure */
id|memset
c_func
(paren
id|dev
comma
l_int|0x0
comma
r_sizeof
(paren
r_struct
id|saa7146_dev
)paren
)paren
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;pci:%p&bslash;n&quot;
comma
id|pci
)paren
)paren
suffix:semicolon
id|err
op_assign
id|pci_enable_device
c_func
(paren
id|pci
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;pci_enable_device() failed.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|err_free
suffix:semicolon
)brace
multiline_comment|/* enable bus-mastering */
id|pci_set_master
c_func
(paren
id|pci
)paren
suffix:semicolon
id|dev-&gt;pci
op_assign
id|pci
suffix:semicolon
multiline_comment|/* get chip-revision; this is needed to enable bug-fixes */
id|err
op_assign
id|pci_read_config_dword
c_func
(paren
id|pci
comma
id|PCI_CLASS_REVISION
comma
op_amp
id|dev-&gt;revision
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;pci_read_config_dword() failed.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|err_disable
suffix:semicolon
)brace
id|dev-&gt;revision
op_and_assign
l_int|0xf
suffix:semicolon
multiline_comment|/* remap the memory from virtual to physical adress */
id|err
op_assign
id|pci_request_region
c_func
(paren
id|pci
comma
l_int|0
comma
l_string|&quot;saa7146&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|err_disable
suffix:semicolon
id|dev-&gt;mem
op_assign
id|ioremap
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pci
comma
l_int|0
)paren
comma
id|pci_resource_len
c_func
(paren
id|pci
comma
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;mem
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;ioremap() failed.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|err_release
suffix:semicolon
)brace
multiline_comment|/* we don&squot;t do a master reset here anymore, it screws up&n;&t;   some boards that don&squot;t have an i2c-eeprom for configuration&n;&t;   values */
multiline_comment|/*&n;&t;saa7146_write(dev, MC1, MASK_31);&n;*/
multiline_comment|/* disable all irqs */
id|saa7146_write
c_func
(paren
id|dev
comma
id|IER
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* shut down all dma transfers and rps tasks */
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC1
comma
l_int|0x30ff0000
)paren
suffix:semicolon
multiline_comment|/* clear out any rps-signals pending */
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
l_int|0xf8000000
)paren
suffix:semicolon
multiline_comment|/* request an interrupt for the saa7146 */
id|err
op_assign
id|request_irq
c_func
(paren
id|pci-&gt;irq
comma
id|interrupt_hw
comma
id|SA_SHIRQ
op_or
id|SA_INTERRUPT
comma
id|dev-&gt;name
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|ERR
c_func
(paren
(paren
l_string|&quot;request_irq() failed.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|err_unmap
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* get memory for various stuff */
id|dev-&gt;d_rps0.cpu_addr
op_assign
id|pci_alloc_consistent
c_func
(paren
id|pci
comma
id|SAA7146_RPS_MEM
comma
op_amp
id|dev-&gt;d_rps0.dma_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;d_rps0.cpu_addr
)paren
r_goto
id|err_free_irq
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;d_rps0.cpu_addr
comma
l_int|0x0
comma
id|SAA7146_RPS_MEM
)paren
suffix:semicolon
id|dev-&gt;d_rps1.cpu_addr
op_assign
id|pci_alloc_consistent
c_func
(paren
id|pci
comma
id|SAA7146_RPS_MEM
comma
op_amp
id|dev-&gt;d_rps1.dma_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;d_rps1.cpu_addr
)paren
r_goto
id|err_free_rps0
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;d_rps1.cpu_addr
comma
l_int|0x0
comma
id|SAA7146_RPS_MEM
)paren
suffix:semicolon
id|dev-&gt;d_i2c.cpu_addr
op_assign
id|pci_alloc_consistent
c_func
(paren
id|pci
comma
id|SAA7146_RPS_MEM
comma
op_amp
id|dev-&gt;d_i2c.dma_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;d_i2c.cpu_addr
)paren
r_goto
id|err_free_rps1
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;d_i2c.cpu_addr
comma
l_int|0x0
comma
id|SAA7146_RPS_MEM
)paren
suffix:semicolon
multiline_comment|/* the rest + print status message */
multiline_comment|/* create a nice device name */
id|sprintf
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;saa7146 (%d)&quot;
comma
id|saa7146_num
)paren
suffix:semicolon
id|INFO
c_func
(paren
(paren
l_string|&quot;found saa7146 @ mem %p (revision %d, irq %d) (0x%04x,0x%04x).&bslash;n&quot;
comma
id|dev-&gt;mem
comma
id|dev-&gt;revision
comma
id|pci-&gt;irq
comma
id|pci-&gt;subsystem_vendor
comma
id|pci-&gt;subsystem_device
)paren
)paren
suffix:semicolon
id|dev-&gt;ext
op_assign
id|ext
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pci
comma
id|dev
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|dev-&gt;int_slock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|dev-&gt;i2c_lock
)paren
suffix:semicolon
id|dev-&gt;module
op_assign
id|THIS_MODULE
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev-&gt;i2c_wq
)paren
suffix:semicolon
multiline_comment|/* set some sane pci arbitrition values */
id|saa7146_write
c_func
(paren
id|dev
comma
id|PCI_BT_V1
comma
l_int|0x1c00101f
)paren
suffix:semicolon
multiline_comment|/* TODO: use the status code of the callback */
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|ext-&gt;probe
op_logical_and
id|ext
op_member_access_from_pointer
id|probe
c_func
(paren
id|dev
)paren
)paren
(brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;ext-&gt;probe() failed for %p. skipping device.&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
r_goto
id|err_free_i2c
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ext
op_member_access_from_pointer
id|attach
c_func
(paren
id|dev
comma
id|pci_ext
)paren
)paren
(brace
id|DEB_D
c_func
(paren
(paren
l_string|&quot;ext-&gt;attach() failed for %p. skipping device.&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
r_goto
id|err_unprobe
suffix:semicolon
)brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;item
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|dev-&gt;item
comma
op_amp
id|saa7146_devices
)paren
suffix:semicolon
id|saa7146_num
op_increment
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
id|err_unprobe
suffix:colon
id|pci_set_drvdata
c_func
(paren
id|pci
comma
l_int|NULL
)paren
suffix:semicolon
id|err_free_i2c
suffix:colon
id|pci_free_consistent
c_func
(paren
id|pci
comma
id|SAA7146_RPS_MEM
comma
id|dev-&gt;d_i2c.cpu_addr
comma
id|dev-&gt;d_i2c.dma_handle
)paren
suffix:semicolon
id|err_free_rps1
suffix:colon
id|pci_free_consistent
c_func
(paren
id|pci
comma
id|SAA7146_RPS_MEM
comma
id|dev-&gt;d_rps1.cpu_addr
comma
id|dev-&gt;d_rps1.dma_handle
)paren
suffix:semicolon
id|err_free_rps0
suffix:colon
id|pci_free_consistent
c_func
(paren
id|pci
comma
id|SAA7146_RPS_MEM
comma
id|dev-&gt;d_rps0.cpu_addr
comma
id|dev-&gt;d_rps0.dma_handle
)paren
suffix:semicolon
id|err_free_irq
suffix:colon
id|free_irq
c_func
(paren
id|pci-&gt;irq
comma
(paren
r_void
op_star
)paren
id|dev
)paren
suffix:semicolon
id|err_unmap
suffix:colon
id|iounmap
c_func
(paren
id|dev-&gt;mem
)paren
suffix:semicolon
id|err_release
suffix:colon
id|pci_release_region
c_func
(paren
id|pci
comma
l_int|0
)paren
suffix:semicolon
id|err_disable
suffix:colon
id|pci_disable_device
c_func
(paren
id|pci
)paren
suffix:semicolon
id|err_free
suffix:colon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|saa7146_remove_one
r_static
r_void
id|saa7146_remove_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|pci_get_drvdata
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_struct
(brace
r_void
op_star
id|addr
suffix:semicolon
id|dma_addr_t
id|dma
suffix:semicolon
)brace
id|dev_map
(braket
)braket
op_assign
(brace
(brace
id|dev-&gt;d_i2c.cpu_addr
comma
id|dev-&gt;d_i2c.dma_handle
)brace
comma
(brace
id|dev-&gt;d_rps1.cpu_addr
comma
id|dev-&gt;d_rps1.dma_handle
)brace
comma
(brace
id|dev-&gt;d_rps0.cpu_addr
comma
id|dev-&gt;d_rps0.dma_handle
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
)brace
comma
op_star
id|p
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev:%p&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
id|dev-&gt;ext
op_member_access_from_pointer
id|detach
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* shut down all video dma transfers */
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC1
comma
l_int|0x00ff0000
)paren
suffix:semicolon
multiline_comment|/* disable all irqs, release irq-routine */
id|saa7146_write
c_func
(paren
id|dev
comma
id|IER
comma
l_int|0
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|pdev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|dev_map
suffix:semicolon
id|p-&gt;addr
suffix:semicolon
id|p
op_increment
)paren
id|pci_free_consistent
c_func
(paren
id|pdev
comma
id|SAA7146_RPS_MEM
comma
id|p-&gt;addr
comma
id|p-&gt;dma
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|dev-&gt;mem
)paren
suffix:semicolon
id|pci_release_region
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|dev-&gt;item
)paren
suffix:semicolon
id|pci_disable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
id|saa7146_num
op_decrement
suffix:semicolon
)brace
multiline_comment|/*********************************************************************************/
multiline_comment|/* extension handling functions                                                  */
DECL|function|saa7146_register_extension
r_int
id|saa7146_register_extension
c_func
(paren
r_struct
id|saa7146_extension
op_star
id|ext
)paren
(brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;ext:%p&bslash;n&quot;
comma
id|ext
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|initialized
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|saa7146_devices
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|saa7146_devices_lock
)paren
suffix:semicolon
id|initialized
op_assign
l_int|1
suffix:semicolon
)brace
id|ext-&gt;driver.name
op_assign
id|ext-&gt;name
suffix:semicolon
id|ext-&gt;driver.id_table
op_assign
id|ext-&gt;pci_tbl
suffix:semicolon
id|ext-&gt;driver.probe
op_assign
id|saa7146_init_one
suffix:semicolon
id|ext-&gt;driver.remove
op_assign
id|saa7146_remove_one
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;saa7146: register extension &squot;%s&squot;.&bslash;n&quot;
comma
id|ext-&gt;name
)paren
suffix:semicolon
r_return
id|pci_module_init
c_func
(paren
op_amp
id|ext-&gt;driver
)paren
suffix:semicolon
)brace
DECL|function|saa7146_unregister_extension
r_int
id|saa7146_unregister_extension
c_func
(paren
r_struct
id|saa7146_extension
op_star
id|ext
)paren
(brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;ext:%p&bslash;n&quot;
comma
id|ext
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;saa7146: unregister extension &squot;%s&squot;.&bslash;n&quot;
comma
id|ext-&gt;name
)paren
suffix:semicolon
id|pci_unregister_driver
c_func
(paren
op_amp
id|ext-&gt;driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7146_init_module
r_static
r_int
id|__init
id|saa7146_init_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_eq
id|initialized
)paren
(brace
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|saa7146_devices
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|saa7146_devices_lock
)paren
suffix:semicolon
id|initialized
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7146_cleanup_module
r_static
r_void
id|__exit
id|saa7146_cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
DECL|variable|saa7146_init_module
id|module_init
c_func
(paren
id|saa7146_init_module
)paren
suffix:semicolon
DECL|variable|saa7146_cleanup_module
id|module_exit
c_func
(paren
id|saa7146_cleanup_module
)paren
suffix:semicolon
DECL|variable|saa7146_register_extension
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_register_extension
)paren
suffix:semicolon
DECL|variable|saa7146_unregister_extension
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_unregister_extension
)paren
suffix:semicolon
multiline_comment|/* misc functions used by extension modules */
DECL|variable|saa7146_pgtable_alloc
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_pgtable_alloc
)paren
suffix:semicolon
DECL|variable|saa7146_pgtable_free
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_pgtable_free
)paren
suffix:semicolon
DECL|variable|saa7146_pgtable_build_single
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_pgtable_build_single
)paren
suffix:semicolon
DECL|variable|saa7146_vmalloc_build_pgtable
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_vmalloc_build_pgtable
)paren
suffix:semicolon
DECL|variable|saa7146_wait_for_debi_done
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_wait_for_debi_done
)paren
suffix:semicolon
DECL|variable|saa7146_setgpio
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_setgpio
)paren
suffix:semicolon
DECL|variable|saa7146_i2c_transfer
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_i2c_transfer
)paren
suffix:semicolon
DECL|variable|saa7146_i2c_adapter_prepare
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_i2c_adapter_prepare
)paren
suffix:semicolon
DECL|variable|saa7146_debug
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_debug
)paren
suffix:semicolon
DECL|variable|saa7146_devices
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_devices
)paren
suffix:semicolon
DECL|variable|saa7146_devices_lock
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|saa7146_devices_lock
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Michael Hunold &lt;michael@mihu.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;driver for generic saa7146-based hardware&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
