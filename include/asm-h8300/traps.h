multiline_comment|/*&n; *  linux/include/asm/traps.h&n; *&n; *  Copyright (C) 1993        Hamish Macdonald&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _H8300_TRAPS_H
DECL|macro|_H8300_TRAPS_H
mdefine_line|#define _H8300_TRAPS_H
macro_line|#if 0
macro_line|#ifndef __ASSEMBLY__
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
mdefine_line|#define VEC_BUSERR  (2)
mdefine_line|#define VEC_ADDRERR (3)
mdefine_line|#define VEC_ILLEGAL (4)
mdefine_line|#define VEC_ZERODIV (5)
mdefine_line|#define VEC_CHK     (6)
mdefine_line|#define VEC_TRAP    (7)
mdefine_line|#define VEC_PRIV    (8)
mdefine_line|#define VEC_TRACE   (9)
mdefine_line|#define VEC_LINE10  (10)
mdefine_line|#define VEC_LINE11  (11)
mdefine_line|#define VEC_RESV1   (12)
mdefine_line|#define VEC_COPROC  (13)
mdefine_line|#define VEC_FORMAT  (14)
mdefine_line|#define VEC_UNINT   (15)
mdefine_line|#define VEC_SPUR    (24)
mdefine_line|#define VEC_INT1    (25)
mdefine_line|#define VEC_INT2    (26)
mdefine_line|#define VEC_INT3    (27)
mdefine_line|#define VEC_INT4    (28)
mdefine_line|#define VEC_INT5    (29)
mdefine_line|#define VEC_INT6    (30)
mdefine_line|#define VEC_INT7    (31)
mdefine_line|#define VEC_SYS     (32)
mdefine_line|#define VEC_TRAP1   (33)
mdefine_line|#define VEC_TRAP2   (34)
mdefine_line|#define VEC_TRAP3   (35)
mdefine_line|#define VEC_TRAP4   (36)
mdefine_line|#define VEC_TRAP5   (37)
mdefine_line|#define VEC_TRAP6   (38)
mdefine_line|#define VEC_TRAP7   (39)
mdefine_line|#define VEC_TRAP8   (40)
mdefine_line|#define VEC_TRAP9   (41)
mdefine_line|#define VEC_TRAP10  (42)
mdefine_line|#define VEC_TRAP11  (43)
mdefine_line|#define VEC_TRAP12  (44)
mdefine_line|#define VEC_TRAP13  (45)
mdefine_line|#define VEC_TRAP14  (46)
mdefine_line|#define VEC_TRAP15  (47)
mdefine_line|#define VEC_FPBRUC  (48)
mdefine_line|#define VEC_FPIR    (49)
mdefine_line|#define VEC_FPDIVZ  (50)
mdefine_line|#define VEC_FPUNDER (51)
mdefine_line|#define VEC_FPOE    (52)
mdefine_line|#define VEC_FPOVER  (53)
mdefine_line|#define VEC_FPNAN   (54)
mdefine_line|#define VEC_FPUNSUP (55)
mdefine_line|#define&t;VEC_UNIMPEA (60)
mdefine_line|#define&t;VEC_UNIMPII (61)
mdefine_line|#define VEC_USER    (64)
mdefine_line|#define VECOFF(vec) ((vec)&lt;&lt;2)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Status register bits */
mdefine_line|#define PS_T  (0x8000)
mdefine_line|#define PS_S  (0x2000)
mdefine_line|#define PS_M  (0x1000)
mdefine_line|#define PS_C  (0x0001)
multiline_comment|/* bits for 68020/68030 special status word */
mdefine_line|#define FC    (0x8000)
mdefine_line|#define FB    (0x4000)
mdefine_line|#define RC    (0x2000)
mdefine_line|#define RB    (0x1000)
mdefine_line|#define DF    (0x0100)
mdefine_line|#define RM    (0x0080)
mdefine_line|#define RW    (0x0040)
mdefine_line|#define SZ    (0x0030)
mdefine_line|#define DFC   (0x0007)
multiline_comment|/* bits for 68030 MMU status register (mmusr,psr) */
mdefine_line|#define MMU_B&t;     (0x8000)    /* bus error */
mdefine_line|#define MMU_L&t;     (0x4000)    /* limit violation */
mdefine_line|#define MMU_S&t;     (0x2000)    /* supervisor violation */
mdefine_line|#define MMU_WP&t;     (0x0800)    /* write-protected */
mdefine_line|#define MMU_I&t;     (0x0400)    /* invalid descriptor */
mdefine_line|#define MMU_M&t;     (0x0200)    /* ATC entry modified */
mdefine_line|#define MMU_T&t;     (0x0040)    /* transparent translation */
mdefine_line|#define MMU_NUM      (0x0007)    /* number of levels traversed */
multiline_comment|/* bits for 68040 special status word */
mdefine_line|#define CP_040&t;(0x8000)
mdefine_line|#define CU_040&t;(0x4000)
mdefine_line|#define CT_040&t;(0x2000)
mdefine_line|#define CM_040&t;(0x1000)
mdefine_line|#define MA_040&t;(0x0800)
mdefine_line|#define ATC_040 (0x0400)
mdefine_line|#define LK_040&t;(0x0200)
mdefine_line|#define RW_040&t;(0x0100)
mdefine_line|#define SIZ_040 (0x0060)
mdefine_line|#define TT_040&t;(0x0018)
mdefine_line|#define TM_040&t;(0x0007)
multiline_comment|/* bits for 68040 write back status word */
mdefine_line|#define WBV_040   (0x80)
mdefine_line|#define WBSIZ_040 (0x60)
mdefine_line|#define WBBYT_040 (0x20)
mdefine_line|#define WBWRD_040 (0x40)
mdefine_line|#define WBLNG_040 (0x00)
mdefine_line|#define WBTT_040  (0x18)
mdefine_line|#define WBTM_040  (0x07)
multiline_comment|/* bus access size codes */
mdefine_line|#define BA_SIZE_BYTE    (0x20)
mdefine_line|#define BA_SIZE_WORD    (0x40)
mdefine_line|#define BA_SIZE_LONG    (0x00)
mdefine_line|#define BA_SIZE_LINE    (0x60)
multiline_comment|/* bus access transfer type codes */
mdefine_line|#define BA_TT_MOVE16    (0x08)
multiline_comment|/* structure for stack frames */
r_struct
id|frame
(brace
r_struct
id|pt_regs
id|ptregs
suffix:semicolon
r_union
(brace
r_struct
(brace
r_int
r_int
id|iaddr
suffix:semicolon
multiline_comment|/* instruction address */
)brace
id|fmt2
suffix:semicolon
r_struct
(brace
r_int
r_int
id|effaddr
suffix:semicolon
multiline_comment|/* effective address */
)brace
id|fmt3
suffix:semicolon
r_struct
(brace
r_int
r_int
id|effaddr
suffix:semicolon
multiline_comment|/* effective address */
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/* pc of faulted instr */
)brace
id|fmt4
suffix:semicolon
r_struct
(brace
r_int
r_int
id|effaddr
suffix:semicolon
multiline_comment|/* effective address */
r_int
r_int
id|ssw
suffix:semicolon
multiline_comment|/* special status word */
r_int
r_int
id|wb3s
suffix:semicolon
multiline_comment|/* write back 3 status */
r_int
r_int
id|wb2s
suffix:semicolon
multiline_comment|/* write back 2 status */
r_int
r_int
id|wb1s
suffix:semicolon
multiline_comment|/* write back 1 status */
r_int
r_int
id|faddr
suffix:semicolon
multiline_comment|/* fault address */
r_int
r_int
id|wb3a
suffix:semicolon
multiline_comment|/* write back 3 address */
r_int
r_int
id|wb3d
suffix:semicolon
multiline_comment|/* write back 3 data */
r_int
r_int
id|wb2a
suffix:semicolon
multiline_comment|/* write back 2 address */
r_int
r_int
id|wb2d
suffix:semicolon
multiline_comment|/* write back 2 data */
r_int
r_int
id|wb1a
suffix:semicolon
multiline_comment|/* write back 1 address */
r_int
r_int
id|wb1dpd0
suffix:semicolon
multiline_comment|/* write back 1 data/push data 0*/
r_int
r_int
id|pd1
suffix:semicolon
multiline_comment|/* push data 1*/
r_int
r_int
id|pd2
suffix:semicolon
multiline_comment|/* push data 2*/
r_int
r_int
id|pd3
suffix:semicolon
multiline_comment|/* push data 3*/
)brace
id|fmt7
suffix:semicolon
r_struct
(brace
r_int
r_int
id|iaddr
suffix:semicolon
multiline_comment|/* instruction address */
r_int
r_int
id|int1
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* internal registers */
)brace
id|fmt9
suffix:semicolon
r_struct
(brace
r_int
r_int
id|int1
suffix:semicolon
r_int
r_int
id|ssw
suffix:semicolon
multiline_comment|/* special status word */
r_int
r_int
id|isc
suffix:semicolon
multiline_comment|/* instruction stage c */
r_int
r_int
id|isb
suffix:semicolon
multiline_comment|/* instruction stage b */
r_int
r_int
id|daddr
suffix:semicolon
multiline_comment|/* data cycle fault address */
r_int
r_int
id|int2
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|dobuf
suffix:semicolon
multiline_comment|/* data cycle output buffer */
r_int
r_int
id|int3
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|fmta
suffix:semicolon
r_struct
(brace
r_int
r_int
id|int1
suffix:semicolon
r_int
r_int
id|ssw
suffix:semicolon
multiline_comment|/* special status word */
r_int
r_int
id|isc
suffix:semicolon
multiline_comment|/* instruction stage c */
r_int
r_int
id|isb
suffix:semicolon
multiline_comment|/* instruction stage b */
r_int
r_int
id|daddr
suffix:semicolon
multiline_comment|/* data cycle fault address */
r_int
r_int
id|int2
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|dobuf
suffix:semicolon
multiline_comment|/* data cycle output buffer */
r_int
r_int
id|int3
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_int
id|baddr
suffix:semicolon
multiline_comment|/* stage B address */
r_int
r_int
id|int4
(braket
l_int|2
)braket
suffix:semicolon
r_int
r_int
id|dibuf
suffix:semicolon
multiline_comment|/* data cycle input buffer */
r_int
r_int
id|int5
(braket
l_int|3
)braket
suffix:semicolon
r_int
id|ver
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* stack frame version # */
r_int
id|int6
suffix:colon
l_int|12
suffix:semicolon
r_int
r_int
id|int7
(braket
l_int|18
)braket
suffix:semicolon
)brace
id|fmtb
suffix:semicolon
)brace
id|un
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
macro_line|#endif /* _H8300_TRAPS_H */
eof
