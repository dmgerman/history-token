multiline_comment|/**************************************************&n; *                                                *&n; * Definition of D-Link Ethernet Pocket adapter   *&n; *                                                *&n; **************************************************/
multiline_comment|/*&n; * D-Link Ethernet pocket adapter ports&n; */
multiline_comment|/*&n; * OK, so I&squot;m cheating, but there are an awful lot of&n; * reads and writes in order to get anything in and out&n; * of the DE-600 with 4 bits at a time in the parallel port,&n; * so every saved instruction really helps :-)&n; */
macro_line|#ifndef DE600_IO
DECL|macro|DE600_IO
mdefine_line|#define DE600_IO&t;0x378
macro_line|#endif
DECL|macro|DATA_PORT
mdefine_line|#define DATA_PORT&t;(DE600_IO)
DECL|macro|STATUS_PORT
mdefine_line|#define STATUS_PORT&t;(DE600_IO + 1)
DECL|macro|COMMAND_PORT
mdefine_line|#define COMMAND_PORT&t;(DE600_IO + 2)
macro_line|#ifndef DE600_IRQ
DECL|macro|DE600_IRQ
mdefine_line|#define DE600_IRQ&t;7
macro_line|#endif
multiline_comment|/*&n; * It really should look like this, and autoprobing as well...&n; *&n;#define DATA_PORT&t;(dev-&gt;base_addr + 0)&n;#define STATUS_PORT&t;(dev-&gt;base_addr + 1)&n;#define COMMAND_PORT&t;(dev-&gt;base_addr + 2)&n;#define DE600_IRQ&t;dev-&gt;irq&n; */
multiline_comment|/*&n; * D-Link COMMAND_PORT commands&n; */
DECL|macro|SELECT_NIC
mdefine_line|#define SELECT_NIC&t;0x04 /* select Network Interface Card */
DECL|macro|SELECT_PRN
mdefine_line|#define SELECT_PRN&t;0x1c /* select Printer */
DECL|macro|NML_PRN
mdefine_line|#define NML_PRN&t;&t;0xec /* normal Printer situation */
DECL|macro|IRQEN
mdefine_line|#define IRQEN&t;&t;0x10 /* enable IRQ line */
multiline_comment|/*&n; * D-Link STATUS_PORT&n; */
DECL|macro|RX_BUSY
mdefine_line|#define RX_BUSY&t;&t;0x80
DECL|macro|RX_GOOD
mdefine_line|#define RX_GOOD&t;&t;0x40
DECL|macro|TX_FAILED16
mdefine_line|#define TX_FAILED16&t;0x10
DECL|macro|TX_BUSY
mdefine_line|#define TX_BUSY&t;&t;0x08
multiline_comment|/*&n; * D-Link DATA_PORT commands&n; * command in low 4 bits&n; * data in high 4 bits&n; * select current data nibble with HI_NIBBLE bit&n; */
DECL|macro|WRITE_DATA
mdefine_line|#define WRITE_DATA&t;0x00 /* write memory */
DECL|macro|READ_DATA
mdefine_line|#define READ_DATA&t;0x01 /* read memory */
DECL|macro|STATUS
mdefine_line|#define STATUS&t;&t;0x02 /* read  status register */
DECL|macro|COMMAND
mdefine_line|#define COMMAND&t;&t;0x03 /* write command register (see COMMAND below) */
DECL|macro|NULL_COMMAND
mdefine_line|#define NULL_COMMAND&t;0x04 /* null command */
DECL|macro|RX_LEN
mdefine_line|#define RX_LEN&t;&t;0x05 /* read  received packet length */
DECL|macro|TX_ADDR
mdefine_line|#define TX_ADDR&t;&t;0x06 /* set adapter transmit memory address */
DECL|macro|RW_ADDR
mdefine_line|#define RW_ADDR&t;&t;0x07 /* set adapter read/write memory address */
DECL|macro|HI_NIBBLE
mdefine_line|#define HI_NIBBLE&t;0x08 /* read/write the high nibble of data,&n;&t;&t;&t;&t;or-ed with rest of command */
multiline_comment|/*&n; * command register, accessed through DATA_PORT with low bits = COMMAND&n; */
DECL|macro|RX_ALL
mdefine_line|#define RX_ALL&t;&t;0x01 /* PROMISCUOUS */
DECL|macro|RX_BP
mdefine_line|#define RX_BP&t;&t;0x02 /* default: BROADCAST &amp; PHYSICAL ADDRESS */
DECL|macro|RX_MBP
mdefine_line|#define RX_MBP&t;&t;0x03 /* MULTICAST, BROADCAST &amp; PHYSICAL ADDRESS */
DECL|macro|TX_ENABLE
mdefine_line|#define TX_ENABLE&t;0x04 /* bit 2 */
DECL|macro|RX_ENABLE
mdefine_line|#define RX_ENABLE&t;0x08 /* bit 3 */
DECL|macro|RESET
mdefine_line|#define RESET&t;&t;0x80 /* set bit 7 high */
DECL|macro|STOP_RESET
mdefine_line|#define STOP_RESET&t;0x00 /* set bit 7 low */
multiline_comment|/*&n; * data to command register&n; * (high 4 bits in write to DATA_PORT)&n; */
DECL|macro|RX_PAGE2_SELECT
mdefine_line|#define RX_PAGE2_SELECT&t;0x10 /* bit 4, only 2 pages to select */
DECL|macro|RX_BASE_PAGE
mdefine_line|#define RX_BASE_PAGE&t;0x20 /* bit 5, always set when specifying RX_ADDR */
DECL|macro|FLIP_IRQ
mdefine_line|#define FLIP_IRQ&t;0x40 /* bit 6 */
multiline_comment|/*&n; * D-Link adapter internal memory:&n; *&n; * 0-2K 1:st transmit page (send from pointer up to 2K)&n; * 2-4K&t;2:nd transmit page (send from pointer up to 4K)&n; *&n; * 4-6K 1:st receive page (data from 4K upwards)&n; * 6-8K 2:nd receive page (data from 6K upwards)&n; *&n; * 8K+&t;Adapter ROM (contains magic code and last 3 bytes of Ethernet address)&n; */
DECL|macro|MEM_2K
mdefine_line|#define MEM_2K&t;&t;0x0800 /* 2048 */
DECL|macro|MEM_4K
mdefine_line|#define MEM_4K&t;&t;0x1000 /* 4096 */
DECL|macro|MEM_6K
mdefine_line|#define MEM_6K&t;&t;0x1800 /* 6144 */
DECL|macro|NODE_ADDRESS
mdefine_line|#define NODE_ADDRESS&t;0x2000 /* 8192 */
DECL|macro|RUNT
mdefine_line|#define RUNT 60&t;&t;/* Too small Ethernet packet */
multiline_comment|/**************************************************&n; *                                                *&n; *             End of definition                  *&n; *                                                *&n; **************************************************/
multiline_comment|/*&n; * Index to functions, as function prototypes.&n; */
multiline_comment|/* Routines used internally. (See &quot;convenience macros&quot;) */
r_static
id|u8
id|de600_read_status
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
id|u8
id|de600_read_byte
c_func
(paren
r_int
r_char
id|type
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Put in the device structure. */
r_static
r_int
id|de600_open
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
id|de600_close
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
id|get_stats
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
id|de600_start_xmit
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
multiline_comment|/* Dispatch from interrupts. */
r_static
r_void
id|de600_interrupt
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
r_int
id|de600_tx_intr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|irq_status
)paren
suffix:semicolon
r_static
r_void
id|de600_rx_intr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Initialization */
r_static
r_void
id|trigger_interrupt
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|de600_probe
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
id|adapter_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; * Convenience macros/functions for D-Link adapter&n; */
DECL|macro|select_prn
mdefine_line|#define select_prn() outb_p(SELECT_PRN, COMMAND_PORT); DE600_SLOW_DOWN
DECL|macro|select_nic
mdefine_line|#define select_nic() outb_p(SELECT_NIC, COMMAND_PORT); DE600_SLOW_DOWN
multiline_comment|/* Thanks for hints from Mark Burton &lt;markb@ordern.demon.co.uk&gt; */
DECL|macro|de600_put_byte
mdefine_line|#define de600_put_byte(data) ( &bslash;&n;&t;outb_p(((data) &lt;&lt; 4)   | WRITE_DATA            , DATA_PORT), &bslash;&n;&t;outb_p(((data) &amp; 0xf0) | WRITE_DATA | HI_NIBBLE, DATA_PORT))
multiline_comment|/*&n; * The first two outb_p()&squot;s below could perhaps be deleted if there&n; * would be more delay in the last two. Not certain about it yet...&n; */
DECL|macro|de600_put_command
mdefine_line|#define de600_put_command(cmd) ( &bslash;&n;&t;outb_p(( rx_page        &lt;&lt; 4)   | COMMAND            , DATA_PORT), &bslash;&n;&t;outb_p(( rx_page        &amp; 0xf0) | COMMAND | HI_NIBBLE, DATA_PORT), &bslash;&n;&t;outb_p(((rx_page | cmd) &lt;&lt; 4)   | COMMAND            , DATA_PORT), &bslash;&n;&t;outb_p(((rx_page | cmd) &amp; 0xf0) | COMMAND | HI_NIBBLE, DATA_PORT))
DECL|macro|de600_setup_address
mdefine_line|#define de600_setup_address(addr,type) ( &bslash;&n;&t;outb_p((((addr) &lt;&lt; 4) &amp; 0xf0) | type            , DATA_PORT), &bslash;&n;&t;outb_p(( (addr)       &amp; 0xf0) | type | HI_NIBBLE, DATA_PORT), &bslash;&n;&t;outb_p((((addr) &gt;&gt; 4) &amp; 0xf0) | type            , DATA_PORT), &bslash;&n;&t;outb_p((((addr) &gt;&gt; 8) &amp; 0xf0) | type | HI_NIBBLE, DATA_PORT))
DECL|macro|rx_page_adr
mdefine_line|#define rx_page_adr() ((rx_page &amp; RX_PAGE2_SELECT)?(MEM_6K):(MEM_4K))
multiline_comment|/* Flip bit, only 2 pages */
DECL|macro|next_rx_page
mdefine_line|#define next_rx_page() (rx_page ^= RX_PAGE2_SELECT)
DECL|macro|tx_page_adr
mdefine_line|#define tx_page_adr(a) (((a) + 1) * MEM_2K)
eof
