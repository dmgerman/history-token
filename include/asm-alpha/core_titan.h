macro_line|#ifndef __ALPHA_TITAN__H__
DECL|macro|__ALPHA_TITAN__H__
mdefine_line|#define __ALPHA_TITAN__H__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * TITAN is the internal names for a core logic chipset which provides&n; * memory controller and PCI/AGP access for 21264 based systems.&n; *&n; * This file is based on:&n; *&n; * Titan Chipset Engineering Specification&n; * Revision 0.12&n; * 13 July 1999&n; *&n; */
multiline_comment|/* XXX: Do we need to conditionalize on this?  */
macro_line|#ifdef USE_48_BIT_KSEG
DECL|macro|TI_BIAS
mdefine_line|#define TI_BIAS 0x80000000000UL
macro_line|#else
DECL|macro|TI_BIAS
mdefine_line|#define TI_BIAS 0x10000000000UL
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
DECL|typedef|titan_64
)brace
id|titan_64
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|csc
id|titan_64
id|csc
suffix:semicolon
DECL|member|mtr
id|titan_64
id|mtr
suffix:semicolon
DECL|member|misc
id|titan_64
id|misc
suffix:semicolon
DECL|member|mpd
id|titan_64
id|mpd
suffix:semicolon
DECL|member|aar0
id|titan_64
id|aar0
suffix:semicolon
DECL|member|aar1
id|titan_64
id|aar1
suffix:semicolon
DECL|member|aar2
id|titan_64
id|aar2
suffix:semicolon
DECL|member|aar3
id|titan_64
id|aar3
suffix:semicolon
DECL|member|dim0
id|titan_64
id|dim0
suffix:semicolon
DECL|member|dim1
id|titan_64
id|dim1
suffix:semicolon
DECL|member|dir0
id|titan_64
id|dir0
suffix:semicolon
DECL|member|dir1
id|titan_64
id|dir1
suffix:semicolon
DECL|member|drir
id|titan_64
id|drir
suffix:semicolon
DECL|member|prben
id|titan_64
id|prben
suffix:semicolon
DECL|member|iic0
id|titan_64
id|iic0
suffix:semicolon
DECL|member|iic1
id|titan_64
id|iic1
suffix:semicolon
DECL|member|mpr0
id|titan_64
id|mpr0
suffix:semicolon
DECL|member|mpr1
id|titan_64
id|mpr1
suffix:semicolon
DECL|member|mpr2
id|titan_64
id|mpr2
suffix:semicolon
DECL|member|mpr3
id|titan_64
id|mpr3
suffix:semicolon
DECL|member|rsvd
id|titan_64
id|rsvd
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ttr
id|titan_64
id|ttr
suffix:semicolon
DECL|member|tdr
id|titan_64
id|tdr
suffix:semicolon
DECL|member|dim2
id|titan_64
id|dim2
suffix:semicolon
DECL|member|dim3
id|titan_64
id|dim3
suffix:semicolon
DECL|member|dir2
id|titan_64
id|dir2
suffix:semicolon
DECL|member|dir3
id|titan_64
id|dir3
suffix:semicolon
DECL|member|iic2
id|titan_64
id|iic2
suffix:semicolon
DECL|member|iic3
id|titan_64
id|iic3
suffix:semicolon
DECL|member|pwr
id|titan_64
id|pwr
suffix:semicolon
DECL|member|reserved
id|titan_64
id|reserved
(braket
l_int|17
)braket
suffix:semicolon
DECL|member|cmonctla
id|titan_64
id|cmonctla
suffix:semicolon
DECL|member|cmonctlb
id|titan_64
id|cmonctlb
suffix:semicolon
DECL|member|cmoncnt01
id|titan_64
id|cmoncnt01
suffix:semicolon
DECL|member|cmoncnt23
id|titan_64
id|cmoncnt23
suffix:semicolon
DECL|member|cpen
id|titan_64
id|cpen
suffix:semicolon
DECL|typedef|titan_cchip
)brace
id|titan_cchip
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|dsc
id|titan_64
id|dsc
suffix:semicolon
DECL|member|str
id|titan_64
id|str
suffix:semicolon
DECL|member|drev
id|titan_64
id|drev
suffix:semicolon
DECL|member|dsc2
id|titan_64
id|dsc2
suffix:semicolon
DECL|typedef|titan_dchip
)brace
id|titan_dchip
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|wsba
id|titan_64
id|wsba
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|wsm
id|titan_64
id|wsm
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|tba
id|titan_64
id|tba
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|pctl
id|titan_64
id|pctl
suffix:semicolon
DECL|member|plat
id|titan_64
id|plat
suffix:semicolon
DECL|member|reserved0
id|titan_64
id|reserved0
(braket
l_int|2
)braket
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|serror
id|titan_64
id|serror
suffix:semicolon
DECL|member|serren
id|titan_64
id|serren
suffix:semicolon
DECL|member|serrset
id|titan_64
id|serrset
suffix:semicolon
DECL|member|reserved0
id|titan_64
id|reserved0
suffix:semicolon
DECL|member|gperror
id|titan_64
id|gperror
suffix:semicolon
DECL|member|gperren
id|titan_64
id|gperren
suffix:semicolon
DECL|member|gperrset
id|titan_64
id|gperrset
suffix:semicolon
DECL|member|reserved1
id|titan_64
id|reserved1
suffix:semicolon
DECL|member|gtlbiv
id|titan_64
id|gtlbiv
suffix:semicolon
DECL|member|gtlbia
id|titan_64
id|gtlbia
suffix:semicolon
DECL|member|reserved2
id|titan_64
id|reserved2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|sctl
id|titan_64
id|sctl
suffix:semicolon
DECL|member|reserved3
id|titan_64
id|reserved3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|g
)brace
id|g
suffix:semicolon
r_struct
(brace
DECL|member|agperror
id|titan_64
id|agperror
suffix:semicolon
DECL|member|agperren
id|titan_64
id|agperren
suffix:semicolon
DECL|member|agperrset
id|titan_64
id|agperrset
suffix:semicolon
DECL|member|agplastwr
id|titan_64
id|agplastwr
suffix:semicolon
DECL|member|aperror
id|titan_64
id|aperror
suffix:semicolon
DECL|member|aperren
id|titan_64
id|aperren
suffix:semicolon
DECL|member|aperrset
id|titan_64
id|aperrset
suffix:semicolon
DECL|member|reserved0
id|titan_64
id|reserved0
suffix:semicolon
DECL|member|atlbiv
id|titan_64
id|atlbiv
suffix:semicolon
DECL|member|atlbia
id|titan_64
id|atlbia
suffix:semicolon
DECL|member|reserved1
id|titan_64
id|reserved1
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|a
)brace
id|a
suffix:semicolon
DECL|member|port_specific
)brace
id|port_specific
suffix:semicolon
DECL|member|sprst
id|titan_64
id|sprst
suffix:semicolon
DECL|member|reserved1
id|titan_64
id|reserved1
(braket
l_int|31
)braket
suffix:semicolon
DECL|typedef|titan_pachip_port
)brace
id|titan_pachip_port
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|g_port
id|titan_pachip_port
id|g_port
suffix:semicolon
DECL|member|a_port
id|titan_pachip_port
id|a_port
suffix:semicolon
DECL|typedef|titan_pachip
)brace
id|titan_pachip
suffix:semicolon
DECL|macro|TITAN_cchip
mdefine_line|#define TITAN_cchip&t;((titan_cchip  *)(IDENT_ADDR+TI_BIAS+0x1A0000000UL))
DECL|macro|TITAN_dchip
mdefine_line|#define TITAN_dchip    &t;((titan_dchip  *)(IDENT_ADDR+TI_BIAS+0x1B0000800UL))
DECL|macro|TITAN_pachip0
mdefine_line|#define TITAN_pachip0 &t;((titan_pachip *)(IDENT_ADDR+TI_BIAS+0x180000000UL))
DECL|macro|TITAN_pachip1
mdefine_line|#define TITAN_pachip1 &t;((titan_pachip *)(IDENT_ADDR+TI_BIAS+0x380000000UL))
r_extern
r_int
id|TITAN_agp
suffix:semicolon
r_extern
r_int
id|TITAN_bootcpu
suffix:semicolon
multiline_comment|/*&n; * TITAN PA-chip Window Space Base Address register.&n; * (WSBA[0-2])&n; */
DECL|macro|wsba_m_ena
mdefine_line|#define wsba_m_ena 0x1                
DECL|macro|wsba_m_sg
mdefine_line|#define wsba_m_sg 0x2
DECL|macro|wsba_m_addr
mdefine_line|#define wsba_m_addr 0xFFF00000  
DECL|macro|wmask_k_sz1gb
mdefine_line|#define wmask_k_sz1gb 0x3FF00000                   
DECL|union|TPAchipWSBA
r_union
id|TPAchipWSBA
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
DECL|member|wsba_v_rsvd1
r_int
id|wsba_v_rsvd1
suffix:colon
l_int|18
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
multiline_comment|/*&n; * TITAN PA-chip Control Register&n; * This definition covers both the G-Port GPCTL and the A-PORT APCTL.&n; * Bits &lt;51:0&gt; are the same in both cases. APCTL&lt;63:52&gt; are only &n; * applicable to AGP.&n; */
DECL|macro|pctl_m_fbtb
mdefine_line|#define pctl_m_fbtb &t;&t;&t;0x00000001
DECL|macro|pctl_m_thdis
mdefine_line|#define pctl_m_thdis &t;&t;&t;0x00000002
DECL|macro|pctl_m_chaindis
mdefine_line|#define pctl_m_chaindis &t;&t;0x00000004
DECL|macro|pctl_m_tgtlat
mdefine_line|#define pctl_m_tgtlat &t;&t;&t;0x00000018
DECL|macro|pctl_m_hole
mdefine_line|#define pctl_m_hole  &t;  &t;&t;0x00000020
DECL|macro|pctl_m_mwin
mdefine_line|#define pctl_m_mwin &t;  &t;&t;0x00000040
DECL|macro|pctl_m_arbena
mdefine_line|#define pctl_m_arbena &t;  &t;&t;0x00000080
DECL|macro|pctl_m_prigrp
mdefine_line|#define pctl_m_prigrp &t;  &t;&t;0x0000FF00
DECL|macro|pctl_m_ppri
mdefine_line|#define pctl_m_ppri &t;  &t;&t;0x00010000
DECL|macro|pctl_m_pcispd66
mdefine_line|#define pctl_m_pcispd66  &t;&t;0x00020000
DECL|macro|pctl_m_cngstlt
mdefine_line|#define pctl_m_cngstlt&t;  &t;&t;0x003C0000
DECL|macro|pctl_m_ptpdesten
mdefine_line|#define pctl_m_ptpdesten &t;&t;0x3FC00000
DECL|macro|pctl_m_dpcen
mdefine_line|#define pctl_m_dpcen&t;&t;&t;0x40000000
DECL|macro|pctl_m_apcen
mdefine_line|#define pctl_m_apcen&t;&t;0x0000000080000000UL
DECL|macro|pctl_m_dcrtv
mdefine_line|#define pctl_m_dcrtv&t;&t;0x0000000300000000UL
DECL|macro|pctl_m_en_stepping
mdefine_line|#define pctl_m_en_stepping&t;0x0000000400000000UL
DECL|macro|apctl_m_rsvd1
mdefine_line|#define apctl_m_rsvd1&t;&t;0x000FFFF800000000UL
DECL|macro|apctl_m_agp_rate
mdefine_line|#define apctl_m_agp_rate&t;0x0030000000000000UL
DECL|macro|apctl_m_agp_sba_en
mdefine_line|#define apctl_m_agp_sba_en&t;0x0040000000000000UL
DECL|macro|apctl_m_agp_en
mdefine_line|#define apctl_m_agp_en&t;&t;0x0080000000000000UL
DECL|macro|apctl_m_rsvd2
mdefine_line|#define apctl_m_rsvd2&t;&t;0x0100000000000000UL
DECL|macro|apctl_m_agp_present
mdefine_line|#define apctl_m_agp_present&t;0x0200000000000000UL
DECL|macro|apctl_agp_hp_rd
mdefine_line|#define apctl_agp_hp_rd&t;&t;0x1C00000000000000UL
DECL|macro|apctl_agp_lp_rd
mdefine_line|#define apctl_agp_lp_rd&t;&t;0xE000000000000000UL
DECL|macro|gpctl_m_rsvd
mdefine_line|#define gpctl_m_rsvd&t;&t;0xFFFFFFF800000000UL
DECL|union|TPAchipPCTL
r_union
id|TPAchipPCTL
(brace
r_struct
(brace
DECL|member|pctl_v_fbtb
r_int
id|pctl_v_fbtb
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A/G [0]     */
DECL|member|pctl_v_thdis
r_int
id|pctl_v_thdis
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A/G [1]     */
DECL|member|pctl_v_chaindis
r_int
id|pctl_v_chaindis
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A/G [2]     */
DECL|member|pctl_v_tgtlat
r_int
id|pctl_v_tgtlat
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* A/G [4:3]   */
DECL|member|pctl_v_hole
r_int
id|pctl_v_hole
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A/G [5]     */
DECL|member|pctl_v_mwin
r_int
id|pctl_v_mwin
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A/G [6]     */
DECL|member|pctl_v_arbena
r_int
id|pctl_v_arbena
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A/G [7]     */
DECL|member|pctl_v_prigrp
r_int
id|pctl_v_prigrp
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* A/G [15:8]  */
DECL|member|pctl_v_ppri
r_int
id|pctl_v_ppri
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A/G [16]    */
DECL|member|pctl_v_pcispd66
r_int
id|pctl_v_pcispd66
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A/G [17]    */
DECL|member|pctl_v_cngstlt
r_int
id|pctl_v_cngstlt
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* A/G [21:18] */
DECL|member|pctl_v_ptpdesten
r_int
id|pctl_v_ptpdesten
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* A/G [29:22] */
DECL|member|pctl_v_dpcen
r_int
id|pctl_v_dpcen
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A/G [30]    */
DECL|member|pctl_v_apcen
r_int
id|pctl_v_apcen
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A/G [31]    */
DECL|member|pctl_v_dcrtv
r_int
id|pctl_v_dcrtv
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* A/G [33:32] */
DECL|member|pctl_v_en_stepping
r_int
id|pctl_v_en_stepping
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A/G [34]    */
DECL|member|apctl_v_rsvd1
r_int
id|apctl_v_rsvd1
suffix:colon
l_int|17
suffix:semicolon
multiline_comment|/* A   [51:35] */
DECL|member|apctl_v_agp_rate
r_int
id|apctl_v_agp_rate
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* A   [53:52] */
DECL|member|apctl_v_agp_sba_en
r_int
id|apctl_v_agp_sba_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A   [54]    */
DECL|member|apctl_v_agp_en
r_int
id|apctl_v_agp_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A   [55]    */
DECL|member|apctl_v_rsvd2
r_int
id|apctl_v_rsvd2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A   [56]    */
DECL|member|apctl_v_agp_present
r_int
id|apctl_v_agp_present
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A   [57]    */
DECL|member|apctl_v_agp_hp_rd
r_int
id|apctl_v_agp_hp_rd
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* A   [60:58] */
DECL|member|apctl_v_agp_lp_rd
r_int
id|apctl_v_agp_lp_rd
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* A   [63:61] */
DECL|member|pctl_r_bits
)brace
id|pctl_r_bits
suffix:semicolon
DECL|member|pctl_l_whole
r_int
r_int
id|pctl_l_whole
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pctl_q_whole
r_int
r_int
id|pctl_q_whole
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * SERROR / SERREN / SERRSET&n; */
DECL|union|TPAchipSERR
r_union
id|TPAchipSERR
(brace
r_struct
(brace
DECL|member|serr_v_lost_uecc
r_int
id|serr_v_lost_uecc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [0]&t;&t;*/
DECL|member|serr_v_uecc
r_int
id|serr_v_uecc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [1]  &t;*/
DECL|member|serr_v_cre
r_int
id|serr_v_cre
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [2]&t;&t;*/
DECL|member|serr_v_nxio
r_int
id|serr_v_nxio
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [3]&t;&t;*/
DECL|member|serr_v_lost_cre
r_int
id|serr_v_lost_cre
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [4]&t;&t;*/
DECL|member|serr_v_rsvd0
r_int
id|serr_v_rsvd0
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* [14:5]&t;*/
DECL|member|serr_v_addr
r_int
id|serr_v_addr
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* [46:15]&t;*/
DECL|member|serr_v_rsvd1
r_int
id|serr_v_rsvd1
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* [51:47]&t;*/
DECL|member|serr_v_source
r_int
id|serr_v_source
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* [53:52]&t;*/
DECL|member|serr_v_cmd
r_int
id|serr_v_cmd
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* [55:54]&t;*/
DECL|member|serr_v_syn
r_int
id|serr_v_syn
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* [63:56]&t;*/
DECL|member|serr_r_bits
)brace
id|serr_r_bits
suffix:semicolon
DECL|member|serr_l_whole
r_int
r_int
id|serr_l_whole
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|serr_q_whole
r_int
r_int
id|serr_q_whole
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * GPERROR / APERROR / GPERREN / APERREN / GPERRSET / APERRSET&n; */
DECL|union|TPAchipPERR
r_union
id|TPAchipPERR
(brace
r_struct
(brace
DECL|member|perr_v_lost
r_int
r_int
id|perr_v_lost
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [0]&t;&t;*/
DECL|member|perr_v_serr
r_int
r_int
id|perr_v_serr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [1]&t;&t;*/
DECL|member|perr_v_perr
r_int
r_int
id|perr_v_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [2]&t;&t;*/
DECL|member|perr_v_dcrto
r_int
r_int
id|perr_v_dcrto
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [3]&t;&t;*/
DECL|member|perr_v_sge
r_int
r_int
id|perr_v_sge
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [4]&t;&t;*/
DECL|member|perr_v_ape
r_int
r_int
id|perr_v_ape
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [5]&t;&t;*/
DECL|member|perr_v_ta
r_int
r_int
id|perr_v_ta
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [6]&t;&t;*/
DECL|member|perr_v_dpe
r_int
r_int
id|perr_v_dpe
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [7]&t;&t;*/
DECL|member|perr_v_nds
r_int
r_int
id|perr_v_nds
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [8]&t;&t;*/
DECL|member|perr_v_iptpr
r_int
r_int
id|perr_v_iptpr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [9]&t;&t;*/
DECL|member|perr_v_iptpw
r_int
r_int
id|perr_v_iptpw
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [10] &t;*/
DECL|member|perr_v_rsvd0
r_int
r_int
id|perr_v_rsvd0
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* [13:11]&t;*/
DECL|member|perr_v_addr
r_int
r_int
id|perr_v_addr
suffix:colon
l_int|33
suffix:semicolon
multiline_comment|/* [46:14]&t;*/
DECL|member|perr_v_dac
r_int
r_int
id|perr_v_dac
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [47]&t;&t;*/
DECL|member|perr_v_mwin
r_int
r_int
id|perr_v_mwin
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [48]&t;&t;*/
DECL|member|perr_v_rsvd1
r_int
r_int
id|perr_v_rsvd1
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* [51:49]&t;*/
DECL|member|perr_v_cmd
r_int
r_int
id|perr_v_cmd
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* [55:52]&t;*/
DECL|member|perr_v_rsvd2
r_int
r_int
id|perr_v_rsvd2
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* [63:56]&t;*/
DECL|member|perr_r_bits
)brace
id|perr_r_bits
suffix:semicolon
DECL|member|perr_l_whole
r_int
r_int
id|perr_l_whole
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|perr_q_whole
r_int
r_int
id|perr_q_whole
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * AGPERROR / AGPERREN / AGPERRSET&n; */
DECL|union|TPAchipAGPERR
r_union
id|TPAchipAGPERR
(brace
r_struct
(brace
DECL|member|agperr_v_lost
r_int
id|agperr_v_lost
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [0]&t;&t;*/
DECL|member|agperr_v_lpqfull
r_int
id|agperr_v_lpqfull
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [1]&t;&t;*/
DECL|member|apgerr_v_hpqfull
r_int
id|apgerr_v_hpqfull
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [2]&t;&t;*/
DECL|member|agperr_v_rescmd
r_int
id|agperr_v_rescmd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [3]&t;&t;*/
DECL|member|agperr_v_ipte
r_int
id|agperr_v_ipte
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [4]&t;&t;*/
DECL|member|agperr_v_ptp
r_int
id|agperr_v_ptp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [5]&t;&t;*/
DECL|member|agperr_v_nowindow
r_int
id|agperr_v_nowindow
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [6]&t;&t;*/
DECL|member|agperr_v_rsvd0
r_int
id|agperr_v_rsvd0
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* [14:7]&t;*/
DECL|member|agperr_v_addr
r_int
id|agperr_v_addr
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* [46:15]&t;*/
DECL|member|agperr_v_rsvd1
r_int
id|agperr_v_rsvd1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [47]&t;&t;*/
DECL|member|agperr_v_dac
r_int
id|agperr_v_dac
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [48]&t;&t;*/
DECL|member|agperr_v_mwin
r_int
id|agperr_v_mwin
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [49]&t;&t;*/
DECL|member|agperr_v_cmd
r_int
id|agperr_v_cmd
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* [52:50]&t;*/
DECL|member|agperr_v_length
r_int
id|agperr_v_length
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* [58:53]&t;*/
DECL|member|agperr_v_fence
r_int
id|agperr_v_fence
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [59]&t;&t;*/
DECL|member|agperr_v_rsvd2
r_int
id|agperr_v_rsvd2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* [63:60]&t;*/
DECL|member|agperr_r_bits
)brace
id|agperr_r_bits
suffix:semicolon
DECL|member|agperr_l_whole
r_int
r_int
id|agperr_l_whole
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|agperr_q_whole
r_int
r_int
id|agperr_q_whole
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Memory spaces:&n; * Hose numbers are assigned as follows:&n; *&t;&t;0 - pachip 0 / G Port&n; *&t;&t;1 - pachip 1 / G Port&n; * &t;&t;2 - pachip 0 / A Port&n; *      &t;3 - pachip 1 / A Port&n; */
DECL|macro|TITAN_HOSE
mdefine_line|#define TITAN_HOSE(h)&t;&t;(((unsigned long)(h)) &lt;&lt; 33)
DECL|macro|TITAN_BASE
mdefine_line|#define TITAN_BASE&t;&t;(IDENT_ADDR + TI_BIAS)
DECL|macro|TITAN_MEM
mdefine_line|#define TITAN_MEM(h)&t;     &t;(TITAN_BASE+TITAN_HOSE(h)+0x000000000UL)
DECL|macro|_TITAN_IACK_SC
mdefine_line|#define _TITAN_IACK_SC(h)    &t;(TITAN_BASE+TITAN_HOSE(h)+0x1F8000000UL)
DECL|macro|TITAN_IO
mdefine_line|#define TITAN_IO(h)&t;     &t;(TITAN_BASE+TITAN_HOSE(h)+0x1FC000000UL)
DECL|macro|TITAN_CONF
mdefine_line|#define TITAN_CONF(h)&t;     &t;(TITAN_BASE+TITAN_HOSE(h)+0x1FE000000UL)
DECL|macro|TITAN_IACK_SC
mdefine_line|#define TITAN_IACK_SC&t;     &t;_TITAN_IACK_SC(0) /* hack! */
multiline_comment|/* &n; * The canonical non-remaped I/O and MEM addresses have these values&n; * subtracted out.  This is arranged so that folks manipulating ISA&n; * devices can use their familiar numbers and have them map to bus 0.&n; */
DECL|macro|TITAN_IO_BIAS
mdefine_line|#define TITAN_IO_BIAS          TITAN_IO(0)
DECL|macro|TITAN_MEM_BIAS
mdefine_line|#define TITAN_MEM_BIAS         TITAN_MEM(0)
multiline_comment|/* The IO address space is larger than 0xffff */
DECL|macro|TITAN_IO_SPACE
mdefine_line|#define TITAN_IO_SPACE&t;&t;(TITAN_CONF(0) - TITAN_IO(0))
multiline_comment|/* TIG Space */
DECL|macro|TITAN_TIG_SPACE
mdefine_line|#define TITAN_TIG_SPACE&t;&t;(TITAN_BASE + 0x100000000UL)
multiline_comment|/*&n; * Data structure for handling TITAN machine checks:&n; */
DECL|macro|SCB_Q_SYSERR
mdefine_line|#define SCB_Q_SYSERR&t;0x620
DECL|macro|SCB_Q_PROCERR
mdefine_line|#define SCB_Q_PROCERR&t;0x630
DECL|macro|SCB_Q_SYSMCHK
mdefine_line|#define SCB_Q_SYSMCHK&t;0x660
DECL|macro|SCB_Q_PROCMCHK
mdefine_line|#define SCB_Q_PROCMCHK&t;0x670
DECL|macro|SCB_Q_SYSEVENT
mdefine_line|#define SCB_Q_SYSEVENT&t;0x680&t;/* environmental / system management */
DECL|struct|el_TITAN_sysdata_mcheck
r_struct
id|el_TITAN_sysdata_mcheck
(brace
DECL|member|summary
id|u64
id|summary
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|c_dirx
id|u64
id|c_dirx
suffix:semicolon
multiline_comment|/* 0x08 */
DECL|member|c_misc
id|u64
id|c_misc
suffix:semicolon
multiline_comment|/* 0x10 */
DECL|member|p0_serror
id|u64
id|p0_serror
suffix:semicolon
multiline_comment|/* 0x18 */
DECL|member|p0_gperror
id|u64
id|p0_gperror
suffix:semicolon
multiline_comment|/* 0x20 */
DECL|member|p0_aperror
id|u64
id|p0_aperror
suffix:semicolon
multiline_comment|/* 0x28 */
DECL|member|p0_agperror
id|u64
id|p0_agperror
suffix:semicolon
multiline_comment|/* 0x30 */
DECL|member|p1_serror
id|u64
id|p1_serror
suffix:semicolon
multiline_comment|/* 0x38 */
DECL|member|p1_gperror
id|u64
id|p1_gperror
suffix:semicolon
multiline_comment|/* 0x40 */
DECL|member|p1_aperror
id|u64
id|p1_aperror
suffix:semicolon
multiline_comment|/* 0x48 */
DECL|member|p1_agperror
id|u64
id|p1_agperror
suffix:semicolon
multiline_comment|/* 0x50 */
)brace
suffix:semicolon
multiline_comment|/*&n; * System area for a privateer 680 environmental/system management mcheck &n; */
DECL|struct|el_PRIVATEER_envdata_mcheck
r_struct
id|el_PRIVATEER_envdata_mcheck
(brace
DECL|member|summary
id|u64
id|summary
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|c_dirx
id|u64
id|c_dirx
suffix:semicolon
multiline_comment|/* 0x08 */
DECL|member|smir
id|u64
id|smir
suffix:semicolon
multiline_comment|/* 0x10 */
DECL|member|cpuir
id|u64
id|cpuir
suffix:semicolon
multiline_comment|/* 0x18 */
DECL|member|psir
id|u64
id|psir
suffix:semicolon
multiline_comment|/* 0x20 */
DECL|member|fault
id|u64
id|fault
suffix:semicolon
multiline_comment|/* 0x28 */
DECL|member|sys_doors
id|u64
id|sys_doors
suffix:semicolon
multiline_comment|/* 0x30 */
DECL|member|temp_warn
id|u64
id|temp_warn
suffix:semicolon
multiline_comment|/* 0x38 */
DECL|member|fan_ctrl
id|u64
id|fan_ctrl
suffix:semicolon
multiline_comment|/* 0x40 */
DECL|member|code
id|u64
id|code
suffix:semicolon
multiline_comment|/* 0x48 */
DECL|member|reserved
id|u64
id|reserved
suffix:semicolon
multiline_comment|/* 0x50 */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__IO_EXTERN_INLINE
mdefine_line|#define __IO_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * I/O functions:&n; *&n; * TITAN, a 21??? PCI/memory support chipset for the EV6 (21264)&n; * can only use linear accesses to get at PCI/AGP memory and I/O spaces.&n; */
DECL|macro|vucp
mdefine_line|#define vucp&t;volatile unsigned char *
DECL|macro|vusp
mdefine_line|#define vusp&t;volatile unsigned short *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int *
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long *
DECL|function|titan_inb
id|__EXTERN_INLINE
r_int
r_int
id|titan_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
multiline_comment|/* ??? I wish I could get rid of this.  But there&squot;s no ioremap&n;&t;   equivalent for I/O space.  PCI I/O can be forced into the&n;&t;   correct hose&squot;s I/O region, but that doesn&squot;t take care of&n;&t;   legacy ISA crap.  */
id|addr
op_add_assign
id|TITAN_IO_BIAS
suffix:semicolon
r_return
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|titan_outb
id|__EXTERN_INLINE
r_void
id|titan_outb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|addr
op_add_assign
id|TITAN_IO_BIAS
suffix:semicolon
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|titan_inw
id|__EXTERN_INLINE
r_int
r_int
id|titan_inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|addr
op_add_assign
id|TITAN_IO_BIAS
suffix:semicolon
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
DECL|function|titan_outw
id|__EXTERN_INLINE
r_void
id|titan_outw
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|addr
op_add_assign
id|TITAN_IO_BIAS
suffix:semicolon
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
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|titan_inl
id|__EXTERN_INLINE
r_int
r_int
id|titan_inl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|addr
op_add_assign
id|TITAN_IO_BIAS
suffix:semicolon
r_return
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
)brace
DECL|function|titan_outl
id|__EXTERN_INLINE
r_void
id|titan_outl
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|addr
op_add_assign
id|TITAN_IO_BIAS
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|addr
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory functions.  all accesses are done through linear space.&n; */
DECL|function|titan_ioremap
id|__EXTERN_INLINE
r_int
r_int
id|titan_ioremap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
op_plus
id|TITAN_MEM_BIAS
suffix:semicolon
)brace
DECL|function|titan_is_ioaddr
id|__EXTERN_INLINE
r_int
id|titan_is_ioaddr
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
id|TITAN_BASE
suffix:semicolon
)brace
DECL|function|titan_readb
id|__EXTERN_INLINE
r_int
r_int
id|titan_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|titan_readw
id|__EXTERN_INLINE
r_int
r_int
id|titan_readw
c_func
(paren
r_int
r_int
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
DECL|function|titan_readl
id|__EXTERN_INLINE
r_int
r_int
id|titan_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
)brace
DECL|function|titan_readq
id|__EXTERN_INLINE
r_int
r_int
id|titan_readq
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vulp
)paren
id|addr
suffix:semicolon
)brace
DECL|function|titan_writeb
id|__EXTERN_INLINE
r_void
id|titan_writeb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|titan_writew
id|__EXTERN_INLINE
r_void
id|titan_writew
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
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
DECL|function|titan_writel
id|__EXTERN_INLINE
r_void
id|titan_writel
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vuip
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|titan_writeq
id|__EXTERN_INLINE
r_void
id|titan_writeq
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vulp
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|macro|vucp
macro_line|#undef vucp
DECL|macro|vusp
macro_line|#undef vusp
DECL|macro|vuip
macro_line|#undef vuip
DECL|macro|vulp
macro_line|#undef vulp
macro_line|#ifdef __WANT_IO_DEF
DECL|macro|__inb
mdefine_line|#define __inb&t;&t;titan_inb
DECL|macro|__inw
mdefine_line|#define __inw&t;&t;titan_inw
DECL|macro|__inl
mdefine_line|#define __inl&t;&t;titan_inl
DECL|macro|__outb
mdefine_line|#define __outb&t;&t;titan_outb
DECL|macro|__outw
mdefine_line|#define __outw&t;&t;titan_outw
DECL|macro|__outl
mdefine_line|#define __outl&t;&t;titan_outl
DECL|macro|__readb
mdefine_line|#define __readb&t;&t;titan_readb
DECL|macro|__readw
mdefine_line|#define __readw&t;&t;titan_readw
DECL|macro|__writeb
mdefine_line|#define __writeb&t;titan_writeb
DECL|macro|__writew
mdefine_line|#define __writew&t;titan_writew
DECL|macro|__readl
mdefine_line|#define __readl&t;&t;titan_readl
DECL|macro|__readq
mdefine_line|#define __readq&t;&t;titan_readq
DECL|macro|__writel
mdefine_line|#define __writel&t;titan_writel
DECL|macro|__writeq
mdefine_line|#define __writeq&t;titan_writeq
DECL|macro|__ioremap
mdefine_line|#define __ioremap&t;titan_ioremap
DECL|macro|__is_ioaddr
mdefine_line|#define __is_ioaddr&t;titan_is_ioaddr
DECL|macro|inb
mdefine_line|#define inb(port) &t;__inb((port))
DECL|macro|inw
mdefine_line|#define inw(port) &t;__inw((port))
DECL|macro|inl
mdefine_line|#define inl(port) &t;__inl((port))
DECL|macro|outb
mdefine_line|#define outb(v, port) &t;__outb((v),(port))
DECL|macro|outw
mdefine_line|#define outw(v, port) &t;__outw((v),(port))
DECL|macro|outl
mdefine_line|#define outl(v, port) &t;__outl((v),(port))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(a)&t;&t;__readb((unsigned long)(a))
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(a)&t;&t;__readw((unsigned long)(a))
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(a)&t;&t;__readl((unsigned long)(a))
DECL|macro|__raw_readq
mdefine_line|#define __raw_readq(a)&t;&t;__readq((unsigned long)(a))
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb(v,a)&t;__writeb((v),(unsigned long)(a))
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(v,a)&t;__writew((v),(unsigned long)(a))
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(v,a)&t;__writel((v),(unsigned long)(a))
DECL|macro|__raw_writeq
mdefine_line|#define __raw_writeq(v,a)&t;__writeq((v),(unsigned long)(a))
macro_line|#endif /* __WANT_IO_DEF */
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_TITAN__H__ */
eof
