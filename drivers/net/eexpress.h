multiline_comment|/*&n; * eexpress.h: Intel EtherExpress16 defines&n; */
multiline_comment|/*&n; * EtherExpress card register addresses&n; * as offsets from the base IO region (dev-&gt;base_addr)&n; */
DECL|macro|DATAPORT
mdefine_line|#define DATAPORT      0x0000
DECL|macro|WRITE_PTR
mdefine_line|#define WRITE_PTR     0x0002
DECL|macro|READ_PTR
mdefine_line|#define READ_PTR      0x0004
DECL|macro|SIGNAL_CA
mdefine_line|#define SIGNAL_CA     0x0006
DECL|macro|SET_IRQ
mdefine_line|#define SET_IRQ       0x0007
DECL|macro|SM_PTR
mdefine_line|#define SM_PTR        0x0008
DECL|macro|MEM_Dec
mdefine_line|#define&t;MEM_Dec&t;      0x000a
DECL|macro|MEM_Ctrl
mdefine_line|#define MEM_Ctrl      0x000b
DECL|macro|MEM_Page_Ctrl
mdefine_line|#define MEM_Page_Ctrl 0x000c
DECL|macro|Config
mdefine_line|#define Config        0x000d
DECL|macro|EEPROM_Ctrl
mdefine_line|#define EEPROM_Ctrl   0x000e
DECL|macro|ID_PORT
mdefine_line|#define ID_PORT       0x000f
DECL|macro|MEM_ECtrl
mdefine_line|#define&t;MEM_ECtrl     0x000f
multiline_comment|/*&n; * card register defines&n; */
multiline_comment|/* SET_IRQ */
DECL|macro|SIRQ_en
mdefine_line|#define SIRQ_en       0x08
DECL|macro|SIRQ_dis
mdefine_line|#define SIRQ_dis      0x00
multiline_comment|/* EEPROM_Ctrl */
DECL|macro|EC_Clk
mdefine_line|#define EC_Clk        0x01
DECL|macro|EC_CS
mdefine_line|#define EC_CS         0x02
DECL|macro|EC_Wr
mdefine_line|#define EC_Wr         0x04
DECL|macro|EC_Rd
mdefine_line|#define EC_Rd         0x08
DECL|macro|ASIC_RST
mdefine_line|#define ASIC_RST      0x40
DECL|macro|i586_RST
mdefine_line|#define i586_RST      0x80
DECL|macro|eeprom_delay
mdefine_line|#define eeprom_delay() { udelay(40); }
multiline_comment|/*&n; * i82586 Memory Configuration&n; */
multiline_comment|/* (System Configuration Pointer) System start up block, read after 586_RST */
DECL|macro|SCP_START
mdefine_line|#define SCP_START 0xfff6
multiline_comment|/* Intermediate System Configuration Pointer */
DECL|macro|ISCP_START
mdefine_line|#define ISCP_START 0x0000
multiline_comment|/* System Command Block */
DECL|macro|SCB_START
mdefine_line|#define SCB_START 0x0008
multiline_comment|/* Start of buffer region.  Everything before this is used for control&n; * structures and the CU configuration program.  The memory layout is &n; * determined in eexp_hw_probe(), once we know how much memory is &n; * available on the card.&n; */
DECL|macro|TX_BUF_START
mdefine_line|#define TX_BUF_START 0x0100
DECL|macro|TX_BUF_SIZE
mdefine_line|#define TX_BUF_SIZE ((24+ETH_FRAME_LEN+31)&amp;~0x1f)
DECL|macro|RX_BUF_SIZE
mdefine_line|#define RX_BUF_SIZE ((32+ETH_FRAME_LEN+31)&amp;~0x1f)
multiline_comment|/*&n; * SCB defines &n; */
multiline_comment|/* these functions take the SCB status word and test the relevant status bit */
DECL|macro|SCB_complete
mdefine_line|#define SCB_complete(s) ((s&amp;0x8000)!=0)
DECL|macro|SCB_rxdframe
mdefine_line|#define SCB_rxdframe(s) ((s&amp;0x4000)!=0)
DECL|macro|SCB_CUdead
mdefine_line|#define SCB_CUdead(s)   ((s&amp;0x2000)!=0)
DECL|macro|SCB_RUdead
mdefine_line|#define SCB_RUdead(s)   ((s&amp;0x1000)!=0)
DECL|macro|SCB_ack
mdefine_line|#define SCB_ack(s)      (s &amp; 0xf000)
multiline_comment|/* Command unit status: 0=idle, 1=suspended, 2=active */
DECL|macro|SCB_CUstat
mdefine_line|#define SCB_CUstat(s)   ((s&amp;0x0300)&gt;&gt;8)
multiline_comment|/* Receive unit status: 0=idle, 1=suspended, 2=out of resources, 4=ready */
DECL|macro|SCB_RUstat
mdefine_line|#define SCB_RUstat(s)   ((s&amp;0x0070)&gt;&gt;4)
multiline_comment|/* SCB commands */
DECL|macro|SCB_CUnop
mdefine_line|#define SCB_CUnop       0x0000
DECL|macro|SCB_CUstart
mdefine_line|#define SCB_CUstart     0x0100
DECL|macro|SCB_CUresume
mdefine_line|#define SCB_CUresume    0x0200
DECL|macro|SCB_CUsuspend
mdefine_line|#define SCB_CUsuspend   0x0300
DECL|macro|SCB_CUabort
mdefine_line|#define SCB_CUabort     0x0400
DECL|macro|SCB_resetchip
mdefine_line|#define SCB_resetchip   0x0080
DECL|macro|SCB_RUnop
mdefine_line|#define SCB_RUnop       0x0000
DECL|macro|SCB_RUstart
mdefine_line|#define SCB_RUstart     0x0010
DECL|macro|SCB_RUresume
mdefine_line|#define SCB_RUresume    0x0020
DECL|macro|SCB_RUsuspend
mdefine_line|#define SCB_RUsuspend   0x0030
DECL|macro|SCB_RUabort
mdefine_line|#define SCB_RUabort     0x0040
multiline_comment|/*&n; * Command block defines &n; */
DECL|macro|Stat_Done
mdefine_line|#define Stat_Done(s)    ((s&amp;0x8000)!=0)
DECL|macro|Stat_Busy
mdefine_line|#define Stat_Busy(s)    ((s&amp;0x4000)!=0)
DECL|macro|Stat_OK
mdefine_line|#define Stat_OK(s)      ((s&amp;0x2000)!=0)
DECL|macro|Stat_Abort
mdefine_line|#define Stat_Abort(s)   ((s&amp;0x1000)!=0)
DECL|macro|Stat_STFail
mdefine_line|#define Stat_STFail     ((s&amp;0x0800)!=0)
DECL|macro|Stat_TNoCar
mdefine_line|#define Stat_TNoCar(s)  ((s&amp;0x0400)!=0)
DECL|macro|Stat_TNoCTS
mdefine_line|#define Stat_TNoCTS(s)  ((s&amp;0x0200)!=0)
DECL|macro|Stat_TNoDMA
mdefine_line|#define Stat_TNoDMA(s)  ((s&amp;0x0100)!=0)
DECL|macro|Stat_TDefer
mdefine_line|#define Stat_TDefer(s)  ((s&amp;0x0080)!=0)
DECL|macro|Stat_TColl
mdefine_line|#define Stat_TColl(s)   ((s&amp;0x0040)!=0)
DECL|macro|Stat_TXColl
mdefine_line|#define Stat_TXColl(s)  ((s&amp;0x0020)!=0)
DECL|macro|Stat_NoColl
mdefine_line|#define Stat_NoColl(s)  (s&amp;0x000f)
multiline_comment|/* Cmd_END will end AFTER the command if this is the first&n; * command block after an SCB_CUstart, but BEFORE the command&n; * for all subsequent commands. Best strategy is to place&n; * Cmd_INT on the last command in the sequence, followed by a&n; * dummy Cmd_Nop with Cmd_END after this.&n; */
DECL|macro|Cmd_END
mdefine_line|#define Cmd_END     0x8000
DECL|macro|Cmd_SUS
mdefine_line|#define Cmd_SUS     0x4000
DECL|macro|Cmd_INT
mdefine_line|#define Cmd_INT     0x2000
DECL|macro|Cmd_Nop
mdefine_line|#define Cmd_Nop     0x0000
DECL|macro|Cmd_SetAddr
mdefine_line|#define Cmd_SetAddr 0x0001
DECL|macro|Cmd_Config
mdefine_line|#define Cmd_Config  0x0002
DECL|macro|Cmd_MCast
mdefine_line|#define Cmd_MCast   0x0003
DECL|macro|Cmd_Xmit
mdefine_line|#define Cmd_Xmit    0x0004
DECL|macro|Cmd_TDR
mdefine_line|#define Cmd_TDR     0x0005
DECL|macro|Cmd_Dump
mdefine_line|#define Cmd_Dump    0x0006
DECL|macro|Cmd_Diag
mdefine_line|#define Cmd_Diag    0x0007
multiline_comment|/*&n; * Frame Descriptor (Receive block) defines&n; */
DECL|macro|FD_Done
mdefine_line|#define FD_Done(s)  ((s&amp;0x8000)!=0)
DECL|macro|FD_Busy
mdefine_line|#define FD_Busy(s)  ((s&amp;0x4000)!=0)
DECL|macro|FD_OK
mdefine_line|#define FD_OK(s)    ((s&amp;0x2000)!=0)
DECL|macro|FD_CRC
mdefine_line|#define FD_CRC(s)   ((s&amp;0x0800)!=0)
DECL|macro|FD_Align
mdefine_line|#define FD_Align(s) ((s&amp;0x0400)!=0)
DECL|macro|FD_Resrc
mdefine_line|#define FD_Resrc(s) ((s&amp;0x0200)!=0)
DECL|macro|FD_DMA
mdefine_line|#define FD_DMA(s)   ((s&amp;0x0100)!=0)
DECL|macro|FD_Short
mdefine_line|#define FD_Short(s) ((s&amp;0x0080)!=0)
DECL|macro|FD_NoEOF
mdefine_line|#define FD_NoEOF(s) ((s&amp;0x0040)!=0)
DECL|struct|rfd_header
r_struct
id|rfd_header
(brace
DECL|member|flags
r_volatile
r_int
r_int
id|flags
suffix:semicolon
DECL|member|link
r_volatile
r_int
r_int
id|link
suffix:semicolon
DECL|member|rbd_offset
r_volatile
r_int
r_int
id|rbd_offset
suffix:semicolon
DECL|member|dstaddr1
r_volatile
r_int
r_int
id|dstaddr1
suffix:semicolon
DECL|member|dstaddr2
r_volatile
r_int
r_int
id|dstaddr2
suffix:semicolon
DECL|member|dstaddr3
r_volatile
r_int
r_int
id|dstaddr3
suffix:semicolon
DECL|member|srcaddr1
r_volatile
r_int
r_int
id|srcaddr1
suffix:semicolon
DECL|member|srcaddr2
r_volatile
r_int
r_int
id|srcaddr2
suffix:semicolon
DECL|member|srcaddr3
r_volatile
r_int
r_int
id|srcaddr3
suffix:semicolon
DECL|member|length
r_volatile
r_int
r_int
id|length
suffix:semicolon
multiline_comment|/* This is actually a Receive Buffer Descriptor.  The way we &n;&t; * arrange memory means that an RBD always follows the RFD that &n;&t; * points to it, so they might as well be in the same structure.&n;&t; */
DECL|member|actual_count
r_volatile
r_int
r_int
id|actual_count
suffix:semicolon
DECL|member|next_rbd
r_volatile
r_int
r_int
id|next_rbd
suffix:semicolon
DECL|member|buf_addr1
r_volatile
r_int
r_int
id|buf_addr1
suffix:semicolon
DECL|member|buf_addr2
r_volatile
r_int
r_int
id|buf_addr2
suffix:semicolon
DECL|member|size
r_volatile
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Returned data from the Time Domain Reflectometer */
DECL|macro|TDR_LINKOK
mdefine_line|#define TDR_LINKOK       (1&lt;&lt;15)
DECL|macro|TDR_XCVRPROBLEM
mdefine_line|#define TDR_XCVRPROBLEM  (1&lt;&lt;14)
DECL|macro|TDR_OPEN
mdefine_line|#define TDR_OPEN         (1&lt;&lt;13)
DECL|macro|TDR_SHORT
mdefine_line|#define TDR_SHORT        (1&lt;&lt;12)
DECL|macro|TDR_TIME
mdefine_line|#define TDR_TIME         0x7ff
eof
