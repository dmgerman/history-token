multiline_comment|/*&n; * linux/include/asm-arm/ecard.h&n; *&n; * definitions for expansion cards&n; *&n; * This is a new system as from Linux 1.2.3&n; *&n; * Changelog:&n; *  11-12-1996&t;RMK&t;Further minor improvements&n; *  12-09-1997&t;RMK&t;Added interrupt enable/disable for card level&n; *&n; * Reference: Acorns Risc OS 3 Programmers Reference Manuals.&n; */
macro_line|#ifndef __ASM_ECARD_H
DECL|macro|__ASM_ECARD_H
mdefine_line|#define __ASM_ECARD_H
multiline_comment|/*&n; * Currently understood cards (but not necessarily&n; * supported):&n; *                        Manufacturer  Product ID&n; */
DECL|macro|MANU_ACORN
mdefine_line|#define MANU_ACORN&t;&t;0x0000
DECL|macro|PROD_ACORN_SCSI
mdefine_line|#define PROD_ACORN_SCSI&t;&t;&t;0x0002
DECL|macro|PROD_ACORN_ETHER1
mdefine_line|#define PROD_ACORN_ETHER1&t;&t;0x0003
DECL|macro|PROD_ACORN_MFM
mdefine_line|#define PROD_ACORN_MFM&t;&t;&t;0x000b
DECL|macro|MANU_ANT2
mdefine_line|#define MANU_ANT2&t;&t;0x0011
DECL|macro|PROD_ANT_ETHER3
mdefine_line|#define PROD_ANT_ETHER3&t;&t;&t;0x00a4
DECL|macro|MANU_ATOMWIDE
mdefine_line|#define MANU_ATOMWIDE&t;&t;0x0017
DECL|macro|PROD_ATOMWIDE_3PSERIAL
mdefine_line|#define PROD_ATOMWIDE_3PSERIAL&t;&t;0x0090
DECL|macro|MANU_IRLAM_INSTRUMENTS
mdefine_line|#define MANU_IRLAM_INSTRUMENTS&t;0x001f
DECL|macro|MANU_IRLAM_INSTRUMENTS_ETHERN
mdefine_line|#define MANU_IRLAM_INSTRUMENTS_ETHERN&t;0x5678
DECL|macro|MANU_OAK
mdefine_line|#define MANU_OAK&t;&t;0x0021
DECL|macro|PROD_OAK_SCSI
mdefine_line|#define PROD_OAK_SCSI&t;&t;&t;0x0058
DECL|macro|MANU_MORLEY
mdefine_line|#define MANU_MORLEY&t;&t;0x002b
DECL|macro|PROD_MORLEY_SCSI_UNCACHED
mdefine_line|#define PROD_MORLEY_SCSI_UNCACHED&t;0x0067
DECL|macro|MANU_CUMANA
mdefine_line|#define MANU_CUMANA&t;&t;0x003a
DECL|macro|PROD_CUMANA_SCSI_1
mdefine_line|#define PROD_CUMANA_SCSI_1&t;&t;0x00a0
DECL|macro|PROD_CUMANA_SCSI_2
mdefine_line|#define PROD_CUMANA_SCSI_2&t;&t;0x003a
DECL|macro|MANU_ICS
mdefine_line|#define MANU_ICS&t;&t;0x003c
DECL|macro|PROD_ICS_IDE
mdefine_line|#define PROD_ICS_IDE&t;&t;&t;0x00ae
DECL|macro|MANU_ICS2
mdefine_line|#define MANU_ICS2&t;&t;0x003d
DECL|macro|PROD_ICS2_IDE
mdefine_line|#define PROD_ICS2_IDE&t;&t;&t;0x00ae
DECL|macro|MANU_SERPORT
mdefine_line|#define MANU_SERPORT&t;&t;0x003f
DECL|macro|PROD_SERPORT_DSPORT
mdefine_line|#define PROD_SERPORT_DSPORT&t;&t;0x00b9
DECL|macro|MANU_I3
mdefine_line|#define MANU_I3&t;&t;&t;0x0046
DECL|macro|PROD_I3_ETHERLAN500
mdefine_line|#define PROD_I3_ETHERLAN500&t;&t;0x00d4
DECL|macro|PROD_I3_ETHERLAN600
mdefine_line|#define PROD_I3_ETHERLAN600&t;&t;0x00ec
DECL|macro|PROD_I3_ETHERLAN600A
mdefine_line|#define PROD_I3_ETHERLAN600A&t;&t;0x011e
DECL|macro|MANU_ANT
mdefine_line|#define MANU_ANT&t;&t;0x0053
DECL|macro|PROD_ANT_ETHERB
mdefine_line|#define PROD_ANT_ETHERB&t;&t;&t;0x00e4
DECL|macro|MANU_ALSYSTEMS
mdefine_line|#define MANU_ALSYSTEMS&t;&t;0x005b
DECL|macro|PROD_ALSYS_SCSIATAPI
mdefine_line|#define PROD_ALSYS_SCSIATAPI&t;&t;0x0107
DECL|macro|MANU_MCS
mdefine_line|#define MANU_MCS&t;&t;0x0063
DECL|macro|PROD_MCS_CONNECT32
mdefine_line|#define PROD_MCS_CONNECT32&t;&t;0x0125
DECL|macro|MANU_EESOX
mdefine_line|#define MANU_EESOX&t;&t;0x0064
DECL|macro|PROD_EESOX_SCSI2
mdefine_line|#define PROD_EESOX_SCSI2&t;&t;0x008c
DECL|macro|MANU_YELLOWSTONE
mdefine_line|#define MANU_YELLOWSTONE&t;0x0096
DECL|macro|PROD_YELLOWSTONE_RAPIDE32
mdefine_line|#define PROD_YELLOWSTONE_RAPIDE32&t;0x0120
macro_line|#ifdef ECARD_C
DECL|macro|CONST
mdefine_line|#define CONST
macro_line|#else
DECL|macro|CONST
mdefine_line|#define CONST const
macro_line|#endif
DECL|macro|MAX_ECARDS
mdefine_line|#define MAX_ECARDS&t;9
r_typedef
r_enum
(brace
multiline_comment|/* Cards address space&t;&t;*/
DECL|enumerator|ECARD_IOC
id|ECARD_IOC
comma
DECL|enumerator|ECARD_MEMC
id|ECARD_MEMC
comma
DECL|enumerator|ECARD_EASI
id|ECARD_EASI
DECL|typedef|card_type_t
)brace
id|card_type_t
suffix:semicolon
r_typedef
r_enum
(brace
multiline_comment|/* Speed for ECARD_IOC space&t;*/
DECL|enumerator|ECARD_SLOW
id|ECARD_SLOW
op_assign
l_int|0
comma
DECL|enumerator|ECARD_MEDIUM
id|ECARD_MEDIUM
op_assign
l_int|1
comma
DECL|enumerator|ECARD_FAST
id|ECARD_FAST
op_assign
l_int|2
comma
DECL|enumerator|ECARD_SYNC
id|ECARD_SYNC
op_assign
l_int|3
DECL|typedef|card_speed_t
)brace
id|card_speed_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* Card ID structure&t;&t;*/
DECL|member|manufacturer
r_int
r_int
id|manufacturer
suffix:semicolon
DECL|member|product
r_int
r_int
id|product
suffix:semicolon
DECL|typedef|card_ids
)brace
id|card_ids
suffix:semicolon
DECL|struct|in_ecid
r_struct
id|in_ecid
(brace
multiline_comment|/* Packed card ID information&t;*/
DECL|member|product
r_int
r_int
id|product
suffix:semicolon
multiline_comment|/* Product code&t;&t;&t;*/
DECL|member|manufacturer
r_int
r_int
id|manufacturer
suffix:semicolon
multiline_comment|/* Manufacturer code&t;&t;*/
DECL|member|id
r_int
r_char
id|id
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Simple ID&t;&t;&t;*/
DECL|member|cd
r_int
r_char
id|cd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Chunk dir present&t;&t;*/
DECL|member|is
r_int
r_char
id|is
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Interrupt status pointers&t;*/
DECL|member|w
r_int
r_char
id|w
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Width&t;&t;&t;*/
DECL|member|country
r_int
r_char
id|country
suffix:semicolon
multiline_comment|/* Country&t;&t;&t;*/
DECL|member|irqmask
r_int
r_char
id|irqmask
suffix:semicolon
multiline_comment|/* IRQ mask&t;&t;&t;*/
DECL|member|fiqmask
r_int
r_char
id|fiqmask
suffix:semicolon
multiline_comment|/* FIQ mask&t;&t;&t;*/
DECL|member|irqoff
r_int
r_int
id|irqoff
suffix:semicolon
multiline_comment|/* IRQ offset&t;&t;&t;*/
DECL|member|fiqoff
r_int
r_int
id|fiqoff
suffix:semicolon
multiline_comment|/* FIQ offset&t;&t;&t;*/
)brace
suffix:semicolon
DECL|typedef|ecard_t
r_typedef
r_struct
id|expansion_card
id|ecard_t
suffix:semicolon
DECL|typedef|loader_t
r_typedef
r_int
r_int
op_star
id|loader_t
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* Card handler routines&t;*/
DECL|member|irqenable
r_void
(paren
op_star
id|irqenable
)paren
(paren
id|ecard_t
op_star
id|ec
comma
r_int
id|irqnr
)paren
suffix:semicolon
DECL|member|irqdisable
r_void
(paren
op_star
id|irqdisable
)paren
(paren
id|ecard_t
op_star
id|ec
comma
r_int
id|irqnr
)paren
suffix:semicolon
DECL|member|irqpending
r_int
(paren
op_star
id|irqpending
)paren
(paren
id|ecard_t
op_star
id|ec
)paren
suffix:semicolon
DECL|member|fiqenable
r_void
(paren
op_star
id|fiqenable
)paren
(paren
id|ecard_t
op_star
id|ec
comma
r_int
id|fiqnr
)paren
suffix:semicolon
DECL|member|fiqdisable
r_void
(paren
op_star
id|fiqdisable
)paren
(paren
id|ecard_t
op_star
id|ec
comma
r_int
id|fiqnr
)paren
suffix:semicolon
DECL|member|fiqpending
r_int
(paren
op_star
id|fiqpending
)paren
(paren
id|ecard_t
op_star
id|ec
)paren
suffix:semicolon
DECL|typedef|expansioncard_ops_t
)brace
id|expansioncard_ops_t
suffix:semicolon
multiline_comment|/*&n; * This contains all the info needed on an expansion card&n; */
DECL|struct|expansion_card
r_struct
id|expansion_card
(brace
DECL|member|next
r_struct
id|expansion_card
op_star
id|next
suffix:semicolon
multiline_comment|/* Public data */
DECL|member|irqaddr
r_volatile
r_int
r_char
op_star
id|irqaddr
suffix:semicolon
multiline_comment|/* address of IRQ register&t;*/
DECL|member|fiqaddr
r_volatile
r_int
r_char
op_star
id|fiqaddr
suffix:semicolon
multiline_comment|/* address of FIQ register&t;*/
DECL|member|irqmask
r_int
r_char
id|irqmask
suffix:semicolon
multiline_comment|/* IRQ mask&t;&t;&t;*/
DECL|member|fiqmask
r_int
r_char
id|fiqmask
suffix:semicolon
multiline_comment|/* FIQ mask&t;&t;&t;*/
DECL|member|claimed
r_int
r_char
id|claimed
suffix:semicolon
multiline_comment|/* Card claimed?&t;&t;*/
DECL|member|irq_data
r_void
op_star
id|irq_data
suffix:semicolon
multiline_comment|/* Data for use for IRQ by card&t;*/
DECL|member|fiq_data
r_void
op_star
id|fiq_data
suffix:semicolon
multiline_comment|/* Data for use for FIQ by card&t;*/
DECL|member|ops
id|expansioncard_ops_t
op_star
id|ops
suffix:semicolon
multiline_comment|/* Enable/Disable Ops for card&t;*/
DECL|member|slot_no
id|CONST
r_int
r_int
id|slot_no
suffix:semicolon
multiline_comment|/* Slot number&t;&t;&t;*/
DECL|member|dma
id|CONST
r_int
r_int
id|dma
suffix:semicolon
multiline_comment|/* DMA number (for request_dma)&t;*/
DECL|member|irq
id|CONST
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ number (for request_irq)&t;*/
DECL|member|fiq
id|CONST
r_int
r_int
id|fiq
suffix:semicolon
multiline_comment|/* FIQ number (for request_irq)&t;*/
DECL|member|type
id|CONST
id|card_type_t
id|type
suffix:semicolon
multiline_comment|/* Type of card&t;&t;&t;*/
DECL|member|cid
id|CONST
r_struct
id|in_ecid
id|cid
suffix:semicolon
multiline_comment|/* Card Identification&t;&t;*/
multiline_comment|/* Private internal data */
DECL|member|card_desc
r_const
r_char
op_star
id|card_desc
suffix:semicolon
multiline_comment|/* Card description&t;&t;*/
DECL|member|podaddr
id|CONST
r_int
r_int
id|podaddr
suffix:semicolon
multiline_comment|/* Base Linux address for card&t;*/
DECL|member|loader
id|CONST
id|loader_t
id|loader
suffix:semicolon
multiline_comment|/* loader program */
)brace
suffix:semicolon
DECL|struct|in_chunk_dir
r_struct
id|in_chunk_dir
(brace
DECL|member|start_offset
r_int
r_int
id|start_offset
suffix:semicolon
r_union
(brace
DECL|member|string
r_int
r_char
id|string
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|d
)brace
id|d
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ecard_claim: claim an expansion card entry&n; */
DECL|macro|ecard_claim
mdefine_line|#define ecard_claim(ec) ((ec)-&gt;claimed = 1)
multiline_comment|/*&n; * ecard_release: release an expansion card entry&n; */
DECL|macro|ecard_release
mdefine_line|#define ecard_release(ec) ((ec)-&gt;claimed = 0)
multiline_comment|/*&n; * Start finding cards from the top of the list&n; */
r_extern
r_void
id|ecard_startfind
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Find an expansion card with the correct cid, product and manufacturer code&n; */
r_extern
r_struct
id|expansion_card
op_star
id|ecard_find
(paren
r_int
id|cid
comma
r_const
id|card_ids
op_star
id|ids
)paren
suffix:semicolon
multiline_comment|/*&n; * Read a chunk from an expansion card&n; * cd : where to put read data&n; * ec : expansion card info struct&n; * id : id number to find&n; * num: (n+1)&squot;th id to find.&n; */
r_extern
r_int
id|ecard_readchunk
(paren
r_struct
id|in_chunk_dir
op_star
id|cd
comma
r_struct
id|expansion_card
op_star
id|ec
comma
r_int
id|id
comma
r_int
id|num
)paren
suffix:semicolon
multiline_comment|/*&n; * Obtain the address of a card&n; */
r_extern
r_int
r_int
id|ecard_address
(paren
r_struct
id|expansion_card
op_star
id|ec
comma
id|card_type_t
id|card_type
comma
id|card_speed_t
id|speed
)paren
suffix:semicolon
macro_line|#ifdef ECARD_C
multiline_comment|/* Definitions internal to ecard.c - for it&squot;s use only!!&n; *&n; * External expansion card header as read from the card&n; */
DECL|struct|ex_ecid
r_struct
id|ex_ecid
(brace
DECL|member|r_irq
r_int
r_char
id|r_irq
suffix:colon
l_int|1
suffix:semicolon
DECL|member|r_zero
r_int
r_char
id|r_zero
suffix:colon
l_int|1
suffix:semicolon
DECL|member|r_fiq
r_int
r_char
id|r_fiq
suffix:colon
l_int|1
suffix:semicolon
DECL|member|r_id
r_int
r_char
id|r_id
suffix:colon
l_int|4
suffix:semicolon
DECL|member|r_a
r_int
r_char
id|r_a
suffix:colon
l_int|1
suffix:semicolon
DECL|member|r_cd
r_int
r_char
id|r_cd
suffix:colon
l_int|1
suffix:semicolon
DECL|member|r_is
r_int
r_char
id|r_is
suffix:colon
l_int|1
suffix:semicolon
DECL|member|r_w
r_int
r_char
id|r_w
suffix:colon
l_int|2
suffix:semicolon
DECL|member|r_r1
r_int
r_char
id|r_r1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|r_r2
r_int
r_char
id|r_r2
suffix:colon
l_int|8
suffix:semicolon
DECL|member|r_prod
r_int
r_char
id|r_prod
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|r_manu
r_int
r_char
id|r_manu
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|r_country
r_int
r_char
id|r_country
suffix:semicolon
DECL|member|r_irqmask
r_int
r_char
id|r_irqmask
suffix:semicolon
DECL|member|r_irqoff
r_int
r_char
id|r_irqoff
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|r_fiqmask
r_int
r_char
id|r_fiqmask
suffix:semicolon
DECL|member|r_fiqoff
r_int
r_char
id|r_fiqoff
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Chunk directory entry as read from the card&n; */
DECL|struct|ex_chunk_dir
r_struct
id|ex_chunk_dir
(brace
DECL|member|r_id
r_int
r_char
id|r_id
suffix:semicolon
DECL|member|r_len
r_int
r_char
id|r_len
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|r_start
r_int
r_int
id|r_start
suffix:semicolon
r_union
(brace
DECL|member|string
r_char
id|string
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|data
r_char
id|data
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|d
)brace
id|d
suffix:semicolon
DECL|macro|c_id
mdefine_line|#define c_id(x)&t;&t;((x)-&gt;r_id)
DECL|macro|c_len
mdefine_line|#define c_len(x)&t;((x)-&gt;r_len[0]|((x)-&gt;r_len[1]&lt;&lt;8)|((x)-&gt;r_len[2]&lt;&lt;16))
DECL|macro|c_start
mdefine_line|#define c_start(x)&t;((x)-&gt;r_start)
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
