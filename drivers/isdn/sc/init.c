multiline_comment|/*&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;includes.h&quot;
macro_line|#include &quot;hardware.h&quot;
macro_line|#include &quot;card.h&quot;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ISDN4Linux: Driver for Spellcaster card&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Spellcaster Telecommunications Inc.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|ram
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|do_reset
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|variable|sc_adapter
id|board
op_star
id|sc_adapter
(braket
id|MAX_CARDS
)braket
suffix:semicolon
DECL|variable|cinst
r_int
id|cinst
suffix:semicolon
DECL|variable|devname
r_static
r_char
id|devname
(braket
)braket
op_assign
l_string|&quot;scX&quot;
suffix:semicolon
DECL|variable|version
r_const
r_char
id|version
(braket
)braket
op_assign
l_string|&quot;2.0b1&quot;
suffix:semicolon
DECL|variable|boardname
r_const
r_char
op_star
id|boardname
(braket
)braket
op_assign
(brace
l_string|&quot;DataCommute/BRI&quot;
comma
l_string|&quot;DataCommute/PRI&quot;
comma
l_string|&quot;TeleCommute/BRI&quot;
)brace
suffix:semicolon
multiline_comment|/* insmod set parameters */
DECL|variable|io
r_static
r_int
r_int
id|io
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|irq
r_static
r_int
r_char
id|irq
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|ram
r_static
r_int
r_int
id|ram
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|do_reset
r_static
r_int
id|do_reset
op_assign
l_int|0
suffix:semicolon
DECL|variable|sup_irq
r_static
r_int
id|sup_irq
(braket
)braket
op_assign
(brace
l_int|11
comma
l_int|10
comma
l_int|9
comma
l_int|5
comma
l_int|12
comma
l_int|14
comma
l_int|7
comma
l_int|3
comma
l_int|4
comma
l_int|6
)brace
suffix:semicolon
DECL|macro|MAX_IRQS
mdefine_line|#define MAX_IRQS&t;10
r_extern
id|irqreturn_t
id|interrupt_handler
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sndpkt
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|command
c_func
(paren
id|isdn_ctrl
op_star
)paren
suffix:semicolon
r_extern
r_int
id|indicate_status
c_func
(paren
r_int
comma
r_int
comma
id|ulong
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|reset
c_func
(paren
r_int
)paren
suffix:semicolon
r_int
id|identify_board
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|function|irq_supported
r_int
id|irq_supported
c_func
(paren
r_int
id|irq_x
)paren
(brace
r_int
id|i
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
id|MAX_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sup_irq
(braket
id|i
)braket
op_eq
id|irq_x
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sc_init
r_static
r_int
id|__init
id|sc_init
c_func
(paren
r_void
)paren
(brace
r_int
id|b
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|status
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_int
r_int
id|memsize
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|features
op_assign
l_int|0
suffix:semicolon
id|isdn_if
op_star
id|interface
suffix:semicolon
r_int
r_char
id|channels
suffix:semicolon
r_int
r_char
id|pgport
suffix:semicolon
r_int
r_int
id|magic
suffix:semicolon
r_int
id|model
suffix:semicolon
r_int
id|last_base
op_assign
id|IOBASE_MIN
suffix:semicolon
r_int
id|probe_exhasted
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef MODULE
id|pr_info
c_func
(paren
l_string|&quot;SpellCaster ISA ISDN Adapter Driver rev. %s Loaded&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
macro_line|#else
id|pr_info
c_func
(paren
l_string|&quot;SpellCaster ISA ISDN Adapter Driver rev. %s&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
macro_line|#endif
id|pr_info
c_func
(paren
l_string|&quot;Copyright (C) 1996 SpellCaster Telecommunications Inc.&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|b
op_increment
OL
id|MAX_CARDS
op_minus
l_int|1
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Probing for adapter #%d&bslash;n&quot;
comma
id|b
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Initialize reusable variables&n;&t;&t; */
id|model
op_assign
op_minus
l_int|1
suffix:semicolon
id|magic
op_assign
l_int|0
suffix:semicolon
id|channels
op_assign
l_int|0
suffix:semicolon
id|pgport
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n;&t;&t; * See if we should probe for IO base &n;&t;&t; */
id|pr_debug
c_func
(paren
l_string|&quot;I/O Base for board %d is 0x%x, %s probe&bslash;n&quot;
comma
id|b
comma
id|io
(braket
id|b
)braket
comma
id|io
(braket
id|b
)braket
op_eq
l_int|0
ques
c_cond
l_string|&quot;will&quot;
suffix:colon
l_string|&quot;won&squot;t&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io
(braket
id|b
)braket
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * No, I/O Base has been provided&n;&t;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_IO_REGS
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|io
(braket
id|b
)braket
op_plus
id|i
op_star
l_int|0x400
comma
l_int|1
comma
l_string|&quot;sc test&quot;
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;check_region for 0x%x failed&bslash;n&quot;
comma
id|io
(braket
id|b
)braket
op_plus
id|i
op_star
l_int|0x400
)paren
suffix:semicolon
id|io
(braket
id|b
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
id|release_region
c_func
(paren
id|io
(braket
id|b
)braket
op_plus
id|i
op_star
l_int|0x400
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Confirm the I/O Address with a test&n;&t;&t;&t; */
r_if
c_cond
(paren
id|io
(braket
id|b
)braket
op_eq
l_int|0
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;I/O Address 0x%x is in use.&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|outb
c_func
(paren
l_int|0x18
comma
id|io
(braket
id|b
)braket
op_plus
l_int|0x400
op_star
id|EXP_PAGE0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|io
(braket
id|b
)braket
op_plus
l_int|0x400
op_star
id|EXP_PAGE0
)paren
op_ne
l_int|0x18
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;I/O Base 0x%x fails test&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * Yes, probe for I/O Base&n;&t;&t;&t; */
r_if
c_cond
(paren
id|probe_exhasted
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;All probe addresses exhasted, skipping&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;Probing for I/O...&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|last_base
suffix:semicolon
id|i
op_le
id|IOBASE_MAX
suffix:semicolon
id|i
op_add_assign
id|IOBASE_OFFSET
)paren
(brace
r_int
id|found_io
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|IOBASE_MAX
)paren
(brace
id|probe_exhasted
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* No more addresses to probe */
id|pr_debug
c_func
(paren
l_string|&quot;End of Probes&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|last_base
op_assign
id|i
op_plus
id|IOBASE_OFFSET
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;  checking 0x%x...&quot;
comma
id|i
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|MAX_IO_REGS
op_minus
l_int|1
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|i
op_plus
id|j
op_star
l_int|0x400
comma
l_int|1
comma
l_string|&quot;sc test&quot;
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Failed&bslash;n&quot;
)paren
suffix:semicolon
id|found_io
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
id|release_region
c_func
(paren
id|i
op_plus
id|j
op_star
l_int|0x400
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found_io
)paren
(brace
id|io
(braket
id|b
)braket
op_assign
id|i
suffix:semicolon
id|outb
c_func
(paren
l_int|0x18
comma
id|io
(braket
id|b
)braket
op_plus
l_int|0x400
op_star
id|EXP_PAGE0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|io
(braket
id|b
)braket
op_plus
l_int|0x400
op_star
id|EXP_PAGE0
)paren
op_ne
l_int|0x18
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Failed by test&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;Passed&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|probe_exhasted
)paren
(brace
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * See if we should probe for shared RAM&n;&t;&t; */
r_if
c_cond
(paren
id|do_reset
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Doing a SAFE probe reset&bslash;n&quot;
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xFF
comma
id|io
(braket
id|b
)braket
op_plus
id|RESET_OFFSET
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|milliseconds
c_func
(paren
l_int|10000
)paren
)paren
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;RAM Base for board %d is 0x%x, %s probe&bslash;n&quot;
comma
id|b
comma
id|ram
(braket
id|b
)braket
comma
id|ram
(braket
id|b
)braket
op_eq
l_int|0
ques
c_cond
l_string|&quot;will&quot;
suffix:colon
l_string|&quot;won&squot;t&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ram
(braket
id|b
)braket
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * No, the RAM base has been provided&n;&t;&t;&t; * Just look for a signature and ID the&n;&t;&t;&t; * board model&n;&t;&t;&t; */
r_if
c_cond
(paren
id|request_region
c_func
(paren
id|ram
(braket
id|b
)braket
comma
id|SRAM_PAGESIZE
comma
l_string|&quot;sc test&quot;
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;request_region for RAM base 0x%x succeeded&bslash;n&quot;
comma
id|ram
(braket
id|b
)braket
)paren
suffix:semicolon
id|model
op_assign
id|identify_board
c_func
(paren
id|ram
(braket
id|b
)braket
comma
id|io
(braket
id|b
)braket
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|ram
(braket
id|b
)braket
comma
id|SRAM_PAGESIZE
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * Yes, probe for free RAM and look for&n;&t;&t;&t; * a signature and id the board model&n;&t;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|SRAM_MIN
suffix:semicolon
id|i
OL
id|SRAM_MAX
suffix:semicolon
id|i
op_add_assign
id|SRAM_PAGESIZE
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Checking RAM address 0x%x...&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_region
c_func
(paren
id|i
comma
id|SRAM_PAGESIZE
comma
l_string|&quot;sc test&quot;
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;  check_region succeeded&bslash;n&quot;
)paren
suffix:semicolon
id|model
op_assign
id|identify_board
c_func
(paren
id|i
comma
id|io
(braket
id|b
)braket
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|i
comma
id|SRAM_PAGESIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|model
op_ge
l_int|0
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;  Identified a %s&bslash;n&quot;
comma
id|boardname
(braket
id|model
)braket
)paren
suffix:semicolon
id|ram
(braket
id|b
)braket
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;  Unidentifed or inaccessible&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;  request failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * See if we found free RAM and the board model&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ram
(braket
id|b
)braket
op_logical_or
id|model
OL
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Nope, there was no place in RAM for the&n;&t;&t;&t; * board, or it couldn&squot;t be identified&n;&t;&t;&t; */
id|pr_debug
c_func
(paren
l_string|&quot;Failed to find an adapter at 0x%x&bslash;n&quot;
comma
id|ram
(braket
id|b
)braket
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Set the board&squot;s magic number, memory size and page register&n;&t;&t; */
r_switch
c_cond
(paren
id|model
)paren
(brace
r_case
id|PRI_BOARD
suffix:colon
id|channels
op_assign
l_int|23
suffix:semicolon
id|magic
op_assign
l_int|0x20000
suffix:semicolon
id|memsize
op_assign
l_int|0x100000
suffix:semicolon
id|features
op_assign
id|PRI_FEATURES
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BRI_BOARD
suffix:colon
r_case
id|POTS_BOARD
suffix:colon
id|channels
op_assign
l_int|2
suffix:semicolon
id|magic
op_assign
l_int|0x60000
suffix:semicolon
id|memsize
op_assign
l_int|0x10000
suffix:semicolon
id|features
op_assign
id|BRI_FEATURES
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ram
(braket
id|b
)braket
op_rshift
l_int|12
op_amp
l_int|0x0F
)paren
(brace
r_case
l_int|0x0
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;RAM Page register set to EXP_PAGE0&bslash;n&quot;
)paren
suffix:semicolon
id|pgport
op_assign
id|EXP_PAGE0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;RAM Page register set to EXP_PAGE1&bslash;n&quot;
)paren
suffix:semicolon
id|pgport
op_assign
id|EXP_PAGE1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x8
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;RAM Page register set to EXP_PAGE2&bslash;n&quot;
)paren
suffix:semicolon
id|pgport
op_assign
id|EXP_PAGE2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xC
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;RAM Page register set to EXP_PAGE3&bslash;n&quot;
)paren
suffix:semicolon
id|pgport
op_assign
id|EXP_PAGE3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;RAM base address doesn&squot;t fall on 16K boundary&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;current IRQ: %d  b: %d&bslash;n&quot;
comma
id|irq
(braket
id|b
)braket
comma
id|b
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Make sure we got an IRQ&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|irq
(braket
id|b
)braket
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * No interrupt could be used&n;&t;&t;&t; */
id|pr_debug
c_func
(paren
l_string|&quot;Failed to acquire an IRQ line&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Horray! We found a board, Make sure we can register&n;&t;&t; * it with ISDN4Linux&n;&t;&t; */
id|interface
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|isdn_if
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|interface
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Oops, can&squot;t malloc isdn_if&n;&t;&t;&t; */
r_continue
suffix:semicolon
)brace
id|memset
c_func
(paren
id|interface
comma
l_int|0
comma
r_sizeof
(paren
id|isdn_if
)paren
)paren
suffix:semicolon
id|interface-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|interface-&gt;hl_hdrlen
op_assign
l_int|0
suffix:semicolon
id|interface-&gt;channels
op_assign
id|channels
suffix:semicolon
id|interface-&gt;maxbufsize
op_assign
id|BUFFER_SIZE
suffix:semicolon
id|interface-&gt;features
op_assign
id|features
suffix:semicolon
id|interface-&gt;writebuf_skb
op_assign
id|sndpkt
suffix:semicolon
id|interface-&gt;writecmd
op_assign
l_int|NULL
suffix:semicolon
id|interface-&gt;command
op_assign
id|command
suffix:semicolon
id|strcpy
c_func
(paren
id|interface-&gt;id
comma
id|devname
)paren
suffix:semicolon
id|interface-&gt;id
(braket
l_int|2
)braket
op_assign
l_char|&squot;0&squot;
op_plus
id|cinst
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Allocate the board structure&n;&t;&t; */
id|sc_adapter
(braket
id|cinst
)braket
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|board
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sc_adapter
(braket
id|cinst
)braket
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Oops, can&squot;t alloc memory for the board&n;&t;&t;&t; */
id|kfree
c_func
(paren
id|interface
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|memset
c_func
(paren
id|sc_adapter
(braket
id|cinst
)braket
comma
l_int|0
comma
r_sizeof
(paren
id|board
)paren
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|register_isdn
c_func
(paren
id|interface
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Oops, couldn&squot;t register for some reason&n;&t;&t;&t; */
id|kfree
c_func
(paren
id|interface
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sc_adapter
(braket
id|cinst
)braket
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|card
op_assign
id|interface
suffix:semicolon
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|driverId
op_assign
id|interface-&gt;channels
suffix:semicolon
id|strcpy
c_func
(paren
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|devicename
comma
id|interface-&gt;id
)paren
suffix:semicolon
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|nChannels
op_assign
id|channels
suffix:semicolon
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|ramsize
op_assign
id|memsize
suffix:semicolon
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|shmem_magic
op_assign
id|magic
suffix:semicolon
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|shmem_pgport
op_assign
id|pgport
suffix:semicolon
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|StartOnReset
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Allocate channels status structures&n;&t;&t; */
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|channel
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|bchan
)paren
op_star
id|channels
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|channel
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Oops, can&squot;t alloc memory for the channels&n;&t;&t;&t; */
id|indicate_status
c_func
(paren
id|cinst
comma
id|ISDN_STAT_UNLOAD
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Fix me */
id|kfree
c_func
(paren
id|interface
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sc_adapter
(braket
id|cinst
)braket
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|memset
c_func
(paren
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|channel
comma
l_int|0
comma
r_sizeof
(paren
id|bchan
)paren
op_star
id|channels
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Lock down the hardware resources&n;&t;&t; */
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|interrupt
op_assign
id|irq
(braket
id|b
)braket
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|interrupt
comma
id|interrupt_handler
comma
id|SA_INTERRUPT
comma
id|interface-&gt;id
comma
l_int|NULL
)paren
)paren
(brace
id|kfree
c_func
(paren
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|channel
)paren
suffix:semicolon
id|indicate_status
c_func
(paren
id|cinst
comma
id|ISDN_STAT_UNLOAD
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Fix me */
id|kfree
c_func
(paren
id|interface
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sc_adapter
(braket
id|cinst
)braket
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|iobase
op_assign
id|io
(braket
id|b
)braket
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
id|MAX_IO_REGS
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|ioport
(braket
id|i
)braket
op_assign
id|io
(braket
id|b
)braket
op_plus
id|i
op_star
l_int|0x400
suffix:semicolon
id|request_region
c_func
(paren
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|ioport
(braket
id|i
)braket
comma
l_int|1
comma
id|interface-&gt;id
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Requesting I/O Port %#x&bslash;n&quot;
comma
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|ioport
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|ioport
(braket
id|IRQ_SELECT
)braket
op_assign
id|io
(braket
id|b
)braket
op_plus
l_int|0x2
suffix:semicolon
id|request_region
c_func
(paren
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|ioport
(braket
id|IRQ_SELECT
)braket
comma
l_int|1
comma
id|interface-&gt;id
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Requesting I/O Port %#x&bslash;n&quot;
comma
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|ioport
(braket
id|IRQ_SELECT
)braket
)paren
suffix:semicolon
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|rambase
op_assign
id|ram
(braket
id|b
)braket
suffix:semicolon
id|request_region
c_func
(paren
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|rambase
comma
id|SRAM_PAGESIZE
comma
id|interface-&gt;id
)paren
suffix:semicolon
id|pr_info
c_func
(paren
l_string|&quot;  %s (%d) - %s %d channels IRQ %d, I/O Base 0x%x, RAM Base 0x%lx&bslash;n&quot;
comma
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|devicename
comma
id|sc_adapter
(braket
id|cinst
)braket
op_member_access_from_pointer
id|driverId
comma
id|boardname
(braket
id|model
)braket
comma
id|channels
comma
id|irq
(braket
id|b
)braket
comma
id|io
(braket
id|b
)braket
comma
id|ram
(braket
id|b
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * reset the adapter to put things in motion&n;&t;&t; */
id|reset
c_func
(paren
id|cinst
)paren
suffix:semicolon
id|cinst
op_increment
suffix:semicolon
id|status
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
)paren
id|pr_info
c_func
(paren
l_string|&quot;Failed to find any adapters, driver unloaded&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|sc_exit
r_static
r_void
id|__exit
id|sc_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
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
id|cinst
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Cleaning up after adapter %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * kill the timers&n;&t;&t; */
id|del_timer
c_func
(paren
op_amp
(paren
id|sc_adapter
(braket
id|i
)braket
op_member_access_from_pointer
id|reset_timer
)paren
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
(paren
id|sc_adapter
(braket
id|i
)braket
op_member_access_from_pointer
id|stat_timer
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Tell I4L we&squot;re toast&n;&t;&t; */
id|indicate_status
c_func
(paren
id|i
comma
id|ISDN_STAT_STOP
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|indicate_status
c_func
(paren
id|i
comma
id|ISDN_STAT_UNLOAD
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Release shared RAM&n;&t;&t; */
id|release_region
c_func
(paren
id|sc_adapter
(braket
id|i
)braket
op_member_access_from_pointer
id|rambase
comma
id|SRAM_PAGESIZE
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Release the IRQ&n;&t;&t; */
id|FREE_IRQ
c_func
(paren
id|sc_adapter
(braket
id|i
)braket
op_member_access_from_pointer
id|interrupt
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Reset for a clean start&n;&t;&t; */
id|outb
c_func
(paren
l_int|0xFF
comma
id|sc_adapter
(braket
id|i
)braket
op_member_access_from_pointer
id|ioport
(braket
id|SFT_RESET
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Release the I/O Port regions&n;&t;&t; */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|MAX_IO_REGS
op_minus
l_int|1
suffix:semicolon
id|j
op_increment
)paren
(brace
id|release_region
c_func
(paren
id|sc_adapter
(braket
id|i
)braket
op_member_access_from_pointer
id|ioport
(braket
id|j
)braket
comma
l_int|1
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Releasing I/O Port %#x&bslash;n&quot;
comma
id|sc_adapter
(braket
id|i
)braket
op_member_access_from_pointer
id|ioport
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
id|release_region
c_func
(paren
id|sc_adapter
(braket
id|i
)braket
op_member_access_from_pointer
id|ioport
(braket
id|IRQ_SELECT
)braket
comma
l_int|1
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Releasing I/O Port %#x&bslash;n&quot;
comma
id|sc_adapter
(braket
id|i
)braket
op_member_access_from_pointer
id|ioport
(braket
id|IRQ_SELECT
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Release any memory we alloced&n;&t;&t; */
id|kfree
c_func
(paren
id|sc_adapter
(braket
id|i
)braket
op_member_access_from_pointer
id|channel
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sc_adapter
(braket
id|i
)braket
op_member_access_from_pointer
id|card
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sc_adapter
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|pr_info
c_func
(paren
l_string|&quot;SpellCaster ISA ISDN Adapter Driver Unloaded.&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|identify_board
r_int
id|identify_board
c_func
(paren
r_int
r_int
id|rambase
comma
r_int
r_int
id|iobase
)paren
(brace
r_int
r_int
id|pgport
suffix:semicolon
r_int
r_int
id|sig
suffix:semicolon
id|DualPortMemory
op_star
id|dpm
suffix:semicolon
id|RspMessage
id|rcvmsg
suffix:semicolon
id|ReqMessage
id|sndmsg
suffix:semicolon
id|HWConfig_pl
id|hwci
suffix:semicolon
r_int
id|x
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Attempting to identify adapter @ 0x%x io 0x%x&bslash;n&quot;
comma
id|rambase
comma
id|iobase
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Enable the base pointer&n;&t; */
id|outb
c_func
(paren
id|rambase
op_rshift
l_int|12
comma
id|iobase
op_plus
l_int|0x2c00
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|rambase
op_rshift
l_int|12
op_amp
l_int|0x0F
)paren
(brace
r_case
l_int|0x0
suffix:colon
id|pgport
op_assign
id|iobase
op_plus
id|PG0_OFFSET
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Page Register offset is 0x%x&bslash;n&quot;
comma
id|PG0_OFFSET
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4
suffix:colon
id|pgport
op_assign
id|iobase
op_plus
id|PG1_OFFSET
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Page Register offset is 0x%x&bslash;n&quot;
comma
id|PG1_OFFSET
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x8
suffix:colon
id|pgport
op_assign
id|iobase
op_plus
id|PG2_OFFSET
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Page Register offset is 0x%x&bslash;n&quot;
comma
id|PG2_OFFSET
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xC
suffix:colon
id|pgport
op_assign
id|iobase
op_plus
id|PG3_OFFSET
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Page Register offset is 0x%x&bslash;n&quot;
comma
id|PG3_OFFSET
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|pr_debug
c_func
(paren
l_string|&quot;Invalid rambase 0x%lx&bslash;n&quot;
comma
id|rambase
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Try to identify a PRI card&n;&t; */
id|outb
c_func
(paren
id|PRI_BASEPG_VAL
comma
id|pgport
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
)paren
suffix:semicolon
id|sig
op_assign
id|readl
c_func
(paren
id|rambase
op_plus
id|SIG_OFFSET
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Looking for a signature, got 0x%x&bslash;n&quot;
comma
id|sig
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_eq
id|SIGNATURE
)paren
(brace
r_return
id|PRI_BOARD
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Try to identify a PRI card&n;&t; */
id|outb
c_func
(paren
id|BRI_BASEPG_VAL
comma
id|pgport
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
)paren
suffix:semicolon
id|sig
op_assign
id|readl
c_func
(paren
id|rambase
op_plus
id|SIG_OFFSET
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Looking for a signature, got 0x%x&bslash;n&quot;
comma
id|sig
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_eq
id|SIGNATURE
)paren
(brace
r_return
id|BRI_BOARD
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Try to spot a card&n;&t; */
id|sig
op_assign
id|readl
c_func
(paren
id|rambase
op_plus
id|SIG_OFFSET
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Looking for a signature, got 0x%x&bslash;n&quot;
comma
id|sig
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_ne
id|SIGNATURE
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dpm
op_assign
(paren
id|DualPortMemory
op_star
)paren
id|rambase
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|sndmsg
comma
l_int|0
comma
id|MSG_LEN
)paren
suffix:semicolon
id|sndmsg.msg_byte_cnt
op_assign
l_int|3
suffix:semicolon
id|sndmsg.type
op_assign
id|cmReqType1
suffix:semicolon
id|sndmsg
dot
r_class
op_assign
id|cmReqClass0
suffix:semicolon
id|sndmsg.code
op_assign
id|cmReqHWConfig
suffix:semicolon
id|memcpy_toio
c_func
(paren
op_amp
(paren
id|dpm-&gt;req_queue
(braket
id|dpm-&gt;req_head
op_increment
)braket
)paren
comma
op_amp
id|sndmsg
comma
id|MSG_LEN
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|iobase
op_plus
l_int|0x400
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Sent HWConfig message&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Wait for the response&n;&t; */
id|x
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|iobase
op_plus
id|FIFOSTAT_OFFSET
)paren
op_amp
id|RF_HAS_DATA
)paren
op_logical_and
id|x
OL
l_int|100
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|x
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x
op_eq
l_int|100
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;Timeout waiting for response&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|memcpy_fromio
c_func
(paren
op_amp
id|rcvmsg
comma
op_amp
(paren
id|dpm-&gt;rsp_queue
(braket
id|dpm-&gt;rsp_tail
)braket
)paren
comma
id|MSG_LEN
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Got HWConfig response, status = 0x%x&bslash;n&quot;
comma
id|rcvmsg.rsp_status
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|hwci
comma
op_amp
(paren
id|rcvmsg.msg_data.HWCresponse
)paren
comma
r_sizeof
(paren
id|HWConfig_pl
)paren
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Hardware Config: Interface: %s, RAM Size: %d, Serial: %s&bslash;n&quot;
l_string|&quot;                 Part: %s, Rev: %s&bslash;n&quot;
comma
id|hwci.st_u_sense
ques
c_cond
l_string|&quot;S/T&quot;
suffix:colon
l_string|&quot;U&quot;
comma
id|hwci.ram_size
comma
id|hwci.serial_no
comma
id|hwci.part_no
comma
id|hwci.rev_no
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|PRI_PARTNO
comma
id|hwci.part_no
comma
l_int|6
)paren
)paren
(brace
r_return
id|PRI_BOARD
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|BRI_PARTNO
comma
id|hwci.part_no
comma
l_int|6
)paren
)paren
(brace
r_return
id|BRI_BOARD
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|sc_init
id|module_init
c_func
(paren
id|sc_init
)paren
suffix:semicolon
DECL|variable|sc_exit
id|module_exit
c_func
(paren
id|sc_exit
)paren
suffix:semicolon
eof
