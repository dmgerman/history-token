multiline_comment|/*&n; * Marvel systems use the IO7 I/O chip provides PCI/PCIX/AGP access&n; *&n; * This file is based on:&n; *&n; * Marvel / EV7 System Programmer&squot;s Manual&n; * Revision 1.00&n; * 14 May 2001&n; */
macro_line|#ifndef __ALPHA_MARVEL__H__
DECL|macro|__ALPHA_MARVEL__H__
mdefine_line|#define __ALPHA_MARVEL__H__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
DECL|macro|MARVEL_MAX_PIDS
mdefine_line|#define MARVEL_MAX_PIDS&t;&t; 32 /* as long as we rely on 43-bit superpage */
DECL|macro|MARVEL_IRQ_VEC_PE_SHIFT
mdefine_line|#define MARVEL_IRQ_VEC_PE_SHIFT&t;(10)
DECL|macro|MARVEL_IRQ_VEC_IRQ_MASK
mdefine_line|#define MARVEL_IRQ_VEC_IRQ_MASK&t;((1 &lt;&lt; MARVEL_IRQ_VEC_PE_SHIFT) - 1)
DECL|macro|MARVEL_NR_IRQS
mdefine_line|#define MARVEL_NR_IRQS&t;&t;&bslash;&n;&t;(16 + (MARVEL_MAX_PIDS * (1 &lt;&lt; MARVEL_IRQ_VEC_PE_SHIFT)))
multiline_comment|/*&n; * EV7 RBOX Registers&n; */
r_typedef
r_struct
(brace
DECL|member|csr
r_volatile
r_int
r_int
id|csr
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
DECL|typedef|ev7_csr
)brace
id|ev7_csr
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|RBOX_CFG
id|ev7_csr
id|RBOX_CFG
suffix:semicolon
multiline_comment|/* 0x0000 */
DECL|member|RBOX_NSVC
id|ev7_csr
id|RBOX_NSVC
suffix:semicolon
DECL|member|RBOX_EWVC
id|ev7_csr
id|RBOX_EWVC
suffix:semicolon
DECL|member|RBOX_WHAMI
id|ev7_csr
id|RBOX_WHAMI
suffix:semicolon
DECL|member|RBOX_TCTL
id|ev7_csr
id|RBOX_TCTL
suffix:semicolon
multiline_comment|/* 0x0040 */
DECL|member|RBOX_INT
id|ev7_csr
id|RBOX_INT
suffix:semicolon
DECL|member|RBOX_IMASK
id|ev7_csr
id|RBOX_IMASK
suffix:semicolon
DECL|member|RBOX_IREQ
id|ev7_csr
id|RBOX_IREQ
suffix:semicolon
DECL|member|RBOX_INTQ
id|ev7_csr
id|RBOX_INTQ
suffix:semicolon
multiline_comment|/* 0x0080 */
DECL|member|RBOX_INTA
id|ev7_csr
id|RBOX_INTA
suffix:semicolon
DECL|member|RBOX_IT
id|ev7_csr
id|RBOX_IT
suffix:semicolon
DECL|member|RBOX_SCRATCH1
id|ev7_csr
id|RBOX_SCRATCH1
suffix:semicolon
DECL|member|RBOX_SCRATCH2
id|ev7_csr
id|RBOX_SCRATCH2
suffix:semicolon
multiline_comment|/* 0x00c0 */
DECL|member|RBOX_L_ERR
id|ev7_csr
id|RBOX_L_ERR
suffix:semicolon
DECL|typedef|ev7_csrs
)brace
id|ev7_csrs
suffix:semicolon
multiline_comment|/*&n; * EV7 CSR addressing macros&n; */
DECL|macro|EV7_MASK40
mdefine_line|#define EV7_MASK40(addr)        ((addr) &amp; ((1UL &lt;&lt; 41) - 1))
DECL|macro|EV7_KERN_ADDR
mdefine_line|#define EV7_KERN_ADDR(addr)&t;((void *)(IDENT_ADDR | EV7_MASK40(addr)))
DECL|macro|EV7_PE_MASK
mdefine_line|#define EV7_PE_MASK&t;&t;0x1ffUL /* 9 bits ( 256 + mem/io ) */
DECL|macro|EV7_IPE
mdefine_line|#define EV7_IPE(pe)&t;&t;((~((long)(pe)) &amp; EV7_PE_MASK) &lt;&lt; 35)
DECL|macro|EV7_CSR_PHYS
mdefine_line|#define EV7_CSR_PHYS(pe, off)&t;(EV7_IPE(pe) | (0x7FFCUL &lt;&lt; 20) | (off))
DECL|macro|EV7_CSRS_PHYS
mdefine_line|#define EV7_CSRS_PHYS(pe)&t;(EV7_CSR_PHYS(pe, 0UL))
DECL|macro|EV7_CSR_KERN
mdefine_line|#define EV7_CSR_KERN(pe, off)&t;(EV7_KERN_ADDR(EV7_CSR_PHYS(pe, off)))
DECL|macro|EV7_CSRS_KERN
mdefine_line|#define EV7_CSRS_KERN(pe)&t;(EV7_KERN_ADDR(EV7_CSRS_PHYS(pe)))
DECL|macro|EV7_CSR_OFFSET
mdefine_line|#define EV7_CSR_OFFSET(name)&t;((unsigned long)&amp;((ev7_csrs *)NULL)-&gt;name.csr)
multiline_comment|/*&n; * IO7 registers&n; */
r_typedef
r_struct
(brace
DECL|member|csr
r_volatile
r_int
r_int
id|csr
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|64
)paren
)paren
)paren
suffix:semicolon
DECL|typedef|io7_csr
)brace
id|io7_csr
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* I/O Port Control Registers */
DECL|member|POx_CTRL
id|io7_csr
id|POx_CTRL
suffix:semicolon
multiline_comment|/* 0x0000 */
DECL|member|POx_CACHE_CTL
id|io7_csr
id|POx_CACHE_CTL
suffix:semicolon
DECL|member|POx_TIMER
id|io7_csr
id|POx_TIMER
suffix:semicolon
DECL|member|POx_IO_ADR_EXT
id|io7_csr
id|POx_IO_ADR_EXT
suffix:semicolon
DECL|member|POx_MEM_ADR_EXT
id|io7_csr
id|POx_MEM_ADR_EXT
suffix:semicolon
multiline_comment|/* 0x0100 */
DECL|member|POx_XCAL_CTRL
id|io7_csr
id|POx_XCAL_CTRL
suffix:semicolon
DECL|member|rsvd1
id|io7_csr
id|rsvd1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* ?? spec doesn&squot;t show 0x180 */
DECL|member|POx_DM_SOURCE
id|io7_csr
id|POx_DM_SOURCE
suffix:semicolon
multiline_comment|/* 0x0200 */
DECL|member|POx_DM_DEST
id|io7_csr
id|POx_DM_DEST
suffix:semicolon
DECL|member|POx_DM_SIZE
id|io7_csr
id|POx_DM_SIZE
suffix:semicolon
DECL|member|POx_DM_CTRL
id|io7_csr
id|POx_DM_CTRL
suffix:semicolon
DECL|member|rsvd2
id|io7_csr
id|rsvd2
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x0300 */
multiline_comment|/* AGP Control Registers -- port 3 only */
DECL|member|AGP_CAP_ID
id|io7_csr
id|AGP_CAP_ID
suffix:semicolon
multiline_comment|/* 0x0400 */
DECL|member|AGP_STAT
id|io7_csr
id|AGP_STAT
suffix:semicolon
DECL|member|AGP_CMD
id|io7_csr
id|AGP_CMD
suffix:semicolon
DECL|member|rsvd3
id|io7_csr
id|rsvd3
suffix:semicolon
multiline_comment|/* I/O Port Monitor Registers */
DECL|member|POx_MONCTL
id|io7_csr
id|POx_MONCTL
suffix:semicolon
multiline_comment|/* 0x0500 */
DECL|member|POx_CTRA
id|io7_csr
id|POx_CTRA
suffix:semicolon
DECL|member|POx_CTRB
id|io7_csr
id|POx_CTRB
suffix:semicolon
DECL|member|POx_CTR56
id|io7_csr
id|POx_CTR56
suffix:semicolon
DECL|member|POx_SCRATCH
id|io7_csr
id|POx_SCRATCH
suffix:semicolon
multiline_comment|/* 0x0600 */
DECL|member|POx_XTRA_A
id|io7_csr
id|POx_XTRA_A
suffix:semicolon
DECL|member|POx_XTRA_TS
id|io7_csr
id|POx_XTRA_TS
suffix:semicolon
DECL|member|POx_XTRA_Z
id|io7_csr
id|POx_XTRA_Z
suffix:semicolon
DECL|member|rsvd4
id|io7_csr
id|rsvd4
suffix:semicolon
multiline_comment|/* 0x0700 */
DECL|member|POx_THRESHA
id|io7_csr
id|POx_THRESHA
suffix:semicolon
DECL|member|POx_THRESHB
id|io7_csr
id|POx_THRESHB
suffix:semicolon
DECL|member|rsvd5
id|io7_csr
id|rsvd5
(braket
l_int|33
)braket
suffix:semicolon
multiline_comment|/* System Address Space Window Control Registers */
DECL|member|POx_WBASE
id|io7_csr
id|POx_WBASE
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x1000 */
DECL|member|POx_WMASK
id|io7_csr
id|POx_WMASK
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|POx_TBASE
id|io7_csr
id|POx_TBASE
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|POx_SG_TBIA
id|io7_csr
id|POx_SG_TBIA
suffix:semicolon
DECL|member|POx_MSI_WBASE
id|io7_csr
id|POx_MSI_WBASE
suffix:semicolon
DECL|member|rsvd6
id|io7_csr
id|rsvd6
(braket
l_int|50
)braket
suffix:semicolon
multiline_comment|/* I/O Port Error Registers */
DECL|member|POx_ERR_SUM
id|io7_csr
id|POx_ERR_SUM
suffix:semicolon
DECL|member|POx_FIRST_ERR
id|io7_csr
id|POx_FIRST_ERR
suffix:semicolon
DECL|member|POx_MSK_HEI
id|io7_csr
id|POx_MSK_HEI
suffix:semicolon
DECL|member|POx_TLB_ERR
id|io7_csr
id|POx_TLB_ERR
suffix:semicolon
DECL|member|POx_SPL_COMPLT
id|io7_csr
id|POx_SPL_COMPLT
suffix:semicolon
DECL|member|POx_TRANS_SUM
id|io7_csr
id|POx_TRANS_SUM
suffix:semicolon
DECL|member|POx_FRC_PCI_ERR
id|io7_csr
id|POx_FRC_PCI_ERR
suffix:semicolon
DECL|member|POx_MULT_ERR
id|io7_csr
id|POx_MULT_ERR
suffix:semicolon
DECL|member|rsvd7
id|io7_csr
id|rsvd7
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* I/O Port End of Interrupt Registers */
DECL|member|EOI_DAT
id|io7_csr
id|EOI_DAT
suffix:semicolon
DECL|member|rsvd8
id|io7_csr
id|rsvd8
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|POx_IACK_SPECIAL
id|io7_csr
id|POx_IACK_SPECIAL
suffix:semicolon
DECL|member|rsvd9
id|io7_csr
id|rsvd9
(braket
l_int|103
)braket
suffix:semicolon
DECL|typedef|io7_ioport_csrs
)brace
id|io7_ioport_csrs
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|IO_ASIC_REV
id|io7_csr
id|IO_ASIC_REV
suffix:semicolon
multiline_comment|/* 0x30.0000 */
DECL|member|IO_SYS_REV
id|io7_csr
id|IO_SYS_REV
suffix:semicolon
DECL|member|SER_CHAIN3
id|io7_csr
id|SER_CHAIN3
suffix:semicolon
DECL|member|PO7_RST1
id|io7_csr
id|PO7_RST1
suffix:semicolon
DECL|member|PO7_RST2
id|io7_csr
id|PO7_RST2
suffix:semicolon
multiline_comment|/* 0x30.0100 */
DECL|member|POx_RST
id|io7_csr
id|POx_RST
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|IO7_DWNH
id|io7_csr
id|IO7_DWNH
suffix:semicolon
DECL|member|IO7_MAF
id|io7_csr
id|IO7_MAF
suffix:semicolon
DECL|member|IO7_MAF_TO
id|io7_csr
id|IO7_MAF_TO
suffix:semicolon
DECL|member|IO7_ACC_CLUMP
id|io7_csr
id|IO7_ACC_CLUMP
suffix:semicolon
multiline_comment|/* 0x30.0300 */
DECL|member|IO7_PMASK
id|io7_csr
id|IO7_PMASK
suffix:semicolon
DECL|member|IO7_IOMASK
id|io7_csr
id|IO7_IOMASK
suffix:semicolon
DECL|member|IO7_UPH
id|io7_csr
id|IO7_UPH
suffix:semicolon
DECL|member|IO7_UPH_TO
id|io7_csr
id|IO7_UPH_TO
suffix:semicolon
multiline_comment|/* 0x30.0400 */
DECL|member|RBX_IREQ_OFF
id|io7_csr
id|RBX_IREQ_OFF
suffix:semicolon
DECL|member|RBX_INTA_OFF
id|io7_csr
id|RBX_INTA_OFF
suffix:semicolon
DECL|member|INT_RTY
id|io7_csr
id|INT_RTY
suffix:semicolon
DECL|member|PO7_MONCTL
id|io7_csr
id|PO7_MONCTL
suffix:semicolon
multiline_comment|/* 0x30.0500 */
DECL|member|PO7_CTRA
id|io7_csr
id|PO7_CTRA
suffix:semicolon
DECL|member|PO7_CTRB
id|io7_csr
id|PO7_CTRB
suffix:semicolon
DECL|member|PO7_CTR56
id|io7_csr
id|PO7_CTR56
suffix:semicolon
DECL|member|PO7_SCRATCH
id|io7_csr
id|PO7_SCRATCH
suffix:semicolon
multiline_comment|/* 0x30.0600 */
DECL|member|PO7_XTRA_A
id|io7_csr
id|PO7_XTRA_A
suffix:semicolon
DECL|member|PO7_XTRA_TS
id|io7_csr
id|PO7_XTRA_TS
suffix:semicolon
DECL|member|PO7_XTRA_Z
id|io7_csr
id|PO7_XTRA_Z
suffix:semicolon
DECL|member|PO7_PMASK
id|io7_csr
id|PO7_PMASK
suffix:semicolon
multiline_comment|/* 0x30.0700 */
DECL|member|PO7_THRESHA
id|io7_csr
id|PO7_THRESHA
suffix:semicolon
DECL|member|PO7_THRESHB
id|io7_csr
id|PO7_THRESHB
suffix:semicolon
DECL|member|rsvd1
id|io7_csr
id|rsvd1
(braket
l_int|97
)braket
suffix:semicolon
DECL|member|PO7_ERROR_SUM
id|io7_csr
id|PO7_ERROR_SUM
suffix:semicolon
multiline_comment|/* 0x30.2000 */
DECL|member|PO7_BHOLE_MASK
id|io7_csr
id|PO7_BHOLE_MASK
suffix:semicolon
DECL|member|PO7_HEI_MSK
id|io7_csr
id|PO7_HEI_MSK
suffix:semicolon
DECL|member|PO7_CRD_MSK
id|io7_csr
id|PO7_CRD_MSK
suffix:semicolon
DECL|member|PO7_UNCRR_SYM
id|io7_csr
id|PO7_UNCRR_SYM
suffix:semicolon
multiline_comment|/* 0x30.2100 */
DECL|member|PO7_CRRCT_SYM
id|io7_csr
id|PO7_CRRCT_SYM
suffix:semicolon
DECL|member|PO7_ERR_PKT
id|io7_csr
id|PO7_ERR_PKT
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|PO7_UGBGE_SYM
id|io7_csr
id|PO7_UGBGE_SYM
suffix:semicolon
multiline_comment|/* 0x30.2200 */
DECL|member|rsbv2
id|io7_csr
id|rsbv2
(braket
l_int|887
)braket
suffix:semicolon
DECL|member|PO7_LSI_CTL
id|io7_csr
id|PO7_LSI_CTL
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* 0x31.0000 */
DECL|member|rsvd3
id|io7_csr
id|rsvd3
(braket
l_int|123
)braket
suffix:semicolon
DECL|member|HLT_CTL
id|io7_csr
id|HLT_CTL
suffix:semicolon
multiline_comment|/* 0x31.3ec0 */
DECL|member|HPI_CTL
id|io7_csr
id|HPI_CTL
suffix:semicolon
multiline_comment|/* 0x31.3f00 */
DECL|member|CRD_CTL
id|io7_csr
id|CRD_CTL
suffix:semicolon
DECL|member|STV_CTL
id|io7_csr
id|STV_CTL
suffix:semicolon
DECL|member|HEI_CTL
id|io7_csr
id|HEI_CTL
suffix:semicolon
DECL|member|PO7_MSI_CTL
id|io7_csr
id|PO7_MSI_CTL
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x31.4000 */
DECL|member|rsvd4
id|io7_csr
id|rsvd4
(braket
l_int|240
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Interrupt Diagnostic / Test&n;&t; */
r_struct
(brace
DECL|member|INT_PND
id|io7_csr
id|INT_PND
suffix:semicolon
DECL|member|INT_CLR
id|io7_csr
id|INT_CLR
suffix:semicolon
DECL|member|INT_EOI
id|io7_csr
id|INT_EOI
suffix:semicolon
DECL|member|rsvd
id|io7_csr
id|rsvd
(braket
l_int|29
)braket
suffix:semicolon
DECL|member|INT_DIAG
)brace
id|INT_DIAG
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|rsvd5
id|io7_csr
id|rsvd5
(braket
l_int|125
)braket
suffix:semicolon
multiline_comment|/* 0x31.a000 */
DECL|member|MISC_PND
id|io7_csr
id|MISC_PND
suffix:semicolon
multiline_comment|/* 0x31.b800 */
DECL|member|rsvd6
id|io7_csr
id|rsvd6
(braket
l_int|31
)braket
suffix:semicolon
DECL|member|MSI_PND
id|io7_csr
id|MSI_PND
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x31.c000 */
DECL|member|rsvd7
id|io7_csr
id|rsvd7
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|MSI_CLR
id|io7_csr
id|MSI_CLR
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x31.c800 */
DECL|typedef|io7_port7_csrs
)brace
id|io7_port7_csrs
suffix:semicolon
multiline_comment|/* &n; * IO7 DMA Window Base register (POx_WBASEx)&n; */
DECL|macro|wbase_m_ena
mdefine_line|#define wbase_m_ena  0x1
DECL|macro|wbase_m_sg
mdefine_line|#define wbase_m_sg   0x2
DECL|macro|wbase_m_dac
mdefine_line|#define wbase_m_dac  0x4
DECL|macro|wbase_m_addr
mdefine_line|#define wbase_m_addr 0xFFF00000
DECL|union|IO7_POx_WBASE
r_union
id|IO7_POx_WBASE
(brace
r_struct
(brace
DECL|member|ena
r_int
id|ena
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* &lt;0&gt;&t;&t;&t;*/
DECL|member|sg
r_int
id|sg
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* &lt;1&gt;&t;&t;&t;*/
DECL|member|dac
r_int
id|dac
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* &lt;2&gt; -- window 3 only */
DECL|member|rsvd1
r_int
id|rsvd1
suffix:colon
l_int|17
suffix:semicolon
DECL|member|addr
r_int
id|addr
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* &lt;31:20&gt;&t;&t;*/
DECL|member|rsvd2
r_int
id|rsvd2
suffix:colon
l_int|32
suffix:semicolon
DECL|member|bits
)brace
id|bits
suffix:semicolon
DECL|member|as_long
r_int
id|as_long
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|as_quad
r_int
id|as_quad
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * IO7 IID (Interrupt IDentifier) format&n; *&n; * For level-sensative interrupts, int_num is encoded as:&n; *&n; *&t;bus/port&t;slot/device&t;INTx&n; *&t;&lt;7:5&gt;&t;&t;&lt;4:2&gt;&t;&t;&lt;1:0&gt;&n; */
DECL|union|IO7_IID
r_union
id|IO7_IID
(brace
r_struct
(brace
DECL|member|int_num
r_int
id|int_num
suffix:colon
l_int|9
suffix:semicolon
multiline_comment|/* &lt;8:0&gt;    &t;*/
DECL|member|tpu_mask
r_int
id|tpu_mask
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* &lt;12:9&gt; rsvd&t;*/
DECL|member|msi
r_int
id|msi
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 13&t;&t;*/
DECL|member|ipe
r_int
id|ipe
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* &lt;23:14&gt;&t;*/
DECL|member|rsvd
r_int
r_int
id|rsvd
suffix:colon
l_int|40
suffix:semicolon
DECL|member|bits
)brace
id|bits
suffix:semicolon
DECL|member|as_long
r_int
r_int
id|as_long
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|as_quad
r_int
r_int
id|as_quad
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * IO7 addressing macros&n; */
DECL|macro|IO7_KERN_ADDR
mdefine_line|#define IO7_KERN_ADDR(addr)&t;(EV7_KERN_ADDR(addr))
DECL|macro|IO7_PORT_MASK
mdefine_line|#define IO7_PORT_MASK&t;   &t;0x07UL&t;/* 3 bits of port &t;   */
DECL|macro|IO7_IPE
mdefine_line|#define IO7_IPE(pe)&t;&t;(EV7_IPE(pe))
DECL|macro|IO7_IPORT
mdefine_line|#define IO7_IPORT(port)&t;&t;((~((long)(port)) &amp; IO7_PORT_MASK) &lt;&lt; 32)
DECL|macro|IO7_HOSE
mdefine_line|#define IO7_HOSE(pe, port)&t;(IO7_IPE(pe) | IO7_IPORT(port))
DECL|macro|IO7_MEM_PHYS
mdefine_line|#define IO7_MEM_PHYS(pe, port)&t;(IO7_HOSE(pe, port) | 0x00000000UL)
DECL|macro|IO7_CONF_PHYS
mdefine_line|#define IO7_CONF_PHYS(pe, port)&t;(IO7_HOSE(pe, port) | 0xFE000000UL)
DECL|macro|IO7_IO_PHYS
mdefine_line|#define IO7_IO_PHYS(pe, port)&t;(IO7_HOSE(pe, port) | 0xFF000000UL)
DECL|macro|IO7_CSR_PHYS
mdefine_line|#define IO7_CSR_PHYS(pe, port, off) &bslash;&n;                                (IO7_HOSE(pe, port) | 0xFF800000UL | (off))
DECL|macro|IO7_CSRS_PHYS
mdefine_line|#define IO7_CSRS_PHYS(pe, port)&t;(IO7_CSR_PHYS(pe, port, 0UL))
DECL|macro|IO7_PORT7_CSRS_PHYS
mdefine_line|#define IO7_PORT7_CSRS_PHYS(pe) (IO7_CSR_PHYS(pe, 7, 0x300000UL))
DECL|macro|IO7_MEM_KERN
mdefine_line|#define IO7_MEM_KERN(pe, port)      (IO7_KERN_ADDR(IO7_MEM_PHYS(pe, port)))
DECL|macro|IO7_CONF_KERN
mdefine_line|#define IO7_CONF_KERN(pe, port)     (IO7_KERN_ADDR(IO7_CONF_PHYS(pe, port)))
DECL|macro|IO7_IO_KERN
mdefine_line|#define IO7_IO_KERN(pe, port)       (IO7_KERN_ADDR(IO7_IO_PHYS(pe, port)))
DECL|macro|IO7_CSR_KERN
mdefine_line|#define IO7_CSR_KERN(pe, port, off) (IO7_KERN_ADDR(IO7_CSR_PHYS(pe,port,off)))
DECL|macro|IO7_CSRS_KERN
mdefine_line|#define IO7_CSRS_KERN(pe, port)     (IO7_KERN_ADDR(IO7_CSRS_PHYS(pe, port)))
DECL|macro|IO7_PORT7_CSRS_KERN
mdefine_line|#define IO7_PORT7_CSRS_KERN(pe)&t;    (IO7_KERN_ADDR(IO7_PORT7_CSRS_PHYS(pe)))
DECL|macro|IO7_PLL_RNGA
mdefine_line|#define IO7_PLL_RNGA(pll)&t;(((pll) &gt;&gt; 3) &amp; 0x7)
DECL|macro|IO7_PLL_RNGB
mdefine_line|#define IO7_PLL_RNGB(pll)&t;(((pll) &gt;&gt; 6) &amp; 0x7)
DECL|macro|IO7_MEM_SPACE
mdefine_line|#define IO7_MEM_SPACE&t;&t;(2UL * 1024 * 1024 * 1024)&t;/* 2GB MEM */
DECL|macro|IO7_IO_SPACE
mdefine_line|#define IO7_IO_SPACE&t;&t;(8UL * 1024 * 1024)&t;&t;/* 8MB I/O */
multiline_comment|/* &n; * Offset between ram physical addresses and pci64 DAC addresses&n; */
DECL|macro|IO7_DAC_OFFSET
mdefine_line|#define IO7_DAC_OFFSET&t;&t;(1UL &lt;&lt; 49)
multiline_comment|/*&n; * This is needed to satisify the IO() macro used in initializing the machvec&n; */
DECL|macro|MARVEL_IACK_SC
mdefine_line|#define MARVEL_IACK_SC &t;&t;&t;&t;&t;&t;&t;&bslash;&n;        ((unsigned long)&t;&t;&t;&t;&t;&t;&bslash;&n;&t; (&amp;(((io7_ioport_csrs *)IO7_CSRS_KERN(0, 0))-&gt;POx_IACK_SPECIAL)))
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * IO7 structs&n; */
DECL|macro|IO7_NUM_PORTS
mdefine_line|#define IO7_NUM_PORTS 4
DECL|macro|IO7_AGP_PORT
mdefine_line|#define IO7_AGP_PORT  3
DECL|struct|io7_port
r_struct
id|io7_port
(brace
DECL|member|io7
r_struct
id|io7
op_star
id|io7
suffix:semicolon
DECL|member|hose
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
DECL|member|enabled
r_int
id|enabled
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|csrs
id|io7_ioport_csrs
op_star
id|csrs
suffix:semicolon
DECL|member|saved_wbase
r_int
r_int
id|saved_wbase
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|saved_wmask
r_int
r_int
id|saved_wmask
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|saved_tbase
r_int
r_int
id|saved_tbase
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|io7
r_struct
id|io7
(brace
DECL|member|next
r_struct
id|io7
op_star
id|next
suffix:semicolon
DECL|member|pe
r_int
r_int
id|pe
suffix:semicolon
DECL|member|csrs
id|io7_port7_csrs
op_star
id|csrs
suffix:semicolon
DECL|member|ports
r_struct
id|io7_port
id|ports
(braket
id|IO7_NUM_PORTS
)braket
suffix:semicolon
DECL|member|irq_lock
id|spinlock_t
id|irq_lock
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|# define __EXTERN_INLINE extern inline
DECL|macro|__IO_EXTERN_INLINE
macro_line|# define __IO_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * I/O functions. All access through linear space.&n; */
multiline_comment|/*&n; * Memory functions.  All accesses through linear space.&n; */
DECL|macro|vucp
mdefine_line|#define vucp&t;volatile unsigned char __force *
DECL|macro|vusp
mdefine_line|#define vusp&t;volatile unsigned short __force *
r_extern
r_int
r_int
id|marvel_ioread8
c_func
(paren
r_void
id|__iomem
op_star
)paren
suffix:semicolon
r_extern
r_void
id|marvel_iowrite8
c_func
(paren
id|u8
id|b
comma
r_void
id|__iomem
op_star
)paren
suffix:semicolon
DECL|function|marvel_ioread16
id|__EXTERN_INLINE
r_int
r_int
id|marvel_ioread16
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|marvel_iowrite16
id|__EXTERN_INLINE
r_void
id|marvel_iowrite16
c_func
(paren
id|u16
id|b
comma
r_void
id|__iomem
op_star
id|addr
)paren
(brace
id|__kernel_stw
c_func
(paren
id|b
comma
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__iomem
op_star
id|marvel_ioremap
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
suffix:semicolon
r_extern
r_void
id|marvel_iounmap
c_func
(paren
r_volatile
r_void
id|__iomem
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|__iomem
op_star
id|marvel_ioportmap
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|function|marvel_is_ioaddr
id|__EXTERN_INLINE
r_int
id|marvel_is_ioaddr
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
(paren
id|addr
op_rshift
l_int|40
)paren
op_amp
l_int|1
suffix:semicolon
)brace
r_extern
r_int
id|marvel_is_mmio
c_func
(paren
r_const
r_volatile
r_void
id|__iomem
op_star
)paren
suffix:semicolon
DECL|macro|vucp
macro_line|#undef vucp
DECL|macro|vusp
macro_line|#undef vusp
DECL|macro|__IO_PREFIX
macro_line|#undef __IO_PREFIX
DECL|macro|__IO_PREFIX
mdefine_line|#define __IO_PREFIX&t;&t;marvel
DECL|macro|marvel_trivial_rw_bw
mdefine_line|#define marvel_trivial_rw_bw&t;1
DECL|macro|marvel_trivial_rw_lq
mdefine_line|#define marvel_trivial_rw_lq&t;1
DECL|macro|marvel_trivial_io_bw
mdefine_line|#define marvel_trivial_io_bw&t;0
DECL|macro|marvel_trivial_io_lq
mdefine_line|#define marvel_trivial_io_lq&t;1
DECL|macro|marvel_trivial_iounmap
mdefine_line|#define marvel_trivial_iounmap&t;0
macro_line|#include &lt;asm/io_trivial.h&gt;
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|# undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|# undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_MARVEL__H__ */
eof
