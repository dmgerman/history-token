multiline_comment|/*&n; *  skisa.c: A network driver for SK-NET TMS380-based ISA token ring cards.&n; *&n; *  Based on tmspci written 1999 by Adam Fritzler&n; *  &n; *  Written 2000 by Jochen Friedrich&n; *  Dedicated to my girlfriend Steffi Bopp&n; *&n; *  This software may be used and distributed according to the terms&n; *  of the GNU General Public License, incorporated herein by reference.&n; *&n; *  This driver module supports the following cards:&n; *&t;- SysKonnect TR4/16(+) ISA&t;(SK-4190)&n; *&n; *  Maintainer(s):&n; *    AF        Adam Fritzler           mid@auk.cx&n; *    JF&t;Jochen Friedrich&t;jochen@scram.de&n; *&n; *  Modification History:&n; *&t;14-Jan-01&t;JF&t;Created&n; *&t;28-Oct-02&t;JF&t;Fixed probe of card for static compilation.&n; *&t;&t;&t;&t;Fixed module init to not make hotplug go wild.&n; *&t;09-Nov-02&t;JF&t;Fixed early bail out on out of memory&n; *&t;&t;&t;&t;situations if multiple cards are found.&n; *&t;&t;&t;&t;Cleaned up some unnecessary console SPAM.&n; *&t;09-Dec-02&t;JF&t;Fixed module reference counting.&n; *&t;02-Jan-03&t;JF&t;Renamed to skisa.c&n; *&n; */
DECL|variable|version
r_static
r_const
r_char
id|version
(braket
)braket
op_assign
l_string|&quot;skisa.c: v1.03 09/12/2002 by Jochen Friedrich&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &quot;tms380tr.h&quot;
DECL|macro|SK_ISA_IO_EXTENT
mdefine_line|#define SK_ISA_IO_EXTENT 32
multiline_comment|/* A zero-terminated list of I/O addresses to be probed. */
DECL|variable|__initdata
r_static
r_int
r_int
id|portlist
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x0A20
comma
l_int|0x1A20
comma
l_int|0x0B20
comma
l_int|0x1B20
comma
l_int|0x0980
comma
l_int|0x1980
comma
l_int|0x0900
comma
l_int|0x1900
comma
singleline_comment|// SK
l_int|0
)brace
suffix:semicolon
multiline_comment|/* A zero-terminated list of IRQs to be probed. &n; * Used again after initial probe for sktr_chipset_init, called from sktr_open.&n; */
DECL|variable|irqlist
r_static
r_const
r_int
r_int
id|irqlist
(braket
)braket
op_assign
(brace
l_int|3
comma
l_int|5
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
comma
l_int|15
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* A zero-terminated list of DMAs to be probed. */
DECL|variable|__initdata
r_static
r_int
id|dmalist
(braket
)braket
id|__initdata
op_assign
(brace
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|isa_cardname
r_static
r_char
id|isa_cardname
(braket
)braket
op_assign
l_string|&quot;SK NET TR 4/16 ISA&bslash;0&quot;
suffix:semicolon
r_struct
id|net_device
op_star
id|sk_isa_probe
c_func
(paren
r_int
id|unit
)paren
suffix:semicolon
r_static
r_int
id|sk_isa_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|sk_isa_read_eeprom
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
r_int
id|sk_isa_setnselout_pins
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|function|sk_isa_sifreadb
r_static
r_int
r_int
id|sk_isa_sifreadb
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|reg
)paren
(brace
r_return
id|inb
c_func
(paren
id|dev-&gt;base_addr
op_plus
id|reg
)paren
suffix:semicolon
)brace
DECL|function|sk_isa_sifreadw
r_static
r_int
r_int
id|sk_isa_sifreadw
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|reg
)paren
(brace
r_return
id|inw
c_func
(paren
id|dev-&gt;base_addr
op_plus
id|reg
)paren
suffix:semicolon
)brace
DECL|function|sk_isa_sifwriteb
r_static
r_void
id|sk_isa_sifwriteb
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|val
comma
r_int
r_int
id|reg
)paren
(brace
id|outb
c_func
(paren
id|val
comma
id|dev-&gt;base_addr
op_plus
id|reg
)paren
suffix:semicolon
)brace
DECL|function|sk_isa_sifwritew
r_static
r_void
id|sk_isa_sifwritew
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|val
comma
r_int
r_int
id|reg
)paren
(brace
id|outw
c_func
(paren
id|val
comma
id|dev-&gt;base_addr
op_plus
id|reg
)paren
suffix:semicolon
)brace
DECL|function|sk_isa_probe1
r_static
r_int
id|__init
id|sk_isa_probe1
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|ioaddr
)paren
(brace
r_int
r_char
id|old
comma
id|chk1
comma
id|chk2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|ioaddr
comma
id|SK_ISA_IO_EXTENT
comma
id|isa_cardname
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|old
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|SIFADR
)paren
suffix:semicolon
multiline_comment|/* Get the old SIFADR value */
id|chk1
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Begin with check value 0 */
r_do
(brace
multiline_comment|/* Write new SIFADR value */
id|outb
c_func
(paren
id|chk1
comma
id|ioaddr
op_plus
id|SIFADR
)paren
suffix:semicolon
multiline_comment|/* Read, invert and write */
id|chk2
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|SIFADD
)paren
suffix:semicolon
id|chk2
op_xor_assign
l_int|0x0FE
suffix:semicolon
id|outb
c_func
(paren
id|chk2
comma
id|ioaddr
op_plus
id|SIFADR
)paren
suffix:semicolon
multiline_comment|/* Read, invert and compare */
id|chk2
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|SIFADD
)paren
suffix:semicolon
id|chk2
op_xor_assign
l_int|0x0FE
suffix:semicolon
r_if
c_cond
(paren
id|chk1
op_ne
id|chk2
)paren
(brace
id|release_region
c_func
(paren
id|ioaddr
comma
id|SK_ISA_IO_EXTENT
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|chk1
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_while
c_loop
(paren
id|chk1
op_ne
l_int|0
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Repeat 128 times (all byte values) */
multiline_comment|/* Restore the SIFADR value */
id|outb
c_func
(paren
id|old
comma
id|ioaddr
op_plus
id|SIFADR
)paren
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|setup_card
r_static
r_int
id|__init
id|setup_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|tp
suffix:semicolon
r_static
r_int
id|versionprinted
suffix:semicolon
r_const
r_int
op_star
id|port
suffix:semicolon
r_int
id|j
comma
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;base_addr
)paren
multiline_comment|/* probe specific location */
id|err
op_assign
id|sk_isa_probe1
c_func
(paren
id|dev
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
r_else
(brace
r_for
c_loop
(paren
id|port
op_assign
id|portlist
suffix:semicolon
op_star
id|port
suffix:semicolon
id|port
op_increment
)paren
(brace
id|err
op_assign
id|sk_isa_probe1
c_func
(paren
id|dev
comma
op_star
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out4
suffix:semicolon
multiline_comment|/* At this point we have found a valid card. */
r_if
c_cond
(paren
id|versionprinted
op_increment
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s&quot;
comma
id|version
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|tmsdev_init
c_func
(paren
id|dev
comma
id|ISA_MAX_ADDRESS
comma
l_int|NULL
)paren
)paren
r_goto
id|out4
suffix:semicolon
id|dev-&gt;base_addr
op_and_assign
op_complement
l_int|3
suffix:semicolon
id|sk_isa_read_eeprom
c_func
(paren
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s:    Ring Station Address: &quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%2.2x&quot;
comma
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
l_int|6
suffix:semicolon
id|j
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;:%2.2x&quot;
comma
id|dev-&gt;dev_addr
(braket
id|j
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|tp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|tp-&gt;setnselout
op_assign
id|sk_isa_setnselout_pins
suffix:semicolon
id|tp-&gt;sifreadb
op_assign
id|sk_isa_sifreadb
suffix:semicolon
id|tp-&gt;sifreadw
op_assign
id|sk_isa_sifreadw
suffix:semicolon
id|tp-&gt;sifwriteb
op_assign
id|sk_isa_sifwriteb
suffix:semicolon
id|tp-&gt;sifwritew
op_assign
id|sk_isa_sifwritew
suffix:semicolon
id|memcpy
c_func
(paren
id|tp-&gt;ProductID
comma
id|isa_cardname
comma
id|PROD_ID_SIZE
op_plus
l_int|1
)paren
suffix:semicolon
id|tp-&gt;tmspriv
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;open
op_assign
id|sk_isa_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|tms380tr_close
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|irqlist
(braket
id|j
)braket
op_ne
l_int|0
suffix:semicolon
id|j
op_increment
)paren
(brace
id|dev-&gt;irq
op_assign
id|irqlist
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|tms380tr_interrupt
comma
l_int|0
comma
id|isa_cardname
comma
id|dev
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irqlist
(braket
id|j
)braket
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: AutoSelect no IRQ available&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_goto
id|out3
suffix:semicolon
)brace
)brace
r_else
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|irqlist
(braket
id|j
)braket
op_ne
l_int|0
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|irqlist
(braket
id|j
)braket
op_eq
id|dev-&gt;irq
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|irqlist
(braket
id|j
)braket
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Illegal IRQ %d specified&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_goto
id|out3
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|tms380tr_interrupt
comma
l_int|0
comma
id|isa_cardname
comma
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Selected IRQ %d not available&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_goto
id|out3
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dev-&gt;dma
op_eq
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|dmalist
(braket
id|j
)braket
op_ne
l_int|0
suffix:semicolon
id|j
op_increment
)paren
(brace
id|dev-&gt;dma
op_assign
id|dmalist
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_dma
c_func
(paren
id|dev-&gt;dma
comma
id|isa_cardname
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dmalist
(braket
id|j
)braket
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: AutoSelect no DMA available&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_goto
id|out2
suffix:semicolon
)brace
)brace
r_else
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|dmalist
(braket
id|j
)braket
op_ne
l_int|0
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|dmalist
(braket
id|j
)braket
op_eq
id|dev-&gt;dma
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|dmalist
(braket
id|j
)braket
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Illegal DMA %d specified&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;dma
)paren
suffix:semicolon
r_goto
id|out2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|dev-&gt;dma
comma
id|isa_cardname
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Selected DMA %d not available&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;dma
)paren
suffix:semicolon
r_goto
id|out2
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s:    IO: %#4lx  IRQ: %d  DMA: %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;base_addr
comma
id|dev-&gt;irq
comma
id|dev-&gt;dma
)paren
suffix:semicolon
id|err
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|free_dma
c_func
(paren
id|dev-&gt;dma
)paren
suffix:semicolon
id|out2
suffix:colon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|out3
suffix:colon
id|tmsdev_term
c_func
(paren
id|dev
)paren
suffix:semicolon
id|out4
suffix:colon
id|release_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|SK_ISA_IO_EXTENT
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|sk_isa_probe
r_struct
id|net_device
op_star
id|__init
id|sk_isa_probe
c_func
(paren
r_int
id|unit
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|alloc_trdev
c_func
(paren
r_sizeof
(paren
r_struct
id|net_local
)paren
)paren
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unit
op_ge
l_int|0
)paren
(brace
id|sprintf
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;tr%d&quot;
comma
id|unit
)paren
suffix:semicolon
id|netdev_boot_setup_check
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|err
op_assign
id|setup_card
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
r_return
id|dev
suffix:semicolon
id|out
suffix:colon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|err
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Reads MAC address from adapter RAM, which should&squot;ve read it from&n; * the onboard ROM.  &n; *&n; * Calling this on a board that does not support it can be a very&n; * dangerous thing.  The Madge board, for instance, will lock your&n; * machine hard when this is called.  Luckily, its supported in a&n; * separate driver.  --ASF&n; */
DECL|function|sk_isa_read_eeprom
r_static
r_void
id|sk_isa_read_eeprom
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Address: 0000:0000 */
id|sk_isa_sifwritew
c_func
(paren
id|dev
comma
l_int|0
comma
id|SIFADX
)paren
suffix:semicolon
id|sk_isa_sifwritew
c_func
(paren
id|dev
comma
l_int|0
comma
id|SIFADR
)paren
suffix:semicolon
multiline_comment|/* Read six byte MAC address data */
id|dev-&gt;addr_len
op_assign
l_int|6
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|sk_isa_sifreadw
c_func
(paren
id|dev
comma
id|SIFINC
)paren
op_rshift
l_int|8
suffix:semicolon
)brace
)brace
DECL|function|sk_isa_setnselout_pins
r_int
r_int
id|sk_isa_setnselout_pins
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sk_isa_open
r_static
r_int
id|sk_isa_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|tp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
r_int
id|val
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|oldval
suffix:semicolon
r_int
id|i
suffix:semicolon
id|val
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|irqlist
(braket
id|i
)braket
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|irqlist
(braket
id|i
)braket
op_eq
id|dev-&gt;irq
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|val
op_or_assign
id|CYCLE_TIME
op_lshift
l_int|2
suffix:semicolon
id|val
op_or_assign
id|i
op_lshift
l_int|4
suffix:semicolon
id|i
op_assign
id|dev-&gt;dma
op_minus
l_int|5
suffix:semicolon
id|val
op_or_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;DataRate
op_eq
id|SPEED_4
)paren
(brace
id|val
op_or_assign
id|LINE_SPEED_BIT
suffix:semicolon
)brace
r_else
id|val
op_and_assign
op_complement
id|LINE_SPEED_BIT
suffix:semicolon
id|oldval
op_assign
id|sk_isa_sifreadb
c_func
(paren
id|dev
comma
id|POSREG
)paren
suffix:semicolon
multiline_comment|/* Leave cycle bits alone */
id|oldval
op_or_assign
l_int|0xf3
suffix:semicolon
id|val
op_and_assign
id|oldval
suffix:semicolon
id|sk_isa_sifwriteb
c_func
(paren
id|dev
comma
id|val
comma
id|POSREG
)paren
suffix:semicolon
r_return
id|tms380tr_open
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|macro|ISATR_MAX_ADAPTERS
mdefine_line|#define ISATR_MAX_ADAPTERS 3
DECL|variable|io
r_static
r_int
id|io
(braket
id|ISATR_MAX_ADAPTERS
)braket
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
(braket
id|ISATR_MAX_ADAPTERS
)braket
suffix:semicolon
DECL|variable|dma
r_static
r_int
id|dma
(braket
id|ISATR_MAX_ADAPTERS
)braket
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
id|ISATR_MAX_ADAPTERS
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
id|ISATR_MAX_ADAPTERS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|dma
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|ISATR_MAX_ADAPTERS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|variable|sk_isa_dev
r_static
r_struct
id|net_device
op_star
id|sk_isa_dev
(braket
id|ISATR_MAX_ADAPTERS
)braket
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|i
comma
id|num
op_assign
l_int|0
comma
id|err
op_assign
l_int|0
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
id|ISATR_MAX_ADAPTERS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev
op_assign
id|alloc_trdev
c_func
(paren
r_sizeof
(paren
r_struct
id|net_local
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_continue
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|io
(braket
id|i
)braket
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
(braket
id|i
)braket
suffix:semicolon
id|dev-&gt;dma
op_assign
id|dma
(braket
id|i
)braket
suffix:semicolon
id|err
op_assign
id|setup_card
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|sk_isa_dev
(braket
id|i
)braket
op_assign
id|dev
suffix:semicolon
op_increment
id|num
suffix:semicolon
)brace
r_else
(brace
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;skisa.c: %d cards found.&bslash;n&quot;
comma
id|num
)paren
suffix:semicolon
multiline_comment|/* Probe for cards. */
r_if
c_cond
(paren
id|num
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;skisa.c: No cards found.&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
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
id|ISATR_MAX_ADAPTERS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|sk_isa_dev
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_continue
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|SK_ISA_IO_EXTENT
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|free_dma
c_func
(paren
id|dev-&gt;dma
)paren
suffix:semicolon
id|tmsdev_term
c_func
(paren
id|dev
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* MODULE */
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -DMODVERSIONS  -DMODULE -D__KERNEL__ -Wall -Wstrict-prototypes -O6 -fomit-frame-pointer -I/usr/src/linux/drivers/net/tokenring/ -c skisa.c&quot;&n; *  alt-compile-command: &quot;gcc -DMODULE -D__KERNEL__ -Wall -Wstrict-prototypes -O6 -fomit-frame-pointer -I/usr/src/linux/drivers/net/tokenring/ -c skisa.c&quot;&n; *  c-set-style &quot;K&amp;R&quot;&n; *  c-indent-level: 8&n; *  c-basic-offset: 8&n; *  tab-width: 8&n; * End:&n; */
eof
