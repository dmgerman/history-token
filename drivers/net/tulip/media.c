multiline_comment|/*&n;&t;drivers/net/tulip/media.c&n;&n;&t;Maintained by Jeff Garzik &lt;jgarzik@pobox.com&gt;&n;&t;Copyright 2000,2001  The Linux Kernel Team&n;&t;Written/copyright 1994-2001 by Donald Becker.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU General Public License, incorporated herein by reference.&n;&n;&t;Please refer to Documentation/DocBook/tulip-user.{pdf,ps,html}&n;&t;for more information on this driver, or visit the project&n;&t;Web page at http://sourceforge.net/projects/tulip/&n;&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mii.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;tulip.h&quot;
multiline_comment|/* The maximum data clock rate is 2.5 Mhz.  The minimum timing is usually&n;   met by back-to-back PCI I/O cycles, but we insert a delay to avoid&n;   &quot;overclocking&quot; issues or future 66Mhz PCI. */
DECL|macro|mdio_delay
mdefine_line|#define mdio_delay() ioread32(mdio_addr)
multiline_comment|/* Read and write the MII registers using software-generated serial&n;   MDIO protocol.  It is just different enough from the EEPROM protocol&n;   to not share code.  The maxium data clock rate is 2.5 Mhz. */
DECL|macro|MDIO_SHIFT_CLK
mdefine_line|#define MDIO_SHIFT_CLK&t;&t;0x10000
DECL|macro|MDIO_DATA_WRITE0
mdefine_line|#define MDIO_DATA_WRITE0&t;0x00000
DECL|macro|MDIO_DATA_WRITE1
mdefine_line|#define MDIO_DATA_WRITE1&t;0x20000
DECL|macro|MDIO_ENB
mdefine_line|#define MDIO_ENB&t;&t;0x00000 /* Ignore the 0x02000 databook setting. */
DECL|macro|MDIO_ENB_IN
mdefine_line|#define MDIO_ENB_IN&t;&t;0x40000
DECL|macro|MDIO_DATA_READ
mdefine_line|#define MDIO_DATA_READ&t;&t;0x80000
DECL|variable|comet_miireg2offset
r_static
r_const
r_int
r_char
id|comet_miireg2offset
(braket
l_int|32
)braket
op_assign
(brace
l_int|0xB4
comma
l_int|0xB8
comma
l_int|0xBC
comma
l_int|0xC0
comma
l_int|0xC4
comma
l_int|0xC8
comma
l_int|0xCC
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0xD0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0xD4
comma
l_int|0xD8
comma
l_int|0xDC
comma
)brace
suffix:semicolon
multiline_comment|/* MII transceiver control section.&n;   Read and write the MII registers using software-generated serial&n;   MDIO protocol.  See the MII specifications or DP83840A data sheet&n;   for details. */
DECL|function|tulip_mdio_read
r_int
id|tulip_mdio_read
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|phy_id
comma
r_int
id|location
)paren
(brace
r_struct
id|tulip_private
op_star
id|tp
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|read_cmd
op_assign
(paren
l_int|0xf6
op_lshift
l_int|10
)paren
op_or
(paren
(paren
id|phy_id
op_amp
l_int|0x1f
)paren
op_lshift
l_int|5
)paren
op_or
id|location
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_void
id|__iomem
op_star
id|ioaddr
op_assign
id|tp-&gt;base_addr
suffix:semicolon
r_void
id|__iomem
op_star
id|mdio_addr
op_assign
id|ioaddr
op_plus
id|CSR9
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|location
op_amp
op_complement
l_int|0x1f
)paren
r_return
l_int|0xffff
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;chip_id
op_eq
id|COMET
op_logical_and
id|phy_id
op_eq
l_int|30
)paren
(brace
r_if
c_cond
(paren
id|comet_miireg2offset
(braket
id|location
)braket
)paren
r_return
id|ioread32
c_func
(paren
id|ioaddr
op_plus
id|comet_miireg2offset
(braket
id|location
)braket
)paren
suffix:semicolon
r_return
l_int|0xffff
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|tp-&gt;mii_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;chip_id
op_eq
id|LC82C168
)paren
(brace
r_int
id|i
op_assign
l_int|1000
suffix:semicolon
id|iowrite32
c_func
(paren
l_int|0x60020000
op_plus
(paren
id|phy_id
op_lshift
l_int|23
)paren
op_plus
(paren
id|location
op_lshift
l_int|18
)paren
comma
id|ioaddr
op_plus
l_int|0xA0
)paren
suffix:semicolon
id|ioread32
c_func
(paren
id|ioaddr
op_plus
l_int|0xA0
)paren
suffix:semicolon
id|ioread32
c_func
(paren
id|ioaddr
op_plus
l_int|0xA0
)paren
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|i
OG
l_int|0
)paren
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|retval
op_assign
id|ioread32
c_func
(paren
id|ioaddr
op_plus
l_int|0xA0
)paren
)paren
op_amp
l_int|0x80000000
)paren
)paren
r_break
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tp-&gt;mii_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|retval
op_amp
l_int|0xffff
suffix:semicolon
)brace
multiline_comment|/* Establish sync by sending at least 32 logic ones. */
r_for
c_loop
(paren
id|i
op_assign
l_int|32
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|iowrite32
c_func
(paren
id|MDIO_ENB
op_or
id|MDIO_DATA_WRITE1
comma
id|mdio_addr
)paren
suffix:semicolon
id|mdio_delay
c_func
(paren
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|MDIO_ENB
op_or
id|MDIO_DATA_WRITE1
op_or
id|MDIO_SHIFT_CLK
comma
id|mdio_addr
)paren
suffix:semicolon
id|mdio_delay
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Shift the read command bits out. */
r_for
c_loop
(paren
id|i
op_assign
l_int|15
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_int
id|dataval
op_assign
(paren
id|read_cmd
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
ques
c_cond
id|MDIO_DATA_WRITE1
suffix:colon
l_int|0
suffix:semicolon
id|iowrite32
c_func
(paren
id|MDIO_ENB
op_or
id|dataval
comma
id|mdio_addr
)paren
suffix:semicolon
id|mdio_delay
c_func
(paren
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|MDIO_ENB
op_or
id|dataval
op_or
id|MDIO_SHIFT_CLK
comma
id|mdio_addr
)paren
suffix:semicolon
id|mdio_delay
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Read the two transition, 16 data, and wire-idle bits. */
r_for
c_loop
(paren
id|i
op_assign
l_int|19
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|iowrite32
c_func
(paren
id|MDIO_ENB_IN
comma
id|mdio_addr
)paren
suffix:semicolon
id|mdio_delay
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
(paren
id|retval
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|ioread32
c_func
(paren
id|mdio_addr
)paren
op_amp
id|MDIO_DATA_READ
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|MDIO_ENB_IN
op_or
id|MDIO_SHIFT_CLK
comma
id|mdio_addr
)paren
suffix:semicolon
id|mdio_delay
c_func
(paren
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tp-&gt;mii_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
id|retval
op_rshift
l_int|1
)paren
op_amp
l_int|0xffff
suffix:semicolon
)brace
DECL|function|tulip_mdio_write
r_void
id|tulip_mdio_write
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|phy_id
comma
r_int
id|location
comma
r_int
id|val
)paren
(brace
r_struct
id|tulip_private
op_star
id|tp
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|cmd
op_assign
(paren
l_int|0x5002
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|phy_id
op_amp
l_int|0x1f
)paren
op_lshift
l_int|23
)paren
op_or
(paren
id|location
op_lshift
l_int|18
)paren
op_or
(paren
id|val
op_amp
l_int|0xffff
)paren
suffix:semicolon
r_void
id|__iomem
op_star
id|ioaddr
op_assign
id|tp-&gt;base_addr
suffix:semicolon
r_void
id|__iomem
op_star
id|mdio_addr
op_assign
id|ioaddr
op_plus
id|CSR9
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|location
op_amp
op_complement
l_int|0x1f
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;chip_id
op_eq
id|COMET
op_logical_and
id|phy_id
op_eq
l_int|30
)paren
(brace
r_if
c_cond
(paren
id|comet_miireg2offset
(braket
id|location
)braket
)paren
id|iowrite32
c_func
(paren
id|val
comma
id|ioaddr
op_plus
id|comet_miireg2offset
(braket
id|location
)braket
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|tp-&gt;mii_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;chip_id
op_eq
id|LC82C168
)paren
(brace
r_int
id|i
op_assign
l_int|1000
suffix:semicolon
id|iowrite32
c_func
(paren
id|cmd
comma
id|ioaddr
op_plus
l_int|0xA0
)paren
suffix:semicolon
r_do
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ioread32
c_func
(paren
id|ioaddr
op_plus
l_int|0xA0
)paren
op_amp
l_int|0x80000000
)paren
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
OG
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tp-&gt;mii_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Establish sync by sending 32 logic ones. */
r_for
c_loop
(paren
id|i
op_assign
l_int|32
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|iowrite32
c_func
(paren
id|MDIO_ENB
op_or
id|MDIO_DATA_WRITE1
comma
id|mdio_addr
)paren
suffix:semicolon
id|mdio_delay
c_func
(paren
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|MDIO_ENB
op_or
id|MDIO_DATA_WRITE1
op_or
id|MDIO_SHIFT_CLK
comma
id|mdio_addr
)paren
suffix:semicolon
id|mdio_delay
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Shift the command bits out. */
r_for
c_loop
(paren
id|i
op_assign
l_int|31
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_int
id|dataval
op_assign
(paren
id|cmd
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
ques
c_cond
id|MDIO_DATA_WRITE1
suffix:colon
l_int|0
suffix:semicolon
id|iowrite32
c_func
(paren
id|MDIO_ENB
op_or
id|dataval
comma
id|mdio_addr
)paren
suffix:semicolon
id|mdio_delay
c_func
(paren
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|MDIO_ENB
op_or
id|dataval
op_or
id|MDIO_SHIFT_CLK
comma
id|mdio_addr
)paren
suffix:semicolon
id|mdio_delay
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear out extra bits. */
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|iowrite32
c_func
(paren
id|MDIO_ENB_IN
comma
id|mdio_addr
)paren
suffix:semicolon
id|mdio_delay
c_func
(paren
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|MDIO_ENB_IN
op_or
id|MDIO_SHIFT_CLK
comma
id|mdio_addr
)paren
suffix:semicolon
id|mdio_delay
c_func
(paren
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tp-&gt;mii_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Set up the transceiver control registers for the selected media type. */
DECL|function|tulip_select_media
r_void
id|tulip_select_media
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|startup
)paren
(brace
r_struct
id|tulip_private
op_star
id|tp
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_void
id|__iomem
op_star
id|ioaddr
op_assign
id|tp-&gt;base_addr
suffix:semicolon
r_struct
id|mediatable
op_star
id|mtable
op_assign
id|tp-&gt;mtable
suffix:semicolon
id|u32
id|new_csr6
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|mtable
)paren
(brace
r_struct
id|medialeaf
op_star
id|mleaf
op_assign
op_amp
id|mtable-&gt;mleaf
(braket
id|tp-&gt;cur_index
)braket
suffix:semicolon
r_int
r_char
op_star
id|p
op_assign
id|mleaf-&gt;leafdata
suffix:semicolon
r_switch
c_cond
(paren
id|mleaf-&gt;type
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* 21140 non-MII xcvr. */
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Using a 21140 non-MII transceiver&quot;
l_string|&quot; with control setting %2.2x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|p
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|dev-&gt;if_port
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|startup
)paren
id|iowrite32
c_func
(paren
id|mtable-&gt;csr12dir
op_or
l_int|0x100
comma
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|p
(braket
l_int|1
)braket
comma
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
id|new_csr6
op_assign
l_int|0x02000000
op_or
(paren
(paren
id|p
(braket
l_int|2
)braket
op_amp
l_int|0x71
)paren
op_lshift
l_int|18
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_case
l_int|4
suffix:colon
(brace
id|u16
id|setup
(braket
l_int|5
)braket
suffix:semicolon
id|u32
id|csr13val
comma
id|csr14val
comma
id|csr15dir
comma
id|csr15val
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
l_int|5
suffix:semicolon
id|i
op_increment
)paren
id|setup
(braket
id|i
)braket
op_assign
id|get_u16
c_func
(paren
op_amp
id|p
(braket
id|i
op_star
l_int|2
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|dev-&gt;if_port
op_assign
id|p
(braket
l_int|0
)braket
op_amp
id|MEDIA_MASK
suffix:semicolon
r_if
c_cond
(paren
id|tulip_media_cap
(braket
id|dev-&gt;if_port
)braket
op_amp
id|MediaAlwaysFD
)paren
id|tp-&gt;full_duplex
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|startup
op_logical_and
id|mtable-&gt;has_reset
)paren
(brace
r_struct
id|medialeaf
op_star
id|rleaf
op_assign
op_amp
id|mtable-&gt;mleaf
(braket
id|mtable-&gt;has_reset
)braket
suffix:semicolon
r_int
r_char
op_star
id|rst
op_assign
id|rleaf-&gt;leafdata
suffix:semicolon
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Resetting the transceiver.&bslash;n&quot;
comma
id|dev-&gt;name
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
id|rst
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
)paren
id|iowrite32
c_func
(paren
id|get_u16
c_func
(paren
id|rst
op_plus
l_int|1
op_plus
(paren
id|i
op_lshift
l_int|1
)paren
)paren
op_lshift
l_int|16
comma
id|ioaddr
op_plus
id|CSR15
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: 21143 non-MII %s transceiver control &quot;
l_string|&quot;%4.4x/%4.4x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|medianame
(braket
id|dev-&gt;if_port
)braket
comma
id|setup
(braket
l_int|0
)braket
comma
id|setup
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
(braket
l_int|0
)braket
op_amp
l_int|0x40
)paren
(brace
multiline_comment|/* SIA (CSR13-15) setup values are provided. */
id|csr13val
op_assign
id|setup
(braket
l_int|0
)braket
suffix:semicolon
id|csr14val
op_assign
id|setup
(braket
l_int|1
)braket
suffix:semicolon
id|csr15dir
op_assign
(paren
id|setup
(braket
l_int|3
)braket
op_lshift
l_int|16
)paren
op_or
id|setup
(braket
l_int|2
)braket
suffix:semicolon
id|csr15val
op_assign
(paren
id|setup
(braket
l_int|4
)braket
op_lshift
l_int|16
)paren
op_or
id|setup
(braket
l_int|2
)braket
suffix:semicolon
id|iowrite32
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|CSR13
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|csr14val
comma
id|ioaddr
op_plus
id|CSR14
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|csr15dir
comma
id|ioaddr
op_plus
id|CSR15
)paren
suffix:semicolon
multiline_comment|/* Direction */
id|iowrite32
c_func
(paren
id|csr15val
comma
id|ioaddr
op_plus
id|CSR15
)paren
suffix:semicolon
multiline_comment|/* Data */
id|iowrite32
c_func
(paren
id|csr13val
comma
id|ioaddr
op_plus
id|CSR13
)paren
suffix:semicolon
)brace
r_else
(brace
id|csr13val
op_assign
l_int|1
suffix:semicolon
id|csr14val
op_assign
l_int|0
suffix:semicolon
id|csr15dir
op_assign
(paren
id|setup
(braket
l_int|0
)braket
op_lshift
l_int|16
)paren
op_or
l_int|0x0008
suffix:semicolon
id|csr15val
op_assign
(paren
id|setup
(braket
l_int|1
)braket
op_lshift
l_int|16
)paren
op_or
l_int|0x0008
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;if_port
op_le
l_int|4
)paren
id|csr14val
op_assign
id|t21142_csr14
(braket
id|dev-&gt;if_port
)braket
suffix:semicolon
r_if
c_cond
(paren
id|startup
)paren
(brace
id|iowrite32
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|CSR13
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|csr14val
comma
id|ioaddr
op_plus
id|CSR14
)paren
suffix:semicolon
)brace
id|iowrite32
c_func
(paren
id|csr15dir
comma
id|ioaddr
op_plus
id|CSR15
)paren
suffix:semicolon
multiline_comment|/* Direction */
id|iowrite32
c_func
(paren
id|csr15val
comma
id|ioaddr
op_plus
id|CSR15
)paren
suffix:semicolon
multiline_comment|/* Data */
r_if
c_cond
(paren
id|startup
)paren
id|iowrite32
c_func
(paren
id|csr13val
comma
id|ioaddr
op_plus
id|CSR13
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s:  Setting CSR15 to %8.8x/%8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr15dir
comma
id|csr15val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mleaf-&gt;type
op_eq
l_int|4
)paren
id|new_csr6
op_assign
l_int|0x82020000
op_or
(paren
(paren
id|setup
(braket
l_int|2
)braket
op_amp
l_int|0x71
)paren
op_lshift
l_int|18
)paren
suffix:semicolon
r_else
id|new_csr6
op_assign
l_int|0x82420000
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|1
suffix:colon
r_case
l_int|3
suffix:colon
(brace
r_int
id|phy_num
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|init_length
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
id|u16
op_star
id|misc_info
comma
id|tmp_info
suffix:semicolon
id|dev-&gt;if_port
op_assign
l_int|11
suffix:semicolon
id|new_csr6
op_assign
l_int|0x020E0000
suffix:semicolon
r_if
c_cond
(paren
id|mleaf-&gt;type
op_eq
l_int|3
)paren
(brace
multiline_comment|/* 21142 */
id|u16
op_star
id|init_sequence
op_assign
(paren
id|u16
op_star
)paren
(paren
id|p
op_plus
l_int|2
)paren
suffix:semicolon
id|u16
op_star
id|reset_sequence
op_assign
op_amp
(paren
(paren
id|u16
op_star
)paren
(paren
id|p
op_plus
l_int|3
)paren
)paren
(braket
id|init_length
)braket
suffix:semicolon
r_int
id|reset_length
op_assign
id|p
(braket
l_int|2
op_plus
id|init_length
op_star
l_int|2
)braket
suffix:semicolon
id|misc_info
op_assign
id|reset_sequence
op_plus
id|reset_length
suffix:semicolon
r_if
c_cond
(paren
id|startup
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|reset_length
suffix:semicolon
id|i
op_increment
)paren
id|iowrite32
c_func
(paren
id|get_u16
c_func
(paren
op_amp
id|reset_sequence
(braket
id|i
)braket
)paren
op_lshift
l_int|16
comma
id|ioaddr
op_plus
id|CSR15
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
id|init_length
suffix:semicolon
id|i
op_increment
)paren
id|iowrite32
c_func
(paren
id|get_u16
c_func
(paren
op_amp
id|init_sequence
(braket
id|i
)braket
)paren
op_lshift
l_int|16
comma
id|ioaddr
op_plus
id|CSR15
)paren
suffix:semicolon
)brace
r_else
(brace
id|u8
op_star
id|init_sequence
op_assign
id|p
op_plus
l_int|2
suffix:semicolon
id|u8
op_star
id|reset_sequence
op_assign
id|p
op_plus
l_int|3
op_plus
id|init_length
suffix:semicolon
r_int
id|reset_length
op_assign
id|p
(braket
l_int|2
op_plus
id|init_length
)braket
suffix:semicolon
id|misc_info
op_assign
(paren
id|u16
op_star
)paren
(paren
id|reset_sequence
op_plus
id|reset_length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|startup
)paren
(brace
id|iowrite32
c_func
(paren
id|mtable-&gt;csr12dir
op_or
l_int|0x100
comma
id|ioaddr
op_plus
id|CSR12
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
id|reset_length
suffix:semicolon
id|i
op_increment
)paren
id|iowrite32
c_func
(paren
id|reset_sequence
(braket
id|i
)braket
comma
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|init_length
suffix:semicolon
id|i
op_increment
)paren
id|iowrite32
c_func
(paren
id|init_sequence
(braket
id|i
)braket
comma
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
)brace
id|tmp_info
op_assign
id|get_u16
c_func
(paren
op_amp
id|misc_info
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp_info
)paren
id|tp-&gt;advertising
(braket
id|phy_num
)braket
op_assign
id|tmp_info
op_or
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|tmp_info
op_logical_and
id|startup
OL
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;mii_advertise
op_eq
l_int|0
)paren
id|tp-&gt;mii_advertise
op_assign
id|tp-&gt;advertising
(braket
id|phy_num
)braket
suffix:semicolon
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s:  Advertising %4.4x on MII %d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|tp-&gt;mii_advertise
comma
id|tp-&gt;phys
(braket
id|phy_num
)braket
)paren
suffix:semicolon
id|tulip_mdio_write
c_func
(paren
id|dev
comma
id|tp-&gt;phys
(braket
id|phy_num
)braket
comma
l_int|4
comma
id|tp-&gt;mii_advertise
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
l_int|5
suffix:colon
r_case
l_int|6
suffix:colon
(brace
id|u16
id|setup
(braket
l_int|5
)braket
suffix:semicolon
id|new_csr6
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|5
suffix:semicolon
id|i
op_increment
)paren
id|setup
(braket
id|i
)braket
op_assign
id|get_u16
c_func
(paren
op_amp
id|p
(braket
id|i
op_star
l_int|2
op_plus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|startup
op_logical_and
id|mtable-&gt;has_reset
)paren
(brace
r_struct
id|medialeaf
op_star
id|rleaf
op_assign
op_amp
id|mtable-&gt;mleaf
(braket
id|mtable-&gt;has_reset
)braket
suffix:semicolon
r_int
r_char
op_star
id|rst
op_assign
id|rleaf-&gt;leafdata
suffix:semicolon
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Resetting the transceiver.&bslash;n&quot;
comma
id|dev-&gt;name
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
id|rst
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
)paren
id|iowrite32
c_func
(paren
id|get_u16
c_func
(paren
id|rst
op_plus
l_int|1
op_plus
(paren
id|i
op_lshift
l_int|1
)paren
)paren
op_lshift
l_int|16
comma
id|ioaddr
op_plus
id|CSR15
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s:  Invalid media table selection %d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|mleaf-&gt;type
)paren
suffix:semicolon
id|new_csr6
op_assign
l_int|0x020E0000
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Using media type %s, CSR12 is %2.2x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|medianame
(braket
id|dev-&gt;if_port
)braket
comma
id|ioread32
c_func
(paren
id|ioaddr
op_plus
id|CSR12
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tp-&gt;chip_id
op_eq
id|LC82C168
)paren
(brace
r_if
c_cond
(paren
id|startup
op_logical_and
op_logical_neg
id|tp-&gt;medialock
)paren
id|dev-&gt;if_port
op_assign
id|tp-&gt;mii_cnt
ques
c_cond
l_int|11
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: PNIC PHY status is %3.3x, media %s.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ioread32
c_func
(paren
id|ioaddr
op_plus
l_int|0xB8
)paren
comma
id|medianame
(braket
id|dev-&gt;if_port
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;mii_cnt
)paren
(brace
id|new_csr6
op_assign
l_int|0x810C0000
suffix:semicolon
id|iowrite32
c_func
(paren
l_int|0x0001
comma
id|ioaddr
op_plus
id|CSR15
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
l_int|0x0201B07A
comma
id|ioaddr
op_plus
l_int|0xB8
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|startup
)paren
(brace
multiline_comment|/* Start with 10mbps to do autonegotiation. */
id|iowrite32
c_func
(paren
l_int|0x32
comma
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
id|new_csr6
op_assign
l_int|0x00420000
suffix:semicolon
id|iowrite32
c_func
(paren
l_int|0x0001B078
comma
id|ioaddr
op_plus
l_int|0xB8
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
l_int|0x0201B078
comma
id|ioaddr
op_plus
l_int|0xB8
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;if_port
op_eq
l_int|3
op_logical_or
id|dev-&gt;if_port
op_eq
l_int|5
)paren
(brace
id|iowrite32
c_func
(paren
l_int|0x33
comma
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
id|new_csr6
op_assign
l_int|0x01860000
suffix:semicolon
multiline_comment|/* Trigger autonegotiation. */
id|iowrite32
c_func
(paren
id|startup
ques
c_cond
l_int|0x0201F868
suffix:colon
l_int|0x0001F868
comma
id|ioaddr
op_plus
l_int|0xB8
)paren
suffix:semicolon
)brace
r_else
(brace
id|iowrite32
c_func
(paren
l_int|0x32
comma
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
id|new_csr6
op_assign
l_int|0x00420000
suffix:semicolon
id|iowrite32
c_func
(paren
l_int|0x1F078
comma
id|ioaddr
op_plus
l_int|0xB8
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Unknown chip type with no media table. */
r_if
c_cond
(paren
id|tp-&gt;default_port
op_eq
l_int|0
)paren
id|dev-&gt;if_port
op_assign
id|tp-&gt;mii_cnt
ques
c_cond
l_int|11
suffix:colon
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|tulip_media_cap
(braket
id|dev-&gt;if_port
)braket
op_amp
id|MediaIsMII
)paren
(brace
id|new_csr6
op_assign
l_int|0x020E0000
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tulip_media_cap
(braket
id|dev-&gt;if_port
)braket
op_amp
id|MediaIsFx
)paren
(brace
id|new_csr6
op_assign
l_int|0x02860000
suffix:semicolon
)brace
r_else
id|new_csr6
op_assign
l_int|0x03860000
suffix:semicolon
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: No media description table, assuming &quot;
l_string|&quot;%s transceiver, CSR12 %2.2x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|medianame
(braket
id|dev-&gt;if_port
)braket
comma
id|ioread32
c_func
(paren
id|ioaddr
op_plus
id|CSR12
)paren
)paren
suffix:semicolon
)brace
id|tp-&gt;csr6
op_assign
id|new_csr6
op_or
(paren
id|tp-&gt;csr6
op_amp
l_int|0xfdff
)paren
op_or
(paren
id|tp-&gt;full_duplex
ques
c_cond
l_int|0x0200
suffix:colon
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;  Check the MII negotiated duplex and change the CSR6 setting if&n;  required.&n;  Return 0 if everything is OK.&n;  Return &lt; 0 if the transceiver is missing or has no link beat.&n;  */
DECL|function|tulip_check_duplex
r_int
id|tulip_check_duplex
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|tulip_private
op_star
id|tp
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_int
id|bmsr
comma
id|lpa
comma
id|negotiated
comma
id|new_csr6
suffix:semicolon
id|bmsr
op_assign
id|tulip_mdio_read
c_func
(paren
id|dev
comma
id|tp-&gt;phys
(braket
l_int|0
)braket
comma
id|MII_BMSR
)paren
suffix:semicolon
id|lpa
op_assign
id|tulip_mdio_read
c_func
(paren
id|dev
comma
id|tp-&gt;phys
(braket
l_int|0
)braket
comma
id|MII_LPA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: MII status %4.4x, Link partner report &quot;
l_string|&quot;%4.4x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|bmsr
comma
id|lpa
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bmsr
op_eq
l_int|0xffff
)paren
r_return
op_minus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bmsr
op_amp
id|BMSR_LSTATUS
)paren
op_eq
l_int|0
)paren
(brace
r_int
id|new_bmsr
op_assign
id|tulip_mdio_read
c_func
(paren
id|dev
comma
id|tp-&gt;phys
(braket
l_int|0
)braket
comma
id|MII_BMSR
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|new_bmsr
op_amp
id|BMSR_LSTATUS
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: No link beat on the MII interface,&quot;
l_string|&quot; status %4.4x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|new_bmsr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|negotiated
op_assign
id|lpa
op_amp
id|tp-&gt;advertising
(braket
l_int|0
)braket
suffix:semicolon
id|tp-&gt;full_duplex
op_assign
id|mii_duplex
c_func
(paren
id|tp-&gt;full_duplex_lock
comma
id|negotiated
)paren
suffix:semicolon
id|new_csr6
op_assign
id|tp-&gt;csr6
suffix:semicolon
r_if
c_cond
(paren
id|negotiated
op_amp
id|LPA_100
)paren
id|new_csr6
op_and_assign
op_complement
id|TxThreshold
suffix:semicolon
r_else
id|new_csr6
op_or_assign
id|TxThreshold
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;full_duplex
)paren
id|new_csr6
op_or_assign
id|FullDuplex
suffix:semicolon
r_else
id|new_csr6
op_and_assign
op_complement
id|FullDuplex
suffix:semicolon
r_if
c_cond
(paren
id|new_csr6
op_ne
id|tp-&gt;csr6
)paren
(brace
id|tp-&gt;csr6
op_assign
id|new_csr6
suffix:semicolon
id|tulip_restart_rxtx
c_func
(paren
id|tp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Setting %s-duplex based on MII&quot;
l_string|&quot;#%d link partner capability of %4.4x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|tp-&gt;full_duplex
ques
c_cond
l_string|&quot;full&quot;
suffix:colon
l_string|&quot;half&quot;
comma
id|tp-&gt;phys
(braket
l_int|0
)braket
comma
id|lpa
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tulip_find_mii
r_void
id|__devinit
id|tulip_find_mii
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|board_idx
)paren
(brace
r_struct
id|tulip_private
op_star
id|tp
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|phyn
comma
id|phy_idx
op_assign
l_int|0
suffix:semicolon
r_int
id|mii_reg0
suffix:semicolon
r_int
id|mii_advert
suffix:semicolon
r_int
r_int
id|to_advert
comma
id|new_bmcr
comma
id|ane_switch
suffix:semicolon
multiline_comment|/* Find the connected MII xcvrs.&n;&t;   Doing this in open() would allow detecting external xcvrs later,&n;&t;   but takes much time. */
r_for
c_loop
(paren
id|phyn
op_assign
l_int|1
suffix:semicolon
id|phyn
op_le
l_int|32
op_logical_and
id|phy_idx
OL
r_sizeof
(paren
id|tp-&gt;phys
)paren
suffix:semicolon
id|phyn
op_increment
)paren
(brace
r_int
id|phy
op_assign
id|phyn
op_amp
l_int|0x1f
suffix:semicolon
r_int
id|mii_status
op_assign
id|tulip_mdio_read
(paren
id|dev
comma
id|phy
comma
id|MII_BMSR
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mii_status
op_amp
l_int|0x8301
)paren
op_eq
l_int|0x8001
op_logical_or
(paren
(paren
id|mii_status
op_amp
id|BMSR_100BASE4
)paren
op_eq
l_int|0
op_logical_and
(paren
id|mii_status
op_amp
l_int|0x7800
)paren
op_ne
l_int|0
)paren
)paren
(brace
multiline_comment|/* preserve Becker logic, gain indentation level */
)brace
r_else
(brace
r_continue
suffix:semicolon
)brace
id|mii_reg0
op_assign
id|tulip_mdio_read
(paren
id|dev
comma
id|phy
comma
id|MII_BMCR
)paren
suffix:semicolon
id|mii_advert
op_assign
id|tulip_mdio_read
(paren
id|dev
comma
id|phy
comma
id|MII_ADVERTISE
)paren
suffix:semicolon
id|ane_switch
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* if not advertising at all, gen an&n;&t;&t; * advertising value from the capability&n;&t;&t; * bits in BMSR&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|mii_advert
op_amp
id|ADVERTISE_ALL
)paren
op_eq
l_int|0
)paren
(brace
r_int
r_int
id|tmpadv
op_assign
id|tulip_mdio_read
(paren
id|dev
comma
id|phy
comma
id|MII_BMSR
)paren
suffix:semicolon
id|mii_advert
op_assign
(paren
(paren
id|tmpadv
op_rshift
l_int|6
)paren
op_amp
l_int|0x3e0
)paren
op_or
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tp-&gt;mii_advertise
)paren
(brace
id|tp-&gt;advertising
(braket
id|phy_idx
)braket
op_assign
id|to_advert
op_assign
id|tp-&gt;mii_advertise
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tp-&gt;advertising
(braket
id|phy_idx
)braket
)paren
(brace
id|to_advert
op_assign
id|tp-&gt;advertising
(braket
id|phy_idx
)braket
suffix:semicolon
)brace
r_else
(brace
id|tp-&gt;advertising
(braket
id|phy_idx
)braket
op_assign
id|tp-&gt;mii_advertise
op_assign
id|to_advert
op_assign
id|mii_advert
suffix:semicolon
)brace
id|tp-&gt;phys
(braket
id|phy_idx
op_increment
)braket
op_assign
id|phy
suffix:semicolon
id|printk
(paren
id|KERN_INFO
l_string|&quot;tulip%d:  MII transceiver #%d &quot;
l_string|&quot;config %4.4x status %4.4x advertising %4.4x.&bslash;n&quot;
comma
id|board_idx
comma
id|phy
comma
id|mii_reg0
comma
id|mii_status
comma
id|mii_advert
)paren
suffix:semicolon
multiline_comment|/* Fixup for DLink with miswired PHY. */
r_if
c_cond
(paren
id|mii_advert
op_ne
id|to_advert
)paren
(brace
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;tulip%d:  Advertising %4.4x on PHY %d,&quot;
l_string|&quot; previously advertising %4.4x.&bslash;n&quot;
comma
id|board_idx
comma
id|to_advert
comma
id|phy
comma
id|mii_advert
)paren
suffix:semicolon
id|tulip_mdio_write
(paren
id|dev
comma
id|phy
comma
l_int|4
comma
id|to_advert
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable autonegotiation: some boards default to off. */
r_if
c_cond
(paren
id|tp-&gt;default_port
op_eq
l_int|0
)paren
(brace
id|new_bmcr
op_assign
id|mii_reg0
op_or
id|BMCR_ANENABLE
suffix:semicolon
r_if
c_cond
(paren
id|new_bmcr
op_ne
id|mii_reg0
)paren
(brace
id|new_bmcr
op_or_assign
id|BMCR_ANRESTART
suffix:semicolon
id|ane_switch
op_assign
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* ...or disable nway, if forcing media */
r_else
(brace
id|new_bmcr
op_assign
id|mii_reg0
op_amp
op_complement
id|BMCR_ANENABLE
suffix:semicolon
r_if
c_cond
(paren
id|new_bmcr
op_ne
id|mii_reg0
)paren
id|ane_switch
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* clear out bits we never want at this point */
id|new_bmcr
op_and_assign
op_complement
(paren
id|BMCR_CTST
op_or
id|BMCR_FULLDPLX
op_or
id|BMCR_ISOLATE
op_or
id|BMCR_PDOWN
op_or
id|BMCR_SPEED100
op_or
id|BMCR_LOOPBACK
op_or
id|BMCR_RESET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;full_duplex
)paren
id|new_bmcr
op_or_assign
id|BMCR_FULLDPLX
suffix:semicolon
r_if
c_cond
(paren
id|tulip_media_cap
(braket
id|tp-&gt;default_port
)braket
op_amp
id|MediaIs100
)paren
id|new_bmcr
op_or_assign
id|BMCR_SPEED100
suffix:semicolon
r_if
c_cond
(paren
id|new_bmcr
op_ne
id|mii_reg0
)paren
(brace
multiline_comment|/* some phys need the ANE switch to&n;&t;&t;&t; * happen before forced media settings&n;&t;&t;&t; * will &quot;take.&quot;  However, we write the&n;&t;&t;&t; * same value twice in order not to&n;&t;&t;&t; * confuse the sane phys.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|ane_switch
)paren
(brace
id|tulip_mdio_write
(paren
id|dev
comma
id|phy
comma
id|MII_BMCR
comma
id|new_bmcr
)paren
suffix:semicolon
id|udelay
(paren
l_int|10
)paren
suffix:semicolon
)brace
id|tulip_mdio_write
(paren
id|dev
comma
id|phy
comma
id|MII_BMCR
comma
id|new_bmcr
)paren
suffix:semicolon
)brace
)brace
id|tp-&gt;mii_cnt
op_assign
id|phy_idx
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;mtable
op_logical_and
id|tp-&gt;mtable-&gt;has_mii
op_logical_and
id|phy_idx
op_eq
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;tulip%d: ***WARNING***: No MII transceiver found!&bslash;n&quot;
comma
id|board_idx
)paren
suffix:semicolon
id|tp-&gt;phys
(braket
l_int|0
)braket
op_assign
l_int|1
suffix:semicolon
)brace
)brace
eof
