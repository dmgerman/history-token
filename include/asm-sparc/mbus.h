multiline_comment|/* $Id: mbus.h,v 1.9 1997/06/24 15:48:12 jj Exp $&n; * mbus.h:  Various defines for MBUS modules.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_MBUS_H
DECL|macro|_SPARC_MBUS_H
mdefine_line|#define _SPARC_MBUS_H
macro_line|#include &lt;asm/ross.h&gt;    /* HyperSparc stuff */
macro_line|#include &lt;asm/cypress.h&gt; /* Cypress Chips */
macro_line|#include &lt;asm/viking.h&gt;  /* Ugh, bug city... */
DECL|enum|mbus_module
r_enum
id|mbus_module
(brace
DECL|enumerator|HyperSparc
id|HyperSparc
op_assign
l_int|0
comma
DECL|enumerator|Cypress
id|Cypress
op_assign
l_int|1
comma
DECL|enumerator|Cypress_vE
id|Cypress_vE
op_assign
l_int|2
comma
DECL|enumerator|Cypress_vD
id|Cypress_vD
op_assign
l_int|3
comma
DECL|enumerator|Swift_ok
id|Swift_ok
op_assign
l_int|4
comma
DECL|enumerator|Swift_bad_c
id|Swift_bad_c
op_assign
l_int|5
comma
DECL|enumerator|Swift_lots_o_bugs
id|Swift_lots_o_bugs
op_assign
l_int|6
comma
DECL|enumerator|Tsunami
id|Tsunami
op_assign
l_int|7
comma
DECL|enumerator|Viking_12
id|Viking_12
op_assign
l_int|8
comma
DECL|enumerator|Viking_2x
id|Viking_2x
op_assign
l_int|9
comma
DECL|enumerator|Viking_30
id|Viking_30
op_assign
l_int|10
comma
DECL|enumerator|Viking_35
id|Viking_35
op_assign
l_int|11
comma
DECL|enumerator|Viking_new
id|Viking_new
op_assign
l_int|12
comma
DECL|enumerator|TurboSparc
id|TurboSparc
op_assign
l_int|13
comma
DECL|enumerator|SRMMU_INVAL_MOD
id|SRMMU_INVAL_MOD
op_assign
l_int|14
comma
)brace
suffix:semicolon
r_extern
r_enum
id|mbus_module
id|srmmu_modtype
suffix:semicolon
r_extern
r_int
r_int
id|viking_rev
comma
id|swift_rev
comma
id|cypress_rev
suffix:semicolon
multiline_comment|/* HW Mbus module bugs we have to deal with */
DECL|macro|HWBUG_COPYBACK_BROKEN
mdefine_line|#define HWBUG_COPYBACK_BROKEN        0x00000001
DECL|macro|HWBUG_ASIFLUSH_BROKEN
mdefine_line|#define HWBUG_ASIFLUSH_BROKEN        0x00000002
DECL|macro|HWBUG_VACFLUSH_BITROT
mdefine_line|#define HWBUG_VACFLUSH_BITROT        0x00000004
DECL|macro|HWBUG_KERN_ACCBROKEN
mdefine_line|#define HWBUG_KERN_ACCBROKEN         0x00000008
DECL|macro|HWBUG_KERN_CBITBROKEN
mdefine_line|#define HWBUG_KERN_CBITBROKEN        0x00000010
DECL|macro|HWBUG_MODIFIED_BITROT
mdefine_line|#define HWBUG_MODIFIED_BITROT        0x00000020
DECL|macro|HWBUG_PC_BADFAULT_ADDR
mdefine_line|#define HWBUG_PC_BADFAULT_ADDR       0x00000040
DECL|macro|HWBUG_SUPERSCALAR_BAD
mdefine_line|#define HWBUG_SUPERSCALAR_BAD        0x00000080
DECL|macro|HWBUG_PACINIT_BITROT
mdefine_line|#define HWBUG_PACINIT_BITROT         0x00000100
r_extern
r_int
r_int
id|hwbug_bitmask
suffix:semicolon
multiline_comment|/* First the module type values. To find out which you have, just load&n; * the mmu control register from ASI_M_MMUREG alternate address space and&n; * shift the value right 28 bits.&n; */
multiline_comment|/* IMPL field means the company which produced the chip. */
DECL|macro|MBUS_VIKING
mdefine_line|#define MBUS_VIKING        0x4   /* bleech, Texas Instruments Module */
DECL|macro|MBUS_LSI
mdefine_line|#define MBUS_LSI           0x3   /* LSI Logics */
DECL|macro|MBUS_ROSS
mdefine_line|#define MBUS_ROSS          0x1   /* Ross is nice */
DECL|macro|MBUS_FMI
mdefine_line|#define MBUS_FMI           0x0   /* Fujitsu Microelectronics/Swift */
multiline_comment|/* Ross Module versions */
DECL|macro|ROSS_604_REV_CDE
mdefine_line|#define ROSS_604_REV_CDE        0x0   /* revisions c, d, and e */
DECL|macro|ROSS_604_REV_F
mdefine_line|#define ROSS_604_REV_F          0x1   /* revision f */
DECL|macro|ROSS_605
mdefine_line|#define ROSS_605                0xf   /* revision a, a.1, and a.2 */
DECL|macro|ROSS_605_REV_B
mdefine_line|#define ROSS_605_REV_B          0xe   /* revision b */
multiline_comment|/* TI Viking Module versions */
DECL|macro|VIKING_REV_12
mdefine_line|#define VIKING_REV_12           0x1   /* Version 1.2 or SPARCclassic&squot;s CPU */
DECL|macro|VIKING_REV_2
mdefine_line|#define VIKING_REV_2            0x2   /* Version 2.1, 2.2, 2.3, and 2.4 */
DECL|macro|VIKING_REV_30
mdefine_line|#define VIKING_REV_30           0x3   /* Version 3.0 */
DECL|macro|VIKING_REV_35
mdefine_line|#define VIKING_REV_35           0x4   /* Version 3.5 */
multiline_comment|/* LSI Logics. */
DECL|macro|LSI_L64815
mdefine_line|#define LSI_L64815&t;&t;0x0
multiline_comment|/* Fujitsu */
DECL|macro|FMI_AURORA
mdefine_line|#define FMI_AURORA&t;&t;0x4   /* MB8690x, a Swift module... */
DECL|macro|FMI_TURBO
mdefine_line|#define FMI_TURBO&t;&t;0x5   /* MB86907, a TurboSparc module... */
multiline_comment|/* For multiprocessor support we need to be able to obtain the CPU id and&n; * the MBUS Module id.&n; */
multiline_comment|/* The CPU ID is encoded in the trap base register, 20 bits to the left of&n; * bit zero, with 2 bits being significant.&n; */
DECL|macro|TBR_ID_SHIFT
mdefine_line|#define TBR_ID_SHIFT            20
DECL|function|get_cpuid
r_extern
id|__inline__
r_int
id|get_cpuid
c_func
(paren
r_void
)paren
(brace
r_register
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%tbr, %0&bslash;n&bslash;t&quot;
l_string|&quot;srl %0, %1, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|TBR_ID_SHIFT
)paren
)paren
suffix:semicolon
r_return
(paren
id|retval
op_amp
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|get_modid
r_extern
id|__inline__
r_int
id|get_modid
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|get_cpuid
c_func
(paren
)paren
op_or
l_int|0x8
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC_MBUS_H) */
eof
