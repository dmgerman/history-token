multiline_comment|/**************************************************************************&n; *                                                                        *&n; *  Copyright (C) 2001 Silicon Graphics, Inc. All rights reserved.        *&n; *                                                                        *&n; *  These coded instructions, statements, and computer programs  contain  *&n; *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *&n; *  are protected by Federal copyright law.  They  may  not be disclosed  *&n; *  to  third  parties  or copied or duplicated in any form, in whole or  *&n; *  in part, without the prior written consent of Silicon Graphics, Inc.  *&n; *                                                                        *&n; **************************************************************************/
macro_line|#ifndef _SHUB_MD_H
DECL|macro|_SHUB_MD_H
mdefine_line|#define _SHUB_MD_H
multiline_comment|/* SN2 supports a mostly-flat address space with 4 CPU-visible, evenly spaced, &n;   contiguous regions, or &quot;software banks&quot;.  On SN2, software bank n begins at &n;   addresses n * 16GB, 0 &lt;= n &lt; 4.  Each bank has a 16GB address space.  If &n;   the 4 dimms do not use up this space there will be holes between the &n;   banks.  Even with these holes the whole memory space within a bank is&n;   not addressable address space.  The top 1/32 of each bank is directory&n;   memory space and is accessible through bist only.&n;&n;   Physically a SN2 node board contains 2 daughter cards with 8 dimm sockets&n;   each.  A total of 16 dimm sockets arranged as 4 &quot;DIMM banks&quot; of 4 dimms &n;   each.  The data is stripped across the 4 memory busses so all dimms within &n;   a dimm bank must have identical capacity dimms.  Memory is increased or &n;   decreased in sets of 4.  Each dimm bank has 2 dimms on each side.&n;&n;             Physical Dimm Bank layout.&n;                  DTR Card0&n;                 ------------&n;   Dimm Bank 3   |  MemYL3  |   CS 3&n;                 |  MemXL3  |&n;                 |----------|&n;   Dimm Bank 2   |  MemYL2  |   CS 2&n;                 |  MemXL2  |&n;                 |----------|&n;   Dimm Bank 1   |  MemYL1  |   CS 1&n;                 |  MemXL1  |&n;                 |----------|&n;   Dimm Bank 0   |  MemYL0  |   CS 0 &n;                 |  MemXL0  |&n;                 ------------&n;                  |       |&n;                  BUS     BUS&n;                  XL      YL&n;                  |       |&n;                 ------------&n;                 |   SHUB   |&n;                 |    MD    |&n;                 ------------&n;                  |       |&n;                  BUS     BUS&n;                  XR      YR&n;                  |       |&n;                 ------------&n;   Dimm Bank 0   |  MemXR0  |   CS 0&n;                 |  MemYR0  |&n;                 |----------|&n;   Dimm Bank 1   |  MemXR1  |   CS 1&n;                 |  MemYR1  |&n;                 |----------|&n;   Dimm Bank 2   |  MemXR2  |   CS 2&n;                 |  MemYR2  |&n;                 |----------|&n;   Dimm Bank 3   |  MemXR3  |   CS 3&n;                 |  MemYR3  |&n;                 ------------&n;                  DTR Card1&n;&n;   The dimms can be 1 or 2 sided dimms.  The size and bankness is defined  &n;   separately for each dimm bank in the sh_[x,y,jnr]_dimm_cfg MMR register.&n;&n;   Normally software bank 0 would map directly to physical dimm bank 0.  The &n;   software banks can map to the different physical dimm banks via the &n;   DIMM[0-3]_CS field in SH_[x,y,jnr]_DIMM_CFG for each dimm slot.   &n;&n;   All the PROM&squot;s data structures (promlog variables, klconfig, etc.)&n;   track memory by the physical dimm bank number.  The kernel usually&n;   tracks memory by the software bank number.&n;&n; */
multiline_comment|/* Preprocessor macros */
DECL|macro|MD_MEM_BANKS
mdefine_line|#define MD_MEM_BANKS&t;&t;4
DECL|macro|MD_PHYS_BANKS_PER_DIMM
mdefine_line|#define MD_PHYS_BANKS_PER_DIMM  2                  /* dimms may be 2 sided. */
DECL|macro|MD_NUM_PHYS_BANKS
mdefine_line|#define MD_NUM_PHYS_BANKS       (MD_MEM_BANKS * MD_PHYS_BANKS_PER_DIMM)
DECL|macro|MD_DIMMS_IN_SLOT
mdefine_line|#define MD_DIMMS_IN_SLOT&t;4  /* 4 dimms in each dimm bank.  aka slot */
multiline_comment|/* Address bits 35,34 control dimm bank access. */
DECL|macro|MD_BANK_SHFT
mdefine_line|#define MD_BANK_SHFT       &t;34     
DECL|macro|MD_BANK_MASK
mdefine_line|#define MD_BANK_MASK       &t;(UINT64_CAST 0x3 &lt;&lt; MD_BANK_SHFT )
DECL|macro|MD_BANK_GET
mdefine_line|#define MD_BANK_GET(addr)  &t;(((addr) &amp; MD_BANK_MASK) &gt;&gt; MD_BANK_SHFT)
DECL|macro|MD_BANK_SIZE
mdefine_line|#define MD_BANK_SIZE       &t;(UINT64_CAST 0x1 &lt;&lt; MD_BANK_SHFT ) /* 16 gb */
DECL|macro|MD_BANK_OFFSET
mdefine_line|#define MD_BANK_OFFSET(_b) &t;(UINT64_CAST (_b) &lt;&lt; MD_BANK_SHFT)
multiline_comment|/*Address bit 12 selects side of dimm if 2bnk dimms present. */
DECL|macro|MD_PHYS_BANK_SEL_SHFT
mdefine_line|#define MD_PHYS_BANK_SEL_SHFT   12
DECL|macro|MD_PHYS_BANK_SEL_MASK
mdefine_line|#define MD_PHYS_BANK_SEL_MASK   (UINT64_CAST 0x1 &lt;&lt; MD_PHYS_BANK_SEL_SHFT)
multiline_comment|/* Address bit 7 determines if data resides on X or Y memory system. &n; * If addr Bit 7 is set the data resides on Y memory system and&n; * the corresponing directory entry reside on the X. &n; */
DECL|macro|MD_X_OR_Y_SEL_SHFT
mdefine_line|#define MD_X_OR_Y_SEL_SHFT&t;7&t;
DECL|macro|MD_X_OR_Y_SEL_MASK
mdefine_line|#define MD_X_OR_Y_SEL_MASK&t;(1 &lt;&lt; MD_X_OR_Y_SEL_SHFT)&t;
multiline_comment|/* Address bit 8 determines which directory entry of the pair the address&n; * corresponds to.  If addr Bit 8 is set DirB corresponds to the memory address.&n; */
DECL|macro|MD_DIRA_OR_DIRB_SEL_SHFT
mdefine_line|#define MD_DIRA_OR_DIRB_SEL_SHFT&t;8
DECL|macro|MD_DIRA_OR_DIRB_SEL_MASK
mdefine_line|#define MD_DIRA_OR_DIRB_SEL_MASK  &t;(1 &lt;&lt; MD_DIRA_OR_DIRB_SEL_SHFT)&t;
multiline_comment|/* Address bit 11 determines if corresponding directory entry resides &n; * on Left or Right memory bus.  If addr Bit 11 is set the corresponding &n; * directory entry resides on Right memory bus.&n; */
DECL|macro|MD_L_OR_R_SEL_SHFT
mdefine_line|#define MD_L_OR_R_SEL_SHFT&t;11
DECL|macro|MD_L_OR_R_SEL_MASK
mdefine_line|#define MD_L_OR_R_SEL_MASK&t;(1 &lt;&lt; MD_L_OR_R_SEL_SHFT)&t;
multiline_comment|/* DRAM sizes. */
DECL|macro|MD_SZ_64_Mb
mdefine_line|#define MD_SZ_64_Mb&t;&t;0x0
DECL|macro|MD_SZ_128_Mb
mdefine_line|#define MD_SZ_128_Mb&t;&t;0x1
DECL|macro|MD_SZ_256_Mb
mdefine_line|#define MD_SZ_256_Mb&t;&t;0x2
DECL|macro|MD_SZ_512_Mb
mdefine_line|#define MD_SZ_512_Mb&t;&t;0x3
DECL|macro|MD_SZ_1024_Mb
mdefine_line|#define MD_SZ_1024_Mb&t;&t;0x4
DECL|macro|MD_SZ_2048_Mb
mdefine_line|#define MD_SZ_2048_Mb&t; &t;0x5
DECL|macro|MD_SZ_UNUSED
mdefine_line|#define MD_SZ_UNUSED&t;&t;0x7
DECL|macro|MD_DIMM_SIZE_BYTES
mdefine_line|#define MD_DIMM_SIZE_BYTES(_size, _2bk) (&t;&t;&t;&t; &bslash;&n;&t;&t;( (_size) == 7 ? 0 : ( 0x4000000L &lt;&lt; (_size)) &lt;&lt; (_2bk)))&bslash;&n;
DECL|macro|MD_DIMM_SIZE_MBYTES
mdefine_line|#define MD_DIMM_SIZE_MBYTES(_size, _2bk) (&t;&t;&t;&t; &bslash;&n;&t; &t;( (_size) == 7 ? 0 : ( 0x40L &lt;&lt; (_size) ) &lt;&lt; (_2bk)))  &t; &bslash;&n;
multiline_comment|/* The top 1/32 of each bank is directory memory, and not accessable&n; * via normal reads and writes */
DECL|macro|MD_DIMM_USER_SIZE
mdefine_line|#define MD_DIMM_USER_SIZE(_size)&t;((_size) * 31 / 32)
multiline_comment|/* Minimum size of a populated bank is 64M (62M usable) */
DECL|macro|MIN_BANK_SIZE
mdefine_line|#define MIN_BANK_SIZE&t;&t;MD_DIMM_USER_SIZE((64 * 0x100000))
DECL|macro|MIN_BANK_STRING
mdefine_line|#define MIN_BANK_STRING&t;&t;&quot;62&quot;
multiline_comment|/*Possible values for FREQ field in sh_[x,y,jnr]_dimm_cfg regs */
DECL|macro|MD_DIMM_100_CL2_0
mdefine_line|#define MD_DIMM_100_CL2_0 &t;0x0
DECL|macro|MD_DIMM_133_CL2_0
mdefine_line|#define MD_DIMM_133_CL2_0 &t;0x1
DECL|macro|MD_DIMM_133_CL2_5
mdefine_line|#define MD_DIMM_133_CL2_5 &t;0x2
DECL|macro|MD_DIMM_160_CL2_0
mdefine_line|#define MD_DIMM_160_CL2_0 &t;0x3
DECL|macro|MD_DIMM_160_CL2_5
mdefine_line|#define MD_DIMM_160_CL2_5 &t;0x4
DECL|macro|MD_DIMM_160_CL3_0
mdefine_line|#define MD_DIMM_160_CL3_0 &t;0x5
DECL|macro|MD_DIMM_200_CL2_0
mdefine_line|#define MD_DIMM_200_CL2_0 &t;0x6
DECL|macro|MD_DIMM_200_CL2_5
mdefine_line|#define MD_DIMM_200_CL2_5 &t;0x7
DECL|macro|MD_DIMM_200_CL3_0
mdefine_line|#define MD_DIMM_200_CL3_0 &t;0x8
multiline_comment|/* DIMM_CFG fields */
DECL|macro|MD_DIMM_SHFT
mdefine_line|#define MD_DIMM_SHFT(_dimm)&t;((_dimm) &lt;&lt; 3)
DECL|macro|MD_DIMM_SIZE_MASK
mdefine_line|#define MD_DIMM_SIZE_MASK(_dimm)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(SH_JNR_DIMM_CFG_DIMM0_SIZE_MASK &lt;&lt; &t;&t;&t;&bslash;&n;&t;&t;(MD_DIMM_SHFT(_dimm)))
DECL|macro|MD_DIMM_2BK_MASK
mdefine_line|#define MD_DIMM_2BK_MASK(_dimm)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(SH_JNR_DIMM_CFG_DIMM0_2BK_MASK &lt;&lt; &t;&t;&t;&bslash;&n;&t;&t;MD_DIMM_SHFT(_dimm))
DECL|macro|MD_DIMM_REV_MASK
mdefine_line|#define MD_DIMM_REV_MASK(_dimm)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(SH_JNR_DIMM_CFG_DIMM0_REV_MASK &lt;&lt; &t;&t;&t;&bslash;&n;&t;&t;MD_DIMM_SHFT(_dimm))
DECL|macro|MD_DIMM_CS_MASK
mdefine_line|#define MD_DIMM_CS_MASK(_dimm)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(SH_JNR_DIMM_CFG_DIMM0_CS_MASK &lt;&lt; &t;&t;&t;&bslash;&n;&t;&t;MD_DIMM_SHFT(_dimm))
DECL|macro|MD_DIMM_SIZE
mdefine_line|#define MD_DIMM_SIZE(_dimm, _cfg)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((_cfg) &amp; MD_DIMM_SIZE_MASK(_dimm))&t;&t;&t;&bslash;&n;&t;&t;&gt;&gt; (MD_DIMM_SHFT(_dimm)+SH_JNR_DIMM_CFG_DIMM0_SIZE_SHFT))
DECL|macro|MD_DIMM_TWO_SIDED
mdefine_line|#define MD_DIMM_TWO_SIDED(_dimm,_cfg)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;( ((_cfg) &amp; MD_DIMM_2BK_MASK(_dimm))&t;&t;&t;&bslash;&n;&t;&t;&gt;&gt; (MD_DIMM_SHFT(_dimm)+SH_JNR_DIMM_CFG_DIMM0_2BK_SHFT))
DECL|macro|MD_DIMM_REVERSED
mdefine_line|#define MD_DIMM_REVERSED(_dimm,_cfg) &t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((_cfg) &amp; MD_DIMM_REV_MASK(_dimm))&t;&t;&t;&bslash;&n;&t;&t;&gt;&gt; (MD_DIMM_SHFT(_dimm)+SH_JNR_DIMM_CFG_DIMM0_REV_SHFT))
DECL|macro|MD_DIMM_CS
mdefine_line|#define MD_DIMM_CS(_dimm,_cfg)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(((_cfg) &amp; MD_DIMM_CS_MASK(_dimm))&t;&t;&t;&bslash;&n;&t;&t;&gt;&gt; (MD_DIMM_SHFT(_dimm)+SH_JNR_DIMM_CFG_DIMM0_CS_SHFT))
multiline_comment|/* Macros to set MMRs that must be set identically to others. */
DECL|macro|MD_SET_DIMM_CFG
mdefine_line|#define MD_SET_DIMM_CFG(_n, _value) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_X_DIMM_CFG,_value);&t;&t;&t;&bslash;&n;                REMOTE_HUB_S(_n, SH_Y_DIMM_CFG, _value);&t;&t;&bslash;&n;                REMOTE_HUB_S(_n, SH_JNR_DIMM_CFG, _value);}
DECL|macro|MD_SET_DQCT_CFG
mdefine_line|#define MD_SET_DQCT_CFG(_n, _value) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_X_DQCT_CFG,_value);&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_Y_DQCT_CFG,_value); }
DECL|macro|MD_SET_CFG
mdefine_line|#define MD_SET_CFG(_n, _value) {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_X_CFG,_value);&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_Y_CFG,_value);} 
DECL|macro|MD_SET_REFRESH_CONTROL
mdefine_line|#define MD_SET_REFRESH_CONTROL(_n, _value) {&t;&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_X_REFRESH_CONTROL, _value);&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_Y_REFRESH_CONTROL, _value);}
DECL|macro|MD_SET_DQ_MMR_DIR_COFIG
mdefine_line|#define MD_SET_DQ_MMR_DIR_COFIG(_n, _value) {&t;&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_MD_DQLP_MMR_DIR_CONFIG, _value);&t;&bslash;&n;                REMOTE_HUB_S(_n, SH_MD_DQRP_MMR_DIR_CONFIG, _value);}
DECL|macro|MD_SET_PIOWD_DIR_ENTRYS
mdefine_line|#define MD_SET_PIOWD_DIR_ENTRYS(_n, _value) {&t;&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_MD_DQLP_MMR_PIOWD_DIR_ENTRY, _value);&bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_MD_DQRP_MMR_PIOWD_DIR_ENTRY, _value);}
multiline_comment|/* &n; * There are 12 Node Presence MMRs, 4 in each primary DQ and 4 in the&n; * LB.  The data in the left and right DQ MMRs and the LB must match.&n; */
DECL|macro|MD_SET_PRESENT_VEC
mdefine_line|#define MD_SET_PRESENT_VEC(_n, _vec, _value) {&t;&t;&t;&t;   &bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_MD_DQLP_MMR_DIR_PRESVEC0+((_vec)*0x10),&bslash;&n;&t;&t;&t; _value);&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_MD_DQRP_MMR_DIR_PRESVEC0+((_vec)*0x10),&bslash;&n;&t;&t;&t; _value);&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_SHUBS_PRESENT0+((_vec)*0x80), _value);}
multiline_comment|/*&n; * There are 16 Privilege Vector MMRs, 8 in each primary DQ.  The data&n; * in the corresponding left and right DQ MMRs must match.  Each MMR&n; * pair is used for a single partition.&n; */
DECL|macro|MD_SET_PRI_VEC
mdefine_line|#define MD_SET_PRI_VEC(_n, _vec, _value) {&t;&t;&t;&t;  &bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_MD_DQLP_MMR_DIR_PRIVEC0+((_vec)*0x10),&bslash;&n;&t;&t;&t; _value);&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_MD_DQRP_MMR_DIR_PRIVEC0+((_vec)*0x10),&bslash;&n;&t;&t;&t; _value);}
multiline_comment|/*&n; * There are 16 Local/Remote MMRs, 8 in each primary DQ.  The data in&n; * the corresponding left and right DQ MMRs must match.  Each MMR pair&n; * is used for a single partition.&n; */
DECL|macro|MD_SET_LOC_VEC
mdefine_line|#define MD_SET_LOC_VEC(_n, _vec, _value) {&t;&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_MD_DQLP_MMR_DIR_LOCVEC0+((_vec)*0x10),&bslash;&n;&t;&t;&t; _value);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;REMOTE_HUB_S(_n, SH_MD_DQRP_MMR_DIR_LOCVEC0+((_vec)*0x10),&bslash;&n;&t;&t;&t; _value);}
multiline_comment|/* Memory BIST CMDS */
DECL|macro|MD_DIMM_INIT_MODE_SET
mdefine_line|#define MD_DIMM_INIT_MODE_SET&t;0x0
DECL|macro|MD_DIMM_INIT_REFRESH
mdefine_line|#define MD_DIMM_INIT_REFRESH&t;0x1
DECL|macro|MD_DIMM_INIT_PRECHARGE
mdefine_line|#define MD_DIMM_INIT_PRECHARGE&t;0x2
DECL|macro|MD_DIMM_INIT_BURST_TERM
mdefine_line|#define MD_DIMM_INIT_BURST_TERM&t;0x6
DECL|macro|MD_DIMM_INIT_NOP
mdefine_line|#define MD_DIMM_INIT_NOP&t;0x7
DECL|macro|MD_DIMM_BIST_READ
mdefine_line|#define MD_DIMM_BIST_READ&t;0x10
DECL|macro|MD_FILL_DIR
mdefine_line|#define MD_FILL_DIR&t;&t;0x20
DECL|macro|MD_FILL_DATA
mdefine_line|#define MD_FILL_DATA&t;&t;0x30
DECL|macro|MD_FILL_DIR_ACCESS
mdefine_line|#define MD_FILL_DIR_ACCESS&t;0X40
DECL|macro|MD_READ_DIR_PAIR
mdefine_line|#define MD_READ_DIR_PAIR&t;0x50
DECL|macro|MD_READ_DIR_TAG
mdefine_line|#define MD_READ_DIR_TAG&t;&t;0x60
multiline_comment|/* SH_MMRBIST_CTL macros */
DECL|macro|MD_BIST_FAIL
mdefine_line|#define MD_BIST_FAIL(_n) (REMOTE_HUB_L(_n, SH_MMRBIST_CTL) &amp;&t;&t;&bslash;&n;                SH_MMRBIST_CTL_FAIL_MASK)
DECL|macro|MD_BIST_IN_PROGRESS
mdefine_line|#define MD_BIST_IN_PROGRESS(_n) (REMOTE_HUB_L(_n, SH_MMRBIST_CTL) &amp; &t;&bslash;&n;                SH_MMRBIST_CTL_IN_PROGRESS_MASK)
DECL|macro|MD_BIST_MEM_IDLE
mdefine_line|#define MD_BIST_MEM_IDLE(_n); (REMOTE_HUB_L(_n, SH_MMRBIST_CTL) &amp; &t;&bslash;&n;                SH_MMRBIST_CTL_MEM_IDLE_MASK)
multiline_comment|/* SH_MMRBIST_ERR macros */
DECL|macro|MD_BIST_MISCOMPARE
mdefine_line|#define MD_BIST_MISCOMPARE(_n) (REMOTE_HUB_L(_n, SH_MMRBIST_ERR) &amp;&t;&bslash;&n;&t;&t;SH_MMRBIST_ERR_DETECTED_MASK)
macro_line|#endif&t;/* _SHUB_MD_H */
eof
