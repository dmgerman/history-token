macro_line|#ifndef __ALPHA_CIA__H__
DECL|macro|__ALPHA_CIA__H__
mdefine_line|#define __ALPHA_CIA__H__
multiline_comment|/* Define to experiment with fitting everything into one 512MB HAE window.  */
DECL|macro|CIA_ONE_HAE_WINDOW
mdefine_line|#define CIA_ONE_HAE_WINDOW 1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * CIA is the internal name for the 21171 chipset which provides&n; * memory controller and PCI access for the 21164 chip based systems.&n; * Also supported here is the 21172 (CIA-2) and 21174 (PYXIS).&n; *&n; * The lineage is a bit confused, since the 21174 was reportedly started&n; * from the 21171 Pass 1 mask, and so is missing bug fixes that appear&n; * in 21171 Pass 2 and 21172, but it also contains additional features.&n; *&n; * This file is based on:&n; *&n; * DECchip 21171 Core Logic Chipset&n; * Technical Reference Manual&n; *&n; * EC-QE18B-TE&n; *&n; * david.rusling@reo.mts.dec.com Initial Version.&n; *&n; */
multiline_comment|/*&n; * CIA ADDRESS BIT DEFINITIONS&n; *&n; *  3333 3333 3322 2222 2222 1111 1111 11&n; *  9876 5432 1098 7654 3210 9876 5432 1098 7654 3210&n; *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----&n; *  1                                             000&n; *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----&n; *  |                                             |&bslash;|&n; *  |                               Byte Enable --+ |&n; *  |                             Transfer Length --+&n; *  +-- IO space, not cached&n; *&n; *   Byte      Transfer&n; *   Enable    Length    Transfer  Byte    Address&n; *   adr&lt;6:5&gt;  adr&lt;4:3&gt;  Length    Enable  Adder&n; *   ---------------------------------------------&n; *      00        00      Byte      1110   0x000&n; *      01        00      Byte      1101   0x020&n; *      10        00      Byte      1011   0x040&n; *      11        00      Byte      0111   0x060&n; *&n; *      00        01      Word      1100   0x008&n; *      01        01      Word      1001   0x028 &lt;= Not supported in this code.&n; *      10        01      Word      0011   0x048&n; *&n; *      00        10      Tribyte   1000   0x010&n; *      01        10      Tribyte   0001   0x030&n; *&n; *      10        11      Longword  0000   0x058&n; *&n; *      Note that byte enables are asserted low.&n; *&n; */
DECL|macro|CIA_MEM_R1_MASK
mdefine_line|#define CIA_MEM_R1_MASK 0x1fffffff  /* SPARSE Mem region 1 mask is 29 bits */
DECL|macro|CIA_MEM_R2_MASK
mdefine_line|#define CIA_MEM_R2_MASK 0x07ffffff  /* SPARSE Mem region 2 mask is 27 bits */
DECL|macro|CIA_MEM_R3_MASK
mdefine_line|#define CIA_MEM_R3_MASK 0x03ffffff  /* SPARSE Mem region 3 mask is 26 bits */
multiline_comment|/*&n; * 21171-CA Control and Status Registers&n; */
DECL|macro|CIA_IOC_CIA_REV
mdefine_line|#define CIA_IOC_CIA_REV&t;&t;&t;(IDENT_ADDR + 0x8740000080UL)
DECL|macro|CIA_REV_MASK
macro_line|#  define CIA_REV_MASK&t;&t;&t;0xff
DECL|macro|CIA_IOC_PCI_LAT
mdefine_line|#define CIA_IOC_PCI_LAT&t;&t;&t;(IDENT_ADDR + 0x87400000C0UL)
DECL|macro|CIA_IOC_CIA_CTRL
mdefine_line|#define CIA_IOC_CIA_CTRL&t;&t;(IDENT_ADDR + 0x8740000100UL)
DECL|macro|CIA_CTRL_PCI_EN
macro_line|#  define CIA_CTRL_PCI_EN&t;&t;(1 &lt;&lt; 0)
DECL|macro|CIA_CTRL_PCI_LOCK_EN
macro_line|#  define CIA_CTRL_PCI_LOCK_EN&t;&t;(1 &lt;&lt; 1)
DECL|macro|CIA_CTRL_PCI_LOOP_EN
macro_line|#  define CIA_CTRL_PCI_LOOP_EN&t;&t;(1 &lt;&lt; 2)
DECL|macro|CIA_CTRL_FST_BB_EN
macro_line|#  define CIA_CTRL_FST_BB_EN&t;&t;(1 &lt;&lt; 3)
DECL|macro|CIA_CTRL_PCI_MST_EN
macro_line|#  define CIA_CTRL_PCI_MST_EN&t;&t;(1 &lt;&lt; 4)
DECL|macro|CIA_CTRL_PCI_MEM_EN
macro_line|#  define CIA_CTRL_PCI_MEM_EN&t;&t;(1 &lt;&lt; 5)
DECL|macro|CIA_CTRL_PCI_REQ64_EN
macro_line|#  define CIA_CTRL_PCI_REQ64_EN&t;&t;(1 &lt;&lt; 6)
DECL|macro|CIA_CTRL_PCI_ACK64_EN
macro_line|#  define CIA_CTRL_PCI_ACK64_EN&t;&t;(1 &lt;&lt; 7)
DECL|macro|CIA_CTRL_ADDR_PE_EN
macro_line|#  define CIA_CTRL_ADDR_PE_EN&t;&t;(1 &lt;&lt; 8)
DECL|macro|CIA_CTRL_PERR_EN
macro_line|#  define CIA_CTRL_PERR_EN&t;&t;(1 &lt;&lt; 9)
DECL|macro|CIA_CTRL_FILL_ERR_EN
macro_line|#  define CIA_CTRL_FILL_ERR_EN&t;&t;(1 &lt;&lt; 10)
DECL|macro|CIA_CTRL_MCHK_ERR_EN
macro_line|#  define CIA_CTRL_MCHK_ERR_EN&t;&t;(1 &lt;&lt; 11)
DECL|macro|CIA_CTRL_ECC_CHK_EN
macro_line|#  define CIA_CTRL_ECC_CHK_EN&t;&t;(1 &lt;&lt; 12)
DECL|macro|CIA_CTRL_ASSERT_IDLE_BC
macro_line|#  define CIA_CTRL_ASSERT_IDLE_BC&t;(1 &lt;&lt; 13)
DECL|macro|CIA_CTRL_COM_IDLE_BC
macro_line|#  define CIA_CTRL_COM_IDLE_BC&t;&t;(1 &lt;&lt; 14)
DECL|macro|CIA_CTRL_CSR_IOA_BYPASS
macro_line|#  define CIA_CTRL_CSR_IOA_BYPASS&t;(1 &lt;&lt; 15)
DECL|macro|CIA_CTRL_IO_FLUSHREQ_EN
macro_line|#  define CIA_CTRL_IO_FLUSHREQ_EN&t;(1 &lt;&lt; 16)
DECL|macro|CIA_CTRL_CPU_FLUSHREQ_EN
macro_line|#  define CIA_CTRL_CPU_FLUSHREQ_EN&t;(1 &lt;&lt; 17)
DECL|macro|CIA_CTRL_ARB_CPU_EN
macro_line|#  define CIA_CTRL_ARB_CPU_EN&t;&t;(1 &lt;&lt; 18)
DECL|macro|CIA_CTRL_EN_ARB_LINK
macro_line|#  define CIA_CTRL_EN_ARB_LINK&t;&t;(1 &lt;&lt; 19)
DECL|macro|CIA_CTRL_RD_TYPE_SHIFT
macro_line|#  define CIA_CTRL_RD_TYPE_SHIFT&t;20
DECL|macro|CIA_CTRL_RL_TYPE_SHIFT
macro_line|#  define CIA_CTRL_RL_TYPE_SHIFT&t;24
DECL|macro|CIA_CTRL_RM_TYPE_SHIFT
macro_line|#  define CIA_CTRL_RM_TYPE_SHIFT&t;28
DECL|macro|CIA_CTRL_EN_DMA_RD_PERF
macro_line|#  define CIA_CTRL_EN_DMA_RD_PERF&t;(1 &lt;&lt; 31)
DECL|macro|CIA_IOC_CIA_CNFG
mdefine_line|#define CIA_IOC_CIA_CNFG&t;&t;(IDENT_ADDR + 0x8740000140UL)
DECL|macro|CIA_CNFG_IOA_BWEN
macro_line|#  define CIA_CNFG_IOA_BWEN&t;&t;(1 &lt;&lt; 0)
DECL|macro|CIA_CNFG_PCI_MWEN
macro_line|#  define CIA_CNFG_PCI_MWEN&t;&t;(1 &lt;&lt; 4)
DECL|macro|CIA_CNFG_PCI_DWEN
macro_line|#  define CIA_CNFG_PCI_DWEN&t;&t;(1 &lt;&lt; 5)
DECL|macro|CIA_CNFG_PCI_WLEN
macro_line|#  define CIA_CNFG_PCI_WLEN&t;&t;(1 &lt;&lt; 8)
DECL|macro|CIA_IOC_FLASH_CTRL
mdefine_line|#define CIA_IOC_FLASH_CTRL&t;&t;(IDENT_ADDR + 0x8740000200UL)
DECL|macro|CIA_IOC_HAE_MEM
mdefine_line|#define CIA_IOC_HAE_MEM&t;&t;&t;(IDENT_ADDR + 0x8740000400UL)
DECL|macro|CIA_IOC_HAE_IO
mdefine_line|#define CIA_IOC_HAE_IO&t;&t;&t;(IDENT_ADDR + 0x8740000440UL)
DECL|macro|CIA_IOC_CFG
mdefine_line|#define CIA_IOC_CFG&t;&t;&t;(IDENT_ADDR + 0x8740000480UL)
DECL|macro|CIA_IOC_CACK_EN
mdefine_line|#define CIA_IOC_CACK_EN&t;&t;&t;(IDENT_ADDR + 0x8740000600UL)
DECL|macro|CIA_CACK_EN_LOCK_EN
macro_line|#  define CIA_CACK_EN_LOCK_EN&t;&t;(1 &lt;&lt; 0)
DECL|macro|CIA_CACK_EN_MB_EN
macro_line|#  define CIA_CACK_EN_MB_EN&t;&t;(1 &lt;&lt; 1)
DECL|macro|CIA_CACK_EN_SET_DIRTY_EN
macro_line|#  define CIA_CACK_EN_SET_DIRTY_EN&t;(1 &lt;&lt; 2)
DECL|macro|CIA_CACK_EN_BC_VICTIM_EN
macro_line|#  define CIA_CACK_EN_BC_VICTIM_EN&t;(1 &lt;&lt; 3)
multiline_comment|/*&n; * 21171-CA Diagnostic Registers&n; */
DECL|macro|CIA_IOC_CIA_DIAG
mdefine_line|#define CIA_IOC_CIA_DIAG&t;&t;(IDENT_ADDR + 0x8740002000UL)
DECL|macro|CIA_IOC_DIAG_CHECK
mdefine_line|#define CIA_IOC_DIAG_CHECK&t;&t;(IDENT_ADDR + 0x8740003000UL)
multiline_comment|/*&n; * 21171-CA Performance Monitor registers&n; */
DECL|macro|CIA_IOC_PERF_MONITOR
mdefine_line|#define CIA_IOC_PERF_MONITOR&t;&t;(IDENT_ADDR + 0x8740004000UL)
DECL|macro|CIA_IOC_PERF_CONTROL
mdefine_line|#define CIA_IOC_PERF_CONTROL&t;&t;(IDENT_ADDR + 0x8740004040UL)
multiline_comment|/*&n; * 21171-CA Error registers&n; */
DECL|macro|CIA_IOC_CPU_ERR0
mdefine_line|#define CIA_IOC_CPU_ERR0&t;&t;(IDENT_ADDR + 0x8740008000UL)
DECL|macro|CIA_IOC_CPU_ERR1
mdefine_line|#define CIA_IOC_CPU_ERR1&t;&t;(IDENT_ADDR + 0x8740008040UL)
DECL|macro|CIA_IOC_CIA_ERR
mdefine_line|#define CIA_IOC_CIA_ERR&t;&t;&t;(IDENT_ADDR + 0x8740008200UL)
DECL|macro|CIA_ERR_COR_ERR
macro_line|#  define CIA_ERR_COR_ERR&t;&t;(1 &lt;&lt; 0)
DECL|macro|CIA_ERR_UN_COR_ERR
macro_line|#  define CIA_ERR_UN_COR_ERR&t;&t;(1 &lt;&lt; 1)
DECL|macro|CIA_ERR_CPU_PE
macro_line|#  define CIA_ERR_CPU_PE&t;&t;(1 &lt;&lt; 2)
DECL|macro|CIA_ERR_MEM_NEM
macro_line|#  define CIA_ERR_MEM_NEM&t;&t;(1 &lt;&lt; 3)
DECL|macro|CIA_ERR_PCI_SERR
macro_line|#  define CIA_ERR_PCI_SERR&t;&t;(1 &lt;&lt; 4)
DECL|macro|CIA_ERR_PERR
macro_line|#  define CIA_ERR_PERR&t;&t;&t;(1 &lt;&lt; 5)
DECL|macro|CIA_ERR_PCI_ADDR_PE
macro_line|#  define CIA_ERR_PCI_ADDR_PE&t;&t;(1 &lt;&lt; 6)
DECL|macro|CIA_ERR_RCVD_MAS_ABT
macro_line|#  define CIA_ERR_RCVD_MAS_ABT&t;&t;(1 &lt;&lt; 7)
DECL|macro|CIA_ERR_RCVD_TAR_ABT
macro_line|#  define CIA_ERR_RCVD_TAR_ABT&t;&t;(1 &lt;&lt; 8)
DECL|macro|CIA_ERR_PA_PTE_INV
macro_line|#  define CIA_ERR_PA_PTE_INV&t;&t;(1 &lt;&lt; 9)
DECL|macro|CIA_ERR_FROM_WRT_ERR
macro_line|#  define CIA_ERR_FROM_WRT_ERR&t;&t;(1 &lt;&lt; 10)
DECL|macro|CIA_ERR_IOA_TIMEOUT
macro_line|#  define CIA_ERR_IOA_TIMEOUT&t;&t;(1 &lt;&lt; 11)
DECL|macro|CIA_ERR_LOST_CORR_ERR
macro_line|#  define CIA_ERR_LOST_CORR_ERR&t;&t;(1 &lt;&lt; 16)
DECL|macro|CIA_ERR_LOST_UN_CORR_ERR
macro_line|#  define CIA_ERR_LOST_UN_CORR_ERR&t;(1 &lt;&lt; 17)
DECL|macro|CIA_ERR_LOST_CPU_PE
macro_line|#  define CIA_ERR_LOST_CPU_PE&t;&t;(1 &lt;&lt; 18)
DECL|macro|CIA_ERR_LOST_MEM_NEM
macro_line|#  define CIA_ERR_LOST_MEM_NEM&t;&t;(1 &lt;&lt; 19)
DECL|macro|CIA_ERR_LOST_PERR
macro_line|#  define CIA_ERR_LOST_PERR&t;&t;(1 &lt;&lt; 21)
DECL|macro|CIA_ERR_LOST_PCI_ADDR_PE
macro_line|#  define CIA_ERR_LOST_PCI_ADDR_PE&t;(1 &lt;&lt; 22)
DECL|macro|CIA_ERR_LOST_RCVD_MAS_ABT
macro_line|#  define CIA_ERR_LOST_RCVD_MAS_ABT&t;(1 &lt;&lt; 23)
DECL|macro|CIA_ERR_LOST_RCVD_TAR_ABT
macro_line|#  define CIA_ERR_LOST_RCVD_TAR_ABT&t;(1 &lt;&lt; 24)
DECL|macro|CIA_ERR_LOST_PA_PTE_INV
macro_line|#  define CIA_ERR_LOST_PA_PTE_INV&t;(1 &lt;&lt; 25)
DECL|macro|CIA_ERR_LOST_FROM_WRT_ERR
macro_line|#  define CIA_ERR_LOST_FROM_WRT_ERR&t;(1 &lt;&lt; 26)
DECL|macro|CIA_ERR_LOST_IOA_TIMEOUT
macro_line|#  define CIA_ERR_LOST_IOA_TIMEOUT&t;(1 &lt;&lt; 27)
DECL|macro|CIA_ERR_VALID
macro_line|#  define CIA_ERR_VALID&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|CIA_IOC_CIA_STAT
mdefine_line|#define CIA_IOC_CIA_STAT&t;&t;(IDENT_ADDR + 0x8740008240UL)
DECL|macro|CIA_IOC_ERR_MASK
mdefine_line|#define CIA_IOC_ERR_MASK&t;&t;(IDENT_ADDR + 0x8740008280UL)
DECL|macro|CIA_IOC_CIA_SYN
mdefine_line|#define CIA_IOC_CIA_SYN&t;&t;&t;(IDENT_ADDR + 0x8740008300UL)
DECL|macro|CIA_IOC_MEM_ERR0
mdefine_line|#define CIA_IOC_MEM_ERR0&t;&t;(IDENT_ADDR + 0x8740008400UL)
DECL|macro|CIA_IOC_MEM_ERR1
mdefine_line|#define CIA_IOC_MEM_ERR1&t;&t;(IDENT_ADDR + 0x8740008440UL)
DECL|macro|CIA_IOC_PCI_ERR0
mdefine_line|#define CIA_IOC_PCI_ERR0&t;&t;(IDENT_ADDR + 0x8740008800UL)
DECL|macro|CIA_IOC_PCI_ERR1
mdefine_line|#define CIA_IOC_PCI_ERR1&t;&t;(IDENT_ADDR + 0x8740008840UL)
DECL|macro|CIA_IOC_PCI_ERR3
mdefine_line|#define CIA_IOC_PCI_ERR3&t;&t;(IDENT_ADDR + 0x8740008880UL)
multiline_comment|/*&n; * 21171-CA System configuration registers&n; */
DECL|macro|CIA_IOC_MCR
mdefine_line|#define CIA_IOC_MCR&t;&t;&t;(IDENT_ADDR + 0x8750000000UL)
DECL|macro|CIA_IOC_MBA0
mdefine_line|#define CIA_IOC_MBA0&t;&t;&t;(IDENT_ADDR + 0x8750000600UL)
DECL|macro|CIA_IOC_MBA2
mdefine_line|#define CIA_IOC_MBA2&t;&t;&t;(IDENT_ADDR + 0x8750000680UL)
DECL|macro|CIA_IOC_MBA4
mdefine_line|#define CIA_IOC_MBA4&t;&t;&t;(IDENT_ADDR + 0x8750000700UL)
DECL|macro|CIA_IOC_MBA6
mdefine_line|#define CIA_IOC_MBA6&t;&t;&t;(IDENT_ADDR + 0x8750000780UL)
DECL|macro|CIA_IOC_MBA8
mdefine_line|#define CIA_IOC_MBA8&t;&t;&t;(IDENT_ADDR + 0x8750000800UL)
DECL|macro|CIA_IOC_MBAA
mdefine_line|#define CIA_IOC_MBAA&t;&t;&t;(IDENT_ADDR + 0x8750000880UL)
DECL|macro|CIA_IOC_MBAC
mdefine_line|#define CIA_IOC_MBAC&t;&t;&t;(IDENT_ADDR + 0x8750000900UL)
DECL|macro|CIA_IOC_MBAE
mdefine_line|#define CIA_IOC_MBAE&t;&t;&t;(IDENT_ADDR + 0x8750000980UL)
DECL|macro|CIA_IOC_TMG0
mdefine_line|#define CIA_IOC_TMG0&t;&t;&t;(IDENT_ADDR + 0x8750000B00UL)
DECL|macro|CIA_IOC_TMG1
mdefine_line|#define CIA_IOC_TMG1&t;&t;&t;(IDENT_ADDR + 0x8750000B40UL)
DECL|macro|CIA_IOC_TMG2
mdefine_line|#define CIA_IOC_TMG2&t;&t;&t;(IDENT_ADDR + 0x8750000B80UL)
multiline_comment|/*&n; * 2117A-CA PCI Address and Scatter-Gather Registers.&n; */
DECL|macro|CIA_IOC_PCI_TBIA
mdefine_line|#define CIA_IOC_PCI_TBIA&t;&t;(IDENT_ADDR + 0x8760000100UL)
DECL|macro|CIA_IOC_PCI_W0_BASE
mdefine_line|#define CIA_IOC_PCI_W0_BASE&t;&t;(IDENT_ADDR + 0x8760000400UL)
DECL|macro|CIA_IOC_PCI_W0_MASK
mdefine_line|#define CIA_IOC_PCI_W0_MASK&t;&t;(IDENT_ADDR + 0x8760000440UL)
DECL|macro|CIA_IOC_PCI_T0_BASE
mdefine_line|#define CIA_IOC_PCI_T0_BASE&t;&t;(IDENT_ADDR + 0x8760000480UL)
DECL|macro|CIA_IOC_PCI_W1_BASE
mdefine_line|#define CIA_IOC_PCI_W1_BASE&t;&t;(IDENT_ADDR + 0x8760000500UL)
DECL|macro|CIA_IOC_PCI_W1_MASK
mdefine_line|#define CIA_IOC_PCI_W1_MASK&t;&t;(IDENT_ADDR + 0x8760000540UL)
DECL|macro|CIA_IOC_PCI_T1_BASE
mdefine_line|#define CIA_IOC_PCI_T1_BASE&t;&t;(IDENT_ADDR + 0x8760000580UL)
DECL|macro|CIA_IOC_PCI_W2_BASE
mdefine_line|#define CIA_IOC_PCI_W2_BASE&t;&t;(IDENT_ADDR + 0x8760000600UL)
DECL|macro|CIA_IOC_PCI_W2_MASK
mdefine_line|#define CIA_IOC_PCI_W2_MASK&t;&t;(IDENT_ADDR + 0x8760000640UL)
DECL|macro|CIA_IOC_PCI_T2_BASE
mdefine_line|#define CIA_IOC_PCI_T2_BASE&t;&t;(IDENT_ADDR + 0x8760000680UL)
DECL|macro|CIA_IOC_PCI_W3_BASE
mdefine_line|#define CIA_IOC_PCI_W3_BASE&t;&t;(IDENT_ADDR + 0x8760000700UL)
DECL|macro|CIA_IOC_PCI_W3_MASK
mdefine_line|#define CIA_IOC_PCI_W3_MASK&t;&t;(IDENT_ADDR + 0x8760000740UL)
DECL|macro|CIA_IOC_PCI_T3_BASE
mdefine_line|#define CIA_IOC_PCI_T3_BASE&t;&t;(IDENT_ADDR + 0x8760000780UL)
DECL|macro|CIA_IOC_PCI_Wn_BASE
mdefine_line|#define CIA_IOC_PCI_Wn_BASE(N)&t;(IDENT_ADDR + 0x8760000400UL + (N)*0x100) 
DECL|macro|CIA_IOC_PCI_Wn_MASK
mdefine_line|#define CIA_IOC_PCI_Wn_MASK(N)&t;(IDENT_ADDR + 0x8760000440UL + (N)*0x100) 
DECL|macro|CIA_IOC_PCI_Tn_BASE
mdefine_line|#define CIA_IOC_PCI_Tn_BASE(N)&t;(IDENT_ADDR + 0x8760000480UL + (N)*0x100) 
DECL|macro|CIA_IOC_PCI_W_DAC
mdefine_line|#define CIA_IOC_PCI_W_DAC&t;&t;(IDENT_ADDR + 0x87600007C0UL)
multiline_comment|/*&n; * 2117A-CA Address Translation Registers.&n; */
multiline_comment|/* 8 tag registers, the first 4 of which are lockable.  */
DECL|macro|CIA_IOC_TB_TAGn
mdefine_line|#define CIA_IOC_TB_TAGn(n) &bslash;&n;&t;(IDENT_ADDR + 0x8760000800UL + (n)*0x40)
multiline_comment|/* 4 page registers per tag register.  */
DECL|macro|CIA_IOC_TBn_PAGEm
mdefine_line|#define CIA_IOC_TBn_PAGEm(n,m) &bslash;&n;&t;(IDENT_ADDR + 0x8760001000UL + (n)*0x100 + (m)*0x40)
multiline_comment|/*&n; * Memory spaces:&n; */
DECL|macro|CIA_IACK_SC
mdefine_line|#define CIA_IACK_SC&t;&t;&t;(IDENT_ADDR + 0x8720000000UL)
DECL|macro|CIA_CONF
mdefine_line|#define CIA_CONF&t;&t;&t;(IDENT_ADDR + 0x8700000000UL)
DECL|macro|CIA_IO
mdefine_line|#define CIA_IO&t;&t;&t;&t;(IDENT_ADDR + 0x8580000000UL)
DECL|macro|CIA_SPARSE_MEM
mdefine_line|#define CIA_SPARSE_MEM&t;&t;&t;(IDENT_ADDR + 0x8000000000UL)
DECL|macro|CIA_SPARSE_MEM_R2
mdefine_line|#define CIA_SPARSE_MEM_R2&t;&t;(IDENT_ADDR + 0x8400000000UL)
DECL|macro|CIA_SPARSE_MEM_R3
mdefine_line|#define CIA_SPARSE_MEM_R3&t;&t;(IDENT_ADDR + 0x8500000000UL)
DECL|macro|CIA_DENSE_MEM
mdefine_line|#define CIA_DENSE_MEM&t;&t;        (IDENT_ADDR + 0x8600000000UL)
DECL|macro|CIA_BW_MEM
mdefine_line|#define CIA_BW_MEM&t;&t;&t;(IDENT_ADDR + 0x8800000000UL)
DECL|macro|CIA_BW_IO
mdefine_line|#define CIA_BW_IO&t;&t;&t;(IDENT_ADDR + 0x8900000000UL)
DECL|macro|CIA_BW_CFG_0
mdefine_line|#define CIA_BW_CFG_0&t;&t;&t;(IDENT_ADDR + 0x8a00000000UL)
DECL|macro|CIA_BW_CFG_1
mdefine_line|#define CIA_BW_CFG_1&t;&t;&t;(IDENT_ADDR + 0x8b00000000UL)
multiline_comment|/*&n; * ALCOR&squot;s GRU ASIC registers&n; */
DECL|macro|GRU_INT_REQ
mdefine_line|#define GRU_INT_REQ&t;&t;&t;(IDENT_ADDR + 0x8780000000UL)
DECL|macro|GRU_INT_MASK
mdefine_line|#define GRU_INT_MASK&t;&t;&t;(IDENT_ADDR + 0x8780000040UL)
DECL|macro|GRU_INT_EDGE
mdefine_line|#define GRU_INT_EDGE&t;&t;&t;(IDENT_ADDR + 0x8780000080UL)
DECL|macro|GRU_INT_HILO
mdefine_line|#define GRU_INT_HILO&t;&t;&t;(IDENT_ADDR + 0x87800000C0UL)
DECL|macro|GRU_INT_CLEAR
mdefine_line|#define GRU_INT_CLEAR&t;&t;&t;(IDENT_ADDR + 0x8780000100UL)
DECL|macro|GRU_CACHE_CNFG
mdefine_line|#define GRU_CACHE_CNFG&t;&t;&t;(IDENT_ADDR + 0x8780000200UL)
DECL|macro|GRU_SCR
mdefine_line|#define GRU_SCR&t;&t;&t;&t;(IDENT_ADDR + 0x8780000300UL)
DECL|macro|GRU_LED
mdefine_line|#define GRU_LED&t;&t;&t;&t;(IDENT_ADDR + 0x8780000800UL)
DECL|macro|GRU_RESET
mdefine_line|#define GRU_RESET&t;&t;&t;(IDENT_ADDR + 0x8780000900UL)
DECL|macro|ALCOR_GRU_INT_REQ_BITS
mdefine_line|#define ALCOR_GRU_INT_REQ_BITS&t;&t;0x800fffffUL
DECL|macro|XLT_GRU_INT_REQ_BITS
mdefine_line|#define XLT_GRU_INT_REQ_BITS&t;&t;0x80003fffUL
DECL|macro|GRU_INT_REQ_BITS
mdefine_line|#define GRU_INT_REQ_BITS&t;&t;(alpha_mv.sys.cia.gru_int_req_bits+0)
multiline_comment|/*&n; * PYXIS interrupt control registers&n; */
DECL|macro|PYXIS_INT_REQ
mdefine_line|#define PYXIS_INT_REQ&t;&t;&t;(IDENT_ADDR + 0x87A0000000UL)
DECL|macro|PYXIS_INT_MASK
mdefine_line|#define PYXIS_INT_MASK&t;&t;&t;(IDENT_ADDR + 0x87A0000040UL)
DECL|macro|PYXIS_INT_HILO
mdefine_line|#define PYXIS_INT_HILO&t;&t;&t;(IDENT_ADDR + 0x87A00000C0UL)
DECL|macro|PYXIS_INT_ROUTE
mdefine_line|#define PYXIS_INT_ROUTE&t;&t;&t;(IDENT_ADDR + 0x87A0000140UL)
DECL|macro|PYXIS_GPO
mdefine_line|#define PYXIS_GPO&t;&t;&t;(IDENT_ADDR + 0x87A0000180UL)
DECL|macro|PYXIS_INT_CNFG
mdefine_line|#define PYXIS_INT_CNFG&t;&t;&t;(IDENT_ADDR + 0x87A00001C0UL)
DECL|macro|PYXIS_RT_COUNT
mdefine_line|#define PYXIS_RT_COUNT&t;&t;&t;(IDENT_ADDR + 0x87A0000200UL)
DECL|macro|PYXIS_INT_TIME
mdefine_line|#define PYXIS_INT_TIME&t;&t;&t;(IDENT_ADDR + 0x87A0000240UL)
DECL|macro|PYXIS_IIC_CTRL
mdefine_line|#define PYXIS_IIC_CTRL&t;&t;&t;(IDENT_ADDR + 0x87A00002C0UL)
DECL|macro|PYXIS_RESET
mdefine_line|#define PYXIS_RESET&t;&t;&t;(IDENT_ADDR + 0x8780000900UL)
multiline_comment|/* Offset between ram physical addresses and pci64 DAC bus addresses.  */
DECL|macro|PYXIS_DAC_OFFSET
mdefine_line|#define PYXIS_DAC_OFFSET&t;&t;(1UL &lt;&lt; 40)
multiline_comment|/*&n; * Data structure for handling CIA machine checks.&n; */
multiline_comment|/* System-specific info.  */
DECL|struct|el_CIA_sysdata_mcheck
r_struct
id|el_CIA_sysdata_mcheck
(brace
DECL|member|cpu_err0
r_int
r_int
id|cpu_err0
suffix:semicolon
DECL|member|cpu_err1
r_int
r_int
id|cpu_err1
suffix:semicolon
DECL|member|cia_err
r_int
r_int
id|cia_err
suffix:semicolon
DECL|member|cia_stat
r_int
r_int
id|cia_stat
suffix:semicolon
DECL|member|err_mask
r_int
r_int
id|err_mask
suffix:semicolon
DECL|member|cia_syn
r_int
r_int
id|cia_syn
suffix:semicolon
DECL|member|mem_err0
r_int
r_int
id|mem_err0
suffix:semicolon
DECL|member|mem_err1
r_int
r_int
id|mem_err1
suffix:semicolon
DECL|member|pci_err0
r_int
r_int
id|pci_err0
suffix:semicolon
DECL|member|pci_err1
r_int
r_int
id|pci_err1
suffix:semicolon
DECL|member|pci_err2
r_int
r_int
id|pci_err2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __EXTERN_INLINE
multiline_comment|/* Do not touch, this should *NOT* be static inline */
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__IO_EXTERN_INLINE
mdefine_line|#define __IO_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * I/O functions:&n; *&n; * CIA (the 2117x PCI/memory support chipset for the EV5 (21164)&n; * series of processors uses a sparse address mapping scheme to&n; * get at PCI memory and I/O.&n; */
multiline_comment|/*&n; * Memory functions.  64-bit and 32-bit accesses are done through&n; * dense memory space, everything else through sparse space.&n; *&n; * For reading and writing 8 and 16 bit quantities we need to&n; * go through one of the three sparse address mapping regions&n; * and use the HAE_MEM CSR to provide some bits of the address.&n; * The following few routines use only sparse address region 1&n; * which gives 1Gbyte of accessible space which relates exactly&n; * to the amount of PCI memory mapping *into* system address space.&n; * See p 6-17 of the specification but it looks something like this:&n; *&n; * 21164 Address:&n; *&n; *          3         2         1&n; * 9876543210987654321098765432109876543210&n; * 1ZZZZ0.PCI.QW.Address............BBLL&n; *&n; * ZZ = SBZ&n; * BB = Byte offset&n; * LL = Transfer length&n; *&n; * PCI Address:&n; *&n; * 3         2         1&n; * 10987654321098765432109876543210&n; * HHH....PCI.QW.Address........ 00&n; *&n; * HHH = 31:29 HAE_MEM CSR&n; *&n; */
DECL|macro|vip
mdefine_line|#define vip&t;volatile int __force *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int __force *
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long __force *
DECL|function|cia_ioread8
id|__EXTERN_INLINE
r_int
r_int
id|cia_ioread8
c_func
(paren
r_void
id|__iomem
op_star
id|xaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|xaddr
suffix:semicolon
r_int
r_int
id|result
comma
id|base_and_type
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|CIA_DENSE_MEM
)paren
id|base_and_type
op_assign
id|CIA_SPARSE_MEM
op_plus
l_int|0x00
suffix:semicolon
r_else
id|base_and_type
op_assign
id|CIA_IO
op_plus
l_int|0x00
suffix:semicolon
multiline_comment|/* We can use CIA_MEM_R1_MASK for io ports too, since it is large&n;&t;   enough to cover all io ports, and smaller than CIA_IO.  */
id|addr
op_and_assign
id|CIA_MEM_R1_MASK
suffix:semicolon
id|result
op_assign
op_star
(paren
id|vip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|base_and_type
)paren
suffix:semicolon
r_return
id|__kernel_extbl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|cia_iowrite8
id|__EXTERN_INLINE
r_void
id|cia_iowrite8
c_func
(paren
id|u8
id|b
comma
r_void
id|__iomem
op_star
id|xaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|xaddr
suffix:semicolon
r_int
r_int
id|w
comma
id|base_and_type
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|CIA_DENSE_MEM
)paren
id|base_and_type
op_assign
id|CIA_SPARSE_MEM
op_plus
l_int|0x00
suffix:semicolon
r_else
id|base_and_type
op_assign
id|CIA_IO
op_plus
l_int|0x00
suffix:semicolon
id|addr
op_and_assign
id|CIA_MEM_R1_MASK
suffix:semicolon
id|w
op_assign
id|__kernel_insbl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|base_and_type
)paren
op_assign
id|w
suffix:semicolon
)brace
DECL|function|cia_ioread16
id|__EXTERN_INLINE
r_int
r_int
id|cia_ioread16
c_func
(paren
r_void
id|__iomem
op_star
id|xaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|xaddr
suffix:semicolon
r_int
r_int
id|result
comma
id|base_and_type
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|CIA_DENSE_MEM
)paren
id|base_and_type
op_assign
id|CIA_SPARSE_MEM
op_plus
l_int|0x08
suffix:semicolon
r_else
id|base_and_type
op_assign
id|CIA_IO
op_plus
l_int|0x08
suffix:semicolon
id|addr
op_and_assign
id|CIA_MEM_R1_MASK
suffix:semicolon
id|result
op_assign
op_star
(paren
id|vip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|base_and_type
)paren
suffix:semicolon
r_return
id|__kernel_extwl
c_func
(paren
id|result
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|cia_iowrite16
id|__EXTERN_INLINE
r_void
id|cia_iowrite16
c_func
(paren
id|u16
id|b
comma
r_void
id|__iomem
op_star
id|xaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|xaddr
suffix:semicolon
r_int
r_int
id|w
comma
id|base_and_type
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|CIA_DENSE_MEM
)paren
id|base_and_type
op_assign
id|CIA_SPARSE_MEM
op_plus
l_int|0x08
suffix:semicolon
r_else
id|base_and_type
op_assign
id|CIA_IO
op_plus
l_int|0x08
suffix:semicolon
id|addr
op_and_assign
id|CIA_MEM_R1_MASK
suffix:semicolon
id|w
op_assign
id|__kernel_inswl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|base_and_type
)paren
op_assign
id|w
suffix:semicolon
)brace
DECL|function|cia_ioread32
id|__EXTERN_INLINE
r_int
r_int
id|cia_ioread32
c_func
(paren
r_void
id|__iomem
op_star
id|xaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|xaddr
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|CIA_DENSE_MEM
)paren
id|addr
op_assign
(paren
(paren
id|addr
op_minus
id|CIA_IO
)paren
op_lshift
l_int|5
)paren
op_plus
id|CIA_IO
op_plus
l_int|0x18
suffix:semicolon
r_return
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
)brace
DECL|function|cia_iowrite32
id|__EXTERN_INLINE
r_void
id|cia_iowrite32
c_func
(paren
id|u32
id|b
comma
r_void
id|__iomem
op_star
id|xaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|xaddr
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|CIA_DENSE_MEM
)paren
id|addr
op_assign
(paren
(paren
id|addr
op_minus
id|CIA_IO
)paren
op_lshift
l_int|5
)paren
op_plus
id|CIA_IO
op_plus
l_int|0x18
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|cia_ioportmap
id|__EXTERN_INLINE
r_void
id|__iomem
op_star
id|cia_ioportmap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
id|addr
op_plus
id|CIA_IO
)paren
suffix:semicolon
)brace
DECL|function|cia_ioremap
id|__EXTERN_INLINE
r_void
id|__iomem
op_star
id|cia_ioremap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
id|addr
op_plus
id|CIA_DENSE_MEM
)paren
suffix:semicolon
)brace
DECL|function|cia_is_ioaddr
id|__EXTERN_INLINE
r_int
id|cia_is_ioaddr
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
op_ge
id|IDENT_ADDR
op_plus
l_int|0x8000000000UL
suffix:semicolon
)brace
DECL|function|cia_is_mmio
id|__EXTERN_INLINE
r_int
id|cia_is_mmio
c_func
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|addr
op_ge
id|CIA_DENSE_MEM
suffix:semicolon
)brace
DECL|function|cia_bwx_ioportmap
id|__EXTERN_INLINE
r_void
id|__iomem
op_star
id|cia_bwx_ioportmap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
id|addr
op_plus
id|CIA_BW_IO
)paren
suffix:semicolon
)brace
DECL|function|cia_bwx_ioremap
id|__EXTERN_INLINE
r_void
id|__iomem
op_star
id|cia_bwx_ioremap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_return
(paren
r_void
id|__iomem
op_star
)paren
(paren
id|addr
op_plus
id|CIA_BW_MEM
)paren
suffix:semicolon
)brace
DECL|function|cia_bwx_is_ioaddr
id|__EXTERN_INLINE
r_int
id|cia_bwx_is_ioaddr
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
op_ge
id|IDENT_ADDR
op_plus
l_int|0x8000000000UL
suffix:semicolon
)brace
DECL|function|cia_bwx_is_mmio
id|__EXTERN_INLINE
r_int
id|cia_bwx_is_mmio
c_func
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|addr
OL
id|CIA_BW_IO
suffix:semicolon
)brace
DECL|macro|vip
macro_line|#undef vip
DECL|macro|vuip
macro_line|#undef vuip
DECL|macro|vulp
macro_line|#undef vulp
DECL|macro|__IO_PREFIX
macro_line|#undef __IO_PREFIX
DECL|macro|__IO_PREFIX
mdefine_line|#define __IO_PREFIX&t;&t;cia
DECL|macro|cia_trivial_rw_bw
mdefine_line|#define cia_trivial_rw_bw&t;2
DECL|macro|cia_trivial_rw_lq
mdefine_line|#define cia_trivial_rw_lq&t;1
DECL|macro|cia_trivial_io_bw
mdefine_line|#define cia_trivial_io_bw&t;0
DECL|macro|cia_trivial_io_lq
mdefine_line|#define cia_trivial_io_lq&t;0
DECL|macro|cia_trivial_iounmap
mdefine_line|#define cia_trivial_iounmap&t;1
macro_line|#include &lt;asm/io_trivial.h&gt;
DECL|macro|__IO_PREFIX
macro_line|#undef __IO_PREFIX
DECL|macro|__IO_PREFIX
mdefine_line|#define __IO_PREFIX&t;&t;cia_bwx
DECL|macro|cia_bwx_trivial_rw_bw
mdefine_line|#define cia_bwx_trivial_rw_bw&t;1
DECL|macro|cia_bwx_trivial_rw_lq
mdefine_line|#define cia_bwx_trivial_rw_lq&t;1
DECL|macro|cia_bwx_trivial_io_bw
mdefine_line|#define cia_bwx_trivial_io_bw&t;1
DECL|macro|cia_bwx_trivial_io_lq
mdefine_line|#define cia_bwx_trivial_io_lq&t;1
DECL|macro|cia_bwx_trivial_iounmap
mdefine_line|#define cia_bwx_trivial_iounmap&t;1
macro_line|#include &lt;asm/io_trivial.h&gt;
DECL|macro|__IO_PREFIX
macro_line|#undef __IO_PREFIX
macro_line|#ifdef CONFIG_ALPHA_PYXIS
DECL|macro|__IO_PREFIX
mdefine_line|#define __IO_PREFIX&t;&t;cia_bwx
macro_line|#else
DECL|macro|__IO_PREFIX
mdefine_line|#define __IO_PREFIX&t;&t;cia
macro_line|#endif
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_CIA__H__ */
eof
