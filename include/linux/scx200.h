multiline_comment|/* linux/include/linux/scx200.h&n;&n;   Copyright (c) 2001,2002 Christer Weinigel &lt;wingel@nano-system.com&gt;&n;&n;   Defines for the National Semiconductor SCx200 Processors&n;*/
multiline_comment|/* Interesting stuff for the National Semiconductor SCx200 CPU */
multiline_comment|/* F0 PCI Header/Bridge Configuration Registers */
DECL|macro|SCx200_DOCCS_BASE
mdefine_line|#define SCx200_DOCCS_BASE 0x78&t;/* DOCCS Base Address Register */
DECL|macro|SCx200_DOCCS_CTRL
mdefine_line|#define SCx200_DOCCS_CTRL 0x7c&t;/* DOCCS Control Register */
multiline_comment|/* GPIO Register Block */
DECL|macro|SCx200_GPIO_SIZE
mdefine_line|#define SCx200_GPIO_SIZE 0x2c&t;/* Size of GPIO register block */
multiline_comment|/* General Configuration Block */
DECL|macro|SCx200_CB_BASE
mdefine_line|#define SCx200_CB_BASE 0x9000&t;/* Base fixed at 0x9000 according to errata */
multiline_comment|/* Watchdog Timer */
DECL|macro|SCx200_WDT_OFFSET
mdefine_line|#define SCx200_WDT_OFFSET 0x00&t;/* offset within configuration block */
DECL|macro|SCx200_WDT_SIZE
mdefine_line|#define SCx200_WDT_SIZE 0x05&t;/* size */
DECL|macro|SCx200_WDT_WDTO
mdefine_line|#define SCx200_WDT_WDTO 0x00&t;/* Time-Out Register */
DECL|macro|SCx200_WDT_WDCNFG
mdefine_line|#define SCx200_WDT_WDCNFG 0x02&t;/* Configuration Register */
DECL|macro|SCx200_WDT_WDSTS
mdefine_line|#define SCx200_WDT_WDSTS 0x04&t;/* Status Register */
DECL|macro|SCx200_WDT_WDSTS_WDOVF
mdefine_line|#define SCx200_WDT_WDSTS_WDOVF (1&lt;&lt;0) /* Overflow bit */
multiline_comment|/* High Resolution Timer */
DECL|macro|SCx200_TIMER_OFFSET
mdefine_line|#define SCx200_TIMER_OFFSET 0x08
DECL|macro|SCx200_TIMER_SIZE
mdefine_line|#define SCx200_TIMER_SIZE 0x05
multiline_comment|/* Clock Generators */
DECL|macro|SCx200_CLOCKGEN_OFFSET
mdefine_line|#define SCx200_CLOCKGEN_OFFSET 0x10
DECL|macro|SCx200_CLOCKGEN_SIZE
mdefine_line|#define SCx200_CLOCKGEN_SIZE 0x10
multiline_comment|/* Pin Multiplexing and Miscellaneous Configuration Registers */
DECL|macro|SCx200_MISC_OFFSET
mdefine_line|#define SCx200_MISC_OFFSET 0x30
DECL|macro|SCx200_MISC_SIZE
mdefine_line|#define SCx200_MISC_SIZE 0x10
DECL|macro|SCx200_PMR
mdefine_line|#define SCx200_PMR 0x30&t;&t;/* Pin Multiplexing Register */
DECL|macro|SCx200_MCR
mdefine_line|#define SCx200_MCR 0x34&t;&t;/* Miscellaneous Configuration Register */
DECL|macro|SCx200_INTSEL
mdefine_line|#define SCx200_INTSEL 0x38&t;/* Interrupt Selection Register */
DECL|macro|SCx200_IID
mdefine_line|#define SCx200_IID 0x3c&t;&t;/* IA On a Chip Identification Number Reg */
DECL|macro|SCx200_REV
mdefine_line|#define SCx200_REV 0x3d&t;&t;/* Revision Register */
DECL|macro|SCx200_CBA
mdefine_line|#define SCx200_CBA 0x3e&t;&t;/* Configuration Base Address Register */
multiline_comment|/* Verify that the configuration block really is there */
DECL|macro|scx200_cb_probe
mdefine_line|#define scx200_cb_probe(base) (inw((base) + SCx200_CBA) == (base))
multiline_comment|/*&n;    Local variables:&n;        compile-command: &quot;make -C ../.. bzImage modules&quot;&n;        c-basic-offset: 8&n;    End:&n;*/
eof
