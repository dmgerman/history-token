multiline_comment|/* Miscellaneous definitions for VIA chipsets&n;   Currently used only by drivers/parport/parport_pc.c */
multiline_comment|/* Values for SuperIO function select configuration register */
DECL|macro|VIA_FUNCTION_PARPORT_SPP
mdefine_line|#define VIA_FUNCTION_PARPORT_SPP     0x00
DECL|macro|VIA_FUNCTION_PARPORT_ECP
mdefine_line|#define VIA_FUNCTION_PARPORT_ECP     0x01
DECL|macro|VIA_FUNCTION_PARPORT_EPP
mdefine_line|#define VIA_FUNCTION_PARPORT_EPP     0x02
DECL|macro|VIA_FUNCTION_PARPORT_DISABLE
mdefine_line|#define VIA_FUNCTION_PARPORT_DISABLE 0x03
DECL|macro|VIA_FUNCTION_PROBE
mdefine_line|#define VIA_FUNCTION_PROBE           0xFF /* Special magic value to be used in code, not to be written into chip */
multiline_comment|/* Bits for parallel port mode configuration register */
DECL|macro|VIA_PARPORT_ECPEPP
mdefine_line|#define VIA_PARPORT_ECPEPP 0X20
DECL|macro|VIA_PARPORT_BIDIR
mdefine_line|#define VIA_PARPORT_BIDIR  0x80
multiline_comment|/* VIA configuration registers */
DECL|macro|VIA_CONFIG_INDEX
mdefine_line|#define VIA_CONFIG_INDEX 0x3F0
DECL|macro|VIA_CONFIG_DATA
mdefine_line|#define VIA_CONFIG_DATA  0x3F1
multiline_comment|/* Mask for parallel port IRQ bits (in ISA PnP IRQ routing register 1) */
DECL|macro|VIA_IRQCONTROL_PARALLEL
mdefine_line|#define VIA_IRQCONTROL_PARALLEL 0xF0
multiline_comment|/* Mask for parallel port DMA bits (in ISA PnP DMA routing register) */
DECL|macro|VIA_DMACONTROL_PARALLEL
mdefine_line|#define VIA_DMACONTROL_PARALLEL 0x0C
eof
