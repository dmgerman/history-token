multiline_comment|/*&n; * $Id$&n; *&n; * Ocelot Board Register Definitions&n; *&n; * (C) 2001 Red Hat, Inc.&n; *&n; * GPL&squot;d&n; *&n; */
macro_line|#ifndef __MOMENCO_OCELOT_PLD_H__
DECL|macro|__MOMENCO_OCELOT_PLD_H__
mdefine_line|#define __MOMENCO_OCELOT_PLD_H__
DECL|macro|OCELOT_CS0_ADDR
mdefine_line|#define OCELOT_CS0_ADDR (0xe0020000)
DECL|macro|OCELOT_REG_BOARDREV
mdefine_line|#define OCELOT_REG_BOARDREV (0)
DECL|macro|OCELOT_REG_PLD1_ID
mdefine_line|#define OCELOT_REG_PLD1_ID (1)
DECL|macro|OCELOT_REG_PLD2_ID
mdefine_line|#define OCELOT_REG_PLD2_ID (2)
DECL|macro|OCELOT_REG_RESET_STATUS
mdefine_line|#define OCELOT_REG_RESET_STATUS (3)
DECL|macro|OCELOT_REG_BOARD_STATUS
mdefine_line|#define OCELOT_REG_BOARD_STATUS (4)
DECL|macro|OCELOT_REG_CPCI_ID
mdefine_line|#define OCELOT_REG_CPCI_ID (5)
DECL|macro|OCELOT_REG_I2C_CTRL
mdefine_line|#define OCELOT_REG_I2C_CTRL (8)
DECL|macro|OCELOT_REG_EEPROM_MODE
mdefine_line|#define OCELOT_REG_EEPROM_MODE (9)
DECL|macro|OCELOT_REG_INTMASK
mdefine_line|#define OCELOT_REG_INTMASK (10)
DECL|macro|OCELOT_REG_INTSTATUS
mdefine_line|#define OCELOT_REG_INTSTATUS (11)
DECL|macro|OCELOT_REG_INTSET
mdefine_line|#define OCELOT_REG_INTSET (12)
DECL|macro|OCELOT_REG_INTCLR
mdefine_line|#define OCELOT_REG_INTCLR (13)
DECL|macro|OCELOT_PLD_WRITE
mdefine_line|#define OCELOT_PLD_WRITE(x, y) writeb(x, OCELOT_CS0_ADDR + OCELOT_REG_##y)
DECL|macro|OCELOT_PLD_READ
mdefine_line|#define OCELOT_PLD_READ(x) readb(OCELOT_CS0_ADDR + OCELOT_REG_##x)
macro_line|#endif /* __MOMENCO_OCELOT_PLD_H__ */
eof
