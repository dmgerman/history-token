multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Derived from IRIX &lt;sys/SN/gda.h&gt;.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; *&n; * gda.h -- Contains the data structure for the global data area,&n; * &t;The GDA contains information communicated between the&n; *&t;PROM, SYMMON, and the kernel. &n; */
macro_line|#ifndef _ASM_SN_GDA_H
DECL|macro|_ASM_SN_GDA_H
mdefine_line|#define _ASM_SN_GDA_H
macro_line|#include &lt;asm/sn/addrs.h&gt;
DECL|macro|GDA_MAGIC
mdefine_line|#define GDA_MAGIC&t;0x58464552
multiline_comment|/*&n; * GDA Version History&n; *&n; * Version #&t;| Change&n; * -------------+-------------------------------------------------------&n; * &t;1&t;| Initial SN0 version &n; * &t;2&t;| Prom sets g_partid field to the partition number. 0 IS&n; *&t;&t;| a valid partition #. &n; */
DECL|macro|GDA_VERSION
mdefine_line|#define GDA_VERSION&t;2&t;/* Current GDA version # */
DECL|macro|G_MAGICOFF
mdefine_line|#define G_MAGICOFF&t;0
DECL|macro|G_VERSIONOFF
mdefine_line|#define G_VERSIONOFF&t;4
DECL|macro|G_PROMOPOFF
mdefine_line|#define G_PROMOPOFF&t;6
DECL|macro|G_MASTEROFF
mdefine_line|#define G_MASTEROFF&t;8
DECL|macro|G_VDSOFF
mdefine_line|#define G_VDSOFF&t;12
DECL|macro|G_HKDNORMOFF
mdefine_line|#define G_HKDNORMOFF&t;16
DECL|macro|G_HKDUTLBOFF
mdefine_line|#define G_HKDUTLBOFF&t;24
DECL|macro|G_HKDXUTLBOFF
mdefine_line|#define G_HKDXUTLBOFF&t;32
DECL|macro|G_PARTIDOFF
mdefine_line|#define G_PARTIDOFF&t;40
DECL|macro|G_TABLEOFF
mdefine_line|#define G_TABLEOFF&t;128
macro_line|#ifdef _LANGUAGE_C
DECL|struct|gda
r_typedef
r_struct
id|gda
(brace
DECL|member|g_magic
id|u32
id|g_magic
suffix:semicolon
multiline_comment|/* GDA magic number */
DECL|member|g_version
id|u16
id|g_version
suffix:semicolon
multiline_comment|/* Version of this structure */
DECL|member|g_masterid
id|u16
id|g_masterid
suffix:semicolon
multiline_comment|/* The NASID:CPUNUM of the master cpu */
DECL|member|g_promop
id|u32
id|g_promop
suffix:semicolon
multiline_comment|/* Passes requests from the kernel to prom */
DECL|member|g_vds
id|u32
id|g_vds
suffix:semicolon
multiline_comment|/* Store the virtual dipswitches here */
DECL|member|g_hooked_norm
r_void
op_star
op_star
id|g_hooked_norm
suffix:semicolon
multiline_comment|/* ptr to pda loc for norm hndlr */
DECL|member|g_hooked_utlb
r_void
op_star
op_star
id|g_hooked_utlb
suffix:semicolon
multiline_comment|/* ptr to pda loc for utlb hndlr */
DECL|member|g_hooked_xtlb
r_void
op_star
op_star
id|g_hooked_xtlb
suffix:semicolon
multiline_comment|/* ptr to pda loc for xtlb hndlr */
DECL|member|g_partid
r_int
id|g_partid
suffix:semicolon
multiline_comment|/* partition id */
DECL|member|g_symmax
r_int
id|g_symmax
suffix:semicolon
multiline_comment|/* Max symbols in name table. */
DECL|member|g_dbstab
r_void
op_star
id|g_dbstab
suffix:semicolon
multiline_comment|/* Address of idbg symbol table */
DECL|member|g_nametab
r_char
op_star
id|g_nametab
suffix:semicolon
multiline_comment|/* Address of idbg name table */
DECL|member|g_ktext_repmask
r_void
op_star
id|g_ktext_repmask
suffix:semicolon
multiline_comment|/* Pointer to a mask of nodes with copies&n;&t;&t;&t;&t; * of the kernel. */
DECL|member|g_padding
r_char
id|g_padding
(braket
l_int|56
)braket
suffix:semicolon
multiline_comment|/* pad out to 128 bytes */
DECL|member|g_nasidtable
id|nasid_t
id|g_nasidtable
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
multiline_comment|/* NASID of each node,&n;&t;&t;&t;&t;&t;&t;  * indexed by cnodeid.&n;&t;&t;&t;&t;&t;&t;  */
DECL|typedef|gda_t
)brace
id|gda_t
suffix:semicolon
DECL|macro|GDA
mdefine_line|#define GDA ((gda_t*) GDA_ADDR(get_nasid()))
macro_line|#endif /* __LANGUAGE_C */
multiline_comment|/*&n; * Define:&t;PART_GDA_VERSION&n; * Purpose:&t;Define the minimum version of the GDA required, lower &n; *&t;&t;revisions assume GDA is NOT set up, and read partition&n; *&t;&t;information from the board info.&n; */
DECL|macro|PART_GDA_VERSION
mdefine_line|#define&t;PART_GDA_VERSION&t;2
multiline_comment|/*&n; * The following requests can be sent to the PROM during startup.&n; */
DECL|macro|PROMOP_MAGIC
mdefine_line|#define PROMOP_MAGIC&t;&t;0x0ead0000
DECL|macro|PROMOP_MAGIC_MASK
mdefine_line|#define PROMOP_MAGIC_MASK&t;0x0fff0000
DECL|macro|PROMOP_BIST_SHIFT
mdefine_line|#define PROMOP_BIST_SHIFT       11
DECL|macro|PROMOP_BIST_MASK
mdefine_line|#define PROMOP_BIST_MASK        (0x3 &lt;&lt; 11)
DECL|macro|PROMOP_REG
mdefine_line|#define PROMOP_REG&t;&t;PI_ERR_STACK_ADDR_A
DECL|macro|PROMOP_INVALID
mdefine_line|#define PROMOP_INVALID&t;&t;(PROMOP_MAGIC | 0x00)
DECL|macro|PROMOP_HALT
mdefine_line|#define PROMOP_HALT             (PROMOP_MAGIC | 0x10)
DECL|macro|PROMOP_POWERDOWN
mdefine_line|#define PROMOP_POWERDOWN        (PROMOP_MAGIC | 0x20)
DECL|macro|PROMOP_RESTART
mdefine_line|#define PROMOP_RESTART          (PROMOP_MAGIC | 0x30)
DECL|macro|PROMOP_REBOOT
mdefine_line|#define PROMOP_REBOOT           (PROMOP_MAGIC | 0x40)
DECL|macro|PROMOP_IMODE
mdefine_line|#define PROMOP_IMODE            (PROMOP_MAGIC | 0x50)
DECL|macro|PROMOP_CMD_MASK
mdefine_line|#define PROMOP_CMD_MASK&t;&t;0x00f0
DECL|macro|PROMOP_OPTIONS_MASK
mdefine_line|#define PROMOP_OPTIONS_MASK&t;0xfff0
DECL|macro|PROMOP_SKIP_DIAGS
mdefine_line|#define PROMOP_SKIP_DIAGS&t;0x0100&t;&t;/* don&squot;t bother running diags */
DECL|macro|PROMOP_SKIP_MEMINIT
mdefine_line|#define PROMOP_SKIP_MEMINIT&t;0x0200&t;&t;/* don&squot;t bother initing memory */
DECL|macro|PROMOP_SKIP_DEVINIT
mdefine_line|#define PROMOP_SKIP_DEVINIT&t;0x0400&t;&t;/* don&squot;t bother initing devices */
DECL|macro|PROMOP_BIST1
mdefine_line|#define PROMOP_BIST1&t;&t;0x0800&t;&t;/* keep track of which BIST ran */
DECL|macro|PROMOP_BIST2
mdefine_line|#define PROMOP_BIST2&t;&t;0x1000&t;&t;/* keep track of which BIST ran */
macro_line|#endif /* _ASM_SN_GDA_H */
eof
