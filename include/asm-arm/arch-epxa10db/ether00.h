macro_line|#ifndef __ETHER00_H
DECL|macro|__ETHER00_H
mdefine_line|#define __ETHER00_H
multiline_comment|/*&n; * Register definitions for the Ethernet MAC&n; */
multiline_comment|/*&n; * Copyright (c) Altera Corporation 2000.&n; * All rights reserved.&n; */
multiline_comment|/*&n;*&t;Structures for the DMA controller&n;*/
DECL|struct|fda_desc
r_typedef
r_struct
id|fda_desc
(brace
DECL|member|FDNext
r_struct
id|fda_desc
op_star
id|FDNext
suffix:semicolon
DECL|member|FDSystem
r_int
id|FDSystem
suffix:semicolon
DECL|member|FDStat
r_int
id|FDStat
suffix:semicolon
DECL|member|FDLength
r_int
id|FDLength
suffix:semicolon
DECL|member|FDCtl
r_int
id|FDCtl
suffix:semicolon
DECL|typedef|FDA_DESC
)brace
id|FDA_DESC
suffix:semicolon
DECL|struct|buf_desc
r_typedef
r_struct
id|buf_desc
(brace
DECL|member|BuffData
r_char
op_star
id|BuffData
suffix:semicolon
DECL|member|BuffLength
r_int
id|BuffLength
suffix:semicolon
DECL|member|BDStat
r_char
id|BDStat
suffix:semicolon
DECL|member|BDCtl
r_char
id|BDCtl
suffix:semicolon
DECL|typedef|BUF_DESC
)brace
id|BUF_DESC
suffix:semicolon
multiline_comment|/*&n;*&t;Control masks for the DMA controller&n;*/
DECL|macro|FDCTL_BDCOUNT_MSK
mdefine_line|#define FDCTL_BDCOUNT_MSK&t;&t;&t;&t;&t;&t;(0x1F)
DECL|macro|FDCTL_BDCOUNT_OFST
mdefine_line|#define FDCTL_BDCOUNT_OFST&t;&t;&t;&t;&t;&t;(0)
DECL|macro|FDCTL_FRMOPT_MSK
mdefine_line|#define FDCTL_FRMOPT_MSK&t;&t;&t;&t;&t;&t;(0x7C00)
DECL|macro|FDCTL_FRMOPT_OFST
mdefine_line|#define FDCTL_FRMOPT_OFST&t;&t;&t;&t;&t;&t;(10)
DECL|macro|FDCTL_COWNSFD_MSK
mdefine_line|#define&t;FDCTL_COWNSFD_MSK&t;&t;&t;&t;&t;&t;(0x8000)
DECL|macro|FDCTL_COWNSFD_OFST
mdefine_line|#define&t;FDCTL_COWNSFD_OFST&t;&t;&t;&t;&t;&t;(15)
DECL|macro|BDCTL_RXBDSEQN_MSK
mdefine_line|#define BDCTL_RXBDSEQN_MSK&t;&t;&t;&t;&t;&t;(0x7F)
DECL|macro|BDCTL_RXBDSEQN_OFST
mdefine_line|#define BDCTL_RXBDSEQN_OFST&t;&t;&t;&t;&t;&t;(0)
DECL|macro|BDCTL_COWNSBD_MSK
mdefine_line|#define&t;BDCTL_COWNSBD_MSK&t;&t;&t;&t;&t;&t;(0x80)
DECL|macro|BDCTL_COWNSBD_OFST
mdefine_line|#define&t;BDCTL_COWNSBD_OFST&t;&t;&t;&t;&t;&t;(7)
DECL|macro|FDNEXT_EOL_MSK
mdefine_line|#define FDNEXT_EOL_MSK&t;&t;&t;&t;&t;&t;&t;(0x1)
DECL|macro|FDNEXT_EOL_OFST
mdefine_line|#define FDNEXT_EOL_OFST&t;&t;&t;&t;&t;&t;&t;(0)
DECL|macro|FDNEXT_EOL_POINTER_MSK
mdefine_line|#define FDNEXT_EOL_POINTER_MSK&t;&t;&t;&t;&t;(0xFFFFFFF0)
DECL|macro|FDNEXT_EOL_POINTER_OFST
mdefine_line|#define FDNEXT_EOL_POINTER_OFST&t;&t;&t;&t;&t;(4)
DECL|macro|ETHER_ARC_SIZE
mdefine_line|#define ETHER_ARC_SIZE         (21)
multiline_comment|/*&n;*&t;Regsiter definitions and masks&n;*/
DECL|macro|ETHER_DMA_CTL
mdefine_line|#define ETHER_DMA_CTL(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x100))
DECL|macro|ETHER_DMA_CTL_DMBURST_OFST
mdefine_line|#define ETHER_DMA_CTL_DMBURST_OFST&t;&t;&t;&t;(2)
DECL|macro|ETHER_DMA_CTL_DMBURST_MSK
mdefine_line|#define ETHER_DMA_CTL_DMBURST_MSK&t;&t;&t;&t;(0x1FC)
DECL|macro|ETHER_DMA_CTL_POWRMGMNT_OFST
mdefine_line|#define ETHER_DMA_CTL_POWRMGMNT_OFST&t;&t;&t;(11)
DECL|macro|ETHER_DMA_CTL_POWRMGMNT_MSK
mdefine_line|#define ETHER_DMA_CTL_POWRMGMNT_MSK&t;&t;&t;&t;(0x1000)
DECL|macro|ETHER_DMA_CTL_TXBIGE_OFST
mdefine_line|#define ETHER_DMA_CTL_TXBIGE_OFST&t;&t;&t;&t;(14)
DECL|macro|ETHER_DMA_CTL_TXBIGE_MSK
mdefine_line|#define ETHER_DMA_CTL_TXBIGE_MSK&t;&t;&t;&t;(0x4000)
DECL|macro|ETHER_DMA_CTL_RXBIGE_OFST
mdefine_line|#define ETHER_DMA_CTL_RXBIGE_OFST&t;&t;&t;&t;(15)
DECL|macro|ETHER_DMA_CTL_RXBIGE_MSK
mdefine_line|#define ETHER_DMA_CTL_RXBIGE_MSK&t;&t;&t;&t;(0x8000)
DECL|macro|ETHER_DMA_CTL_TXWAKEUP_OFST
mdefine_line|#define ETHER_DMA_CTL_TXWAKEUP_OFST&t;&t;&t;&t;(16)
DECL|macro|ETHER_DMA_CTL_TXWAKEUP_MSK
mdefine_line|#define ETHER_DMA_CTL_TXWAKEUP_MSK&t;&t;&t;&t;(0x10000)
DECL|macro|ETHER_DMA_CTL_SWINTREQ_OFST
mdefine_line|#define ETHER_DMA_CTL_SWINTREQ_OFST&t;&t;&t;&t;(17)
DECL|macro|ETHER_DMA_CTL_SWINTREQ_MSK
mdefine_line|#define ETHER_DMA_CTL_SWINTREQ_MSK&t;&t;&t;&t;(0x20000)
DECL|macro|ETHER_DMA_CTL_INTMASK_OFST
mdefine_line|#define ETHER_DMA_CTL_INTMASK_OFST&t;&t;&t;&t;(18)
DECL|macro|ETHER_DMA_CTL_INTMASK_MSK
mdefine_line|#define ETHER_DMA_CTL_INTMASK_MSK&t;&t;&t;&t;(0x40000)
DECL|macro|ETHER_DMA_CTL_M66ENSTAT_OFST
mdefine_line|#define ETHER_DMA_CTL_M66ENSTAT_OFST&t;&t;&t;(19)
DECL|macro|ETHER_DMA_CTL_M66ENSTAT_MSK
mdefine_line|#define ETHER_DMA_CTL_M66ENSTAT_MSK&t;&t;&t;&t;(0x80000)
DECL|macro|ETHER_DMA_CTL_RMTXINIT_OFST
mdefine_line|#define ETHER_DMA_CTL_RMTXINIT_OFST&t;&t;&t;&t;(20)
DECL|macro|ETHER_DMA_CTL_RMTXINIT_MSK
mdefine_line|#define ETHER_DMA_CTL_RMTXINIT_MSK&t;&t;&t;&t;(0x100000)
DECL|macro|ETHER_DMA_CTL_RMRXINIT_OFST
mdefine_line|#define ETHER_DMA_CTL_RMRXINIT_OFST&t;&t;&t;&t;(21)
DECL|macro|ETHER_DMA_CTL_RMRXINIT_MSK
mdefine_line|#define ETHER_DMA_CTL_RMRXINIT_MSK&t;&t;&t;&t;(0x200000)
DECL|macro|ETHER_DMA_CTL_RXALIGN_OFST
mdefine_line|#define ETHER_DMA_CTL_RXALIGN_OFST&t;&t;&t;&t;(22)
DECL|macro|ETHER_DMA_CTL_RXALIGN_MSK
mdefine_line|#define ETHER_DMA_CTL_RXALIGN_MSK&t;&t;&t;&t;(0xC00000)
DECL|macro|ETHER_DMA_CTL_RMSWRQ_OFST
mdefine_line|#define ETHER_DMA_CTL_RMSWRQ_OFST&t;&t;&t;&t;(24)
DECL|macro|ETHER_DMA_CTL_RMSWRQ_MSK
mdefine_line|#define ETHER_DMA_CTL_RMSWRQ_MSK&t;&t;&t;&t;(0x1000000)
DECL|macro|ETHER_DMA_CTL_RMEMBANK_OFST
mdefine_line|#define ETHER_DMA_CTL_RMEMBANK_OFST&t;&t;&t;&t;(25)
DECL|macro|ETHER_DMA_CTL_RMEMBANK_MSK
mdefine_line|#define ETHER_DMA_CTL_RMEMBANK_MSK&t;&t;&t;&t;(0x2000000)
DECL|macro|ETHER_TXFRMPTR
mdefine_line|#define ETHER_TXFRMPTR(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x104))
DECL|macro|ETHER_TXTHRSH
mdefine_line|#define ETHER_TXTHRSH(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x308))
DECL|macro|ETHER_TXPOLLCTR
mdefine_line|#define ETHER_TXPOLLCTR(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x30c))
DECL|macro|ETHER_BLFRMPTR
mdefine_line|#define&t;ETHER_BLFRMPTR(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x110))
DECL|macro|ETHER_BLFFRMPTR_EOL_OFST
mdefine_line|#define ETHER_BLFFRMPTR_EOL_OFST&t;&t;&t;&t;(0)
DECL|macro|ETHER_BLFFRMPTR_EOL_MSK
mdefine_line|#define ETHER_BLFFRMPTR_EOL_MSK&t;&t;&t;&t;&t;(0x1)
DECL|macro|ETHER_BLFFRMPTR_ADDRESS_OFST
mdefine_line|#define ETHER_BLFFRMPTR_ADDRESS_OFST&t;&t;&t;(4)
DECL|macro|ETHER_BLFFRMPTR_ADDRESS_MSK
mdefine_line|#define ETHER_BLFFRMPTR_ADDRESS_MSK&t;&t;&t;&t;(0xFFFFFFF0)
DECL|macro|ETHER_RXFRAGSIZE
mdefine_line|#define ETHER_RXFRAGSIZE(base)&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x114))
DECL|macro|ETHER_RXFRAGSIZE_MINFRAG_OFST
mdefine_line|#define&t;ETHER_RXFRAGSIZE_MINFRAG_OFST&t;&t;&t;(2)
DECL|macro|ETHER_RXFRAGSIZE_MINFRAG_MSK
mdefine_line|#define&t;ETHER_RXFRAGSIZE_MINFRAG_MSK&t;&t;&t;(0xFFC)
DECL|macro|ETHER_RXFRAGSIZE_ENPACK_OFST
mdefine_line|#define&t;ETHER_RXFRAGSIZE_ENPACK_OFST&t;&t;&t;(15)
DECL|macro|ETHER_RXFRAGSIZE_ENPACK_MSK
mdefine_line|#define&t;ETHER_RXFRAGSIZE_ENPACK_MSK&t;&t;&t;&t;(0x8000)
DECL|macro|ETHER_INT_EN
mdefine_line|#define ETHER_INT_EN(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x118))
DECL|macro|ETHER_INT_EN_FDAEXEN_OFST
mdefine_line|#define ETHER_INT_EN_FDAEXEN_OFST&t;&t;&t;&t;(0)
DECL|macro|ETHER_INT_EN_FDAEXEN_MSK
mdefine_line|#define ETHER_INT_EN_FDAEXEN_MSK&t;&t;&t;&t;(0x1)
DECL|macro|ETHER_INT_EN_BLEXEN_OFST
mdefine_line|#define ETHER_INT_EN_BLEXEN_OFST&t;&t;&t;&t;(1)
DECL|macro|ETHER_INT_EN_BLEXN_MSK
mdefine_line|#define ETHER_INT_EN_BLEXN_MSK&t;&t;&t;&t;&t;(0x2)
DECL|macro|ETHER_INT_EN_STARGABTEN_OFST
mdefine_line|#define ETHER_INT_EN_STARGABTEN_OFST&t;&t;&t;(2)
DECL|macro|ETHER_INT_EN_STARGABTEN_MSK
mdefine_line|#define ETHER_INT_EN_STARGABTEN_MSK&t;&t;&t;&t;(0x4)
DECL|macro|ETHER_INT_EN_RTARGABTEN_OFST
mdefine_line|#define ETHER_INT_EN_RTARGABTEN_OFST&t;&t;&t;(3)
DECL|macro|ETHER_INT_EN_RTARGABTEN_MSK
mdefine_line|#define ETHER_INT_EN_RTARGABTEN_MSK&t;&t;&t;&t;(0x8)
DECL|macro|ETHER_INT_EN_RMASABTEN_OFST
mdefine_line|#define ETHER_INT_EN_RMASABTEN_OFST&t;&t;&t;&t;(4)
DECL|macro|ETHER_INT_EN_RMASABTEN_MSK
mdefine_line|#define ETHER_INT_EN_RMASABTEN_MSK&t;&t;&t;&t;(0x10)
DECL|macro|ETHER_INT_EN_SSYSERREN_OFST
mdefine_line|#define ETHER_INT_EN_SSYSERREN_OFST&t;&t;&t;&t;(5)
DECL|macro|ETHER_INT_EN_SSYSERREN_MSK
mdefine_line|#define ETHER_INT_EN_SSYSERREN_MSK&t;&t;&t;&t;(0x20)
DECL|macro|ETHER_INT_EN_DPARERREN_OFST
mdefine_line|#define ETHER_INT_EN_DPARERREN_OFST&t;&t;&t;&t;(6)
DECL|macro|ETHER_INT_EN_DPARERREN_MSK
mdefine_line|#define ETHER_INT_EN_DPARERREN_MSK&t;&t;&t;&t;(0x40)
DECL|macro|ETHER_INT_EN_EARNOTEN_OFST
mdefine_line|#define ETHER_INT_EN_EARNOTEN_OFST&t;&t;&t;&t;(7)
DECL|macro|ETHER_INT_EN_EARNOTEN_MSK
mdefine_line|#define ETHER_INT_EN_EARNOTEN_MSK&t;&t;&t;&t;(0x80)
DECL|macro|ETHER_INT_EN_DPARDEN_OFST
mdefine_line|#define ETHER_INT_EN_DPARDEN_OFST&t;&t;&t;&t;(8)
DECL|macro|ETHER_INT_EN_DPARDEN_MSK
mdefine_line|#define ETHER_INT_EN_DPARDEN_MSK&t;&t;&t;&t;(0x100)
DECL|macro|ETHER_INT_EN_DMPARERREN_OFST
mdefine_line|#define ETHER_INT_EN_DMPARERREN_OFST&t;&t;&t;(9)
DECL|macro|ETHER_INT_EN_DMPARERREN_MSK
mdefine_line|#define ETHER_INT_EN_DMPARERREN_MSK&t;&t;&t;&t;(0x200)
DECL|macro|ETHER_INT_EN_TXCTLCMPEN_OFST
mdefine_line|#define ETHER_INT_EN_TXCTLCMPEN_OFST&t;&t;&t;(10)
DECL|macro|ETHER_INT_EN_TXCTLCMPEN_MSK
mdefine_line|#define ETHER_INT_EN_TXCTLCMPEN_MSK&t;&t;&t;&t;(0x400)
DECL|macro|ETHER_INT_EN_NRABTEN_OFST
mdefine_line|#define ETHER_INT_EN_NRABTEN_OFST&t;&t;&t;&t;(11)
DECL|macro|ETHER_INT_EN_NRABTEN_MSK
mdefine_line|#define ETHER_INT_EN_NRABTEN_MSK&t;&t;&t;&t;(0x800)
DECL|macro|ETHER_FDA_BAS
mdefine_line|#define&t;ETHER_FDA_BAS(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x11C))
DECL|macro|ETHER_FDA_BAS_ADDRESS_OFST
mdefine_line|#define ETHER_FDA_BAS_ADDRESS_OFST&t;&t;&t;&t;(4)
DECL|macro|ETHER_FDA_BAS_ADDRESS_MSK
mdefine_line|#define ETHER_FDA_BAS_ADDRESS_MSK&t;&t;&t;&t;(0xFFFFFFF0)
DECL|macro|ETHER_FDA_LIM
mdefine_line|#define ETHER_FDA_LIM(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x120))
DECL|macro|ETHER_FDA_LIM_COUNT_OFST
mdefine_line|#define ETHER_FDA_LIM_COUNT_OFST&t;&t;&t;&t;(4)
DECL|macro|ETHER_FDA_LIM_COUNT_MSK
mdefine_line|#define ETHER_FDA_LIM_COUNT_MSK&t;&t;&t;&t;&t;(0xFFF0)
DECL|macro|ETHER_INT_SRC
mdefine_line|#define ETHER_INT_SRC(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x124))
DECL|macro|ETHER_INT_SRC_INTMACTX_OFST
mdefine_line|#define ETHER_INT_SRC_INTMACTX_OFST&t;&t;&t;&t;(0)
DECL|macro|ETHER_INT_SRC_INTMACTX_MSK
mdefine_line|#define ETHER_INT_SRC_INTMACTX_MSK&t;&t;&t;&t;(0x1)
DECL|macro|ETHER_INT_SRC_INTMACRX_OFST
mdefine_line|#define ETHER_INT_SRC_INTMACRX_OFST&t;&t;&t;&t;(1)
DECL|macro|ETHER_INT_SRC_INTMACRX_MSK
mdefine_line|#define ETHER_INT_SRC_INTMACRX_MSK&t;&t;&t;&t;(0x2)
DECL|macro|ETHER_INT_SRC_INTSBUS_OFST
mdefine_line|#define ETHER_INT_SRC_INTSBUS_OFST&t;&t;&t;&t;(2)
DECL|macro|ETHER_INT_SRC_INTSBUS_MSK
mdefine_line|#define ETHER_INT_SRC_INTSBUS_MSK&t;&t;&t;&t;(0x4)
DECL|macro|ETHER_INT_SRC_INTFDAEX_OFST
mdefine_line|#define ETHER_INT_SRC_INTFDAEX_OFST&t;&t;&t;&t;(3)
DECL|macro|ETHER_INT_SRC_INTFDAEX_MSK
mdefine_line|#define ETHER_INT_SRC_INTFDAEX_MSK&t;&t;&t;&t;(0x8)
DECL|macro|ETHER_INT_SRC_INTBLEX_OFST
mdefine_line|#define ETHER_INT_SRC_INTBLEX_OFST&t;&t;&t;&t;(4)
DECL|macro|ETHER_INT_SRC_INTBLEX_MSK
mdefine_line|#define ETHER_INT_SRC_INTBLEX_MSK&t;&t;&t;&t;(0x10)
DECL|macro|ETHER_INT_SRC_SWINT_OFST
mdefine_line|#define ETHER_INT_SRC_SWINT_OFST&t;&t;&t;&t;(5)
DECL|macro|ETHER_INT_SRC_SWINT_MSK
mdefine_line|#define ETHER_INT_SRC_SWINT_MSK&t;&t;&t;&t;&t;(0x20)
DECL|macro|ETHER_INT_SRC_INTEARNOT_OFST
mdefine_line|#define ETHER_INT_SRC_INTEARNOT_OFST&t;&t;&t;(6)
DECL|macro|ETHER_INT_SRC_INTEARNOT_MSK
mdefine_line|#define ETHER_INT_SRC_INTEARNOT_MSK&t;&t;&t;&t;(0x40)
DECL|macro|ETHER_INT_SRC_DMPARERR_OFST
mdefine_line|#define ETHER_INT_SRC_DMPARERR_OFST&t;&t;&t;&t;(7)
DECL|macro|ETHER_INT_SRC_DMPARERR_MSK
mdefine_line|#define ETHER_INT_SRC_DMPARERR_MSK&t;&t;&t;&t;(0x80)
DECL|macro|ETHER_INT_SRC_INTEXBD_OFST
mdefine_line|#define ETHER_INT_SRC_INTEXBD_OFST&t;&t;&t;&t;(8)
DECL|macro|ETHER_INT_SRC_INTEXBD_MSK
mdefine_line|#define ETHER_INT_SRC_INTEXBD_MSK&t;&t;&t;&t;(0x100)
DECL|macro|ETHER_INT_SRC_INTTXCTLCMP_OFST
mdefine_line|#define ETHER_INT_SRC_INTTXCTLCMP_OFST&t;&t;&t;(9)
DECL|macro|ETHER_INT_SRC_INTTXCTLCMP_MSK
mdefine_line|#define ETHER_INT_SRC_INTTXCTLCMP_MSK&t;&t;&t;(0x200)
DECL|macro|ETHER_INT_SRC_INTNRABT_OFST
mdefine_line|#define ETHER_INT_SRC_INTNRABT_OFST&t;&t;&t;&t;(10)
DECL|macro|ETHER_INT_SRC_INTNRABT_MSK
mdefine_line|#define ETHER_INT_SRC_INTNRABT_MSK&t;&t;&t;&t;(0x400)
DECL|macro|ETHER_INT_SRC_FDAEX_OFST
mdefine_line|#define ETHER_INT_SRC_FDAEX_OFST&t;&t;&t;&t;(11)
DECL|macro|ETHER_INT_SRC_FDAEX_MSK
mdefine_line|#define ETHER_INT_SRC_FDAEX_MSK&t;&t;&t;&t;&t;(0x800)
DECL|macro|ETHER_INT_SRC_BLEX_OFST
mdefine_line|#define ETHER_INT_SRC_BLEX_OFST&t;&t;&t;&t;&t;(12)
DECL|macro|ETHER_INT_SRC_BLEX_MSK
mdefine_line|#define ETHER_INT_SRC_BLEX_MSK&t;&t;&t;&t;&t;(0x1000)
DECL|macro|ETHER_INT_SRC_DMPARERRSTAT_OFST
mdefine_line|#define ETHER_INT_SRC_DMPARERRSTAT_OFST&t;&t;&t;(13)
DECL|macro|ETHER_INT_SRC_DMPARERRSTAT_MSK
mdefine_line|#define ETHER_INT_SRC_DMPARERRSTAT_MSK&t;&t;&t;(0x2000)
DECL|macro|ETHER_INT_SRC_NRABT_OFST
mdefine_line|#define ETHER_INT_SRC_NRABT_OFST&t;&t;&t;&t;(14)
DECL|macro|ETHER_INT_SRC_NRABT_MSK
mdefine_line|#define ETHER_INT_SRC_NRABT_MSK&t;&t;&t;&t;&t;(0x4000)
DECL|macro|ETHER_INT_SRC_INTLINK_OFST
mdefine_line|#define ETHER_INT_SRC_INTLINK_OFST&t;&t;&t;&t;(15)
DECL|macro|ETHER_INT_SRC_INTLINK_MSK
mdefine_line|#define ETHER_INT_SRC_INTLINK_MSK&t;&t;&t;&t;(0x8000)
DECL|macro|ETHER_INT_SRC_INTEXDEFER_OFST
mdefine_line|#define ETHER_INT_SRC_INTEXDEFER_OFST&t;&t;&t;(16)
DECL|macro|ETHER_INT_SRC_INTEXDEFER_MSK
mdefine_line|#define ETHER_INT_SRC_INTEXDEFER_MSK&t;&t;&t;(0x10000)
DECL|macro|ETHER_INT_SRC_INTRMON_OFST
mdefine_line|#define ETHER_INT_SRC_INTRMON_OFST&t;&t;&t;&t;(17)
DECL|macro|ETHER_INT_SRC_INTRMON_MSK
mdefine_line|#define ETHER_INT_SRC_INTRMON_MSK&t;&t;&t;&t;(0x20000)
DECL|macro|ETHER_INT_SRC_IRQ_MSK
mdefine_line|#define ETHER_INT_SRC_IRQ_MSK&t;&t;&t;&t;&t;(0x83FF)
DECL|macro|ETHER_PAUSECNT
mdefine_line|#define ETHER_PAUSECNT(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x40))
DECL|macro|ETHER_PAUSECNT_COUNT_OFST
mdefine_line|#define ETHER_PAUSECNT_COUNT_OFST&t;&t;&t;&t;(0)
DECL|macro|ETHER_PAUSECNT_COUNT_MSK
mdefine_line|#define ETHER_PAUSECNT_COUNT_MSK&t;&t;&t;&t;(0xFFFF)
DECL|macro|ETHER_REMPAUCNT
mdefine_line|#define ETHER_REMPAUCNT(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x44))
DECL|macro|ETHER_REMPAUCNT_COUNT_OFST
mdefine_line|#define ETHER_REMPAUCNT_COUNT_OFST&t;&t;&t;&t;(0)
DECL|macro|ETHER_REMPAUCNT_COUNT_MSK
mdefine_line|#define ETHER_REMPAUCNT_COUNT_MSK&t;&t;&t;&t;(0xFFFF)
DECL|macro|ETHER_TXCONFRMSTAT
mdefine_line|#define ETHER_TXCONFRMSTAT(base)&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x348))
DECL|macro|ETHER_TXCONFRMSTAT_TS_STAT_VALUE_OFST
mdefine_line|#define ETHER_TXCONFRMSTAT_TS_STAT_VALUE_OFST&t;(0)
DECL|macro|ETHER_TXCONFRMSTAT_TS_STAT_VALUE_MSK
mdefine_line|#define ETHER_TXCONFRMSTAT_TS_STAT_VALUE_MSK&t;(0x3FFFFF)
DECL|macro|ETHER_MAC_CTL
mdefine_line|#define ETHER_MAC_CTL(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0))
DECL|macro|ETHER_MAC_CTL_HALTREQ_OFST
mdefine_line|#define ETHER_MAC_CTL_HALTREQ_OFST&t;&t;&t;&t;(0)
DECL|macro|ETHER_MAC_CTL_HALTREQ_MSK
mdefine_line|#define ETHER_MAC_CTL_HALTREQ_MSK&t;&t;&t;&t;(0x1)
DECL|macro|ETHER_MAC_CTL_HALTIMM_OFST
mdefine_line|#define ETHER_MAC_CTL_HALTIMM_OFST&t;&t;&t;&t;(1)
DECL|macro|ETHER_MAC_CTL_HALTIMM_MSK
mdefine_line|#define ETHER_MAC_CTL_HALTIMM_MSK&t;&t;&t;&t;(0x2)
DECL|macro|ETHER_MAC_CTL_RESET_OFST
mdefine_line|#define ETHER_MAC_CTL_RESET_OFST&t;&t;&t;&t;(2)
DECL|macro|ETHER_MAC_CTL_RESET_MSK
mdefine_line|#define ETHER_MAC_CTL_RESET_MSK&t;&t;&t;&t;&t;(0x4)
DECL|macro|ETHER_MAC_CTL_FULLDUP_OFST
mdefine_line|#define ETHER_MAC_CTL_FULLDUP_OFST&t;&t;&t;&t;(3)
DECL|macro|ETHER_MAC_CTL_FULLDUP_MSK
mdefine_line|#define ETHER_MAC_CTL_FULLDUP_MSK&t;&t;&t;&t;(0x8)
DECL|macro|ETHER_MAC_CTL_MACLOOP_OFST
mdefine_line|#define ETHER_MAC_CTL_MACLOOP_OFST&t;&t;&t;&t;(4)
DECL|macro|ETHER_MAC_CTL_MACLOOP_MSK
mdefine_line|#define ETHER_MAC_CTL_MACLOOP_MSK&t;&t;&t;&t;(0x10)
DECL|macro|ETHER_MAC_CTL_CONN_OFST
mdefine_line|#define ETHER_MAC_CTL_CONN_OFST&t;&t;&t;&t;&t;(5)
DECL|macro|ETHER_MAC_CTL_CONN_MSK
mdefine_line|#define ETHER_MAC_CTL_CONN_MSK&t;&t;&t;&t;&t;(0x60)
DECL|macro|ETHER_MAC_CTL_LOOP10_OFST
mdefine_line|#define ETHER_MAC_CTL_LOOP10_OFST&t;&t;&t;&t;(7)
DECL|macro|ETHER_MAC_CTL_LOOP10_MSK
mdefine_line|#define ETHER_MAC_CTL_LOOP10_MSK&t;&t;&t;&t;(0x80)
DECL|macro|ETHER_MAC_CTL_LNKCHG_OFST
mdefine_line|#define ETHER_MAC_CTL_LNKCHG_OFST&t;&t;&t;&t;(8)
DECL|macro|ETHER_MAC_CTL_LNKCHG_MSK
mdefine_line|#define ETHER_MAC_CTL_LNKCHG_MSK&t;&t;&t;&t;(0x100)
DECL|macro|ETHER_MAC_CTL_MISSROLL_OFST
mdefine_line|#define ETHER_MAC_CTL_MISSROLL_OFST&t;&t;&t;&t;(10)
DECL|macro|ETHER_MAC_CTL_MISSROLL_MSK
mdefine_line|#define ETHER_MAC_CTL_MISSROLL_MSK&t;&t;&t;&t;(0x400)
DECL|macro|ETHER_MAC_CTL_ENMISSROLL_OFST
mdefine_line|#define ETHER_MAC_CTL_ENMISSROLL_OFST&t;&t;&t;(13)
DECL|macro|ETHER_MAC_CTL_ENMISSROLL_MSK
mdefine_line|#define ETHER_MAC_CTL_ENMISSROLL_MSK&t;&t;&t;(0x2000)
DECL|macro|ETHER_MAC_CTL_LINK10_OFST
mdefine_line|#define ETHER_MAC_CTL_LINK10_OFST&t;&t;&t;&t;(15)
DECL|macro|ETHER_MAC_CTL_LINK10_MSK
mdefine_line|#define ETHER_MAC_CTL_LINK10_MSK&t;&t;&t;&t;(0x8000)
DECL|macro|ETHER_ARC_CTL
mdefine_line|#define ETHER_ARC_CTL(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x4))
DECL|macro|ETHER_ARC_CTL_STATIONACC_OFST
mdefine_line|#define&t;ETHER_ARC_CTL_STATIONACC_OFST&t;&t;&t;(0)
DECL|macro|ETHER_ARC_CTL_STATIONACC_MSK
mdefine_line|#define&t;ETHER_ARC_CTL_STATIONACC_MSK&t;&t;&t;(0x1)
DECL|macro|ETHER_ARC_CTL_GROUPACC_OFST
mdefine_line|#define&t;ETHER_ARC_CTL_GROUPACC_OFST&t;&t;&t;&t;(1)
DECL|macro|ETHER_ARC_CTL_GROUPACC_MSK
mdefine_line|#define&t;ETHER_ARC_CTL_GROUPACC_MSK&t;&t;&t;&t;(0x2)
DECL|macro|ETHER_ARC_CTL_BROADACC_OFST
mdefine_line|#define&t;ETHER_ARC_CTL_BROADACC_OFST&t;&t;&t;&t;(2)
DECL|macro|ETHER_ARC_CTL_BROADACC_MSK
mdefine_line|#define&t;ETHER_ARC_CTL_BROADACC_MSK&t;&t;&t;&t;(0x4)
DECL|macro|ETHER_ARC_CTL_NEGARC_OFST
mdefine_line|#define&t;ETHER_ARC_CTL_NEGARC_OFST&t;&t;&t;&t;(3)
DECL|macro|ETHER_ARC_CTL_NEGARC_MSK
mdefine_line|#define&t;ETHER_ARC_CTL_NEGARC_MSK&t;&t;&t;&t;(0x8)
DECL|macro|ETHER_ARC_CTL_COMPEN_OFST
mdefine_line|#define&t;ETHER_ARC_CTL_COMPEN_OFST&t;&t;&t;&t;(4)
DECL|macro|ETHER_ARC_CTL_COMPEN_MSK
mdefine_line|#define&t;ETHER_ARC_CTL_COMPEN_MSK&t;&t;&t;&t;(0x10)
DECL|macro|ETHER_TX_CTL
mdefine_line|#define ETHER_TX_CTL(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x8))
DECL|macro|ETHER_TX_CTL_TXEN_OFST
mdefine_line|#define ETHER_TX_CTL_TXEN_OFST&t;&t;&t;&t;&t;(0)
DECL|macro|ETHER_TX_CTL_TXEN_MSK
mdefine_line|#define ETHER_TX_CTL_TXEN_MSK&t;&t;&t;&t;&t;(0x1)
DECL|macro|ETHER_TX_CTL_TXHALT_OFST
mdefine_line|#define ETHER_TX_CTL_TXHALT_OFST&t;&t;&t;&t;(1)
DECL|macro|ETHER_TX_CTL_TXHALT_MSK
mdefine_line|#define ETHER_TX_CTL_TXHALT_MSK&t;&t;&t;&t;&t;(0x2)
DECL|macro|ETHER_TX_CTL_NOPAD_OFST
mdefine_line|#define ETHER_TX_CTL_NOPAD_OFST&t;&t;&t;&t;&t;(2)
DECL|macro|ETHER_TX_CTL_NOPAD_MSK
mdefine_line|#define ETHER_TX_CTL_NOPAD_MSK&t;&t;&t;&t;&t;(0x4)
DECL|macro|ETHER_TX_CTL_NOCRC_OFST
mdefine_line|#define ETHER_TX_CTL_NOCRC_OFST&t;&t;&t;&t;&t;(3)
DECL|macro|ETHER_TX_CTL_NOCRC_MSK
mdefine_line|#define ETHER_TX_CTL_NOCRC_MSK&t;&t;&t;&t;&t;(0x8)
DECL|macro|ETHER_TX_CTL_FBACK_OFST
mdefine_line|#define ETHER_TX_CTL_FBACK_OFST&t;&t;&t;&t;&t;(4)
DECL|macro|ETHER_TX_CTL_FBACK_MSK
mdefine_line|#define ETHER_TX_CTL_FBACK_MSK&t;&t;&t;&t;&t;(0x10)
DECL|macro|ETHER_TX_CTL_NOEXDEF_OFST
mdefine_line|#define ETHER_TX_CTL_NOEXDEF_OFST&t;&t;&t;&t;(5)
DECL|macro|ETHER_TX_CTL_NOEXDEF_MSK
mdefine_line|#define ETHER_TX_CTL_NOEXDEF_MSK&t;&t;&t;&t;(0x20)
DECL|macro|ETHER_TX_CTL_SDPAUSE_OFST
mdefine_line|#define ETHER_TX_CTL_SDPAUSE_OFST&t;&t;&t;&t;(6)
DECL|macro|ETHER_TX_CTL_SDPAUSE_MSK
mdefine_line|#define ETHER_TX_CTL_SDPAUSE_MSK&t;&t;&t;&t;(0x40)
DECL|macro|ETHER_TX_CTL_MII10_OFST
mdefine_line|#define ETHER_TX_CTL_MII10_OFST&t;&t;&t;&t;&t;(7)
DECL|macro|ETHER_TX_CTL_MII10_MSK
mdefine_line|#define ETHER_TX_CTL_MII10_MSK&t;&t;&t;&t;&t;(0x80)
DECL|macro|ETHER_TX_CTL_ENUNDER_OFST
mdefine_line|#define ETHER_TX_CTL_ENUNDER_OFST&t;&t;&t;&t;(8)
DECL|macro|ETHER_TX_CTL_ENUNDER_MSK
mdefine_line|#define ETHER_TX_CTL_ENUNDER_MSK&t;&t;&t;&t;(0x100)
DECL|macro|ETHER_TX_CTL_ENEXDEFER_OFST
mdefine_line|#define ETHER_TX_CTL_ENEXDEFER_OFST&t;&t;&t;&t;(9)
DECL|macro|ETHER_TX_CTL_ENEXDEFER_MSK
mdefine_line|#define ETHER_TX_CTL_ENEXDEFER_MSK&t;&t;&t;&t;(0x200)
DECL|macro|ETHER_TX_CTL_ENLCARR_OFST
mdefine_line|#define ETHER_TX_CTL_ENLCARR_OFST&t;&t;&t;&t;(10)
DECL|macro|ETHER_TX_CTL_ENLCARR_MSK
mdefine_line|#define ETHER_TX_CTL_ENLCARR_MSK&t;&t;&t;&t;(0x400)
DECL|macro|ETHER_TX_CTL_ENEXCOLL_OFST
mdefine_line|#define ETHER_TX_CTL_ENEXCOLL_OFST&t;&t;&t;&t;(11)
DECL|macro|ETHER_TX_CTL_ENEXCOLL_MSK
mdefine_line|#define ETHER_TX_CTL_ENEXCOLL_MSK&t;&t;&t;&t;(0x800)
DECL|macro|ETHER_TX_CTL_ENLATECOLL_OFST
mdefine_line|#define ETHER_TX_CTL_ENLATECOLL_OFST&t;&t;&t;&t;(12)
DECL|macro|ETHER_TX_CTL_ENLATECOLL_MSK
mdefine_line|#define ETHER_TX_CTL_ENLATECOLL_MSK&t;&t;&t;&t;(0x1000)
DECL|macro|ETHER_TX_CTL_ENTXPAR_OFST
mdefine_line|#define ETHER_TX_CTL_ENTXPAR_OFST&t;&t;&t;&t;(13)
DECL|macro|ETHER_TX_CTL_ENTXPAR_MSK
mdefine_line|#define ETHER_TX_CTL_ENTXPAR_MSK&t;&t;&t;&t;(0x2000)
DECL|macro|ETHER_TX_CTL_ENCOMP_OFST
mdefine_line|#define ETHER_TX_CTL_ENCOMP_OFST&t;&t;&t;&t;(14)
DECL|macro|ETHER_TX_CTL_ENCOMP_MSK
mdefine_line|#define ETHER_TX_CTL_ENCOMP_MSK&t;&t;&t;&t;&t;(0x4000)
DECL|macro|ETHER_TX_STAT
mdefine_line|#define ETHER_TX_STAT(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0xc))
DECL|macro|ETHER_TX_STAT_TXCOLL_OFST
mdefine_line|#define ETHER_TX_STAT_TXCOLL_OFST&t;&t;&t;&t;(0)
DECL|macro|ETHER_TX_STAT_TXCOLL_MSK
mdefine_line|#define ETHER_TX_STAT_TXCOLL_MSK&t;&t;&t;&t;(0xF)
DECL|macro|ETHER_TX_STAT_EXCOLL_OFST
mdefine_line|#define ETHER_TX_STAT_EXCOLL_OFST&t;&t;&t;&t;(4)
DECL|macro|ETHER_TX_STAT_EXCOLL_MSK
mdefine_line|#define ETHER_TX_STAT_EXCOLL_MSK&t;&t;&t;&t;(0x10)
DECL|macro|ETHER_TX_STAT_TXDEFER_OFST
mdefine_line|#define ETHER_TX_STAT_TXDEFER_OFST&t;&t;&t;&t;(5)
DECL|macro|ETHER_TX_STAT_TXDEFER_MSK
mdefine_line|#define ETHER_TX_STAT_TXDEFER_MSK&t;&t;&t;&t;(0x20)
DECL|macro|ETHER_TX_STAT_PAUSED_OFST
mdefine_line|#define ETHER_TX_STAT_PAUSED_OFST&t;&t;&t;&t;(6)
DECL|macro|ETHER_TX_STAT_PAUSED_MSK
mdefine_line|#define ETHER_TX_STAT_PAUSED_MSK&t;&t;&t;&t;(0x40)
DECL|macro|ETHER_TX_STAT_INTTX_OFST
mdefine_line|#define ETHER_TX_STAT_INTTX_OFST&t;&t;&t;&t;(7)
DECL|macro|ETHER_TX_STAT_INTTX_MSK
mdefine_line|#define ETHER_TX_STAT_INTTX_MSK&t;&t;&t;&t;&t;(0x80)
DECL|macro|ETHER_TX_STAT_UNDER_OFST
mdefine_line|#define ETHER_TX_STAT_UNDER_OFST&t;&t;&t;&t;(8)
DECL|macro|ETHER_TX_STAT_UNDER_MSK
mdefine_line|#define ETHER_TX_STAT_UNDER_MSK&t;&t;&t;&t;&t;(0x100)
DECL|macro|ETHER_TX_STAT_EXDEFER_OFST
mdefine_line|#define ETHER_TX_STAT_EXDEFER_OFST&t;&t;&t;&t;(9)
DECL|macro|ETHER_TX_STAT_EXDEFER_MSK
mdefine_line|#define ETHER_TX_STAT_EXDEFER_MSK&t;&t;&t;&t;(0x200)
DECL|macro|ETHER_TX_STAT_LCARR_OFST
mdefine_line|#define ETHER_TX_STAT_LCARR_OFST&t;&t;&t;&t;(10)
DECL|macro|ETHER_TX_STAT_LCARR_MSK
mdefine_line|#define ETHER_TX_STAT_LCARR_MSK&t;&t;&t;&t;&t;(0x400)
DECL|macro|ETHER_TX_STAT_TX10STAT_OFST
mdefine_line|#define ETHER_TX_STAT_TX10STAT_OFST&t;&t;&t;&t;(11)
DECL|macro|ETHER_TX_STAT_TX10STAT_MSK
mdefine_line|#define ETHER_TX_STAT_TX10STAT_MSK&t;&t;&t;&t;(0x800)
DECL|macro|ETHER_TX_STAT_LATECOLL_OFST
mdefine_line|#define ETHER_TX_STAT_LATECOLL_OFST&t;&t;&t;&t;(12)
DECL|macro|ETHER_TX_STAT_LATECOLL_MSK
mdefine_line|#define ETHER_TX_STAT_LATECOLL_MSK&t;&t;&t;&t;(0x1000)
DECL|macro|ETHER_TX_STAT_TXPAR_OFST
mdefine_line|#define ETHER_TX_STAT_TXPAR_OFST&t;&t;&t;&t;(13)
DECL|macro|ETHER_TX_STAT_TXPAR_MSK
mdefine_line|#define ETHER_TX_STAT_TXPAR_MSK&t;&t;&t;&t;&t;(0x2000)
DECL|macro|ETHER_TX_STAT_COMP_OFST
mdefine_line|#define ETHER_TX_STAT_COMP_OFST&t;&t;&t;&t;&t;(14)
DECL|macro|ETHER_TX_STAT_COMP_MSK
mdefine_line|#define ETHER_TX_STAT_COMP_MSK&t;&t;&t;&t;&t;(0x4000)
DECL|macro|ETHER_TX_STAT_TXHALTED_OFST
mdefine_line|#define ETHER_TX_STAT_TXHALTED_OFST&t;&t;&t;&t;(15)
DECL|macro|ETHER_TX_STAT_TXHALTED_MSK
mdefine_line|#define ETHER_TX_STAT_TXHALTED_MSK&t;&t;&t;&t;(0x8000)
DECL|macro|ETHER_TX_STAT_SQERR_OFST
mdefine_line|#define ETHER_TX_STAT_SQERR_OFST&t;&t;&t;&t;(16)
DECL|macro|ETHER_TX_STAT_SQERR_MSK
mdefine_line|#define ETHER_TX_STAT_SQERR_MSK&t;&t;&t;&t;&t;(0x10000)
DECL|macro|ETHER_TX_STAT_TXMCAST_OFST
mdefine_line|#define ETHER_TX_STAT_TXMCAST_OFST&t;&t;&t;&t;(17)
DECL|macro|ETHER_TX_STAT_TXMCAST_MSK
mdefine_line|#define ETHER_TX_STAT_TXMCAST_MSK&t;&t;&t;&t;(0x20000)
DECL|macro|ETHER_TX_STAT_TXBCAST_OFST
mdefine_line|#define ETHER_TX_STAT_TXBCAST_OFST&t;&t;&t;&t;(18)
DECL|macro|ETHER_TX_STAT_TXBCAST_MSK
mdefine_line|#define ETHER_TX_STAT_TXBCAST_MSK&t;&t;&t;&t;(0x40000)
DECL|macro|ETHER_TX_STAT_VLAN_OFST
mdefine_line|#define ETHER_TX_STAT_VLAN_OFST&t;&t;&t;&t;&t;(19)
DECL|macro|ETHER_TX_STAT_VLAN_MSK
mdefine_line|#define ETHER_TX_STAT_VLAN_MSK&t;&t;&t;&t;&t;(0x80000)
DECL|macro|ETHER_TX_STAT_MACC_OFST
mdefine_line|#define ETHER_TX_STAT_MACC_OFST&t;&t;&t;&t;&t;(20)
DECL|macro|ETHER_TX_STAT_MACC_MSK
mdefine_line|#define ETHER_TX_STAT_MACC_MSK&t;&t;&t;&t;&t;(0x100000)
DECL|macro|ETHER_TX_STAT_TXPAUSE_OFST
mdefine_line|#define ETHER_TX_STAT_TXPAUSE_OFST&t;&t;&t;&t;(21)
DECL|macro|ETHER_TX_STAT_TXPAUSE_MSK
mdefine_line|#define ETHER_TX_STAT_TXPAUSE_MSK&t;&t;&t;&t;(0x200000)
DECL|macro|ETHER_RX_CTL
mdefine_line|#define ETHER_RX_CTL(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x10))
DECL|macro|ETHER_RX_CTL_RXEN_OFST
mdefine_line|#define ETHER_RX_CTL_RXEN_OFST&t;&t;&t;&t;&t;(0)
DECL|macro|ETHER_RX_CTL_RXEN_MSK
mdefine_line|#define ETHER_RX_CTL_RXEN_MSK&t;&t;&t;&t;&t;(0x1)
DECL|macro|ETHER_RX_CTL_RXHALT_OFST
mdefine_line|#define ETHER_RX_CTL_RXHALT_OFST&t;&t;&t;&t;(1)
DECL|macro|ETHER_RX_CTL_RXHALT_MSK
mdefine_line|#define ETHER_RX_CTL_RXHALT_MSK&t;&t;&t;&t;&t;(0x2)
DECL|macro|ETHER_RX_CTL_LONGEN_OFST
mdefine_line|#define ETHER_RX_CTL_LONGEN_OFST&t;&t;&t;&t;(2)
DECL|macro|ETHER_RX_CTL_LONGEN_MSK
mdefine_line|#define ETHER_RX_CTL_LONGEN_MSK&t;&t;&t;&t;&t;(0x4)
DECL|macro|ETHER_RX_CTL_SHORTEN_OFST
mdefine_line|#define ETHER_RX_CTL_SHORTEN_OFST&t;&t;&t;&t;(3)
DECL|macro|ETHER_RX_CTL_SHORTEN_MSK
mdefine_line|#define ETHER_RX_CTL_SHORTEN_MSK&t;&t;&t;&t;(0x8)
DECL|macro|ETHER_RX_CTL_STRIPCRC_OFST
mdefine_line|#define ETHER_RX_CTL_STRIPCRC_OFST&t;&t;&t;&t;(4)
DECL|macro|ETHER_RX_CTL_STRIPCRC_MSK
mdefine_line|#define ETHER_RX_CTL_STRIPCRC_MSK&t;&t;&t;&t;(0x10)
DECL|macro|ETHER_RX_CTL_PASSCTL_OFST
mdefine_line|#define ETHER_RX_CTL_PASSCTL_OFST&t;&t;&t;&t;(5)
DECL|macro|ETHER_RX_CTL_PASSCTL_MSK
mdefine_line|#define ETHER_RX_CTL_PASSCTL_MSK&t;&t;&t;&t;(0x20)
DECL|macro|ETHER_RX_CTL_IGNORECRC_OFST
mdefine_line|#define ETHER_RX_CTL_IGNORECRC_OFST&t;&t;&t;&t;(6)
DECL|macro|ETHER_RX_CTL_IGNORECRC_MSK
mdefine_line|#define ETHER_RX_CTL_IGNORECRC_MSK&t;&t;&t;&t;(0x40)
DECL|macro|ETHER_RX_CTL_ENALIGN_OFST
mdefine_line|#define ETHER_RX_CTL_ENALIGN_OFST&t;&t;&t;&t;(8)
DECL|macro|ETHER_RX_CTL_ENALIGN_MSK
mdefine_line|#define ETHER_RX_CTL_ENALIGN_MSK&t;&t;&t;&t;(0x100)
DECL|macro|ETHER_RX_CTL_ENCRCERR_OFST
mdefine_line|#define ETHER_RX_CTL_ENCRCERR_OFST&t;&t;&t;&t;(9)
DECL|macro|ETHER_RX_CTL_ENCRCERR_MSK
mdefine_line|#define ETHER_RX_CTL_ENCRCERR_MSK&t;&t;&t;&t;(0x200)
DECL|macro|ETHER_RX_CTL_ENOVER_OFST
mdefine_line|#define ETHER_RX_CTL_ENOVER_OFST&t;&t;&t;&t;(10)
DECL|macro|ETHER_RX_CTL_ENOVER_MSK
mdefine_line|#define ETHER_RX_CTL_ENOVER_MSK&t;&t;&t;&t;&t;(0x400)
DECL|macro|ETHER_RX_CTL_ENLONGERR_OFST
mdefine_line|#define ETHER_RX_CTL_ENLONGERR_OFST&t;&t;&t;&t;(11)
DECL|macro|ETHER_RX_CTL_ENLONGERR_MSK
mdefine_line|#define ETHER_RX_CTL_ENLONGERR_MSK&t;&t;&t;&t;(0x800)
DECL|macro|ETHER_RX_CTL_ENRXPAR_OFST
mdefine_line|#define ETHER_RX_CTL_ENRXPAR_OFST&t;&t;&t;&t;(13)
DECL|macro|ETHER_RX_CTL_ENRXPAR_MSK
mdefine_line|#define ETHER_RX_CTL_ENRXPAR_MSK&t;&t;&t;&t;(0x2000)
DECL|macro|ETHER_RX_CTL_ENGOOD_OFST
mdefine_line|#define ETHER_RX_CTL_ENGOOD_OFST&t;&t;&t;&t;(14)
DECL|macro|ETHER_RX_CTL_ENGOOD_MSK
mdefine_line|#define ETHER_RX_CTL_ENGOOD_MSK&t;&t;&t;&t;&t;(0x4000)
DECL|macro|ETHER_RX_STAT
mdefine_line|#define ETHER_RX_STAT(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x14))
DECL|macro|ETHER_RX_STAT_LENERR_OFST
mdefine_line|#define ETHER_RX_STAT_LENERR_OFST&t;&t;&t;&t;(4)
DECL|macro|ETHER_RX_STAT_LENERR_MSK
mdefine_line|#define ETHER_RX_STAT_LENERR_MSK&t;&t;&t;&t;(0x10)
DECL|macro|ETHER_RX_STAT_CTLRECD_OFST
mdefine_line|#define ETHER_RX_STAT_CTLRECD_OFST&t;&t;&t;&t;(5)
DECL|macro|ETHER_RX_STAT_CTLRECD_MSK
mdefine_line|#define ETHER_RX_STAT_CTLRECD_MSK&t;&t;&t;&t;(0x20)
DECL|macro|ETHER_RX_STAT_INTRX_OFST
mdefine_line|#define ETHER_RX_STAT_INTRX_OFST&t;&t;&t;&t;(6)
DECL|macro|ETHER_RX_STAT_INTRX_MSK
mdefine_line|#define ETHER_RX_STAT_INTRX_MSK&t;&t;&t;&t;&t;(0x40)
DECL|macro|ETHER_RX_STAT_RX10STAT_OFST
mdefine_line|#define ETHER_RX_STAT_RX10STAT_OFST&t;&t;&t;&t;(7)
DECL|macro|ETHER_RX_STAT_RX10STAT_MSK
mdefine_line|#define ETHER_RX_STAT_RX10STAT_MSK&t;&t;&t;&t;(0x80)
DECL|macro|ETHER_RX_STAT_ALIGNERR_OFST
mdefine_line|#define ETHER_RX_STAT_ALIGNERR_OFST&t;&t;&t;&t;(8)
DECL|macro|ETHER_RX_STAT_ALIGNERR_MSK
mdefine_line|#define ETHER_RX_STAT_ALIGNERR_MSK&t;&t;&t;&t;(0x100)
DECL|macro|ETHER_RX_STAT_CRCERR_OFST
mdefine_line|#define ETHER_RX_STAT_CRCERR_OFST&t;&t;&t;&t;(9)
DECL|macro|ETHER_RX_STAT_CRCERR_MSK
mdefine_line|#define ETHER_RX_STAT_CRCERR_MSK&t;&t;&t;&t;(0x200)
DECL|macro|ETHER_RX_STAT_OVERFLOW_OFST
mdefine_line|#define ETHER_RX_STAT_OVERFLOW_OFST&t;&t;&t;&t;(10)
DECL|macro|ETHER_RX_STAT_OVERFLOW_MSK
mdefine_line|#define ETHER_RX_STAT_OVERFLOW_MSK&t;&t;&t;&t;(0x400)
DECL|macro|ETHER_RX_STAT_LONGERR_OFST
mdefine_line|#define ETHER_RX_STAT_LONGERR_OFST&t;&t;&t;&t;(11)
DECL|macro|ETHER_RX_STAT_LONGERR_MSK
mdefine_line|#define ETHER_RX_STAT_LONGERR_MSK&t;&t;&t;&t;(0x800)
DECL|macro|ETHER_RX_STAT_RXPAR_OFST
mdefine_line|#define ETHER_RX_STAT_RXPAR_OFST&t;&t;&t;&t;(13)
DECL|macro|ETHER_RX_STAT_RXPAR_MSK
mdefine_line|#define ETHER_RX_STAT_RXPAR_MSK&t;&t;&t;&t;&t;(0x2000)
DECL|macro|ETHER_RX_STAT_GOOD_OFST
mdefine_line|#define ETHER_RX_STAT_GOOD_OFST&t;&t;&t;&t;&t;(14)
DECL|macro|ETHER_RX_STAT_GOOD_MSK
mdefine_line|#define ETHER_RX_STAT_GOOD_MSK&t;&t;&t;&t;&t;(0x4000)
DECL|macro|ETHER_RX_STAT_RXHALTED_OFST
mdefine_line|#define ETHER_RX_STAT_RXHALTED_OFST&t;&t;&t;&t;(15)
DECL|macro|ETHER_RX_STAT_RXHALTED_MSK
mdefine_line|#define ETHER_RX_STAT_RXHALTED_MSK&t;&t;&t;&t;(0x8000)
DECL|macro|ETHER_RX_STAT_RXMCAST_OFST
mdefine_line|#define ETHER_RX_STAT_RXMCAST_OFST&t;&t;&t;&t;(17)
DECL|macro|ETHER_RX_STAT_RXMCAST_MSK
mdefine_line|#define ETHER_RX_STAT_RXMCAST_MSK&t;&t;&t;&t;(0x10000)
DECL|macro|ETHER_RX_STAT_RXBCAST_OFST
mdefine_line|#define ETHER_RX_STAT_RXBCAST_OFST&t;&t;&t;&t;(18)
DECL|macro|ETHER_RX_STAT_RXBCAST_MSK
mdefine_line|#define ETHER_RX_STAT_RXBCAST_MSK&t;&t;&t;&t;(0x20000)
DECL|macro|ETHER_RX_STAT_RXVLAN_OFST
mdefine_line|#define ETHER_RX_STAT_RXVLAN_OFST&t;&t;&t;&t;(19)
DECL|macro|ETHER_RX_STAT_RXVLAN_MSK
mdefine_line|#define ETHER_RX_STAT_RXVLAN_MSK&t;&t;&t;&t;(0x40000)
DECL|macro|ETHER_RX_STAT_RXPAUSE_OFST
mdefine_line|#define ETHER_RX_STAT_RXPAUSE_OFST&t;&t;&t;&t;(20)
DECL|macro|ETHER_RX_STAT_RXPAUSE_MSK
mdefine_line|#define ETHER_RX_STAT_RXPAUSE_MSK&t;&t;&t;&t;(0x80000)
DECL|macro|ETHER_RX_STAT_ARCSTATUS_OFST
mdefine_line|#define ETHER_RX_STAT_ARCSTATUS_OFST&t;&t;&t;&t;(21)
DECL|macro|ETHER_RX_STAT_ARCSTATUS_MSK
mdefine_line|#define ETHER_RX_STAT_ARCSTATUS_MSK&t;&t;&t;&t;(0xF00000)
DECL|macro|ETHER_RX_STAT_ARCENT_OFST
mdefine_line|#define ETHER_RX_STAT_ARCENT_OFST&t;&t;&t;&t;(25)
DECL|macro|ETHER_RX_STAT_ARCENT_MSK
mdefine_line|#define ETHER_RX_STAT_ARCENT_MSK&t;&t;&t;&t;(0x1F000000)
DECL|macro|ETHER_MD_DATA
mdefine_line|#define ETHER_MD_DATA(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x18))
DECL|macro|ETHER_MD_CA
mdefine_line|#define ETHER_MD_CA(base)&t;&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x1c))
DECL|macro|ETHER_MD_CA_ADDR_OFST
mdefine_line|#define ETHER_MD_CA_ADDR_OFST&t;&t;&t;&t;&t;(0)
DECL|macro|ETHER_MD_CA_ADDR_MSK
mdefine_line|#define ETHER_MD_CA_ADDR_MSK&t;&t;&t;&t;&t;(0x1F)
DECL|macro|ETHER_MD_CA_PHY_OFST
mdefine_line|#define ETHER_MD_CA_PHY_OFST&t;&t;&t;&t;&t;(5)
DECL|macro|ETHER_MD_CA_PHY_MSK
mdefine_line|#define ETHER_MD_CA_PHY_MSK&t;&t;&t;&t;&t;(0x3E0)
DECL|macro|ETHER_MD_CA_WR_OFST
mdefine_line|#define ETHER_MD_CA_WR_OFST&t;&t;&t;&t;&t;(10)
DECL|macro|ETHER_MD_CA_WR_MSK
mdefine_line|#define ETHER_MD_CA_WR_MSK&t;&t;&t;&t;&t;(0x400)
DECL|macro|ETHER_MD_CA_BUSY_OFST
mdefine_line|#define ETHER_MD_CA_BUSY_OFST&t;&t;&t;&t;&t;(11)
DECL|macro|ETHER_MD_CA_BUSY_MSK
mdefine_line|#define ETHER_MD_CA_BUSY_MSK&t;&t;&t;&t;&t;(0x800)
DECL|macro|ETHER_MD_CA_PRESUPP_OFST
mdefine_line|#define ETHER_MD_CA_PRESUPP_OFST&t;&t;&t;&t;(12)
DECL|macro|ETHER_MD_CA_PRESUPP_MSK
mdefine_line|#define ETHER_MD_CA_PRESUPP_MSK&t;&t;&t;&t;&t;(0x1000)
DECL|macro|ETHER_ARC_ADR
mdefine_line|#define ETHER_ARC_ADR(base)&t;      (ETHER00_TYPE (base + 0x160))
DECL|macro|ETHER_ARC_ADR_ARC_LOC_OFST
mdefine_line|#define ETHER_ARC_ADR_ARC_LOC_OFST&t;&t;&t;&t;(2)
DECL|macro|ETHER_ARC_ADR_ARC_LOC_MSK
mdefine_line|#define ETHER_ARC_ADR_ARC_LOC_MSK&t;&t;&t;&t;(0xFFC)
DECL|macro|ETHER_ARC_DATA
mdefine_line|#define ETHER_ARC_DATA(base)  (ETHER00_TYPE (base + 0x364))
DECL|macro|ETHER_ARC_ENA
mdefine_line|#define ETHER_ARC_ENA(base)   (ETHER00_TYPE (base + 0x28))
DECL|macro|ETHER_ARC_ENA_MSK
mdefine_line|#define ETHER_ARC_ENA_MSK&t;&t;&t;&t;&t;(0x1FFFFF)
DECL|macro|ETHER_PROM_CTL
mdefine_line|#define ETHER_PROM_CTL(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x2c))
DECL|macro|ETHER_PROM_CTL_PROM_ADDR_OFST
mdefine_line|#define ETHER_PROM_CTL_PROM_ADDR_OFST&t;&t;&t;(0)
DECL|macro|ETHER_PROM_CTL_PROM_ADDR_MSK
mdefine_line|#define ETHER_PROM_CTL_PROM_ADDR_MSK&t;&t;&t;(0x3F)
DECL|macro|ETHER_PROM_CTL_OPCODE_OFST
mdefine_line|#define ETHER_PROM_CTL_OPCODE_OFST&t;&t;&t;&t;(13)
DECL|macro|ETHER_PROM_CTL_OPCODE_MSK
mdefine_line|#define ETHER_PROM_CTL_OPCODE_MSK&t;&t;&t;&t;(0x6000)
DECL|macro|ETHER_PROM_CTL_OPCODE_READ_MSK
mdefine_line|#define ETHER_PROM_CTL_OPCODE_READ_MSK&t;&t;&t;(0x4000)
DECL|macro|ETHER_PROM_CTL_OPCODE_WRITE_MSK
mdefine_line|#define ETHER_PROM_CTL_OPCODE_WRITE_MSK&t;&t;&t;(0x2000)
DECL|macro|ETHER_PROM_CTL_OPCODE_ERASE_MSK
mdefine_line|#define ETHER_PROM_CTL_OPCODE_ERASE_MSK&t;&t;&t;(0x6000)
DECL|macro|ETHER_PROM_CTL_ENABLE_MSK
mdefine_line|#define ETHER_PROM_CTL_ENABLE_MSK&t;&t;&t;&t;(0x0030)
DECL|macro|ETHER_PROM_CTL_DISABLE_MSK
mdefine_line|#define ETHER_PROM_CTL_DISABLE_MSK&t;&t;&t;&t;(0x0000)
DECL|macro|ETHER_PROM_CTL_BUSY_OFST
mdefine_line|#define ETHER_PROM_CTL_BUSY_OFST&t;&t;&t;&t;(15)
DECL|macro|ETHER_PROM_CTL_BUSY_MSK
mdefine_line|#define ETHER_PROM_CTL_BUSY_MSK&t;&t;&t;&t;&t;(0x8000)
DECL|macro|ETHER_PROM_DATA
mdefine_line|#define ETHER_PROM_DATA(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x30))
DECL|macro|ETHER_MISS_CNT
mdefine_line|#define ETHER_MISS_CNT(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x3c))
DECL|macro|ETHER_MISS_CNT_COUNT_OFST
mdefine_line|#define ETHER_MISS_CNT_COUNT_OFST&t;&t;&t;&t;(0)
DECL|macro|ETHER_MISS_CNT_COUNT_MSK
mdefine_line|#define ETHER_MISS_CNT_COUNT_MSK&t;&t;&t;&t;(0xFFFF)
DECL|macro|ETHER_CNTDATA
mdefine_line|#define ETHER_CNTDATA(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x80))
DECL|macro|ETHER_CNTACC
mdefine_line|#define ETHER_CNTACC(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x84))
DECL|macro|ETHER_CNTACC_ADDR_OFST
mdefine_line|#define ETHER_CNTACC_ADDR_OFST&t;&t;&t;&t;&t;(0)
DECL|macro|ETHER_CNTACC_ADDR_MSK
mdefine_line|#define ETHER_CNTACC_ADDR_MSK&t;&t;&t;&t;&t;(0xFF)
DECL|macro|ETHER_CNTACC_WRRDN_OFST
mdefine_line|#define ETHER_CNTACC_WRRDN_OFST&t;&t;&t;&t;&t;(8)
DECL|macro|ETHER_CNTACC_WRRDN_MSK
mdefine_line|#define ETHER_CNTACC_WRRDN_MSK&t;&t;&t;&t;&t;(0x100)
DECL|macro|ETHER_CNTACC_CLEAR_OFST
mdefine_line|#define ETHER_CNTACC_CLEAR_OFST&t;&t;&t;&t;&t;(9)
DECL|macro|ETHER_CNTACC_CLEAR_MSK
mdefine_line|#define ETHER_CNTACC_CLEAR_MSK&t;&t;&t;&t;&t;(0x200)
DECL|macro|ETHER_TXRMINTEN
mdefine_line|#define ETHER_TXRMINTEN(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x88))
DECL|macro|ETHER_TXRMINTEN_MSK
mdefine_line|#define ETHER_TXRMINTEN_MSK&t;&t;&t;&t;&t;&t;(0x3FFFFFFF)
DECL|macro|ETHER_RXRMINTEN
mdefine_line|#define ETHER_RXRMINTEN(base)&t;&t;&t;&t;&t;&t;&t;(ETHER00_TYPE (base + 0x8C))
DECL|macro|ETHER_RXRMINTEN_MSK
mdefine_line|#define ETHER_RXRMINTEN_MSK&t;&t;&t;&t;&t;&t;(0xFFFFFF)
multiline_comment|/*&n;*&t;RMON Registers&n;*/
DECL|macro|RMON_COLLISION0
mdefine_line|#define&t;&t;RMON_COLLISION0&t;&t;&t;&t;&t;&t;0x0
DECL|macro|RMON_COLLISION1
mdefine_line|#define&t;&t;RMON_COLLISION1&t;&t;&t;&t;&t;&t;0x1
DECL|macro|RMON_COLLISION2
mdefine_line|#define&t;&t;RMON_COLLISION2&t;&t;&t;&t;&t;&t;0x2
DECL|macro|RMON_COLLISION3
mdefine_line|#define&t;&t;RMON_COLLISION3&t;&t;&t;&t;&t;&t;0x3
DECL|macro|RMON_COLLISION4
mdefine_line|#define&t;&t;RMON_COLLISION4&t;&t;&t;&t;&t;&t;0x4
DECL|macro|RMON_COLLISION5
mdefine_line|#define&t;&t;RMON_COLLISION5&t;&t;&t;&t;&t;&t;0x5
DECL|macro|RMON_COLLISION6
mdefine_line|#define&t;&t;RMON_COLLISION6&t;&t;&t;&t;&t;&t;0x6
DECL|macro|RMON_COLLISION7
mdefine_line|#define&t;&t;RMON_COLLISION7&t;&t;&t;&t;&t;&t;0x7
DECL|macro|RMON_COLLISION8
mdefine_line|#define&t;&t;RMON_COLLISION8&t;&t;&t;&t;&t;&t;0x8
DECL|macro|RMON_COLLISION9
mdefine_line|#define&t;&t;RMON_COLLISION9&t;&t;&t;&t;&t;&t;0x9
DECL|macro|RMON_COLLISION10
mdefine_line|#define&t;&t;RMON_COLLISION10&t;&t;&t;&t;&t;0xa
DECL|macro|RMON_COLLISION11
mdefine_line|#define&t;&t;RMON_COLLISION11&t;&t;&t;&t;&t;0xb
DECL|macro|RMON_COLLISION12
mdefine_line|#define&t;&t;RMON_COLLISION12&t;&t;&t;&t;&t;0xc
DECL|macro|RMON_COLLISION13
mdefine_line|#define&t;&t;RMON_COLLISION13&t;&t;&t;&t;&t;0xd
DECL|macro|RMON_COLLISION14
mdefine_line|#define&t;&t;RMON_COLLISION14&t;&t;&t;&t;&t;0xe
DECL|macro|RMON_COLLISION15
mdefine_line|#define&t;&t;RMON_COLLISION15&t;&t;&t;&t;&t;0xf
DECL|macro|RMON_COLLISION16
mdefine_line|#define&t;&t;RMON_COLLISION16&t;&t;&t;&t;&t;0x10
DECL|macro|RMON_FRAMES_WITH_DEFERRED_XMISSIONS
mdefine_line|#define&t;&t;RMON_FRAMES_WITH_DEFERRED_XMISSIONS&t;0x11
DECL|macro|RMON_LATE_COLLISIONS
mdefine_line|#define&t;&t;RMON_LATE_COLLISIONS&t;&t;&t;&t;0x12
DECL|macro|RMON_FRAMES_LOST_DUE_TO_MAC_XMIT
mdefine_line|#define&t;&t;RMON_FRAMES_LOST_DUE_TO_MAC_XMIT&t;0x13
DECL|macro|RMON_CARRIER_SENSE_ERRORS
mdefine_line|#define&t;&t;RMON_CARRIER_SENSE_ERRORS&t;&t;&t;0x14
DECL|macro|RMON_FRAMES_WITH_EXCESSIVE_DEFERAL
mdefine_line|#define&t;&t;RMON_FRAMES_WITH_EXCESSIVE_DEFERAL&t;0x15
DECL|macro|RMON_UNICAST_FRAMES_TRANSMITTED_OK
mdefine_line|#define&t;&t;RMON_UNICAST_FRAMES_TRANSMITTED_OK&t;0x16
DECL|macro|RMON_MULTICAST_FRAMES_XMITTED_OK
mdefine_line|#define&t;&t;RMON_MULTICAST_FRAMES_XMITTED_OK&t;0x17
DECL|macro|RMON_BROADCAST_FRAMES_XMITTED_OK
mdefine_line|#define&t;&t;RMON_BROADCAST_FRAMES_XMITTED_OK&t;0x18
DECL|macro|RMON_SQE_TEST_ERRORS
mdefine_line|#define&t;&t;RMON_SQE_TEST_ERRORS&t;&t;&t;&t;0x19
DECL|macro|RMON_PAUSE_MACCTRL_FRAMES_XMITTED
mdefine_line|#define&t;&t;RMON_PAUSE_MACCTRL_FRAMES_XMITTED&t;0x1A
DECL|macro|RMON_MACCTRL_FRAMES_XMITTED
mdefine_line|#define&t;&t;RMON_MACCTRL_FRAMES_XMITTED&t;&t;&t;0x1B
DECL|macro|RMON_VLAN_FRAMES_XMITTED
mdefine_line|#define&t;&t;RMON_VLAN_FRAMES_XMITTED&t;&t;&t;0x1C
DECL|macro|RMON_OCTETS_XMITTED_OK
mdefine_line|#define&t;&t;RMON_OCTETS_XMITTED_OK&t;&t;&t;&t;0x1D
DECL|macro|RMON_OCTETS_XMITTED_OK_HI
mdefine_line|#define&t;&t;RMON_OCTETS_XMITTED_OK_HI&t;&t;&t;0x1E
DECL|macro|RMON_RX_PACKET_SIZES0
mdefine_line|#define&t;&t;RMON_RX_PACKET_SIZES0&t;&t;&t;&t;0x40
DECL|macro|RMON_RX_PACKET_SIZES1
mdefine_line|#define&t;&t;RMON_RX_PACKET_SIZES1&t;&t;&t;&t;0x41
DECL|macro|RMON_RX_PACKET_SIZES2
mdefine_line|#define&t;&t;RMON_RX_PACKET_SIZES2&t;&t;&t;&t;0x42
DECL|macro|RMON_RX_PACKET_SIZES3
mdefine_line|#define&t;&t;RMON_RX_PACKET_SIZES3&t;&t;&t;&t;0x43
DECL|macro|RMON_RX_PACKET_SIZES4
mdefine_line|#define&t;&t;RMON_RX_PACKET_SIZES4&t;&t;&t;&t;0x44
DECL|macro|RMON_RX_PACKET_SIZES5
mdefine_line|#define&t;&t;RMON_RX_PACKET_SIZES5&t;&t;&t;&t;0x45
DECL|macro|RMON_RX_PACKET_SIZES6
mdefine_line|#define&t;&t;RMON_RX_PACKET_SIZES6&t;&t;&t;&t;0x46
DECL|macro|RMON_RX_PACKET_SIZES7
mdefine_line|#define&t;&t;RMON_RX_PACKET_SIZES7&t;&t;&t;&t;0x47
DECL|macro|RMON_FRAME_CHECK_SEQUENCE_ERRORS
mdefine_line|#define&t;&t;RMON_FRAME_CHECK_SEQUENCE_ERRORS&t;0x48
DECL|macro|RMON_ALIGNMENT_ERRORS
mdefine_line|#define&t;&t;RMON_ALIGNMENT_ERRORS&t;&t;&t;&t;0x49
DECL|macro|RMON_FRAGMENTS
mdefine_line|#define&t;&t;RMON_FRAGMENTS&t;&t;&t;&t;&t;&t;0x4A
DECL|macro|RMON_JABBERS
mdefine_line|#define&t;&t;RMON_JABBERS&t;&t;&t;&t;&t;&t;0x4B
DECL|macro|RMON_FRAMES_LOST_TO_INTMACRCVERR
mdefine_line|#define&t;&t;RMON_FRAMES_LOST_TO_INTMACRCVERR&t;0x4C
DECL|macro|RMON_UNICAST_FRAMES_RCVD_OK
mdefine_line|#define&t;&t;RMON_UNICAST_FRAMES_RCVD_OK&t;&t;&t;0x4D
DECL|macro|RMON_MULTICAST_FRAMES_RCVD_OK
mdefine_line|#define&t;&t;RMON_MULTICAST_FRAMES_RCVD_OK&t;&t;0x4E
DECL|macro|RMON_BROADCAST_FRAMES_RCVD_OK
mdefine_line|#define&t;&t;RMON_BROADCAST_FRAMES_RCVD_OK&t;&t;0x4F
DECL|macro|RMON_IN_RANGE_LENGTH_ERRORS
mdefine_line|#define&t;&t;RMON_IN_RANGE_LENGTH_ERRORS&t;&t;&t;0x50
DECL|macro|RMON_OUT_OF_RANGE_LENGTH_ERRORS
mdefine_line|#define&t;&t;RMON_OUT_OF_RANGE_LENGTH_ERRORS&t;&t;0x51
DECL|macro|RMON_VLAN_FRAMES_RCVD
mdefine_line|#define&t;&t;RMON_VLAN_FRAMES_RCVD&t;&t;&t;&t;0x52
DECL|macro|RMON_PAUSE_MAC_CTRL_FRAMES_RCVD
mdefine_line|#define&t;&t;RMON_PAUSE_MAC_CTRL_FRAMES_RCVD&t;&t;0x53
DECL|macro|RMON_MAC_CTRL_FRAMES_RCVD
mdefine_line|#define&t;&t;RMON_MAC_CTRL_FRAMES_RCVD&t;&t;&t;0x54
DECL|macro|RMON_OCTETS_RCVD_OK
mdefine_line|#define&t;&t;RMON_OCTETS_RCVD_OK&t;&t;&t;&t;&t;0x55
DECL|macro|RMON_OCTETS_RCVD_OK_HI
mdefine_line|#define&t;&t;RMON_OCTETS_RCVD_OK_HI&t;&t;&t;&t;0x56
DECL|macro|RMON_OCTETS_RCVD_OTHER
mdefine_line|#define&t;&t;RMON_OCTETS_RCVD_OTHER&t;&t;&t;&t;0x57
DECL|macro|RMON_OCTETS_RCVD_OTHER_HI
mdefine_line|#define&t;&t;RMON_OCTETS_RCVD_OTHER_HI&t;&t;&t;0x58
macro_line|#endif /* __ETHER00_H */
eof
