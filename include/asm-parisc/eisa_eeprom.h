multiline_comment|/*&n; * eisa_eeprom.h - provide support for EISA adapters in PA-RISC machines&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * Copyright (c) 2001, 2002 Daniel Engstrom &lt;5116@telia.com&gt;&n; *&n; */
macro_line|#ifndef ASM_EISA_EEPROM_H
DECL|macro|ASM_EISA_EEPROM_H
mdefine_line|#define ASM_EISA_EEPROM_H
DECL|macro|HPEE_MAX_LENGTH
mdefine_line|#define HPEE_MAX_LENGTH       0x2000&t;/* maximum eeprom length */
DECL|macro|HPEE_SLOT_INFO
mdefine_line|#define HPEE_SLOT_INFO(slot) (20+(48*slot))
DECL|struct|eeprom_header
r_struct
id|eeprom_header
(brace
DECL|member|num_writes
id|u_int32_t
id|num_writes
suffix:semicolon
multiline_comment|/* number of writes */
DECL|member|flags
id|u_int8_t
id|flags
suffix:semicolon
multiline_comment|/* flags, usage? */
DECL|member|ver_maj
id|u_int8_t
id|ver_maj
suffix:semicolon
DECL|member|ver_min
id|u_int8_t
id|ver_min
suffix:semicolon
DECL|member|num_slots
id|u_int8_t
id|num_slots
suffix:semicolon
multiline_comment|/* number of EISA slots in system */
DECL|member|csum
id|u_int16_t
id|csum
suffix:semicolon
multiline_comment|/* checksum, I don&squot;t know how to calulate this */
DECL|member|pad
id|u_int8_t
id|pad
(braket
l_int|10
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|eeprom_eisa_slot_info
r_struct
id|eeprom_eisa_slot_info
(brace
DECL|member|eisa_slot_id
id|u_int32_t
id|eisa_slot_id
suffix:semicolon
DECL|member|config_data_offset
id|u_int32_t
id|config_data_offset
suffix:semicolon
DECL|member|num_writes
id|u_int32_t
id|num_writes
suffix:semicolon
DECL|member|csum
id|u_int16_t
id|csum
suffix:semicolon
DECL|member|num_functions
id|u_int16_t
id|num_functions
suffix:semicolon
DECL|member|config_data_length
id|u_int16_t
id|config_data_length
suffix:semicolon
multiline_comment|/* bits 0..3 are the duplicate slot id */
DECL|macro|HPEE_SLOT_INFO_EMBEDDED
mdefine_line|#define HPEE_SLOT_INFO_EMBEDDED  0x10
DECL|macro|HPEE_SLOT_INFO_VIRTUAL
mdefine_line|#define HPEE_SLOT_INFO_VIRTUAL   0x20
DECL|macro|HPEE_SLOT_INFO_NO_READID
mdefine_line|#define HPEE_SLOT_INFO_NO_READID 0x40
DECL|macro|HPEE_SLOT_INFO_DUPLICATE
mdefine_line|#define HPEE_SLOT_INFO_DUPLICATE 0x80
DECL|member|slot_info
id|u_int8_t
id|slot_info
suffix:semicolon
DECL|macro|HPEE_SLOT_FEATURES_ENABLE
mdefine_line|#define HPEE_SLOT_FEATURES_ENABLE         0x01
DECL|macro|HPEE_SLOT_FEATURES_IOCHK
mdefine_line|#define HPEE_SLOT_FEATURES_IOCHK          0x02
DECL|macro|HPEE_SLOT_FEATURES_CFG_INCOMPLETE
mdefine_line|#define HPEE_SLOT_FEATURES_CFG_INCOMPLETE 0x80
DECL|member|slot_features
id|u_int8_t
id|slot_features
suffix:semicolon
DECL|member|ver_min
id|u_int8_t
id|ver_min
suffix:semicolon
DECL|member|ver_maj
id|u_int8_t
id|ver_maj
suffix:semicolon
DECL|macro|HPEE_FUNCTION_INFO_HAVE_TYPE
mdefine_line|#define HPEE_FUNCTION_INFO_HAVE_TYPE      0x01
DECL|macro|HPEE_FUNCTION_INFO_HAVE_MEMORY
mdefine_line|#define HPEE_FUNCTION_INFO_HAVE_MEMORY    0x02
DECL|macro|HPEE_FUNCTION_INFO_HAVE_IRQ
mdefine_line|#define HPEE_FUNCTION_INFO_HAVE_IRQ       0x04
DECL|macro|HPEE_FUNCTION_INFO_HAVE_DMA
mdefine_line|#define HPEE_FUNCTION_INFO_HAVE_DMA       0x08
DECL|macro|HPEE_FUNCTION_INFO_HAVE_PORT
mdefine_line|#define HPEE_FUNCTION_INFO_HAVE_PORT      0x10
DECL|macro|HPEE_FUNCTION_INFO_HAVE_PORT_INIT
mdefine_line|#define HPEE_FUNCTION_INFO_HAVE_PORT_INIT 0x20
multiline_comment|/* I think there are two slighty different &n; * versions of the function_info field &n; * one int the fixed header and one optional &n; * in the parsed slot data area */
DECL|macro|HPEE_FUNCTION_INFO_HAVE_FUNCTION
mdefine_line|#define HPEE_FUNCTION_INFO_HAVE_FUNCTION  0x01
DECL|macro|HPEE_FUNCTION_INFO_F_DISABLED
mdefine_line|#define HPEE_FUNCTION_INFO_F_DISABLED     0x80
DECL|macro|HPEE_FUNCTION_INFO_CFG_FREE_FORM
mdefine_line|#define HPEE_FUNCTION_INFO_CFG_FREE_FORM  0x40
DECL|member|function_info
id|u_int8_t
id|function_info
suffix:semicolon
DECL|macro|HPEE_FLAG_BOARD_IS_ISA
mdefine_line|#define HPEE_FLAG_BOARD_IS_ISA&t;&t;  0x01 /* flag and minor version for isa board */
DECL|member|flags
id|u_int8_t
id|flags
suffix:semicolon
DECL|member|pad
id|u_int8_t
id|pad
(braket
l_int|24
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|HPEE_MEMORY_MAX_ENT
mdefine_line|#define HPEE_MEMORY_MAX_ENT   9
multiline_comment|/* memory descriptor: byte 0 */
DECL|macro|HPEE_MEMORY_WRITABLE
mdefine_line|#define HPEE_MEMORY_WRITABLE  0x01
DECL|macro|HPEE_MEMORY_CACHABLE
mdefine_line|#define HPEE_MEMORY_CACHABLE  0x02
DECL|macro|HPEE_MEMORY_TYPE_MASK
mdefine_line|#define HPEE_MEMORY_TYPE_MASK 0x18
DECL|macro|HPEE_MEMORY_TYPE_SYS
mdefine_line|#define HPEE_MEMORY_TYPE_SYS  0x00
DECL|macro|HPEE_MEMORY_TYPE_EXP
mdefine_line|#define HPEE_MEMORY_TYPE_EXP  0x08
DECL|macro|HPEE_MEMORY_TYPE_VIR
mdefine_line|#define HPEE_MEMORY_TYPE_VIR  0x10
DECL|macro|HPEE_MEMORY_TYPE_OTH
mdefine_line|#define HPEE_MEMORY_TYPE_OTH  0x18
DECL|macro|HPEE_MEMORY_SHARED
mdefine_line|#define HPEE_MEMORY_SHARED    0x20
DECL|macro|HPEE_MEMORY_MORE
mdefine_line|#define HPEE_MEMORY_MORE      0x80
multiline_comment|/* memory descriptor: byte 1 */
DECL|macro|HPEE_MEMORY_WIDTH_MASK
mdefine_line|#define HPEE_MEMORY_WIDTH_MASK 0x03
DECL|macro|HPEE_MEMORY_WIDTH_BYTE
mdefine_line|#define HPEE_MEMORY_WIDTH_BYTE 0x00
DECL|macro|HPEE_MEMORY_WIDTH_WORD
mdefine_line|#define HPEE_MEMORY_WIDTH_WORD 0x01
DECL|macro|HPEE_MEMORY_WIDTH_DWORD
mdefine_line|#define HPEE_MEMORY_WIDTH_DWORD 0x02
DECL|macro|HPEE_MEMORY_DECODE_MASK
mdefine_line|#define HPEE_MEMORY_DECODE_MASK 0x0c
DECL|macro|HPEE_MEMORY_DECODE_20BITS
mdefine_line|#define HPEE_MEMORY_DECODE_20BITS 0x00
DECL|macro|HPEE_MEMORY_DECODE_24BITS
mdefine_line|#define HPEE_MEMORY_DECODE_24BITS 0x04
DECL|macro|HPEE_MEMORY_DECODE_32BITS
mdefine_line|#define HPEE_MEMORY_DECODE_32BITS 0x08
multiline_comment|/* byte 2 and 3 are a 16bit LE value&n; * containging the memory size in kilobytes */
multiline_comment|/* byte 4,5,6 are a 24bit LE value&n; * containing the memory base address */
DECL|macro|HPEE_IRQ_MAX_ENT
mdefine_line|#define HPEE_IRQ_MAX_ENT      7
multiline_comment|/* Interrupt entry: byte 0 */
DECL|macro|HPEE_IRQ_CHANNEL_MASK
mdefine_line|#define HPEE_IRQ_CHANNEL_MASK 0xf
DECL|macro|HPEE_IRQ_TRIG_LEVEL
mdefine_line|#define HPEE_IRQ_TRIG_LEVEL   0x20
DECL|macro|HPEE_IRQ_MORE
mdefine_line|#define HPEE_IRQ_MORE         0x80
multiline_comment|/* byte 1 seems to be unused */
DECL|macro|HPEE_DMA_MAX_ENT
mdefine_line|#define HPEE_DMA_MAX_ENT     4
multiline_comment|/* dma entry: byte 0 */
DECL|macro|HPEE_DMA_CHANNEL_MASK
mdefine_line|#define HPEE_DMA_CHANNEL_MASK 7
DECL|macro|HPEE_DMA_SIZE_MASK
mdefine_line|#define HPEE_DMA_SIZE_MASK&t;0xc
DECL|macro|HPEE_DMA_SIZE_BYTE
mdefine_line|#define HPEE_DMA_SIZE_BYTE&t;0x0
DECL|macro|HPEE_DMA_SIZE_WORD
mdefine_line|#define HPEE_DMA_SIZE_WORD&t;0x4
DECL|macro|HPEE_DMA_SIZE_DWORD
mdefine_line|#define HPEE_DMA_SIZE_DWORD&t;0x8
DECL|macro|HPEE_DMA_SHARED
mdefine_line|#define HPEE_DMA_SHARED      0x40
DECL|macro|HPEE_DMA_MORE
mdefine_line|#define HPEE_DMA_MORE        0x80
multiline_comment|/* dma entry: byte 1 */
DECL|macro|HPEE_DMA_TIMING_MASK
mdefine_line|#define HPEE_DMA_TIMING_MASK 0x30
DECL|macro|HPEE_DMA_TIMING_ISA
mdefine_line|#define HPEE_DMA_TIMING_ISA&t;0x0
DECL|macro|HPEE_DMA_TIMING_TYPEA
mdefine_line|#define HPEE_DMA_TIMING_TYPEA 0x10
DECL|macro|HPEE_DMA_TIMING_TYPEB
mdefine_line|#define HPEE_DMA_TIMING_TYPEB 0x20
DECL|macro|HPEE_DMA_TIMING_TYPEC
mdefine_line|#define HPEE_DMA_TIMING_TYPEC 0x30
DECL|macro|HPEE_PORT_MAX_ENT
mdefine_line|#define HPEE_PORT_MAX_ENT 20
multiline_comment|/* port entry byte 0 */
DECL|macro|HPEE_PORT_SIZE_MASK
mdefine_line|#define HPEE_PORT_SIZE_MASK 0x1f
DECL|macro|HPEE_PORT_SHARED
mdefine_line|#define HPEE_PORT_SHARED    0x40
DECL|macro|HPEE_PORT_MORE
mdefine_line|#define HPEE_PORT_MORE      0x80
multiline_comment|/* byte 1 and 2 is a 16bit LE value&n; * conating the start port number */
DECL|macro|HPEE_PORT_INIT_MAX_LEN
mdefine_line|#define HPEE_PORT_INIT_MAX_LEN     60 /* in bytes here */
multiline_comment|/* port init entry byte 0 */
DECL|macro|HPEE_PORT_INIT_WIDTH_MASK
mdefine_line|#define HPEE_PORT_INIT_WIDTH_MASK  0x3
DECL|macro|HPEE_PORT_INIT_WIDTH_BYTE
mdefine_line|#define HPEE_PORT_INIT_WIDTH_BYTE  0x0
DECL|macro|HPEE_PORT_INIT_WIDTH_WORD
mdefine_line|#define HPEE_PORT_INIT_WIDTH_WORD  0x1
DECL|macro|HPEE_PORT_INIT_WIDTH_DWORD
mdefine_line|#define HPEE_PORT_INIT_WIDTH_DWORD 0x2
DECL|macro|HPEE_PORT_INIT_MASK
mdefine_line|#define HPEE_PORT_INIT_MASK        0x4
DECL|macro|HPEE_PORT_INIT_MORE
mdefine_line|#define HPEE_PORT_INIT_MORE        0x80
DECL|macro|HPEE_SELECTION_MAX_ENT
mdefine_line|#define HPEE_SELECTION_MAX_ENT 26
DECL|macro|HPEE_TYPE_MAX_LEN
mdefine_line|#define HPEE_TYPE_MAX_LEN    80
macro_line|#endif
eof
