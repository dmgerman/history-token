multiline_comment|/*&n; *  arch/s390/kernel/s390mach.h&n; *   S/390 data definitions for machine check processing&n; *&n; *  S390 version&n; *    Copyright (C) 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; */
macro_line|#ifndef __s390mach_h
DECL|macro|__s390mach_h
mdefine_line|#define __s390mach_h
macro_line|#include &lt;asm/types.h&gt;
singleline_comment|//
singleline_comment|// machine-check-interruption code
singleline_comment|//
DECL|struct|_mcic
r_typedef
r_struct
id|_mcic
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
DECL|member|crw_next
id|crw_t
op_star
id|crw_next
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
DECL|struct|_mchchk_queue_element
r_typedef
r_struct
id|_mchchk_queue_element
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
DECL|member|crwe
id|crwe_t
op_star
id|crwe
suffix:semicolon
multiline_comment|/* CRW if applicable */
DECL|member|next
r_struct
id|mchchk_queue_element
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|mchchk_queue_element
op_star
id|prev
suffix:semicolon
DECL|typedef|mchchk_queue_element_t
)brace
id|mchchk_queue_element_t
suffix:semicolon
DECL|macro|MCHCHK_STATUS_TO_PROCESS
mdefine_line|#define MCHCHK_STATUS_TO_PROCESS    0x00000001
DECL|macro|MCHCHK_STATUS_IN_PROGRESS
mdefine_line|#define MCHCHK_STATUS_IN_PROGRESS   0x00000002
DECL|macro|MCHCHK_STATUS_WAITING
mdefine_line|#define MCHCHK_STATUS_WAITING       0x00000004
r_void
id|s390_init_machine_check
(paren
r_void
)paren
suffix:semicolon
r_void
id|__init
id|s390_do_machine_check
(paren
r_void
)paren
suffix:semicolon
r_void
id|__init
id|s390_machine_check_handler
c_func
(paren
r_struct
id|semaphore
op_star
)paren
suffix:semicolon
macro_line|#endif /* __s390mach */
eof
