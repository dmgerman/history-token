multiline_comment|/*&n;&t;drivers/net/tulip/pnic.c&n;&n;&t;Maintained by Jeff Garzik &lt;jgarzik@pobox.com&gt;&n;&t;Copyright 2000,2001  The Linux Kernel Team&n;&t;Written/copyright 1994-2001 by Donald Becker.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU General Public License, incorporated herein by reference.&n;&n;&t;Please refer to Documentation/DocBook/tulip.{pdf,ps,html}&n;&t;for more information on this driver, or visit the project&n;&t;Web page at http://sourceforge.net/projects/tulip/&n;&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &quot;tulip.h&quot;
DECL|function|pnic_do_nway
r_void
id|pnic_do_nway
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
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|u32
id|phy_reg
op_assign
id|inl
c_func
(paren
id|ioaddr
op_plus
l_int|0xB8
)paren
suffix:semicolon
id|u32
id|new_csr6
op_assign
id|tp-&gt;csr6
op_amp
op_complement
l_int|0x40C40200
suffix:semicolon
r_if
c_cond
(paren
id|phy_reg
op_amp
l_int|0x78000000
)paren
(brace
multiline_comment|/* Ignore baseT4 */
r_if
c_cond
(paren
id|phy_reg
op_amp
l_int|0x20000000
)paren
id|dev-&gt;if_port
op_assign
l_int|5
suffix:semicolon
r_else
r_if
c_cond
(paren
id|phy_reg
op_amp
l_int|0x40000000
)paren
id|dev-&gt;if_port
op_assign
l_int|3
suffix:semicolon
r_else
r_if
c_cond
(paren
id|phy_reg
op_amp
l_int|0x10000000
)paren
id|dev-&gt;if_port
op_assign
l_int|4
suffix:semicolon
r_else
r_if
c_cond
(paren
id|phy_reg
op_amp
l_int|0x08000000
)paren
id|dev-&gt;if_port
op_assign
l_int|0
suffix:semicolon
id|tp-&gt;nwayset
op_assign
l_int|1
suffix:semicolon
id|new_csr6
op_assign
(paren
id|dev-&gt;if_port
op_amp
l_int|1
)paren
ques
c_cond
l_int|0x01860000
suffix:colon
l_int|0x00420000
suffix:semicolon
id|outl
c_func
(paren
l_int|0x32
op_or
(paren
id|dev-&gt;if_port
op_amp
l_int|1
)paren
comma
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;if_port
op_amp
l_int|1
)paren
id|outl
c_func
(paren
l_int|0x1F868
comma
id|ioaddr
op_plus
l_int|0xB8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|phy_reg
op_amp
l_int|0x30000000
)paren
(brace
id|tp-&gt;full_duplex
op_assign
l_int|1
suffix:semicolon
id|new_csr6
op_or_assign
l_int|0x00000200
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
l_string|&quot;%s: PNIC autonegotiated status %8.8x, %s.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|phy_reg
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
id|tp-&gt;csr6
op_ne
id|new_csr6
)paren
(brace
id|tp-&gt;csr6
op_assign
id|new_csr6
suffix:semicolon
multiline_comment|/* Restart Tx */
id|tulip_restart_rxtx
c_func
(paren
id|tp
)paren
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
)brace
)brace
)brace
DECL|function|pnic_lnk_change
r_void
id|pnic_lnk_change
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|csr5
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
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|phy_reg
op_assign
id|inl
c_func
(paren
id|ioaddr
op_plus
l_int|0xB8
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
id|KERN_DEBUG
l_string|&quot;%s: PNIC link changed state %8.8x, CSR5 %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|phy_reg
comma
id|csr5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR5
)paren
op_amp
id|TPLnkFail
)paren
(brace
id|outl
c_func
(paren
(paren
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR7
)paren
op_amp
op_complement
id|TPLnkFail
)paren
op_or
id|TPLnkPass
comma
id|ioaddr
op_plus
id|CSR7
)paren
suffix:semicolon
multiline_comment|/* If we use an external MII, then we mustn&squot;t use the&n;&t;&t; * internal negotiation.&n;&t;&t; */
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
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tp-&gt;nwayset
op_logical_or
id|jiffies
op_minus
id|dev-&gt;trans_start
OG
l_int|1
op_star
id|HZ
)paren
(brace
id|tp-&gt;csr6
op_assign
l_int|0x00420000
op_or
(paren
id|tp-&gt;csr6
op_amp
l_int|0x0000fdff
)paren
suffix:semicolon
id|outl
c_func
(paren
id|tp-&gt;csr6
comma
id|ioaddr
op_plus
id|CSR6
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0x30
comma
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0x0201F078
comma
id|ioaddr
op_plus
l_int|0xB8
)paren
suffix:semicolon
multiline_comment|/* Turn on autonegotiation. */
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR5
)paren
op_amp
id|TPLnkPass
)paren
(brace
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
id|spin_lock
c_func
(paren
op_amp
id|tp-&gt;lock
)paren
suffix:semicolon
id|tulip_check_duplex
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|tp-&gt;lock
)paren
suffix:semicolon
)brace
r_else
(brace
id|pnic_do_nway
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|outl
c_func
(paren
(paren
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR7
)paren
op_amp
op_complement
id|TPLnkPass
)paren
op_or
id|TPLnkFail
comma
id|ioaddr
op_plus
id|CSR7
)paren
suffix:semicolon
)brace
)brace
DECL|function|pnic_timer
r_void
id|pnic_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|data
suffix:semicolon
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
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|next_tick
op_assign
l_int|60
op_star
id|HZ
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR7
)paren
)paren
(brace
multiline_comment|/* the timer was called due to a work overflow&n;&t;&t; * in the interrupt handler. Skip the connection&n;&t;&t; * checks, the nic is definitively speaking with&n;&t;&t; * his link partner.&n;&t;&t; */
r_goto
id|too_good_connection
suffix:semicolon
)brace
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
id|spin_lock_irq
c_func
(paren
op_amp
id|tp-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tulip_check_duplex
c_func
(paren
id|dev
)paren
OG
l_int|0
)paren
id|next_tick
op_assign
l_int|3
op_star
id|HZ
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|tp-&gt;lock
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|csr12
op_assign
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
r_int
id|new_csr6
op_assign
id|tp-&gt;csr6
op_amp
op_complement
l_int|0x40C40200
suffix:semicolon
r_int
id|phy_reg
op_assign
id|inl
c_func
(paren
id|ioaddr
op_plus
l_int|0xB8
)paren
suffix:semicolon
r_int
id|csr5
op_assign
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR5
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
id|KERN_DEBUG
l_string|&quot;%s: PNIC timer PHY status %8.8x, %s &quot;
l_string|&quot;CSR5 %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|phy_reg
comma
id|medianame
(braket
id|dev-&gt;if_port
)braket
comma
id|csr5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|phy_reg
op_amp
l_int|0x04000000
)paren
(brace
multiline_comment|/* Remote link fault */
id|outl
c_func
(paren
l_int|0x0201F078
comma
id|ioaddr
op_plus
l_int|0xB8
)paren
suffix:semicolon
id|next_tick
op_assign
l_int|1
op_star
id|HZ
suffix:semicolon
id|tp-&gt;nwayset
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|phy_reg
op_amp
l_int|0x78000000
)paren
(brace
multiline_comment|/* Ignore baseT4 */
id|pnic_do_nway
c_func
(paren
id|dev
)paren
suffix:semicolon
id|next_tick
op_assign
l_int|60
op_star
id|HZ
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|csr5
op_amp
id|TPLnkFail
)paren
(brace
multiline_comment|/* 100baseTx link beat */
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
l_string|&quot;%s: %s link beat failed, CSR12 %4.4x, &quot;
l_string|&quot;CSR5 %8.8x, PHY %3.3x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|medianame
(braket
id|dev-&gt;if_port
)braket
comma
id|csr12
comma
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR5
)paren
comma
id|inl
c_func
(paren
id|ioaddr
op_plus
l_int|0xB8
)paren
)paren
suffix:semicolon
id|next_tick
op_assign
l_int|3
op_star
id|HZ
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;medialock
)paren
(brace
)brace
r_else
r_if
c_cond
(paren
id|tp-&gt;nwayset
op_logical_and
(paren
id|dev-&gt;if_port
op_amp
l_int|1
)paren
)paren
(brace
id|next_tick
op_assign
l_int|1
op_star
id|HZ
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;if_port
op_eq
l_int|0
)paren
(brace
id|dev-&gt;if_port
op_assign
l_int|3
suffix:semicolon
id|outl
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
id|outl
c_func
(paren
l_int|0x1F868
comma
id|ioaddr
op_plus
l_int|0xB8
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;if_port
op_assign
l_int|0
suffix:semicolon
id|outl
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
id|outl
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
r_if
c_cond
(paren
id|tp-&gt;csr6
op_ne
id|new_csr6
)paren
(brace
id|tp-&gt;csr6
op_assign
id|new_csr6
suffix:semicolon
multiline_comment|/* Restart Tx */
id|tulip_restart_rxtx
c_func
(paren
id|tp
)paren
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
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
l_string|&quot;%s: Changing PNIC configuration to %s &quot;
l_string|&quot;%s-duplex, CSR6 %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|medianame
(braket
id|dev-&gt;if_port
)braket
comma
id|tp-&gt;full_duplex
ques
c_cond
l_string|&quot;full&quot;
suffix:colon
l_string|&quot;half&quot;
comma
id|new_csr6
)paren
suffix:semicolon
)brace
)brace
)brace
id|too_good_connection
suffix:colon
id|mod_timer
c_func
(paren
op_amp
id|tp-&gt;timer
comma
id|RUN_AT
c_func
(paren
id|next_tick
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR7
)paren
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
l_string|&quot;%s: sw timer wakeup.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
id|tulip_refill_rx
c_func
(paren
id|dev
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
id|outl
c_func
(paren
id|tulip_tbl
(braket
id|tp-&gt;chip_id
)braket
dot
id|valid_intrs
comma
id|ioaddr
op_plus
id|CSR7
)paren
suffix:semicolon
)brace
)brace
eof
