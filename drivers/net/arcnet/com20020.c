multiline_comment|/*&n; * Linux ARCnet driver - COM20020 chipset support&n; * &n; * Written 1997 by David Woodhouse.&n; * Written 1994-1999 by Avery Pennarun.&n; * Written 1999 by Martin Mares &lt;mj@ucw.cz&gt;.&n; * Derived from skeleton.c by Donald Becker.&n; *&n; * Special thanks to Contemporary Controls, Inc. (www.ccontrols.com)&n; *  for sponsoring the further development of this driver.&n; *&n; * **********************&n; *&n; * The original copyright of skeleton.c was as follows:&n; *&n; * skeleton.c Written 1993 by Donald Becker.&n; * Copyright 1993 United States Government as represented by the&n; * Director, National Security Agency.  This software may only be used&n; * and distributed according to the terms of the GNU General Public License as&n; * modified by SRC, incorporated herein by reference.&n; *&n; * **********************&n; *&n; * For more details, see drivers/net/arcnet.c&n; *&n; * **********************&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/arcdevice.h&gt;
macro_line|#include &lt;linux/com20020.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;arcnet: COM20020 chipset support (by David Woodhouse et al.)&bslash;n&quot;
DECL|variable|clockrates
r_static
r_char
op_star
id|clockrates
(braket
)braket
op_assign
(brace
l_string|&quot;10 Mb/s&quot;
comma
l_string|&quot;Reserved&quot;
comma
l_string|&quot;5 Mb/s&quot;
comma
l_string|&quot;2.5 Mb/s&quot;
comma
l_string|&quot;1.25Mb/s&quot;
comma
l_string|&quot;625 Kb/s&quot;
comma
l_string|&quot;312.5 Kb/s&quot;
comma
l_string|&quot;156.25 Kb/s&quot;
comma
l_string|&quot;Reserved&quot;
comma
l_string|&quot;Reserved&quot;
comma
l_string|&quot;Reserved&quot;
)brace
suffix:semicolon
r_static
r_void
id|com20020_command
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
id|com20020_status
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
id|com20020_setmask
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
id|com20020_reset
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
id|com20020_copy_to_card
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
id|com20020_copy_from_card
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
id|com20020_set_mc_list
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
id|com20020_close
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
DECL|function|com20020_copy_from_card
r_static
r_void
id|com20020_copy_from_card
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
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
comma
id|ofs
op_assign
l_int|512
op_star
id|bufnum
op_plus
id|offset
suffix:semicolon
multiline_comment|/* set up the address register */
id|outb
c_func
(paren
(paren
id|ofs
op_rshift
l_int|8
)paren
op_or
id|RDDATAflag
op_or
id|AUTOINCflag
comma
id|_ADDR_HI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ofs
op_amp
l_int|0xff
comma
id|_ADDR_LO
)paren
suffix:semicolon
multiline_comment|/* copy the data */
id|TIME
c_func
(paren
l_string|&quot;insb&quot;
comma
id|count
comma
id|insb
c_func
(paren
id|_MEMDATA
comma
id|buf
comma
id|count
)paren
)paren
suffix:semicolon
)brace
DECL|function|com20020_copy_to_card
r_static
r_void
id|com20020_copy_to_card
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
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
comma
id|ofs
op_assign
l_int|512
op_star
id|bufnum
op_plus
id|offset
suffix:semicolon
multiline_comment|/* set up the address register */
id|outb
c_func
(paren
(paren
id|ofs
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
id|ofs
op_amp
l_int|0xff
comma
id|_ADDR_LO
)paren
suffix:semicolon
multiline_comment|/* copy the data */
id|TIME
c_func
(paren
l_string|&quot;outsb&quot;
comma
id|count
comma
id|outsb
c_func
(paren
id|_MEMDATA
comma
id|buf
comma
id|count
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Reset the card and check some basic stuff during the detection stage. */
DECL|function|com20020_check
r_int
id|com20020_check
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
r_struct
id|arcnet_local
op_star
id|lp
op_assign
id|dev-&gt;priv
suffix:semicolon
id|ARCRESET0
suffix:semicolon
id|mdelay
c_func
(paren
id|RESETtime
)paren
suffix:semicolon
id|lp-&gt;setup
op_assign
id|lp-&gt;clockm
ques
c_cond
l_int|0
suffix:colon
(paren
id|lp-&gt;clockp
op_lshift
l_int|1
)paren
suffix:semicolon
id|lp-&gt;setup2
op_assign
(paren
id|lp-&gt;clockm
op_lshift
l_int|4
)paren
op_or
l_int|8
suffix:semicolon
multiline_comment|/* CHECK: should we do this for SOHARD cards ? */
multiline_comment|/* Enable P1Mode for backplane mode */
id|lp-&gt;setup
op_assign
id|lp-&gt;setup
op_or
id|P1MODE
suffix:semicolon
id|SET_SUBADR
c_func
(paren
id|SUB_SETUP1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|lp-&gt;setup
comma
id|_XREG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;card_flags
op_amp
id|ARC_CAN_10MBIT
)paren
(brace
id|SET_SUBADR
c_func
(paren
id|SUB_SETUP2
)paren
suffix:semicolon
id|outb
c_func
(paren
id|lp-&gt;setup2
comma
id|_XREG
)paren
suffix:semicolon
multiline_comment|/* must now write the magic &quot;restart operation&quot; command */
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x18
comma
id|_COMMAND
)paren
suffix:semicolon
)brace
id|lp-&gt;config
op_assign
l_int|0x21
op_or
(paren
id|lp-&gt;timeout
op_lshift
l_int|3
)paren
op_or
(paren
id|lp-&gt;backplane
op_lshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* set node ID to 0x42 (but transmitter is disabled, so it&squot;s okay) */
id|SETCONF
suffix:semicolon
id|outb
c_func
(paren
l_int|0x42
comma
id|ioaddr
op_plus
id|BUS_ALIGN
op_star
l_int|7
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
l_int|0x99
)paren
op_ne
(paren
id|NORXflag
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
id|D_NORMAL
comma
l_string|&quot;status invalid (%Xh).&bslash;n&quot;
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
l_string|&quot;status after reset: %X&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
multiline_comment|/* Enable TX */
id|outb
c_func
(paren
l_int|0x39
comma
id|_CONFIG
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|BUS_ALIGN
op_star
l_int|8
)paren
comma
id|ioaddr
op_plus
id|BUS_ALIGN
op_star
l_int|7
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
id|status
op_assign
id|ASTATUS
c_func
(paren
)paren
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_INIT_REASONS
comma
l_string|&quot;status after reset acknowledged: %X&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
multiline_comment|/* Read first location of memory */
id|outb
c_func
(paren
l_int|0
op_or
id|RDDATAflag
op_or
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
id|TESTvalue
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Signature byte not found (%02Xh != D1h).&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Set up the struct net_device associated with this card.  Called after&n; * probing succeeds.&n; */
DECL|function|com20020_found
r_int
id|com20020_found
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|shared
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
multiline_comment|/* Initialize the rest of the device structure. */
id|lp
op_assign
id|dev-&gt;priv
suffix:semicolon
id|lp-&gt;hw.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|lp-&gt;hw.command
op_assign
id|com20020_command
suffix:semicolon
id|lp-&gt;hw.status
op_assign
id|com20020_status
suffix:semicolon
id|lp-&gt;hw.intmask
op_assign
id|com20020_setmask
suffix:semicolon
id|lp-&gt;hw.reset
op_assign
id|com20020_reset
suffix:semicolon
id|lp-&gt;hw.copy_to_card
op_assign
id|com20020_copy_to_card
suffix:semicolon
id|lp-&gt;hw.copy_from_card
op_assign
id|com20020_copy_from_card
suffix:semicolon
id|lp-&gt;hw.close
op_assign
id|com20020_close
suffix:semicolon
id|dev-&gt;set_multicast_list
op_assign
id|com20020_set_mc_list
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
)paren
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|BUS_ALIGN
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* FIXME: do this some other way! */
id|SET_SUBADR
c_func
(paren
id|SUB_SETUP1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|lp-&gt;setup
comma
id|_XREG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;card_flags
op_amp
id|ARC_CAN_10MBIT
)paren
(brace
id|SET_SUBADR
c_func
(paren
id|SUB_SETUP2
)paren
suffix:semicolon
id|outb
c_func
(paren
id|lp-&gt;setup2
comma
id|_XREG
)paren
suffix:semicolon
multiline_comment|/* must now write the magic &quot;restart operation&quot; command */
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x18
comma
id|_COMMAND
)paren
suffix:semicolon
)brace
id|lp-&gt;config
op_assign
l_int|0x20
op_or
(paren
id|lp-&gt;timeout
op_lshift
l_int|3
)paren
op_or
(paren
id|lp-&gt;backplane
op_lshift
l_int|2
)paren
op_or
l_int|1
suffix:semicolon
multiline_comment|/* Default 0x38 + register: Node ID */
id|SETCONF
suffix:semicolon
id|outb
c_func
(paren
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
comma
id|_XREG
)paren
suffix:semicolon
multiline_comment|/* reserve the irq */
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
id|shared
comma
l_string|&quot;arcnet (COM20020)&quot;
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
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;%s: station %02Xh found at %03lXh, IRQ %d.&bslash;n&quot;
comma
id|lp-&gt;card_name
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
r_if
c_cond
(paren
id|lp-&gt;backplane
)paren
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Using backplane mode.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;timeout
op_ne
l_int|3
)paren
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Using extended timeout value of %d.&bslash;n&quot;
comma
id|lp-&gt;timeout
)paren
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Using CKP %d - data rate %s.&bslash;n&quot;
comma
id|lp-&gt;setup
op_rshift
l_int|1
comma
id|clockrates
(braket
l_int|3
op_minus
(paren
(paren
id|lp-&gt;setup2
op_amp
l_int|0xF0
)paren
op_rshift
l_int|4
)paren
op_plus
(paren
(paren
id|lp-&gt;setup
op_amp
l_int|0x0F
)paren
op_rshift
l_int|1
)paren
)braket
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
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * Do a hardware reset on the card, and set up necessary registers.&n; * &n; * This should be called as little as possible, because it disrupts the&n; * token on the network (causes a RECON) and requires a significant delay.&n; *&n; * However, it does make sure the card is in a defined state.&n; */
DECL|function|com20020_reset
r_static
r_int
id|com20020_reset
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
id|dev-&gt;priv
suffix:semicolon
id|u_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|u_char
id|inbyte
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_DEBUG
comma
l_string|&quot;%s: %d: %s: dev: %p, lp: %p, dev-&gt;name: %s&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|__FUNCTION__
comma
id|dev
comma
id|lp
comma
id|dev-&gt;name
)paren
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
id|BUGMSG
c_func
(paren
id|D_DEBUG
comma
l_string|&quot;%s: %d: %s&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|lp-&gt;config
op_assign
id|TXENcfg
op_or
(paren
id|lp-&gt;timeout
op_lshift
l_int|3
)paren
op_or
(paren
id|lp-&gt;backplane
op_lshift
l_int|2
)paren
suffix:semicolon
multiline_comment|/* power-up defaults */
id|SETCONF
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_DEBUG
comma
l_string|&quot;%s: %d: %s&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|really_reset
)paren
(brace
multiline_comment|/* reset the card */
id|ARCRESET
suffix:semicolon
id|mdelay
c_func
(paren
id|RESETtime
op_star
l_int|2
)paren
suffix:semicolon
multiline_comment|/* COM20020 seems to be slower sometimes */
)brace
multiline_comment|/* clear flags &amp; end reset */
id|BUGMSG
c_func
(paren
id|D_DEBUG
comma
l_string|&quot;%s: %d: %s&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|__FUNCTION__
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
multiline_comment|/* verify that the ARCnet signature byte is present */
id|BUGMSG
c_func
(paren
id|D_DEBUG
comma
l_string|&quot;%s: %d: %s&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|com20020_copy_from_card
c_func
(paren
id|dev
comma
l_int|0
comma
l_int|0
comma
op_amp
id|inbyte
comma
l_int|1
)paren
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_DEBUG
comma
l_string|&quot;%s: %d: %s&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inbyte
op_ne
id|TESTvalue
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_DEBUG
comma
l_string|&quot;%s: %d: %s&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|__FUNCTION__
)paren
suffix:semicolon
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
id|BUGMSG
c_func
(paren
id|D_DEBUG
comma
l_string|&quot;%s: %d: %s&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|__FUNCTION__
)paren
suffix:semicolon
multiline_comment|/* done!  return success. */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|com20020_setmask
r_static
r_void
id|com20020_setmask
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
id|u_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|BUGMSG
c_func
(paren
id|D_DURING
comma
l_string|&quot;Setting mask to %x at %x&bslash;n&quot;
comma
id|mask
comma
id|ioaddr
)paren
suffix:semicolon
id|AINTMASK
c_func
(paren
id|mask
)paren
suffix:semicolon
)brace
DECL|function|com20020_command
r_static
r_void
id|com20020_command
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
id|u_int
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
DECL|function|com20020_status
r_static
r_int
id|com20020_status
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|u_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_return
id|ASTATUS
c_func
(paren
)paren
op_plus
(paren
id|ADIAGSTATUS
c_func
(paren
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|com20020_close
r_static
r_void
id|com20020_close
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
op_assign
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
multiline_comment|/* disable transmitter */
id|lp-&gt;config
op_and_assign
op_complement
id|TXENcfg
suffix:semicolon
id|SETCONF
suffix:semicolon
)brace
multiline_comment|/* Set or clear the multicast filter for this adaptor.&n; * num_addrs == -1    Promiscuous mode, receive all packets&n; * num_addrs == 0       Normal mode, clear multicast list&n; * num_addrs &gt; 0        Multicast mode, receive normal and MC packets, and do&n; *                      best-effort filtering.&n; *      FIXME - do multicast stuff, not just promiscuous.&n; */
DECL|function|com20020_set_mc_list
r_static
r_void
id|com20020_set_mc_list
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
op_assign
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;flags
op_amp
id|IFF_PROMISC
)paren
op_logical_and
(paren
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
)paren
(brace
multiline_comment|/* Enable promiscuous mode */
r_if
c_cond
(paren
op_logical_neg
(paren
id|lp-&gt;setup
op_amp
id|PROMISCset
)paren
)paren
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Setting promiscuous flag...&bslash;n&quot;
)paren
suffix:semicolon
id|SET_SUBADR
c_func
(paren
id|SUB_SETUP1
)paren
suffix:semicolon
id|lp-&gt;setup
op_or_assign
id|PROMISCset
suffix:semicolon
id|outb
c_func
(paren
id|lp-&gt;setup
comma
id|_XREG
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* Disable promiscuous mode, use normal mode */
(brace
r_if
c_cond
(paren
(paren
id|lp-&gt;setup
op_amp
id|PROMISCset
)paren
)paren
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Resetting promiscuous flag...&bslash;n&quot;
)paren
suffix:semicolon
id|SET_SUBADR
c_func
(paren
id|SUB_SETUP1
)paren
suffix:semicolon
id|lp-&gt;setup
op_and_assign
op_complement
id|PROMISCset
suffix:semicolon
id|outb
c_func
(paren
id|lp-&gt;setup
comma
id|_XREG
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef MODULE
DECL|variable|com20020_check
id|EXPORT_SYMBOL
c_func
(paren
id|com20020_check
)paren
suffix:semicolon
DECL|variable|com20020_found
id|EXPORT_SYMBOL
c_func
(paren
id|com20020_found
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
)brace
macro_line|#endif&t;&t;&t;&t;/* MODULE */
eof
