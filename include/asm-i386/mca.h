multiline_comment|/* -*- mode: c; c-basic-offset: 8 -*- */
multiline_comment|/* Platform specific MCA defines */
macro_line|#ifndef _ASM_MCA_H
DECL|macro|_ASM_MCA_H
mdefine_line|#define _ASM_MCA_H
multiline_comment|/* Maximal number of MCA slots - actually, some machines have less, but&n; * they all have sufficient number of POS registers to cover 8.&n; */
DECL|macro|MCA_MAX_SLOT_NR
mdefine_line|#define MCA_MAX_SLOT_NR  8
multiline_comment|/* Most machines have only one MCA bus.  The only multiple bus machines&n; * I know have at most two */
DECL|macro|MAX_MCA_BUSSES
mdefine_line|#define MAX_MCA_BUSSES 2
DECL|macro|MCA_PRIMARY_BUS
mdefine_line|#define MCA_PRIMARY_BUS&t;&t;0
DECL|macro|MCA_SECONDARY_BUS
mdefine_line|#define MCA_SECONDARY_BUS&t;1
multiline_comment|/* Dummy slot numbers on primary MCA for integrated functions */
DECL|macro|MCA_INTEGSCSI
mdefine_line|#define MCA_INTEGSCSI&t;(MCA_MAX_SLOT_NR)
DECL|macro|MCA_INTEGVIDEO
mdefine_line|#define MCA_INTEGVIDEO&t;(MCA_MAX_SLOT_NR+1)
DECL|macro|MCA_MOTHERBOARD
mdefine_line|#define MCA_MOTHERBOARD (MCA_MAX_SLOT_NR+2)
multiline_comment|/* Dummy POS values for integrated functions */
DECL|macro|MCA_DUMMY_POS_START
mdefine_line|#define MCA_DUMMY_POS_START&t;0x10000
DECL|macro|MCA_INTEGSCSI_POS
mdefine_line|#define MCA_INTEGSCSI_POS&t;(MCA_DUMMY_POS_START+1)
DECL|macro|MCA_INTEGVIDEO_POS
mdefine_line|#define MCA_INTEGVIDEO_POS&t;(MCA_DUMMY_POS_START+2)
DECL|macro|MCA_MOTHERBOARD_POS
mdefine_line|#define MCA_MOTHERBOARD_POS&t;(MCA_DUMMY_POS_START+3)
multiline_comment|/* MCA registers */
DECL|macro|MCA_MOTHERBOARD_SETUP_REG
mdefine_line|#define MCA_MOTHERBOARD_SETUP_REG&t;0x94
DECL|macro|MCA_ADAPTER_SETUP_REG
mdefine_line|#define MCA_ADAPTER_SETUP_REG&t;&t;0x96
DECL|macro|MCA_POS_REG
mdefine_line|#define MCA_POS_REG(n)&t;&t;&t;(0x100+(n))
DECL|macro|MCA_ENABLED
mdefine_line|#define MCA_ENABLED&t;0x01&t;/* POS 2, set if adapter enabled */
multiline_comment|/* Max number of adapters, including both slots and various integrated&n; * things.&n; */
DECL|macro|MCA_NUMADAPTERS
mdefine_line|#define MCA_NUMADAPTERS (MCA_MAX_SLOT_NR+3)
macro_line|#endif
eof
