multiline_comment|/*&n;&t;drivers/net/tulip/pnic2.c&n;&n;&t;Maintained by Jeff Garzik &lt;jgarzik@pobox.com&gt;&n;&t;Copyright 2000,2001  The Linux Kernel Team&n;&t;Written/copyright 1994-2001 by Donald Becker.&n;        Modified to hep support PNIC_II by Kevin B. Hendricks&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU General Public License, incorporated herein by reference.&n;&n;&t;Please refer to Documentation/DocBook/tulip-user.{pdf,ps,html}&n;&t;for more information on this driver, or visit the project&n;&t;Web page at http://sourceforge.net/projects/tulip/&n;&n;*/
multiline_comment|/* Understanding the PNIC_II - everything is this file is based&n; * on the PNIC_II_PDF datasheet which is sorely lacking in detail&n; *&n; * As I understand things, here are the registers and bits that&n; * explain the masks and constants used in this file that are&n; * either different from the 21142/3 or important for basic operation.&n; *&n; *&n; * CSR 6  (mask = 0xfe3bd1fd of bits not to change)&n; * -----&n; * Bit 24    - SCR&n; * Bit 23    - PCS&n; * Bit 22    - TTM (Trasmit Threshold Mode)&n; * Bit 18    - Port Select&n; * Bit 13    - Start - 1, Stop - 0 Transmissions&n; * Bit 11:10 - Loop Back Operation Mode&n; * Bit 9     - Full Duplex mode (Advertise 10BaseT-FD is CSR14&lt;7&gt; is set)&n; * Bit 1     - Start - 1, Stop - 0 Receive&n; *&n; *&n; * CSR 14  (mask = 0xfff0ee39 of bits not to change)&n; * ------&n; * Bit 19    - PAUSE-Pause&n; * Bit 18    - Advertise T4&n; * Bit 17    - Advertise 100baseTx-FD&n; * Bit 16    - Advertise 100baseTx-HD&n; * Bit 12    - LTE - Link Test Enable&n; * Bit 7     - ANE - Auto Negotiate Enable&n; * Bit 6     - HDE - Advertise 10baseT-HD&n; * Bit 2     - Reset to Power down - kept as 1 for normal operation&n; * Bit 1     -  Loop Back enable for 10baseT MCC&n; *&n; *&n; * CSR 12&n; * ------&n; * Bit 25    - Partner can do T4&n; * Bit 24    - Partner can do 100baseTx-FD&n; * Bit 23    - Partner can do 100baseTx-HD&n; * Bit 22    - Partner can do 10baseT-FD&n; * Bit 21    - Partner can do 10baseT-HD&n; * Bit 15    - LPN is 1 if all above bits are valid other wise 0&n; * Bit 14:12 - autonegotiation state (write 001 to start autonegotiate)&n; * Bit 3     - Autopolarity state&n; * Bit 2     - LS10B - link state of 10baseT 0 - good, 1 - failed&n; * Bit 1     - LS100B - link state of 100baseT 0 - good, 1- faild&n; *&n; *&n; * Data Port Selection Info&n; *-------------------------&n; *&n; * CSR14&lt;7&gt;   CSR6&lt;18&gt;    CSR6&lt;22&gt;    CSR6&lt;23&gt;    CSR6&lt;24&gt;   MODE/PORT&n; *   1           0           0 (X)       0 (X)       1        NWAY&n; *   0           0           1           0 (X)       0        10baseT&n; *   0           1           0           1           1 (X)    100baseT&n; *&n; *&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;tulip.h&quot;
macro_line|#include &lt;linux/delay.h&gt;
DECL|function|pnic2_timer
r_void
id|pnic2_timer
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
r_void
id|__iomem
op_star
id|ioaddr
op_assign
id|tp-&gt;base_addr
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
id|tulip_debug
OG
l_int|3
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: PNIC2 negotiation status %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
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
r_if
c_cond
(paren
id|next_tick
)paren
(brace
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
)brace
DECL|function|pnic2_start_nway
r_void
id|pnic2_start_nway
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
r_void
id|__iomem
op_star
id|ioaddr
op_assign
id|tp-&gt;base_addr
suffix:semicolon
r_int
id|csr14
suffix:semicolon
r_int
id|csr12
suffix:semicolon
multiline_comment|/* set up what to advertise during the negotiation */
multiline_comment|/* load in csr14  and mask off bits not to touch&n;         * comment at top of file explains mask value&n;         */
id|csr14
op_assign
(paren
id|ioread32
c_func
(paren
id|ioaddr
op_plus
id|CSR14
)paren
op_amp
l_int|0xfff0ee39
)paren
suffix:semicolon
multiline_comment|/* bit 17 - advetise 100baseTx-FD */
r_if
c_cond
(paren
id|tp-&gt;sym_advertise
op_amp
l_int|0x0100
)paren
id|csr14
op_or_assign
l_int|0x00020000
suffix:semicolon
multiline_comment|/* bit 16 - advertise 100baseTx-HD */
r_if
c_cond
(paren
id|tp-&gt;sym_advertise
op_amp
l_int|0x0080
)paren
id|csr14
op_or_assign
l_int|0x00010000
suffix:semicolon
multiline_comment|/* bit 6 - advertise 10baseT-HD */
r_if
c_cond
(paren
id|tp-&gt;sym_advertise
op_amp
l_int|0x0020
)paren
id|csr14
op_or_assign
l_int|0x00000040
suffix:semicolon
multiline_comment|/* Now set bit 12 Link Test Enable, Bit 7 Autonegotiation Enable&n;         * and bit 0 Don&squot;t PowerDown 10baseT&n;         */
id|csr14
op_or_assign
l_int|0x00001184
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
l_string|&quot;%s: Restarting PNIC2 autonegotiation, &quot;
l_string|&quot;csr14=%8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr14
)paren
suffix:semicolon
multiline_comment|/* tell pnic2_lnk_change we are doing an nway negotiation */
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
multiline_comment|/* now we have to set up csr6 for NWAY state */
id|tp-&gt;csr6
op_assign
id|ioread32
c_func
(paren
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
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: On Entry to Nway, &quot;
l_string|&quot;csr6=%8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|tp-&gt;csr6
)paren
suffix:semicolon
multiline_comment|/* mask off any bits not to touch&n;         * comment at top of file explains mask value&n;         */
id|tp-&gt;csr6
op_assign
id|tp-&gt;csr6
op_amp
l_int|0xfe3bd1fd
suffix:semicolon
multiline_comment|/* don&squot;t forget that bit 9 is also used for advertising */
multiline_comment|/* advertise 10baseT-FD for the negotiation (bit 9) */
r_if
c_cond
(paren
id|tp-&gt;sym_advertise
op_amp
l_int|0x0040
)paren
id|tp-&gt;csr6
op_or_assign
l_int|0x00000200
suffix:semicolon
multiline_comment|/* set bit 24 for nway negotiation mode ...&n;         * see Data Port Selection comment at top of file&n;         * and &quot;Stop&quot; - reset both Transmit (bit 13) and Receive (bit 1)&n;         */
id|tp-&gt;csr6
op_or_assign
l_int|0x01000000
suffix:semicolon
id|iowrite32
c_func
(paren
id|csr14
comma
id|ioaddr
op_plus
id|CSR14
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|tp-&gt;csr6
comma
id|ioaddr
op_plus
id|CSR6
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/* all set up so now force the negotiation to begin */
multiline_comment|/* read in current values and mask off all but the&n;&t; * Autonegotiation bits 14:12.  Writing a 001 to those bits&n;         * should start the autonegotiation&n;         */
id|csr12
op_assign
(paren
id|ioread32
c_func
(paren
id|ioaddr
op_plus
id|CSR12
)paren
op_amp
l_int|0xffff8fff
)paren
suffix:semicolon
id|csr12
op_or_assign
l_int|0x1000
suffix:semicolon
id|iowrite32
c_func
(paren
id|csr12
comma
id|ioaddr
op_plus
id|CSR12
)paren
suffix:semicolon
)brace
DECL|function|pnic2_lnk_change
r_void
id|pnic2_lnk_change
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
r_void
id|__iomem
op_star
id|ioaddr
op_assign
id|tp-&gt;base_addr
suffix:semicolon
r_int
id|csr14
suffix:semicolon
multiline_comment|/* read the staus register to find out what is up */
r_int
id|csr12
op_assign
id|ioread32
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
l_string|&quot;%s: PNIC2 link status interrupt %8.8x, &quot;
l_string|&quot; CSR5 %x, %8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr12
comma
id|csr5
comma
id|ioread32
c_func
(paren
id|ioaddr
op_plus
id|CSR14
)paren
)paren
suffix:semicolon
multiline_comment|/* If NWay finished and we have a negotiated partner capability.&n;         * check bits 14:12 for bit pattern 101 - all is good&n;         */
r_if
c_cond
(paren
id|tp-&gt;nway
op_logical_and
op_logical_neg
id|tp-&gt;nwayset
)paren
(brace
multiline_comment|/* we did an auto negotiation */
r_if
c_cond
(paren
(paren
id|csr12
op_amp
l_int|0x7000
)paren
op_eq
l_int|0x5000
)paren
(brace
multiline_comment|/* negotiation ended successfully */
multiline_comment|/* get the link partners reply and mask out all but&n;                        * bits 24-21 which show the partners capabilites&n;                        * and match those to what we advertised&n;                        *&n;                        * then begin to interpret the results of the negotiation.&n;                        * Always go in this order : (we are ignoring T4 for now)&n;                        *     100baseTx-FD, 100baseTx-HD, 10baseT-FD, 10baseT-HD&n;                        */
r_int
id|negotiated
op_assign
(paren
(paren
id|csr12
op_rshift
l_int|16
)paren
op_amp
l_int|0x01E0
)paren
op_amp
id|tp-&gt;sym_advertise
suffix:semicolon
id|tp-&gt;lpar
op_assign
(paren
id|csr12
op_rshift
l_int|16
)paren
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
l_string|&quot;%s: funny autonegotiate result &quot;
l_string|&quot;csr12 %8.8x advertising %4.4x&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr12
comma
id|tp-&gt;sym_advertise
)paren
suffix:semicolon
id|tp-&gt;nwayset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* so check  if 100baseTx link state is okay */
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
multiline_comment|/* now record the duplex that was negotiated */
id|tp-&gt;full_duplex
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;if_port
op_eq
l_int|4
)paren
op_logical_or
(paren
id|dev-&gt;if_port
op_eq
l_int|5
)paren
)paren
id|tp-&gt;full_duplex
op_assign
l_int|1
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
)brace
multiline_comment|/* remember to turn off bit 7 - autonegotiate&n;                         * enable so we can properly end nway mode and&n;                         * set duplex (ie. use csr6&lt;9&gt; again)&n;                         */
id|csr14
op_assign
(paren
id|ioread32
c_func
(paren
id|ioaddr
op_plus
id|CSR14
)paren
op_amp
l_int|0xffffff7f
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|csr14
comma
id|ioaddr
op_plus
id|CSR14
)paren
suffix:semicolon
multiline_comment|/* now set the data port and operating mode&n;&t;&t;&t; * (see the Data Port Selection comments at&n;&t;&t;&t; * the top of the file&n;&t;&t;&t; */
multiline_comment|/* get current csr6 and mask off bits not to touch */
multiline_comment|/* see comment at top of file */
id|tp-&gt;csr6
op_assign
(paren
id|ioread32
c_func
(paren
id|ioaddr
op_plus
id|CSR6
)paren
op_amp
l_int|0xfe3bd1fd
)paren
suffix:semicolon
multiline_comment|/* so if using if_port 3 or 5 then select the 100baseT&n;&t;&t;&t; * port else select the 10baseT port.&n;&t;&t;&t; * See the Data Port Selection table at the top&n;&t;&t;&t; * of the file which was taken from the PNIC_II.PDF&n;&t;&t;&t; * datasheet&n;&t;&t;&t; */
r_if
c_cond
(paren
id|dev-&gt;if_port
op_amp
l_int|1
)paren
id|tp-&gt;csr6
op_or_assign
l_int|0x01840000
suffix:semicolon
r_else
id|tp-&gt;csr6
op_or_assign
l_int|0x00400000
suffix:semicolon
multiline_comment|/* now set the full duplex bit appropriately */
r_if
c_cond
(paren
id|tp-&gt;full_duplex
)paren
id|tp-&gt;csr6
op_or_assign
l_int|0x00000200
suffix:semicolon
id|iowrite32
c_func
(paren
l_int|1
comma
id|ioaddr
op_plus
id|CSR13
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
l_string|&quot;%s:  Setting CSR6 %8.8x/%x CSR12 &quot;
l_string|&quot;%8.8x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|tp-&gt;csr6
comma
id|ioread32
c_func
(paren
id|ioaddr
op_plus
id|CSR6
)paren
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
multiline_comment|/* now the following actually writes out the&n;&t;&t;&t; * new csr6 values&n;&t;&t;&t; */
id|tulip_start_rxtx
c_func
(paren
id|tp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Autonegotiation failed, &quot;
l_string|&quot;using %s, link beat status %4.4x.&bslash;n&quot;
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
multiline_comment|/* remember to turn off bit 7 - autonegotiate&n;                         * enable so we don&squot;t forget&n;                         */
id|csr14
op_assign
(paren
id|ioread32
c_func
(paren
id|ioaddr
op_plus
id|CSR14
)paren
op_amp
l_int|0xffffff7f
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|csr14
comma
id|ioaddr
op_plus
id|CSR14
)paren
suffix:semicolon
multiline_comment|/* what should we do when autonegotiate fails?&n;                         * should we try again or default to baseline&n;                         * case.  I just don&squot;t know.&n;                         *&n;                         * for now default to some baseline case&n;                         */
id|dev-&gt;if_port
op_assign
l_int|0
suffix:semicolon
id|tp-&gt;nway
op_assign
l_int|0
suffix:semicolon
id|tp-&gt;nwayset
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* set to 10baseTx-HD - see Data Port Selection&n;                          * comment given at the top of the file&n;                          */
id|tp-&gt;csr6
op_assign
(paren
id|ioread32
c_func
(paren
id|ioaddr
op_plus
id|CSR6
)paren
op_amp
l_int|0xfe3bd1fd
)paren
suffix:semicolon
id|tp-&gt;csr6
op_or_assign
l_int|0x00400000
suffix:semicolon
id|tulip_restart_rxtx
c_func
(paren
id|tp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
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
l_string|&quot;%s: Ugh! Link blew?&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|tp-&gt;timer
)paren
suffix:semicolon
id|pnic2_start_nway
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
r_return
suffix:semicolon
)brace
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
multiline_comment|/* we are at 100mb and a potential link change occurred */
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
l_string|&quot;%s: PNIC2 %s link beat %s.&bslash;n&quot;
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
multiline_comment|/* check 100 link beat */
id|tp-&gt;nway
op_assign
l_int|0
suffix:semicolon
id|tp-&gt;nwayset
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* if failed then try doing an nway to get in sync */
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
id|pnic2_start_nway
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
r_return
suffix:semicolon
)brace
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
multiline_comment|/* we are at 10mb and a potential link change occurred */
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
l_string|&quot;%s: PNIC2 %s link beat %s.&bslash;n&quot;
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
l_int|4
)paren
ques
c_cond
l_string|&quot;failed&quot;
suffix:colon
l_string|&quot;good&quot;
)paren
suffix:semicolon
id|tp-&gt;nway
op_assign
l_int|0
suffix:semicolon
id|tp-&gt;nwayset
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* if failed, try doing an nway to get in sync */
r_if
c_cond
(paren
(paren
id|csr12
op_amp
l_int|4
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
id|pnic2_start_nway
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
r_return
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
l_string|&quot;%s: PNIC2 Link Change Default?&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
multiline_comment|/* if all else fails default to trying 10baseT-HD */
id|dev-&gt;if_port
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* make sure autonegotiate enable is off */
id|csr14
op_assign
(paren
id|ioread32
c_func
(paren
id|ioaddr
op_plus
id|CSR14
)paren
op_amp
l_int|0xffffff7f
)paren
suffix:semicolon
id|iowrite32
c_func
(paren
id|csr14
comma
id|ioaddr
op_plus
id|CSR14
)paren
suffix:semicolon
multiline_comment|/* set to 10baseTx-HD - see Data Port Selection&n;         * comment given at the top of the file&n;         */
id|tp-&gt;csr6
op_assign
(paren
id|ioread32
c_func
(paren
id|ioaddr
op_plus
id|CSR6
)paren
op_amp
l_int|0xfe3bd1fd
)paren
suffix:semicolon
id|tp-&gt;csr6
op_or_assign
l_int|0x00400000
suffix:semicolon
id|tulip_restart_rxtx
c_func
(paren
id|tp
)paren
suffix:semicolon
)brace
eof
