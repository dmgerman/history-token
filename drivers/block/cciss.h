macro_line|#ifndef CCISS_H
DECL|macro|CCISS_H
mdefine_line|#define CCISS_H
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &quot;cciss_cmd.h&quot;
DECL|macro|NWD
mdefine_line|#define NWD&t;&t;16
DECL|macro|NWD_SHIFT
mdefine_line|#define NWD_SHIFT&t;4
DECL|macro|MAX_PART
mdefine_line|#define MAX_PART&t;16
DECL|macro|IO_OK
mdefine_line|#define IO_OK&t;&t;0
DECL|macro|IO_ERROR
mdefine_line|#define IO_ERROR&t;1
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR COMPAQ_CISS_MAJOR 
r_struct
id|ctlr_info
suffix:semicolon
DECL|typedef|ctlr_info_t
r_typedef
r_struct
id|ctlr_info
id|ctlr_info_t
suffix:semicolon
DECL|struct|access_method
r_struct
id|access_method
(brace
DECL|member|submit_command
r_void
(paren
op_star
id|submit_command
)paren
(paren
id|ctlr_info_t
op_star
id|h
comma
id|CommandList_struct
op_star
id|c
)paren
suffix:semicolon
DECL|member|set_intr_mask
r_void
(paren
op_star
id|set_intr_mask
)paren
(paren
id|ctlr_info_t
op_star
id|h
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|member|fifo_full
r_int
r_int
(paren
op_star
id|fifo_full
)paren
(paren
id|ctlr_info_t
op_star
id|h
)paren
suffix:semicolon
DECL|member|intr_pending
r_int
r_int
(paren
op_star
id|intr_pending
)paren
(paren
id|ctlr_info_t
op_star
id|h
)paren
suffix:semicolon
DECL|member|command_completed
r_int
r_int
(paren
op_star
id|command_completed
)paren
(paren
id|ctlr_info_t
op_star
id|h
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_drive_info_struct
r_typedef
r_struct
id|_drive_info_struct
(brace
DECL|member|LunID
id|__u32
id|LunID
suffix:semicolon
DECL|member|usage_count
r_int
id|usage_count
suffix:semicolon
DECL|member|nr_blocks
r_int
id|nr_blocks
suffix:semicolon
DECL|member|block_size
r_int
id|block_size
suffix:semicolon
DECL|member|heads
r_int
id|heads
suffix:semicolon
DECL|member|sectors
r_int
id|sectors
suffix:semicolon
DECL|member|cylinders
r_int
id|cylinders
suffix:semicolon
DECL|typedef|drive_info_struct
)brace
id|drive_info_struct
suffix:semicolon
DECL|struct|ctlr_info
r_struct
id|ctlr_info
(brace
DECL|member|ctlr
r_int
id|ctlr
suffix:semicolon
DECL|member|devname
r_char
id|devname
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|product_name
r_char
op_star
id|product_name
suffix:semicolon
DECL|member|firm_ver
r_char
id|firm_ver
(braket
l_int|4
)braket
suffix:semicolon
singleline_comment|// Firmware version 
DECL|member|pci_bus
id|unchar
id|pci_bus
suffix:semicolon
DECL|member|pci_dev_fn
id|unchar
id|pci_dev_fn
suffix:semicolon
DECL|member|board_id
id|__u32
id|board_id
suffix:semicolon
DECL|member|vaddr
id|ulong
id|vaddr
suffix:semicolon
DECL|member|paddr
id|__u32
id|paddr
suffix:semicolon
DECL|member|cfgtable
id|CfgTable_struct
op_star
id|cfgtable
suffix:semicolon
DECL|member|intr
r_int
id|intr
suffix:semicolon
DECL|member|max_commands
r_int
id|max_commands
suffix:semicolon
DECL|member|commands_outstanding
r_int
id|commands_outstanding
suffix:semicolon
DECL|member|max_outstanding
r_int
id|max_outstanding
suffix:semicolon
multiline_comment|/* Debug */
DECL|member|num_luns
r_int
id|num_luns
suffix:semicolon
DECL|member|usage_count
r_int
id|usage_count
suffix:semicolon
multiline_comment|/* number of opens all all minor devices */
singleline_comment|// information about each logical volume
DECL|member|drv
id|drive_info_struct
id|drv
(braket
id|CISS_MAX_LUN
)braket
suffix:semicolon
DECL|member|access
r_struct
id|access_method
id|access
suffix:semicolon
multiline_comment|/* queue and queue Info */
DECL|member|reqQ
id|CommandList_struct
op_star
id|reqQ
suffix:semicolon
DECL|member|cmpQ
id|CommandList_struct
op_star
id|cmpQ
suffix:semicolon
DECL|member|Qdepth
r_int
r_int
id|Qdepth
suffix:semicolon
DECL|member|maxQsinceinit
r_int
r_int
id|maxQsinceinit
suffix:semicolon
DECL|member|maxSG
r_int
r_int
id|maxSG
suffix:semicolon
singleline_comment|//* pointers to command and error info pool */ 
DECL|member|cmd_pool
id|CommandList_struct
op_star
id|cmd_pool
suffix:semicolon
DECL|member|errinfo_pool
id|ErrorInfo_struct
op_star
id|errinfo_pool
suffix:semicolon
DECL|member|cmd_pool_bits
id|__u32
op_star
id|cmd_pool_bits
suffix:semicolon
DECL|member|nr_allocs
r_int
id|nr_allocs
suffix:semicolon
DECL|member|nr_frees
r_int
id|nr_frees
suffix:semicolon
singleline_comment|// Disk structures we need to pass back
DECL|member|gendisk
r_struct
id|gendisk
id|gendisk
suffix:semicolon
singleline_comment|// indexed by minor numbers
DECL|member|hd
r_struct
id|hd_struct
id|hd
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|sizes
r_int
id|sizes
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|blocksizes
r_int
id|blocksizes
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|hardsizes
r_int
id|hardsizes
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*  Defining the diffent access_menthods */
multiline_comment|/*&n; * Memory mapped FIFO interface (SMART 53xx cards)&n; */
DECL|macro|SA5_DOORBELL
mdefine_line|#define SA5_DOORBELL&t;0x20
DECL|macro|SA5_REQUEST_PORT_OFFSET
mdefine_line|#define SA5_REQUEST_PORT_OFFSET&t;0x40
DECL|macro|SA5_REPLY_INTR_MASK_OFFSET
mdefine_line|#define SA5_REPLY_INTR_MASK_OFFSET&t;0x34
DECL|macro|SA5_REPLY_PORT_OFFSET
mdefine_line|#define SA5_REPLY_PORT_OFFSET&t;&t;0x44
DECL|macro|SA5_INTR_STATUS
mdefine_line|#define SA5_INTR_STATUS&t;&t;0x30
DECL|macro|SA5_CTCFG_OFFSET
mdefine_line|#define SA5_CTCFG_OFFSET&t;0xB4
DECL|macro|SA5_CTMEM_OFFSET
mdefine_line|#define SA5_CTMEM_OFFSET&t;0xB8
DECL|macro|SA5_INTR_OFF
mdefine_line|#define SA5_INTR_OFF&t;&t;0x08
DECL|macro|SA5B_INTR_OFF
mdefine_line|#define SA5B_INTR_OFF&t;&t;0x04
DECL|macro|SA5_INTR_PENDING
mdefine_line|#define SA5_INTR_PENDING&t;0x08
DECL|macro|SA5B_INTR_PENDING
mdefine_line|#define SA5B_INTR_PENDING&t;0x04
DECL|macro|FIFO_EMPTY
mdefine_line|#define FIFO_EMPTY&t;&t;0xffffffff&t;
DECL|macro|CISS_ERROR_BIT
mdefine_line|#define  CISS_ERROR_BIT&t;&t;0x02
DECL|macro|CCISS_INTR_ON
mdefine_line|#define CCISS_INTR_ON &t;1 
DECL|macro|CCISS_INTR_OFF
mdefine_line|#define CCISS_INTR_OFF&t;0
multiline_comment|/* &n;&t;Send the command to the hardware &n;*/
DECL|function|SA5_submit_command
r_static
r_void
id|SA5_submit_command
c_func
(paren
id|ctlr_info_t
op_star
id|h
comma
id|CommandList_struct
op_star
id|c
)paren
(brace
macro_line|#ifdef CCISS_DEBUG
id|printk
c_func
(paren
l_string|&quot;Sending %x - down to controller&bslash;n&quot;
comma
id|c-&gt;busaddr
)paren
suffix:semicolon
macro_line|#endif /* CCISS_DEBUG */ 
id|writel
c_func
(paren
id|c-&gt;busaddr
comma
id|h-&gt;vaddr
op_plus
id|SA5_REQUEST_PORT_OFFSET
)paren
suffix:semicolon
id|h-&gt;commands_outstanding
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|h-&gt;commands_outstanding
OG
id|h-&gt;max_outstanding
)paren
id|h-&gt;max_outstanding
op_assign
id|h-&gt;commands_outstanding
suffix:semicolon
)brace
multiline_comment|/*  &n; *  This card is the opposite of the other cards.  &n; *   0 turns interrupts on... &n; *   0x08 turns them off... &n; */
DECL|function|SA5_intr_mask
r_static
r_void
id|SA5_intr_mask
c_func
(paren
id|ctlr_info_t
op_star
id|h
comma
r_int
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|val
)paren
(brace
multiline_comment|/* Turn interrupts on */
id|writel
c_func
(paren
l_int|0
comma
id|h-&gt;vaddr
op_plus
id|SA5_REPLY_INTR_MASK_OFFSET
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* Turn them off */
(brace
id|writel
c_func
(paren
id|SA5_INTR_OFF
comma
id|h-&gt;vaddr
op_plus
id|SA5_REPLY_INTR_MASK_OFFSET
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  This card is the opposite of the other cards.&n; *   0 turns interrupts on...&n; *   0x04 turns them off...&n; */
DECL|function|SA5B_intr_mask
r_static
r_void
id|SA5B_intr_mask
c_func
(paren
id|ctlr_info_t
op_star
id|h
comma
r_int
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|val
)paren
(brace
multiline_comment|/* Turn interrupts on */
id|writel
c_func
(paren
l_int|0
comma
id|h-&gt;vaddr
op_plus
id|SA5_REPLY_INTR_MASK_OFFSET
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/* Turn them off */
(brace
id|writel
c_func
(paren
id|SA5B_INTR_OFF
comma
id|h-&gt;vaddr
op_plus
id|SA5_REPLY_INTR_MASK_OFFSET
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  Returns true if fifo is full.  &n; * &n; */
DECL|function|SA5_fifo_full
r_static
r_int
r_int
id|SA5_fifo_full
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_if
c_cond
(paren
id|h-&gt;commands_outstanding
op_ge
id|h-&gt;max_commands
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; *   returns value read from hardware. &n; *     returns FIFO_EMPTY if there is nothing to read &n; */
DECL|function|SA5_completed
r_static
r_int
r_int
id|SA5_completed
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_int
r_int
id|register_value
op_assign
id|readl
c_func
(paren
id|h-&gt;vaddr
op_plus
id|SA5_REPLY_PORT_OFFSET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_value
op_ne
id|FIFO_EMPTY
)paren
(brace
id|h-&gt;commands_outstanding
op_decrement
suffix:semicolon
macro_line|#ifdef CCISS_DEBUG
id|printk
c_func
(paren
l_string|&quot;cciss:  Read %lx back from board&bslash;n&quot;
comma
id|register_value
)paren
suffix:semicolon
macro_line|#endif /* CCISS_DEBUG */ 
)brace
macro_line|#ifdef CCISS_DEBUG
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;cciss:  FIFO Empty read&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif 
r_return
(paren
id|register_value
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Returns true if an interrupt is pending.. &n; */
DECL|function|SA5_intr_pending
r_static
r_int
r_int
id|SA5_intr_pending
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_int
r_int
id|register_value
op_assign
id|readl
c_func
(paren
id|h-&gt;vaddr
op_plus
id|SA5_INTR_STATUS
)paren
suffix:semicolon
macro_line|#ifdef CCISS_DEBUG
id|printk
c_func
(paren
l_string|&quot;cciss: intr_pending %lx&bslash;n&quot;
comma
id|register_value
)paren
suffix:semicolon
macro_line|#endif  /* CCISS_DEBUG */
r_if
c_cond
(paren
id|register_value
op_amp
id|SA5_INTR_PENDING
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *      Returns true if an interrupt is pending..&n; */
DECL|function|SA5B_intr_pending
r_static
r_int
r_int
id|SA5B_intr_pending
c_func
(paren
id|ctlr_info_t
op_star
id|h
)paren
(brace
r_int
r_int
id|register_value
op_assign
id|readl
c_func
(paren
id|h-&gt;vaddr
op_plus
id|SA5_INTR_STATUS
)paren
suffix:semicolon
macro_line|#ifdef CCISS_DEBUG
id|printk
c_func
(paren
l_string|&quot;cciss: intr_pending %lx&bslash;n&quot;
comma
id|register_value
)paren
suffix:semicolon
macro_line|#endif  /* CCISS_DEBUG */
r_if
c_cond
(paren
id|register_value
op_amp
id|SA5B_INTR_PENDING
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|SA5_access
r_static
r_struct
id|access_method
id|SA5_access
op_assign
(brace
id|SA5_submit_command
comma
id|SA5_intr_mask
comma
id|SA5_fifo_full
comma
id|SA5_intr_pending
comma
id|SA5_completed
comma
)brace
suffix:semicolon
DECL|variable|SA5B_access
r_static
r_struct
id|access_method
id|SA5B_access
op_assign
(brace
id|SA5_submit_command
comma
id|SA5B_intr_mask
comma
id|SA5_fifo_full
comma
id|SA5B_intr_pending
comma
id|SA5_completed
comma
)brace
suffix:semicolon
DECL|struct|board_type
r_struct
id|board_type
(brace
DECL|member|board_id
id|__u32
id|board_id
suffix:semicolon
DECL|member|product_name
r_char
op_star
id|product_name
suffix:semicolon
DECL|member|access
r_struct
id|access_method
op_star
id|access
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* CCISS_H */
eof
