macro_line|#ifndef __SAA7146_CORE__
DECL|macro|__SAA7146_CORE__
mdefine_line|#define __SAA7146_CORE__
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* definitions of u32 etc. */
macro_line|#include &quot;../dvb-core/dvbdev.h&quot;
macro_line|#if LINUX_VERSION_CODE &lt; 0x020300
DECL|macro|DECLARE_MUTEX
mdefine_line|#define DECLARE_MUTEX(foo)         struct semaphore foo = MUTEX
DECL|macro|DECLARE_MUTEX_LOCKED
mdefine_line|#define DECLARE_MUTEX_LOCKED(foo)  struct semaphore foo = MUTEX_LOCKED
DECL|macro|WAIT_QUEUE
mdefine_line|#define WAIT_QUEUE                 struct wait_queue*
DECL|macro|init_waitqueue_head
mdefine_line|#define init_waitqueue_head(wq)    *(wq) = NULL;
macro_line|#else
DECL|macro|WAIT_QUEUE
mdefine_line|#define WAIT_QUEUE                 wait_queue_head_t
macro_line|#endif
multiline_comment|/* maximum number of capture frames we support */
DECL|macro|SAA7146_MAX_BUF
mdefine_line|#define SAA7146_MAX_BUF&t;&t;5
multiline_comment|/* maximum number of extensions we support */
DECL|macro|SAA7146_MAX_EXTENSIONS
mdefine_line|#define SAA7146_MAX_EXTENSIONS&t;4
multiline_comment|/* stuff for writing to saa7146 */
DECL|macro|saa7146_write
mdefine_line|#define saa7146_write(mem,adr,dat)    writel((dat),(mem+(adr)))
DECL|macro|saa7146_read
mdefine_line|#define saa7146_read(mem,adr)         readl(mem+(adr))
DECL|macro|DVB_CARD_TT_SIEMENS
mdefine_line|#define DVB_CARD_TT_SIEMENS   0
DECL|macro|DVB_CARD_TT_BUDGET
mdefine_line|#define DVB_CARD_TT_BUDGET    1
DECL|macro|DVB_CARD_TT_BUDGET_CI
mdefine_line|#define DVB_CARD_TT_BUDGET_CI 2
DECL|macro|DVB_CARD_KNC1
mdefine_line|#define DVB_CARD_KNC1         3
multiline_comment|/* this struct contains some constants needed for horizontal and vertical scaling. &n;   currently we only support PAL (mode=0)and NTSC (mode=1). */
DECL|struct|saa7146
r_struct
id|saa7146
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* give it a nice name */
DECL|member|list_head
r_struct
id|list_head
id|list_head
suffix:semicolon
DECL|member|dvb_adapter
id|dvb_adapter_t
op_star
id|dvb_adapter
suffix:semicolon
DECL|member|i2c_bus
r_struct
id|dvb_i2c_bus
op_star
id|i2c_bus
suffix:semicolon
DECL|member|device
r_struct
id|pci_dev
op_star
id|device
suffix:semicolon
DECL|member|card_type
r_int
id|card_type
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
(braket
id|SAA7146_MAX_EXTENSIONS
)braket
suffix:semicolon
multiline_comment|/* data hooks for extensions */
DECL|member|command
r_int
(paren
op_star
id|command
)paren
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|member|mem
r_int
r_char
op_star
id|mem
suffix:semicolon
multiline_comment|/* pointer to mapped IO memory */
DECL|member|revision
r_int
id|revision
suffix:semicolon
multiline_comment|/* chip revision; needed for bug-workarounds*/
DECL|member|interlace
r_int
id|interlace
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|i2c
id|u32
op_star
id|i2c
suffix:semicolon
multiline_comment|/* i2c memory */
DECL|member|grabbing
id|u32
op_star
id|grabbing
suffix:semicolon
multiline_comment|/* grabbing memory */
DECL|member|clipping
id|u32
op_star
id|clipping
suffix:semicolon
multiline_comment|/* clipping memory for mask or rectangle clipping*/
DECL|member|rps0
id|u32
op_star
id|rps0
suffix:semicolon
multiline_comment|/* memory for rps0-program */
DECL|member|rps1
id|u32
op_star
id|rps1
suffix:semicolon
multiline_comment|/* memory for rps1-program */
DECL|member|debi
id|u32
op_star
id|debi
suffix:semicolon
multiline_comment|/* memory for debi-transfers */
DECL|member|buffers
r_int
id|buffers
suffix:semicolon
multiline_comment|/* number of grabbing-buffers */
DECL|member|page_table
id|u32
op_star
id|page_table
(braket
id|SAA7146_MAX_BUF
)braket
suffix:semicolon
multiline_comment|/* page_tables for buffers*/
DECL|member|frame_stat
r_int
id|frame_stat
(braket
id|SAA7146_MAX_BUF
)braket
suffix:semicolon
multiline_comment|/* status of grabbing buffers */
DECL|member|grab_width
r_int
id|grab_width
(braket
id|SAA7146_MAX_BUF
)braket
suffix:semicolon
multiline_comment|/* pixel width of grabs */
DECL|member|grab_height
r_int
id|grab_height
(braket
id|SAA7146_MAX_BUF
)braket
suffix:semicolon
multiline_comment|/* pixel height of grabs */
DECL|member|grab_format
r_int
id|grab_format
(braket
id|SAA7146_MAX_BUF
)braket
suffix:semicolon
multiline_comment|/* video format of grabs */
DECL|member|grab_port
r_int
id|grab_port
(braket
id|SAA7146_MAX_BUF
)braket
suffix:semicolon
multiline_comment|/* video port for grab */
DECL|member|rps0_wq
id|WAIT_QUEUE
id|rps0_wq
suffix:semicolon
multiline_comment|/* rps0 interrupt queue (=&gt; capture) */
DECL|member|rps1_wq
id|WAIT_QUEUE
id|rps1_wq
suffix:semicolon
multiline_comment|/* rps1 interrupt queue (=&gt; i2c, ...) */
)brace
suffix:semicolon
DECL|macro|SAA7146_IRQ_RPS0
mdefine_line|#define&t;SAA7146_IRQ_RPS0  
DECL|macro|SAA7146_IRQ_RPS1
mdefine_line|#define&t;SAA7146_IRQ_RPS1 
DECL|struct|saa7146_extension
r_struct
id|saa7146_extension
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|handles_irqs
id|u32
id|handles_irqs
suffix:semicolon
DECL|member|irq_handler
r_void
(paren
op_star
id|irq_handler
)paren
(paren
r_struct
id|saa7146
op_star
comma
id|u32
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|command
r_int
(paren
op_star
id|command
)paren
(paren
r_struct
id|saa7146
op_star
comma
r_void
op_star
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|member|attach
r_int
(paren
op_star
id|attach
)paren
(paren
r_struct
id|saa7146
op_star
comma
r_void
op_star
op_star
)paren
suffix:semicolon
DECL|member|detach
r_int
(paren
op_star
id|detach
)paren
(paren
r_struct
id|saa7146
op_star
comma
r_void
op_star
op_star
)paren
suffix:semicolon
DECL|member|inc_use
r_void
(paren
op_star
id|inc_use
)paren
(paren
r_struct
id|saa7146
op_star
)paren
suffix:semicolon
DECL|member|dec_use
r_void
(paren
op_star
id|dec_use
)paren
(paren
r_struct
id|saa7146
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|saa7146_add_extension
c_func
(paren
r_struct
id|saa7146_extension
op_star
id|ext
)paren
suffix:semicolon
r_extern
r_int
id|saa7146_del_extension
c_func
(paren
r_struct
id|saa7146_extension
op_star
id|ext
)paren
suffix:semicolon
multiline_comment|/* external grabbing states */
DECL|macro|GBUFFER_UNUSED
mdefine_line|#define GBUFFER_UNUSED         0x000
DECL|macro|GBUFFER_GRABBING
mdefine_line|#define GBUFFER_GRABBING       0x001
DECL|macro|GBUFFER_DONE
mdefine_line|#define GBUFFER_DONE           0x002
DECL|macro|SAA7146_CORE_BASE
mdefine_line|#define SAA7146_CORE_BASE&t;200
DECL|macro|SAA7146_DO_MMAP
mdefine_line|#define&t;SAA7146_DO_MMAP&t;&t;_IOW(&squot;d&squot;, (SAA7146_CORE_BASE+11), struct vm_area_struct *)
DECL|macro|SAA7146_SET_DD1
mdefine_line|#define SAA7146_SET_DD1&t;&t;_IOW(&squot;d&squot;, (SAA7146_CORE_BASE+12), u32)
DECL|macro|SAA7146_DUMP_REGISTERS
mdefine_line|#define SAA7146_DUMP_REGISTERS&t;_IOW(&squot;d&squot;, (SAA7146_CORE_BASE+13), u32)
DECL|macro|SAA7146_DEBI_TRANSFER
mdefine_line|#define SAA7146_DEBI_TRANSFER&t;_IOW(&squot;d&squot;, (SAA7146_CORE_BASE+14), struct saa7146_debi_transfer)
DECL|macro|SAA7146_SUSPEND
mdefine_line|#define SAA7146_SUSPEND&t;_IOW(&squot;d&squot;, (SAA7146_CORE_BASE+32), u32)
DECL|macro|SAA7146_RESUME
mdefine_line|#define SAA7146_RESUME&t;_IOW(&squot;d&squot;, (SAA7146_CORE_BASE+33), u32)
macro_line|#endif
eof
