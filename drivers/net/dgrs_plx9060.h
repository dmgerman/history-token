multiline_comment|/*&n; *&t;PLX 9060 PCI Interface chip&n; */
multiline_comment|/*&n; *&t;PCI configuration registers, same offset on local and PCI sides,&n; *&t;but on PCI side, must use PCI BIOS calls to read/write.&n; */
DECL|macro|PCI_PLXREGS_BASE_ADDR
mdefine_line|#define&t;PCI_PLXREGS_BASE_ADDR&t;0x10
DECL|macro|PCI_PLXREGS_IO_ADDR
mdefine_line|#define&t;PCI_PLXREGS_IO_ADDR&t;0x14
DECL|macro|PCI_SPACE0_BASE_ADDR
mdefine_line|#define&t;PCI_SPACE0_BASE_ADDR&t;0x18
DECL|macro|PCI_ROM_BASE_ADDR
mdefine_line|#define&t;PCI_ROM_BASE_ADDR&t;0x30
DECL|macro|PCI_ROM_ENABLED
macro_line|#&t;define PCI_ROM_ENABLED&t;&t;0x00000001
DECL|macro|PCI_INT_LINE
mdefine_line|#define&t;PCI_INT_LINE&t;&t;0x3C
multiline_comment|/*&n; *&t;Registers accessable directly from PCI and local side.&n; *&t;Offset is from PCI side.  Add PLX_LCL_OFFSET for local address.&n; */
DECL|macro|PLX_LCL_OFFSET
mdefine_line|#define&t;PLX_LCL_OFFSET&t;0x80&t;/* Offset of regs from local side */
multiline_comment|/*&n; *&t;Local Configuration Registers&n; */
DECL|macro|PLX_SPACE0_RANGE
mdefine_line|#define&t;PLX_SPACE0_RANGE&t;0x00&t;/* Range for PCI to Lcl Addr Space 0 */
DECL|macro|PLX_SPACE0_BASE_ADDR
mdefine_line|#define&t;PLX_SPACE0_BASE_ADDR&t;0x04&t;/* Lcl Base address remap */
DECL|macro|PLX_ROM_RANGE
mdefine_line|#define&t;PLX_ROM_RANGE&t;&t;0x10&t;/* Range for expansion ROM (DMA) */
DECL|macro|PLX_ROM_BASE_ADDR
mdefine_line|#define&t;PLX_ROM_BASE_ADDR&t;0x14&t;/* Lcl base address remap for ROM */
DECL|macro|PLX_BUS_REGION
mdefine_line|#define&t;PLX_BUS_REGION&t;&t;0x18&t;/* Bus Region Descriptors */
multiline_comment|/*&n; *&t;Shared Run Time Registers&n; */
DECL|macro|PLX_MBOX0
mdefine_line|#define&t;PLX_MBOX0&t;&t;0x40
DECL|macro|PLX_MBOX1
mdefine_line|#define&t;PLX_MBOX1&t;&t;0x44
DECL|macro|PLX_MBOX2
mdefine_line|#define&t;PLX_MBOX2&t;&t;0x48
DECL|macro|PLX_MBOX3
mdefine_line|#define&t;PLX_MBOX3&t;&t;0x4C
DECL|macro|PLX_MBOX4
mdefine_line|#define&t;PLX_MBOX4&t;&t;0x50
DECL|macro|PLX_MBOX5
mdefine_line|#define&t;PLX_MBOX5&t;&t;0x54
DECL|macro|PLX_MBOX6
mdefine_line|#define&t;PLX_MBOX6&t;&t;0x58
DECL|macro|PLX_MBOX7
mdefine_line|#define&t;PLX_MBOX7&t;&t;0x5C
DECL|macro|PLX_PCI2LCL_DOORBELL
mdefine_line|#define&t;PLX_PCI2LCL_DOORBELL&t;0x60
DECL|macro|PLX_LCL2PCI_DOORBELL
mdefine_line|#define&t;PLX_LCL2PCI_DOORBELL&t;0x64
DECL|macro|PLX_INT_CSR
mdefine_line|#define&t;PLX_INT_CSR&t;&t;0x68&t;/* Interrupt Control/Status */
DECL|macro|PLX_LSERR_ENABLE
macro_line|#&t;define&t;PLX_LSERR_ENABLE&t;0x00000001
DECL|macro|PLX_LSERR_PE
macro_line|#&t;define&t;PLX_LSERR_PE&t;&t;0x00000002
DECL|macro|PLX_SERR
macro_line|#&t;define&t;PLX_SERR&t;&t;0x00000004
DECL|macro|PLX_UNUSED
macro_line|#&t;undef  PLX_UNUSED /*&t;&t;0x00000008&t;&t;&t;*/
DECL|macro|PLX_UNUSED
macro_line|#&t;undef  PLX_UNUSED /*&t;&t;0x00000010&t;&t;&t;*/
DECL|macro|PLX_UNUSED
macro_line|#&t;undef  PLX_UNUSED /*&t;&t;0x00000020&t;&t;&t;*/
DECL|macro|PLX_UNUSED
macro_line|#&t;undef  PLX_UNUSED /*&t;&t;0x00000040&t;&t;&t;*/
DECL|macro|PLX_UNUSED
macro_line|#&t;undef  PLX_UNUSED /*&t;&t;0x00000080&t;&t;&t;*/
DECL|macro|PLX_PCI_IE
macro_line|#&t;define PLX_PCI_IE&t;&t;0x00000100
DECL|macro|PLX_PCI_DOORBELL_IE
macro_line|#&t;define&t;PLX_PCI_DOORBELL_IE&t;0x00000200
DECL|macro|PLX_PCI_ABORT_IE
macro_line|#&t;define&t;PLX_PCI_ABORT_IE&t;0x00000400
DECL|macro|PLX_PCI_LOCAL_IE
macro_line|#&t;define&t;PLX_PCI_LOCAL_IE&t;0x00000800
DECL|macro|PLX_RETRY_ABORT_ENABLE
macro_line|#&t;define&t;PLX_RETRY_ABORT_ENABLE&t;0x00001000
DECL|macro|PLX_PCI_DOORBELL_INT
macro_line|#&t;define&t;PLX_PCI_DOORBELL_INT&t;0x00002000
DECL|macro|PLX_PCI_ABORT_INT
macro_line|#&t;define&t;PLX_PCI_ABORT_INT&t;0x00004000
DECL|macro|PLX_PCI_LOCAL_INT
macro_line|#&t;define&t;PLX_PCI_LOCAL_INT&t;0x00008000
DECL|macro|PLX_LCL_IE
macro_line|#&t;define&t;PLX_LCL_IE&t;&t;0x00010000
DECL|macro|PLX_LCL_DOORBELL_IE
macro_line|#&t;define&t;PLX_LCL_DOORBELL_IE&t;0x00020000
DECL|macro|PLX_LCL_DMA0_IE
macro_line|#&t;define&t;PLX_LCL_DMA0_IE&t;&t;0x00040000
DECL|macro|PLX_LCL_DMA1_IE
macro_line|#&t;define&t;PLX_LCL_DMA1_IE&t;&t;0x00080000
DECL|macro|PLX_LCL_DOORBELL_INT
macro_line|#&t;define&t;PLX_LCL_DOORBELL_INT&t;0x00100000
DECL|macro|PLX_LCL_DMA0_INT
macro_line|#&t;define&t;PLX_LCL_DMA0_INT&t;0x00200000
DECL|macro|PLX_LCL_DMA1_INT
macro_line|#&t;define&t;PLX_LCL_DMA1_INT&t;0x00400000
DECL|macro|PLX_LCL_BIST_INT
macro_line|#&t;define&t;PLX_LCL_BIST_INT&t;0x00800000
DECL|macro|PLX_BM_DIRECT_
macro_line|#&t;define&t;PLX_BM_DIRECT_&t;&t;0x01000000
DECL|macro|PLX_BM_DMA0_
macro_line|#&t;define&t;PLX_BM_DMA0_&t;&t;0x02000000
DECL|macro|PLX_BM_DMA1_
macro_line|#&t;define&t;PLX_BM_DMA1_&t;&t;0x04000000
DECL|macro|PLX_BM_ABORT_
macro_line|#&t;define&t;PLX_BM_ABORT_&t;&t;0x08000000
DECL|macro|PLX_UNUSED
macro_line|#&t;undef  PLX_UNUSED /*&t;&t;0x10000000&t;&t;&t;*/
DECL|macro|PLX_UNUSED
macro_line|#&t;undef  PLX_UNUSED /*&t;&t;0x20000000&t;&t;&t;*/
DECL|macro|PLX_UNUSED
macro_line|#&t;undef  PLX_UNUSED /*&t;&t;0x40000000&t;&t;&t;*/
DECL|macro|PLX_UNUSED
macro_line|#&t;undef  PLX_UNUSED /*&t;&t;0x80000000&t;&t;&t;*/
DECL|macro|PLX_MISC_CSR
mdefine_line|#define&t;PLX_MISC_CSR&t;&t;0x6c&t;/* EEPROM,PCI,User,Init Control/Status*/
DECL|macro|PLX_USEROUT
macro_line|#&t;define PLX_USEROUT&t;&t;0x00010000
DECL|macro|PLX_USERIN
macro_line|#&t;define PLX_USERIN&t;&t;0x00020000
DECL|macro|PLX_EECK
macro_line|#&t;define PLX_EECK&t;&t;&t;0x01000000
DECL|macro|PLX_EECS
macro_line|#&t;define PLX_EECS&t;&t;&t;0x02000000
DECL|macro|PLX_EEWD
macro_line|#&t;define PLX_EEWD&t;&t;&t;0x04000000
DECL|macro|PLX_EERD
macro_line|#&t;define PLX_EERD&t;&t;&t;0x08000000
multiline_comment|/*&n; *&t;DMA registers.  Offset is from local side&n; */
DECL|macro|PLX_DMA0_MODE
mdefine_line|#define&t;PLX_DMA0_MODE&t;&t;0x100
DECL|macro|PLX_DMA_MODE_WIDTH32
macro_line|#&t;define PLX_DMA_MODE_WIDTH32&t;0x00000003
DECL|macro|PLX_DMA_MODE_WAITSTATES
macro_line|#&t;define PLX_DMA_MODE_WAITSTATES(X)&t;((X)&lt;&lt;2)
DECL|macro|PLX_DMA_MODE_NOREADY
macro_line|#&t;define PLX_DMA_MODE_NOREADY&t;0x00000000
DECL|macro|PLX_DMA_MODE_READY
macro_line|#&t;define PLX_DMA_MODE_READY&t;0x00000040
DECL|macro|PLX_DMA_MODE_NOBTERM
macro_line|#&t;define PLX_DMA_MODE_NOBTERM&t;0x00000000
DECL|macro|PLX_DMA_MODE_BTERM
macro_line|#&t;define PLX_DMA_MODE_BTERM&t;0x00000080
DECL|macro|PLX_DMA_MODE_NOBURST
macro_line|#&t;define PLX_DMA_MODE_NOBURST&t;0x00000000
DECL|macro|PLX_DMA_MODE_BURST
macro_line|#&t;define PLX_DMA_MODE_BURST&t;0x00000100
DECL|macro|PLX_DMA_MODE_NOCHAIN
macro_line|#&t;define PLX_DMA_MODE_NOCHAIN&t;0x00000000
DECL|macro|PLX_DMA_MODE_CHAIN
macro_line|#&t;define PLX_DMA_MODE_CHAIN&t;0x00000200
DECL|macro|PLX_DMA_MODE_DONE_IE
macro_line|#&t;define PLX_DMA_MODE_DONE_IE&t;0x00000400
DECL|macro|PLX_DMA_MODE_ADDR_HOLD
macro_line|#&t;define PLX_DMA_MODE_ADDR_HOLD&t;0x00000800
DECL|macro|PLX_DMA0_PCI_ADDR
mdefine_line|#define&t;PLX_DMA0_PCI_ADDR&t;0x104
multiline_comment|/* non-chaining mode PCI address */
DECL|macro|PLX_DMA0_LCL_ADDR
mdefine_line|#define&t;PLX_DMA0_LCL_ADDR&t;0x108
multiline_comment|/* non-chaining mode local address */
DECL|macro|PLX_DMA0_SIZE
mdefine_line|#define&t;PLX_DMA0_SIZE&t;&t;0x10C
multiline_comment|/* non-chaining mode length */
DECL|macro|PLX_DMA0_DESCRIPTOR
mdefine_line|#define&t;PLX_DMA0_DESCRIPTOR&t;0x110
DECL|macro|PLX_DMA_DESC_EOC
macro_line|#&t;define&t;PLX_DMA_DESC_EOC&t;0x00000002
DECL|macro|PLX_DMA_DESC_TC_IE
macro_line|#&t;define&t;PLX_DMA_DESC_TC_IE&t;0x00000004
DECL|macro|PLX_DMA_DESC_TO_HOST
macro_line|#&t;define&t;PLX_DMA_DESC_TO_HOST&t;0x00000008
DECL|macro|PLX_DMA_DESC_TO_BOARD
macro_line|#&t;define&t;PLX_DMA_DESC_TO_BOARD&t;0x00000000
DECL|macro|PLX_DMA_DESC_NEXTADDR
macro_line|#&t;define&t;PLX_DMA_DESC_NEXTADDR&t;0xFFFFfff0
DECL|macro|PLX_DMA1_MODE
mdefine_line|#define&t;PLX_DMA1_MODE&t;&t;0x114
DECL|macro|PLX_DMA1_PCI_ADDR
mdefine_line|#define&t;PLX_DMA1_PCI_ADDR&t;0x118
DECL|macro|PLX_DMA1_LCL_ADDR
mdefine_line|#define&t;PLX_DMA1_LCL_ADDR&t;0x11C
DECL|macro|PLX_DMA1_SIZE
mdefine_line|#define&t;PLX_DMA1_SIZE&t;&t;0x110
DECL|macro|PLX_DMA1_DESCRIPTOR
mdefine_line|#define&t;PLX_DMA1_DESCRIPTOR&t;0x124
DECL|macro|PLX_DMA_CSR
mdefine_line|#define&t;PLX_DMA_CSR&t;&t;0x128
DECL|macro|PLX_DMA_CSR_0_ENABLE
macro_line|#&t;define PLX_DMA_CSR_0_ENABLE&t;0x00000001
DECL|macro|PLX_DMA_CSR_0_START
macro_line|#&t;define PLX_DMA_CSR_0_START&t;0x00000002
DECL|macro|PLX_DMA_CSR_0_ABORT
macro_line|#&t;define PLX_DMA_CSR_0_ABORT&t;0x00000004
DECL|macro|PLX_DMA_CSR_0_CLR_INTR
macro_line|#&t;define PLX_DMA_CSR_0_CLR_INTR&t;0x00000008
DECL|macro|PLX_DMA_CSR_0_DONE
macro_line|#&t;define PLX_DMA_CSR_0_DONE&t;0x00000010
DECL|macro|PLX_DMA_CSR_1_ENABLE
macro_line|#&t;define PLX_DMA_CSR_1_ENABLE&t;0x00000100
DECL|macro|PLX_DMA_CSR_1_START
macro_line|#&t;define PLX_DMA_CSR_1_START&t;0x00000200
DECL|macro|PLX_DMA_CSR_1_ABORT
macro_line|#&t;define PLX_DMA_CSR_1_ABORT&t;0x00000400
DECL|macro|PLX_DMA_CSR_1_CLR_INTR
macro_line|#&t;define PLX_DMA_CSR_1_CLR_INTR&t;0x00000800
DECL|macro|PLX_DMA_CSR_1_DONE
macro_line|#&t;define PLX_DMA_CSR_1_DONE&t;0x00001000
DECL|macro|PLX_DMA_ARB0
mdefine_line|#define&t;PLX_DMA_ARB0&t;&t;0x12C
DECL|macro|PLX_DMA_ARB0_LATENCY_T
macro_line|#&t;define PLX_DMA_ARB0_LATENCY_T&t;0x000000FF
DECL|macro|PLX_DMA_ARB0_PAUSE_T
macro_line|#&t;define PLX_DMA_ARB0_PAUSE_T&t;0x0000FF00
DECL|macro|PLX_DMA_ARB0_LATENCY_EN
macro_line|#&t;define PLX_DMA_ARB0_LATENCY_EN&t;0x00010000
DECL|macro|PLX_DMA_ARB0_PAUSE_EN
macro_line|#&t;define PLX_DMA_ARB0_PAUSE_EN&t;0x00020000
DECL|macro|PLX_DMA_ARB0_BREQ_EN
macro_line|#&t;define PLX_DMA_ARB0_BREQ_EN&t;0x00040000
DECL|macro|PLX_DMA_ARB0_PRI
macro_line|#&t;define PLX_DMA_ARB0_PRI&t;&t;0x00180000
DECL|macro|PLX_DMA_ARB0_PRI_ROUND
macro_line|#&t;define PLX_DMA_ARB0_PRI_ROUND&t;0x00000000
DECL|macro|PLX_DMA_ARB0_PRI_0
macro_line|#&t;define PLX_DMA_ARB0_PRI_0&t;0x00080000
DECL|macro|PLX_DMA_ARB0_PRI_1
macro_line|#&t;define PLX_DMA_ARB0_PRI_1&t;0x00100000
DECL|macro|PLX_DMA_ARB1
mdefine_line|#define&t;PLX_DMA_ARB1&t;&t;0x130
multiline_comment|/* Chan 0: FIFO DEPTH=16 */
DECL|macro|PLX_DMA_ARB1_0_P2L_LW_TRIG
macro_line|#&t;define PLX_DMA_ARB1_0_P2L_LW_TRIG(X)&t;( ((X)&amp;15) &lt;&lt;  0 )
DECL|macro|PLX_DMA_ARB1_0_L2P_LR_TRIG
macro_line|#&t;define PLX_DMA_ARB1_0_L2P_LR_TRIG(X)&t;( ((X)&amp;15) &lt;&lt;  4 )
DECL|macro|PLX_DMA_ARB1_0_L2P_PW_TRIG
macro_line|#&t;define PLX_DMA_ARB1_0_L2P_PW_TRIG(X)&t;( ((X)&amp;15) &lt;&lt;  8 )
DECL|macro|PLX_DMA_ARB1_0_P2L_PR_TRIG
macro_line|#&t;define PLX_DMA_ARB1_0_P2L_PR_TRIG(X)&t;( ((X)&amp;15) &lt;&lt; 12 )
multiline_comment|/* Chan 1: FIFO DEPTH=8 */
DECL|macro|PLX_DMA_ARB1_1_P2L_LW_TRIG
macro_line|#&t;define PLX_DMA_ARB1_1_P2L_LW_TRIG(X)&t;( ((X)&amp; 7) &lt;&lt; 16 )
DECL|macro|PLX_DMA_ARB1_1_L2P_LR_TRIG
macro_line|#&t;define PLX_DMA_ARB1_1_L2P_LR_TRIG(X)&t;( ((X)&amp; 7) &lt;&lt; 20 )
DECL|macro|PLX_DMA_ARB1_1_L2P_PW_TRIG
macro_line|#&t;define PLX_DMA_ARB1_1_L2P_PW_TRIG(X)&t;( ((X)&amp; 7) &lt;&lt; 24 )
DECL|macro|PLX_DMA_ARB1_1_P2L_PR_TRIG
macro_line|#&t;define PLX_DMA_ARB1_1_P2L_PR_TRIG(X)&t;( ((X)&amp; 7) &lt;&lt; 28 )
DECL|struct|_dmachain
r_typedef
r_struct
id|_dmachain
(brace
DECL|member|pciaddr
id|ulong
id|pciaddr
suffix:semicolon
DECL|member|lcladdr
id|ulong
id|lcladdr
suffix:semicolon
DECL|member|len
id|ulong
id|len
suffix:semicolon
DECL|member|next
id|ulong
id|next
suffix:semicolon
DECL|typedef|DMACHAIN
)brace
id|DMACHAIN
suffix:semicolon
eof
