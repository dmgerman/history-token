multiline_comment|/*&n; * ohare.h: definitions for using the &quot;O&squot;Hare&quot; I/O controller chip.&n; *&n; * Copyright (C) 1997 Paul Mackerras.&n; * &n; * BenH: Changed to match those of heathrow (but not all of them). Please&n; *       check if I didn&squot;t break anything (especially the media bay).&n; */
multiline_comment|/* offset from ohare base for feature control register */
DECL|macro|OHARE_FEATURE_REG
mdefine_line|#define OHARE_FEATURE_REG&t;0x38
multiline_comment|/*&n; * Bits in feature control register.&n; * These were mostly derived by experiment on a powerbook 3400&n; * and may differ for other machines.&n; */
DECL|macro|OH_SCC_RESET
mdefine_line|#define OH_SCC_RESET&t;&t;1
DECL|macro|OH_BAY_POWER_N
mdefine_line|#define OH_BAY_POWER_N&t;&t;2&t;/* a guess */
DECL|macro|OH_BAY_PCI_ENABLE
mdefine_line|#define OH_BAY_PCI_ENABLE&t;4&t;/* a guess */
DECL|macro|OH_BAY_IDE_ENABLE
mdefine_line|#define OH_BAY_IDE_ENABLE&t;8
DECL|macro|OH_BAY_FLOPPY_ENABLE
mdefine_line|#define OH_BAY_FLOPPY_ENABLE&t;0x10
DECL|macro|OH_IDE0_ENABLE
mdefine_line|#define OH_IDE0_ENABLE&t;&t;0x20
DECL|macro|OH_IDE0_RESET_N
mdefine_line|#define OH_IDE0_RESET_N&t;&t;0x40&t;/* a guess */
DECL|macro|OH_BAY_RESET_N
mdefine_line|#define OH_BAY_RESET_N&t;&t;0x80
DECL|macro|OH_IOBUS_ENABLE
mdefine_line|#define OH_IOBUS_ENABLE&t;&t;0x100&t;/* IOBUS seems to be IDE */
DECL|macro|OH_SCC_ENABLE
mdefine_line|#define OH_SCC_ENABLE&t;&t;0x200
DECL|macro|OH_MESH_ENABLE
mdefine_line|#define OH_MESH_ENABLE&t;&t;0x400
DECL|macro|OH_FLOPPY_ENABLE
mdefine_line|#define OH_FLOPPY_ENABLE&t;0x800
DECL|macro|OH_SCCA_IO
mdefine_line|#define OH_SCCA_IO&t;&t;0x4000
DECL|macro|OH_SCCB_IO
mdefine_line|#define OH_SCCB_IO&t;&t;0x8000
DECL|macro|OH_VIA_ENABLE
mdefine_line|#define OH_VIA_ENABLE&t;&t;0x10000&t;/* Is apparently wrong, to be verified */
DECL|macro|OH_IDE1_RESET_N
mdefine_line|#define OH_IDE1_RESET_N&t;&t;0x800000
multiline_comment|/*&n; * Bits to set in the feature control register on PowerBooks.&n; */
DECL|macro|PBOOK_FEATURES
mdefine_line|#define PBOOK_FEATURES&t;&t;(OH_IDE_ENABLE | OH_SCC_ENABLE | &bslash;&n;&t;&t;&t;&t; OH_MESH_ENABLE | OH_SCCA_IO | OH_SCCB_IO)
multiline_comment|/*&n; * A magic value to put into the feature control register of the&n; * &quot;ohare&quot; I/O controller on Starmaxes to enable the IDE CD interface.&n; * Contributed by Harry Eaton.&n; */
DECL|macro|STARMAX_FEATURES
mdefine_line|#define STARMAX_FEATURES&t;0xbeff7a
eof
