multiline_comment|/*&n;&t;drivers/net/tulip/21142.c&n;&n;&t;Maintained by Jeff Garzik &lt;jgarzik@mandrakesoft.com&gt;&n;&t;Copyright 2000,2001  The Linux Kernel Team&n;&t;Written/copyright 1994-2001 by Donald Becker.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU General Public License, incorporated herein by reference.&n;&n;&t;Please refer to Documentation/DocBook/tulip.{pdf,ps,html}&n;&t;for more information on this driver, or visit the project&n;&t;Web page at http://sourceforge.net/projects/tulip/&n;&n;*/
macro_line|#include &quot;tulip.h&quot;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|variable|t21142_csr13
r_static
id|u16
id|t21142_csr13
(braket
)braket
op_assign
(brace
l_int|0x0001
comma
l_int|0x0009
comma
l_int|0x0009
comma
l_int|0x0000
comma
l_int|0x0001
comma
)brace
suffix:semicolon
DECL|variable|t21142_csr14
id|u16
id|t21142_csr14
(braket
)braket
op_assign
(brace
l_int|0xFFFF
comma
l_int|0x0705
comma
l_int|0x0705
comma
l_int|0x0000
comma
l_int|0x7F3D
comma
)brace
suffix:semicolon
DECL|variable|t21142_csr15
r_static
id|u16
id|t21142_csr15
(braket
)braket
op_assign
(brace
l_int|0x0008
comma
l_int|0x0006
comma
l_int|0x000E
comma
l_int|0x0008
comma
l_int|0x0008
comma
)brace
suffix:semicolon
multiline_comment|/* Handle the 21143 uniquely: do autoselect with NWay, not the EEPROM list&n;   of available transceivers.  */
DECL|function|t21142_timer
r_void
id|t21142_timer
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
(paren
r_struct
id|tulip_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
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
id|next_tick
op_assign
l_int|60
op_star
id|HZ
suffix:semicolon
r_int
id|new_csr6
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: 21143 negotiation status %8.8x, %s.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr12
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
id|tulip_media_cap
(braket
id|dev-&gt;if_port
)braket
op_amp
id|MediaIsMII
)paren
(brace
id|tulip_check_duplex
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
id|tp-&gt;nwayset
)paren
(brace
multiline_comment|/* Don&squot;t screw up a negotiated session! */
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
l_string|&quot;%s: Using NWay-set %s media, csr12 %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|medianame
(braket
id|dev-&gt;if_port
)braket
comma
id|csr12
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tp-&gt;medialock
)paren
(brace
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;if_port
op_eq
l_int|3
)paren
(brace
r_if
c_cond
(paren
id|csr12
op_amp
l_int|2
)paren
(brace
multiline_comment|/* No 100mbps link beat, revert to 10mbps. */
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
l_string|&quot;%s: No 21143 100baseTx link beat, %8.8x, &quot;
l_string|&quot;trying NWay.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr12
)paren
suffix:semicolon
id|t21142_start_nway
c_func
(paren
id|dev
)paren
suffix:semicolon
id|next_tick
op_assign
l_int|3
op_star
id|HZ
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
id|csr12
op_amp
l_int|0x7000
)paren
op_ne
l_int|0x5000
)paren
(brace
multiline_comment|/* Negotiation failed.  Search media types. */
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
l_string|&quot;%s: 21143 negotiation failed, status %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr12
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|csr12
op_amp
l_int|4
)paren
)paren
(brace
multiline_comment|/* 10mbps link beat good. */
id|new_csr6
op_assign
l_int|0x82420000
suffix:semicolon
id|dev-&gt;if_port
op_assign
l_int|0
suffix:semicolon
id|outl
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|CSR13
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0x0003FFFF
comma
id|ioaddr
op_plus
id|CSR14
)paren
suffix:semicolon
id|outw
c_func
(paren
id|t21142_csr15
(braket
id|dev-&gt;if_port
)braket
comma
id|ioaddr
op_plus
id|CSR15
)paren
suffix:semicolon
id|outl
c_func
(paren
id|t21142_csr13
(braket
id|dev-&gt;if_port
)braket
comma
id|ioaddr
op_plus
id|CSR13
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Select 100mbps port to check for link beat. */
id|new_csr6
op_assign
l_int|0x83860000
suffix:semicolon
id|dev-&gt;if_port
op_assign
l_int|3
suffix:semicolon
id|outl
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|CSR13
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0x0003FF7F
comma
id|ioaddr
op_plus
id|CSR14
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|8
comma
id|ioaddr
op_plus
id|CSR15
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|1
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
id|KERN_INFO
l_string|&quot;%s: Testing new 21143 media %s.&bslash;n&quot;
comma
id|dev-&gt;name
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
id|new_csr6
op_ne
(paren
id|tp-&gt;csr6
op_amp
op_complement
l_int|0x00D5
)paren
)paren
(brace
id|tp-&gt;csr6
op_and_assign
l_int|0x00D5
suffix:semicolon
id|tp-&gt;csr6
op_or_assign
id|new_csr6
suffix:semicolon
id|outl
c_func
(paren
l_int|0x0301
comma
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
id|tulip_restart_rxtx
c_func
(paren
id|tp
)paren
suffix:semicolon
)brace
id|next_tick
op_assign
l_int|3
op_star
id|HZ
suffix:semicolon
)brace
multiline_comment|/* mod_timer synchronizes us with potential add_timer calls&n;&t; * from interrupts.&n;&t; */
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
)brace
DECL|function|t21142_start_nway
r_void
id|t21142_start_nway
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
(paren
r_struct
id|tulip_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|csr14
op_assign
(paren
(paren
id|tp-&gt;sym_advertise
op_amp
l_int|0x0780
)paren
op_lshift
l_int|9
)paren
op_or
(paren
(paren
id|tp-&gt;sym_advertise
op_amp
l_int|0x0020
)paren
op_lshift
l_int|1
)paren
op_or
l_int|0xffbf
suffix:semicolon
id|dev-&gt;if_port
op_assign
l_int|0
suffix:semicolon
id|tp-&gt;nway
op_assign
id|tp-&gt;mediasense
op_assign
l_int|1
suffix:semicolon
id|tp-&gt;nwayset
op_assign
id|tp-&gt;lpar
op_assign
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
l_string|&quot;%s: Restarting 21143 autonegotiation, csr14=%8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr14
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0x0001
comma
id|ioaddr
op_plus
id|CSR13
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|outl
c_func
(paren
id|csr14
comma
id|ioaddr
op_plus
id|CSR14
)paren
suffix:semicolon
id|tp-&gt;csr6
op_assign
l_int|0x82420000
op_or
(paren
id|tp-&gt;sym_advertise
op_amp
l_int|0x0040
ques
c_cond
id|FullDuplex
suffix:colon
l_int|0
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
r_if
c_cond
(paren
id|tp-&gt;mtable
op_logical_and
id|tp-&gt;mtable-&gt;csr15dir
)paren
(brace
id|outl
c_func
(paren
id|tp-&gt;mtable-&gt;csr15dir
comma
id|ioaddr
op_plus
id|CSR15
)paren
suffix:semicolon
id|outl
c_func
(paren
id|tp-&gt;mtable-&gt;csr15val
comma
id|ioaddr
op_plus
id|CSR15
)paren
suffix:semicolon
)brace
r_else
id|outw
c_func
(paren
l_int|0x0008
comma
id|ioaddr
op_plus
id|CSR15
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0x1301
comma
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
multiline_comment|/* Trigger NWAY. */
)brace
DECL|function|t21142_lnk_change
r_void
id|t21142_lnk_change
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
(paren
r_struct
id|tulip_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
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
l_string|&quot;%s: 21143 link status interrupt %8.8x, CSR5 %x, &quot;
l_string|&quot;%8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr12
comma
id|csr5
comma
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR14
)paren
)paren
suffix:semicolon
multiline_comment|/* If NWay finished and we have a negotiated partner capability. */
r_if
c_cond
(paren
id|tp-&gt;nway
op_logical_and
op_logical_neg
id|tp-&gt;nwayset
op_logical_and
(paren
id|csr12
op_amp
l_int|0x7000
)paren
op_eq
l_int|0x5000
)paren
(brace
r_int
id|setup_done
op_assign
l_int|0
suffix:semicolon
r_int
id|negotiated
op_assign
id|tp-&gt;sym_advertise
op_amp
(paren
id|csr12
op_rshift
l_int|16
)paren
suffix:semicolon
id|tp-&gt;lpar
op_assign
id|csr12
op_rshift
l_int|16
suffix:semicolon
id|tp-&gt;nwayset
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|negotiated
op_amp
l_int|0x0100
)paren
id|dev-&gt;if_port
op_assign
l_int|5
suffix:semicolon
r_else
r_if
c_cond
(paren
id|negotiated
op_amp
l_int|0x0080
)paren
id|dev-&gt;if_port
op_assign
l_int|3
suffix:semicolon
r_else
r_if
c_cond
(paren
id|negotiated
op_amp
l_int|0x0040
)paren
id|dev-&gt;if_port
op_assign
l_int|4
suffix:semicolon
r_else
r_if
c_cond
(paren
id|negotiated
op_amp
l_int|0x0020
)paren
id|dev-&gt;if_port
op_assign
l_int|0
suffix:semicolon
r_else
(brace
id|tp-&gt;nwayset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|csr12
op_amp
l_int|2
)paren
op_eq
l_int|0
op_logical_and
(paren
id|tp-&gt;sym_advertise
op_amp
l_int|0x0180
)paren
)paren
id|dev-&gt;if_port
op_assign
l_int|3
suffix:semicolon
)brace
id|tp-&gt;full_duplex
op_assign
(paren
id|tulip_media_cap
(braket
id|dev-&gt;if_port
)braket
op_amp
id|MediaAlwaysFD
)paren
ques
c_cond
l_int|1
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
(brace
r_if
c_cond
(paren
id|tp-&gt;nwayset
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Switching to %s based on link &quot;
l_string|&quot;negotiation %4.4x &amp; %4.4x = %4.4x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|medianame
(braket
id|dev-&gt;if_port
)braket
comma
id|tp-&gt;sym_advertise
comma
id|tp-&gt;lpar
comma
id|negotiated
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Autonegotiation failed, using %s,&quot;
l_string|&quot; link beat status %4.4x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|medianame
(braket
id|dev-&gt;if_port
)braket
comma
id|csr12
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tp-&gt;mtable
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
id|tp-&gt;mtable-&gt;leafcount
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|tp-&gt;mtable-&gt;mleaf
(braket
id|i
)braket
dot
id|media
op_eq
id|dev-&gt;if_port
)paren
(brace
id|tp-&gt;cur_index
op_assign
id|i
suffix:semicolon
id|tulip_select_media
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
id|setup_done
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|setup_done
)paren
(brace
id|tp-&gt;csr6
op_assign
(paren
id|dev-&gt;if_port
op_amp
l_int|1
ques
c_cond
l_int|0x838E0000
suffix:colon
l_int|0x82420000
)paren
op_or
(paren
id|tp-&gt;csr6
op_amp
l_int|0x20ff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;full_duplex
)paren
id|tp-&gt;csr6
op_or_assign
l_int|0x0200
suffix:semicolon
id|outl
c_func
(paren
l_int|1
comma
id|ioaddr
op_plus
id|CSR13
)paren
suffix:semicolon
)brace
macro_line|#if 0&t;&t;&t;&t;&t;&t;&t;/* Restart shouldn&squot;t be needed. */
id|outl
c_func
(paren
id|tp-&gt;csr6
op_or
id|RxOn
comma
id|ioaddr
op_plus
id|CSR6
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tulip_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s:  Restarting Tx and Rx, CSR5 is %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR5
)paren
)paren
suffix:semicolon
macro_line|#endif
id|tulip_start_rxtx
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
l_int|2
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s:  Setting CSR6 %8.8x/%x CSR12 %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|tp-&gt;csr6
comma
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR6
)paren
comma
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR12
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|tp-&gt;nwayset
op_logical_and
(paren
id|csr5
op_amp
l_int|0x08000000
)paren
op_logical_and
(paren
id|dev-&gt;if_port
op_eq
l_int|3
op_logical_or
id|dev-&gt;if_port
op_eq
l_int|5
)paren
op_logical_and
(paren
id|csr12
op_amp
l_int|2
)paren
op_eq
l_int|2
)paren
op_logical_or
(paren
id|tp-&gt;nway
op_logical_and
(paren
id|csr5
op_amp
(paren
id|TPLnkFail
)paren
)paren
)paren
)paren
(brace
multiline_comment|/* Link blew? Maybe restart NWay. */
id|del_timer_sync
c_func
(paren
op_amp
id|tp-&gt;timer
)paren
suffix:semicolon
id|t21142_start_nway
c_func
(paren
id|dev
)paren
suffix:semicolon
id|tp-&gt;timer.expires
op_assign
id|RUN_AT
c_func
(paren
l_int|3
op_star
id|HZ
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|tp-&gt;timer
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
l_string|&quot;%s: 21143 %s link beat %s.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|medianame
(braket
id|dev-&gt;if_port
)braket
comma
(paren
id|csr12
op_amp
l_int|2
)paren
ques
c_cond
l_string|&quot;failed&quot;
suffix:colon
l_string|&quot;good&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|csr12
op_amp
l_int|2
)paren
op_logical_and
op_logical_neg
id|tp-&gt;medialock
)paren
(brace
id|del_timer_sync
c_func
(paren
op_amp
id|tp-&gt;timer
)paren
suffix:semicolon
id|t21142_start_nway
c_func
(paren
id|dev
)paren
suffix:semicolon
id|tp-&gt;timer.expires
op_assign
id|RUN_AT
c_func
(paren
l_int|3
op_star
id|HZ
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|tp-&gt;timer
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;if_port
op_eq
l_int|5
)paren
id|outl
c_func
(paren
id|inl
c_func
(paren
id|ioaddr
op_plus
id|CSR14
)paren
op_amp
op_complement
l_int|0x080
comma
id|ioaddr
op_plus
id|CSR14
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;if_port
op_eq
l_int|0
op_logical_or
id|dev-&gt;if_port
op_eq
l_int|4
)paren
(brace
r_if
c_cond
(paren
(paren
id|csr12
op_amp
l_int|4
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: 21143 10baseT link beat good.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|csr12
op_amp
l_int|4
)paren
)paren
(brace
multiline_comment|/* 10mbps link beat good. */
r_if
c_cond
(paren
id|tulip_debug
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: 21143 10mbps sensed media.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dev-&gt;if_port
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|tp-&gt;nwayset
)paren
(brace
r_if
c_cond
(paren
id|tulip_debug
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: 21143 using NWay-set %s, csr6 %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|medianame
(braket
id|dev-&gt;if_port
)braket
comma
id|tp-&gt;csr6
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* 100mbps link beat good. */
r_if
c_cond
(paren
id|tulip_debug
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: 21143 100baseTx sensed media.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dev-&gt;if_port
op_assign
l_int|3
suffix:semicolon
id|tp-&gt;csr6
op_assign
l_int|0x838E0000
op_or
(paren
id|tp-&gt;csr6
op_amp
l_int|0x20ff
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0x0003FF7F
comma
id|ioaddr
op_plus
id|CSR14
)paren
suffix:semicolon
id|outl
c_func
(paren
l_int|0x0301
comma
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
id|tulip_restart_rxtx
c_func
(paren
id|tp
)paren
suffix:semicolon
)brace
)brace
eof
