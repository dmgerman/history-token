multiline_comment|/* mac89x0.c: A Crystal Semiconductor CS89[02]0 driver for linux. */
multiline_comment|/*&n;&t;Written 1996 by Russell Nelson, with reference to skeleton.c&n;&t;written 1993-1994 by Donald Becker.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU General Public License, incorporated herein by reference.&n;&n;&t;The author may be reached at nelson@crynwr.com, Crynwr&n;&t;Software, 11 Grant St., Potsdam, NY 13676&n;&n;  Changelog:&n;&n;  Mike Cruse        : mcruse@cti-ltd.com&n;                    : Changes for Linux 2.0 compatibility. &n;                    : Added dev_id parameter in net_interrupt(),&n;                    : request_irq() and free_irq(). Just NULL for now.&n;&n;  Mike Cruse        : Added MOD_INC_USE_COUNT and MOD_DEC_USE_COUNT macros&n;                    : in net_open() and net_close() so kerneld would know&n;                    : that the module is in use and wouldn&squot;t eject the &n;                    : driver prematurely.&n;&n;  Mike Cruse        : Rewrote init_module() and cleanup_module using 8390.c&n;                    : as an example. Disabled autoprobing in init_module(),&n;                    : not a good thing to do to other devices while Linux&n;                    : is running from all accounts.&n;                    &n;  Alan Cox          : Removed 1.2 support, added 2.1 extra counters.&n;&n;  David Huggins-Daines &lt;dhd@debian.org&gt;&n;  &n;  Split this off into mac89x0.c, and gutted it of all parts which are&n;  not relevant to the existing CS8900 cards on the Macintosh&n;  (i.e. basically the Daynaport CS and LC cards).  To be precise:&n;&n;    * Removed all the media-detection stuff, because these cards are&n;    TP-only.&n;&n;    * Lobotomized the ISA interrupt bogosity, because these cards use&n;    a hardwired NuBus interrupt and a magic ISAIRQ value in the card.&n;&n;    * Basically eliminated everything not relevant to getting the&n;    cards minimally functioning on the Macintosh.&n;&n;  I might add that these cards are badly designed even from the Mac&n;  standpoint, in that Dayna, in their infinite wisdom, used NuBus slot&n;  I/O space and NuBus interrupts for these cards, but neglected to&n;  provide anything even remotely resembling a NuBus ROM.  Therefore we&n;  have to probe for them in a brain-damaged ISA-like fashion.&n;&n;  Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt; - 11/01/2001&n;  check kmalloc and release the allocated memory on failure in&n;  mac89x0_probe and in init_module&n;  use save_flags/restore_flags in net_get_stat, not just cli/sti&n;*/
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;cs89x0.c:v1.02 11/26/96 Russell Nelson &lt;nelson@crynwr.com&gt;&bslash;n&quot;
suffix:semicolon
multiline_comment|/* ======================= configure the driver here ======================= */
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug */
macro_line|#ifndef NET_DEBUG
DECL|macro|NET_DEBUG
mdefine_line|#define NET_DEBUG 0
macro_line|#endif
multiline_comment|/* ======================= end of configuration ======================= */
multiline_comment|/* Always include &squot;config.h&squot; first in case the user wants to turn on&n;   or override something. */
macro_line|#include &lt;linux/module.h&gt;
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x) printk x
multiline_comment|/*&n;  Sources:&n;&n;&t;Crynwr packet driver epktisa.&n;&n;&t;Crystal Semiconductor data sheets.&n;&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/nubus.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hwtest.h&gt;
macro_line|#include &lt;asm/macints.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &quot;cs89x0.h&quot;
DECL|variable|net_debug
r_static
r_int
r_int
id|net_debug
op_assign
id|NET_DEBUG
suffix:semicolon
multiline_comment|/* Information that need to be kept for each board. */
DECL|struct|net_local
r_struct
id|net_local
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|chip_type
r_int
id|chip_type
suffix:semicolon
multiline_comment|/* one of: CS8900, CS8920, CS8920M */
DECL|member|chip_revision
r_char
id|chip_revision
suffix:semicolon
multiline_comment|/* revision letter of the chip (&squot;A&squot;...) */
DECL|member|send_cmd
r_int
id|send_cmd
suffix:semicolon
multiline_comment|/* the propercommand used to send a packet. */
DECL|member|rx_mode
r_int
id|rx_mode
suffix:semicolon
DECL|member|curr_rx_cfg
r_int
id|curr_rx_cfg
suffix:semicolon
DECL|member|send_underrun
r_int
id|send_underrun
suffix:semicolon
multiline_comment|/* keep track of how many underruns in a row we get */
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Index to functions, as function prototypes. */
r_extern
r_int
id|mac89x0_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#if 0
r_extern
r_void
id|reset_chip
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
r_static
r_int
id|net_open
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
id|net_send_packet
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
id|net_interrupt
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
suffix:semicolon
r_static
r_void
id|set_multicast_list
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
id|net_rx
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
id|net_close
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
r_int
id|set_mac_address
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/* Example routines you must write ;-&gt;. */
DECL|macro|tx_done
mdefine_line|#define tx_done(dev) 1
multiline_comment|/* For reading/writing registers ISA-style */
r_static
r_int
r_inline
DECL|function|readreg_io
id|readreg_io
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|portno
)paren
(brace
id|writew
c_func
(paren
id|swab16
c_func
(paren
id|portno
)paren
comma
id|dev-&gt;base_addr
op_plus
id|ADD_PORT
)paren
suffix:semicolon
r_return
id|swab16
c_func
(paren
id|readw
c_func
(paren
id|dev-&gt;base_addr
op_plus
id|DATA_PORT
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
r_inline
DECL|function|writereg_io
id|writereg_io
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|portno
comma
r_int
id|value
)paren
(brace
id|writew
c_func
(paren
id|swab16
c_func
(paren
id|portno
)paren
comma
id|dev-&gt;base_addr
op_plus
id|ADD_PORT
)paren
suffix:semicolon
id|writew
c_func
(paren
id|swab16
c_func
(paren
id|value
)paren
comma
id|dev-&gt;base_addr
op_plus
id|DATA_PORT
)paren
suffix:semicolon
)brace
multiline_comment|/* These are for reading/writing registers in shared memory */
r_static
r_int
r_inline
DECL|function|readreg
id|readreg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|portno
)paren
(brace
r_return
id|swab16
c_func
(paren
id|readw
c_func
(paren
id|dev-&gt;mem_start
op_plus
id|portno
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
r_inline
DECL|function|writereg
id|writereg
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|portno
comma
r_int
id|value
)paren
(brace
id|writew
c_func
(paren
id|swab16
c_func
(paren
id|value
)paren
comma
id|dev-&gt;mem_start
op_plus
id|portno
)paren
suffix:semicolon
)brace
multiline_comment|/* Probe for the CS8900 card in slot E.  We won&squot;t bother looking&n;   anywhere else until we have a really good reason to do so. */
DECL|function|mac89x0_probe
r_int
id|__init
id|mac89x0_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_static
r_int
id|once_is_enough
suffix:semicolon
r_struct
id|net_local
op_star
id|lp
suffix:semicolon
r_static
r_int
id|version_printed
suffix:semicolon
r_int
id|i
comma
id|slot
suffix:semicolon
r_int
id|rev_type
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|ioaddr
suffix:semicolon
r_int
r_int
id|sig
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
id|once_is_enough
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|once_is_enough
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We might have to parameterize this later */
id|slot
op_assign
l_int|0xE
suffix:semicolon
multiline_comment|/* Get out now if there&squot;s a real NuBus card in slot E */
r_if
c_cond
(paren
id|nubus_find_slot
c_func
(paren
id|slot
comma
l_int|NULL
)paren
op_ne
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* The pseudo-ISA bits always live at offset 0x300 (gee,&n;           wonder why...) */
id|ioaddr
op_assign
(paren
r_int
r_int
)paren
id|nubus_slot_addr
c_func
(paren
id|slot
)paren
op_or
(paren
(paren
(paren
id|slot
op_amp
l_int|0xf
)paren
op_lshift
l_int|20
)paren
op_plus
id|DEFAULTIOBASE
)paren
suffix:semicolon
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|card_present
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
id|card_present
op_assign
id|hwreg_present
c_func
(paren
(paren
r_void
op_star
)paren
id|ioaddr
op_plus
l_int|4
)paren
op_logical_and
id|hwreg_present
c_func
(paren
(paren
r_void
op_star
)paren
id|ioaddr
op_plus
id|DATA_PORT
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
id|card_present
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|writew
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|ADD_PORT
)paren
suffix:semicolon
id|sig
op_assign
id|readw
c_func
(paren
id|ioaddr
op_plus
id|DATA_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_ne
id|swab16
c_func
(paren
id|CHIP_EISA_ID_SIG
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Initialize the net_device structure. */
r_if
c_cond
(paren
id|dev-&gt;priv
op_eq
l_int|NULL
)paren
(brace
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
)brace
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/* Fill in the &squot;dev&squot; fields. */
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|dev-&gt;mem_start
op_assign
(paren
r_int
r_int
)paren
id|nubus_slot_addr
c_func
(paren
id|slot
)paren
op_or
(paren
(paren
(paren
id|slot
op_amp
l_int|0xf
)paren
op_lshift
l_int|20
)paren
op_plus
id|MMIOBASE
)paren
suffix:semicolon
id|dev-&gt;mem_end
op_assign
id|dev-&gt;mem_start
op_plus
l_int|0x1000
suffix:semicolon
multiline_comment|/* Turn on shared memory */
id|writereg_io
c_func
(paren
id|dev
comma
id|PP_BusCTL
comma
id|MEMORY_ON
)paren
suffix:semicolon
multiline_comment|/* get the chip type */
id|rev_type
op_assign
id|readreg
c_func
(paren
id|dev
comma
id|PRODUCT_ID_ADD
)paren
suffix:semicolon
id|lp-&gt;chip_type
op_assign
id|rev_type
op_amp
op_complement
id|REVISON_BITS
suffix:semicolon
id|lp-&gt;chip_revision
op_assign
(paren
(paren
id|rev_type
op_amp
id|REVISON_BITS
)paren
op_rshift
l_int|8
)paren
op_plus
l_char|&squot;A&squot;
suffix:semicolon
multiline_comment|/* Check the chip type and revision in order to set the correct send command&n;&t;CS8920 revision C and CS8900 revision F can use the faster send. */
id|lp-&gt;send_cmd
op_assign
id|TX_AFTER_381
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;chip_type
op_eq
id|CS8900
op_logical_and
id|lp-&gt;chip_revision
op_ge
l_char|&squot;F&squot;
)paren
id|lp-&gt;send_cmd
op_assign
id|TX_NOW
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;chip_type
op_ne
id|CS8900
op_logical_and
id|lp-&gt;chip_revision
op_ge
l_char|&squot;C&squot;
)paren
id|lp-&gt;send_cmd
op_assign
id|TX_NOW
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
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
id|KERN_INFO
l_string|&quot;%s: cs89%c0%s rev %c found at %#8lx&quot;
comma
id|dev-&gt;name
comma
id|lp-&gt;chip_type
op_eq
id|CS8900
ques
c_cond
l_char|&squot;0&squot;
suffix:colon
l_char|&squot;2&squot;
comma
id|lp-&gt;chip_type
op_eq
id|CS8920M
ques
c_cond
l_string|&quot;M&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|lp-&gt;chip_revision
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
multiline_comment|/* Try to read the MAC address */
r_if
c_cond
(paren
(paren
id|readreg
c_func
(paren
id|dev
comma
id|PP_SelfST
)paren
op_amp
(paren
id|EEPROM_PRESENT
op_or
id|EEPROM_OK
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nmac89x0: No EEPROM, giving up now.&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
id|dev-&gt;priv
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
(brace
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
op_add_assign
l_int|2
)paren
(brace
multiline_comment|/* Big-endian (why??!) */
r_int
r_int
id|s
op_assign
id|readreg
c_func
(paren
id|dev
comma
id|PP_IA
op_plus
id|i
)paren
suffix:semicolon
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|s
op_rshift
l_int|8
suffix:semicolon
id|dev-&gt;dev_addr
(braket
id|i
op_plus
l_int|1
)braket
op_assign
id|s
op_amp
l_int|0xff
suffix:semicolon
)brace
)brace
id|dev-&gt;irq
op_assign
id|SLOT2IRQ
c_func
(paren
id|slot
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; IRQ %d ADDR &quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* print the ethernet address. */
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
id|printk
c_func
(paren
l_string|&quot;%2.2x%s&quot;
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
comma
(paren
(paren
id|i
OL
id|ETH_ALEN
op_minus
l_int|1
)paren
ques
c_cond
l_string|&quot;:&quot;
suffix:colon
l_string|&quot;&quot;
)paren
)paren
suffix:semicolon
id|dev-&gt;open
op_assign
id|net_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|net_close
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|net_send_packet
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|net_get_stats
suffix:semicolon
id|dev-&gt;set_multicast_list
op_assign
op_amp
id|set_multicast_list
suffix:semicolon
id|dev-&gt;set_mac_address
op_assign
op_amp
id|set_mac_address
suffix:semicolon
multiline_comment|/* Fill in the fields of the net_device structure with ethernet values. */
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/* This is useful for something, but I don&squot;t know what yet. */
r_void
id|__init
id|reset_chip
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|reset_start_time
suffix:semicolon
id|writereg
c_func
(paren
id|dev
comma
id|PP_SelfCTL
comma
id|readreg
c_func
(paren
id|dev
comma
id|PP_SelfCTL
)paren
op_or
id|POWER_ON_RESET
)paren
suffix:semicolon
multiline_comment|/* wait 30 ms */
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|30
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* Wait until the chip is reset */
id|reset_start_time
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
(paren
id|readreg
c_func
(paren
id|dev
comma
id|PP_SelfST
)paren
op_amp
id|INIT_DONE
)paren
op_eq
l_int|0
op_logical_and
id|jiffies
op_minus
id|reset_start_time
OL
l_int|2
)paren
(brace
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* Open/initialize the board.  This is called (in the current kernel)&n;   sometime after booting when the &squot;ifconfig&squot; program is run.&n;&n;   This routine should set everything up anew at each open, even&n;   registers that &quot;should&quot; only need to be set once at boot, so that&n;   there is non-reboot way to recover if something goes wrong.&n;   */
r_static
r_int
DECL|function|net_open
id|net_open
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
id|i
suffix:semicolon
multiline_comment|/* Disable the interrupt for now */
id|writereg
c_func
(paren
id|dev
comma
id|PP_BusCTL
comma
id|readreg
c_func
(paren
id|dev
comma
id|PP_BusCTL
)paren
op_amp
op_complement
id|ENABLE_IRQ
)paren
suffix:semicolon
multiline_comment|/* Grab the interrupt */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
op_amp
id|net_interrupt
comma
l_int|0
comma
l_string|&quot;cs89x0&quot;
comma
id|dev
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
multiline_comment|/* Set up the IRQ - Apparently magic */
r_if
c_cond
(paren
id|lp-&gt;chip_type
op_eq
id|CS8900
)paren
id|writereg
c_func
(paren
id|dev
comma
id|PP_CS8900_ISAINT
comma
l_int|0
)paren
suffix:semicolon
r_else
id|writereg
c_func
(paren
id|dev
comma
id|PP_CS8920_ISAINT
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* set the Ethernet address */
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
op_div
l_int|2
suffix:semicolon
id|i
op_increment
)paren
id|writereg
c_func
(paren
id|dev
comma
id|PP_IA
op_plus
id|i
op_star
l_int|2
comma
id|dev-&gt;dev_addr
(braket
id|i
op_star
l_int|2
)braket
op_or
(paren
id|dev-&gt;dev_addr
(braket
id|i
op_star
l_int|2
op_plus
l_int|1
)braket
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
multiline_comment|/* Turn on both receive and transmit operations */
id|writereg
c_func
(paren
id|dev
comma
id|PP_LineCTL
comma
id|readreg
c_func
(paren
id|dev
comma
id|PP_LineCTL
)paren
op_or
id|SERIAL_RX_ON
op_or
id|SERIAL_TX_ON
)paren
suffix:semicolon
multiline_comment|/* Receive only error free packets addressed to this card */
id|lp-&gt;rx_mode
op_assign
l_int|0
suffix:semicolon
id|writereg
c_func
(paren
id|dev
comma
id|PP_RxCTL
comma
id|DEF_RX_ACCEPT
)paren
suffix:semicolon
id|lp-&gt;curr_rx_cfg
op_assign
id|RX_OK_ENBL
op_or
id|RX_CRC_ERROR_ENBL
suffix:semicolon
id|writereg
c_func
(paren
id|dev
comma
id|PP_RxCFG
comma
id|lp-&gt;curr_rx_cfg
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|dev
comma
id|PP_TxCFG
comma
id|TX_LOST_CRS_ENBL
op_or
id|TX_SQE_ERROR_ENBL
op_or
id|TX_OK_ENBL
op_or
id|TX_LATE_COL_ENBL
op_or
id|TX_JBR_ENBL
op_or
id|TX_ANY_COL_ENBL
op_or
id|TX_16_COL_ENBL
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|dev
comma
id|PP_BufCFG
comma
id|READY_FOR_TX_ENBL
op_or
id|RX_MISS_COUNT_OVRFLOW_ENBL
op_or
id|TX_COL_COUNT_OVRFLOW_ENBL
op_or
id|TX_UNDERRUN_ENBL
)paren
suffix:semicolon
multiline_comment|/* now that we&squot;ve got our act together, enable everything */
id|writereg
c_func
(paren
id|dev
comma
id|PP_BusCTL
comma
id|readreg
c_func
(paren
id|dev
comma
id|PP_BusCTL
)paren
op_or
id|ENABLE_IRQ
)paren
suffix:semicolon
id|netif_start_queue
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
DECL|function|net_send_packet
id|net_send_packet
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
r_if
c_cond
(paren
id|dev-&gt;tbusy
)paren
(brace
multiline_comment|/* If we get here, some higher level has decided we are broken.&n;&t;&t;   There should really be a &quot;kick me&quot; function call instead. */
r_int
id|tickssofar
op_assign
id|jiffies
op_minus
id|dev-&gt;trans_start
suffix:semicolon
r_if
c_cond
(paren
id|tickssofar
OL
l_int|5
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
OG
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s: transmit timed out, %s?&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|tx_done
c_func
(paren
id|dev
)paren
ques
c_cond
l_string|&quot;IRQ conflict&quot;
suffix:colon
l_string|&quot;network cable problem&quot;
)paren
suffix:semicolon
multiline_comment|/* Try to restart the adaptor. */
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
)brace
multiline_comment|/* Block a timer-based transmit from overlapping.  This could better be&n;&t;   done with atomic_swap(1, dev-&gt;tbusy), but set_bit() works as well. */
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
(paren
r_void
op_star
)paren
op_amp
id|dev-&gt;tbusy
)paren
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Transmitter access conflict.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_else
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
r_if
c_cond
(paren
id|net_debug
OG
l_int|3
)paren
id|printk
c_func
(paren
l_string|&quot;%s: sent %d byte packet of type %x&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|skb-&gt;len
comma
(paren
id|skb-&gt;data
(braket
id|ETH_ALEN
op_plus
id|ETH_ALEN
)braket
op_lshift
l_int|8
)paren
op_or
id|skb-&gt;data
(braket
id|ETH_ALEN
op_plus
id|ETH_ALEN
op_plus
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* keep the upload from being interrupted, since we&n;                   ask the chip to start transmitting before the&n;                   whole packet has been completely uploaded. */
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
multiline_comment|/* initiate a transmit sequence */
id|writereg
c_func
(paren
id|dev
comma
id|PP_TxCMD
comma
id|lp-&gt;send_cmd
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|dev
comma
id|PP_TxLength
comma
id|skb-&gt;len
)paren
suffix:semicolon
multiline_comment|/* Test to see if the chip has allocated memory for the packet */
r_if
c_cond
(paren
(paren
id|readreg
c_func
(paren
id|dev
comma
id|PP_BusST
)paren
op_amp
id|READY_FOR_TX_NOW
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Gasp!  It hasn&squot;t.  But that shouldn&squot;t happen since&n;&t;&t;&t;   we&squot;re waiting for TxOk, so return 1 and requeue this packet. */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Write the contents of the packet */
id|memcpy_toio
c_func
(paren
id|dev-&gt;mem_start
op_plus
id|PP_TxFrame
comma
id|skb-&gt;data
comma
id|skb-&gt;len
op_plus
l_int|1
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
)brace
id|dev_kfree_skb
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
"&f;"
multiline_comment|/* The typical workload of the driver:&n;   Handle the network interface interrupts. */
DECL|function|net_interrupt
r_static
r_void
id|net_interrupt
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
r_struct
id|net_device
op_star
id|dev
op_assign
id|dev_id
suffix:semicolon
r_struct
id|net_local
op_star
id|lp
suffix:semicolon
r_int
id|ioaddr
comma
id|status
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
l_string|&quot;net_interrupt(): irq %d for unknown device.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;interrupt
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Re-entering the interrupt handler.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dev-&gt;interrupt
op_assign
l_int|1
suffix:semicolon
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/* we MUST read all the events out of the ISQ, otherwise we&squot;ll never&n;           get interrupted again.  As a consequence, we can&squot;t have any limit&n;           on the number of times we loop in the interrupt handler.  The&n;           hardware guarantees that eventually we&squot;ll run out of events.  Of&n;           course, if you&squot;re on a slow machine, and packets are arriving&n;           faster than you can read them off, you&squot;re screwed.  Hasta la&n;           vista, baby!  */
r_while
c_loop
(paren
(paren
id|status
op_assign
id|swab16
c_func
(paren
id|readw
c_func
(paren
id|dev-&gt;base_addr
op_plus
id|ISQ_PORT
)paren
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|net_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot;%s: event=%04x&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|status
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
op_amp
id|ISQ_EVENT_MASK
)paren
(brace
r_case
id|ISQ_RECEIVER_EVENT
suffix:colon
multiline_comment|/* Got a packet(s). */
id|net_rx
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ISQ_TRANSMITTER_EVENT
suffix:colon
id|lp-&gt;stats.tx_packets
op_increment
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|mark_bh
c_func
(paren
id|NET_BH
)paren
suffix:semicolon
multiline_comment|/* Inform upper layers. */
r_if
c_cond
(paren
(paren
id|status
op_amp
id|TX_OK
)paren
op_eq
l_int|0
)paren
id|lp-&gt;stats.tx_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|TX_LOST_CRS
)paren
id|lp-&gt;stats.tx_carrier_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|TX_SQE_ERROR
)paren
id|lp-&gt;stats.tx_heartbeat_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|TX_LATE_COL
)paren
id|lp-&gt;stats.tx_window_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|TX_16_COL
)paren
id|lp-&gt;stats.tx_aborted_errors
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ISQ_BUFFER_EVENT
suffix:colon
r_if
c_cond
(paren
id|status
op_amp
id|READY_FOR_TX
)paren
(brace
multiline_comment|/* we tried to transmit a packet earlier,&n;                                   but inexplicably ran out of buffers.&n;                                   That shouldn&squot;t happen since we only ever&n;                                   load one packet.  Shrug.  Do the right&n;                                   thing anyway. */
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|mark_bh
c_func
(paren
id|NET_BH
)paren
suffix:semicolon
multiline_comment|/* Inform upper layers. */
)brace
r_if
c_cond
(paren
id|status
op_amp
id|TX_UNDERRUN
)paren
(brace
r_if
c_cond
(paren
id|net_debug
OG
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s: transmit underrun&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|lp-&gt;send_underrun
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;send_underrun
op_eq
l_int|3
)paren
id|lp-&gt;send_cmd
op_assign
id|TX_AFTER_381
suffix:semicolon
r_else
r_if
c_cond
(paren
id|lp-&gt;send_underrun
op_eq
l_int|6
)paren
id|lp-&gt;send_cmd
op_assign
id|TX_AFTER_ALL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ISQ_RX_MISS_EVENT
suffix:colon
id|lp-&gt;stats.rx_missed_errors
op_add_assign
(paren
id|status
op_rshift
l_int|6
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ISQ_TX_COL_EVENT
suffix:colon
id|lp-&gt;stats.collisions
op_add_assign
(paren
id|status
op_rshift
l_int|6
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* We have a good packet(s), get it/them out of the buffers. */
r_static
r_void
DECL|function|net_rx
id|net_rx
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
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|status
comma
id|length
suffix:semicolon
id|status
op_assign
id|readreg
c_func
(paren
id|dev
comma
id|PP_RxStatus
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|RX_OK
)paren
op_eq
l_int|0
)paren
(brace
id|lp-&gt;stats.rx_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|RX_RUNT
)paren
id|lp-&gt;stats.rx_length_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|RX_EXTRA_DATA
)paren
id|lp-&gt;stats.rx_length_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|RX_CRC_ERROR
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
(paren
id|RX_EXTRA_DATA
op_or
id|RX_RUNT
)paren
)paren
)paren
multiline_comment|/* per str 172 */
id|lp-&gt;stats.rx_crc_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|RX_DRIBBLE
)paren
id|lp-&gt;stats.rx_frame_errors
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
id|length
op_assign
id|readreg
c_func
(paren
id|dev
comma
id|PP_RxLength
)paren
suffix:semicolon
multiline_comment|/* Malloc up new buffer. */
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|length
comma
id|GFP_ATOMIC
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
r_return
suffix:semicolon
)brace
id|skb_put
c_func
(paren
id|skb
comma
id|length
)paren
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|memcpy_fromio
c_func
(paren
id|skb-&gt;data
comma
id|dev-&gt;mem_start
op_plus
id|PP_RxFrame
comma
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
OG
l_int|3
)paren
id|printk
c_func
(paren
l_string|&quot;%s: received %d byte packet of type %x&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|length
comma
(paren
id|skb-&gt;data
(braket
id|ETH_ALEN
op_plus
id|ETH_ALEN
)braket
op_lshift
l_int|8
)paren
op_or
id|skb-&gt;data
(braket
id|ETH_ALEN
op_plus
id|ETH_ALEN
op_plus
l_int|1
)braket
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
id|length
suffix:semicolon
)brace
multiline_comment|/* The inverse routine to net_open(). */
r_static
r_int
DECL|function|net_close
id|net_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|writereg
c_func
(paren
id|dev
comma
id|PP_RxCFG
comma
l_int|0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|dev
comma
id|PP_TxCFG
comma
l_int|0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|dev
comma
id|PP_BufCFG
comma
l_int|0
)paren
suffix:semicolon
id|writereg
c_func
(paren
id|dev
comma
id|PP_BusCTL
comma
l_int|0
)paren
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|dev
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
multiline_comment|/* Update the statistics here. */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Get the current statistics.&t;This may be called with the card open or&n;   closed. */
r_static
r_struct
id|net_device_stats
op_star
DECL|function|net_get_stats
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
multiline_comment|/* Update the statistics from the device registers. */
id|lp-&gt;stats.rx_missed_errors
op_add_assign
(paren
id|readreg
c_func
(paren
id|dev
comma
id|PP_RxMiss
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
id|lp-&gt;stats.collisions
op_add_assign
(paren
id|readreg
c_func
(paren
id|dev
comma
id|PP_TxCol
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_amp
id|lp-&gt;stats
suffix:semicolon
)brace
DECL|function|set_multicast_list
r_static
r_void
id|set_multicast_list
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
id|dev-&gt;flags
op_amp
id|IFF_PROMISC
)paren
(brace
id|lp-&gt;rx_mode
op_assign
id|RX_ALL_ACCEPT
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|dev-&gt;flags
op_amp
id|IFF_ALLMULTI
)paren
op_logical_or
id|dev-&gt;mc_list
)paren
(brace
multiline_comment|/* The multicast-accept list is initialized to accept-all, and we&n;&t;&t;   rely on higher-level filtering for now. */
id|lp-&gt;rx_mode
op_assign
id|RX_MULTCAST_ACCEPT
suffix:semicolon
)brace
r_else
id|lp-&gt;rx_mode
op_assign
l_int|0
suffix:semicolon
id|writereg
c_func
(paren
id|dev
comma
id|PP_RxCTL
comma
id|DEF_RX_ACCEPT
op_or
id|lp-&gt;rx_mode
)paren
suffix:semicolon
multiline_comment|/* in promiscuous mode, we accept errored packets, so we have to enable interrupts on them also */
id|writereg
c_func
(paren
id|dev
comma
id|PP_RxCFG
comma
id|lp-&gt;curr_rx_cfg
op_or
(paren
id|lp-&gt;rx_mode
op_eq
id|RX_ALL_ACCEPT
ques
c_cond
(paren
id|RX_CRC_ERROR_ENBL
op_or
id|RX_RUNT_ENBL
op_or
id|RX_EXTRA_DATA_ENBL
)paren
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
)brace
DECL|function|set_mac_address
r_static
r_int
id|set_mac_address
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_void
op_star
id|addr
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;start
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: Setting MAC address to &quot;
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot; %2.2x&quot;
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
(paren
(paren
r_int
r_char
op_star
)paren
id|addr
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* set the Ethernet address */
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
op_div
l_int|2
suffix:semicolon
id|i
op_increment
)paren
id|writereg
c_func
(paren
id|dev
comma
id|PP_IA
op_plus
id|i
op_star
l_int|2
comma
id|dev-&gt;dev_addr
(braket
id|i
op_star
l_int|2
)braket
op_or
(paren
id|dev-&gt;dev_addr
(braket
id|i
op_star
l_int|2
op_plus
l_int|1
)braket
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|variable|dev_cs89x0
r_static
r_struct
id|net_device
id|dev_cs89x0
suffix:semicolon
DECL|variable|debug
r_static
r_int
id|debug
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;CS89[02]0 debug level (0-5)&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
id|net_debug
op_assign
id|debug
suffix:semicolon
id|dev_cs89x0.init
op_assign
id|mac89x0_probe
suffix:semicolon
id|dev_cs89x0.priv
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
id|dev_cs89x0.priv
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|dev_cs89x0.priv
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
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
op_amp
id|dev_cs89x0
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;mac89x0.c: No card found&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev_cs89x0.priv
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
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
macro_line|#endif
macro_line|#ifdef MODULE
id|writew
c_func
(paren
l_int|0
comma
id|dev_cs89x0.base_addr
op_plus
id|ADD_PORT
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MODULE
r_if
c_cond
(paren
id|dev_cs89x0.priv
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Free up the private structure, or leak memory :-)  */
id|unregister_netdev
c_func
(paren
op_amp
id|dev_cs89x0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev_cs89x0.priv
)paren
suffix:semicolon
id|dev_cs89x0.priv
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* gets re-allocated by cs89x0_probe1 */
)brace
)brace
macro_line|#endif /* MODULE */
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;m68k-linux-gcc -D__KERNEL__ -I../../include -Wall -Wstrict-prototypes -O2 -fomit-frame-pointer -pipe -fno-strength-reduce -ffixed-a2 -DMODULE -DMODVERSIONS -include ../../include/linux/modversions.h   -c -o mac89x0.o mac89x0.c&quot;&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  c-indent-level: 8&n; *  tab-width: 8&n; * End:&n; *&n; */
eof
