multiline_comment|/* $Id: parport.h,v 1.1 1998/05/17 10:57:52 andrea Exp andrea $ */
multiline_comment|/*&n; * Any part of this program may be used in documents licensed under&n; * the GNU Free Documentation License, Version 1.1 or any later version&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _PARPORT_H_
DECL|macro|_PARPORT_H_
mdefine_line|#define _PARPORT_H_
multiline_comment|/* Start off with user-visible constants */
multiline_comment|/* Maximum of 16 ports per machine */
DECL|macro|PARPORT_MAX
mdefine_line|#define PARPORT_MAX  16
multiline_comment|/* Magic numbers */
DECL|macro|PARPORT_IRQ_NONE
mdefine_line|#define PARPORT_IRQ_NONE  -1
DECL|macro|PARPORT_DMA_NONE
mdefine_line|#define PARPORT_DMA_NONE  -1
DECL|macro|PARPORT_IRQ_AUTO
mdefine_line|#define PARPORT_IRQ_AUTO  -2
DECL|macro|PARPORT_DMA_AUTO
mdefine_line|#define PARPORT_DMA_AUTO  -2
DECL|macro|PARPORT_DMA_NOFIFO
mdefine_line|#define PARPORT_DMA_NOFIFO -3
DECL|macro|PARPORT_DISABLE
mdefine_line|#define PARPORT_DISABLE   -2
DECL|macro|PARPORT_IRQ_PROBEONLY
mdefine_line|#define PARPORT_IRQ_PROBEONLY -3
DECL|macro|PARPORT_IOHI_AUTO
mdefine_line|#define PARPORT_IOHI_AUTO -1
DECL|macro|PARPORT_CONTROL_STROBE
mdefine_line|#define PARPORT_CONTROL_STROBE    0x1
DECL|macro|PARPORT_CONTROL_AUTOFD
mdefine_line|#define PARPORT_CONTROL_AUTOFD    0x2
DECL|macro|PARPORT_CONTROL_INIT
mdefine_line|#define PARPORT_CONTROL_INIT      0x4
DECL|macro|PARPORT_CONTROL_SELECT
mdefine_line|#define PARPORT_CONTROL_SELECT    0x8
DECL|macro|PARPORT_STATUS_ERROR
mdefine_line|#define PARPORT_STATUS_ERROR      0x8
DECL|macro|PARPORT_STATUS_SELECT
mdefine_line|#define PARPORT_STATUS_SELECT     0x10
DECL|macro|PARPORT_STATUS_PAPEROUT
mdefine_line|#define PARPORT_STATUS_PAPEROUT   0x20
DECL|macro|PARPORT_STATUS_ACK
mdefine_line|#define PARPORT_STATUS_ACK        0x40
DECL|macro|PARPORT_STATUS_BUSY
mdefine_line|#define PARPORT_STATUS_BUSY       0x80
multiline_comment|/* Type classes for Plug-and-Play probe.  */
r_typedef
r_enum
(brace
DECL|enumerator|PARPORT_CLASS_LEGACY
id|PARPORT_CLASS_LEGACY
op_assign
l_int|0
comma
multiline_comment|/* Non-IEEE1284 device */
DECL|enumerator|PARPORT_CLASS_PRINTER
id|PARPORT_CLASS_PRINTER
comma
DECL|enumerator|PARPORT_CLASS_MODEM
id|PARPORT_CLASS_MODEM
comma
DECL|enumerator|PARPORT_CLASS_NET
id|PARPORT_CLASS_NET
comma
DECL|enumerator|PARPORT_CLASS_HDC
id|PARPORT_CLASS_HDC
comma
multiline_comment|/* Hard disk controller */
DECL|enumerator|PARPORT_CLASS_PCMCIA
id|PARPORT_CLASS_PCMCIA
comma
DECL|enumerator|PARPORT_CLASS_MEDIA
id|PARPORT_CLASS_MEDIA
comma
multiline_comment|/* Multimedia device */
DECL|enumerator|PARPORT_CLASS_FDC
id|PARPORT_CLASS_FDC
comma
multiline_comment|/* Floppy disk controller */
DECL|enumerator|PARPORT_CLASS_PORTS
id|PARPORT_CLASS_PORTS
comma
DECL|enumerator|PARPORT_CLASS_SCANNER
id|PARPORT_CLASS_SCANNER
comma
DECL|enumerator|PARPORT_CLASS_DIGCAM
id|PARPORT_CLASS_DIGCAM
comma
DECL|enumerator|PARPORT_CLASS_OTHER
id|PARPORT_CLASS_OTHER
comma
multiline_comment|/* Anything else */
DECL|enumerator|PARPORT_CLASS_UNSPEC
id|PARPORT_CLASS_UNSPEC
comma
multiline_comment|/* No CLS field in ID */
DECL|enumerator|PARPORT_CLASS_SCSIADAPTER
id|PARPORT_CLASS_SCSIADAPTER
DECL|typedef|parport_device_class
)brace
id|parport_device_class
suffix:semicolon
multiline_comment|/* The &quot;modes&quot; entry in parport is a bit field representing the&n;   capabilities of the hardware. */
DECL|macro|PARPORT_MODE_PCSPP
mdefine_line|#define PARPORT_MODE_PCSPP&t;(1&lt;&lt;0) /* IBM PC registers available. */
DECL|macro|PARPORT_MODE_TRISTATE
mdefine_line|#define PARPORT_MODE_TRISTATE&t;(1&lt;&lt;1) /* Can tristate. */
DECL|macro|PARPORT_MODE_EPP
mdefine_line|#define PARPORT_MODE_EPP&t;(1&lt;&lt;2) /* Hardware EPP. */
DECL|macro|PARPORT_MODE_ECP
mdefine_line|#define PARPORT_MODE_ECP&t;(1&lt;&lt;3) /* Hardware ECP. */
DECL|macro|PARPORT_MODE_COMPAT
mdefine_line|#define PARPORT_MODE_COMPAT&t;(1&lt;&lt;4) /* Hardware &squot;printer protocol&squot;. */
DECL|macro|PARPORT_MODE_DMA
mdefine_line|#define PARPORT_MODE_DMA&t;(1&lt;&lt;5) /* Hardware can DMA. */
DECL|macro|PARPORT_MODE_SAFEININT
mdefine_line|#define PARPORT_MODE_SAFEININT&t;(1&lt;&lt;6) /* SPP registers accessible in IRQ. */
multiline_comment|/* IEEE1284 modes: &n;   Nibble mode, byte mode, ECP, ECPRLE and EPP are their own&n;   &squot;extensibility request&squot; values.  Others are special.&n;   &squot;Real&squot; ECP modes must have the IEEE1284_MODE_ECP bit set.  */
DECL|macro|IEEE1284_MODE_NIBBLE
mdefine_line|#define IEEE1284_MODE_NIBBLE             0
DECL|macro|IEEE1284_MODE_BYTE
mdefine_line|#define IEEE1284_MODE_BYTE              (1&lt;&lt;0)
DECL|macro|IEEE1284_MODE_COMPAT
mdefine_line|#define IEEE1284_MODE_COMPAT            (1&lt;&lt;8)
DECL|macro|IEEE1284_MODE_BECP
mdefine_line|#define IEEE1284_MODE_BECP              (1&lt;&lt;9) /* Bounded ECP mode */
DECL|macro|IEEE1284_MODE_ECP
mdefine_line|#define IEEE1284_MODE_ECP               (1&lt;&lt;4)
DECL|macro|IEEE1284_MODE_ECPRLE
mdefine_line|#define IEEE1284_MODE_ECPRLE            (IEEE1284_MODE_ECP | (1&lt;&lt;5))
DECL|macro|IEEE1284_MODE_ECPSWE
mdefine_line|#define IEEE1284_MODE_ECPSWE            (1&lt;&lt;10) /* Software-emulated */
DECL|macro|IEEE1284_MODE_EPP
mdefine_line|#define IEEE1284_MODE_EPP               (1&lt;&lt;6)
DECL|macro|IEEE1284_MODE_EPPSL
mdefine_line|#define IEEE1284_MODE_EPPSL             (1&lt;&lt;11) /* EPP 1.7 */
DECL|macro|IEEE1284_MODE_EPPSWE
mdefine_line|#define IEEE1284_MODE_EPPSWE            (1&lt;&lt;12) /* Software-emulated */
DECL|macro|IEEE1284_DEVICEID
mdefine_line|#define IEEE1284_DEVICEID               (1&lt;&lt;2)  /* This is a flag */
DECL|macro|IEEE1284_EXT_LINK
mdefine_line|#define IEEE1284_EXT_LINK               (1&lt;&lt;14) /* This flag causes the&n;&t;&t;&t;&t;&t;&t; * extensibility link to&n;&t;&t;&t;&t;&t;&t; * be requested, using&n;&t;&t;&t;&t;&t;&t; * bits 0-6. */
multiline_comment|/* For the benefit of parport_read/write, you can use these with&n; * parport_negotiate to use address operations.  They have no effect&n; * other than to make parport_read/write use address transfers. */
DECL|macro|IEEE1284_ADDR
mdefine_line|#define IEEE1284_ADDR&t;&t;&t;(1&lt;&lt;13)&t;/* This is a flag */
DECL|macro|IEEE1284_DATA
mdefine_line|#define IEEE1284_DATA&t;&t;&t; 0&t;/* So is this */
multiline_comment|/* Flags for block transfer operations. */
DECL|macro|PARPORT_EPP_FAST
mdefine_line|#define PARPORT_EPP_FAST&t;&t;(1&lt;&lt;0) /* Unreliable counts. */
DECL|macro|PARPORT_W91284PIC
mdefine_line|#define PARPORT_W91284PIC&t;&t;(1&lt;&lt;1) /* have a Warp9 w91284pic in the device */
multiline_comment|/* The rest is for the kernel only */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
multiline_comment|/* Define this later. */
r_struct
id|parport
suffix:semicolon
r_struct
id|pardevice
suffix:semicolon
DECL|struct|pc_parport_state
r_struct
id|pc_parport_state
(brace
DECL|member|ctr
r_int
r_int
id|ctr
suffix:semicolon
DECL|member|ecr
r_int
r_int
id|ecr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ax_parport_state
r_struct
id|ax_parport_state
(brace
DECL|member|ctr
r_int
r_int
id|ctr
suffix:semicolon
DECL|member|ecr
r_int
r_int
id|ecr
suffix:semicolon
DECL|member|dcsr
r_int
r_int
id|dcsr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* used by both parport_amiga and parport_mfc3 */
DECL|struct|amiga_parport_state
r_struct
id|amiga_parport_state
(brace
DECL|member|data
r_int
r_char
id|data
suffix:semicolon
multiline_comment|/* ciaa.prb */
DECL|member|datadir
r_int
r_char
id|datadir
suffix:semicolon
multiline_comment|/* ciaa.ddrb */
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
multiline_comment|/* ciab.pra &amp; 7 */
DECL|member|statusdir
r_int
r_char
id|statusdir
suffix:semicolon
multiline_comment|/* ciab.ddrb &amp; 7 */
)brace
suffix:semicolon
DECL|struct|parport_state
r_struct
id|parport_state
(brace
r_union
(brace
DECL|member|pc
r_struct
id|pc_parport_state
id|pc
suffix:semicolon
multiline_comment|/* ARC has no state. */
DECL|member|ax
r_struct
id|ax_parport_state
id|ax
suffix:semicolon
DECL|member|amiga
r_struct
id|amiga_parport_state
id|amiga
suffix:semicolon
multiline_comment|/* Atari has not state. */
DECL|member|misc
r_void
op_star
id|misc
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|parport_operations
r_struct
id|parport_operations
(brace
multiline_comment|/* IBM PC-style virtual registers. */
DECL|member|write_data
r_void
(paren
op_star
id|write_data
)paren
(paren
r_struct
id|parport
op_star
comma
r_int
r_char
)paren
suffix:semicolon
DECL|member|read_data
r_int
r_char
(paren
op_star
id|read_data
)paren
(paren
r_struct
id|parport
op_star
)paren
suffix:semicolon
DECL|member|write_control
r_void
(paren
op_star
id|write_control
)paren
(paren
r_struct
id|parport
op_star
comma
r_int
r_char
)paren
suffix:semicolon
DECL|member|read_control
r_int
r_char
(paren
op_star
id|read_control
)paren
(paren
r_struct
id|parport
op_star
)paren
suffix:semicolon
DECL|member|frob_control
r_int
r_char
(paren
op_star
id|frob_control
)paren
(paren
r_struct
id|parport
op_star
comma
r_int
r_char
id|mask
comma
r_int
r_char
id|val
)paren
suffix:semicolon
DECL|member|read_status
r_int
r_char
(paren
op_star
id|read_status
)paren
(paren
r_struct
id|parport
op_star
)paren
suffix:semicolon
multiline_comment|/* IRQs. */
DECL|member|enable_irq
r_void
(paren
op_star
id|enable_irq
)paren
(paren
r_struct
id|parport
op_star
)paren
suffix:semicolon
DECL|member|disable_irq
r_void
(paren
op_star
id|disable_irq
)paren
(paren
r_struct
id|parport
op_star
)paren
suffix:semicolon
multiline_comment|/* Data direction. */
DECL|member|data_forward
r_void
(paren
op_star
id|data_forward
)paren
(paren
r_struct
id|parport
op_star
)paren
suffix:semicolon
DECL|member|data_reverse
r_void
(paren
op_star
id|data_reverse
)paren
(paren
r_struct
id|parport
op_star
)paren
suffix:semicolon
multiline_comment|/* For core parport code. */
DECL|member|init_state
r_void
(paren
op_star
id|init_state
)paren
(paren
r_struct
id|pardevice
op_star
comma
r_struct
id|parport_state
op_star
)paren
suffix:semicolon
DECL|member|save_state
r_void
(paren
op_star
id|save_state
)paren
(paren
r_struct
id|parport
op_star
comma
r_struct
id|parport_state
op_star
)paren
suffix:semicolon
DECL|member|restore_state
r_void
(paren
op_star
id|restore_state
)paren
(paren
r_struct
id|parport
op_star
comma
r_struct
id|parport_state
op_star
)paren
suffix:semicolon
multiline_comment|/* Block read/write */
DECL|member|epp_write_data
r_int
(paren
op_star
id|epp_write_data
)paren
(paren
r_struct
id|parport
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|epp_read_data
r_int
(paren
op_star
id|epp_read_data
)paren
(paren
r_struct
id|parport
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|epp_write_addr
r_int
(paren
op_star
id|epp_write_addr
)paren
(paren
r_struct
id|parport
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|epp_read_addr
r_int
(paren
op_star
id|epp_read_addr
)paren
(paren
r_struct
id|parport
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|ecp_write_data
r_int
(paren
op_star
id|ecp_write_data
)paren
(paren
r_struct
id|parport
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|ecp_read_data
r_int
(paren
op_star
id|ecp_read_data
)paren
(paren
r_struct
id|parport
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|ecp_write_addr
r_int
(paren
op_star
id|ecp_write_addr
)paren
(paren
r_struct
id|parport
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|compat_write_data
r_int
(paren
op_star
id|compat_write_data
)paren
(paren
r_struct
id|parport
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|nibble_read_data
r_int
(paren
op_star
id|nibble_read_data
)paren
(paren
r_struct
id|parport
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|byte_read_data
r_int
(paren
op_star
id|byte_read_data
)paren
(paren
r_struct
id|parport
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|parport_device_info
r_struct
id|parport_device_info
(brace
DECL|member|class
id|parport_device_class
r_class
suffix:semicolon
DECL|member|class_name
r_const
r_char
op_star
id|class_name
suffix:semicolon
DECL|member|mfr
r_const
r_char
op_star
id|mfr
suffix:semicolon
DECL|member|model
r_const
r_char
op_star
id|model
suffix:semicolon
DECL|member|cmdset
r_const
r_char
op_star
id|cmdset
suffix:semicolon
DECL|member|description
r_const
r_char
op_star
id|description
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Each device can have two callback functions:&n; *  1) a preemption function, called by the resource manager to request&n; *     that the driver relinquish control of the port.  The driver should&n; *     return zero if it agrees to release the port, and nonzero if it &n; *     refuses.  Do not call parport_release() - the kernel will do this&n; *     implicitly.&n; *&n; *  2) a wake-up function, called by the resource manager to tell drivers&n; *     that the port is available to be claimed.  If a driver wants to use&n; *     the port, it should call parport_claim() here.&n; */
multiline_comment|/* A parallel port device */
DECL|struct|pardevice
r_struct
id|pardevice
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|port
r_struct
id|parport
op_star
id|port
suffix:semicolon
DECL|member|daisy
r_int
id|daisy
suffix:semicolon
DECL|member|preempt
r_int
(paren
op_star
id|preempt
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|wakeup
r_void
(paren
op_star
id|wakeup
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|irq_func
r_void
(paren
op_star
id|irq_func
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|next
r_struct
id|pardevice
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|pardevice
op_star
id|prev
suffix:semicolon
DECL|member|state
r_struct
id|parport_state
op_star
id|state
suffix:semicolon
multiline_comment|/* saved status over preemption */
DECL|member|wait_q
id|wait_queue_head_t
id|wait_q
suffix:semicolon
DECL|member|time
r_int
r_int
r_int
id|time
suffix:semicolon
DECL|member|timeslice
r_int
r_int
r_int
id|timeslice
suffix:semicolon
DECL|member|timeout
r_volatile
r_int
r_int
id|timeout
suffix:semicolon
DECL|member|waiting
r_int
r_int
id|waiting
suffix:semicolon
multiline_comment|/* long req&squot;d for set_bit --RR */
DECL|member|waitprev
r_struct
id|pardevice
op_star
id|waitprev
suffix:semicolon
DECL|member|waitnext
r_struct
id|pardevice
op_star
id|waitnext
suffix:semicolon
DECL|member|sysctl_table
r_void
op_star
id|sysctl_table
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* IEEE1284 information */
multiline_comment|/* IEEE1284 phases */
DECL|enum|ieee1284_phase
r_enum
id|ieee1284_phase
(brace
DECL|enumerator|IEEE1284_PH_FWD_DATA
id|IEEE1284_PH_FWD_DATA
comma
DECL|enumerator|IEEE1284_PH_FWD_IDLE
id|IEEE1284_PH_FWD_IDLE
comma
DECL|enumerator|IEEE1284_PH_TERMINATE
id|IEEE1284_PH_TERMINATE
comma
DECL|enumerator|IEEE1284_PH_NEGOTIATION
id|IEEE1284_PH_NEGOTIATION
comma
DECL|enumerator|IEEE1284_PH_HBUSY_DNA
id|IEEE1284_PH_HBUSY_DNA
comma
DECL|enumerator|IEEE1284_PH_REV_IDLE
id|IEEE1284_PH_REV_IDLE
comma
DECL|enumerator|IEEE1284_PH_HBUSY_DAVAIL
id|IEEE1284_PH_HBUSY_DAVAIL
comma
DECL|enumerator|IEEE1284_PH_REV_DATA
id|IEEE1284_PH_REV_DATA
comma
DECL|enumerator|IEEE1284_PH_ECP_SETUP
id|IEEE1284_PH_ECP_SETUP
comma
DECL|enumerator|IEEE1284_PH_ECP_FWD_TO_REV
id|IEEE1284_PH_ECP_FWD_TO_REV
comma
DECL|enumerator|IEEE1284_PH_ECP_REV_TO_FWD
id|IEEE1284_PH_ECP_REV_TO_FWD
comma
DECL|enumerator|IEEE1284_PH_ECP_DIR_UNKNOWN
id|IEEE1284_PH_ECP_DIR_UNKNOWN
comma
)brace
suffix:semicolon
DECL|struct|ieee1284_info
r_struct
id|ieee1284_info
(brace
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|phase
r_volatile
r_enum
id|ieee1284_phase
id|phase
suffix:semicolon
DECL|member|irq
r_struct
id|semaphore
id|irq
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A parallel port */
DECL|struct|parport
r_struct
id|parport
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* base address */
DECL|member|base_hi
r_int
r_int
id|base_hi
suffix:semicolon
multiline_comment|/* base address (hi - ECR) */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* IO extent */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|modes
r_int
r_int
id|modes
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* interrupt (or -1 for none) */
DECL|member|dma
r_int
id|dma
suffix:semicolon
DECL|member|muxport
r_int
id|muxport
suffix:semicolon
multiline_comment|/* which muxport (if any) this is */
DECL|member|portnum
r_int
id|portnum
suffix:semicolon
multiline_comment|/* which physical parallel port (not mux) */
DECL|member|physport
r_struct
id|parport
op_star
id|physport
suffix:semicolon
multiline_comment|/* If this is a non-default mux&n;&t;&t;&t;&t;   parport, i.e. we&squot;re a clone of a real&n;&t;&t;&t;&t;   physical port, this is a pointer to that&n;&t;&t;&t;&t;   port. The locking is only done in the&n;&t;&t;&t;&t;   real port.  For a clone port, the&n;&t;&t;&t;&t;   following structure members are&n;&t;&t;&t;&t;   meaningless: devices, cad, muxsel,&n;&t;&t;&t;&t;   waithead, waittail, flags, pdir,&n;&t;&t;&t;&t;   ieee1284, *_lock.&n;&n;&t;&t;&t;&t;   It this is a default mux parport, or&n;&t;&t;&t;&t;   there is no mux involved, this points to&n;&t;&t;&t;&t;   ourself. */
DECL|member|devices
r_struct
id|pardevice
op_star
id|devices
suffix:semicolon
DECL|member|cad
r_struct
id|pardevice
op_star
id|cad
suffix:semicolon
multiline_comment|/* port owner */
DECL|member|daisy
r_int
id|daisy
suffix:semicolon
multiline_comment|/* currently selected daisy addr */
DECL|member|muxsel
r_int
id|muxsel
suffix:semicolon
multiline_comment|/* currently selected mux port */
DECL|member|waithead
r_struct
id|pardevice
op_star
id|waithead
suffix:semicolon
DECL|member|waittail
r_struct
id|pardevice
op_star
id|waittail
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|sysctl_table
r_void
op_star
id|sysctl_table
suffix:semicolon
DECL|member|probe_info
r_struct
id|parport_device_info
id|probe_info
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* 0-3 + non-IEEE1284.3 */
DECL|member|ieee1284
r_struct
id|ieee1284_info
id|ieee1284
suffix:semicolon
DECL|member|ops
r_struct
id|parport_operations
op_star
id|ops
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
multiline_comment|/* for lowlevel driver */
DECL|member|number
r_int
id|number
suffix:semicolon
multiline_comment|/* port index - the `n&squot; in `parportn&squot; */
DECL|member|pardevice_lock
id|spinlock_t
id|pardevice_lock
suffix:semicolon
DECL|member|waitlist_lock
id|spinlock_t
id|waitlist_lock
suffix:semicolon
DECL|member|cad_lock
id|rwlock_t
id|cad_lock
suffix:semicolon
DECL|member|spintime
r_int
id|spintime
suffix:semicolon
DECL|member|ref_count
id|atomic_t
id|ref_count
suffix:semicolon
DECL|member|full_list
r_struct
id|list_head
id|full_list
suffix:semicolon
DECL|member|slaves
r_struct
id|parport
op_star
id|slaves
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DEFAULT_SPIN_TIME
mdefine_line|#define DEFAULT_SPIN_TIME 500 /* us */
DECL|struct|parport_driver
r_struct
id|parport_driver
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|attach
r_void
(paren
op_star
id|attach
)paren
(paren
r_struct
id|parport
op_star
)paren
suffix:semicolon
DECL|member|detach
r_void
(paren
op_star
id|detach
)paren
(paren
r_struct
id|parport
op_star
)paren
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* parport_register_port registers a new parallel port at the given&n;   address (if one does not already exist) and returns a pointer to it.&n;   This entails claiming the I/O region, IRQ and DMA.  NULL is returned&n;   if initialisation fails. */
r_struct
id|parport
op_star
id|parport_register_port
c_func
(paren
r_int
r_int
id|base
comma
r_int
id|irq
comma
r_int
id|dma
comma
r_struct
id|parport_operations
op_star
id|ops
)paren
suffix:semicolon
multiline_comment|/* Once a registered port is ready for high-level drivers to use, the&n;   low-level driver that registered it should announce it.  This will&n;   call the high-level drivers&squot; attach() functions (after things like&n;   determining the IEEE 1284.3 topology of the port and collecting&n;   DeviceIDs). */
r_void
id|parport_announce_port
(paren
r_struct
id|parport
op_star
id|port
)paren
suffix:semicolon
multiline_comment|/* Unregister a port. */
r_extern
r_void
id|parport_remove_port
c_func
(paren
r_struct
id|parport
op_star
id|port
)paren
suffix:semicolon
multiline_comment|/* Register a new high-level driver. */
r_extern
r_int
id|parport_register_driver
(paren
r_struct
id|parport_driver
op_star
)paren
suffix:semicolon
multiline_comment|/* Unregister a high-level driver. */
r_extern
r_void
id|parport_unregister_driver
(paren
r_struct
id|parport_driver
op_star
)paren
suffix:semicolon
multiline_comment|/* If parport_register_driver doesn&squot;t fit your needs, perhaps&n; * parport_find_xxx does. */
r_extern
r_struct
id|parport
op_star
id|parport_find_number
(paren
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|parport
op_star
id|parport_find_base
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Reference counting for ports. */
r_extern
r_struct
id|parport
op_star
id|parport_get_port
(paren
r_struct
id|parport
op_star
)paren
suffix:semicolon
r_extern
r_void
id|parport_put_port
(paren
r_struct
id|parport
op_star
)paren
suffix:semicolon
multiline_comment|/* parport_register_device declares that a device is connected to a&n;   port, and tells the kernel all it needs to know.&n;   - pf is the preemption function (may be NULL for no callback)&n;   - kf is the wake-up function (may be NULL for no callback)&n;   - irq_func is the interrupt handler (may be NULL for no interrupts)&n;   - handle is a user pointer that gets handed to callback functions.  */
r_struct
id|pardevice
op_star
id|parport_register_device
c_func
(paren
r_struct
id|parport
op_star
id|port
comma
r_const
r_char
op_star
id|name
comma
r_int
(paren
op_star
id|pf
)paren
(paren
r_void
op_star
)paren
comma
r_void
(paren
op_star
id|kf
)paren
(paren
r_void
op_star
)paren
comma
r_void
(paren
op_star
id|irq_func
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
id|flags
comma
r_void
op_star
id|handle
)paren
suffix:semicolon
multiline_comment|/* parport_unregister unlinks a device from the chain. */
r_extern
r_void
id|parport_unregister_device
c_func
(paren
r_struct
id|pardevice
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* parport_claim tries to gain ownership of the port for a particular&n;   driver.  This may fail (return non-zero) if another driver is busy.&n;   If this driver has registered an interrupt handler, it will be&n;   enabled.  */
r_extern
r_int
id|parport_claim
c_func
(paren
r_struct
id|pardevice
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* parport_claim_or_block is the same, but sleeps if the port cannot&n;   be claimed.  Return value is 1 if it slept, 0 normally and -errno&n;   on error.  */
r_extern
r_int
id|parport_claim_or_block
c_func
(paren
r_struct
id|pardevice
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* parport_release reverses a previous parport_claim.  This can never&n;   fail, though the effects are undefined (except that they are bad)&n;   if you didn&squot;t previously own the port.  Once you have released the&n;   port you should make sure that neither your code nor the hardware&n;   on the port tries to initiate any communication without first&n;   re-claiming the port.  If you mess with the port state (enabling&n;   ECP for example) you should clean up before releasing the port. */
r_extern
r_void
id|parport_release
c_func
(paren
r_struct
id|pardevice
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/**&n; * parport_yield - relinquish a parallel port temporarily&n; * @dev: a device on the parallel port&n; *&n; * This function relinquishes the port if it would be helpful to other&n; * drivers to do so.  Afterwards it tries to reclaim the port using&n; * parport_claim(), and the return value is the same as for&n; * parport_claim().  If it fails, the port is left unclaimed and it is&n; * the driver&squot;s responsibility to reclaim the port.&n; *&n; * The parport_yield() and parport_yield_blocking() functions are for&n; * marking points in the driver at which other drivers may claim the&n; * port and use their devices.  Yielding the port is similar to&n; * releasing it and reclaiming it, but is more efficient because no&n; * action is taken if there are no other devices needing the port.  In&n; * fact, nothing is done even if there are other devices waiting but&n; * the current device is still within its &quot;timeslice&quot;.  The default&n; * timeslice is half a second, but it can be adjusted via the /proc&n; * interface.&n; **/
DECL|function|parport_yield
r_static
id|__inline__
r_int
id|parport_yield
c_func
(paren
r_struct
id|pardevice
op_star
id|dev
)paren
(brace
r_int
r_int
r_int
id|timeslip
op_assign
(paren
id|jiffies
op_minus
id|dev-&gt;time
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;port-&gt;waithead
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|timeslip
OL
id|dev-&gt;timeslice
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|parport_release
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|parport_claim
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * parport_yield_blocking - relinquish a parallel port temporarily&n; * @dev: a device on the parallel port&n; *&n; * This function relinquishes the port if it would be helpful to other&n; * drivers to do so.  Afterwards it tries to reclaim the port using&n; * parport_claim_or_block(), and the return value is the same as for&n; * parport_claim_or_block().&n; **/
DECL|function|parport_yield_blocking
r_static
id|__inline__
r_int
id|parport_yield_blocking
c_func
(paren
r_struct
id|pardevice
op_star
id|dev
)paren
(brace
r_int
r_int
r_int
id|timeslip
op_assign
(paren
id|jiffies
op_minus
id|dev-&gt;time
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;port-&gt;waithead
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|timeslip
OL
id|dev-&gt;timeslice
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|parport_release
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|parport_claim_or_block
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/* Flags used to identify what a device does. */
DECL|macro|PARPORT_DEV_TRAN
mdefine_line|#define PARPORT_DEV_TRAN&t;&t;0&t;/* WARNING !! DEPRECATED !! */
DECL|macro|PARPORT_DEV_LURK
mdefine_line|#define PARPORT_DEV_LURK&t;&t;(1&lt;&lt;0)&t;/* WARNING !! DEPRECATED !! */
DECL|macro|PARPORT_DEV_EXCL
mdefine_line|#define PARPORT_DEV_EXCL&t;&t;(1&lt;&lt;1)&t;/* Need exclusive access. */
DECL|macro|PARPORT_FLAG_EXCL
mdefine_line|#define PARPORT_FLAG_EXCL&t;&t;(1&lt;&lt;1)&t;/* EXCL driver registered. */
multiline_comment|/* IEEE1284 functions */
r_extern
r_void
id|parport_ieee1284_interrupt
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|parport_negotiate
(paren
r_struct
id|parport
op_star
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
id|ssize_t
id|parport_write
(paren
r_struct
id|parport
op_star
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
id|ssize_t
id|parport_read
(paren
r_struct
id|parport
op_star
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
DECL|macro|PARPORT_INACTIVITY_O_NONBLOCK
mdefine_line|#define PARPORT_INACTIVITY_O_NONBLOCK 1
r_extern
r_int
id|parport_set_timeout
(paren
r_struct
id|pardevice
op_star
comma
r_int
id|inactivity
)paren
suffix:semicolon
r_extern
r_int
id|parport_wait_event
(paren
r_struct
id|parport
op_star
comma
r_int
id|timeout
)paren
suffix:semicolon
r_extern
r_int
id|parport_wait_peripheral
(paren
r_struct
id|parport
op_star
id|port
comma
r_int
r_char
id|mask
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_extern
r_int
id|parport_poll_peripheral
(paren
r_struct
id|parport
op_star
id|port
comma
r_int
r_char
id|mask
comma
r_int
r_char
id|val
comma
r_int
id|usec
)paren
suffix:semicolon
multiline_comment|/* For architectural drivers */
r_extern
r_int
id|parport_ieee1284_write_compat
(paren
r_struct
id|parport
op_star
comma
r_const
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|parport_ieee1284_read_nibble
(paren
r_struct
id|parport
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|parport_ieee1284_read_byte
(paren
r_struct
id|parport
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|parport_ieee1284_ecp_read_data
(paren
r_struct
id|parport
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|parport_ieee1284_ecp_write_data
(paren
r_struct
id|parport
op_star
comma
r_const
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|parport_ieee1284_ecp_write_addr
(paren
r_struct
id|parport
op_star
comma
r_const
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|parport_ieee1284_epp_write_data
(paren
r_struct
id|parport
op_star
comma
r_const
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|parport_ieee1284_epp_read_data
(paren
r_struct
id|parport
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|parport_ieee1284_epp_write_addr
(paren
r_struct
id|parport
op_star
comma
r_const
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|parport_ieee1284_epp_read_addr
(paren
r_struct
id|parport
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* IEEE1284.3 functions */
r_extern
r_int
id|parport_daisy_init
(paren
r_struct
id|parport
op_star
id|port
)paren
suffix:semicolon
r_extern
r_void
id|parport_daisy_fini
(paren
r_struct
id|parport
op_star
id|port
)paren
suffix:semicolon
r_extern
r_struct
id|pardevice
op_star
id|parport_open
(paren
r_int
id|devnum
comma
r_const
r_char
op_star
id|name
comma
r_int
(paren
op_star
id|pf
)paren
(paren
r_void
op_star
)paren
comma
r_void
(paren
op_star
id|kf
)paren
(paren
r_void
op_star
)paren
comma
r_void
(paren
op_star
id|irqf
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
id|flags
comma
r_void
op_star
id|handle
)paren
suffix:semicolon
r_extern
r_void
id|parport_close
(paren
r_struct
id|pardevice
op_star
id|dev
)paren
suffix:semicolon
r_extern
id|ssize_t
id|parport_device_id
(paren
r_int
id|devnum
comma
r_char
op_star
id|buffer
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|parport_device_num
(paren
r_int
id|parport
comma
r_int
id|mux
comma
r_int
id|daisy
)paren
suffix:semicolon
r_extern
r_void
id|parport_daisy_deselect_all
(paren
r_struct
id|parport
op_star
id|port
)paren
suffix:semicolon
r_extern
r_int
id|parport_daisy_select
(paren
r_struct
id|parport
op_star
id|port
comma
r_int
id|daisy
comma
r_int
id|mode
)paren
suffix:semicolon
multiline_comment|/* Lowlevel drivers _can_ call this support function to handle irqs.  */
DECL|function|parport_generic_irq
r_static
id|__inline__
r_void
id|parport_generic_irq
c_func
(paren
r_int
id|irq
comma
r_struct
id|parport
op_star
id|port
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|parport_ieee1284_interrupt
(paren
id|irq
comma
id|port
comma
id|regs
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|port-&gt;cad_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;cad
op_logical_and
id|port-&gt;cad-&gt;irq_func
)paren
id|port-&gt;cad
op_member_access_from_pointer
id|irq_func
c_func
(paren
id|irq
comma
id|port-&gt;cad
op_member_access_from_pointer
r_private
comma
id|regs
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|port-&gt;cad_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Prototypes from parport_procfs */
r_extern
r_int
id|parport_proc_register
c_func
(paren
r_struct
id|parport
op_star
id|pp
)paren
suffix:semicolon
r_extern
r_int
id|parport_proc_unregister
c_func
(paren
r_struct
id|parport
op_star
id|pp
)paren
suffix:semicolon
r_extern
r_int
id|parport_device_proc_register
c_func
(paren
r_struct
id|pardevice
op_star
id|device
)paren
suffix:semicolon
r_extern
r_int
id|parport_device_proc_unregister
c_func
(paren
r_struct
id|pardevice
op_star
id|device
)paren
suffix:semicolon
multiline_comment|/* If PC hardware is the only type supported, we can optimise a bit.  */
macro_line|#if !defined(CONFIG_PARPORT_NOT_PC)
macro_line|#include &lt;linux/parport_pc.h&gt;
DECL|macro|parport_write_data
mdefine_line|#define parport_write_data(p,x)            parport_pc_write_data(p,x)
DECL|macro|parport_read_data
mdefine_line|#define parport_read_data(p)               parport_pc_read_data(p)
DECL|macro|parport_write_control
mdefine_line|#define parport_write_control(p,x)         parport_pc_write_control(p,x)
DECL|macro|parport_read_control
mdefine_line|#define parport_read_control(p)            parport_pc_read_control(p)
DECL|macro|parport_frob_control
mdefine_line|#define parport_frob_control(p,m,v)        parport_pc_frob_control(p,m,v)
DECL|macro|parport_read_status
mdefine_line|#define parport_read_status(p)             parport_pc_read_status(p)
DECL|macro|parport_enable_irq
mdefine_line|#define parport_enable_irq(p)              parport_pc_enable_irq(p)
DECL|macro|parport_disable_irq
mdefine_line|#define parport_disable_irq(p)             parport_pc_disable_irq(p)
DECL|macro|parport_data_forward
mdefine_line|#define parport_data_forward(p)            parport_pc_data_forward(p)
DECL|macro|parport_data_reverse
mdefine_line|#define parport_data_reverse(p)            parport_pc_data_reverse(p)
macro_line|#else  /*  !CONFIG_PARPORT_NOT_PC  */
multiline_comment|/* Generic operations vector through the dispatch table. */
DECL|macro|parport_write_data
mdefine_line|#define parport_write_data(p,x)            (p)-&gt;ops-&gt;write_data(p,x)
DECL|macro|parport_read_data
mdefine_line|#define parport_read_data(p)               (p)-&gt;ops-&gt;read_data(p)
DECL|macro|parport_write_control
mdefine_line|#define parport_write_control(p,x)         (p)-&gt;ops-&gt;write_control(p,x)
DECL|macro|parport_read_control
mdefine_line|#define parport_read_control(p)            (p)-&gt;ops-&gt;read_control(p)
DECL|macro|parport_frob_control
mdefine_line|#define parport_frob_control(p,m,v)        (p)-&gt;ops-&gt;frob_control(p,m,v)
DECL|macro|parport_read_status
mdefine_line|#define parport_read_status(p)             (p)-&gt;ops-&gt;read_status(p)
DECL|macro|parport_enable_irq
mdefine_line|#define parport_enable_irq(p)              (p)-&gt;ops-&gt;enable_irq(p)
DECL|macro|parport_disable_irq
mdefine_line|#define parport_disable_irq(p)             (p)-&gt;ops-&gt;disable_irq(p)
DECL|macro|parport_data_forward
mdefine_line|#define parport_data_forward(p)            (p)-&gt;ops-&gt;data_forward(p)
DECL|macro|parport_data_reverse
mdefine_line|#define parport_data_reverse(p)            (p)-&gt;ops-&gt;data_reverse(p)
macro_line|#endif /*  !CONFIG_PARPORT_NOT_PC  */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _PARPORT_H_ */
eof
