macro_line|#ifndef _SPARC64_CMT_H
DECL|macro|_SPARC64_CMT_H
mdefine_line|#define _SPARC64_CMT_H
multiline_comment|/* cmt.h: Chip Multi-Threading register definitions&n; *&n; * Copyright (C) 2004 David S. Miller (davem@redhat.com)&n; */
multiline_comment|/* ASI_CORE_ID - private */
DECL|macro|LP_ID
mdefine_line|#define LP_ID&t;&t;0x0000000000000010UL
DECL|macro|LP_ID_MAX
mdefine_line|#define  LP_ID_MAX&t;0x00000000003f0000UL
DECL|macro|LP_ID_ID
mdefine_line|#define  LP_ID_ID&t;0x000000000000003fUL
multiline_comment|/* ASI_INTR_ID - private */
DECL|macro|LP_INTR_ID
mdefine_line|#define LP_INTR_ID&t;0x0000000000000000UL
DECL|macro|LP_INTR_ID_ID
mdefine_line|#define  LP_INTR_ID_ID&t;0x00000000000003ffUL
multiline_comment|/* ASI_CESR_ID - private */
DECL|macro|CESR_ID
mdefine_line|#define CESR_ID&t;&t;0x0000000000000040UL
DECL|macro|CESR_ID_ID
mdefine_line|#define  CESR_ID_ID&t;0x00000000000000ffUL
multiline_comment|/* ASI_CORE_AVAILABLE - shared */
DECL|macro|LP_AVAIL
mdefine_line|#define LP_AVAIL&t;0x0000000000000000UL
DECL|macro|LP_AVAIL_1
mdefine_line|#define  LP_AVAIL_1&t;0x0000000000000002UL
DECL|macro|LP_AVAIL_0
mdefine_line|#define  LP_AVAIL_0&t;0x0000000000000001UL
multiline_comment|/* ASI_CORE_ENABLE_STATUS - shared */
DECL|macro|LP_ENAB_STAT
mdefine_line|#define LP_ENAB_STAT&t;0x0000000000000010UL
DECL|macro|LP_ENAB_STAT_1
mdefine_line|#define  LP_ENAB_STAT_1&t;0x0000000000000002UL
DECL|macro|LP_ENAB_STAT_0
mdefine_line|#define  LP_ENAB_STAT_0&t;0x0000000000000001UL
multiline_comment|/* ASI_CORE_ENABLE - shared */
DECL|macro|LP_ENAB
mdefine_line|#define LP_ENAB&t;&t;0x0000000000000020UL
DECL|macro|LP_ENAB_1
mdefine_line|#define  LP_ENAB_1&t;0x0000000000000002UL
DECL|macro|LP_ENAB_0
mdefine_line|#define  LP_ENAB_0&t;0x0000000000000001UL
multiline_comment|/* ASI_CORE_RUNNING - shared */
DECL|macro|LP_RUNNING_RW
mdefine_line|#define LP_RUNNING_RW&t;0x0000000000000050UL
DECL|macro|LP_RUNNING_W1S
mdefine_line|#define LP_RUNNING_W1S&t;0x0000000000000060UL
DECL|macro|LP_RUNNING_W1C
mdefine_line|#define LP_RUNNING_W1C&t;0x0000000000000068UL
DECL|macro|LP_RUNNING_1
mdefine_line|#define  LP_RUNNING_1&t;0x0000000000000002UL
DECL|macro|LP_RUNNING_0
mdefine_line|#define  LP_RUNNING_0&t;0x0000000000000001UL
multiline_comment|/* ASI_CORE_RUNNING_STAT - shared */
DECL|macro|LP_RUN_STAT
mdefine_line|#define LP_RUN_STAT&t;0x0000000000000058UL
DECL|macro|LP_RUN_STAT_1
mdefine_line|#define  LP_RUN_STAT_1&t;0x0000000000000002UL
DECL|macro|LP_RUN_STAT_0
mdefine_line|#define  LP_RUN_STAT_0&t;0x0000000000000001UL
multiline_comment|/* ASI_XIR_STEERING - shared */
DECL|macro|LP_XIR_STEER
mdefine_line|#define LP_XIR_STEER&t;0x0000000000000030UL
DECL|macro|LP_XIR_STEER_1
mdefine_line|#define  LP_XIR_STEER_1&t;0x0000000000000002UL
DECL|macro|LP_XIR_STEER_0
mdefine_line|#define  LP_XIR_STEER_0&t;0x0000000000000001UL
multiline_comment|/* ASI_CMT_ERROR_STEERING - shared */
DECL|macro|CMT_ER_STEER
mdefine_line|#define CMT_ER_STEER&t;0x0000000000000040UL
DECL|macro|CMT_ER_STEER_1
mdefine_line|#define  CMT_ER_STEER_1&t;0x0000000000000002UL
DECL|macro|CMT_ER_STEER_0
mdefine_line|#define  CMT_ER_STEER_0&t;0x0000000000000001UL
macro_line|#endif /* _SPARC64_CMT_H */
eof
