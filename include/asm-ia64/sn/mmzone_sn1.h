macro_line|#ifndef _ASM_IA64_MMZONE_SN1_H
DECL|macro|_ASM_IA64_MMZONE_SN1_H
mdefine_line|#define _ASM_IA64_MMZONE_SN1_H
multiline_comment|/*&n; * Copyright, 2000, Silicon Graphics, sprasad@engr.sgi.com&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Maximum configuration supported by SNIA hardware. There are other&n; * restrictions that may limit us to a smaller max configuration.&n; */
DECL|macro|MAXNODES
mdefine_line|#define MAXNODES                128
DECL|macro|MAXNASIDS
mdefine_line|#define MAXNASIDS&t;&t;128
DECL|macro|CHUNKSZ
mdefine_line|#define CHUNKSZ                (64*1024*1024)
DECL|macro|CHUNKSHIFT
mdefine_line|#define CHUNKSHIFT              26      /* 2 ^^ CHUNKSHIFT == CHUNKSZ */
r_extern
r_int
id|cnodeid_map
(braket
)braket
suffix:semicolon
r_extern
r_int
id|nasid_map
(braket
)braket
suffix:semicolon
DECL|macro|CNODEID_TO_NASID
mdefine_line|#define CNODEID_TO_NASID(n)&t;(cnodeid_map[(n)])
DECL|macro|NASID_TO_CNODEID
mdefine_line|#define NASID_TO_CNODEID(n)     (nasid_map[(n)])
DECL|macro|MAX_CHUNKS_PER_NODE
mdefine_line|#define MAX_CHUNKS_PER_NODE     128
multiline_comment|/*&n; * These are a bunch of sn1 hw specific defines. For now, keep it &n; * in this file. If it gets too diverse we may want to create a &n; * mmhwdefs_sn1.h&n; */
multiline_comment|/*&n; * Structure of the mem config of the node as a SN1 MI reg&n; * Medusa supports this reg config.&n; */
DECL|struct|node_memmap_s
r_typedef
r_struct
id|node_memmap_s
(brace
DECL|member|b0
r_int
r_int
id|b0
suffix:colon
l_int|1
comma
multiline_comment|/* 0 bank 0 present */
DECL|member|b1
id|b1
suffix:colon
l_int|1
comma
multiline_comment|/* 1 bank 1 present */
DECL|member|r01
id|r01
suffix:colon
l_int|2
comma
multiline_comment|/* 2-3 reserved */
DECL|member|b01size
id|b01size
suffix:colon
l_int|4
comma
multiline_comment|/* 4-7 Size of bank 0 and 1 */
DECL|member|b2
id|b2
suffix:colon
l_int|1
comma
multiline_comment|/* 8 bank 2 present */
DECL|member|b3
id|b3
suffix:colon
l_int|1
comma
multiline_comment|/* 9 bank 3 present */
DECL|member|r23
id|r23
suffix:colon
l_int|2
comma
multiline_comment|/* 10-11 reserved */
DECL|member|b23size
id|b23size
suffix:colon
l_int|4
comma
multiline_comment|/* 12-15 Size of bank 2 and 3 */
DECL|member|b4
id|b4
suffix:colon
l_int|1
comma
multiline_comment|/* 16 bank 4 present */
DECL|member|b5
id|b5
suffix:colon
l_int|1
comma
multiline_comment|/* 17 bank 5 present */
DECL|member|r45
id|r45
suffix:colon
l_int|2
comma
multiline_comment|/* 18-19 reserved */
DECL|member|b45size
id|b45size
suffix:colon
l_int|4
comma
multiline_comment|/* 20-23 Size of bank 4 and 5 */
DECL|member|b6
id|b6
suffix:colon
l_int|1
comma
multiline_comment|/* 24 bank 6 present */
DECL|member|b7
id|b7
suffix:colon
l_int|1
comma
multiline_comment|/* 25 bank 7 present */
DECL|member|r67
id|r67
suffix:colon
l_int|2
comma
multiline_comment|/* 26-27 reserved */
DECL|member|b67size
id|b67size
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 28-31 Size of bank 6 and 7 */
DECL|typedef|node_memmap_t
)brace
id|node_memmap_t
suffix:semicolon
DECL|macro|GBSHIFT
mdefine_line|#define GBSHIFT                 30
DECL|macro|MBSHIFT
mdefine_line|#define MBSHIFT                 20
multiline_comment|/*&n; * SN1 Arch defined values&n; */
DECL|macro|SN1_MAX_BANK_PER_NODE
mdefine_line|#define SN1_MAX_BANK_PER_NODE   8
DECL|macro|SN1_BANK_PER_NODE_SHIFT
mdefine_line|#define SN1_BANK_PER_NODE_SHIFT 3       /* derived from SN1_MAX_BANK_PER_NODE */
DECL|macro|SN1_NODE_ADDR_SHIFT
mdefine_line|#define SN1_NODE_ADDR_SHIFT     (GBSHIFT+3)             /* 8GB */
DECL|macro|SN1_BANK_ADDR_SHIFT
mdefine_line|#define SN1_BANK_ADDR_SHIFT     (SN1_NODE_ADDR_SHIFT-SN1_BANK_PER_NODE_SHIFT)
DECL|macro|SN1_BANK_SIZE_SHIFT
mdefine_line|#define SN1_BANK_SIZE_SHIFT     (MBSHIFT+6)     /* 64 MB */
DECL|macro|SN1_MIN_BANK_SIZE_SHIFT
mdefine_line|#define SN1_MIN_BANK_SIZE_SHIFT SN1_BANK_SIZE_SHIFT
multiline_comment|/*&n; * BankSize nibble to bank size mapping&n; *&n; *      1 - 64 MB&n; *      2 - 128 MB&n; *      3 - 256 MB&n; *      4 - 512 MB&n; *      5 - 1024 MB (1GB)&n; */
multiline_comment|/* fixme - this macro breaks for bsize 6-8 and 0 */
macro_line|#ifdef CONFIG_IA64_SGI_SN1_SIM
multiline_comment|/* Support the medusa hack for 8M/16M/32M nodes */
DECL|macro|BankSizeBytes
mdefine_line|#define BankSizeBytes(bsize)            ((bsize&lt;6) ? (1&lt;&lt;((bsize-1)+SN1_BANK_SIZE_SHIFT)) :&bslash;&n;&t;&t;&t;&t;&t; (1&lt;&lt;((bsize-9)+MBSHIFT)))
macro_line|#else
DECL|macro|BankSizeBytes
mdefine_line|#define BankSizeBytes(bsize)            (1&lt;&lt;((bsize-1)+SN1_BANK_SIZE_SHIFT))
macro_line|#endif
DECL|macro|BankSizeToEFIPages
mdefine_line|#define BankSizeToEFIPages(bsize)       ((BankSizeBytes(bsize)) &gt;&gt; 12)
DECL|macro|GetPhysAddr
mdefine_line|#define GetPhysAddr(n,b)                (((u64)n&lt;&lt;SN1_NODE_ADDR_SHIFT) | &bslash;&n;                                                ((u64)b&lt;&lt;SN1_BANK_ADDR_SHIFT))
DECL|macro|GetNasId
mdefine_line|#define GetNasId(paddr)&t;&t;&t;((u64)(paddr) &gt;&gt; SN1_NODE_ADDR_SHIFT)
DECL|macro|GetBankId
mdefine_line|#define GetBankId(paddr)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;(((u64)(paddr) &gt;&gt; SN1_BANK_ADDR_SHIFT) &amp; 7)
DECL|macro|SN1_MAX_BANK_SIZE
mdefine_line|#define SN1_MAX_BANK_SIZE&t;&t;((u64)BankSizeBytes(5))
DECL|macro|SN1_BANK_SIZE_MASK
mdefine_line|#define SN1_BANK_SIZE_MASK&t;&t;(~(SN1_MAX_BANK_SIZE-1))
macro_line|#endif /* _ASM_IA64_MMZONE_SN1_H */
eof
