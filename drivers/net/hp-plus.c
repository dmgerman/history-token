multiline_comment|/* hp-plus.c: A HP PCLAN/plus ethernet driver for linux. */
multiline_comment|/*&n;&t;Written 1994 by Donald Becker.&n;&n;&t;This driver is for the Hewlett Packard PC LAN (27***) plus ethercards.&n;&t;These cards are sold under several model numbers, usually 2724*.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU General Public License, incorporated herein by reference.&n;&n;&t;The author may be reached as becker@scyld.com, or C/O&n;&t;Scyld Computing Corporation&n;&t;410 Severn Ave., Suite 210&n;&t;Annapolis MD 21403&n;&n;&t;As is often the case, a great deal of credit is owed to Russ Nelson.&n;&t;The Crynwr packet driver was my primary source of HP-specific&n;&t;programming information.&n;*/
DECL|variable|version
r_static
r_const
r_char
id|version
(braket
)braket
op_assign
l_string|&quot;hp-plus.c:v1.10 9/24/94 Donald Becker (becker@cesdis.gsfc.nasa.gov)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;&t;&t;/* Important -- this inlines word moves. */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;8390.h&quot;
multiline_comment|/* A zero-terminated list of I/O addresses to be probed. */
DECL|variable|__initdata
r_static
r_int
r_int
id|hpplus_portlist
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x200
comma
l_int|0x240
comma
l_int|0x280
comma
l_int|0x2C0
comma
l_int|0x300
comma
l_int|0x320
comma
l_int|0x340
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n;   The HP EtherTwist chip implementation is a fairly routine DP8390&n;   implementation.  It allows both shared memory and programmed-I/O buffer&n;   access, using a custom interface for both.  The programmed-I/O mode is&n;   entirely implemented in the HP EtherTwist chip, bypassing the problem&n;   ridden built-in 8390 facilities used on NE2000 designs.  The shared&n;   memory mode is likewise special, with an offset register used to make&n;   packets appear at the shared memory base.  Both modes use a base and bounds&n;   page register to hide the Rx ring buffer wrap -- a packet that spans the&n;   end of physical buffer memory appears continuous to the driver. (c.f. the&n;   3c503 and Cabletron E2100)&n;&n;   A special note: the internal buffer of the board is only 8 bits wide.&n;   This lays several nasty traps for the unaware:&n;   - the 8390 must be programmed for byte-wide operations&n;   - all I/O and memory operations must work on whole words (the access&n;     latches are serially preloaded and have no byte-swapping ability).&n;&n;   This board is laid out in I/O space much like the earlier HP boards:&n;   the first 16 locations are for the board registers, and the second 16 are&n;   for the 8390.  The board is easy to identify, with both a dedicated 16 bit&n;   ID register and a constant 0x530* value in the upper bits of the paging&n;   register.&n;*/
DECL|macro|HP_ID
mdefine_line|#define HP_ID&t;&t;&t;0x00&t;/* ID register, always 0x4850. */
DECL|macro|HP_PAGING
mdefine_line|#define HP_PAGING&t;&t;0x02&t;/* Registers visible @ 8-f, see PageName. */
DECL|macro|HPP_OPTION
mdefine_line|#define HPP_OPTION&t;&t;0x04&t;/* Bitmapped options, see HP_Option.&t;*/
DECL|macro|HPP_OUT_ADDR
mdefine_line|#define HPP_OUT_ADDR&t;0x08&t;/* I/O output location in Perf_Page.&t;*/
DECL|macro|HPP_IN_ADDR
mdefine_line|#define HPP_IN_ADDR&t;&t;0x0A&t;/* I/O input location in Perf_Page.&t;&t;*/
DECL|macro|HP_DATAPORT
mdefine_line|#define HP_DATAPORT&t;&t;0x0c&t;/* I/O data transfer in Perf_Page.&t;&t;*/
DECL|macro|NIC_OFFSET
mdefine_line|#define NIC_OFFSET&t;&t;0x10&t;/* Offset to the 8390 registers.&t;&t;*/
DECL|macro|HP_IO_EXTENT
mdefine_line|#define HP_IO_EXTENT&t;32
DECL|macro|HP_START_PG
mdefine_line|#define HP_START_PG&t;&t;0x00&t;/* First page of TX buffer */
DECL|macro|HP_STOP_PG
mdefine_line|#define HP_STOP_PG&t;&t;0x80&t;/* Last page +1 of RX ring */
multiline_comment|/* The register set selected in HP_PAGING. */
DECL|enum|PageName
r_enum
id|PageName
(brace
DECL|enumerator|Perf_Page
id|Perf_Page
op_assign
l_int|0
comma
multiline_comment|/* Normal operation. */
DECL|enumerator|MAC_Page
id|MAC_Page
op_assign
l_int|1
comma
multiline_comment|/* The ethernet address (+checksum). */
DECL|enumerator|HW_Page
id|HW_Page
op_assign
l_int|2
comma
multiline_comment|/* EEPROM-loaded hardware parameters. */
DECL|enumerator|LAN_Page
id|LAN_Page
op_assign
l_int|4
comma
multiline_comment|/* Transceiver selection, testing, etc. */
DECL|enumerator|ID_Page
id|ID_Page
op_assign
l_int|6
)brace
suffix:semicolon
multiline_comment|/* The bit definitions for the HPP_OPTION register. */
DECL|enum|HP_Option
r_enum
id|HP_Option
(brace
DECL|enumerator|NICReset
DECL|enumerator|ChipReset
id|NICReset
op_assign
l_int|1
comma
id|ChipReset
op_assign
l_int|2
comma
multiline_comment|/* Active low, really UNreset. */
DECL|enumerator|EnableIRQ
DECL|enumerator|FakeIntr
DECL|enumerator|BootROMEnb
DECL|enumerator|IOEnb
id|EnableIRQ
op_assign
l_int|4
comma
id|FakeIntr
op_assign
l_int|8
comma
id|BootROMEnb
op_assign
l_int|0x10
comma
id|IOEnb
op_assign
l_int|0x20
comma
DECL|enumerator|MemEnable
DECL|enumerator|ZeroWait
DECL|enumerator|MemDisable
id|MemEnable
op_assign
l_int|0x40
comma
id|ZeroWait
op_assign
l_int|0x80
comma
id|MemDisable
op_assign
l_int|0x1000
comma
)brace
suffix:semicolon
r_static
r_int
id|hpp_probe1
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
suffix:semicolon
r_static
r_void
id|hpp_reset_8390
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
id|hpp_open
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
id|hpp_close
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
id|hpp_mem_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ring_offset
)paren
suffix:semicolon
r_static
r_void
id|hpp_mem_block_output
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|start_page
)paren
suffix:semicolon
r_static
r_void
id|hpp_mem_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
suffix:semicolon
r_static
r_void
id|hpp_io_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ring_offset
)paren
suffix:semicolon
r_static
r_void
id|hpp_io_block_output
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|start_page
)paren
suffix:semicolon
r_static
r_void
id|hpp_io_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
suffix:semicolon
"&f;"
multiline_comment|/*&t;Probe a list of addresses for an HP LAN+ adaptor.&n;&t;This routine is almost boilerplate. */
DECL|function|do_hpp_probe
r_static
r_int
id|__init
id|do_hpp_probe
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
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|irq
op_assign
id|dev-&gt;irq
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
id|base_addr
OG
l_int|0x1ff
)paren
multiline_comment|/* Check a single specified location. */
r_return
id|hpp_probe1
c_func
(paren
id|dev
comma
id|base_addr
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base_addr
op_ne
l_int|0
)paren
multiline_comment|/* Don&squot;t probe at all. */
r_return
op_minus
id|ENXIO
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|hpplus_portlist
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|hpp_probe1
c_func
(paren
id|dev
comma
id|hpplus_portlist
(braket
id|i
)braket
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|cleanup_card
r_static
r_void
id|cleanup_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* NB: hpp_close() handles free_irq */
id|release_region
c_func
(paren
id|dev-&gt;base_addr
op_minus
id|NIC_OFFSET
comma
id|HP_IO_EXTENT
)paren
suffix:semicolon
)brace
DECL|function|hp_plus_probe
r_struct
id|net_device
op_star
id|__init
id|hp_plus_probe
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
id|alloc_ei_netdev
c_func
(paren
)paren
suffix:semicolon
r_int
id|err
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
id|sprintf
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;eth%d&quot;
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
id|err
op_assign
id|do_hpp_probe
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
id|out1
suffix:semicolon
r_return
id|dev
suffix:semicolon
id|out1
suffix:colon
id|cleanup_card
c_func
(paren
id|dev
)paren
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
multiline_comment|/* Do the interesting part of the probe at a single address. */
DECL|function|hpp_probe1
r_static
r_int
id|__init
id|hpp_probe1
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
id|i
comma
id|retval
suffix:semicolon
r_int
r_char
id|checksum
op_assign
l_int|0
suffix:semicolon
r_const
r_char
id|name
(braket
)braket
op_assign
l_string|&quot;HP-PC-LAN+&quot;
suffix:semicolon
r_int
id|mem_start
suffix:semicolon
r_static
r_int
id|version_printed
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
id|HP_IO_EXTENT
comma
id|dev-&gt;name
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Check for the HP+ signature, 50 48 0x 53. */
r_if
c_cond
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
id|HP_ID
)paren
op_ne
l_int|0x4850
op_logical_or
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
id|HP_PAGING
)paren
op_amp
l_int|0xfff0
)paren
op_ne
l_int|0x5300
)paren
(brace
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ei_debug
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
l_string|&quot;%s: %s at %#3x,&quot;
comma
id|dev-&gt;name
comma
id|name
comma
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/* Retrieve and checksum the station address. */
id|outw
c_func
(paren
id|MAC_Page
comma
id|ioaddr
op_plus
id|HP_PAGING
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
id|ETHER_ADDR_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|inval
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|8
op_plus
id|i
)paren
suffix:semicolon
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|inval
suffix:semicolon
id|checksum
op_add_assign
id|inval
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %2.2x&quot;
comma
id|inval
)paren
suffix:semicolon
)brace
id|checksum
op_add_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|14
)paren
suffix:semicolon
r_if
c_cond
(paren
id|checksum
op_ne
l_int|0xff
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; bad checksum %2.2x.&bslash;n&quot;
comma
id|checksum
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Point at the Software Configuration Flags. */
id|outw
c_func
(paren
id|ID_Page
comma
id|ioaddr
op_plus
id|HP_PAGING
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; ID %4.4x&quot;
comma
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|12
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Read the IRQ line. */
id|outw
c_func
(paren
id|HW_Page
comma
id|ioaddr
op_plus
id|HP_PAGING
)paren
suffix:semicolon
(brace
r_int
id|irq
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|13
)paren
op_amp
l_int|0x0f
suffix:semicolon
r_int
id|option
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|option
op_amp
id|MemEnable
)paren
(brace
id|mem_start
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|9
)paren
op_lshift
l_int|8
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;, IRQ %d, memory address %#x.&bslash;n&quot;
comma
id|irq
comma
id|mem_start
)paren
suffix:semicolon
)brace
r_else
(brace
id|mem_start
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;, IRQ %d, programmed-I/O mode.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Set the wrap registers for string I/O reads.   */
id|outw
c_func
(paren
(paren
id|HP_START_PG
op_plus
id|TX_2X_PAGES
)paren
op_or
(paren
(paren
id|HP_STOP_PG
op_minus
l_int|1
)paren
op_lshift
l_int|8
)paren
comma
id|ioaddr
op_plus
l_int|14
)paren
suffix:semicolon
multiline_comment|/* Set the base address to point to the NIC, not the &quot;real&quot; base! */
id|dev-&gt;base_addr
op_assign
id|ioaddr
op_plus
id|NIC_OFFSET
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|hpp_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|hpp_close
suffix:semicolon
id|ei_status.name
op_assign
id|name
suffix:semicolon
id|ei_status.word16
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Agggghhhhh! Debug time: 2 days! */
id|ei_status.tx_start_page
op_assign
id|HP_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|HP_START_PG
op_plus
id|TX_2X_PAGES
suffix:semicolon
id|ei_status.stop_page
op_assign
id|HP_STOP_PG
suffix:semicolon
id|ei_status.reset_8390
op_assign
op_amp
id|hpp_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|hpp_io_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|hpp_io_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|hpp_io_get_8390_hdr
suffix:semicolon
multiline_comment|/* Check if the memory_enable flag is set in the option register. */
r_if
c_cond
(paren
id|mem_start
)paren
(brace
id|ei_status.block_input
op_assign
op_amp
id|hpp_mem_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|hpp_mem_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|hpp_mem_get_8390_hdr
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|mem_start
suffix:semicolon
id|ei_status.rmem_start
op_assign
id|dev-&gt;mem_start
op_plus
id|TX_2X_PAGES
op_star
l_int|256
suffix:semicolon
id|dev-&gt;mem_end
op_assign
id|ei_status.rmem_end
op_assign
id|dev-&gt;mem_start
op_plus
(paren
id|HP_STOP_PG
op_minus
id|HP_START_PG
)paren
op_star
l_int|256
suffix:semicolon
)brace
id|outw
c_func
(paren
id|Perf_Page
comma
id|ioaddr
op_plus
id|HP_PAGING
)paren
suffix:semicolon
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Leave the 8390 and HP chip reset. */
id|outw
c_func
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
id|HPP_OPTION
)paren
op_amp
op_complement
id|EnableIRQ
comma
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
id|release_region
c_func
(paren
id|ioaddr
comma
id|HP_IO_EXTENT
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_int
DECL|function|hpp_open
id|hpp_open
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
op_minus
id|NIC_OFFSET
suffix:semicolon
r_int
id|option_reg
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|ei_interrupt
comma
l_int|0
comma
id|dev-&gt;name
comma
id|dev
)paren
)paren
)paren
(brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Reset the 8390 and HP chip. */
id|option_reg
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
id|outw
c_func
(paren
id|option_reg
op_amp
op_complement
(paren
id|NICReset
op_plus
id|ChipReset
)paren
comma
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/* Unreset the board and enable interrupts. */
id|outw
c_func
(paren
id|option_reg
op_or
(paren
id|EnableIRQ
op_plus
id|NICReset
op_plus
id|ChipReset
)paren
comma
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
multiline_comment|/* Set the wrap registers for programmed-I/O operation.   */
id|outw
c_func
(paren
id|HW_Page
comma
id|ioaddr
op_plus
id|HP_PAGING
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|HP_START_PG
op_plus
id|TX_2X_PAGES
)paren
op_or
(paren
(paren
id|HP_STOP_PG
op_minus
l_int|1
)paren
op_lshift
l_int|8
)paren
comma
id|ioaddr
op_plus
l_int|14
)paren
suffix:semicolon
multiline_comment|/* Select the operational page. */
id|outw
c_func
(paren
id|Perf_Page
comma
id|ioaddr
op_plus
id|HP_PAGING
)paren
suffix:semicolon
id|ei_open
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|hpp_close
id|hpp_close
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
op_minus
id|NIC_OFFSET
suffix:semicolon
r_int
id|option_reg
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|HPP_OPTION
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
id|ei_close
c_func
(paren
id|dev
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|option_reg
op_amp
op_complement
id|EnableIRQ
)paren
op_or
id|MemDisable
op_or
id|NICReset
op_or
id|ChipReset
comma
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|hpp_reset_8390
id|hpp_reset_8390
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
op_minus
id|NIC_OFFSET
suffix:semicolon
r_int
id|option_reg
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;resetting the 8390 time=%ld...&quot;
comma
id|jiffies
)paren
suffix:semicolon
id|outw
c_func
(paren
id|option_reg
op_amp
op_complement
(paren
id|NICReset
op_plus
id|ChipReset
)paren
comma
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
multiline_comment|/* Pause a few cycles for the hardware reset to take place. */
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
id|outw
c_func
(paren
id|option_reg
op_or
(paren
id|EnableIRQ
op_plus
id|NICReset
op_plus
id|ChipReset
)paren
comma
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inb_p
c_func
(paren
id|ioaddr
op_plus
id|NIC_OFFSET
op_plus
id|EN0_ISR
)paren
op_amp
id|ENISR_RESET
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s: hp_reset_8390() did not complete.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;8390 reset done (%ld).&quot;
comma
id|jiffies
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* The programmed-I/O version of reading the 4 byte 8390 specific header.&n;   Note that transfer with the EtherTwist+ must be on word boundaries. */
r_static
r_void
DECL|function|hpp_io_get_8390_hdr
id|hpp_io_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|NIC_OFFSET
suffix:semicolon
id|outw
c_func
(paren
(paren
id|ring_page
op_lshift
l_int|8
)paren
comma
id|ioaddr
op_plus
id|HPP_IN_ADDR
)paren
suffix:semicolon
id|insw
c_func
(paren
id|ioaddr
op_plus
id|HP_DATAPORT
comma
id|hdr
comma
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Block input and output, similar to the Crynwr packet driver. */
r_static
r_void
DECL|function|hpp_io_block_input
id|hpp_io_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ring_offset
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|NIC_OFFSET
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|skb-&gt;data
suffix:semicolon
id|outw
c_func
(paren
id|ring_offset
comma
id|ioaddr
op_plus
id|HPP_IN_ADDR
)paren
suffix:semicolon
id|insw
c_func
(paren
id|ioaddr
op_plus
id|HP_DATAPORT
comma
id|buf
comma
id|count
op_rshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_amp
l_int|0x01
)paren
id|buf
(braket
id|count
op_minus
l_int|1
)braket
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|HP_DATAPORT
)paren
suffix:semicolon
)brace
multiline_comment|/* The corresponding shared memory versions of the above 2 functions. */
r_static
r_void
DECL|function|hpp_mem_get_8390_hdr
id|hpp_mem_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|NIC_OFFSET
suffix:semicolon
r_int
id|option_reg
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
id|outw
c_func
(paren
(paren
id|ring_page
op_lshift
l_int|8
)paren
comma
id|ioaddr
op_plus
id|HPP_IN_ADDR
)paren
suffix:semicolon
id|outw
c_func
(paren
id|option_reg
op_amp
op_complement
(paren
id|MemDisable
op_plus
id|BootROMEnb
)paren
comma
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
id|isa_memcpy_fromio
c_func
(paren
id|hdr
comma
id|dev-&gt;mem_start
comma
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
)paren
suffix:semicolon
id|outw
c_func
(paren
id|option_reg
comma
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
id|hdr-&gt;count
op_assign
(paren
id|le16_to_cpu
c_func
(paren
id|hdr-&gt;count
)paren
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
multiline_comment|/* Round up allocation. */
)brace
r_static
r_void
DECL|function|hpp_mem_block_input
id|hpp_mem_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ring_offset
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|NIC_OFFSET
suffix:semicolon
r_int
id|option_reg
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
id|outw
c_func
(paren
id|ring_offset
comma
id|ioaddr
op_plus
id|HPP_IN_ADDR
)paren
suffix:semicolon
id|outw
c_func
(paren
id|option_reg
op_amp
op_complement
(paren
id|MemDisable
op_plus
id|BootROMEnb
)paren
comma
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
multiline_comment|/* Caution: this relies on get_8390_hdr() rounding up count!&n;&t;   Also note that we *can&squot;t* use eth_io_copy_and_sum() because&n;&t;   it will not always copy &quot;count&quot; bytes (e.g. padded IP).  */
id|isa_memcpy_fromio
c_func
(paren
id|skb-&gt;data
comma
id|dev-&gt;mem_start
comma
id|count
)paren
suffix:semicolon
id|outw
c_func
(paren
id|option_reg
comma
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
)brace
multiline_comment|/* A special note: we *must* always transfer &gt;=16 bit words.&n;   It&squot;s always safe to round up, so we do. */
r_static
r_void
DECL|function|hpp_io_block_output
id|hpp_io_block_output
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|start_page
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|NIC_OFFSET
suffix:semicolon
id|outw
c_func
(paren
id|start_page
op_lshift
l_int|8
comma
id|ioaddr
op_plus
id|HPP_OUT_ADDR
)paren
suffix:semicolon
id|outsl
c_func
(paren
id|ioaddr
op_plus
id|HP_DATAPORT
comma
id|buf
comma
(paren
id|count
op_plus
l_int|3
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|hpp_mem_block_output
id|hpp_mem_block_output
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|start_page
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|NIC_OFFSET
suffix:semicolon
r_int
id|option_reg
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
id|outw
c_func
(paren
id|start_page
op_lshift
l_int|8
comma
id|ioaddr
op_plus
id|HPP_OUT_ADDR
)paren
suffix:semicolon
id|outw
c_func
(paren
id|option_reg
op_amp
op_complement
(paren
id|MemDisable
op_plus
id|BootROMEnb
)paren
comma
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
id|isa_memcpy_toio
c_func
(paren
id|dev-&gt;mem_start
comma
id|buf
comma
(paren
id|count
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
)paren
suffix:semicolon
id|outw
c_func
(paren
id|option_reg
comma
id|ioaddr
op_plus
id|HPP_OPTION
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
"&f;"
macro_line|#ifdef MODULE
DECL|macro|MAX_HPP_CARDS
mdefine_line|#define MAX_HPP_CARDS&t;4&t;/* Max number of HPP cards per module */
DECL|variable|dev_hpp
r_static
r_struct
id|net_device
op_star
id|dev_hpp
(braket
id|MAX_HPP_CARDS
)braket
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
(braket
id|MAX_HPP_CARDS
)braket
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
(braket
id|MAX_HPP_CARDS
)braket
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
id|MAX_HPP_CARDS
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
id|MAX_HPP_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;I/O port address(es)&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|irq
comma
l_string|&quot;IRQ number(s); ignored if properly detected&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;HP PC-LAN+ ISA ethernet driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* This is set up so that only a single autoprobe takes place per call.&n;ISA device autoprobes on a running machine are not recommended. */
r_int
DECL|function|init_module
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
id|this_dev
comma
id|found
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|this_dev
op_assign
l_int|0
suffix:semicolon
id|this_dev
OL
id|MAX_HPP_CARDS
suffix:semicolon
id|this_dev
op_increment
)paren
(brace
r_if
c_cond
(paren
id|io
(braket
id|this_dev
)braket
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|this_dev
op_ne
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* only autoprobe 1st one */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;hp-plus.c: Presently autoprobing (not recommended) for a single card.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|dev
op_assign
id|alloc_ei_netdev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_break
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
(braket
id|this_dev
)braket
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|io
(braket
id|this_dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|do_hpp_probe
c_func
(paren
id|dev
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
id|dev
)paren
op_eq
l_int|0
)paren
(brace
id|dev_hpp
(braket
id|found
op_increment
)braket
op_assign
id|dev
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|cleanup_card
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;hp-plus.c: No HP-Plus card found (i/o = 0x%x).&bslash;n&quot;
comma
id|io
(braket
id|this_dev
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|ENXIO
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
r_int
id|this_dev
suffix:semicolon
r_for
c_loop
(paren
id|this_dev
op_assign
l_int|0
suffix:semicolon
id|this_dev
OL
id|MAX_HPP_CARDS
suffix:semicolon
id|this_dev
op_increment
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|dev_hpp
(braket
id|this_dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|cleanup_card
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
)brace
macro_line|#endif /* MODULE */
eof
