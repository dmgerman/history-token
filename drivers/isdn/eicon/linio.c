multiline_comment|/*&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * Eicon File Revision :    1.16  &n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
DECL|macro|N_DATA
mdefine_line|#define N_DATA
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|macro|N_DATA
macro_line|#undef N_DATA
macro_line|#include &quot;uxio.h&quot;
r_static
DECL|variable|log_on
r_int
id|log_on
op_assign
l_int|0
suffix:semicolon
DECL|variable|Divasdevflag
r_int
id|Divasdevflag
op_assign
l_int|0
suffix:semicolon
DECL|variable|diva_lock
id|spinlock_t
id|diva_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_static
DECL|variable|card_pool
id|ux_diva_card_t
id|card_pool
(braket
id|MAX_CARDS
)braket
suffix:semicolon
DECL|function|UxPause
r_void
id|UxPause
c_func
(paren
r_int
r_int
id|ms
)paren
(brace
r_int
r_int
id|timeout
op_assign
id|jiffies
op_plus
(paren
(paren
id|ms
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
r_while
c_loop
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|timeout
)paren
)paren
suffix:semicolon
)brace
DECL|function|UxCardHandleGet
r_int
id|UxCardHandleGet
c_func
(paren
id|ux_diva_card_t
op_star
op_star
id|card
comma
id|dia_card_t
op_star
id|cfg
)paren
(brace
r_int
id|i
suffix:semicolon
id|ux_diva_card_t
op_star
id|c
suffix:semicolon
r_if
c_cond
(paren
id|cfg-&gt;bus_type
op_ne
id|DIA_BUS_TYPE_PCI
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: type not PCI (%d)&quot;
comma
id|cfg-&gt;bus_type
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|DIM
c_func
(paren
id|card_pool
)paren
)paren
op_logical_and
(paren
id|card_pool
(braket
id|i
)braket
dot
id|in_use
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|DIM
c_func
(paren
id|card_pool
)paren
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: card_pool exhausted&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|c
op_assign
op_star
id|card
op_assign
op_amp
id|card_pool
(braket
id|i
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|cfg-&gt;bus_type
)paren
(brace
r_case
id|DIA_BUS_TYPE_PCI
suffix:colon
id|c-&gt;pdev
op_assign
id|cfg-&gt;pdev
suffix:semicolon
id|c-&gt;io_base
op_assign
id|cfg-&gt;io_base
suffix:semicolon
id|c-&gt;reset_base
op_assign
id|cfg-&gt;reset_base
suffix:semicolon
id|c-&gt;card_type
op_assign
id|cfg-&gt;card_type
suffix:semicolon
id|c-&gt;mapped
op_assign
l_int|NULL
suffix:semicolon
id|c-&gt;slot
op_assign
id|cfg-&gt;slot
suffix:semicolon
id|c-&gt;irq
op_assign
(paren
r_int
)paren
id|cfg-&gt;irq
suffix:semicolon
id|c-&gt;pDRAM
op_assign
id|cfg-&gt;memory
(braket
id|DIVAS_RAM_MEMORY
)braket
suffix:semicolon
id|c-&gt;pDEVICES
op_assign
id|cfg-&gt;memory
(braket
id|DIVAS_REG_MEMORY
)braket
suffix:semicolon
id|c-&gt;pCONFIG
op_assign
id|cfg-&gt;memory
(braket
id|DIVAS_CFG_MEMORY
)braket
suffix:semicolon
id|c-&gt;pSHARED
op_assign
id|cfg-&gt;memory
(braket
id|DIVAS_SHARED_MEMORY
)braket
suffix:semicolon
id|c-&gt;pCONTROL
op_assign
id|cfg-&gt;memory
(braket
id|DIVAS_CTL_MEMORY
)braket
suffix:semicolon
multiline_comment|/*&t;&t;c-&gt;bus_type &t;= DIA_BUS_TYPE_PCI;&n;&t;&t;c-&gt;bus_num &t;= cfg-&gt;bus_num &amp; 0x3f;&n;&t;&t;c-&gt;slot &t;= cfg-&gt;slot;&n;&t;&t;c-&gt;irq &t;&t;= (int) cfg-&gt;irq;&n;&t;&t;c-&gt;int_priority = (int) cfg-&gt;int_priority;&n;&t;&t;c-&gt;card_type    = cfg-&gt;card_type;&n;&t;&t;c-&gt;io_base      = cfg-&gt;io_base;&n;&t;&t;c-&gt;reset_base   = cfg-&gt;reset_base;&n;&t;&t;c-&gt;pDRAM    &t;= cfg-&gt;memory[DIVAS_RAM_MEMORY];&n;&t;&t;c-&gt;pDEVICES &t;= cfg-&gt;memory[DIVAS_REG_MEMORY];&n;&t;&t;c-&gt;pCONFIG  &t;= cfg-&gt;memory[DIVAS_CFG_MEMORY];&n;&t;&t;c-&gt;pSHARED  &t;= cfg-&gt;memory[DIVAS_SHARED_MEMORY];&n;&t;&t;DPRINTF((&quot;divas hw: pDRAM is 0x%x&quot;, c-&gt;pDRAM));&n;&t;&t;DPRINTF((&quot;divas hw: pSHARED is 0x%x&quot;, c-&gt;pSHARED));&n;&t;&t;DPRINTF((&quot;divas hw: pCONFIG is 0x%x&quot;, c-&gt;pCONFIG));&n;&t;&t;c-&gt;cm_key&t;&t;= cm_getbrdkey(&quot;Divas&quot;, cfg-&gt;card_id);*/
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|c-&gt;in_use
op_assign
id|TRUE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|UxCardHandleFree
r_void
id|UxCardHandleFree
c_func
(paren
id|ux_diva_card_t
op_star
id|card
)paren
(brace
id|card-&gt;in_use
op_assign
id|FALSE
suffix:semicolon
)brace
DECL|macro|PLX_IOBASE
mdefine_line|#define PLX_IOBASE 0
DECL|macro|DIVAS_IOBASE
mdefine_line|#define DIVAS_IOBASE 1
DECL|function|UxCardMemAttach
r_void
op_star
id|UxCardMemAttach
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_int
id|id
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;card_type
op_eq
id|DIA_CARD_TYPE_DIVA_SERVER
)paren
(brace
r_switch
c_cond
(paren
id|id
)paren
(brace
r_case
id|DIVAS_SHARED_MEMORY
suffix:colon
id|card-&gt;mapped
op_assign
id|card-&gt;pSHARED
suffix:semicolon
r_return
id|card-&gt;pSHARED
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVAS_RAM_MEMORY
suffix:colon
id|card-&gt;mapped
op_assign
id|card-&gt;pDRAM
suffix:semicolon
r_return
id|card-&gt;pDRAM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVAS_REG_MEMORY
suffix:colon
id|card-&gt;mapped
op_assign
id|card-&gt;pDEVICES
suffix:semicolon
r_return
id|card-&gt;pDEVICES
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVAS_CFG_MEMORY
suffix:colon
id|card-&gt;mapped
op_assign
id|card-&gt;pCONFIG
suffix:semicolon
r_return
id|card-&gt;pCONFIG
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ASSERT
c_func
(paren
id|FALSE
)paren
suffix:semicolon
id|card-&gt;mapped
op_assign
l_int|NULL
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|card-&gt;card_type
op_eq
id|DIA_CARD_TYPE_DIVA_SERVER_B
)paren
(brace
r_switch
c_cond
(paren
id|id
)paren
(brace
r_case
id|PLX_IOBASE
suffix:colon
r_return
(paren
r_void
op_star
)paren
id|card-&gt;reset_base
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVAS_IOBASE
suffix:colon
r_return
(paren
r_void
op_star
)paren
id|card-&gt;io_base
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ASSERT
c_func
(paren
id|FALSE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|card-&gt;card_type
op_eq
id|DIA_CARD_TYPE_DIVA_SERVER_Q
)paren
(brace
r_switch
c_cond
(paren
id|id
)paren
(brace
r_case
id|DIVAS_SHARED_MEMORY
suffix:colon
id|card-&gt;mapped
op_assign
id|card-&gt;pSHARED
suffix:semicolon
r_return
id|card-&gt;pSHARED
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVAS_RAM_MEMORY
suffix:colon
id|card-&gt;mapped
op_assign
id|card-&gt;pDRAM
suffix:semicolon
r_return
id|card-&gt;pDRAM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVAS_REG_MEMORY
suffix:colon
id|card-&gt;mapped
op_assign
(paren
r_void
op_star
)paren
id|card-&gt;io_base
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|card-&gt;io_base
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVAS_CTL_MEMORY
suffix:colon
id|card-&gt;mapped
op_assign
id|card-&gt;pCONTROL
suffix:semicolon
r_return
id|card-&gt;pCONTROL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
singleline_comment|// ASSERT(FALSE);
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: Trying to attach to mem %d&quot;
comma
id|id
)paren
)paren
suffix:semicolon
id|card-&gt;mapped
op_assign
l_int|NULL
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
l_int|0
suffix:semicolon
)brace
)brace
r_else
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: Tried to attach to unknown card&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* Unknown card type */
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|UxCardMemDetach
r_void
id|UxCardMemDetach
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|address
)paren
(brace
r_return
suffix:semicolon
singleline_comment|// Just a place holder. No un-mapping done.
)brace
DECL|function|UxCardLog
r_void
id|UxCardLog
c_func
(paren
r_int
id|turn_on
)paren
(brace
id|log_on
op_assign
id|turn_on
suffix:semicolon
)brace
multiline_comment|/*&n; * Control Register I/O Routines to be performed on Attached I/O ports&n; */
DECL|function|UxCardPortIoOut
r_void
id|UxCardPortIoOut
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|AttachedBase
comma
r_int
id|offset
comma
id|byte
id|the_byte
)paren
(brace
id|word
id|base
op_assign
(paren
id|word
)paren
(paren
id|dword
)paren
id|AttachedBase
suffix:semicolon
id|base
op_add_assign
id|offset
suffix:semicolon
id|outb
c_func
(paren
id|the_byte
comma
id|base
)paren
suffix:semicolon
)brace
DECL|function|UxCardPortIoOutW
r_void
id|UxCardPortIoOutW
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|AttachedBase
comma
r_int
id|offset
comma
id|word
id|the_word
)paren
(brace
id|word
id|base
op_assign
(paren
id|word
)paren
(paren
id|dword
)paren
id|AttachedBase
suffix:semicolon
id|base
op_add_assign
id|offset
suffix:semicolon
id|outw
c_func
(paren
id|the_word
comma
id|base
)paren
suffix:semicolon
)brace
DECL|function|UxCardPortIoOutD
r_void
id|UxCardPortIoOutD
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|AttachedBase
comma
r_int
id|offset
comma
id|dword
id|the_dword
)paren
(brace
id|word
id|base
op_assign
(paren
id|word
)paren
(paren
id|dword
)paren
id|AttachedBase
suffix:semicolon
id|base
op_add_assign
id|offset
suffix:semicolon
id|outl
c_func
(paren
id|the_dword
comma
id|base
)paren
suffix:semicolon
)brace
DECL|function|UxCardPortIoIn
id|byte
id|UxCardPortIoIn
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|AttachedBase
comma
r_int
id|offset
)paren
(brace
id|word
id|base
op_assign
(paren
id|word
)paren
(paren
id|dword
)paren
id|AttachedBase
suffix:semicolon
id|base
op_add_assign
id|offset
suffix:semicolon
r_return
id|inb
c_func
(paren
id|base
)paren
suffix:semicolon
)brace
DECL|function|UxCardPortIoInW
id|word
id|UxCardPortIoInW
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|AttachedBase
comma
r_int
id|offset
)paren
(brace
id|word
id|base
op_assign
(paren
id|word
)paren
(paren
id|dword
)paren
id|AttachedBase
suffix:semicolon
id|base
op_add_assign
id|offset
suffix:semicolon
r_return
id|inw
c_func
(paren
id|base
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory mapped card I/O functions&n; */
DECL|function|UxCardMemIn
id|byte
id|UxCardMemIn
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|address
)paren
(brace
id|byte
id|b
suffix:semicolon
r_volatile
id|byte
op_star
id|t
op_assign
(paren
id|byte
op_star
)paren
id|address
suffix:semicolon
id|b
op_assign
op_star
id|t
suffix:semicolon
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|byte
op_star
id|a
op_assign
id|address
suffix:semicolon
id|a
op_sub_assign
(paren
r_int
)paren
id|card-&gt;mapped
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: read 0x%02x from 0x%x (memory mapped)&quot;
comma
id|b
op_amp
l_int|0xff
comma
id|a
)paren
)paren
suffix:semicolon
)brace
r_return
id|b
suffix:semicolon
)brace
DECL|function|UxCardMemInW
id|word
id|UxCardMemInW
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|address
)paren
(brace
id|word
id|w
suffix:semicolon
r_volatile
id|word
op_star
id|t
op_assign
(paren
id|word
op_star
)paren
id|address
suffix:semicolon
id|w
op_assign
op_star
id|t
suffix:semicolon
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|byte
op_star
id|a
op_assign
id|address
suffix:semicolon
id|a
op_sub_assign
(paren
r_int
)paren
id|card-&gt;mapped
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: read 0x%04x from 0x%x (memory mapped)&quot;
comma
id|w
op_amp
l_int|0xffff
comma
id|a
)paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|w
)paren
suffix:semicolon
)brace
DECL|function|UxCardMemInD
id|dword
id|UxCardMemInD
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|address
)paren
(brace
id|dword
id|dw
suffix:semicolon
r_volatile
id|dword
op_star
id|t
op_assign
(paren
id|dword
op_star
)paren
id|address
suffix:semicolon
id|dw
op_assign
op_star
id|t
suffix:semicolon
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|byte
op_star
id|a
op_assign
id|address
suffix:semicolon
id|a
op_sub_assign
(paren
r_int
)paren
id|card-&gt;mapped
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: read 0x%08x from 0x%x (memory mapped)&quot;
comma
id|dw
comma
id|a
)paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|dw
)paren
suffix:semicolon
)brace
DECL|function|UxCardMemInBuffer
r_void
id|UxCardMemInBuffer
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|address
comma
r_void
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
r_volatile
id|byte
op_star
id|pSource
op_assign
id|address
suffix:semicolon
id|byte
op_star
id|pDest
op_assign
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|length
op_decrement
)paren
(brace
op_star
id|pDest
op_increment
op_assign
op_star
id|pSource
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|byte
op_star
id|a
op_assign
id|address
suffix:semicolon
id|a
op_sub_assign
(paren
r_int
)paren
id|card-&gt;mapped
suffix:semicolon
id|pDest
op_assign
id|buffer
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: read %02x %02x %02x %02x %02x %02x %02x %02x from 0x%x (memory mapped)&quot;
comma
id|pDest
(braket
l_int|0
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|1
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|2
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|3
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|4
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|5
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|6
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|7
)braket
op_amp
l_int|0xff
comma
id|a
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|UxCardMemOut
r_void
id|UxCardMemOut
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|address
comma
id|byte
id|data
)paren
(brace
r_volatile
id|byte
op_star
id|t
op_assign
(paren
id|byte
op_star
)paren
id|address
suffix:semicolon
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|byte
op_star
id|a
op_assign
id|address
suffix:semicolon
id|a
op_sub_assign
(paren
r_int
)paren
id|card-&gt;mapped
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: wrote 0x%02x to 0x%x (memory mapped)&quot;
comma
id|data
op_amp
l_int|0xff
comma
id|a
)paren
)paren
suffix:semicolon
)brace
op_star
id|t
op_assign
id|data
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|UxCardMemOutW
r_void
id|UxCardMemOutW
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|address
comma
id|word
id|data
)paren
(brace
r_volatile
id|word
op_star
id|t
op_assign
(paren
id|word
op_star
)paren
id|address
suffix:semicolon
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|byte
op_star
id|a
op_assign
id|address
suffix:semicolon
id|a
op_sub_assign
(paren
r_int
)paren
id|card-&gt;mapped
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: wrote 0x%04x to 0x%x (memory mapped)&quot;
comma
id|data
op_amp
l_int|0xffff
comma
id|a
)paren
)paren
suffix:semicolon
)brace
op_star
id|t
op_assign
id|data
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|UxCardMemOutD
r_void
id|UxCardMemOutD
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|address
comma
id|dword
id|data
)paren
(brace
r_volatile
id|dword
op_star
id|t
op_assign
(paren
id|dword
op_star
)paren
id|address
suffix:semicolon
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|byte
op_star
id|a
op_assign
id|address
suffix:semicolon
id|a
op_sub_assign
(paren
r_int
)paren
id|card-&gt;mapped
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: wrote 0x%08x to 0x%x (memory mapped)&quot;
comma
id|data
comma
id|a
)paren
)paren
suffix:semicolon
)brace
op_star
id|t
op_assign
id|data
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|UxCardMemOutBuffer
r_void
id|UxCardMemOutBuffer
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|address
comma
r_void
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
id|byte
op_star
id|pSource
op_assign
id|buffer
suffix:semicolon
id|byte
op_star
id|pDest
op_assign
id|address
suffix:semicolon
r_while
c_loop
(paren
id|length
op_decrement
)paren
(brace
op_star
id|pDest
op_increment
op_assign
op_star
id|pSource
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|byte
op_star
id|a
op_assign
id|address
suffix:semicolon
id|a
op_sub_assign
(paren
r_int
)paren
id|card-&gt;mapped
suffix:semicolon
id|pDest
op_assign
id|buffer
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: wrote %02x %02x %02x %02x %02x %02x %02x %02x to 0x%x (memory mapped)&quot;
comma
id|pDest
(braket
l_int|0
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|1
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|2
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|3
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|4
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|5
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|6
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|7
)braket
op_amp
l_int|0xff
comma
id|a
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory mapped card I/O functions&n; */
DECL|function|UxCardIoIn
id|byte
id|UxCardIoIn
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|AttachedDivasIOBase
comma
r_void
op_star
id|address
)paren
(brace
id|byte
id|the_byte
suffix:semicolon
id|outb
c_func
(paren
l_int|0xFF
comma
id|card-&gt;io_base
op_plus
l_int|0xC
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|word
)paren
(paren
id|dword
)paren
id|address
comma
id|card-&gt;io_base
op_plus
l_int|4
)paren
suffix:semicolon
id|the_byte
op_assign
id|inb
c_func
(paren
id|card-&gt;io_base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: read 0x%02x from 0x%x (I/O mapped)&quot;
comma
id|the_byte
op_amp
l_int|0xff
comma
id|address
)paren
)paren
suffix:semicolon
)brace
r_return
id|the_byte
suffix:semicolon
)brace
DECL|function|UxCardIoInW
id|word
id|UxCardIoInW
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|AttachedDivasIOBase
comma
r_void
op_star
id|address
)paren
(brace
id|word
id|the_word
suffix:semicolon
id|outb
c_func
(paren
l_int|0xFF
comma
id|card-&gt;io_base
op_plus
l_int|0xC
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|word
)paren
(paren
id|dword
)paren
id|address
comma
id|card-&gt;io_base
op_plus
l_int|4
)paren
suffix:semicolon
id|the_word
op_assign
id|inw
c_func
(paren
id|card-&gt;io_base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: read 0x%04x from 0x%x (I/O mapped)&quot;
comma
id|the_word
op_amp
l_int|0xffff
comma
id|address
)paren
)paren
suffix:semicolon
)brace
r_return
id|the_word
suffix:semicolon
)brace
DECL|function|UxCardIoInD
id|dword
id|UxCardIoInD
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|AttachedDivasIOBase
comma
r_void
op_star
id|address
)paren
(brace
id|dword
id|the_dword
suffix:semicolon
id|outb
c_func
(paren
l_int|0xFF
comma
id|card-&gt;io_base
op_plus
l_int|0xC
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|word
)paren
(paren
id|dword
)paren
id|address
comma
id|card-&gt;io_base
op_plus
l_int|4
)paren
suffix:semicolon
id|the_dword
op_assign
id|inl
c_func
(paren
id|card-&gt;io_base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: read 0x%08x from 0x%x (I/O mapped)&quot;
comma
id|the_dword
comma
id|address
)paren
)paren
suffix:semicolon
)brace
r_return
id|the_dword
suffix:semicolon
)brace
DECL|function|UxCardIoInBuffer
r_void
id|UxCardIoInBuffer
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|AttachedDivasIOBase
comma
r_void
op_star
id|address
comma
r_void
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
id|byte
op_star
id|pSource
op_assign
id|address
suffix:semicolon
id|byte
op_star
id|pDest
op_assign
id|buffer
suffix:semicolon
r_if
c_cond
(paren
(paren
id|word
)paren
(paren
id|dword
)paren
id|address
op_amp
l_int|0x1
)paren
(brace
id|outb
c_func
(paren
l_int|0xFF
comma
id|card-&gt;io_base
op_plus
l_int|0xC
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|word
)paren
(paren
id|dword
)paren
id|pSource
comma
id|card-&gt;io_base
op_plus
l_int|4
)paren
suffix:semicolon
op_star
id|pDest
op_assign
(paren
id|byte
)paren
id|inb
c_func
(paren
id|card-&gt;io_base
)paren
suffix:semicolon
id|pDest
op_increment
suffix:semicolon
id|pSource
op_increment
suffix:semicolon
id|length
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|length
)paren
(brace
r_return
suffix:semicolon
)brace
)brace
id|outb
c_func
(paren
l_int|0xFF
comma
id|card-&gt;io_base
op_plus
l_int|0xC
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|word
)paren
(paren
id|dword
)paren
id|pSource
comma
id|card-&gt;io_base
op_plus
l_int|4
)paren
suffix:semicolon
id|insw
c_func
(paren
id|card-&gt;io_base
comma
(paren
id|word
op_star
)paren
id|pDest
comma
id|length
op_mod
l_int|2
ques
c_cond
(paren
id|length
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:colon
id|length
op_rshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|pDest
op_assign
id|buffer
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: read %02x %02x %02x %02x %02x %02x %02x %02x from 0x%x (I/O mapped)&quot;
comma
id|pDest
(braket
l_int|0
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|1
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|2
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|3
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|4
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|5
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|6
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|7
)braket
op_amp
l_int|0xff
comma
id|address
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Output */
DECL|function|UxCardIoOut
r_void
id|UxCardIoOut
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|AttachedDivasIOBase
comma
r_void
op_star
id|address
comma
id|byte
id|data
)paren
(brace
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: wrote 0x%02x to 0x%x (I/O mapped)&quot;
comma
id|data
op_amp
l_int|0xff
comma
id|address
)paren
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
l_int|0xFF
comma
id|card-&gt;io_base
op_plus
l_int|0xC
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|word
)paren
(paren
id|dword
)paren
id|address
comma
id|card-&gt;io_base
op_plus
l_int|4
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|byte
)paren
id|data
op_amp
l_int|0xFF
comma
id|card-&gt;io_base
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|UxCardIoOutW
r_void
id|UxCardIoOutW
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|AttachedDivasIOBase
comma
r_void
op_star
id|address
comma
id|word
id|data
)paren
(brace
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: wrote 0x%04x to 0x%x (I/O mapped)&quot;
comma
id|data
op_amp
l_int|0xffff
comma
id|address
)paren
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
l_int|0xFF
comma
id|card-&gt;io_base
op_plus
l_int|0xC
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|word
)paren
(paren
id|dword
)paren
id|address
comma
id|card-&gt;io_base
op_plus
l_int|4
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|word
)paren
id|data
op_amp
l_int|0xFFFF
comma
id|card-&gt;io_base
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|UxCardIoOutD
r_void
id|UxCardIoOutD
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|AttachedDivasIOBase
comma
r_void
op_star
id|address
comma
id|dword
id|data
)paren
(brace
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: wrote 0x%08x to 0x%x (I/O mapped)&quot;
comma
id|data
comma
id|address
)paren
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
l_int|0xFF
comma
id|card-&gt;io_base
op_plus
l_int|0xC
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|word
)paren
(paren
id|dword
)paren
id|address
comma
id|card-&gt;io_base
op_plus
l_int|4
)paren
suffix:semicolon
id|outl
c_func
(paren
(paren
id|dword
)paren
id|data
op_amp
l_int|0xFFFFFFFF
comma
id|card-&gt;io_base
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|UxCardIoOutBuffer
r_void
id|UxCardIoOutBuffer
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|AttachedDivasIOBase
comma
r_void
op_star
id|address
comma
r_void
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
id|byte
op_star
id|pSource
op_assign
id|buffer
suffix:semicolon
id|byte
op_star
id|pDest
op_assign
id|address
suffix:semicolon
r_if
c_cond
(paren
(paren
id|word
)paren
(paren
id|dword
)paren
id|address
op_amp
l_int|1
)paren
(brace
id|outb
c_func
(paren
l_int|0xFF
comma
id|card-&gt;io_base
op_plus
l_int|0xC
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|word
)paren
(paren
id|dword
)paren
id|pDest
comma
id|card-&gt;io_base
op_plus
l_int|4
)paren
suffix:semicolon
id|outb
c_func
(paren
op_star
id|pSource
comma
id|card-&gt;io_base
)paren
suffix:semicolon
id|pSource
op_increment
suffix:semicolon
id|pDest
op_increment
suffix:semicolon
id|length
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|length
)paren
(brace
r_return
suffix:semicolon
)brace
)brace
id|outb
c_func
(paren
l_int|0xFF
comma
id|card-&gt;io_base
op_plus
l_int|0xC
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|word
)paren
(paren
id|dword
)paren
id|pDest
comma
id|card-&gt;io_base
op_plus
l_int|4
)paren
suffix:semicolon
id|outsw
c_func
(paren
id|card-&gt;io_base
comma
(paren
id|word
op_star
)paren
id|pSource
comma
id|length
op_mod
l_int|2
ques
c_cond
(paren
id|length
op_plus
l_int|1
)paren
op_rshift
l_int|1
suffix:colon
id|length
op_rshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|log_on
)paren
(brace
id|pDest
op_assign
id|buffer
suffix:semicolon
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas hw: wrote %02x %02x %02x %02x %02x %02x %02x %02x to 0x%x (I/O mapped)&quot;
comma
id|pDest
(braket
l_int|0
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|1
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|2
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|3
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|4
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|5
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|6
)braket
op_amp
l_int|0xff
comma
id|pDest
(braket
l_int|7
)braket
op_amp
l_int|0xff
comma
id|address
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|Divasintr
id|irqreturn_t
id|Divasintr
c_func
(paren
r_int
id|arg
comma
r_void
op_star
id|unused
comma
r_struct
id|pt_regs
op_star
id|unused_regs
)paren
(brace
r_int
id|i
suffix:semicolon
id|card_t
op_star
id|card
op_assign
l_int|NULL
suffix:semicolon
id|ux_diva_card_t
op_star
id|ux_ref
op_assign
l_int|NULL
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
id|DivasCardNext
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|arg
op_eq
id|DivasCards
(braket
id|i
)braket
dot
id|cfg.irq
)paren
(brace
id|card
op_assign
op_amp
id|DivasCards
(braket
id|i
)braket
suffix:semicolon
id|ux_ref
op_assign
id|card-&gt;hw
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ux_ref
)paren
op_logical_and
(paren
id|card-&gt;is_live
)paren
)paren
(brace
(paren
op_star
id|ux_ref-&gt;user_isr
)paren
(paren
id|ux_ref-&gt;user_isr_arg
)paren
suffix:semicolon
)brace
r_else
(brace
id|DPRINTF
c_func
(paren
(paren
l_string|&quot;divas: ISR couldn&squot;t locate card&quot;
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|UxIsrInstall
r_int
id|UxIsrInstall
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
id|isr_fn_t
op_star
id|isr_fn
comma
r_void
op_star
id|isr_arg
)paren
(brace
r_int
id|result
suffix:semicolon
id|card-&gt;user_isr
op_assign
id|isr_fn
suffix:semicolon
id|card-&gt;user_isr_arg
op_assign
id|isr_arg
suffix:semicolon
id|result
op_assign
id|request_irq
c_func
(paren
id|card-&gt;irq
comma
id|Divasintr
comma
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
comma
l_string|&quot;Divas&quot;
comma
(paren
r_void
op_star
)paren
id|isr_arg
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|UxIsrRemove
r_void
id|UxIsrRemove
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_void
op_star
id|dev_id
)paren
(brace
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card-&gt;user_isr_arg
)paren
suffix:semicolon
)brace
DECL|function|UxPciConfigWrite
r_void
id|UxPciConfigWrite
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_int
id|size
comma
r_int
id|offset
comma
r_void
op_star
id|value
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
r_sizeof
(paren
id|byte
)paren
suffix:colon
id|pci_write_config_byte
c_func
(paren
id|card-&gt;pdev
comma
id|offset
comma
op_star
(paren
id|byte
op_star
)paren
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
id|word
)paren
suffix:colon
id|pci_write_config_word
c_func
(paren
id|card-&gt;pdev
comma
id|offset
comma
op_star
(paren
id|word
op_star
)paren
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
id|dword
)paren
suffix:colon
id|pci_write_config_dword
c_func
(paren
id|card-&gt;pdev
comma
id|offset
comma
op_star
(paren
id|dword
op_star
)paren
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Divas: Invalid size in UxPciConfigWrite&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|UxPciConfigRead
r_void
id|UxPciConfigRead
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_int
id|size
comma
r_int
id|offset
comma
r_void
op_star
id|value
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
r_sizeof
(paren
id|byte
)paren
suffix:colon
id|pci_read_config_byte
c_func
(paren
id|card-&gt;pdev
comma
id|offset
comma
(paren
id|byte
op_star
)paren
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
id|word
)paren
suffix:colon
id|pci_read_config_word
c_func
(paren
id|card-&gt;pdev
comma
id|offset
comma
(paren
id|word
op_star
)paren
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
r_sizeof
(paren
id|dword
)paren
suffix:colon
id|pci_read_config_dword
c_func
(paren
id|card-&gt;pdev
comma
id|offset
comma
(paren
r_int
r_int
op_star
)paren
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Divas: Invalid size in UxPciConfigRead&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|UxAlloc
r_void
op_star
id|UxAlloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_void
op_star
id|m
suffix:semicolon
id|m
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_return
id|m
suffix:semicolon
)brace
DECL|function|UxFree
r_void
id|UxFree
c_func
(paren
r_void
op_star
id|ptr
)paren
(brace
id|kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
DECL|function|UxCardLock
r_int
id|UxCardLock
c_func
(paren
id|ux_diva_card_t
op_star
id|card
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|diva_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|flags
suffix:semicolon
)brace
DECL|function|UxCardUnlock
r_void
id|UxCardUnlock
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_int
r_int
id|ipl
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|diva_lock
comma
id|ipl
)paren
suffix:semicolon
)brace
DECL|function|UxTimeGet
id|dword
id|UxTimeGet
c_func
(paren
r_void
)paren
(brace
r_return
id|jiffies
suffix:semicolon
)brace
DECL|function|UxInterlockedIncrement
r_int
id|UxInterlockedIncrement
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_int
op_star
id|dst
)paren
(brace
r_register
r_volatile
r_int
op_star
id|p
suffix:semicolon
r_register
r_int
id|ret
suffix:semicolon
r_int
id|ipl
suffix:semicolon
id|p
op_assign
id|dst
suffix:semicolon
id|ipl
op_assign
id|UxCardLock
c_func
(paren
id|card
)paren
suffix:semicolon
op_star
id|p
op_add_assign
l_int|1
suffix:semicolon
id|ret
op_assign
op_star
id|p
suffix:semicolon
id|UxCardUnlock
c_func
(paren
id|card
comma
id|ipl
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|UxInterlockedDecrement
r_int
id|UxInterlockedDecrement
c_func
(paren
id|ux_diva_card_t
op_star
id|card
comma
r_int
op_star
id|dst
)paren
(brace
r_register
r_volatile
r_int
op_star
id|p
suffix:semicolon
r_register
r_int
id|ret
suffix:semicolon
r_int
id|ipl
suffix:semicolon
id|p
op_assign
id|dst
suffix:semicolon
id|ipl
op_assign
id|UxCardLock
c_func
(paren
id|card
)paren
suffix:semicolon
op_star
id|p
op_sub_assign
l_int|1
suffix:semicolon
id|ret
op_assign
op_star
id|p
suffix:semicolon
id|UxCardUnlock
c_func
(paren
id|card
comma
id|ipl
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
