macro_line|#ifndef __ALPHA_TSUNAMI__H__
DECL|macro|__ALPHA_TSUNAMI__H__
mdefine_line|#define __ALPHA_TSUNAMI__H__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * TSUNAMI/TYPHOON are the internal names for the core logic chipset which&n; * provides memory controller and PCI access for the 21264 based systems.&n; *&n; * This file is based on:&n; *&n; * Tsunami System Programmers Manual&n; * Preliminary, Chapters 2-5&n; *&n; */
multiline_comment|/* XXX: Do we need to conditionalize on this?  */
macro_line|#ifdef USE_48_BIT_KSEG
DECL|macro|TS_BIAS
mdefine_line|#define TS_BIAS 0x80000000000UL
macro_line|#else
DECL|macro|TS_BIAS
mdefine_line|#define TS_BIAS 0x10000000000UL
macro_line|#endif
multiline_comment|/*&n; * CChip, DChip, and PChip registers&n; */
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
DECL|typedef|tsunami_64
)brace
id|tsunami_64
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|csc
id|tsunami_64
id|csc
suffix:semicolon
DECL|member|mtr
id|tsunami_64
id|mtr
suffix:semicolon
DECL|member|misc
id|tsunami_64
id|misc
suffix:semicolon
DECL|member|mpd
id|tsunami_64
id|mpd
suffix:semicolon
DECL|member|aar0
id|tsunami_64
id|aar0
suffix:semicolon
DECL|member|aar1
id|tsunami_64
id|aar1
suffix:semicolon
DECL|member|aar2
id|tsunami_64
id|aar2
suffix:semicolon
DECL|member|aar3
id|tsunami_64
id|aar3
suffix:semicolon
DECL|member|dim0
id|tsunami_64
id|dim0
suffix:semicolon
DECL|member|dim1
id|tsunami_64
id|dim1
suffix:semicolon
DECL|member|dir0
id|tsunami_64
id|dir0
suffix:semicolon
DECL|member|dir1
id|tsunami_64
id|dir1
suffix:semicolon
DECL|member|drir
id|tsunami_64
id|drir
suffix:semicolon
DECL|member|prben
id|tsunami_64
id|prben
suffix:semicolon
DECL|member|iic
id|tsunami_64
id|iic
suffix:semicolon
multiline_comment|/* a.k.a. iic0 */
DECL|member|wdr
id|tsunami_64
id|wdr
suffix:semicolon
multiline_comment|/* a.k.a. iic1 */
DECL|member|mpr0
id|tsunami_64
id|mpr0
suffix:semicolon
DECL|member|mpr1
id|tsunami_64
id|mpr1
suffix:semicolon
DECL|member|mpr2
id|tsunami_64
id|mpr2
suffix:semicolon
DECL|member|mpr3
id|tsunami_64
id|mpr3
suffix:semicolon
DECL|member|mctl
id|tsunami_64
id|mctl
suffix:semicolon
DECL|member|__pad1
id|tsunami_64
id|__pad1
suffix:semicolon
DECL|member|ttr
id|tsunami_64
id|ttr
suffix:semicolon
DECL|member|tdr
id|tsunami_64
id|tdr
suffix:semicolon
DECL|member|dim2
id|tsunami_64
id|dim2
suffix:semicolon
DECL|member|dim3
id|tsunami_64
id|dim3
suffix:semicolon
DECL|member|dir2
id|tsunami_64
id|dir2
suffix:semicolon
DECL|member|dir3
id|tsunami_64
id|dir3
suffix:semicolon
DECL|member|iic2
id|tsunami_64
id|iic2
suffix:semicolon
DECL|member|iic3
id|tsunami_64
id|iic3
suffix:semicolon
DECL|typedef|tsunami_cchip
)brace
id|tsunami_cchip
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|dsc
id|tsunami_64
id|dsc
suffix:semicolon
DECL|member|str
id|tsunami_64
id|str
suffix:semicolon
DECL|member|drev
id|tsunami_64
id|drev
suffix:semicolon
DECL|typedef|tsunami_dchip
)brace
id|tsunami_dchip
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|wsba
id|tsunami_64
id|wsba
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|wsm
id|tsunami_64
id|wsm
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|tba
id|tsunami_64
id|tba
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|pctl
id|tsunami_64
id|pctl
suffix:semicolon
DECL|member|plat
id|tsunami_64
id|plat
suffix:semicolon
DECL|member|reserved
id|tsunami_64
id|reserved
suffix:semicolon
DECL|member|perror
id|tsunami_64
id|perror
suffix:semicolon
DECL|member|perrmask
id|tsunami_64
id|perrmask
suffix:semicolon
DECL|member|perrset
id|tsunami_64
id|perrset
suffix:semicolon
DECL|member|tlbiv
id|tsunami_64
id|tlbiv
suffix:semicolon
DECL|member|tlbia
id|tsunami_64
id|tlbia
suffix:semicolon
DECL|member|pmonctl
id|tsunami_64
id|pmonctl
suffix:semicolon
DECL|member|pmoncnt
id|tsunami_64
id|pmoncnt
suffix:semicolon
DECL|typedef|tsunami_pchip
)brace
id|tsunami_pchip
suffix:semicolon
DECL|macro|TSUNAMI_cchip
mdefine_line|#define TSUNAMI_cchip  ((tsunami_cchip *)(IDENT_ADDR+TS_BIAS+0x1A0000000UL))
DECL|macro|TSUNAMI_dchip
mdefine_line|#define TSUNAMI_dchip  ((tsunami_dchip *)(IDENT_ADDR+TS_BIAS+0x1B0000800UL))
DECL|macro|TSUNAMI_pchip0
mdefine_line|#define TSUNAMI_pchip0 ((tsunami_pchip *)(IDENT_ADDR+TS_BIAS+0x180000000UL))
DECL|macro|TSUNAMI_pchip1
mdefine_line|#define TSUNAMI_pchip1 ((tsunami_pchip *)(IDENT_ADDR+TS_BIAS+0x380000000UL))
r_extern
r_int
id|TSUNAMI_bootcpu
suffix:semicolon
multiline_comment|/*&n; * TSUNAMI Pchip Error register.&n; */
DECL|macro|perror_m_lost
mdefine_line|#define perror_m_lost 0x1
DECL|macro|perror_m_serr
mdefine_line|#define perror_m_serr 0x2
DECL|macro|perror_m_perr
mdefine_line|#define perror_m_perr 0x4
DECL|macro|perror_m_dcrto
mdefine_line|#define perror_m_dcrto 0x8
DECL|macro|perror_m_sge
mdefine_line|#define perror_m_sge 0x10
DECL|macro|perror_m_ape
mdefine_line|#define perror_m_ape 0x20
DECL|macro|perror_m_ta
mdefine_line|#define perror_m_ta 0x40
DECL|macro|perror_m_rdpe
mdefine_line|#define perror_m_rdpe 0x80
DECL|macro|perror_m_nds
mdefine_line|#define perror_m_nds 0x100
DECL|macro|perror_m_rto
mdefine_line|#define perror_m_rto 0x200
DECL|macro|perror_m_uecc
mdefine_line|#define perror_m_uecc 0x400
DECL|macro|perror_m_cre
mdefine_line|#define perror_m_cre 0x800
DECL|macro|perror_m_addrl
mdefine_line|#define perror_m_addrl 0xFFFFFFFF0000UL
DECL|macro|perror_m_addrh
mdefine_line|#define perror_m_addrh 0x7000000000000UL
DECL|macro|perror_m_cmd
mdefine_line|#define perror_m_cmd 0xF0000000000000UL
DECL|macro|perror_m_syn
mdefine_line|#define perror_m_syn 0xFF00000000000000UL
DECL|union|TPchipPERROR
r_union
id|TPchipPERROR
(brace
r_struct
(brace
DECL|member|perror_v_lost
r_int
r_int
id|perror_v_lost
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_serr
r_int
id|perror_v_serr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_perr
r_int
id|perror_v_perr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_dcrto
r_int
id|perror_v_dcrto
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_sge
r_int
id|perror_v_sge
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_ape
r_int
id|perror_v_ape
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_ta
r_int
id|perror_v_ta
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_rdpe
r_int
id|perror_v_rdpe
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_nds
r_int
id|perror_v_nds
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_rto
r_int
id|perror_v_rto
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_uecc
r_int
id|perror_v_uecc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_cre
r_int
id|perror_v_cre
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_rsvd1
r_int
id|perror_v_rsvd1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|perror_v_addrl
r_int
id|perror_v_addrl
suffix:colon
l_int|32
suffix:semicolon
DECL|member|perror_v_addrh
r_int
id|perror_v_addrh
suffix:colon
l_int|3
suffix:semicolon
DECL|member|perror_v_rsvd2
r_int
id|perror_v_rsvd2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perror_v_cmd
r_int
id|perror_v_cmd
suffix:colon
l_int|4
suffix:semicolon
DECL|member|perror_v_syn
r_int
id|perror_v_syn
suffix:colon
l_int|8
suffix:semicolon
DECL|member|perror_r_bits
)brace
id|perror_r_bits
suffix:semicolon
DECL|member|perror_q_whole
r_int
id|perror_q_whole
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * TSUNAMI Pchip Window Space Base Address register.&n; */
DECL|macro|wsba_m_ena
mdefine_line|#define wsba_m_ena 0x1                
DECL|macro|wsba_m_sg
mdefine_line|#define wsba_m_sg 0x2
DECL|macro|wsba_m_ptp
mdefine_line|#define wsba_m_ptp 0x4
DECL|macro|wsba_m_addr
mdefine_line|#define wsba_m_addr 0xFFF00000  
DECL|macro|wmask_k_sz1gb
mdefine_line|#define wmask_k_sz1gb 0x3FF00000                   
DECL|union|TPchipWSBA
r_union
id|TPchipWSBA
(brace
r_struct
(brace
DECL|member|wsba_v_ena
r_int
id|wsba_v_ena
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wsba_v_sg
r_int
id|wsba_v_sg
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wsba_v_ptp
r_int
id|wsba_v_ptp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wsba_v_rsvd1
r_int
id|wsba_v_rsvd1
suffix:colon
l_int|17
suffix:semicolon
DECL|member|wsba_v_addr
r_int
id|wsba_v_addr
suffix:colon
l_int|12
suffix:semicolon
DECL|member|wsba_v_rsvd2
r_int
id|wsba_v_rsvd2
suffix:colon
l_int|32
suffix:semicolon
DECL|member|wsba_r_bits
)brace
id|wsba_r_bits
suffix:semicolon
DECL|member|wsba_q_whole
r_int
id|wsba_q_whole
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * TSUNAMI Pchip Control Register&n; */
DECL|macro|pctl_m_fdsc
mdefine_line|#define pctl_m_fdsc 0x1
DECL|macro|pctl_m_fbtb
mdefine_line|#define pctl_m_fbtb 0x2
DECL|macro|pctl_m_thdis
mdefine_line|#define pctl_m_thdis 0x4
DECL|macro|pctl_m_chaindis
mdefine_line|#define pctl_m_chaindis 0x8
DECL|macro|pctl_m_tgtlat
mdefine_line|#define pctl_m_tgtlat 0x10
DECL|macro|pctl_m_hole
mdefine_line|#define pctl_m_hole 0x20
DECL|macro|pctl_m_mwin
mdefine_line|#define pctl_m_mwin 0x40
DECL|macro|pctl_m_arbena
mdefine_line|#define pctl_m_arbena 0x80
DECL|macro|pctl_m_prigrp
mdefine_line|#define pctl_m_prigrp 0x7F00
DECL|macro|pctl_m_ppri
mdefine_line|#define pctl_m_ppri 0x8000
DECL|macro|pctl_m_rsvd1
mdefine_line|#define pctl_m_rsvd1 0x30000
DECL|macro|pctl_m_eccen
mdefine_line|#define pctl_m_eccen 0x40000
DECL|macro|pctl_m_padm
mdefine_line|#define pctl_m_padm 0x80000
DECL|macro|pctl_m_cdqmax
mdefine_line|#define pctl_m_cdqmax 0xF00000
DECL|macro|pctl_m_rev
mdefine_line|#define pctl_m_rev 0xFF000000
DECL|macro|pctl_m_crqmax
mdefine_line|#define pctl_m_crqmax 0xF00000000UL
DECL|macro|pctl_m_ptpmax
mdefine_line|#define pctl_m_ptpmax 0xF000000000UL
DECL|macro|pctl_m_pclkx
mdefine_line|#define pctl_m_pclkx 0x30000000000UL
DECL|macro|pctl_m_fdsdis
mdefine_line|#define pctl_m_fdsdis 0x40000000000UL
DECL|macro|pctl_m_fdwdis
mdefine_line|#define pctl_m_fdwdis 0x80000000000UL
DECL|macro|pctl_m_ptevrfy
mdefine_line|#define pctl_m_ptevrfy 0x100000000000UL
DECL|macro|pctl_m_rpp
mdefine_line|#define pctl_m_rpp 0x200000000000UL
DECL|macro|pctl_m_pid
mdefine_line|#define pctl_m_pid 0xC00000000000UL
DECL|macro|pctl_m_rsvd2
mdefine_line|#define pctl_m_rsvd2 0xFFFF000000000000UL
DECL|union|TPchipPCTL
r_union
id|TPchipPCTL
(brace
r_struct
(brace
DECL|member|pctl_v_fdsc
r_int
id|pctl_v_fdsc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_fbtb
r_int
id|pctl_v_fbtb
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_thdis
r_int
id|pctl_v_thdis
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_chaindis
r_int
id|pctl_v_chaindis
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_tgtlat
r_int
id|pctl_v_tgtlat
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_hole
r_int
id|pctl_v_hole
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_mwin
r_int
id|pctl_v_mwin
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_arbena
r_int
id|pctl_v_arbena
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_prigrp
r_int
id|pctl_v_prigrp
suffix:colon
l_int|7
suffix:semicolon
DECL|member|pctl_v_ppri
r_int
id|pctl_v_ppri
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_rsvd1
r_int
id|pctl_v_rsvd1
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pctl_v_eccen
r_int
id|pctl_v_eccen
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_padm
r_int
id|pctl_v_padm
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_cdqmax
r_int
id|pctl_v_cdqmax
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pctl_v_rev
r_int
id|pctl_v_rev
suffix:colon
l_int|8
suffix:semicolon
DECL|member|pctl_v_crqmax
r_int
id|pctl_v_crqmax
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pctl_v_ptpmax
r_int
id|pctl_v_ptpmax
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pctl_v_pclkx
r_int
id|pctl_v_pclkx
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pctl_v_fdsdis
r_int
id|pctl_v_fdsdis
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_fdwdis
r_int
id|pctl_v_fdwdis
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_ptevrfy
r_int
id|pctl_v_ptevrfy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_rpp
r_int
id|pctl_v_rpp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pctl_v_pid
r_int
id|pctl_v_pid
suffix:colon
l_int|2
suffix:semicolon
DECL|member|pctl_v_rsvd2
r_int
id|pctl_v_rsvd2
suffix:colon
l_int|16
suffix:semicolon
DECL|member|pctl_r_bits
)brace
id|pctl_r_bits
suffix:semicolon
DECL|member|pctl_q_whole
r_int
id|pctl_q_whole
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * TSUNAMI Pchip Error Mask Register.&n; */
DECL|macro|perrmask_m_lost
mdefine_line|#define perrmask_m_lost 0x1
DECL|macro|perrmask_m_serr
mdefine_line|#define perrmask_m_serr 0x2
DECL|macro|perrmask_m_perr
mdefine_line|#define perrmask_m_perr 0x4
DECL|macro|perrmask_m_dcrto
mdefine_line|#define perrmask_m_dcrto 0x8
DECL|macro|perrmask_m_sge
mdefine_line|#define perrmask_m_sge 0x10
DECL|macro|perrmask_m_ape
mdefine_line|#define perrmask_m_ape 0x20
DECL|macro|perrmask_m_ta
mdefine_line|#define perrmask_m_ta 0x40
DECL|macro|perrmask_m_rdpe
mdefine_line|#define perrmask_m_rdpe 0x80
DECL|macro|perrmask_m_nds
mdefine_line|#define perrmask_m_nds 0x100
DECL|macro|perrmask_m_rto
mdefine_line|#define perrmask_m_rto 0x200
DECL|macro|perrmask_m_uecc
mdefine_line|#define perrmask_m_uecc 0x400
DECL|macro|perrmask_m_cre
mdefine_line|#define perrmask_m_cre 0x800
DECL|macro|perrmask_m_rsvd
mdefine_line|#define perrmask_m_rsvd 0xFFFFFFFFFFFFF000UL
DECL|union|TPchipPERRMASK
r_union
id|TPchipPERRMASK
(brace
r_struct
(brace
DECL|member|perrmask_v_lost
r_int
r_int
id|perrmask_v_lost
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_serr
r_int
id|perrmask_v_serr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_perr
r_int
id|perrmask_v_perr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_dcrto
r_int
id|perrmask_v_dcrto
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_sge
r_int
id|perrmask_v_sge
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_ape
r_int
id|perrmask_v_ape
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_ta
r_int
id|perrmask_v_ta
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_rdpe
r_int
id|perrmask_v_rdpe
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_nds
r_int
id|perrmask_v_nds
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_rto
r_int
id|perrmask_v_rto
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_uecc
r_int
id|perrmask_v_uecc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_cre
r_int
id|perrmask_v_cre
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perrmask_v_rsvd1
r_int
id|perrmask_v_rsvd1
suffix:colon
l_int|20
suffix:semicolon
DECL|member|perrmask_v_rsvd2
r_int
id|perrmask_v_rsvd2
suffix:colon
l_int|32
suffix:semicolon
DECL|member|perrmask_r_bits
)brace
id|perrmask_r_bits
suffix:semicolon
DECL|member|perrmask_q_whole
r_int
id|perrmask_q_whole
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Memory spaces:&n; */
DECL|macro|TSUNAMI_HOSE
mdefine_line|#define TSUNAMI_HOSE(h)&t;&t;(((unsigned long)(h)) &lt;&lt; 33)
DECL|macro|TSUNAMI_BASE
mdefine_line|#define TSUNAMI_BASE&t;&t;(IDENT_ADDR + TS_BIAS)
DECL|macro|TSUNAMI_MEM
mdefine_line|#define TSUNAMI_MEM(h)&t;&t;(TSUNAMI_BASE+TSUNAMI_HOSE(h) + 0x000000000UL)
DECL|macro|_TSUNAMI_IACK_SC
mdefine_line|#define _TSUNAMI_IACK_SC(h)&t;(TSUNAMI_BASE+TSUNAMI_HOSE(h) + 0x1F8000000UL)
DECL|macro|TSUNAMI_IO
mdefine_line|#define TSUNAMI_IO(h)&t;&t;(TSUNAMI_BASE+TSUNAMI_HOSE(h) + 0x1FC000000UL)
DECL|macro|TSUNAMI_CONF
mdefine_line|#define TSUNAMI_CONF(h)&t;&t;(TSUNAMI_BASE+TSUNAMI_HOSE(h) + 0x1FE000000UL)
DECL|macro|TSUNAMI_IACK_SC
mdefine_line|#define TSUNAMI_IACK_SC&t;&t;_TSUNAMI_IACK_SC(0) /* hack! */
multiline_comment|/* &n; * The canonical non-remaped I/O and MEM addresses have these values&n; * subtracted out.  This is arranged so that folks manipulating ISA&n; * devices can use their familiar numbers and have them map to bus 0.&n; */
DECL|macro|TSUNAMI_IO_BIAS
mdefine_line|#define TSUNAMI_IO_BIAS          TSUNAMI_IO(0)
DECL|macro|TSUNAMI_MEM_BIAS
mdefine_line|#define TSUNAMI_MEM_BIAS         TSUNAMI_MEM(0)
multiline_comment|/* The IO address space is larger than 0xffff */
DECL|macro|TSUNAMI_IO_SPACE
mdefine_line|#define TSUNAMI_IO_SPACE&t;(TSUNAMI_CONF(0) - TSUNAMI_IO(0))
multiline_comment|/* Offset between ram physical addresses and pci64 DAC bus addresses.  */
DECL|macro|TSUNAMI_DAC_OFFSET
mdefine_line|#define TSUNAMI_DAC_OFFSET&t;(1UL &lt;&lt; 40)
multiline_comment|/*&n; * Data structure for handling TSUNAMI machine checks:&n; */
DECL|struct|el_TSUNAMI_sysdata_mcheck
r_struct
id|el_TSUNAMI_sysdata_mcheck
(brace
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__IO_EXTERN_INLINE
mdefine_line|#define __IO_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * I/O functions:&n; *&n; * TSUNAMI, the 21??? PCI/memory support chipset for the EV6 (21264)&n; * can only use linear accesses to get at PCI memory and I/O spaces.&n; */
multiline_comment|/*&n; * Memory functions.  all accesses are done through linear space.&n; */
DECL|function|tsunami_ioportmap
id|__EXTERN_INLINE
r_void
id|__iomem
op_star
id|tsunami_ioportmap
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
id|TSUNAMI_IO_BIAS
)paren
suffix:semicolon
)brace
DECL|function|tsunami_ioremap
id|__EXTERN_INLINE
r_void
id|__iomem
op_star
id|tsunami_ioremap
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
id|TSUNAMI_MEM_BIAS
)paren
suffix:semicolon
)brace
DECL|function|tsunami_is_ioaddr
id|__EXTERN_INLINE
r_int
id|tsunami_is_ioaddr
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
id|TSUNAMI_BASE
suffix:semicolon
)brace
DECL|function|tsunami_is_mmio
id|__EXTERN_INLINE
r_int
id|tsunami_is_mmio
c_func
(paren
r_const
r_volatile
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
r_return
(paren
id|addr
op_amp
l_int|0x100000000UL
)paren
op_eq
l_int|0
suffix:semicolon
)brace
DECL|macro|__IO_PREFIX
macro_line|#undef __IO_PREFIX
DECL|macro|__IO_PREFIX
mdefine_line|#define __IO_PREFIX&t;&t;tsunami
DECL|macro|tsunami_trivial_rw_bw
mdefine_line|#define tsunami_trivial_rw_bw&t;1
DECL|macro|tsunami_trivial_rw_lq
mdefine_line|#define tsunami_trivial_rw_lq&t;1
DECL|macro|tsunami_trivial_io_bw
mdefine_line|#define tsunami_trivial_io_bw&t;1
DECL|macro|tsunami_trivial_io_lq
mdefine_line|#define tsunami_trivial_io_lq&t;1
DECL|macro|tsunami_trivial_iounmap
mdefine_line|#define tsunami_trivial_iounmap&t;1
macro_line|#include &lt;asm/io_trivial.h&gt;
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_TSUNAMI__H__ */
eof
