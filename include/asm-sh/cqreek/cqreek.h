macro_line|#ifndef __ASM_SH_CQREEK_CQREEK_H
DECL|macro|__ASM_SH_CQREEK_CQREEK_H
mdefine_line|#define __ASM_SH_CQREEK_CQREEK_H
DECL|macro|BRIDGE_FEATURE
mdefine_line|#define BRIDGE_FEATURE&t;&t;0x0002
DECL|macro|BRIDGE_IDE_CTRL
mdefine_line|#define BRIDGE_IDE_CTRL&t;&t;0x0018
DECL|macro|BRIDGE_IDE_INTR_LVL
mdefine_line|#define BRIDGE_IDE_INTR_LVL    &t;0x001A
DECL|macro|BRIDGE_IDE_INTR_MASK
mdefine_line|#define BRIDGE_IDE_INTR_MASK&t;0x001C
DECL|macro|BRIDGE_IDE_INTR_STAT
mdefine_line|#define BRIDGE_IDE_INTR_STAT&t;0x001E
DECL|macro|BRIDGE_ISA_CTRL
mdefine_line|#define BRIDGE_ISA_CTRL&t;&t;0x0028
DECL|macro|BRIDGE_ISA_INTR_LVL
mdefine_line|#define BRIDGE_ISA_INTR_LVL    &t;0x002A
DECL|macro|BRIDGE_ISA_INTR_MASK
mdefine_line|#define BRIDGE_ISA_INTR_MASK&t;0x002C
DECL|macro|BRIDGE_ISA_INTR_STAT
mdefine_line|#define BRIDGE_ISA_INTR_STAT&t;0x002E
multiline_comment|/* arch/sh/boards/cqreek/setup.c */
r_extern
r_void
id|setup_cqreek
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* arch/sh/boards/cqreek/irq.c */
r_extern
r_int
id|cqreek_has_ide
comma
id|cqreek_has_isa
suffix:semicolon
r_extern
r_void
id|init_cqreek_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* arch/sh/boards/cqreek/io.c */
r_extern
r_int
r_int
id|cqreek_port2addr
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
macro_line|#endif /* __ASM_SH_CQREEK_CQREEK_H */
eof
