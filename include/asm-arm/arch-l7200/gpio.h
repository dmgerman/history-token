multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *      linux/include/asm-arm/arch-l7200/gpio.h&n; *&n; *      Registers and  helper functions for the L7200 Link-Up Systems&n; *      GPIO.&n; *&n; *      (C) Copyright 2000, S A McConnell  (samcconn@cotw.com)&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
multiline_comment|/****************************************************************************/
DECL|macro|GPIO_OFF
mdefine_line|#define GPIO_OFF   0x00005000  /* Offset from IO_START to the GPIO reg&squot;s. */
multiline_comment|/* IO_START and IO_BASE are defined in hardware.h */
DECL|macro|GPIO_START
mdefine_line|#define GPIO_START (IO_START_2 + GPIO_OFF) /* Physical addr of the GPIO reg. */
DECL|macro|GPIO_BASE
mdefine_line|#define GPIO_BASE  (IO_BASE_2  + GPIO_OFF) /* Virtual addr of the GPIO reg. */
multiline_comment|/* Offsets from the start of the GPIO for all the registers. */
DECL|macro|PADR_OFF
mdefine_line|#define PADR_OFF     0x000
DECL|macro|PADDR_OFF
mdefine_line|#define PADDR_OFF    0x004
DECL|macro|PASBSR_OFF
mdefine_line|#define PASBSR_OFF   0x008
DECL|macro|PAEENR_OFF
mdefine_line|#define PAEENR_OFF   0x00c
DECL|macro|PAESNR_OFF
mdefine_line|#define PAESNR_OFF   0x010
DECL|macro|PAESTR_OFF
mdefine_line|#define PAESTR_OFF   0x014
DECL|macro|PAIMR_OFF
mdefine_line|#define PAIMR_OFF    0x018
DECL|macro|PAINT_OFF
mdefine_line|#define PAINT_OFF    0x01c
DECL|macro|PBDR_OFF
mdefine_line|#define PBDR_OFF     0x020
DECL|macro|PBDDR_OFF
mdefine_line|#define PBDDR_OFF    0x024
DECL|macro|PBSBSR_OFF
mdefine_line|#define PBSBSR_OFF   0x028
DECL|macro|PBIMR_OFF
mdefine_line|#define PBIMR_OFF    0x038
DECL|macro|PBINT_OFF
mdefine_line|#define PBINT_OFF    0x03c
DECL|macro|PCDR_OFF
mdefine_line|#define PCDR_OFF     0x040
DECL|macro|PCDDR_OFF
mdefine_line|#define PCDDR_OFF    0x044
DECL|macro|PCSBSR_OFF
mdefine_line|#define PCSBSR_OFF   0x048
DECL|macro|PCIMR_OFF
mdefine_line|#define PCIMR_OFF    0x058
DECL|macro|PCINT_OFF
mdefine_line|#define PCINT_OFF    0x05c
DECL|macro|PDDR_OFF
mdefine_line|#define PDDR_OFF     0x060
DECL|macro|PDDDR_OFF
mdefine_line|#define PDDDR_OFF    0x064
DECL|macro|PDSBSR_OFF
mdefine_line|#define PDSBSR_OFF   0x068
DECL|macro|PDEENR_OFF
mdefine_line|#define PDEENR_OFF   0x06c
DECL|macro|PDESNR_OFF
mdefine_line|#define PDESNR_OFF   0x070
DECL|macro|PDESTR_OFF
mdefine_line|#define PDESTR_OFF   0x074
DECL|macro|PDIMR_OFF
mdefine_line|#define PDIMR_OFF    0x078
DECL|macro|PDINT_OFF
mdefine_line|#define PDINT_OFF    0x07c
DECL|macro|PEDR_OFF
mdefine_line|#define PEDR_OFF     0x080
DECL|macro|PEDDR_OFF
mdefine_line|#define PEDDR_OFF    0x084
DECL|macro|PESBSR_OFF
mdefine_line|#define PESBSR_OFF   0x088
DECL|macro|PEEENR_OFF
mdefine_line|#define PEEENR_OFF   0x08c
DECL|macro|PEESNR_OFF
mdefine_line|#define PEESNR_OFF   0x090
DECL|macro|PEESTR_OFF
mdefine_line|#define PEESTR_OFF   0x094
DECL|macro|PEIMR_OFF
mdefine_line|#define PEIMR_OFF    0x098
DECL|macro|PEINT_OFF
mdefine_line|#define PEINT_OFF    0x09c
multiline_comment|/* Define the GPIO registers for use by device drivers and the kernel. */
DECL|macro|PADR
mdefine_line|#define PADR   (*(volatile unsigned long *)(GPIO_BASE+PADR_OFF))
DECL|macro|PADDR
mdefine_line|#define PADDR  (*(volatile unsigned long *)(GPIO_BASE+PADDR_OFF))
DECL|macro|PASBSR
mdefine_line|#define PASBSR (*(volatile unsigned long *)(GPIO_BASE+PASBSR_OFF))
DECL|macro|PAEENR
mdefine_line|#define PAEENR (*(volatile unsigned long *)(GPIO_BASE+PAEENR_OFF))
DECL|macro|PAESNR
mdefine_line|#define PAESNR (*(volatile unsigned long *)(GPIO_BASE+PAESNR_OFF))
DECL|macro|PAESTR
mdefine_line|#define PAESTR (*(volatile unsigned long *)(GPIO_BASE+PAESTR_OFF))
DECL|macro|PAIMR
mdefine_line|#define PAIMR  (*(volatile unsigned long *)(GPIO_BASE+PAIMR_OFF))
DECL|macro|PAINT
mdefine_line|#define PAINT  (*(volatile unsigned long *)(GPIO_BASE+PAINT_OFF))
DECL|macro|PBDR
mdefine_line|#define PBDR   (*(volatile unsigned long *)(GPIO_BASE+PBDR_OFF))
DECL|macro|PBDDR
mdefine_line|#define PBDDR  (*(volatile unsigned long *)(GPIO_BASE+PBDDR_OFF))
DECL|macro|PBSBSR
mdefine_line|#define PBSBSR (*(volatile unsigned long *)(GPIO_BASE+PBSBSR_OFF))
DECL|macro|PBIMR
mdefine_line|#define PBIMR  (*(volatile unsigned long *)(GPIO_BASE+PBIMR_OFF))
DECL|macro|PBINT
mdefine_line|#define PBINT  (*(volatile unsigned long *)(GPIO_BASE+PBINT_OFF))
DECL|macro|PCDR
mdefine_line|#define PCDR   (*(volatile unsigned long *)(GPIO_BASE+PCDR_OFF))
DECL|macro|PCDDR
mdefine_line|#define PCDDR  (*(volatile unsigned long *)(GPIO_BASE+PCDDR_OFF))
DECL|macro|PCSBSR
mdefine_line|#define PCSBSR (*(volatile unsigned long *)(GPIO_BASE+PCSBSR_OFF))
DECL|macro|PCIMR
mdefine_line|#define PCIMR  (*(volatile unsigned long *)(GPIO_BASE+PCIMR_OFF))
DECL|macro|PCINT
mdefine_line|#define PCINT  (*(volatile unsigned long *)(GPIO_BASE+PCINT_OFF))
DECL|macro|PDDR
mdefine_line|#define PDDR   (*(volatile unsigned long *)(GPIO_BASE+PDDR_OFF))
DECL|macro|PDDDR
mdefine_line|#define PDDDR  (*(volatile unsigned long *)(GPIO_BASE+PDDDR_OFF))
DECL|macro|PDSBSR
mdefine_line|#define PDSBSR (*(volatile unsigned long *)(GPIO_BASE+PDSBSR_OFF))
DECL|macro|PDEENR
mdefine_line|#define PDEENR (*(volatile unsigned long *)(GPIO_BASE+PDEENR_OFF))
DECL|macro|PDESNR
mdefine_line|#define PDESNR (*(volatile unsigned long *)(GPIO_BASE+PDESNR_OFF))
DECL|macro|PDESTR
mdefine_line|#define PDESTR (*(volatile unsigned long *)(GPIO_BASE+PDESTR_OFF))
DECL|macro|PDIMR
mdefine_line|#define PDIMR  (*(volatile unsigned long *)(GPIO_BASE+PDIMR_OFF))
DECL|macro|PDINT
mdefine_line|#define PDINT  (*(volatile unsigned long *)(GPIO_BASE+PDINT_OFF))
DECL|macro|PEDR
mdefine_line|#define PEDR   (*(volatile unsigned long *)(GPIO_BASE+PEDR_OFF))
DECL|macro|PEDDR
mdefine_line|#define PEDDR  (*(volatile unsigned long *)(GPIO_BASE+PEDDR_OFF))
DECL|macro|PESBSR
mdefine_line|#define PESBSR (*(volatile unsigned long *)(GPIO_BASE+PESBSR_OFF))
DECL|macro|PEEENR
mdefine_line|#define PEEENR (*(volatile unsigned long *)(GPIO_BASE+PEEENR_OFF))
DECL|macro|PEESNR
mdefine_line|#define PEESNR (*(volatile unsigned long *)(GPIO_BASE+PEESNR_OFF))
DECL|macro|PEESTR
mdefine_line|#define PEESTR (*(volatile unsigned long *)(GPIO_BASE+PEESTR_OFF))
DECL|macro|PEIMR
mdefine_line|#define PEIMR  (*(volatile unsigned long *)(GPIO_BASE+PEIMR_OFF))
DECL|macro|PEINT
mdefine_line|#define PEINT  (*(volatile unsigned long *)(GPIO_BASE+PEINT_OFF))
DECL|macro|VEE_EN
mdefine_line|#define VEE_EN         0x02
DECL|macro|BACKLIGHT_EN
mdefine_line|#define BACKLIGHT_EN   0x04
eof
