multiline_comment|/*&n; * SL811HS register declarations and HCD data structures&n; *&n; * Copyright (C) 2004 Psion Teklogix&n; * Copyright (C) 2004 David Brownell&n; * Copyright (C) 2001 Cypress Semiconductor Inc. &n; */
multiline_comment|/*&n; * SL811HS has transfer registers, and control registers.  In host/master&n; * mode one set of registers is used; in peripheral/slave mode, another.&n; *  - SL11H only has some &quot;A&quot; transfer registers from 0x00-0x04&n; *  - SL811HS also has &quot;B&quot; registers from 0x08-0x0c&n; *  - SL811S (or HS in slave mode) has four A+B sets, at 00, 10, 20, 30&n; */
DECL|macro|SL811_EP_A
mdefine_line|#define SL811_EP_A(base)&t;((base) + 0)
DECL|macro|SL811_EP_B
mdefine_line|#define SL811_EP_B(base)&t;((base) + 8)
DECL|macro|SL811_HOST_BUF
mdefine_line|#define SL811_HOST_BUF&t;&t;0x00
DECL|macro|SL811_PERIPH_EP0
mdefine_line|#define SL811_PERIPH_EP0&t;0x00
DECL|macro|SL811_PERIPH_EP1
mdefine_line|#define SL811_PERIPH_EP1&t;0x10
DECL|macro|SL811_PERIPH_EP2
mdefine_line|#define SL811_PERIPH_EP2&t;0x20
DECL|macro|SL811_PERIPH_EP3
mdefine_line|#define SL811_PERIPH_EP3&t;0x30
multiline_comment|/* TRANSFER REGISTERS:  host and peripheral sides are similar&n; * except for the control models (master vs slave).&n; */
DECL|macro|SL11H_HOSTCTLREG
mdefine_line|#define SL11H_HOSTCTLREG&t;0
DECL|macro|SL11H_HCTLMASK_ARM
macro_line|#&t;define SL11H_HCTLMASK_ARM&t;0x01
DECL|macro|SL11H_HCTLMASK_ENABLE
macro_line|#&t;define SL11H_HCTLMASK_ENABLE&t;0x02
DECL|macro|SL11H_HCTLMASK_IN
macro_line|#&t;define SL11H_HCTLMASK_IN&t;0x00
DECL|macro|SL11H_HCTLMASK_OUT
macro_line|#&t;define SL11H_HCTLMASK_OUT&t;0x04
DECL|macro|SL11H_HCTLMASK_ISOCH
macro_line|#&t;define SL11H_HCTLMASK_ISOCH&t;0x10
DECL|macro|SL11H_HCTLMASK_AFTERSOF
macro_line|#&t;define SL11H_HCTLMASK_AFTERSOF&t;0x20
DECL|macro|SL11H_HCTLMASK_TOGGLE
macro_line|#&t;define SL11H_HCTLMASK_TOGGLE&t;0x40
DECL|macro|SL11H_HCTLMASK_PREAMBLE
macro_line|#&t;define SL11H_HCTLMASK_PREAMBLE&t;0x80
DECL|macro|SL11H_BUFADDRREG
mdefine_line|#define SL11H_BUFADDRREG&t;1
DECL|macro|SL11H_BUFLNTHREG
mdefine_line|#define SL11H_BUFLNTHREG&t;2
DECL|macro|SL11H_PKTSTATREG
mdefine_line|#define SL11H_PKTSTATREG&t;3&t;/* read */
DECL|macro|SL11H_STATMASK_ACK
macro_line|#&t;define SL11H_STATMASK_ACK&t;0x01
DECL|macro|SL11H_STATMASK_ERROR
macro_line|#&t;define SL11H_STATMASK_ERROR&t;0x02
DECL|macro|SL11H_STATMASK_TMOUT
macro_line|#&t;define SL11H_STATMASK_TMOUT&t;0x04
DECL|macro|SL11H_STATMASK_SEQ
macro_line|#&t;define SL11H_STATMASK_SEQ&t;0x08
DECL|macro|SL11H_STATMASK_SETUP
macro_line|#&t;define SL11H_STATMASK_SETUP&t;0x10
DECL|macro|SL11H_STATMASK_OVF
macro_line|#&t;define SL11H_STATMASK_OVF&t;0x20
DECL|macro|SL11H_STATMASK_NAK
macro_line|#&t;define SL11H_STATMASK_NAK&t;0x40
DECL|macro|SL11H_STATMASK_STALL
macro_line|#&t;define SL11H_STATMASK_STALL&t;0x80
DECL|macro|SL11H_PIDEPREG
mdefine_line|#define SL11H_PIDEPREG&t;&t;3&t;/* write */
DECL|macro|SL_SETUP
macro_line|#&t;define&t;SL_SETUP&t;0xd0
DECL|macro|SL_IN
macro_line|#&t;define&t;SL_IN&t;&t;0x90
DECL|macro|SL_OUT
macro_line|#&t;define&t;SL_OUT&t;&t;0x10
DECL|macro|SL_SOF
macro_line|#&t;define&t;SL_SOF&t;&t;0x50
DECL|macro|SL_PREAMBLE
macro_line|#&t;define&t;SL_PREAMBLE&t;0xc0
DECL|macro|SL_NAK
macro_line|#&t;define&t;SL_NAK&t;&t;0xa0
DECL|macro|SL_STALL
macro_line|#&t;define&t;SL_STALL&t;0xe0
DECL|macro|SL_DATA0
macro_line|#&t;define&t;SL_DATA0&t;0x30
DECL|macro|SL_DATA1
macro_line|#&t;define&t;SL_DATA1&t;0xb0
DECL|macro|SL11H_XFERCNTREG
mdefine_line|#define SL11H_XFERCNTREG&t;4&t;/* read */
DECL|macro|SL11H_DEVADDRREG
mdefine_line|#define SL11H_DEVADDRREG&t;4&t;/* write */
multiline_comment|/* CONTROL REGISTERS:  host and peripheral are very different.&n; */
DECL|macro|SL11H_CTLREG1
mdefine_line|#define SL11H_CTLREG1&t;&t;5
DECL|macro|SL11H_CTL1MASK_SOF_ENA
macro_line|#&t;define SL11H_CTL1MASK_SOF_ENA&t;0x01
DECL|macro|SL11H_CTL1MASK_FORCE
macro_line|#&t;define SL11H_CTL1MASK_FORCE&t;0x18
DECL|macro|SL11H_CTL1MASK_NORMAL
macro_line|#&t;&t;define SL11H_CTL1MASK_NORMAL&t;0x00
DECL|macro|SL11H_CTL1MASK_SE0
macro_line|#&t;&t;define SL11H_CTL1MASK_SE0&t;0x08&t;/* reset */
DECL|macro|SL11H_CTL1MASK_J
macro_line|#&t;&t;define SL11H_CTL1MASK_J&t;&t;0x10
DECL|macro|SL11H_CTL1MASK_K
macro_line|#&t;&t;define SL11H_CTL1MASK_K&t;&t;0x18&t;/* resume */
DECL|macro|SL11H_CTL1MASK_LSPD
macro_line|#&t;define SL11H_CTL1MASK_LSPD&t;0x20
DECL|macro|SL11H_CTL1MASK_SUSPEND
macro_line|#&t;define SL11H_CTL1MASK_SUSPEND&t;0x40
DECL|macro|SL11H_IRQ_ENABLE
mdefine_line|#define SL11H_IRQ_ENABLE&t;6
DECL|macro|SL11H_INTMASK_DONE_A
macro_line|#&t;define SL11H_INTMASK_DONE_A&t;0x01
DECL|macro|SL11H_INTMASK_DONE_B
macro_line|#&t;define SL11H_INTMASK_DONE_B&t;0x02
DECL|macro|SL11H_INTMASK_SOFINTR
macro_line|#&t;define SL11H_INTMASK_SOFINTR&t;0x10
DECL|macro|SL11H_INTMASK_INSRMV
macro_line|#&t;define SL11H_INTMASK_INSRMV&t;0x20&t;/* to/from SE0 */
DECL|macro|SL11H_INTMASK_RD
macro_line|#&t;define SL11H_INTMASK_RD&t;&t;0x40
DECL|macro|SL11H_INTMASK_DP
macro_line|#&t;define SL11H_INTMASK_DP&t;&t;0x80&t;/* only in INTSTATREG */
DECL|macro|SL11S_ADDRESS
mdefine_line|#define SL11S_ADDRESS&t;&t;7
multiline_comment|/* 0x08-0x0c are for the B buffer (not in SL11) */
DECL|macro|SL11H_IRQ_STATUS
mdefine_line|#define SL11H_IRQ_STATUS&t;0x0D&t;/* write to ack */
DECL|macro|SL11H_HWREVREG
mdefine_line|#define SL11H_HWREVREG&t;&t;0x0E&t;/* read */
DECL|macro|SL11H_HWRMASK_HWREV
macro_line|#&t;define SL11H_HWRMASK_HWREV&t;0xF0
DECL|macro|SL11H_SOFLOWREG
mdefine_line|#define SL11H_SOFLOWREG&t;&t;0x0E&t;/* write */
DECL|macro|SL11H_SOFTMRREG
mdefine_line|#define SL11H_SOFTMRREG&t;&t;0x0F&t;/* read */
multiline_comment|/* a write to this register enables SL811HS features.&n; * HOST flag presumably overrides the chip input signal?&n; */
DECL|macro|SL811HS_CTLREG2
mdefine_line|#define SL811HS_CTLREG2&t;&t;0x0F
DECL|macro|SL811HS_CTL2MASK_SOF_MASK
macro_line|#&t;define SL811HS_CTL2MASK_SOF_MASK&t;0x3F
DECL|macro|SL811HS_CTL2MASK_DSWAP
macro_line|#&t;define SL811HS_CTL2MASK_DSWAP&t;&t;0x40
DECL|macro|SL811HS_CTL2MASK_HOST
macro_line|#&t;define SL811HS_CTL2MASK_HOST&t;&t;0x80
DECL|macro|SL811HS_CTL2_INIT
mdefine_line|#define SL811HS_CTL2_INIT&t;(SL811HS_CTL2MASK_HOST | 0x2e)
multiline_comment|/* DATA BUFFERS: registers from 0x10..0xff are for data buffers;&n; * that&squot;s 240 bytes, which we&squot;ll split evenly between A and B sides.&n; * Only ISO can use more than 64 bytes per packet.&n; * (The SL11S has 0x40..0xff for buffers.)&n; */
DECL|macro|H_MAXPACKET
mdefine_line|#define H_MAXPACKET&t;120&t;&t;/* bytes in A or B fifos */
DECL|macro|SL11H_DATA_START
mdefine_line|#define SL11H_DATA_START&t;0x10
DECL|macro|SL811HS_PACKET_BUF
mdefine_line|#define&t;SL811HS_PACKET_BUF(is_a)&t;((is_a) &bslash;&n;&t;&t;? SL11H_DATA_START &bslash;&n;&t;&t;: (SL11H_DATA_START + H_MAXPACKET))
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|macro|LOG2_PERIODIC_SIZE
mdefine_line|#define&t;LOG2_PERIODIC_SIZE&t;5&t;/* arbitrary; this matches OHCI */
DECL|macro|PERIODIC_SIZE
mdefine_line|#define&t;PERIODIC_SIZE&t;&t;(1 &lt;&lt; LOG2_PERIODIC_SIZE)
DECL|struct|sl811
r_struct
id|sl811
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|addr_reg
r_void
id|__iomem
op_star
id|addr_reg
suffix:semicolon
DECL|member|data_reg
r_void
id|__iomem
op_star
id|data_reg
suffix:semicolon
DECL|member|board
r_struct
id|sl811_platform_data
op_star
id|board
suffix:semicolon
DECL|member|pde
r_struct
id|proc_dir_entry
op_star
id|pde
suffix:semicolon
DECL|member|stat_insrmv
r_int
r_int
id|stat_insrmv
suffix:semicolon
DECL|member|stat_wake
r_int
r_int
id|stat_wake
suffix:semicolon
DECL|member|stat_sof
r_int
r_int
id|stat_sof
suffix:semicolon
DECL|member|stat_a
r_int
r_int
id|stat_a
suffix:semicolon
DECL|member|stat_b
r_int
r_int
id|stat_b
suffix:semicolon
DECL|member|stat_lost
r_int
r_int
id|stat_lost
suffix:semicolon
DECL|member|stat_overrun
r_int
r_int
id|stat_overrun
suffix:semicolon
multiline_comment|/* sw model */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|next_periodic
r_struct
id|sl811h_ep
op_star
id|next_periodic
suffix:semicolon
DECL|member|next_async
r_struct
id|sl811h_ep
op_star
id|next_async
suffix:semicolon
DECL|member|active_a
r_struct
id|sl811h_ep
op_star
id|active_a
suffix:semicolon
DECL|member|jiffies_a
r_int
r_int
id|jiffies_a
suffix:semicolon
DECL|member|active_b
r_struct
id|sl811h_ep
op_star
id|active_b
suffix:semicolon
DECL|member|jiffies_b
r_int
r_int
id|jiffies_b
suffix:semicolon
DECL|member|port1
id|u32
id|port1
suffix:semicolon
DECL|member|ctrl1
DECL|member|ctrl2
DECL|member|irq_enable
id|u8
id|ctrl1
comma
id|ctrl2
comma
id|irq_enable
suffix:semicolon
DECL|member|frame
id|u16
id|frame
suffix:semicolon
multiline_comment|/* async schedule: control, bulk */
DECL|member|async
r_struct
id|list_head
id|async
suffix:semicolon
multiline_comment|/* periodic schedule: interrupt, iso */
DECL|member|load
id|u16
id|load
(braket
id|PERIODIC_SIZE
)braket
suffix:semicolon
DECL|member|periodic
r_struct
id|sl811h_ep
op_star
id|periodic
(braket
id|PERIODIC_SIZE
)braket
suffix:semicolon
DECL|member|periodic_count
r_int
id|periodic_count
suffix:semicolon
)brace
suffix:semicolon
DECL|function|hcd_to_sl811
r_static
r_inline
r_struct
id|sl811
op_star
id|hcd_to_sl811
c_func
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_return
(paren
r_struct
id|sl811
op_star
)paren
(paren
id|hcd-&gt;hcd_priv
)paren
suffix:semicolon
)brace
DECL|function|sl811_to_hcd
r_static
r_inline
r_struct
id|usb_hcd
op_star
id|sl811_to_hcd
c_func
(paren
r_struct
id|sl811
op_star
id|sl811
)paren
(brace
r_return
id|container_of
c_func
(paren
(paren
r_void
op_star
)paren
id|sl811
comma
r_struct
id|usb_hcd
comma
id|hcd_priv
)paren
suffix:semicolon
)brace
DECL|struct|sl811h_ep
r_struct
id|sl811h_ep
(brace
DECL|member|hep
r_struct
id|usb_host_endpoint
op_star
id|hep
suffix:semicolon
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|defctrl
id|u8
id|defctrl
suffix:semicolon
DECL|member|maxpacket
id|u8
id|maxpacket
suffix:semicolon
DECL|member|epnum
id|u8
id|epnum
suffix:semicolon
DECL|member|nextpid
id|u8
id|nextpid
suffix:semicolon
DECL|member|error_count
id|u16
id|error_count
suffix:semicolon
DECL|member|nak_count
id|u16
id|nak_count
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
multiline_comment|/* of current packet */
multiline_comment|/* periodic schedule */
DECL|member|period
id|u16
id|period
suffix:semicolon
DECL|member|branch
id|u16
id|branch
suffix:semicolon
DECL|member|load
id|u16
id|load
suffix:semicolon
DECL|member|next
r_struct
id|sl811h_ep
op_star
id|next
suffix:semicolon
multiline_comment|/* async schedule */
DECL|member|schedule
r_struct
id|list_head
id|schedule
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* These register utilities should work for the SL811S register API too&n; * NOTE:  caller must hold sl811-&gt;lock.&n; */
DECL|function|sl811_read
r_static
r_inline
id|u8
id|sl811_read
c_func
(paren
r_struct
id|sl811
op_star
id|sl811
comma
r_int
id|reg
)paren
(brace
id|writeb
c_func
(paren
id|reg
comma
id|sl811-&gt;addr_reg
)paren
suffix:semicolon
r_return
id|readb
c_func
(paren
id|sl811-&gt;data_reg
)paren
suffix:semicolon
)brace
DECL|function|sl811_write
r_static
r_inline
r_void
id|sl811_write
c_func
(paren
r_struct
id|sl811
op_star
id|sl811
comma
r_int
id|reg
comma
id|u8
id|val
)paren
(brace
id|writeb
c_func
(paren
id|reg
comma
id|sl811-&gt;addr_reg
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|val
comma
id|sl811-&gt;data_reg
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|sl811_write_buf
id|sl811_write_buf
c_func
(paren
r_struct
id|sl811
op_star
id|sl811
comma
r_int
id|addr
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_const
id|u8
op_star
id|data
suffix:semicolon
r_void
id|__iomem
op_star
id|data_reg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
suffix:semicolon
id|writeb
c_func
(paren
id|addr
comma
id|sl811-&gt;addr_reg
)paren
suffix:semicolon
id|data
op_assign
id|buf
suffix:semicolon
id|data_reg
op_assign
id|sl811-&gt;data_reg
suffix:semicolon
r_do
(brace
id|writeb
c_func
(paren
op_star
id|data
op_increment
comma
id|data_reg
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|count
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|sl811_read_buf
id|sl811_read_buf
c_func
(paren
r_struct
id|sl811
op_star
id|sl811
comma
r_int
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|count
)paren
(brace
id|u8
op_star
id|data
suffix:semicolon
r_void
id|__iomem
op_star
id|data_reg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
suffix:semicolon
id|writeb
c_func
(paren
id|addr
comma
id|sl811-&gt;addr_reg
)paren
suffix:semicolon
id|data
op_assign
id|buf
suffix:semicolon
id|data_reg
op_assign
id|sl811-&gt;data_reg
suffix:semicolon
r_do
(brace
op_star
id|data
op_increment
op_assign
id|readb
c_func
(paren
id|data_reg
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(stuff...)&t;&t;printk(KERN_DEBUG &quot;sl811: &quot; stuff)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(stuff...)&t;&t;do{}while(0)
macro_line|#endif
macro_line|#ifdef VERBOSE
DECL|macro|VDBG
macro_line|#    define VDBG&t;&t;DBG
macro_line|#else
DECL|macro|VDBG
macro_line|#    define VDBG(stuff...)&t;do{}while(0)
macro_line|#endif
macro_line|#ifdef PACKET_TRACE
DECL|macro|PACKET
macro_line|#    define PACKET&t;&t;VDBG
macro_line|#else
DECL|macro|PACKET
macro_line|#    define PACKET(stuff...)&t;do{}while(0)
macro_line|#endif
DECL|macro|ERR
mdefine_line|#define ERR(stuff...)&t;&t;printk(KERN_ERR &quot;sl811: &quot; stuff)
DECL|macro|WARN
mdefine_line|#define WARN(stuff...)&t;&t;printk(KERN_WARNING &quot;sl811: &quot; stuff)
DECL|macro|INFO
mdefine_line|#define INFO(stuff...)&t;&t;printk(KERN_INFO &quot;sl811: &quot; stuff)
eof
