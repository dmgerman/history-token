multiline_comment|/*&n; *  arch/s390/kernel/s390mach.h&n; *   S/390 data definitions for machine check processing&n; *&n; *  S390 version&n; *    Copyright (C) 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; */
macro_line|#ifndef __s390mach_h
DECL|macro|__s390mach_h
mdefine_line|#define __s390mach_h
macro_line|#include &lt;asm/types.h&gt;
DECL|struct|_mci
r_typedef
r_struct
id|_mci
(brace
DECL|member|to_be_defined_1
id|__u32
id|to_be_defined_1
suffix:colon
l_int|9
suffix:semicolon
DECL|member|cp
id|__u32
id|cp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* channel-report pending */
DECL|member|to_be_defined_2
id|__u32
id|to_be_defined_2
suffix:colon
l_int|22
suffix:semicolon
DECL|member|to_be_defined_3
id|__u32
id|to_be_defined_3
suffix:semicolon
DECL|typedef|mci_t
)brace
id|mci_t
suffix:semicolon
singleline_comment|//
singleline_comment|// machine-check-interruption code
singleline_comment|//
DECL|struct|_mcic
r_typedef
r_struct
id|_mcic
(brace
DECL|union|_mcc
r_union
id|_mcc
(brace
DECL|member|mcl
id|__u64
id|mcl
suffix:semicolon
multiline_comment|/* machine check int. code - long info */
DECL|member|mcd
id|mci_t
id|mcd
suffix:semicolon
multiline_comment|/* machine check int. code - details   */
DECL|member|mcc
)brace
id|mcc
suffix:semicolon
DECL|typedef|mcic_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mcic_t
suffix:semicolon
singleline_comment|//
singleline_comment|// Channel Report Word
singleline_comment|//
DECL|struct|_crw
r_typedef
r_struct
id|_crw
(brace
DECL|member|res1
id|__u32
id|res1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved zero */
DECL|member|slct
id|__u32
id|slct
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* solicited */
DECL|member|oflw
id|__u32
id|oflw
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* overflow */
DECL|member|chn
id|__u32
id|chn
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* chained */
DECL|member|rsc
id|__u32
id|rsc
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* reporting source code */
DECL|member|anc
id|__u32
id|anc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ancillary report */
DECL|member|res2
id|__u32
id|res2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved zero */
DECL|member|erc
id|__u32
id|erc
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* error-recovery code */
DECL|member|rsid
id|__u32
id|rsid
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* reporting-source ID */
DECL|typedef|crw_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|crw_t
suffix:semicolon
DECL|macro|CRW_RSC_MONITOR
mdefine_line|#define CRW_RSC_MONITOR  0x2  /* monitoring facility */
DECL|macro|CRW_RSC_SCH
mdefine_line|#define CRW_RSC_SCH      0x3  /* subchannel */
DECL|macro|CRW_RSC_CPATH
mdefine_line|#define CRW_RSC_CPATH    0x4  /* channel path */
DECL|macro|CRW_RSC_CONFIG
mdefine_line|#define CRW_RSC_CONFIG   0x9  /* configuration-alert facility */
DECL|macro|CRW_RSC_CSS
mdefine_line|#define CRW_RSC_CSS      0xB  /* channel subsystem */
DECL|macro|CRW_ERC_EVENT
mdefine_line|#define CRW_ERC_EVENT    0x00 /* event information pending */
DECL|macro|CRW_ERC_AVAIL
mdefine_line|#define CRW_ERC_AVAIL    0x01 /* available */
DECL|macro|CRW_ERC_INIT
mdefine_line|#define CRW_ERC_INIT     0x02 /* initialized */
DECL|macro|CRW_ERC_TERROR
mdefine_line|#define CRW_ERC_TERROR   0x03 /* temporary error */
DECL|macro|CRW_ERC_IPARM
mdefine_line|#define CRW_ERC_IPARM    0x04 /* installed parm initialized */
DECL|macro|CRW_ERC_TERM
mdefine_line|#define CRW_ERC_TERM     0x05 /* terminal */
DECL|macro|CRW_ERC_PERRN
mdefine_line|#define CRW_ERC_PERRN    0x06 /* perm. error, fac. not init */
DECL|macro|CRW_ERC_PERRI
mdefine_line|#define CRW_ERC_PERRI    0x07 /* perm. error, facility init */
DECL|macro|CRW_ERC_PMOD
mdefine_line|#define CRW_ERC_PMOD     0x08 /* installed parameters modified */
DECL|macro|MAX_CRW_PENDING
mdefine_line|#define MAX_CRW_PENDING  1024
DECL|macro|MAX_MACH_PENDING
mdefine_line|#define MAX_MACH_PENDING 1024
singleline_comment|//
singleline_comment|// CRW Entry
singleline_comment|//
DECL|struct|_crwe
r_typedef
r_struct
id|_crwe
(brace
DECL|member|crw
id|crw_t
id|crw
suffix:semicolon
DECL|member|crwe_next
r_struct
id|_crwe
op_star
id|crwe_next
suffix:semicolon
DECL|typedef|crwe_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|crwe_t
suffix:semicolon
DECL|struct|_mache
r_typedef
r_struct
id|_mache
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
DECL|member|mcic
id|mcic_t
id|mcic
suffix:semicolon
DECL|union|_mc
r_union
id|_mc
(brace
DECL|member|crwe
id|crwe_t
op_star
id|crwe
suffix:semicolon
multiline_comment|/* CRW if applicable */
DECL|member|mc
)brace
id|mc
suffix:semicolon
DECL|member|next
r_struct
id|_mache
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|_mache
op_star
id|prev
suffix:semicolon
DECL|typedef|mache_t
)brace
id|mache_t
suffix:semicolon
DECL|macro|MCHCHK_STATUS_TO_PROCESS
mdefine_line|#define MCHCHK_STATUS_TO_PROCESS    0x00000001
DECL|macro|MCHCHK_STATUS_IN_PROGRESS
mdefine_line|#define MCHCHK_STATUS_IN_PROGRESS   0x00000002
DECL|macro|MCHCHK_STATUS_WAITING
mdefine_line|#define MCHCHK_STATUS_WAITING       0x00000004
r_void
id|s390_init_machine_check
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|s390_do_machine_check
(paren
r_void
)paren
suffix:semicolon
r_void
id|s390_do_crw_pending
(paren
id|crwe_t
op_star
id|pcrwe
)paren
suffix:semicolon
DECL|function|stcrw
r_extern
id|__inline__
r_int
id|stcrw
c_func
(paren
id|__u32
op_star
id|pcrw
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;STCRW 0(%1)&bslash;n&bslash;t&quot;
l_string|&quot;IPM %0&bslash;n&bslash;t&quot;
l_string|&quot;SRL %0,28&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|pcrw
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
macro_line|#endif /* __s390mach */
eof
