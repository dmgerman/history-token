multiline_comment|/* bionet.c     BioNet-100 device driver for linux68k.&n; *&n; * Version:&t;@(#)bionet.c&t;1.0&t;02/06/96&n; *&n; * Author:&t;Hartmut Laue &lt;laue@ifk-mp.uni-kiel.de&gt;&n; * and&t;&t;Torsten Narjes &lt;narjes@ifk-mp.uni-kiel.de&gt;&n; *&n; * Little adaptions for integration into pl7 by Roman Hodek&n; *&n; * Some changes in bionet_poll_rx by Karl-Heinz Lohner&n; *&n;&t;What is it ?&n;&t;------------&n;&t;This driver controls the BIONET-100 LAN-Adapter which connects&n;&t;an ATARI ST/TT via the ACSI-port to an Ethernet-based network.&n;&n;&t;This version can be compiled as a loadable module (See the&n;&t;compile command at the bottom of this file).&n;&t;At load time, you can optionally set the debugging level and the&n;&t;fastest response time on the command line of &squot;insmod&squot;.&n;&n;&t;&squot;bionet_debug&squot;&n;&t;&t;controls the amount of diagnostic messages:&n;&t;  0  : no messages&n;&t;  &gt;0 : see code for meaning of printed messages&n;&n;&t;&squot;bionet_min_poll_time&squot; (always &gt;=1)&n;&t;&t;gives the time (in jiffies) between polls. Low values&n;&t;&t;increase the system load (beware!)&n;&n;&t;When loaded, a net device with the name &squot;bio0&squot; becomes available,&n;&t;which can be controlled with the usual &squot;ifconfig&squot; command.&n;&n;&t;It is possible to compile this driver into the kernel like other&n;&t;(net) drivers. For this purpose, some source files (e.g. config-files&n;&t;makefiles, Space.c) must be changed accordingly. (You may refer to&n;&t;other drivers how to do it.) In this case, the device will be detected&n;&t;at boot time and (probably) appear as &squot;eth0&squot;.&n;&n;&t;This code is based on several sources:&n;&t;- The driver code for a parallel port ethernet adapter by&n;&t;  Donald Becker (see file &squot;atp.c&squot; from the PC linux distribution)&n;&t;- The ACSI code by Roman Hodek for the ATARI-ACSI harddisk support&n;&t;  and DMA handling.&n;&t;- Very limited information about moving packets in and out of the&n;&t;  BIONET-adapter from the TCP package for TOS by BioData GmbH.&n;&n;&t;Theory of Operation&n;&t;-------------------&n;&t;Because the ATARI DMA port is usually shared between several&n;&t;devices (eg. harddisk, floppy) we cannot block the ACSI bus&n;&t;while waiting for interrupts. Therefore we use a polling mechanism&n;&t;to fetch packets from the adapter. For the same reason, we send&n;&t;packets without checking that the previous packet has been sent to&n;&t;the LAN. We rely on the higher levels of the networking code to detect&n;&t;missing packets and resend them.&n;&n;&t;Before we access the ATARI DMA controller, we check if another&n;&t;process is using the DMA. If not, we lock the DMA, perform one or&n;&t;more packet transfers and unlock the DMA before returning.&n;&t;We do not use &squot;stdma_lock&squot; unconditionally because it is unclear&n;&t;if the networking code can be set to sleep, which will happen if&n;&t;another (possibly slow) device is using the DMA controller.&n;&n;&t;The polling is done via timer interrupts which periodically&n;&t;&squot;simulate&squot; an interrupt from the Ethernet adapter. The time (in jiffies)&n;&t;between polls varies depending on an estimate of the net activity.&n;&t;The allowed range is given by the variable &squot;bionet_min_poll_time&squot;&n;&t;for the lower (fastest) limit and the constant &squot;MAX_POLL_TIME&squot;&n;&t;for the higher (slowest) limit.&n;&n;&t;Whenever a packet arrives, we switch to fastest response by setting&n;&t;the polling time to its lowest limit. If the following poll fails,&n;&t;because no packets have arrived, we increase the time for the next&n;&t;poll. When the net activity is low, the polling time effectively&n;&t;stays at its maximum value, resulting in the lowest load for the&n;&t;machine.&n; */
DECL|macro|MAX_POLL_TIME
mdefine_line|#define MAX_POLL_TIME&t;10
DECL|variable|version
r_static
r_char
id|version
(braket
)braket
op_assign
l_string|&quot;bionet.c:v1.0 06-feb-96 (c) Hartmut Laue.&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/atariints.h&gt;
macro_line|#include &lt;asm/atari_acsi.h&gt;
macro_line|#include &lt;asm/atari_stdma.h&gt;
r_extern
r_struct
id|net_device
op_star
id|init_etherdev
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|sizeof_private
)paren
suffix:semicolon
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug&n; */
macro_line|#ifndef NET_DEBUG
DECL|macro|NET_DEBUG
mdefine_line|#define NET_DEBUG 0
macro_line|#endif
multiline_comment|/*&n; * Global variable &squot;bionet_debug&squot;. Can be set at load time by &squot;insmod&squot;&n; */
DECL|variable|bionet_debug
r_int
r_int
id|bionet_debug
op_assign
id|NET_DEBUG
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|bionet_debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|bionet_debug
comma
l_string|&quot;bionet debug level (0-2)&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|bionet_min_poll_time
r_static
r_int
r_int
id|bionet_min_poll_time
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* Information that need to be kept for each board.&n; */
DECL|struct|net_local
r_struct
id|net_local
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|open_time
r_int
id|open_time
suffix:semicolon
multiline_comment|/* for debugging */
DECL|member|poll_time
r_int
id|poll_time
suffix:semicolon
multiline_comment|/* polling time varies with net load */
)brace
suffix:semicolon
DECL|struct|nic_pkt_s
r_static
r_struct
id|nic_pkt_s
(brace
multiline_comment|/* packet format */
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
DECL|member|dummy
r_int
r_char
id|dummy
suffix:semicolon
DECL|member|l_lo
DECL|member|l_hi
r_int
r_char
id|l_lo
comma
id|l_hi
suffix:semicolon
DECL|member|buffer
r_int
r_char
id|buffer
(braket
l_int|3000
)braket
suffix:semicolon
DECL|variable|nic_packet
)brace
op_star
id|nic_packet
suffix:semicolon
DECL|variable|phys_nic_packet
r_int
r_char
op_star
id|phys_nic_packet
suffix:semicolon
multiline_comment|/* Index to functions, as function prototypes.&n; */
r_extern
r_int
id|bionet_probe
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
id|bionet_open
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
id|bionet_send_packet
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|bionet_poll_rx
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_static
r_int
id|bionet_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device_stats
op_star
id|net_get_stats
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
id|bionet_tick
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|variable|bionet_timer
r_static
r_struct
id|timer_list
id|bionet_timer
op_assign
(brace
id|function
suffix:colon
id|bionet_tick
)brace
suffix:semicolon
DECL|macro|STRAM_ADDR
mdefine_line|#define STRAM_ADDR(a)&t;(((a) &amp; 0xff000000) == 0)
multiline_comment|/* The following routines access the ethernet board connected to the&n; * ACSI port via the st_dma chip.&n; */
DECL|macro|NODE_ADR
mdefine_line|#define NODE_ADR 0x60
DECL|macro|C_READ
mdefine_line|#define C_READ 8
DECL|macro|C_WRITE
mdefine_line|#define C_WRITE 0x0a
DECL|macro|C_GETEA
mdefine_line|#define C_GETEA 0x0f
DECL|macro|C_SETCR
mdefine_line|#define C_SETCR 0x0e
r_static
r_int
DECL|function|sendcmd
id|sendcmd
c_func
(paren
r_int
r_int
id|a0
comma
r_int
r_int
id|mod
comma
r_int
r_int
id|cmd
)paren
(brace
r_int
r_int
id|c
suffix:semicolon
id|dma_wd.dma_mode_status
op_assign
(paren
id|mod
op_or
(paren
(paren
id|a0
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
op_or
l_int|0x88
)paren
suffix:semicolon
id|dma_wd.fdc_acces_seccount
op_assign
id|cmd
suffix:semicolon
id|dma_wd.dma_mode_status
op_assign
(paren
id|mod
op_or
l_int|0x8a
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acsi_wait_for_IRQ
c_func
(paren
id|HZ
op_div
l_int|2
)paren
)paren
(brace
multiline_comment|/* wait for cmd ack */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* timeout */
id|c
op_assign
id|dma_wd.fdc_acces_seccount
suffix:semicolon
r_return
(paren
id|c
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|set_status
id|set_status
c_func
(paren
r_int
id|cr
)paren
(brace
id|sendcmd
c_func
(paren
l_int|0
comma
l_int|0x100
comma
id|NODE_ADR
op_or
id|C_SETCR
)paren
suffix:semicolon
multiline_comment|/* CMD: SET CR */
id|sendcmd
c_func
(paren
l_int|1
comma
l_int|0x100
comma
id|cr
)paren
suffix:semicolon
id|dma_wd.dma_mode_status
op_assign
l_int|0x80
suffix:semicolon
)brace
r_static
r_int
DECL|function|get_status
id|get_status
c_func
(paren
r_int
r_char
op_star
id|adr
)paren
(brace
r_int
id|i
comma
id|c
suffix:semicolon
id|DISABLE_IRQ
c_func
(paren
)paren
suffix:semicolon
id|c
op_assign
id|sendcmd
c_func
(paren
l_int|0
comma
l_int|0x00
comma
id|NODE_ADR
op_or
id|C_GETEA
)paren
suffix:semicolon
multiline_comment|/* CMD: GET ETH ADR*/
r_if
c_cond
(paren
id|c
OL
l_int|0
)paren
(brace
r_goto
id|gsend
suffix:semicolon
)brace
multiline_comment|/* now read status bytes */
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
id|dma_wd.fdc_acces_seccount
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* request next byte */
r_if
c_cond
(paren
op_logical_neg
id|acsi_wait_for_IRQ
c_func
(paren
id|HZ
op_div
l_int|2
)paren
)paren
(brace
multiline_comment|/* wait for cmd ack */
id|c
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|gsend
suffix:semicolon
multiline_comment|/* timeout */
)brace
id|c
op_assign
id|dma_wd.fdc_acces_seccount
suffix:semicolon
op_star
id|adr
op_increment
op_assign
(paren
r_int
r_char
)paren
id|c
suffix:semicolon
)brace
id|c
op_assign
l_int|1
suffix:semicolon
id|gsend
suffix:colon
id|dma_wd.dma_mode_status
op_assign
l_int|0x80
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
r_static
r_void
DECL|function|bionet_intr
id|bionet_intr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|data
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_return
suffix:semicolon
)brace
r_static
r_int
DECL|function|get_frame
id|get_frame
c_func
(paren
r_int
r_int
id|paddr
comma
r_int
id|odd
)paren
(brace
r_int
id|c
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|DISABLE_IRQ
c_func
(paren
)paren
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
id|dma_wd.dma_mode_status
op_assign
l_int|0x9a
suffix:semicolon
id|dma_wd.dma_mode_status
op_assign
l_int|0x19a
suffix:semicolon
id|dma_wd.dma_mode_status
op_assign
l_int|0x9a
suffix:semicolon
id|dma_wd.fdc_acces_seccount
op_assign
l_int|0x04
suffix:semicolon
multiline_comment|/* sector count (was 5) */
id|dma_wd.dma_lo
op_assign
(paren
r_int
r_char
)paren
id|paddr
suffix:semicolon
id|paddr
op_rshift_assign
l_int|8
suffix:semicolon
id|dma_wd.dma_md
op_assign
(paren
r_int
r_char
)paren
id|paddr
suffix:semicolon
id|paddr
op_rshift_assign
l_int|8
suffix:semicolon
id|dma_wd.dma_hi
op_assign
(paren
r_int
r_char
)paren
id|paddr
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|c
op_assign
id|sendcmd
c_func
(paren
l_int|0
comma
l_int|0x00
comma
id|NODE_ADR
op_or
id|C_READ
)paren
suffix:semicolon
multiline_comment|/* CMD: READ */
r_if
c_cond
(paren
id|c
OL
l_int|128
)paren
(brace
r_goto
id|rend
suffix:semicolon
)brace
multiline_comment|/* now read block */
id|c
op_assign
id|sendcmd
c_func
(paren
l_int|1
comma
l_int|0x00
comma
id|odd
)paren
suffix:semicolon
multiline_comment|/* odd flag for address shift */
id|dma_wd.dma_mode_status
op_assign
l_int|0x0a
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acsi_wait_for_IRQ
c_func
(paren
l_int|100
)paren
)paren
(brace
multiline_comment|/* wait for DMA to complete */
id|c
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|rend
suffix:semicolon
)brace
id|dma_wd.dma_mode_status
op_assign
l_int|0x8a
suffix:semicolon
id|dma_wd.dma_mode_status
op_assign
l_int|0x18a
suffix:semicolon
id|dma_wd.dma_mode_status
op_assign
l_int|0x8a
suffix:semicolon
id|c
op_assign
id|dma_wd.fdc_acces_seccount
suffix:semicolon
id|dma_wd.dma_mode_status
op_assign
l_int|0x88
suffix:semicolon
id|c
op_assign
id|dma_wd.fdc_acces_seccount
suffix:semicolon
id|c
op_assign
l_int|1
suffix:semicolon
id|rend
suffix:colon
id|dma_wd.dma_mode_status
op_assign
l_int|0x80
suffix:semicolon
id|udelay
c_func
(paren
l_int|40
)paren
suffix:semicolon
id|acsi_wait_for_noIRQ
c_func
(paren
l_int|20
)paren
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
r_static
r_int
DECL|function|hardware_send_packet
id|hardware_send_packet
c_func
(paren
r_int
r_int
id|paddr
comma
r_int
id|cnt
)paren
(brace
r_int
r_int
id|c
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|DISABLE_IRQ
c_func
(paren
)paren
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
id|dma_wd.dma_mode_status
op_assign
l_int|0x19a
suffix:semicolon
id|dma_wd.dma_mode_status
op_assign
l_int|0x9a
suffix:semicolon
id|dma_wd.dma_mode_status
op_assign
l_int|0x19a
suffix:semicolon
id|dma_wd.dma_lo
op_assign
(paren
r_int
r_char
)paren
id|paddr
suffix:semicolon
id|paddr
op_rshift_assign
l_int|8
suffix:semicolon
id|dma_wd.dma_md
op_assign
(paren
r_int
r_char
)paren
id|paddr
suffix:semicolon
id|paddr
op_rshift_assign
l_int|8
suffix:semicolon
id|dma_wd.dma_hi
op_assign
(paren
r_int
r_char
)paren
id|paddr
suffix:semicolon
id|dma_wd.fdc_acces_seccount
op_assign
l_int|0x4
suffix:semicolon
multiline_comment|/* sector count */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|c
op_assign
id|sendcmd
c_func
(paren
l_int|0
comma
l_int|0x100
comma
id|NODE_ADR
op_or
id|C_WRITE
)paren
suffix:semicolon
multiline_comment|/* CMD: WRITE */
id|c
op_assign
id|sendcmd
c_func
(paren
l_int|1
comma
l_int|0x100
comma
id|cnt
op_amp
l_int|0xff
)paren
suffix:semicolon
id|c
op_assign
id|sendcmd
c_func
(paren
l_int|1
comma
l_int|0x100
comma
id|cnt
op_rshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* now write block */
id|dma_wd.dma_mode_status
op_assign
l_int|0x10a
suffix:semicolon
multiline_comment|/* DMA enable */
r_if
c_cond
(paren
op_logical_neg
id|acsi_wait_for_IRQ
c_func
(paren
l_int|100
)paren
)paren
(brace
multiline_comment|/* wait for DMA to complete */
r_goto
id|end
suffix:semicolon
)brace
id|dma_wd.dma_mode_status
op_assign
l_int|0x19a
suffix:semicolon
multiline_comment|/* DMA disable ! */
id|c
op_assign
id|dma_wd.fdc_acces_seccount
suffix:semicolon
id|end
suffix:colon
id|c
op_assign
id|sendcmd
c_func
(paren
l_int|1
comma
l_int|0x100
comma
l_int|0
)paren
suffix:semicolon
id|c
op_assign
id|sendcmd
c_func
(paren
l_int|1
comma
l_int|0x100
comma
l_int|0
)paren
suffix:semicolon
id|dma_wd.dma_mode_status
op_assign
l_int|0x180
suffix:semicolon
id|udelay
c_func
(paren
l_int|40
)paren
suffix:semicolon
id|acsi_wait_for_noIRQ
c_func
(paren
l_int|20
)paren
suffix:semicolon
r_return
id|c
op_amp
l_int|0x02
suffix:semicolon
)brace
multiline_comment|/* Check for a network adaptor of this type, and return &squot;0&squot; if one exists.&n; */
r_int
id|__init
DECL|function|bionet_probe
(def_block
id|bionet_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_char
id|station_addr
(braket
l_int|6
)braket
suffix:semicolon
r_static
r_int
id|version_printed
suffix:semicolon
r_static
r_int
id|no_more_found
suffix:semicolon
multiline_comment|/* avoid &quot;Probing for...&quot; printed 4 times */
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_ATARI
op_logical_or
id|no_more_found
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Probing for BioNet 100 Adapter...&bslash;n&quot;
)paren
suffix:semicolon
id|stdma_lock
c_func
(paren
id|bionet_intr
comma
l_int|NULL
)paren
suffix:semicolon
id|i
op_assign
id|get_status
c_func
(paren
id|station_addr
)paren
suffix:semicolon
multiline_comment|/* Read the station address PROM.  */
id|ENABLE_IRQ
c_func
(paren
)paren
suffix:semicolon
id|stdma_release
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Check the first three octets of the S.A. for the manufactor&squot;s code.&n;&t; */
r_if
c_cond
(paren
id|i
OL
l_int|0
op_logical_or
id|station_addr
(braket
l_int|0
)braket
op_ne
l_char|&squot;B&squot;
op_logical_or
id|station_addr
(braket
l_int|1
)braket
op_ne
l_char|&squot;I&squot;
op_logical_or
id|station_addr
(braket
l_int|2
)braket
op_ne
l_char|&squot;O&squot;
)paren
(brace
id|no_more_found
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;No BioNet 100 found.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bionet_debug
OG
l_int|0
op_logical_and
id|version_printed
op_increment
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|version
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %s found, eth-addr: %02x-%02x-%02x:%02x-%02x-%02x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
l_string|&quot;BioNet 100&quot;
comma
id|station_addr
(braket
l_int|0
)braket
comma
id|station_addr
(braket
l_int|1
)braket
comma
id|station_addr
(braket
l_int|2
)braket
comma
id|station_addr
(braket
l_int|3
)braket
comma
id|station_addr
(braket
l_int|4
)braket
comma
id|station_addr
(braket
l_int|5
)braket
)paren
suffix:semicolon
multiline_comment|/* Initialize the device structure. */
id|nic_packet
op_assign
(paren
r_struct
id|nic_pkt_s
op_star
)paren
id|acsi_buffer
suffix:semicolon
id|phys_nic_packet
op_assign
(paren
r_int
r_char
op_star
)paren
id|phys_acsi_buffer
suffix:semicolon
r_if
c_cond
(paren
id|bionet_debug
OG
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nic_packet at 0x%p, phys at 0x%p&bslash;n&quot;
comma
id|nic_packet
comma
id|phys_nic_packet
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;priv
op_eq
l_int|NULL
)paren
id|dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|net_local
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
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
id|net_local
)paren
)paren
suffix:semicolon
id|dev-&gt;open
op_assign
id|bionet_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|bionet_close
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|bionet_send_packet
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|net_get_stats
suffix:semicolon
multiline_comment|/* Fill in the fields of the device structure with ethernet-generic&n;&t; * values. This should be in a common file instead of per-driver.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ETH_ALEN
suffix:semicolon
id|i
op_increment
)paren
(brace
macro_line|#if 0
id|dev-&gt;broadcast
(braket
id|i
)braket
op_assign
l_int|0xff
suffix:semicolon
macro_line|#endif
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|station_addr
(braket
id|i
)braket
suffix:semicolon
)brace
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)def_block
multiline_comment|/* Open/initialize the board.  This is called (in the current kernel)&n;   sometime after booting when the &squot;ifconfig&squot; program is run.&n;&n;   This routine should set everything up anew at each open, even&n;   registers that &quot;should&quot; only need to be set once at boot, so that&n;   there is non-reboot way to recover if something goes wrong.&n; */
r_static
r_int
DECL|function|bionet_open
id|bionet_open
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
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|bionet_debug
OG
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;bionet_open&bslash;n&quot;
)paren
suffix:semicolon
id|stdma_lock
c_func
(paren
id|bionet_intr
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Reset the hardware here.&n;&t; */
id|set_status
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|lp-&gt;open_time
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*jiffies*/
id|lp-&gt;poll_time
op_assign
id|MAX_POLL_TIME
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|1
suffix:semicolon
id|stdma_release
c_func
(paren
)paren
suffix:semicolon
id|bionet_timer.data
op_assign
(paren
r_int
)paren
id|dev
suffix:semicolon
id|bionet_timer.expires
op_assign
id|jiffies
op_plus
id|lp-&gt;poll_time
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|bionet_timer
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|bionet_send_packet
id|bionet_send_packet
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
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
id|flags
suffix:semicolon
multiline_comment|/* Block a timer-based transmit from overlapping.  This could better be&n;&t; * done with atomic_swap(1, dev-&gt;tbusy), but set_bit() works as well.&n;&t; */
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
id|stdma_islocked
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|lp-&gt;stats.tx_errors
op_increment
suffix:semicolon
)brace
r_else
(brace
r_int
id|length
op_assign
id|ETH_ZLEN
OL
id|skb-&gt;len
ques
c_cond
id|skb-&gt;len
suffix:colon
id|ETH_ZLEN
suffix:semicolon
r_int
r_int
id|buf
op_assign
id|virt_to_phys
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
r_int
id|stat
suffix:semicolon
id|stdma_lock
c_func
(paren
id|bionet_intr
comma
l_int|NULL
)paren
suffix:semicolon
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
id|STRAM_ADDR
c_func
(paren
id|buf
op_plus
id|length
op_minus
l_int|1
)paren
)paren
(brace
id|memcpy
c_func
(paren
id|nic_packet-&gt;buffer
comma
id|skb-&gt;data
comma
id|length
)paren
suffix:semicolon
id|buf
op_assign
(paren
r_int
r_int
)paren
op_amp
(paren
(paren
r_struct
id|nic_pkt_s
op_star
)paren
id|phys_nic_packet
)paren
op_member_access_from_pointer
id|buffer
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bionet_debug
OG
l_int|1
)paren
(brace
id|u_char
op_star
id|data
op_assign
id|nic_packet-&gt;buffer
comma
op_star
id|p
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: TX pkt type 0x%4x from &quot;
comma
id|dev-&gt;name
comma
(paren
(paren
id|u_short
op_star
)paren
id|data
)paren
(braket
l_int|6
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|data
(braket
l_int|6
)braket
comma
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
id|printk
c_func
(paren
l_string|&quot;%02x%s&quot;
comma
op_star
id|p
op_increment
comma
id|i
op_ne
l_int|5
ques
c_cond
l_string|&quot;:&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; to &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|data
comma
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
id|printk
c_func
(paren
l_string|&quot;%02x%s&quot;
comma
op_star
id|p
op_increment
comma
id|i
op_ne
l_int|5
ques
c_cond
l_string|&quot;:&quot;
suffix:colon
l_string|&quot;&quot;
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s: &quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; data %02x%02x %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x&quot;
l_string|&quot; %02x%02x%02x%02x len %d&bslash;n&quot;
comma
id|data
(braket
l_int|12
)braket
comma
id|data
(braket
l_int|13
)braket
comma
id|data
(braket
l_int|14
)braket
comma
id|data
(braket
l_int|15
)braket
comma
id|data
(braket
l_int|16
)braket
comma
id|data
(braket
l_int|17
)braket
comma
id|data
(braket
l_int|18
)braket
comma
id|data
(braket
l_int|19
)braket
comma
id|data
(braket
l_int|20
)braket
comma
id|data
(braket
l_int|21
)braket
comma
id|data
(braket
l_int|22
)braket
comma
id|data
(braket
l_int|23
)braket
comma
id|data
(braket
l_int|24
)braket
comma
id|data
(braket
l_int|25
)braket
comma
id|data
(braket
l_int|26
)braket
comma
id|data
(braket
l_int|27
)braket
comma
id|data
(braket
l_int|28
)braket
comma
id|data
(braket
l_int|29
)braket
comma
id|data
(braket
l_int|30
)braket
comma
id|data
(braket
l_int|31
)braket
comma
id|data
(braket
l_int|32
)braket
comma
id|data
(braket
l_int|33
)braket
comma
id|length
)paren
suffix:semicolon
)brace
id|dma_cache_maintenance
c_func
(paren
id|buf
comma
id|length
comma
l_int|1
)paren
suffix:semicolon
id|stat
op_assign
id|hardware_send_packet
c_func
(paren
id|buf
comma
id|length
)paren
suffix:semicolon
id|ENABLE_IRQ
c_func
(paren
)paren
suffix:semicolon
id|stdma_release
c_func
(paren
)paren
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;stats.tx_packets
op_increment
suffix:semicolon
id|lp-&gt;stats.tx_bytes
op_add_assign
id|length
suffix:semicolon
)brace
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* We have a good packet(s), get it/them out of the buffers.&n; */
r_static
r_void
DECL|function|bionet_poll_rx
id|bionet_poll_rx
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
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|boguscount
op_assign
l_int|10
suffix:semicolon
r_int
id|pkt_len
comma
id|status
suffix:semicolon
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
multiline_comment|/* ++roman: Take care at locking the ST-DMA... This must be done with ints&n;&t; * off, since otherwise an int could slip in between the question and the&n;&t; * locking itself, and then we&squot;d go to sleep... And locking itself is&n;&t; * necessary to keep the floppy_change timer from working with ST-DMA&n;&t; * registers. */
r_if
c_cond
(paren
id|stdma_islocked
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|stdma_lock
c_func
(paren
id|bionet_intr
comma
l_int|NULL
)paren
suffix:semicolon
id|DISABLE_IRQ
c_func
(paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;poll_time
OL
id|MAX_POLL_TIME
)paren
(brace
id|lp-&gt;poll_time
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|boguscount
op_decrement
)paren
(brace
id|status
op_assign
id|get_frame
c_func
(paren
(paren
r_int
r_int
)paren
id|phys_nic_packet
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/* Good packet... */
id|dma_cache_maintenance
c_func
(paren
(paren
r_int
r_int
)paren
id|phys_nic_packet
comma
l_int|1520
comma
l_int|0
)paren
suffix:semicolon
id|pkt_len
op_assign
(paren
id|nic_packet-&gt;l_hi
op_lshift
l_int|8
)paren
op_or
id|nic_packet-&gt;l_lo
suffix:semicolon
id|lp-&gt;poll_time
op_assign
id|bionet_min_poll_time
suffix:semicolon
multiline_comment|/* fast poll */
r_if
c_cond
(paren
id|pkt_len
op_ge
l_int|60
op_logical_and
id|pkt_len
op_le
l_int|1520
)paren
(brace
multiline_comment|/*&t;^^^^ war 1514  KHL */
multiline_comment|/* Malloc up new buffer.&n;&t;&t;&t; */
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|pkt_len
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Memory squeeze, dropping packet.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|lp-&gt;stats.rx_dropped
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* 16 Byte align  */
id|skb_put
c_func
(paren
id|skb
comma
id|pkt_len
)paren
suffix:semicolon
multiline_comment|/* make room */
multiline_comment|/* &squot;skb-&gt;data&squot; points to the start of sk_buff data area.&n;&t;&t;&t; */
id|memcpy
c_func
(paren
id|skb-&gt;data
comma
id|nic_packet-&gt;buffer
comma
id|pkt_len
)paren
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|eth_type_trans
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|dev-&gt;last_rx
op_assign
id|jiffies
suffix:semicolon
id|lp-&gt;stats.rx_packets
op_increment
suffix:semicolon
id|lp-&gt;stats.rx_bytes
op_add_assign
id|pkt_len
suffix:semicolon
multiline_comment|/* If any worth-while packets have been received, dev_rint()&n;&t;   has done a mark_bh(INET_BH) for us and will work on them&n;&t;   when we get to the bottom-half routine.&n;&t; */
r_if
c_cond
(paren
id|bionet_debug
OG
l_int|1
)paren
(brace
id|u_char
op_star
id|data
op_assign
id|nic_packet-&gt;buffer
comma
op_star
id|p
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: RX pkt type 0x%4x from &quot;
comma
id|dev-&gt;name
comma
(paren
(paren
id|u_short
op_star
)paren
id|data
)paren
(braket
l_int|6
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|data
(braket
l_int|6
)braket
comma
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
id|printk
c_func
(paren
l_string|&quot;%02x%s&quot;
comma
op_star
id|p
op_increment
comma
id|i
op_ne
l_int|5
ques
c_cond
l_string|&quot;:&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; to &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|data
comma
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
id|printk
c_func
(paren
l_string|&quot;%02x%s&quot;
comma
op_star
id|p
op_increment
comma
id|i
op_ne
l_int|5
ques
c_cond
l_string|&quot;:&quot;
suffix:colon
l_string|&quot;&quot;
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s: &quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; data %02x%02x %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x&quot;
l_string|&quot; %02x%02x%02x%02x len %d&bslash;n&quot;
comma
id|data
(braket
l_int|12
)braket
comma
id|data
(braket
l_int|13
)braket
comma
id|data
(braket
l_int|14
)braket
comma
id|data
(braket
l_int|15
)braket
comma
id|data
(braket
l_int|16
)braket
comma
id|data
(braket
l_int|17
)braket
comma
id|data
(braket
l_int|18
)braket
comma
id|data
(braket
l_int|19
)braket
comma
id|data
(braket
l_int|20
)braket
comma
id|data
(braket
l_int|21
)braket
comma
id|data
(braket
l_int|22
)braket
comma
id|data
(braket
l_int|23
)braket
comma
id|data
(braket
l_int|24
)braket
comma
id|data
(braket
l_int|25
)braket
comma
id|data
(braket
l_int|26
)braket
comma
id|data
(braket
l_int|27
)braket
comma
id|data
(braket
l_int|28
)braket
comma
id|data
(braket
l_int|29
)braket
comma
id|data
(braket
l_int|30
)braket
comma
id|data
(braket
l_int|31
)braket
comma
id|data
(braket
l_int|32
)braket
comma
id|data
(braket
l_int|33
)braket
comma
id|pkt_len
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; Packet has wrong length: %04d bytes&bslash;n&quot;
comma
id|pkt_len
)paren
suffix:semicolon
id|lp-&gt;stats.rx_errors
op_increment
suffix:semicolon
)brace
)brace
id|stdma_release
c_func
(paren
)paren
suffix:semicolon
id|ENABLE_IRQ
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* bionet_tick: called by bionet_timer. Reads packets from the adapter,&n; * passes them to the higher layers and restarts the timer.&n; */
r_static
r_void
DECL|function|bionet_tick
id|bionet_tick
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
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|bionet_debug
OG
l_int|0
op_logical_and
(paren
id|lp-&gt;open_time
op_increment
op_amp
l_int|7
)paren
op_eq
l_int|8
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bionet_tick: %ld&bslash;n&quot;
comma
id|lp-&gt;open_time
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|stdma_islocked
c_func
(paren
)paren
)paren
(brace
id|bionet_poll_rx
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|bionet_timer.expires
op_assign
id|jiffies
op_plus
id|lp-&gt;poll_time
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|bionet_timer
)paren
suffix:semicolon
)brace
multiline_comment|/* The inverse routine to bionet_open().&n; */
r_static
r_int
DECL|function|bionet_close
id|bionet_close
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
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|bionet_debug
OG
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;bionet_close, open_time=%ld&bslash;n&quot;
comma
id|lp-&gt;open_time
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|bionet_timer
)paren
suffix:semicolon
id|stdma_lock
c_func
(paren
id|bionet_intr
comma
l_int|NULL
)paren
suffix:semicolon
id|set_status
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|lp-&gt;open_time
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|1
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|0
suffix:semicolon
id|stdma_release
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Get the current statistics.&n;   This may be called with the card open or closed.&n; */
DECL|function|net_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|net_get_stats
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
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_return
op_amp
id|lp-&gt;stats
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|variable|bio_dev
r_static
r_struct
id|net_device
id|bio_dev
suffix:semicolon
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|bio_dev.init
op_assign
id|bionet_probe
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|register_netdev
c_func
(paren
op_amp
id|bio_dev
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|EEXIST
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;BIONET: devices already present. Module not loaded.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|unregister_netdev
c_func
(paren
op_amp
id|bio_dev
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
multiline_comment|/* Local variables:&n; *  compile-command: &quot;gcc -D__KERNEL__ -I/usr/src/linux/include&n;&t;-b m68k-linuxaout -Wall -Wstrict-prototypes -O2&n;&t;-fomit-frame-pointer -pipe -DMODULE -I../../net/inet -c bionet.c&quot;&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  tab-width: 8&n; * End:&n; */
eof
