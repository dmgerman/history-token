multiline_comment|/* &n; * 7990.c -- LANCE ethernet IC generic routines. &n; * This is an attempt to separate out the bits of various ethernet&n; * drivers that are common because they all use the AMD 7990 LANCE &n; * (Local Area Network Controller for Ethernet) chip.&n; *&n; * Copyright (C) 05/1998 Peter Maydell &lt;pmaydell@chiark.greenend.org.uk&gt;&n; *&n; * Most of this stuff was obtained by looking at other LANCE drivers,&n; * in particular a2065.[ch]. The AMD C-LANCE datasheet was also helpful.&n; * NB: this was made easy by the fact that Jes Sorensen had cleaned up&n; * most of a2025 and sunlance with the aim of merging them, so the &n; * common code was pretty obvious.&n; */
macro_line|#include &lt;linux/module.h&gt;
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
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
multiline_comment|/* Used for the temporal inet entries and routing */
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;linux/dio.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &quot;7990.h&quot;
multiline_comment|/* Lossage Factor Nine, Mr Sulu. */
DECL|macro|WRITERAP
mdefine_line|#define WRITERAP(x) (lp-&gt;writerap(lp,x))
DECL|macro|WRITERDP
mdefine_line|#define WRITERDP(x) (lp-&gt;writerdp(lp,x))
DECL|macro|READRDP
mdefine_line|#define READRDP() (lp-&gt;readrdp(lp))
multiline_comment|/* These used to be ll-&gt;rap = x, ll-&gt;rdp = x, and (ll-&gt;rdp). Sigh. &n; * If you want to switch them back then &n; * #define DECLARE_LL volatile struct lance_regs *ll = lp-&gt;ll&n; */
DECL|macro|DECLARE_LL
mdefine_line|#define DECLARE_LL /* nothing to declare */
multiline_comment|/* debugging output macros, various flavours */
multiline_comment|/* #define TEST_HITS */
macro_line|#ifdef UNDEF
DECL|macro|PRINT_RINGS
mdefine_line|#define PRINT_RINGS() &bslash;&n;do { &bslash;&n;        int t; &bslash;&n;        for (t=0; t &lt; RX_RING_SIZE; t++) { &bslash;&n;                printk(&quot;R%d: @(%02X %04X) len %04X, mblen %04X, bits %02X&bslash;n&quot;,&bslash;&n;                       t, ib-&gt;brx_ring[t].rmd1_hadr, ib-&gt;brx_ring[t].rmd0,&bslash;&n;                       ib-&gt;brx_ring[t].length,&bslash;&n;                       ib-&gt;brx_ring[t].mblength, ib-&gt;brx_ring[t].rmd1_bits);&bslash;&n;        }&bslash;&n;        for (t=0; t &lt; TX_RING_SIZE; t++) { &bslash;&n;                printk(&quot;T%d: @(%02X %04X) len %04X, misc %04X, bits %02X&bslash;n&quot;,&bslash;&n;                       t, ib-&gt;btx_ring[t].tmd1_hadr, ib-&gt;btx_ring[t].tmd0,&bslash;&n;                       ib-&gt;btx_ring[t].length,&bslash;&n;                       ib-&gt;btx_ring[t].misc, ib-&gt;btx_ring[t].tmd1_bits);&bslash;&n;        }&bslash;&n;} while (0) 
macro_line|#else
DECL|macro|PRINT_RINGS
mdefine_line|#define PRINT_RINGS()
macro_line|#endif        
multiline_comment|/* Load the CSR registers. The LANCE has to be STOPped when we do this! */
DECL|function|load_csrs
r_static
r_void
id|load_csrs
(paren
r_struct
id|lance_private
op_star
id|lp
)paren
(brace
r_volatile
r_struct
id|lance_init_block
op_star
id|aib
op_assign
id|lp-&gt;lance_init_block
suffix:semicolon
r_int
id|leptr
suffix:semicolon
id|DECLARE_LL
suffix:semicolon
id|leptr
op_assign
id|LANCE_ADDR
(paren
id|aib
)paren
suffix:semicolon
id|WRITERAP
c_func
(paren
id|LE_CSR1
)paren
suffix:semicolon
multiline_comment|/* load address of init block */
id|WRITERDP
c_func
(paren
id|leptr
op_amp
l_int|0xFFFF
)paren
suffix:semicolon
id|WRITERAP
c_func
(paren
id|LE_CSR2
)paren
suffix:semicolon
id|WRITERDP
c_func
(paren
id|leptr
op_rshift
l_int|16
)paren
suffix:semicolon
id|WRITERAP
c_func
(paren
id|LE_CSR3
)paren
suffix:semicolon
id|WRITERDP
c_func
(paren
id|lp-&gt;busmaster_regval
)paren
suffix:semicolon
multiline_comment|/* set byteswap/ALEctrl/byte ctrl */
multiline_comment|/* Point back to csr0 */
id|WRITERAP
c_func
(paren
id|LE_CSR0
)paren
suffix:semicolon
)brace
multiline_comment|/* #define to 0 or 1 appropriately */
DECL|macro|DEBUG_IRING
mdefine_line|#define DEBUG_IRING 0
multiline_comment|/* Set up the Lance Rx and Tx rings and the init block */
DECL|function|lance_init_ring
r_static
r_void
id|lance_init_ring
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|lance_private
op_star
id|lp
op_assign
(paren
r_struct
id|lance_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_volatile
r_struct
id|lance_init_block
op_star
id|ib
op_assign
id|lp-&gt;init_block
suffix:semicolon
r_volatile
r_struct
id|lance_init_block
op_star
id|aib
suffix:semicolon
multiline_comment|/* for LANCE_ADDR computations */
r_int
id|leptr
suffix:semicolon
r_int
id|i
suffix:semicolon
id|aib
op_assign
id|lp-&gt;lance_init_block
suffix:semicolon
id|lp-&gt;rx_new
op_assign
id|lp-&gt;tx_new
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;rx_old
op_assign
id|lp-&gt;tx_old
op_assign
l_int|0
suffix:semicolon
id|ib-&gt;mode
op_assign
id|LE_MO_PROM
suffix:semicolon
multiline_comment|/* normal, enable Tx &amp; Rx */
multiline_comment|/* Copy the ethernet address to the lance init block&n;         * Notice that we do a byteswap if we&squot;re big endian.&n;         * [I think this is the right criterion; at least, sunlance,&n;         * a2065 and atarilance do the byteswap and lance.c (PC) doesn&squot;t.&n;         * However, the datasheet says that the BSWAP bit doesn&squot;t affect&n;         * the init block, so surely it should be low byte first for&n;         * everybody? Um.] &n;         * We could define the ib-&gt;physaddr as three 16bit values and&n;         * use (addr[1] &lt;&lt; 8) | addr[0] &amp; co, but this is more efficient.&n;         */
macro_line|#ifdef __BIG_ENDIAN
id|ib-&gt;phys_addr
(braket
l_int|0
)braket
op_assign
id|dev-&gt;dev_addr
(braket
l_int|1
)braket
suffix:semicolon
id|ib-&gt;phys_addr
(braket
l_int|1
)braket
op_assign
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
suffix:semicolon
id|ib-&gt;phys_addr
(braket
l_int|2
)braket
op_assign
id|dev-&gt;dev_addr
(braket
l_int|3
)braket
suffix:semicolon
id|ib-&gt;phys_addr
(braket
l_int|3
)braket
op_assign
id|dev-&gt;dev_addr
(braket
l_int|2
)braket
suffix:semicolon
id|ib-&gt;phys_addr
(braket
l_int|4
)braket
op_assign
id|dev-&gt;dev_addr
(braket
l_int|5
)braket
suffix:semicolon
id|ib-&gt;phys_addr
(braket
l_int|5
)braket
op_assign
id|dev-&gt;dev_addr
(braket
l_int|4
)braket
suffix:semicolon
macro_line|#else
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
id|ib-&gt;phys_addr
(braket
id|i
)braket
op_assign
id|dev-&gt;dev_addr
(braket
id|i
)braket
suffix:semicolon
macro_line|#endif        
r_if
c_cond
(paren
id|DEBUG_IRING
)paren
id|printk
(paren
l_string|&quot;TX rings:&bslash;n&quot;
)paren
suffix:semicolon
id|lp-&gt;tx_full
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Setup the Tx ring entries */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
l_int|1
op_lshift
id|lp-&gt;lance_log_tx_bufs
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|leptr
op_assign
id|LANCE_ADDR
c_func
(paren
op_amp
id|aib-&gt;tx_buf
(braket
id|i
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ib-&gt;btx_ring
(braket
id|i
)braket
dot
id|tmd0
op_assign
id|leptr
suffix:semicolon
id|ib-&gt;btx_ring
(braket
id|i
)braket
dot
id|tmd1_hadr
op_assign
id|leptr
op_rshift
l_int|16
suffix:semicolon
id|ib-&gt;btx_ring
(braket
id|i
)braket
dot
id|tmd1_bits
op_assign
l_int|0
suffix:semicolon
id|ib-&gt;btx_ring
(braket
id|i
)braket
dot
id|length
op_assign
l_int|0xf000
suffix:semicolon
multiline_comment|/* The ones required by tmd2 */
id|ib-&gt;btx_ring
(braket
id|i
)braket
dot
id|misc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|DEBUG_IRING
)paren
id|printk
(paren
l_string|&quot;%d: 0x%8.8x&bslash;n&quot;
comma
id|i
comma
id|leptr
)paren
suffix:semicolon
)brace
multiline_comment|/* Setup the Rx ring entries */
r_if
c_cond
(paren
id|DEBUG_IRING
)paren
id|printk
(paren
l_string|&quot;RX rings:&bslash;n&quot;
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
(paren
l_int|1
op_lshift
id|lp-&gt;lance_log_rx_bufs
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|leptr
op_assign
id|LANCE_ADDR
c_func
(paren
op_amp
id|aib-&gt;rx_buf
(braket
id|i
)braket
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ib-&gt;brx_ring
(braket
id|i
)braket
dot
id|rmd0
op_assign
id|leptr
suffix:semicolon
id|ib-&gt;brx_ring
(braket
id|i
)braket
dot
id|rmd1_hadr
op_assign
id|leptr
op_rshift
l_int|16
suffix:semicolon
id|ib-&gt;brx_ring
(braket
id|i
)braket
dot
id|rmd1_bits
op_assign
id|LE_R1_OWN
suffix:semicolon
multiline_comment|/* 0xf000 == bits that must be one (reserved, presumably) */
id|ib-&gt;brx_ring
(braket
id|i
)braket
dot
id|length
op_assign
op_minus
id|RX_BUFF_SIZE
op_or
l_int|0xf000
suffix:semicolon
id|ib-&gt;brx_ring
(braket
id|i
)braket
dot
id|mblength
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|DEBUG_IRING
)paren
id|printk
(paren
l_string|&quot;%d: 0x%8.8x&bslash;n&quot;
comma
id|i
comma
id|leptr
)paren
suffix:semicolon
)brace
multiline_comment|/* Setup the initialization block */
multiline_comment|/* Setup rx descriptor pointer */
id|leptr
op_assign
id|LANCE_ADDR
c_func
(paren
op_amp
id|aib-&gt;brx_ring
)paren
suffix:semicolon
id|ib-&gt;rx_len
op_assign
(paren
id|lp-&gt;lance_log_rx_bufs
op_lshift
l_int|13
)paren
op_or
(paren
id|leptr
op_rshift
l_int|16
)paren
suffix:semicolon
id|ib-&gt;rx_ptr
op_assign
id|leptr
suffix:semicolon
r_if
c_cond
(paren
id|DEBUG_IRING
)paren
id|printk
(paren
l_string|&quot;RX ptr: %8.8x&bslash;n&quot;
comma
id|leptr
)paren
suffix:semicolon
multiline_comment|/* Setup tx descriptor pointer */
id|leptr
op_assign
id|LANCE_ADDR
c_func
(paren
op_amp
id|aib-&gt;btx_ring
)paren
suffix:semicolon
id|ib-&gt;tx_len
op_assign
(paren
id|lp-&gt;lance_log_tx_bufs
op_lshift
l_int|13
)paren
op_or
(paren
id|leptr
op_rshift
l_int|16
)paren
suffix:semicolon
id|ib-&gt;tx_ptr
op_assign
id|leptr
suffix:semicolon
r_if
c_cond
(paren
id|DEBUG_IRING
)paren
id|printk
(paren
l_string|&quot;TX ptr: %8.8x&bslash;n&quot;
comma
id|leptr
)paren
suffix:semicolon
multiline_comment|/* Clear the multicast filter */
id|ib-&gt;filter
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|ib-&gt;filter
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|PRINT_RINGS
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* LANCE must be STOPped before we do this, too... */
DECL|function|init_restart_lance
r_static
r_int
id|init_restart_lance
(paren
r_struct
id|lance_private
op_star
id|lp
)paren
(brace
r_int
id|i
suffix:semicolon
id|DECLARE_LL
suffix:semicolon
id|WRITERAP
c_func
(paren
id|LE_CSR0
)paren
suffix:semicolon
id|WRITERDP
c_func
(paren
id|LE_C0_INIT
)paren
suffix:semicolon
multiline_comment|/* Need a hook here for sunlance ledma stuff */
multiline_comment|/* Wait for the lance to complete initialization */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
l_int|100
)paren
op_logical_and
op_logical_neg
(paren
id|READRDP
c_func
(paren
)paren
op_amp
(paren
id|LE_C0_ERR
op_or
id|LE_C0_IDON
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_eq
l_int|100
)paren
op_logical_or
(paren
id|READRDP
c_func
(paren
)paren
op_amp
id|LE_C0_ERR
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;LANCE unopened after %d ticks, csr0=%4.4x.&bslash;n&quot;
comma
id|i
comma
id|READRDP
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Clear IDON by writing a &quot;1&quot;, enable interrupts and start lance */
id|WRITERDP
c_func
(paren
id|LE_C0_IDON
)paren
suffix:semicolon
id|WRITERDP
c_func
(paren
id|LE_C0_INEA
op_or
id|LE_C0_STRT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lance_reset
r_static
r_int
id|lance_reset
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|lance_private
op_star
id|lp
op_assign
(paren
r_struct
id|lance_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|status
suffix:semicolon
id|DECLARE_LL
suffix:semicolon
multiline_comment|/* Stop the lance */
id|WRITERAP
c_func
(paren
id|LE_CSR0
)paren
suffix:semicolon
id|WRITERDP
c_func
(paren
id|LE_C0_STOP
)paren
suffix:semicolon
id|load_csrs
(paren
id|lp
)paren
suffix:semicolon
id|lance_init_ring
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|status
op_assign
id|init_restart_lance
(paren
id|lp
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_DRIVER
id|printk
(paren
l_string|&quot;Lance restart=%d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
macro_line|#endif
r_return
id|status
suffix:semicolon
)brace
DECL|function|lance_rx
r_static
r_int
id|lance_rx
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|lance_private
op_star
id|lp
op_assign
(paren
r_struct
id|lance_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_volatile
r_struct
id|lance_init_block
op_star
id|ib
op_assign
id|lp-&gt;init_block
suffix:semicolon
r_volatile
r_struct
id|lance_rx_desc
op_star
id|rd
suffix:semicolon
r_int
r_char
id|bits
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX shut up gcc warnings */
r_struct
id|sk_buff
op_star
id|skb
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX shut up gcc warnings */
macro_line|#ifdef TEST_HITS
r_int
id|i
suffix:semicolon
macro_line|#endif
id|DECLARE_LL
suffix:semicolon
macro_line|#ifdef TEST_HITS
id|printk
(paren
l_string|&quot;[&quot;
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
id|RX_RING_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
id|lp-&gt;rx_new
)paren
id|printk
(paren
l_string|&quot;%s&quot;
comma
id|ib-&gt;brx_ring
(braket
id|i
)braket
dot
id|rmd1_bits
op_amp
id|LE_R1_OWN
ques
c_cond
l_string|&quot;_&quot;
suffix:colon
l_string|&quot;X&quot;
)paren
suffix:semicolon
r_else
id|printk
(paren
l_string|&quot;%s&quot;
comma
id|ib-&gt;brx_ring
(braket
id|i
)braket
dot
id|rmd1_bits
op_amp
id|LE_R1_OWN
ques
c_cond
l_string|&quot;.&quot;
suffix:colon
l_string|&quot;1&quot;
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;]&quot;
)paren
suffix:semicolon
macro_line|#endif
id|WRITERDP
c_func
(paren
id|LE_C0_RINT
op_or
id|LE_C0_INEA
)paren
suffix:semicolon
multiline_comment|/* ack Rx int, reenable ints */
r_for
c_loop
(paren
id|rd
op_assign
op_amp
id|ib-&gt;brx_ring
(braket
id|lp-&gt;rx_new
)braket
suffix:semicolon
multiline_comment|/* For each Rx ring we own... */
op_logical_neg
(paren
(paren
id|bits
op_assign
id|rd-&gt;rmd1_bits
)paren
op_amp
id|LE_R1_OWN
)paren
suffix:semicolon
id|rd
op_assign
op_amp
id|ib-&gt;brx_ring
(braket
id|lp-&gt;rx_new
)braket
)paren
(brace
multiline_comment|/* We got an incomplete frame? */
r_if
c_cond
(paren
(paren
id|bits
op_amp
id|LE_R1_POK
)paren
op_ne
id|LE_R1_POK
)paren
(brace
id|lp-&gt;stats.rx_over_errors
op_increment
suffix:semicolon
id|lp-&gt;stats.rx_errors
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|bits
op_amp
id|LE_R1_ERR
)paren
(brace
multiline_comment|/* Count only the end frame as a rx error,&n;                         * not the beginning&n;                         */
r_if
c_cond
(paren
id|bits
op_amp
id|LE_R1_BUF
)paren
id|lp-&gt;stats.rx_fifo_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_amp
id|LE_R1_CRC
)paren
id|lp-&gt;stats.rx_crc_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_amp
id|LE_R1_OFL
)paren
id|lp-&gt;stats.rx_over_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_amp
id|LE_R1_FRA
)paren
id|lp-&gt;stats.rx_frame_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_amp
id|LE_R1_EOP
)paren
id|lp-&gt;stats.rx_errors
op_increment
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
(paren
id|rd-&gt;mblength
op_amp
l_int|0xfff
)paren
op_minus
l_int|4
suffix:semicolon
id|skb
op_assign
id|dev_alloc_skb
(paren
id|len
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;%s: Memory squeeze, deferring packet.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|lp-&gt;stats.rx_dropped
op_increment
suffix:semicolon
id|rd-&gt;mblength
op_assign
l_int|0
suffix:semicolon
id|rd-&gt;rmd1_bits
op_assign
id|LE_R1_OWN
suffix:semicolon
id|lp-&gt;rx_new
op_assign
(paren
id|lp-&gt;rx_new
op_plus
l_int|1
)paren
op_amp
id|lp-&gt;rx_ring_mod_mask
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb_reserve
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* 16 byte align */
id|skb_put
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* make room */
id|eth_copy_and_sum
c_func
(paren
id|skb
comma
(paren
r_int
r_char
op_star
)paren
op_amp
(paren
id|ib-&gt;rx_buf
(braket
id|lp-&gt;rx_new
)braket
(braket
l_int|0
)braket
)paren
comma
id|len
comma
l_int|0
)paren
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|eth_type_trans
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
id|netif_rx
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
id|len
suffix:semicolon
)brace
multiline_comment|/* Return the packet to the pool */
id|rd-&gt;mblength
op_assign
l_int|0
suffix:semicolon
id|rd-&gt;rmd1_bits
op_assign
id|LE_R1_OWN
suffix:semicolon
id|lp-&gt;rx_new
op_assign
(paren
id|lp-&gt;rx_new
op_plus
l_int|1
)paren
op_amp
id|lp-&gt;rx_ring_mod_mask
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lance_tx
r_static
r_int
id|lance_tx
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|lance_private
op_star
id|lp
op_assign
(paren
r_struct
id|lance_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_volatile
r_struct
id|lance_init_block
op_star
id|ib
op_assign
id|lp-&gt;init_block
suffix:semicolon
r_volatile
r_struct
id|lance_tx_desc
op_star
id|td
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|status
suffix:semicolon
id|DECLARE_LL
suffix:semicolon
multiline_comment|/* csr0 is 2f3 */
id|WRITERDP
c_func
(paren
id|LE_C0_TINT
op_or
id|LE_C0_INEA
)paren
suffix:semicolon
multiline_comment|/* csr0 is 73 */
id|j
op_assign
id|lp-&gt;tx_old
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|j
suffix:semicolon
id|i
op_ne
id|lp-&gt;tx_new
suffix:semicolon
id|i
op_assign
id|j
)paren
(brace
id|td
op_assign
op_amp
id|ib-&gt;btx_ring
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* If we hit a packet not owned by us, stop */
r_if
c_cond
(paren
id|td-&gt;tmd1_bits
op_amp
id|LE_T1_OWN
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|td-&gt;tmd1_bits
op_amp
id|LE_T1_ERR
)paren
(brace
id|status
op_assign
id|td-&gt;misc
suffix:semicolon
id|lp-&gt;stats.tx_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|LE_T3_RTY
)paren
id|lp-&gt;stats.tx_aborted_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|LE_T3_LCOL
)paren
id|lp-&gt;stats.tx_window_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|LE_T3_CLOS
)paren
(brace
id|lp-&gt;stats.tx_carrier_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;auto_select
)paren
(brace
id|lp-&gt;tpe
op_assign
l_int|1
op_minus
id|lp-&gt;tpe
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: Carrier Lost, trying %s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|lp-&gt;tpe
ques
c_cond
l_string|&quot;TPE&quot;
suffix:colon
l_string|&quot;AUI&quot;
)paren
suffix:semicolon
multiline_comment|/* Stop the lance */
id|WRITERAP
c_func
(paren
id|LE_CSR0
)paren
suffix:semicolon
id|WRITERDP
c_func
(paren
id|LE_C0_STOP
)paren
suffix:semicolon
id|lance_init_ring
(paren
id|dev
)paren
suffix:semicolon
id|load_csrs
(paren
id|lp
)paren
suffix:semicolon
id|init_restart_lance
(paren
id|lp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* buffer errors and underflows turn off the transmitter */
multiline_comment|/* Restart the adapter */
r_if
c_cond
(paren
id|status
op_amp
(paren
id|LE_T3_BUF
op_or
id|LE_T3_UFL
)paren
)paren
(brace
id|lp-&gt;stats.tx_fifo_errors
op_increment
suffix:semicolon
id|printk
(paren
l_string|&quot;%s: Tx: ERR_BUF|ERR_UFL, restarting&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
multiline_comment|/* Stop the lance */
id|WRITERAP
c_func
(paren
id|LE_CSR0
)paren
suffix:semicolon
id|WRITERDP
c_func
(paren
id|LE_C0_STOP
)paren
suffix:semicolon
id|lance_init_ring
(paren
id|dev
)paren
suffix:semicolon
id|load_csrs
(paren
id|lp
)paren
suffix:semicolon
id|init_restart_lance
(paren
id|lp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
id|td-&gt;tmd1_bits
op_amp
id|LE_T1_POK
)paren
op_eq
id|LE_T1_POK
)paren
(brace
multiline_comment|/*&n;                         * So we don&squot;t count the packet more than once.&n;                         */
id|td-&gt;tmd1_bits
op_and_assign
op_complement
(paren
id|LE_T1_POK
)paren
suffix:semicolon
multiline_comment|/* One collision before packet was sent. */
r_if
c_cond
(paren
id|td-&gt;tmd1_bits
op_amp
id|LE_T1_EONE
)paren
id|lp-&gt;stats.collisions
op_increment
suffix:semicolon
multiline_comment|/* More than one collision, be optimistic. */
r_if
c_cond
(paren
id|td-&gt;tmd1_bits
op_amp
id|LE_T1_EMORE
)paren
id|lp-&gt;stats.collisions
op_add_assign
l_int|2
suffix:semicolon
id|lp-&gt;stats.tx_packets
op_increment
suffix:semicolon
)brace
id|j
op_assign
(paren
id|j
op_plus
l_int|1
)paren
op_amp
id|lp-&gt;tx_ring_mod_mask
suffix:semicolon
)brace
id|lp-&gt;tx_old
op_assign
id|j
suffix:semicolon
id|WRITERDP
c_func
(paren
id|LE_C0_TINT
op_or
id|LE_C0_INEA
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lance_interrupt
r_static
r_void
id|lance_interrupt
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
(paren
r_struct
id|net_device
op_star
)paren
id|dev_id
suffix:semicolon
r_struct
id|lance_private
op_star
id|lp
op_assign
(paren
r_struct
id|lance_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|csr0
suffix:semicolon
id|DECLARE_LL
suffix:semicolon
id|spin_lock
(paren
op_amp
id|lp-&gt;devlock
)paren
suffix:semicolon
id|WRITERAP
c_func
(paren
id|LE_CSR0
)paren
suffix:semicolon
multiline_comment|/* LANCE Controller Status */
id|csr0
op_assign
id|READRDP
c_func
(paren
)paren
suffix:semicolon
id|PRINT_RINGS
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|csr0
op_amp
id|LE_C0_INTR
)paren
)paren
(brace
multiline_comment|/* Check if any interrupt has */
id|spin_lock
(paren
op_amp
id|lp-&gt;devlock
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* been generated by the Lance. */
)brace
multiline_comment|/* Acknowledge all the interrupt sources ASAP */
id|WRITERDP
c_func
(paren
id|csr0
op_amp
op_complement
(paren
id|LE_C0_INEA
op_or
id|LE_C0_TDMD
op_or
id|LE_C0_STOP
op_or
id|LE_C0_STRT
op_or
id|LE_C0_INIT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|csr0
op_amp
id|LE_C0_ERR
)paren
)paren
(brace
multiline_comment|/* Clear the error condition */
id|WRITERDP
c_func
(paren
id|LE_C0_BABL
op_or
id|LE_C0_ERR
op_or
id|LE_C0_MISS
op_or
id|LE_C0_INEA
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|csr0
op_amp
id|LE_C0_RINT
)paren
id|lance_rx
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csr0
op_amp
id|LE_C0_TINT
)paren
id|lance_tx
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Log misc errors. */
r_if
c_cond
(paren
id|csr0
op_amp
id|LE_C0_BABL
)paren
id|lp-&gt;stats.tx_errors
op_increment
suffix:semicolon
multiline_comment|/* Tx babble. */
r_if
c_cond
(paren
id|csr0
op_amp
id|LE_C0_MISS
)paren
id|lp-&gt;stats.rx_errors
op_increment
suffix:semicolon
multiline_comment|/* Missed a Rx frame. */
r_if
c_cond
(paren
id|csr0
op_amp
id|LE_C0_MERR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Bus master arbitration failure, status %4.4x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr0
)paren
suffix:semicolon
multiline_comment|/* Restart the chip. */
id|WRITERDP
c_func
(paren
id|LE_C0_STRT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lp-&gt;tx_full
op_logical_and
id|netif_queue_stopped
c_func
(paren
id|dev
)paren
op_logical_and
(paren
id|TX_BUFFS_AVAIL
op_ge
l_int|0
)paren
)paren
(brace
id|lp-&gt;tx_full
op_assign
l_int|0
suffix:semicolon
id|netif_wake_queue
(paren
id|dev
)paren
suffix:semicolon
)brace
id|WRITERAP
c_func
(paren
id|LE_CSR0
)paren
suffix:semicolon
id|WRITERDP
c_func
(paren
id|LE_C0_BABL
op_or
id|LE_C0_CERR
op_or
id|LE_C0_MISS
op_or
id|LE_C0_MERR
op_or
id|LE_C0_IDON
op_or
id|LE_C0_INEA
)paren
suffix:semicolon
id|spin_unlock
(paren
op_amp
id|lp-&gt;devlock
)paren
suffix:semicolon
)brace
DECL|function|lance_open
r_int
id|lance_open
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|lance_private
op_star
id|lp
op_assign
(paren
r_struct
id|lance_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|res
suffix:semicolon
id|DECLARE_LL
suffix:semicolon
multiline_comment|/* Install the Interrupt handler. Or we could shunt this out to specific drivers? */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|lp-&gt;irq
comma
id|lance_interrupt
comma
l_int|0
comma
id|lp-&gt;name
comma
id|dev
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|res
op_assign
id|lance_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
id|lp-&gt;devlock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|netif_start_queue
(paren
id|dev
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|lance_close
r_int
id|lance_close
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|lance_private
op_star
id|lp
op_assign
(paren
r_struct
id|lance_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|DECLARE_LL
suffix:semicolon
id|netif_stop_queue
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Stop the LANCE */
id|WRITERAP
c_func
(paren
id|LE_CSR0
)paren
suffix:semicolon
id|WRITERDP
c_func
(paren
id|LE_C0_STOP
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|lp-&gt;irq
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lance_tx_timeout
r_void
id|lance_tx_timeout
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lance_tx_timeout&bslash;n&quot;
)paren
suffix:semicolon
id|lance_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|netif_wake_queue
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|lance_start_xmit
r_int
id|lance_start_xmit
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
id|lance_private
op_star
id|lp
op_assign
(paren
r_struct
id|lance_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_volatile
r_struct
id|lance_init_block
op_star
id|ib
op_assign
id|lp-&gt;init_block
suffix:semicolon
r_int
id|entry
comma
id|skblen
comma
id|len
suffix:semicolon
r_static
r_int
id|outs
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|DECLARE_LL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|TX_BUFFS_AVAIL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|netif_stop_queue
(paren
id|dev
)paren
suffix:semicolon
id|skblen
op_assign
id|skb-&gt;len
suffix:semicolon
macro_line|#ifdef DEBUG_DRIVER
multiline_comment|/* dump the packet */
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
l_int|64
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|16
)paren
op_eq
l_int|0
)paren
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;%2.2x &quot;
comma
id|skb-&gt;data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
id|len
op_assign
(paren
id|skblen
op_le
id|ETH_ZLEN
)paren
ques
c_cond
id|ETH_ZLEN
suffix:colon
id|skblen
suffix:semicolon
id|entry
op_assign
id|lp-&gt;tx_new
op_amp
id|lp-&gt;tx_ring_mod_mask
suffix:semicolon
id|ib-&gt;btx_ring
(braket
id|entry
)braket
dot
id|length
op_assign
(paren
op_minus
id|len
)paren
op_or
l_int|0xf000
suffix:semicolon
id|ib-&gt;btx_ring
(braket
id|entry
)braket
dot
id|misc
op_assign
l_int|0
suffix:semicolon
id|memcpy
(paren
(paren
r_char
op_star
)paren
op_amp
id|ib-&gt;tx_buf
(braket
id|entry
)braket
(braket
l_int|0
)braket
comma
id|skb-&gt;data
comma
id|skblen
)paren
suffix:semicolon
multiline_comment|/* Now, give the packet to the lance */
id|ib-&gt;btx_ring
(braket
id|entry
)braket
dot
id|tmd1_bits
op_assign
(paren
id|LE_T1_POK
op_or
id|LE_T1_OWN
)paren
suffix:semicolon
id|lp-&gt;tx_new
op_assign
(paren
id|lp-&gt;tx_new
op_plus
l_int|1
)paren
op_amp
id|lp-&gt;tx_ring_mod_mask
suffix:semicolon
id|outs
op_increment
suffix:semicolon
multiline_comment|/* Kick the lance: transmit now */
id|WRITERDP
c_func
(paren
id|LE_C0_INEA
op_or
id|LE_C0_TDMD
)paren
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|dev_kfree_skb
(paren
id|skb
)paren
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|lp-&gt;devlock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|TX_BUFFS_AVAIL
)paren
id|netif_start_queue
(paren
id|dev
)paren
suffix:semicolon
r_else
id|lp-&gt;tx_full
op_assign
l_int|1
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|lp-&gt;devlock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lance_get_stats
r_struct
id|net_device_stats
op_star
id|lance_get_stats
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|lance_private
op_star
id|lp
op_assign
(paren
r_struct
id|lance_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_return
op_amp
id|lp-&gt;stats
suffix:semicolon
)brace
multiline_comment|/* taken from the depca driver via a2065.c */
DECL|function|lance_load_multicast
r_static
r_void
id|lance_load_multicast
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|lance_private
op_star
id|lp
op_assign
(paren
r_struct
id|lance_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_volatile
r_struct
id|lance_init_block
op_star
id|ib
op_assign
id|lp-&gt;init_block
suffix:semicolon
r_volatile
id|u16
op_star
id|mcast_table
op_assign
(paren
id|u16
op_star
)paren
op_amp
id|ib-&gt;filter
suffix:semicolon
r_struct
id|dev_mc_list
op_star
id|dmi
op_assign
id|dev-&gt;mc_list
suffix:semicolon
r_char
op_star
id|addrs
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|bit
comma
id|byte
suffix:semicolon
id|u32
id|crc
comma
id|poly
op_assign
id|CRC_POLYNOMIAL_LE
suffix:semicolon
multiline_comment|/* set all multicast bits */
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_ALLMULTI
)paren
(brace
id|ib-&gt;filter
(braket
l_int|0
)braket
op_assign
l_int|0xffffffff
suffix:semicolon
id|ib-&gt;filter
(braket
l_int|1
)braket
op_assign
l_int|0xffffffff
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* clear the multicast filter */
id|ib-&gt;filter
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|ib-&gt;filter
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Add addresses */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dev-&gt;mc_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|addrs
op_assign
id|dmi-&gt;dmi_addr
suffix:semicolon
id|dmi
op_assign
id|dmi-&gt;next
suffix:semicolon
multiline_comment|/* multicast address? */
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|addrs
op_amp
l_int|1
)paren
)paren
r_continue
suffix:semicolon
id|crc
op_assign
l_int|0xffffffff
suffix:semicolon
r_for
c_loop
(paren
id|byte
op_assign
l_int|0
suffix:semicolon
id|byte
OL
l_int|6
suffix:semicolon
id|byte
op_increment
)paren
r_for
c_loop
(paren
id|bit
op_assign
op_star
id|addrs
op_increment
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
comma
id|bit
op_rshift_assign
l_int|1
)paren
(brace
r_int
id|test
suffix:semicolon
id|test
op_assign
(paren
(paren
id|bit
op_xor
id|crc
)paren
op_amp
l_int|0x01
)paren
suffix:semicolon
id|crc
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|test
)paren
(brace
id|crc
op_assign
id|crc
op_xor
id|poly
suffix:semicolon
)brace
)brace
id|crc
op_assign
id|crc
op_rshift
l_int|26
suffix:semicolon
id|mcast_table
(braket
id|crc
op_rshift
l_int|4
)braket
op_or_assign
l_int|1
op_lshift
(paren
id|crc
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|lance_set_multicast
r_void
id|lance_set_multicast
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|lance_private
op_star
id|lp
op_assign
(paren
r_struct
id|lance_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_volatile
r_struct
id|lance_init_block
op_star
id|ib
op_assign
id|lp-&gt;init_block
suffix:semicolon
r_int
id|stopped
suffix:semicolon
id|DECLARE_LL
suffix:semicolon
id|stopped
op_assign
id|netif_queue_stopped
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stopped
)paren
id|netif_stop_queue
(paren
id|dev
)paren
suffix:semicolon
r_while
c_loop
(paren
id|lp-&gt;tx_old
op_ne
id|lp-&gt;tx_new
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|WRITERAP
c_func
(paren
id|LE_CSR0
)paren
suffix:semicolon
id|WRITERDP
c_func
(paren
id|LE_C0_STOP
)paren
suffix:semicolon
id|lance_init_ring
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|IFF_PROMISC
)paren
(brace
id|ib-&gt;mode
op_or_assign
id|LE_MO_PROM
suffix:semicolon
)brace
r_else
(brace
id|ib-&gt;mode
op_and_assign
op_complement
id|LE_MO_PROM
suffix:semicolon
id|lance_load_multicast
(paren
id|dev
)paren
suffix:semicolon
)brace
id|load_csrs
(paren
id|lp
)paren
suffix:semicolon
id|init_restart_lance
(paren
id|lp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stopped
)paren
id|netif_start_queue
(paren
id|dev
)paren
suffix:semicolon
)brace
eof
