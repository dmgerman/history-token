multiline_comment|/* $Id: act2000_isa.c,v 1.11.6.3 2001/09/23 22:24:32 kai Exp $&n; *&n; * ISDN lowlevel-module for the IBM ISDN-S0 Active 2000 (ISA-Version).&n; *&n; * Author       Fritz Elfert&n; * Copyright    by Fritz Elfert      &lt;fritz@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; * Thanks to Friedemann Baitinger and IBM Germany&n; *&n; */
macro_line|#include &quot;act2000.h&quot;
macro_line|#include &quot;act2000_isa.h&quot;
macro_line|#include &quot;capi.h&quot;
DECL|variable|irq2card_map
r_static
id|act2000_card
op_star
id|irq2card_map
(braket
l_int|16
)braket
suffix:semicolon
r_static
r_void
DECL|function|act2000_isa_delay
id|act2000_isa_delay
c_func
(paren
r_int
id|t
)paren
(brace
id|sti
c_func
(paren
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
id|t
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Reset Controller, then try to read the Card&squot;s signature.&n; + Return:&n; *   1 = Signature found.&n; *   0 = Signature not found.&n; */
r_static
r_int
DECL|function|act2000_isa_reset
id|act2000_isa_reset
c_func
(paren
r_int
r_int
id|portbase
)paren
(brace
r_int
r_char
id|reg
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|found
suffix:semicolon
r_int
id|serial
op_assign
l_int|0
suffix:semicolon
id|found
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|reg
op_assign
id|inb
c_func
(paren
id|portbase
op_plus
id|ISA_COR
)paren
)paren
op_ne
l_int|0xff
)paren
(brace
id|outb
c_func
(paren
id|reg
op_or
id|ISA_COR_RESET
comma
id|portbase
op_plus
id|ISA_COR
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|outb
c_func
(paren
id|reg
comma
id|portbase
op_plus
id|ISA_COR
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|10
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|inb
c_func
(paren
id|portbase
op_plus
id|ISA_ISR
)paren
op_amp
id|ISA_ISR_SERIAL
)paren
id|serial
op_or_assign
l_int|0x10000
suffix:semicolon
id|serial
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serial
op_eq
id|ISA_SER_ID
)paren
id|found
op_increment
suffix:semicolon
)brace
r_return
id|found
suffix:semicolon
)brace
r_int
DECL|function|act2000_isa_detect
id|act2000_isa_detect
c_func
(paren
r_int
r_int
id|portbase
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|check_region
c_func
(paren
id|portbase
comma
id|ISA_REGION
)paren
)paren
id|ret
op_assign
id|act2000_isa_reset
c_func
(paren
id|portbase
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
id|irqreturn_t
DECL|function|act2000_isa_interrupt
id|act2000_isa_interrupt
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
id|act2000_card
op_star
id|card
op_assign
id|irq2card_map
(braket
id|irq
)braket
suffix:semicolon
id|u_char
id|istatus
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;act2000: Spurious interrupt!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
id|istatus
op_assign
(paren
id|inb
c_func
(paren
id|ISA_PORT_ISR
)paren
op_amp
l_int|0x07
)paren
suffix:semicolon
r_if
c_cond
(paren
id|istatus
op_amp
id|ISA_ISR_OUT
)paren
(brace
multiline_comment|/* RX fifo has data */
id|istatus
op_and_assign
id|ISA_ISR_OUT_MASK
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|ISA_PORT_SIS
)paren
suffix:semicolon
id|act2000_isa_receive
c_func
(paren
id|card
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ISA_SIS_INT
comma
id|ISA_PORT_SIS
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|istatus
op_amp
id|ISA_ISR_ERR
)paren
(brace
multiline_comment|/* Error Interrupt */
id|istatus
op_and_assign
id|ISA_ISR_ERR_MASK
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;act2000: errIRQ&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|istatus
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;act2000: ?IRQ %d %02x&bslash;n&quot;
comma
id|irq
comma
id|istatus
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_static
r_void
DECL|function|act2000_isa_select_irq
id|act2000_isa_select_irq
c_func
(paren
id|act2000_card
op_star
id|card
)paren
(brace
r_int
r_char
id|reg
suffix:semicolon
id|reg
op_assign
(paren
id|inb
c_func
(paren
id|ISA_PORT_COR
)paren
op_amp
op_complement
id|ISA_COR_IRQOFF
)paren
op_or
id|ISA_COR_PERR
suffix:semicolon
r_switch
c_cond
(paren
id|card-&gt;irq
)paren
(brace
r_case
l_int|3
suffix:colon
id|reg
op_assign
id|ISA_COR_IRQ03
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|reg
op_assign
id|ISA_COR_IRQ05
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|reg
op_assign
id|ISA_COR_IRQ07
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|reg
op_assign
id|ISA_COR_IRQ10
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|reg
op_assign
id|ISA_COR_IRQ11
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|reg
op_assign
id|ISA_COR_IRQ12
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
id|reg
op_assign
id|ISA_COR_IRQ15
suffix:semicolon
r_break
suffix:semicolon
)brace
id|outb
c_func
(paren
id|reg
comma
id|ISA_PORT_COR
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|act2000_isa_enable_irq
id|act2000_isa_enable_irq
c_func
(paren
id|act2000_card
op_star
id|card
)paren
(brace
id|act2000_isa_select_irq
c_func
(paren
id|card
)paren
suffix:semicolon
multiline_comment|/* Enable READ irq */
id|outb
c_func
(paren
id|ISA_SIS_INT
comma
id|ISA_PORT_SIS
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Install interrupt handler, enable irq on card.&n; * If irq is -1, choose next free irq, else irq is given explicitely.&n; */
r_int
DECL|function|act2000_isa_config_irq
id|act2000_isa_config_irq
c_func
(paren
id|act2000_card
op_star
id|card
comma
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;flags
op_amp
id|ACT2000_FLAGS_IVALID
)paren
(brace
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
l_int|NULL
)paren
suffix:semicolon
id|irq2card_map
(braket
id|card-&gt;irq
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
id|card-&gt;flags
op_and_assign
op_complement
id|ACT2000_FLAGS_IVALID
suffix:semicolon
id|outb
c_func
(paren
id|ISA_COR_IRQOFF
comma
id|ISA_PORT_COR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_irq
c_func
(paren
id|irq
comma
op_amp
id|act2000_isa_interrupt
comma
l_int|0
comma
id|card-&gt;regname
comma
l_int|NULL
)paren
)paren
(brace
id|card-&gt;irq
op_assign
id|irq
suffix:semicolon
id|irq2card_map
(braket
id|card-&gt;irq
)braket
op_assign
id|card
suffix:semicolon
id|card-&gt;flags
op_or_assign
id|ACT2000_FLAGS_IVALID
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;act2000: Could not request irq %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
(brace
id|act2000_isa_select_irq
c_func
(paren
id|card
)paren
suffix:semicolon
multiline_comment|/* Disable READ and WRITE irq */
id|outb
c_func
(paren
l_int|0
comma
id|ISA_PORT_SIS
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|ISA_PORT_SOS
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|act2000_isa_config_port
id|act2000_isa_config_port
c_func
(paren
id|act2000_card
op_star
id|card
comma
r_int
r_int
id|portbase
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;flags
op_amp
id|ACT2000_FLAGS_PVALID
)paren
(brace
id|release_region
c_func
(paren
id|card-&gt;port
comma
id|ISA_REGION
)paren
suffix:semicolon
id|card-&gt;flags
op_and_assign
op_complement
id|ACT2000_FLAGS_PVALID
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|check_region
c_func
(paren
id|portbase
comma
id|ISA_REGION
)paren
)paren
(brace
r_if
c_cond
(paren
id|request_region
c_func
(paren
id|portbase
comma
id|ACT2000_PORTLEN
comma
id|card-&gt;regname
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|card-&gt;port
op_assign
id|portbase
suffix:semicolon
id|card-&gt;flags
op_or_assign
id|ACT2000_FLAGS_PVALID
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/*&n; * Release ressources, used by an adaptor.&n; */
r_void
DECL|function|act2000_isa_release
id|act2000_isa_release
c_func
(paren
id|act2000_card
op_star
id|card
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;flags
op_amp
id|ACT2000_FLAGS_IVALID
)paren
(brace
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
l_int|NULL
)paren
suffix:semicolon
id|irq2card_map
(braket
id|card-&gt;irq
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
id|card-&gt;flags
op_and_assign
op_complement
id|ACT2000_FLAGS_IVALID
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;flags
op_amp
id|ACT2000_FLAGS_PVALID
)paren
id|release_region
c_func
(paren
id|card-&gt;port
comma
id|ISA_REGION
)paren
suffix:semicolon
id|card-&gt;flags
op_and_assign
op_complement
id|ACT2000_FLAGS_PVALID
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|act2000_isa_writeb
id|act2000_isa_writeb
c_func
(paren
id|act2000_card
op_star
id|card
comma
id|u_char
id|data
)paren
(brace
id|u_char
id|timeout
op_assign
l_int|40
suffix:semicolon
r_while
c_loop
(paren
id|timeout
)paren
(brace
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ISA_PORT_SOS
)paren
op_amp
id|ISA_SOS_READY
)paren
(brace
id|outb
c_func
(paren
id|data
comma
id|ISA_PORT_SDO
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|timeout
op_decrement
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|act2000_isa_readb
id|act2000_isa_readb
c_func
(paren
id|act2000_card
op_star
id|card
comma
id|u_char
op_star
id|data
)paren
(brace
id|u_char
id|timeout
op_assign
l_int|40
suffix:semicolon
r_while
c_loop
(paren
id|timeout
)paren
(brace
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ISA_PORT_SIS
)paren
op_amp
id|ISA_SIS_READY
)paren
(brace
op_star
id|data
op_assign
id|inb
c_func
(paren
id|ISA_PORT_SDI
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|timeout
op_decrement
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_void
DECL|function|act2000_isa_receive
id|act2000_isa_receive
c_func
(paren
id|act2000_card
op_star
id|card
)paren
(brace
id|u_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|ACT2000_LOCK_RX
comma
(paren
r_void
op_star
)paren
op_amp
id|card-&gt;ilock
)paren
op_ne
l_int|0
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|act2000_isa_readb
c_func
(paren
id|card
comma
op_amp
id|c
)paren
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;idat.isa.rcvidx
OL
l_int|8
)paren
(brace
id|card-&gt;idat.isa.rcvhdr
(braket
id|card-&gt;idat.isa.rcvidx
op_increment
)braket
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;idat.isa.rcvidx
op_eq
l_int|8
)paren
(brace
r_int
id|valid
op_assign
id|actcapi_chkhdr
c_func
(paren
id|card
comma
(paren
id|actcapi_msghdr
op_star
)paren
op_amp
id|card-&gt;idat.isa.rcvhdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|valid
)paren
(brace
id|card-&gt;idat.isa.rcvlen
op_assign
(paren
(paren
id|actcapi_msghdr
op_star
)paren
op_amp
id|card-&gt;idat.isa.rcvhdr
)paren
op_member_access_from_pointer
id|len
suffix:semicolon
id|card-&gt;idat.isa.rcvskb
op_assign
id|dev_alloc_skb
c_func
(paren
id|card-&gt;idat.isa.rcvlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;idat.isa.rcvskb
op_eq
l_int|NULL
)paren
(brace
id|card-&gt;idat.isa.rcvignore
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;act2000_isa_receive: no memory&bslash;n&quot;
)paren
suffix:semicolon
id|test_and_clear_bit
c_func
(paren
id|ACT2000_LOCK_RX
comma
(paren
r_void
op_star
)paren
op_amp
id|card-&gt;ilock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|card-&gt;idat.isa.rcvskb
comma
l_int|8
)paren
comma
id|card-&gt;idat.isa.rcvhdr
comma
l_int|8
)paren
suffix:semicolon
id|card-&gt;idat.isa.rcvptr
op_assign
id|skb_put
c_func
(paren
id|card-&gt;idat.isa.rcvskb
comma
id|card-&gt;idat.isa.rcvlen
op_minus
l_int|8
)paren
suffix:semicolon
)brace
r_else
(brace
id|card-&gt;idat.isa.rcvidx
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;act2000_isa_receive: Invalid CAPI msg&bslash;n&quot;
)paren
suffix:semicolon
(brace
r_int
id|i
suffix:semicolon
id|__u8
op_star
id|p
suffix:semicolon
id|__u8
op_star
id|c
suffix:semicolon
id|__u8
id|tmp
(braket
l_int|30
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|p
op_assign
(paren
id|__u8
op_star
)paren
op_amp
id|card-&gt;idat.isa.rcvhdr
comma
id|c
op_assign
id|tmp
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|c
op_add_assign
id|sprintf
c_func
(paren
id|c
comma
l_string|&quot;%02x &quot;
comma
op_star
(paren
id|p
op_increment
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;act2000_isa_receive: %s&bslash;n&quot;
comma
id|tmp
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;idat.isa.rcvignore
)paren
op_star
id|card-&gt;idat.isa.rcvptr
op_increment
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|card-&gt;idat.isa.rcvidx
op_ge
id|card-&gt;idat.isa.rcvlen
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;idat.isa.rcvignore
)paren
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|card-&gt;rcvq
comma
id|card-&gt;idat.isa.rcvskb
)paren
suffix:semicolon
id|act2000_schedule_rx
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
id|card-&gt;idat.isa.rcvidx
op_assign
l_int|0
suffix:semicolon
id|card-&gt;idat.isa.rcvlen
op_assign
l_int|8
suffix:semicolon
id|card-&gt;idat.isa.rcvignore
op_assign
l_int|0
suffix:semicolon
id|card-&gt;idat.isa.rcvskb
op_assign
l_int|NULL
suffix:semicolon
id|card-&gt;idat.isa.rcvptr
op_assign
id|card-&gt;idat.isa.rcvhdr
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|card-&gt;flags
op_amp
id|ACT2000_FLAGS_IVALID
)paren
)paren
(brace
multiline_comment|/* In polling mode, schedule myself */
r_if
c_cond
(paren
(paren
id|card-&gt;idat.isa.rcvidx
)paren
op_logical_and
(paren
id|card-&gt;idat.isa.rcvignore
op_logical_or
(paren
id|card-&gt;idat.isa.rcvidx
OL
id|card-&gt;idat.isa.rcvlen
)paren
)paren
)paren
id|act2000_schedule_poll
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
id|test_and_clear_bit
c_func
(paren
id|ACT2000_LOCK_RX
comma
(paren
r_void
op_star
)paren
op_amp
id|card-&gt;ilock
)paren
suffix:semicolon
)brace
r_void
DECL|function|act2000_isa_send
id|act2000_isa_send
c_func
(paren
id|act2000_card
op_star
id|card
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|actcapi_msg
op_star
id|msg
suffix:semicolon
r_int
id|l
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|ACT2000_LOCK_TX
comma
(paren
r_void
op_star
)paren
op_amp
id|card-&gt;ilock
)paren
op_ne
l_int|0
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|card-&gt;sbuf
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|card-&gt;sbuf
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|card-&gt;sndq
)paren
)paren
)paren
(brace
id|card-&gt;ack_msg
op_assign
id|card-&gt;sbuf-&gt;data
suffix:semicolon
id|msg
op_assign
(paren
id|actcapi_msg
op_star
)paren
id|card-&gt;sbuf-&gt;data
suffix:semicolon
r_if
c_cond
(paren
(paren
id|msg-&gt;hdr.cmd.cmd
op_eq
l_int|0x86
)paren
op_logical_and
(paren
id|msg-&gt;hdr.cmd.subcmd
op_eq
l_int|0
)paren
)paren
(brace
multiline_comment|/* Save flags in message */
id|card-&gt;need_b3ack
op_assign
id|msg-&gt;msg.data_b3_req.flags
suffix:semicolon
id|msg-&gt;msg.data_b3_req.flags
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|card-&gt;sbuf
)paren
)paren
(brace
multiline_comment|/* No more data to send */
id|test_and_clear_bit
c_func
(paren
id|ACT2000_LOCK_TX
comma
(paren
r_void
op_star
)paren
op_amp
id|card-&gt;ilock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb
op_assign
id|card-&gt;sbuf
suffix:semicolon
id|l
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|skb-&gt;len
)paren
(brace
r_if
c_cond
(paren
id|act2000_isa_writeb
c_func
(paren
id|card
comma
op_star
(paren
id|skb-&gt;data
)paren
)paren
)paren
(brace
multiline_comment|/* Fifo is full, but more data to send */
id|test_and_clear_bit
c_func
(paren
id|ACT2000_LOCK_TX
comma
(paren
r_void
op_star
)paren
op_amp
id|card-&gt;ilock
)paren
suffix:semicolon
multiline_comment|/* Schedule myself */
id|act2000_schedule_tx
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb_pull
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
id|l
op_increment
suffix:semicolon
)brace
id|msg
op_assign
(paren
id|actcapi_msg
op_star
)paren
id|card-&gt;ack_msg
suffix:semicolon
r_if
c_cond
(paren
(paren
id|msg-&gt;hdr.cmd.cmd
op_eq
l_int|0x86
)paren
op_logical_and
(paren
id|msg-&gt;hdr.cmd.subcmd
op_eq
l_int|0
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * If it&squot;s user data, reset data-ptr&n;&t;&t;&t; * and put skb into ackq.&n;&t;&t;&t; */
id|skb-&gt;data
op_assign
id|card-&gt;ack_msg
suffix:semicolon
multiline_comment|/* Restore flags in message */
id|msg-&gt;msg.data_b3_req.flags
op_assign
id|card-&gt;need_b3ack
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|card-&gt;ackq
comma
id|skb
)paren
suffix:semicolon
)brace
r_else
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|card-&gt;sbuf
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Get firmware ID, check for &squot;ISDN&squot; signature.&n; */
r_static
r_int
DECL|function|act2000_isa_getid
id|act2000_isa_getid
c_func
(paren
id|act2000_card
op_star
id|card
)paren
(brace
id|act2000_fwid
id|fid
suffix:semicolon
id|u_char
op_star
id|p
op_assign
(paren
id|u_char
op_star
)paren
op_amp
id|fid
suffix:semicolon
r_int
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
r_if
c_cond
(paren
id|count
OG
l_int|510
)paren
r_return
op_minus
id|EPROTO
suffix:semicolon
r_if
c_cond
(paren
id|act2000_isa_readb
c_func
(paren
id|card
comma
id|p
op_increment
)paren
)paren
r_break
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_le
l_int|20
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;act2000: No Firmware-ID!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ETIME
suffix:semicolon
)brace
op_star
id|p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|fid.revlen
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|fid.isdn
comma
l_string|&quot;ISDN&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;act2000: Wrong Firmware-ID!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EPROTO
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|fid.revision
comma
l_char|&squot;&bslash;n&squot;
)paren
)paren
)paren
op_star
id|p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;act2000: Firmware-ID: %s&bslash;n&quot;
comma
id|fid.revision
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;flags
op_amp
id|ACT2000_FLAGS_IVALID
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Enabling Interrupts ...&bslash;n&quot;
)paren
suffix:semicolon
id|act2000_isa_enable_irq
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Download microcode into card, check Firmware signature.&n; */
r_int
DECL|function|act2000_isa_download
id|act2000_isa_download
c_func
(paren
id|act2000_card
op_star
id|card
comma
id|act2000_ddef
op_star
id|cb
)paren
(brace
r_int
r_int
id|length
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|l
suffix:semicolon
r_int
id|c
suffix:semicolon
r_int
id|timeout
suffix:semicolon
id|u_char
op_star
id|b
suffix:semicolon
id|u_char
op_star
id|p
suffix:semicolon
id|u_char
op_star
id|buf
suffix:semicolon
id|act2000_ddef
id|cblock
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|act2000_isa_reset
c_func
(paren
id|card-&gt;port
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|act2000_isa_delay
c_func
(paren
id|HZ
op_div
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|cblock
comma
(paren
r_char
op_star
)paren
id|cb
comma
r_sizeof
(paren
id|cblock
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|length
op_assign
id|cblock.length
suffix:semicolon
id|p
op_assign
id|cblock.buffer
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|p
comma
id|length
)paren
)paren
)paren
r_return
id|ret
suffix:semicolon
id|buf
op_assign
(paren
id|u_char
op_star
)paren
id|kmalloc
c_func
(paren
l_int|1024
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|timeout
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|length
)paren
(brace
id|l
op_assign
(paren
id|length
OG
l_int|1024
)paren
ques
c_cond
l_int|1024
suffix:colon
id|length
suffix:semicolon
id|c
op_assign
l_int|0
suffix:semicolon
id|b
op_assign
id|buf
suffix:semicolon
id|copy_from_user
c_func
(paren
id|buf
comma
id|p
comma
id|l
)paren
suffix:semicolon
r_while
c_loop
(paren
id|c
OL
id|l
)paren
(brace
r_if
c_cond
(paren
id|act2000_isa_writeb
c_func
(paren
id|card
comma
op_star
id|b
op_increment
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;act2000: loader timed out&quot;
l_string|&quot; len=%d c=%d&bslash;n&quot;
comma
id|length
comma
id|c
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
op_minus
id|ETIME
suffix:semicolon
)brace
id|c
op_increment
suffix:semicolon
)brace
id|length
op_sub_assign
id|l
suffix:semicolon
id|p
op_add_assign
id|l
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|act2000_isa_delay
c_func
(paren
id|HZ
op_div
l_int|2
)paren
suffix:semicolon
r_return
(paren
id|act2000_isa_getid
c_func
(paren
id|card
)paren
)paren
suffix:semicolon
)brace
eof
