multiline_comment|/*&n; *  linux/include/asm/traps.h&n; *&n; *  Copyright (C) 1993        Hamish Macdonald&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _M68K_TRAPS_H
DECL|macro|_M68K_TRAPS_H
mdefine_line|#define _M68K_TRAPS_H
macro_line|#ifndef __ASSEMBLY__
DECL|typedef|e_vector
r_typedef
r_void
(paren
op_star
id|e_vector
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
id|e_vector
id|vectors
(braket
)braket
suffix:semicolon
macro_line|#endif
DECL|macro|VEC_BUSERR
mdefine_line|#define VEC_BUSERR  (2)
DECL|macro|VEC_ADDRERR
mdefine_line|#define VEC_ADDRERR (3)
DECL|macro|VEC_ILLEGAL
mdefine_line|#define VEC_ILLEGAL (4)
DECL|macro|VEC_ZERODIV
mdefine_line|#define VEC_ZERODIV (5)
DECL|macro|VEC_CHK
mdefine_line|#define VEC_CHK     (6)
DECL|macro|VEC_TRAP
mdefine_line|#define VEC_TRAP    (7)
DECL|macro|VEC_PRIV
mdefine_line|#define VEC_PRIV    (8)
DECL|macro|VEC_TRACE
mdefine_line|#define VEC_TRACE   (9)
DECL|macro|VEC_LINE10
mdefine_line|#define VEC_LINE10  (10)
DECL|macro|VEC_LINE11
mdefine_line|#define VEC_LINE11  (11)
DECL|macro|VEC_RESV1
mdefine_line|#define VEC_RESV1   (12)
DECL|macro|VEC_COPROC
mdefine_line|#define VEC_COPROC  (13)
DECL|macro|VEC_FORMAT
mdefine_line|#define VEC_FORMAT  (14)
DECL|macro|VEC_UNINT
mdefine_line|#define VEC_UNINT   (15)
DECL|macro|VEC_SPUR
mdefine_line|#define VEC_SPUR    (24)
DECL|macro|VEC_INT1
mdefine_line|#define VEC_INT1    (25)
DECL|macro|VEC_INT2
mdefine_line|#define VEC_INT2    (26)
DECL|macro|VEC_INT3
mdefine_line|#define VEC_INT3    (27)
DECL|macro|VEC_INT4
mdefine_line|#define VEC_INT4    (28)
DECL|macro|VEC_INT5
mdefine_line|#define VEC_INT5    (29)
DECL|macro|VEC_INT6
mdefine_line|#define VEC_INT6    (30)
DECL|macro|VEC_INT7
mdefine_line|#define VEC_INT7    (31)
DECL|macro|VEC_SYS
mdefine_line|#define VEC_SYS     (32)
DECL|macro|VEC_TRAP1
mdefine_line|#define VEC_TRAP1   (33)
DECL|macro|VEC_TRAP2
mdefine_line|#define VEC_TRAP2   (34)
DECL|macro|VEC_TRAP3
mdefine_line|#define VEC_TRAP3   (35)
DECL|macro|VEC_TRAP4
mdefine_line|#define VEC_TRAP4   (36)
DECL|macro|VEC_TRAP5
mdefine_line|#define VEC_TRAP5   (37)
DECL|macro|VEC_TRAP6
mdefine_line|#define VEC_TRAP6   (38)
DECL|macro|VEC_TRAP7
mdefine_line|#define VEC_TRAP7   (39)
DECL|macro|VEC_TRAP8
mdefine_line|#define VEC_TRAP8   (40)
DECL|macro|VEC_TRAP9
mdefine_line|#define VEC_TRAP9   (41)
DECL|macro|VEC_TRAP10
mdefine_line|#define VEC_TRAP10  (42)
DECL|macro|VEC_TRAP11
mdefine_line|#define VEC_TRAP11  (43)
DECL|macro|VEC_TRAP12
mdefine_line|#define VEC_TRAP12  (44)
DECL|macro|VEC_TRAP13
mdefine_line|#define VEC_TRAP13  (45)
DECL|macro|VEC_TRAP14
mdefine_line|#define VEC_TRAP14  (46)
DECL|macro|VEC_TRAP15
mdefine_line|#define VEC_TRAP15  (47)
DECL|macro|VEC_FPBRUC
mdefine_line|#define VEC_FPBRUC  (48)
DECL|macro|VEC_FPIR
mdefine_line|#define VEC_FPIR    (49)
DECL|macro|VEC_FPDIVZ
mdefine_line|#define VEC_FPDIVZ  (50)
DECL|macro|VEC_FPUNDER
mdefine_line|#define VEC_FPUNDER (51)
DECL|macro|VEC_FPOE
mdefine_line|#define VEC_FPOE    (52)
DECL|macro|VEC_FPOVER
mdefine_line|#define VEC_FPOVER  (53)
DECL|macro|VEC_FPNAN
mdefine_line|#define VEC_FPNAN   (54)
DECL|macro|VEC_FPUNSUP
mdefine_line|#define VEC_FPUNSUP (55)
DECL|macro|VEC_UNIMPEA
mdefine_line|#define&t;VEC_UNIMPEA (60)
DECL|macro|VEC_UNIMPII
mdefine_line|#define&t;VEC_UNIMPII (61)
DECL|macro|VEC_USER
mdefine_line|#define VEC_USER    (64)
DECL|macro|VECOFF
mdefine_line|#define VECOFF(vec) ((vec)&lt;&lt;2)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Status register bits */
DECL|macro|PS_T
mdefine_line|#define PS_T  (0x8000)
DECL|macro|PS_S
mdefine_line|#define PS_S  (0x2000)
DECL|macro|PS_M
mdefine_line|#define PS_M  (0x1000)
DECL|macro|PS_C
mdefine_line|#define PS_C  (0x0001)
multiline_comment|/* bits for 68020/68030 special status word */
DECL|macro|FC
mdefine_line|#define FC    (0x8000)
DECL|macro|FB
mdefine_line|#define FB    (0x4000)
DECL|macro|RC
mdefine_line|#define RC    (0x2000)
DECL|macro|RB
mdefine_line|#define RB    (0x1000)
DECL|macro|DF
mdefine_line|#define DF    (0x0100)
DECL|macro|RM
mdefine_line|#define RM    (0x0080)
DECL|macro|RW
mdefine_line|#define RW    (0x0040)
DECL|macro|SZ
mdefine_line|#define SZ    (0x0030)
DECL|macro|DFC
mdefine_line|#define DFC   (0x0007)
multiline_comment|/* bits for 68030 MMU status register (mmusr,psr) */
DECL|macro|MMU_B
mdefine_line|#define MMU_B&t;     (0x8000)    /* bus error */
DECL|macro|MMU_L
mdefine_line|#define MMU_L&t;     (0x4000)    /* limit violation */
DECL|macro|MMU_S
mdefine_line|#define MMU_S&t;     (0x2000)    /* supervisor violation */
DECL|macro|MMU_WP
mdefine_line|#define MMU_WP&t;     (0x0800)    /* write-protected */
DECL|macro|MMU_I
mdefine_line|#define MMU_I&t;     (0x0400)    /* invalid descriptor */
DECL|macro|MMU_M
mdefine_line|#define MMU_M&t;     (0x0200)    /* ATC entry modified */
DECL|macro|MMU_T
mdefine_line|#define MMU_T&t;     (0x0040)    /* transparent translation */
DECL|macro|MMU_NUM
mdefine_line|#define MMU_NUM      (0x0007)    /* number of levels traversed */
multiline_comment|/* bits for 68040 special status word */
DECL|macro|CP_040
mdefine_line|#define CP_040&t;(0x8000)
DECL|macro|CU_040
mdefine_line|#define CU_040&t;(0x4000)
DECL|macro|CT_040
mdefine_line|#define CT_040&t;(0x2000)
DECL|macro|CM_040
mdefine_line|#define CM_040&t;(0x1000)
DECL|macro|MA_040
mdefine_line|#define MA_040&t;(0x0800)
DECL|macro|ATC_040
mdefine_line|#define ATC_040 (0x0400)
DECL|macro|LK_040
mdefine_line|#define LK_040&t;(0x0200)
DECL|macro|RW_040
mdefine_line|#define RW_040&t;(0x0100)
DECL|macro|SIZ_040
mdefine_line|#define SIZ_040 (0x0060)
DECL|macro|TT_040
mdefine_line|#define TT_040&t;(0x0018)
DECL|macro|TM_040
mdefine_line|#define TM_040&t;(0x0007)
multiline_comment|/* bits for 68040 write back status word */
DECL|macro|WBV_040
mdefine_line|#define WBV_040   (0x80)
DECL|macro|WBSIZ_040
mdefine_line|#define WBSIZ_040 (0x60)
DECL|macro|WBBYT_040
mdefine_line|#define WBBYT_040 (0x20)
DECL|macro|WBWRD_040
mdefine_line|#define WBWRD_040 (0x40)
DECL|macro|WBLNG_040
mdefine_line|#define WBLNG_040 (0x00)
DECL|macro|WBTT_040
mdefine_line|#define WBTT_040  (0x18)
DECL|macro|WBTM_040
mdefine_line|#define WBTM_040  (0x07)
multiline_comment|/* bus access size codes */
DECL|macro|BA_SIZE_BYTE
mdefine_line|#define BA_SIZE_BYTE    (0x20)
DECL|macro|BA_SIZE_WORD
mdefine_line|#define BA_SIZE_WORD    (0x40)
DECL|macro|BA_SIZE_LONG
mdefine_line|#define BA_SIZE_LONG    (0x00)
DECL|macro|BA_SIZE_LINE
mdefine_line|#define BA_SIZE_LINE    (0x60)
multiline_comment|/* bus access transfer type codes */
DECL|macro|BA_TT_MOVE16
mdefine_line|#define BA_TT_MOVE16    (0x08)
multiline_comment|/* bits for 68040 MMU status register (mmusr) */
DECL|macro|MMU_B_040
mdefine_line|#define MMU_B_040   (0x0800)
DECL|macro|MMU_G_040
mdefine_line|#define MMU_G_040   (0x0400)
DECL|macro|MMU_S_040
mdefine_line|#define MMU_S_040   (0x0080)
DECL|macro|MMU_CM_040
mdefine_line|#define MMU_CM_040  (0x0060)
DECL|macro|MMU_M_040
mdefine_line|#define MMU_M_040   (0x0010)
DECL|macro|MMU_WP_040
mdefine_line|#define MMU_WP_040  (0x0004)
DECL|macro|MMU_T_040
mdefine_line|#define MMU_T_040   (0x0002)
DECL|macro|MMU_R_040
mdefine_line|#define MMU_R_040   (0x0001)
multiline_comment|/* bits in the 68060 fault status long word (FSLW) */
DECL|macro|MMU060_MA
mdefine_line|#define&t;MMU060_MA&t;(0x08000000)&t;/* misaligned */
DECL|macro|MMU060_LK
mdefine_line|#define&t;MMU060_LK&t;(0x02000000)&t;/* locked transfer */
DECL|macro|MMU060_RW
mdefine_line|#define&t;MMU060_RW&t;(0x01800000)&t;/* read/write */
DECL|macro|MMU060_RW_W
macro_line|# define MMU060_RW_W&t;(0x00800000)&t;/* write */
DECL|macro|MMU060_RW_R
macro_line|# define MMU060_RW_R&t;(0x01000000)&t;/* read */
DECL|macro|MMU060_RW_RMW
macro_line|# define MMU060_RW_RMW&t;(0x01800000)&t;/* read/modify/write */
DECL|macro|MMU060_W
macro_line|# define MMU060_W&t;(0x00800000)&t;/* general write, includes rmw */
DECL|macro|MMU060_SIZ
mdefine_line|#define&t;MMU060_SIZ&t;(0x00600000)&t;/* transfer size */
DECL|macro|MMU060_TT
mdefine_line|#define&t;MMU060_TT&t;(0x00180000)&t;/* transfer type (TT) bits */
DECL|macro|MMU060_TM
mdefine_line|#define&t;MMU060_TM&t;(0x00070000)&t;/* transfer modifier (TM) bits */
DECL|macro|MMU060_IO
mdefine_line|#define&t;MMU060_IO&t;(0x00008000)&t;/* instruction or operand */
DECL|macro|MMU060_PBE
mdefine_line|#define&t;MMU060_PBE&t;(0x00004000)&t;/* push buffer bus error */
DECL|macro|MMU060_SBE
mdefine_line|#define&t;MMU060_SBE&t;(0x00002000)&t;/* store buffer bus error */
DECL|macro|MMU060_PTA
mdefine_line|#define&t;MMU060_PTA&t;(0x00001000)&t;/* pointer A fault */
DECL|macro|MMU060_PTB
mdefine_line|#define&t;MMU060_PTB&t;(0x00000800)&t;/* pointer B fault */
DECL|macro|MMU060_IL
mdefine_line|#define&t;MMU060_IL&t;(0x00000400)&t;/* double indirect descr fault */
DECL|macro|MMU060_PF
mdefine_line|#define&t;MMU060_PF&t;(0x00000200)&t;/* page fault (invalid descr) */
DECL|macro|MMU060_SP
mdefine_line|#define&t;MMU060_SP&t;(0x00000100)&t;/* supervisor protection */
DECL|macro|MMU060_WP
mdefine_line|#define&t;MMU060_WP&t;(0x00000080)&t;/* write protection */
DECL|macro|MMU060_TWE
mdefine_line|#define&t;MMU060_TWE&t;(0x00000040)&t;/* bus error on table search */
DECL|macro|MMU060_RE
mdefine_line|#define&t;MMU060_RE&t;(0x00000020)&t;/* bus error on read */
DECL|macro|MMU060_WE
mdefine_line|#define&t;MMU060_WE&t;(0x00000010)&t;/* bus error on write */
DECL|macro|MMU060_TTR
mdefine_line|#define&t;MMU060_TTR&t;(0x00000008)&t;/* error caused by TTR translation */
DECL|macro|MMU060_BPE
mdefine_line|#define&t;MMU060_BPE&t;(0x00000004)&t;/* branch prediction error */
DECL|macro|MMU060_SEE
mdefine_line|#define&t;MMU060_SEE&t;(0x00000001)&t;/* software emulated error */
multiline_comment|/* cases of missing or invalid descriptors */
DECL|macro|MMU060_DESC_ERR
mdefine_line|#define MMU060_DESC_ERR (MMU060_PTA | MMU060_PTB | &bslash;&n;&t;&t;&t; MMU060_IL  | MMU060_PF)
multiline_comment|/* bits that indicate real errors */
DECL|macro|MMU060_ERR_BITS
mdefine_line|#define MMU060_ERR_BITS (MMU060_PBE | MMU060_SBE | MMU060_DESC_ERR | MMU060_SP | &bslash;&n;&t;&t;&t; MMU060_WP  | MMU060_TWE | MMU060_RE       | MMU060_WE)
multiline_comment|/* structure for stack frames */
DECL|struct|frame
r_struct
id|frame
(brace
DECL|member|ptregs
r_struct
id|pt_regs
id|ptregs
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|iaddr
r_int
r_int
id|iaddr
suffix:semicolon
multiline_comment|/* instruction address */
DECL|member|fmt2
)brace
id|fmt2
suffix:semicolon
r_struct
(brace
DECL|member|effaddr
r_int
r_int
id|effaddr
suffix:semicolon
multiline_comment|/* effective address */
DECL|member|fmt3
)brace
id|fmt3
suffix:semicolon
r_struct
(brace
DECL|member|effaddr
r_int
r_int
id|effaddr
suffix:semicolon
multiline_comment|/* effective address */
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/* pc of faulted instr */
DECL|member|fmt4
)brace
id|fmt4
suffix:semicolon
r_struct
(brace
DECL|member|effaddr
r_int
r_int
id|effaddr
suffix:semicolon
multiline_comment|/* effective address */
DECL|member|ssw
r_int
r_int
id|ssw
suffix:semicolon
multiline_comment|/* special status word */
DECL|member|wb3s
r_int
r_int
id|wb3s
suffix:semicolon
multiline_comment|/* write back 3 status */
DECL|member|wb2s
r_int
r_int
id|wb2s
suffix:semicolon
multiline_comment|/* write back 2 status */
DECL|member|wb1s
r_int
r_int
id|wb1s
suffix:semicolon
multiline_comment|/* write back 1 status */
DECL|member|faddr
r_int
r_int
id|faddr
suffix:semicolon
multiline_comment|/* fault address */
DECL|member|wb3a
r_int
r_int
id|wb3a
suffix:semicolon
multiline_comment|/* write back 3 address */
DECL|member|wb3d
r_int
r_int
id|wb3d
suffix:semicolon
multiline_comment|/* write back 3 data */
DECL|member|wb2a
r_int
r_int
id|wb2a
suffix:semicolon
multiline_comment|/* write back 2 address */
DECL|member|wb2d
r_int
r_int
id|wb2d
suffix:semicolon
multiline_comment|/* write back 2 data */
DECL|member|wb1a
r_int
r_int
id|wb1a
suffix:semicolon
multiline_comment|/* write back 1 address */
DECL|member|wb1dpd0
r_int
r_int
id|wb1dpd0
suffix:semicolon
multiline_comment|/* write back 1 data/push data 0*/
DECL|member|pd1
r_int
r_int
id|pd1
suffix:semicolon
multiline_comment|/* push data 1*/
DECL|member|pd2
r_int
r_int
id|pd2
suffix:semicolon
multiline_comment|/* push data 2*/
DECL|member|pd3
r_int
r_int
id|pd3
suffix:semicolon
multiline_comment|/* push data 3*/
DECL|member|fmt7
)brace
id|fmt7
suffix:semicolon
r_struct
(brace
DECL|member|iaddr
r_int
r_int
id|iaddr
suffix:semicolon
multiline_comment|/* instruction address */
DECL|member|int1
r_int
r_int
id|int1
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* internal registers */
DECL|member|fmt9
)brace
id|fmt9
suffix:semicolon
r_struct
(brace
DECL|member|int1
r_int
r_int
id|int1
suffix:semicolon
DECL|member|ssw
r_int
r_int
id|ssw
suffix:semicolon
multiline_comment|/* special status word */
DECL|member|isc
r_int
r_int
id|isc
suffix:semicolon
multiline_comment|/* instruction stage c */
DECL|member|isb
r_int
r_int
id|isb
suffix:semicolon
multiline_comment|/* instruction stage b */
DECL|member|daddr
r_int
r_int
id|daddr
suffix:semicolon
multiline_comment|/* data cycle fault address */
DECL|member|int2
r_int
r_int
id|int2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|dobuf
r_int
r_int
id|dobuf
suffix:semicolon
multiline_comment|/* data cycle output buffer */
DECL|member|int3
r_int
r_int
id|int3
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|fmta
)brace
id|fmta
suffix:semicolon
r_struct
(brace
DECL|member|int1
r_int
r_int
id|int1
suffix:semicolon
DECL|member|ssw
r_int
r_int
id|ssw
suffix:semicolon
multiline_comment|/* special status word */
DECL|member|isc
r_int
r_int
id|isc
suffix:semicolon
multiline_comment|/* instruction stage c */
DECL|member|isb
r_int
r_int
id|isb
suffix:semicolon
multiline_comment|/* instruction stage b */
DECL|member|daddr
r_int
r_int
id|daddr
suffix:semicolon
multiline_comment|/* data cycle fault address */
DECL|member|int2
r_int
r_int
id|int2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|dobuf
r_int
r_int
id|dobuf
suffix:semicolon
multiline_comment|/* data cycle output buffer */
DECL|member|int3
r_int
r_int
id|int3
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|baddr
r_int
r_int
id|baddr
suffix:semicolon
multiline_comment|/* stage B address */
DECL|member|int4
r_int
r_int
id|int4
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|dibuf
r_int
r_int
id|dibuf
suffix:semicolon
multiline_comment|/* data cycle input buffer */
DECL|member|int5
r_int
r_int
id|int5
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ver
r_int
id|ver
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* stack frame version # */
DECL|member|int6
r_int
id|int6
suffix:colon
l_int|12
suffix:semicolon
DECL|member|int7
r_int
r_int
id|int7
(braket
l_int|18
)braket
suffix:semicolon
DECL|member|fmtb
)brace
id|fmtb
suffix:semicolon
DECL|member|un
)brace
id|un
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _M68K_TRAPS_H */
eof
