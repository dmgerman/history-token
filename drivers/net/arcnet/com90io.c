multiline_comment|/*&n; * Linux ARCnet driver - COM90xx chipset (IO-mapped buffers)&n; * &n; * Written 1997 by David Woodhouse.&n; * Written 1994-1999 by Avery Pennarun.&n; * Written 1999-2000 by Martin Mares &lt;mj@ucw.cz&gt;.&n; * Derived from skeleton.c by Donald Becker.&n; *&n; * Special thanks to Contemporary Controls, Inc. (www.ccontrols.com)&n; *  for sponsoring the further development of this driver.&n; *&n; * **********************&n; *&n; * The original copyright of skeleton.c was as follows:&n; *&n; * skeleton.c Written 1993 by Donald Becker.&n; * Copyright 1993 United States Government as represented by the&n; * Director, National Security Agency.  This software may only be used&n; * and distributed according to the terms of the GNU General Public License as&n; * modified by SRC, incorporated herein by reference.&n; *&n; * **********************&n; *&n; * For more details, see drivers/net/arcnet.c&n; *&n; * **********************&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/arcdevice.h&gt;
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;arcnet: COM90xx IO-mapped mode support (by David Woodhouse et el.)&bslash;n&quot;
multiline_comment|/* Internal function declarations */
r_static
r_int
id|com90io_found
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
id|com90io_command
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|command
)paren
suffix:semicolon
r_static
r_int
id|com90io_status
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
id|com90io_setmask
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|mask
)paren
suffix:semicolon
r_static
r_int
id|com90io_reset
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|really_reset
)paren
suffix:semicolon
r_static
r_void
id|com90io_copy_to_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
comma
r_int
id|offset
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_static
r_void
id|com90io_copy_from_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
comma
r_int
id|offset
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* Handy defines for ARCnet specific stuff */
multiline_comment|/* The number of low I/O ports used by the card. */
DECL|macro|ARCNET_TOTAL_SIZE
mdefine_line|#define ARCNET_TOTAL_SIZE 16
multiline_comment|/* COM 9026 controller chip --&gt; ARCnet register addresses */
DECL|macro|_INTMASK
mdefine_line|#define _INTMASK (ioaddr+0)&t;/* writable */
DECL|macro|_STATUS
mdefine_line|#define _STATUS  (ioaddr+0)&t;/* readable */
DECL|macro|_COMMAND
mdefine_line|#define _COMMAND (ioaddr+1)&t;/* writable, returns random vals on read (?) */
DECL|macro|_RESET
mdefine_line|#define _RESET  (ioaddr+8)&t;/* software reset (on read) */
DECL|macro|_MEMDATA
mdefine_line|#define _MEMDATA  (ioaddr+12)&t;/* Data port for IO-mapped memory */
DECL|macro|_ADDR_HI
mdefine_line|#define _ADDR_HI  (ioaddr+15)&t;/* Control registers for said */
DECL|macro|_ADDR_LO
mdefine_line|#define _ADDR_LO  (ioaddr+14)
DECL|macro|_CONFIG
mdefine_line|#define _CONFIG  (ioaddr+2)&t;/* Configuration register */
DECL|macro|ASTATUS
macro_line|#undef ASTATUS
DECL|macro|ACOMMAND
macro_line|#undef ACOMMAND
DECL|macro|AINTMASK
macro_line|#undef AINTMASK
DECL|macro|ASTATUS
mdefine_line|#define ASTATUS()&t;inb(_STATUS)
DECL|macro|ACOMMAND
mdefine_line|#define ACOMMAND(cmd) outb((cmd),_COMMAND)
DECL|macro|AINTMASK
mdefine_line|#define AINTMASK(msk)&t;outb((msk),_INTMASK)
DECL|macro|SETCONF
mdefine_line|#define SETCONF() &t;outb((lp-&gt;config),_CONFIG)
multiline_comment|/****************************************************************************&n; *                                                                          *&n; * IO-mapped operation routines                                             *&n; *                                                                          *&n; ****************************************************************************/
DECL|macro|ONE_AT_A_TIME_TX
macro_line|#undef ONE_AT_A_TIME_TX
DECL|macro|ONE_AT_A_TIME_RX
macro_line|#undef ONE_AT_A_TIME_RX
DECL|function|get_buffer_byte
r_static
id|u_char
id|get_buffer_byte
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|offset
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|outb
c_func
(paren
id|offset
op_rshift
l_int|8
comma
id|_ADDR_HI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|offset
op_amp
l_int|0xff
comma
id|_ADDR_LO
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|_MEMDATA
)paren
suffix:semicolon
)brace
macro_line|#ifdef ONE_AT_A_TIME_TX
DECL|function|put_buffer_byte
r_static
r_void
id|put_buffer_byte
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|offset
comma
id|u_char
id|datum
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|outb
c_func
(paren
id|offset
op_rshift
l_int|8
comma
id|_ADDR_HI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|offset
op_amp
l_int|0xff
comma
id|_ADDR_LO
)paren
suffix:semicolon
id|outb
c_func
(paren
id|datum
comma
id|_MEMDATA
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|get_whole_buffer
r_static
r_void
id|get_whole_buffer
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|offset
comma
r_int
id|length
comma
r_char
op_star
id|dest
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|outb
c_func
(paren
(paren
id|offset
op_rshift
l_int|8
)paren
op_or
id|AUTOINCflag
comma
id|_ADDR_HI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|offset
op_amp
l_int|0xff
comma
id|_ADDR_LO
)paren
suffix:semicolon
r_while
c_loop
(paren
id|length
op_decrement
)paren
macro_line|#ifdef ONE_AT_A_TIME_RX
op_star
(paren
id|dest
op_increment
)paren
op_assign
id|get_buffer_byte
c_func
(paren
id|dev
comma
id|offset
op_increment
)paren
suffix:semicolon
macro_line|#else
op_star
(paren
id|dest
op_increment
)paren
op_assign
id|inb
c_func
(paren
id|_MEMDATA
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|put_whole_buffer
r_static
r_void
id|put_whole_buffer
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|offset
comma
r_int
id|length
comma
r_char
op_star
id|dest
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|outb
c_func
(paren
(paren
id|offset
op_rshift
l_int|8
)paren
op_or
id|AUTOINCflag
comma
id|_ADDR_HI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|offset
op_amp
l_int|0xff
comma
id|_ADDR_LO
)paren
suffix:semicolon
r_while
c_loop
(paren
id|length
op_decrement
)paren
macro_line|#ifdef ONE_AT_A_TIME_TX
id|put_buffer_byte
c_func
(paren
id|dev
comma
id|offset
op_increment
comma
op_star
(paren
id|dest
op_increment
)paren
)paren
suffix:semicolon
macro_line|#else
id|outb
c_func
(paren
op_star
(paren
id|dest
op_increment
)paren
comma
id|_MEMDATA
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * We cannot probe for an IO mapped card either, although we can check that&n; * it&squot;s where we were told it was, and even autoirq&n; */
DECL|function|com90io_probe
r_static
r_int
id|__init
id|com90io_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
comma
id|status
suffix:semicolon
r_int
r_int
id|airqmask
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_NORMAL
)paren
id|printk
c_func
(paren
id|VERSION
)paren
suffix:semicolon
id|BUGLVL
c_func
(paren
id|D_NORMAL
)paren
id|printk
c_func
(paren
l_string|&quot;E-mail me if you actually test this driver, please!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ioaddr
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;No autoprobe for IO mapped cards; you &quot;
l_string|&quot;must specify the base address!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|ioaddr
comma
id|ARCNET_TOTAL_SIZE
)paren
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;IO check_region %x-%x failed.&bslash;n&quot;
comma
id|ioaddr
comma
id|ioaddr
op_plus
id|ARCNET_TOTAL_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ASTATUS
c_func
(paren
)paren
op_eq
l_int|0xFF
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;IO address %x empty&bslash;n&quot;
comma
id|ioaddr
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|inb
c_func
(paren
id|_RESET
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|RESETtime
)paren
suffix:semicolon
id|status
op_assign
id|ASTATUS
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0x9D
)paren
op_ne
(paren
id|NORXflag
op_or
id|RECONflag
op_or
id|TXFREEflag
op_or
id|RESETflag
)paren
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;Status invalid (%Xh).&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|BUGMSG
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;Status after reset: %X&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|ACOMMAND
c_func
(paren
id|CFLAGScmd
op_or
id|RESETclear
op_or
id|CONFIGclear
)paren
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;Status after reset acknowledged: %X&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|status
op_assign
id|ASTATUS
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|RESETflag
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;Eternal reset (status=%Xh)&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|outb
c_func
(paren
(paren
l_int|0x16
op_or
id|IOMAPflag
)paren
op_amp
op_complement
id|ENABLE16flag
comma
id|_CONFIG
)paren
suffix:semicolon
multiline_comment|/* Read first loc&squot;n of memory */
id|outb
c_func
(paren
id|AUTOINCflag
comma
id|_ADDR_HI
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|_ADDR_LO
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|inb
c_func
(paren
id|_MEMDATA
)paren
)paren
op_ne
l_int|0xd1
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;Signature byte not found&quot;
l_string|&quot; (%Xh instead).&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;irq
)paren
(brace
multiline_comment|/*&n;&t;&t; * if we do this, we&squot;re sure to get an IRQ since the&n;&t;&t; * card has just reset and the NORXflag is on until&n;&t;&t; * we tell it to start receiving.&n;&t;&t; */
id|airqmask
op_assign
id|probe_irq_on
c_func
(paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|NORXflag
comma
id|_INTMASK
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|_INTMASK
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|probe_irq_off
c_func
(paren
id|airqmask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_le
l_int|0
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;Autoprobe IRQ failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_return
id|com90io_found
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/* Set up the struct net_device associated with this card.  Called after&n; * probing succeeds.&n; */
DECL|function|com90io_found
r_static
r_int
id|__init
id|com90io_found
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|arcnet_local
op_star
id|lp
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
multiline_comment|/* Reserve the irq */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
op_amp
id|arcnet_interrupt
comma
l_int|0
comma
l_string|&quot;arcnet (COM90xx-IO)&quot;
comma
id|dev
)paren
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Can&squot;t get IRQ %d!&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Reserve the I/O region - guaranteed to work by check_region */
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|ARCNET_TOTAL_SIZE
comma
l_string|&quot;arcnet (COM90xx-IO)&quot;
)paren
)paren
(brace
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* Initialize the rest of the device structure. */
id|dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|arcnet_local
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;priv
)paren
(brace
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|ARCNET_TOTAL_SIZE
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
id|dev-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|arcnet_local
)paren
)paren
suffix:semicolon
id|lp
op_assign
(paren
r_struct
id|arcnet_local
op_star
)paren
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
id|lp-&gt;card_name
op_assign
l_string|&quot;COM90xx I/O&quot;
suffix:semicolon
id|lp-&gt;hw.command
op_assign
id|com90io_command
suffix:semicolon
id|lp-&gt;hw.status
op_assign
id|com90io_status
suffix:semicolon
id|lp-&gt;hw.intmask
op_assign
id|com90io_setmask
suffix:semicolon
id|lp-&gt;hw.reset
op_assign
id|com90io_reset
suffix:semicolon
id|lp-&gt;hw.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|lp-&gt;hw.copy_to_card
op_assign
id|com90io_copy_to_card
suffix:semicolon
id|lp-&gt;hw.copy_from_card
op_assign
id|com90io_copy_from_card
suffix:semicolon
multiline_comment|/*&n;&t; * Fill in the fields of the device structure with generic&n;&t; * values.&n;&t; */
id|arcdev_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|lp-&gt;config
op_assign
(paren
l_int|0x16
op_or
id|IOMAPflag
)paren
op_amp
op_complement
id|ENABLE16flag
suffix:semicolon
id|SETCONF
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* get and check the station ID from offset 1 in shmem */
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
op_assign
id|get_buffer_byte
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;COM90IO: station %02Xh found at %03lXh, IRQ %d.&bslash;n&quot;
comma
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
comma
id|dev-&gt;base_addr
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Do a hardware reset on the card, and set up necessary registers.&n; *&n; * This should be called as little as possible, because it disrupts the&n; * token on the network (causes a RECON) and requires a significant delay.&n; *&n; * However, it does make sure the card is in a defined state.&n; */
DECL|function|com90io_reset
r_static
r_int
id|com90io_reset
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|really_reset
)paren
(brace
r_struct
id|arcnet_local
op_star
id|lp
op_assign
(paren
r_struct
id|arcnet_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_INIT
comma
l_string|&quot;Resetting %s (status=%02Xh)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ASTATUS
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|really_reset
)paren
(brace
multiline_comment|/* reset the card */
id|inb
c_func
(paren
id|_RESET
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|RESETtime
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the thing to IO-mapped, 8-bit  mode */
id|lp-&gt;config
op_assign
(paren
l_int|0x1C
op_or
id|IOMAPflag
)paren
op_amp
op_complement
id|ENABLE16flag
suffix:semicolon
id|SETCONF
c_func
(paren
)paren
suffix:semicolon
id|ACOMMAND
c_func
(paren
id|CFLAGScmd
op_or
id|RESETclear
)paren
suffix:semicolon
multiline_comment|/* clear flags &amp; end reset */
id|ACOMMAND
c_func
(paren
id|CFLAGScmd
op_or
id|CONFIGclear
)paren
suffix:semicolon
multiline_comment|/* verify that the ARCnet signature byte is present */
r_if
c_cond
(paren
id|get_buffer_byte
c_func
(paren
id|dev
comma
l_int|0
)paren
op_ne
id|TESTvalue
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;reset failed: TESTvalue not present.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* enable extended (512-byte) packets */
id|ACOMMAND
c_func
(paren
id|CONFIGcmd
op_or
id|EXTconf
)paren
suffix:semicolon
multiline_comment|/* done!  return success. */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|com90io_command
r_static
r_void
id|com90io_command
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|cmd
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|ACOMMAND
c_func
(paren
id|cmd
)paren
suffix:semicolon
)brace
DECL|function|com90io_status
r_static
r_int
id|com90io_status
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_return
id|ASTATUS
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|com90io_setmask
r_static
r_void
id|com90io_setmask
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|mask
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|AINTMASK
c_func
(paren
id|mask
)paren
suffix:semicolon
)brace
DECL|function|com90io_copy_to_card
r_static
r_void
id|com90io_copy_to_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
comma
r_int
id|offset
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
(brace
id|TIME
c_func
(paren
l_string|&quot;put_whole_buffer&quot;
comma
id|count
comma
id|put_whole_buffer
c_func
(paren
id|dev
comma
id|bufnum
op_star
l_int|512
op_plus
id|offset
comma
id|count
comma
id|buf
)paren
)paren
suffix:semicolon
)brace
DECL|function|com90io_copy_from_card
r_static
r_void
id|com90io_copy_from_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|bufnum
comma
r_int
id|offset
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
(brace
id|TIME
c_func
(paren
l_string|&quot;get_whole_buffer&quot;
comma
id|count
comma
id|get_whole_buffer
c_func
(paren
id|dev
comma
id|bufnum
op_star
l_int|512
op_plus
id|offset
comma
id|count
comma
id|buf
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|variable|my_dev
r_static
r_struct
id|net_device
op_star
id|my_dev
suffix:semicolon
multiline_comment|/* Module parameters */
DECL|variable|io
r_static
r_int
id|io
suffix:semicolon
multiline_comment|/* use the insmod io= irq= shmem= options */
DECL|variable|irq
r_static
r_int
id|irq
suffix:semicolon
DECL|variable|device
r_static
r_char
op_star
id|device
suffix:semicolon
multiline_comment|/* use eg. device=arc1 to change name */
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|device
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
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
id|err
suffix:semicolon
id|dev
op_assign
id|dev_alloc
c_func
(paren
id|device
ques
c_cond
suffix:colon
l_string|&quot;arc%d&quot;
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
id|err
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|io
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|2
)paren
id|dev-&gt;irq
op_assign
l_int|9
suffix:semicolon
r_if
c_cond
(paren
id|com90io_probe
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|my_dev
op_assign
id|dev
suffix:semicolon
r_return
l_int|0
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
r_struct
id|net_device
op_star
id|dev
op_assign
id|my_dev
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Set the thing back to MMAP mode, in case the old driver is loaded later */
id|outb
c_func
(paren
(paren
id|inb
c_func
(paren
id|_CONFIG
)paren
op_amp
op_complement
id|IOMAPflag
)paren
comma
id|_CONFIG
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
id|release_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|ARCNET_TOTAL_SIZE
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|com90io_setup
r_static
r_int
id|__init
id|com90io_setup
c_func
(paren
r_char
op_star
id|s
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|ints
(braket
l_int|4
)braket
suffix:semicolon
id|s
op_assign
id|get_options
c_func
(paren
id|s
comma
l_int|4
comma
id|ints
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ints
(braket
l_int|0
)braket
)paren
r_return
l_int|0
suffix:semicolon
id|dev
op_assign
id|alloc_bootmem
c_func
(paren
r_sizeof
(paren
r_struct
id|net_device
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|net_device
)paren
)paren
suffix:semicolon
id|dev-&gt;init
op_assign
id|com90io_probe
suffix:semicolon
r_switch
c_cond
(paren
id|ints
(braket
l_int|0
)braket
)paren
(brace
r_default
suffix:colon
multiline_comment|/* ERROR */
id|printk
c_func
(paren
l_string|&quot;com90io: Too many arguments.&bslash;n&quot;
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* IRQ */
id|dev-&gt;irq
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* IO address */
id|dev-&gt;base_addr
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|s
)paren
id|strncpy
c_func
(paren
id|dev-&gt;name
comma
id|s
comma
l_int|9
)paren
suffix:semicolon
r_else
id|strcpy
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;arc%d&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
id|dev
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;com90io: Cannot register arcnet device&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;com90io=&quot;
comma
id|com90io_setup
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* MODULE */
eof
