multiline_comment|/******************************************************************************&n; *&n; * Module Name: amlresrc.h - AML resource descriptors&n; *              $Revision: 20 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __AMLRESRC_H
DECL|macro|__AMLRESRC_H
mdefine_line|#define __AMLRESRC_H
DECL|macro|ASL_RESNAME_ADDRESS
mdefine_line|#define ASL_RESNAME_ADDRESS                     &quot;_ADR&quot;
DECL|macro|ASL_RESNAME_ALIGNMENT
mdefine_line|#define ASL_RESNAME_ALIGNMENT                   &quot;_ALN&quot;
DECL|macro|ASL_RESNAME_ADDRESSSPACE
mdefine_line|#define ASL_RESNAME_ADDRESSSPACE                &quot;_ASI&quot;
DECL|macro|ASL_RESNAME_BASEADDRESS
mdefine_line|#define ASL_RESNAME_BASEADDRESS                 &quot;_BAS&quot;
DECL|macro|ASL_RESNAME_BUSMASTER
mdefine_line|#define ASL_RESNAME_BUSMASTER                   &quot;_BM_&quot;  /* Master(1), Slave(0) */
DECL|macro|ASL_RESNAME_DECODE
mdefine_line|#define ASL_RESNAME_DECODE                      &quot;_DEC&quot;
DECL|macro|ASL_RESNAME_DMA
mdefine_line|#define ASL_RESNAME_DMA                         &quot;_DMA&quot;
DECL|macro|ASL_RESNAME_DMATYPE
mdefine_line|#define ASL_RESNAME_DMATYPE                     &quot;_TYP&quot;  /* Compatible(0), A(1), B(2), F(3) */
DECL|macro|ASL_RESNAME_GRANULARITY
mdefine_line|#define ASL_RESNAME_GRANULARITY                 &quot;_GRA&quot;
DECL|macro|ASL_RESNAME_INTERRUPT
mdefine_line|#define ASL_RESNAME_INTERRUPT                   &quot;_INT&quot;
DECL|macro|ASL_RESNAME_INTERRUPTLEVEL
mdefine_line|#define ASL_RESNAME_INTERRUPTLEVEL              &quot;_LL_&quot;  /* Active_lo(1), Active_hi(0) */
DECL|macro|ASL_RESNAME_INTERRUPTSHARE
mdefine_line|#define ASL_RESNAME_INTERRUPTSHARE              &quot;_SHR&quot;  /* Shareable(1), No_share(0) */
DECL|macro|ASL_RESNAME_INTERRUPTTYPE
mdefine_line|#define ASL_RESNAME_INTERRUPTTYPE               &quot;_HE_&quot;  /* Edge(1), Level(0) */
DECL|macro|ASL_RESNAME_LENGTH
mdefine_line|#define ASL_RESNAME_LENGTH                      &quot;_LEN&quot;
DECL|macro|ASL_RESNAME_MEMATTRIBUTES
mdefine_line|#define ASL_RESNAME_MEMATTRIBUTES               &quot;_MTP&quot;  /* Memory(0), Reserved(1), ACPI(2), NVS(3) */
DECL|macro|ASL_RESNAME_MEMTYPE
mdefine_line|#define ASL_RESNAME_MEMTYPE                     &quot;_MEM&quot;  /* Non_cache(0), Cacheable(1) Cache+combine(2), Cache+prefetch(3) */
DECL|macro|ASL_RESNAME_MAXADDR
mdefine_line|#define ASL_RESNAME_MAXADDR                     &quot;_MAX&quot;
DECL|macro|ASL_RESNAME_MINADDR
mdefine_line|#define ASL_RESNAME_MINADDR                     &quot;_MIN&quot;
DECL|macro|ASL_RESNAME_MAXTYPE
mdefine_line|#define ASL_RESNAME_MAXTYPE                     &quot;_MAF&quot;
DECL|macro|ASL_RESNAME_MINTYPE
mdefine_line|#define ASL_RESNAME_MINTYPE                     &quot;_MIF&quot;
DECL|macro|ASL_RESNAME_REGISTERBITOFFSET
mdefine_line|#define ASL_RESNAME_REGISTERBITOFFSET           &quot;_RBO&quot;
DECL|macro|ASL_RESNAME_REGISTERBITWIDTH
mdefine_line|#define ASL_RESNAME_REGISTERBITWIDTH            &quot;_RBW&quot;
DECL|macro|ASL_RESNAME_RANGETYPE
mdefine_line|#define ASL_RESNAME_RANGETYPE                   &quot;_RNG&quot;
DECL|macro|ASL_RESNAME_READWRITETYPE
mdefine_line|#define ASL_RESNAME_READWRITETYPE               &quot;_RW_&quot;  /* Read_only(0), Writeable (1) */
DECL|macro|ASL_RESNAME_TRANSLATION
mdefine_line|#define ASL_RESNAME_TRANSLATION                 &quot;_TRA&quot;
DECL|macro|ASL_RESNAME_TRANSTYPE
mdefine_line|#define ASL_RESNAME_TRANSTYPE                   &quot;_TRS&quot;  /* Sparse(1), Dense(0) */
DECL|macro|ASL_RESNAME_TYPE
mdefine_line|#define ASL_RESNAME_TYPE                        &quot;_TTP&quot;  /* Translation(1), Static (0) */
DECL|macro|ASL_RESNAME_XFERTYPE
mdefine_line|#define ASL_RESNAME_XFERTYPE                    &quot;_SIZ&quot;  /* 8(0), 8_and16(1), 16(2) */
multiline_comment|/* Default sizes for &quot;small&quot; resource descriptors */
DECL|macro|ASL_RDESC_IRQ_SIZE
mdefine_line|#define ASL_RDESC_IRQ_SIZE                      0x02
DECL|macro|ASL_RDESC_DMA_SIZE
mdefine_line|#define ASL_RDESC_DMA_SIZE                      0x02
DECL|macro|ASL_RDESC_ST_DEPEND_SIZE
mdefine_line|#define ASL_RDESC_ST_DEPEND_SIZE                0x00
DECL|macro|ASL_RDESC_END_DEPEND_SIZE
mdefine_line|#define ASL_RDESC_END_DEPEND_SIZE               0x00
DECL|macro|ASL_RDESC_IO_SIZE
mdefine_line|#define ASL_RDESC_IO_SIZE                       0x07
DECL|macro|ASL_RDESC_FIXED_IO_SIZE
mdefine_line|#define ASL_RDESC_FIXED_IO_SIZE                 0x03
DECL|macro|ASL_RDESC_END_TAG_SIZE
mdefine_line|#define ASL_RDESC_END_TAG_SIZE                  0x01
DECL|struct|asl_resource_node
r_typedef
r_struct
id|asl_resource_node
(brace
DECL|member|buffer_length
id|u32
id|buffer_length
suffix:semicolon
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
DECL|member|next
r_struct
id|asl_resource_node
op_star
id|next
suffix:semicolon
DECL|typedef|ASL_RESOURCE_NODE
)brace
id|ASL_RESOURCE_NODE
suffix:semicolon
multiline_comment|/*&n; * Resource descriptors defined in the ACPI specification.&n; *&n; * Alignment must be BYTE because these descriptors&n; * are used to overlay the AML byte stream.&n; */
macro_line|#pragma pack(1)
DECL|struct|asl_irq_format_desc
r_typedef
r_struct
id|asl_irq_format_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|irq_mask
id|u16
id|irq_mask
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|typedef|ASL_IRQ_FORMAT_DESC
)brace
id|ASL_IRQ_FORMAT_DESC
suffix:semicolon
DECL|struct|asl_irq_noflags_desc
r_typedef
r_struct
id|asl_irq_noflags_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|irq_mask
id|u16
id|irq_mask
suffix:semicolon
DECL|typedef|ASL_IRQ_NOFLAGS_DESC
)brace
id|ASL_IRQ_NOFLAGS_DESC
suffix:semicolon
DECL|struct|asl_dma_format_desc
r_typedef
r_struct
id|asl_dma_format_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|dma_channel_mask
id|u8
id|dma_channel_mask
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|typedef|ASL_DMA_FORMAT_DESC
)brace
id|ASL_DMA_FORMAT_DESC
suffix:semicolon
DECL|struct|asl_start_dependent_desc
r_typedef
r_struct
id|asl_start_dependent_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|typedef|ASL_START_DEPENDENT_DESC
)brace
id|ASL_START_DEPENDENT_DESC
suffix:semicolon
DECL|struct|asl_start_dependent_noprio_desc
r_typedef
r_struct
id|asl_start_dependent_noprio_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|typedef|ASL_START_DEPENDENT_NOPRIO_DESC
)brace
id|ASL_START_DEPENDENT_NOPRIO_DESC
suffix:semicolon
DECL|struct|asl_end_dependent_desc
r_typedef
r_struct
id|asl_end_dependent_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|typedef|ASL_END_DEPENDENT_DESC
)brace
id|ASL_END_DEPENDENT_DESC
suffix:semicolon
DECL|struct|asl_io_port_desc
r_typedef
r_struct
id|asl_io_port_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|information
id|u8
id|information
suffix:semicolon
DECL|member|address_min
id|u16
id|address_min
suffix:semicolon
DECL|member|address_max
id|u16
id|address_max
suffix:semicolon
DECL|member|alignment
id|u8
id|alignment
suffix:semicolon
DECL|member|length
id|u8
id|length
suffix:semicolon
DECL|typedef|ASL_IO_PORT_DESC
)brace
id|ASL_IO_PORT_DESC
suffix:semicolon
DECL|struct|asl_fixed_io_port_desc
r_typedef
r_struct
id|asl_fixed_io_port_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|base_address
id|u16
id|base_address
suffix:semicolon
DECL|member|length
id|u8
id|length
suffix:semicolon
DECL|typedef|ASL_FIXED_IO_PORT_DESC
)brace
id|ASL_FIXED_IO_PORT_DESC
suffix:semicolon
DECL|struct|asl_small_vendor_desc
r_typedef
r_struct
id|asl_small_vendor_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|vendor_defined
id|u8
id|vendor_defined
(braket
l_int|7
)braket
suffix:semicolon
DECL|typedef|ASL_SMALL_VENDOR_DESC
)brace
id|ASL_SMALL_VENDOR_DESC
suffix:semicolon
DECL|struct|asl_end_tag_desc
r_typedef
r_struct
id|asl_end_tag_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|checksum
id|u8
id|checksum
suffix:semicolon
DECL|typedef|ASL_END_TAG_DESC
)brace
id|ASL_END_TAG_DESC
suffix:semicolon
multiline_comment|/* LARGE descriptors */
DECL|struct|asl_memory_24_desc
r_typedef
r_struct
id|asl_memory_24_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|information
id|u8
id|information
suffix:semicolon
DECL|member|address_min
id|u16
id|address_min
suffix:semicolon
DECL|member|address_max
id|u16
id|address_max
suffix:semicolon
DECL|member|alignment
id|u16
id|alignment
suffix:semicolon
DECL|member|range_length
id|u16
id|range_length
suffix:semicolon
DECL|typedef|ASL_MEMORY_24_DESC
)brace
id|ASL_MEMORY_24_DESC
suffix:semicolon
DECL|struct|asl_large_vendor_desc
r_typedef
r_struct
id|asl_large_vendor_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|vendor_defined
id|u8
id|vendor_defined
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|ASL_LARGE_VENDOR_DESC
)brace
id|ASL_LARGE_VENDOR_DESC
suffix:semicolon
DECL|struct|asl_memory_32_desc
r_typedef
r_struct
id|asl_memory_32_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|information
id|u8
id|information
suffix:semicolon
DECL|member|address_min
id|u32
id|address_min
suffix:semicolon
DECL|member|address_max
id|u32
id|address_max
suffix:semicolon
DECL|member|alignment
id|u32
id|alignment
suffix:semicolon
DECL|member|range_length
id|u32
id|range_length
suffix:semicolon
DECL|typedef|ASL_MEMORY_32_DESC
)brace
id|ASL_MEMORY_32_DESC
suffix:semicolon
DECL|struct|asl_fixed_memory_32_desc
r_typedef
r_struct
id|asl_fixed_memory_32_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|information
id|u8
id|information
suffix:semicolon
DECL|member|base_address
id|u32
id|base_address
suffix:semicolon
DECL|member|range_length
id|u32
id|range_length
suffix:semicolon
DECL|typedef|ASL_FIXED_MEMORY_32_DESC
)brace
id|ASL_FIXED_MEMORY_32_DESC
suffix:semicolon
DECL|struct|asl_qword_address_desc
r_typedef
r_struct
id|asl_qword_address_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|resource_type
id|u8
id|resource_type
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|specific_flags
id|u8
id|specific_flags
suffix:semicolon
DECL|member|granularity
id|u64
id|granularity
suffix:semicolon
DECL|member|address_min
id|u64
id|address_min
suffix:semicolon
DECL|member|address_max
id|u64
id|address_max
suffix:semicolon
DECL|member|translation_offset
id|u64
id|translation_offset
suffix:semicolon
DECL|member|address_length
id|u64
id|address_length
suffix:semicolon
DECL|member|optional_fields
id|u8
id|optional_fields
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|ASL_QWORD_ADDRESS_DESC
)brace
id|ASL_QWORD_ADDRESS_DESC
suffix:semicolon
DECL|struct|asl_dword_address_desc
r_typedef
r_struct
id|asl_dword_address_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|resource_type
id|u8
id|resource_type
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|specific_flags
id|u8
id|specific_flags
suffix:semicolon
DECL|member|granularity
id|u32
id|granularity
suffix:semicolon
DECL|member|address_min
id|u32
id|address_min
suffix:semicolon
DECL|member|address_max
id|u32
id|address_max
suffix:semicolon
DECL|member|translation_offset
id|u32
id|translation_offset
suffix:semicolon
DECL|member|address_length
id|u32
id|address_length
suffix:semicolon
DECL|member|optional_fields
id|u8
id|optional_fields
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|ASL_DWORD_ADDRESS_DESC
)brace
id|ASL_DWORD_ADDRESS_DESC
suffix:semicolon
DECL|struct|asl_word_address_desc
r_typedef
r_struct
id|asl_word_address_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|resource_type
id|u8
id|resource_type
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|specific_flags
id|u8
id|specific_flags
suffix:semicolon
DECL|member|granularity
id|u16
id|granularity
suffix:semicolon
DECL|member|address_min
id|u16
id|address_min
suffix:semicolon
DECL|member|address_max
id|u16
id|address_max
suffix:semicolon
DECL|member|translation_offset
id|u16
id|translation_offset
suffix:semicolon
DECL|member|address_length
id|u16
id|address_length
suffix:semicolon
DECL|member|optional_fields
id|u8
id|optional_fields
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|ASL_WORD_ADDRESS_DESC
)brace
id|ASL_WORD_ADDRESS_DESC
suffix:semicolon
DECL|struct|asl_extended_xrupt_desc
r_typedef
r_struct
id|asl_extended_xrupt_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|table_length
id|u8
id|table_length
suffix:semicolon
DECL|member|interrupt_number
id|u32
id|interrupt_number
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Res_source_index, Res_source optional fields follow */
DECL|typedef|ASL_EXTENDED_XRUPT_DESC
)brace
id|ASL_EXTENDED_XRUPT_DESC
suffix:semicolon
DECL|struct|asl_general_register_desc
r_typedef
r_struct
id|asl_general_register_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
DECL|member|length
id|u16
id|length
suffix:semicolon
DECL|member|address_space_id
id|u8
id|address_space_id
suffix:semicolon
DECL|member|bit_width
id|u8
id|bit_width
suffix:semicolon
DECL|member|bit_offset
id|u8
id|bit_offset
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|address
id|u64
id|address
suffix:semicolon
DECL|typedef|ASL_GENERAL_REGISTER_DESC
)brace
id|ASL_GENERAL_REGISTER_DESC
suffix:semicolon
multiline_comment|/* restore default alignment */
macro_line|#pragma pack()
multiline_comment|/* Union of all resource descriptors, sow we can allocate the worst case */
DECL|union|asl_resource_desc
r_typedef
r_union
id|asl_resource_desc
(brace
DECL|member|irq
id|ASL_IRQ_FORMAT_DESC
id|irq
suffix:semicolon
DECL|member|dma
id|ASL_DMA_FORMAT_DESC
id|dma
suffix:semicolon
DECL|member|std
id|ASL_START_DEPENDENT_DESC
id|std
suffix:semicolon
DECL|member|end
id|ASL_END_DEPENDENT_DESC
id|end
suffix:semicolon
DECL|member|iop
id|ASL_IO_PORT_DESC
id|iop
suffix:semicolon
DECL|member|fio
id|ASL_FIXED_IO_PORT_DESC
id|fio
suffix:semicolon
DECL|member|smv
id|ASL_SMALL_VENDOR_DESC
id|smv
suffix:semicolon
DECL|member|et
id|ASL_END_TAG_DESC
id|et
suffix:semicolon
DECL|member|M24
id|ASL_MEMORY_24_DESC
id|M24
suffix:semicolon
DECL|member|lgv
id|ASL_LARGE_VENDOR_DESC
id|lgv
suffix:semicolon
DECL|member|M32
id|ASL_MEMORY_32_DESC
id|M32
suffix:semicolon
DECL|member|F32
id|ASL_FIXED_MEMORY_32_DESC
id|F32
suffix:semicolon
DECL|member|qas
id|ASL_QWORD_ADDRESS_DESC
id|qas
suffix:semicolon
DECL|member|das
id|ASL_DWORD_ADDRESS_DESC
id|das
suffix:semicolon
DECL|member|was
id|ASL_WORD_ADDRESS_DESC
id|was
suffix:semicolon
DECL|member|exx
id|ASL_EXTENDED_XRUPT_DESC
id|exx
suffix:semicolon
DECL|member|grg
id|ASL_GENERAL_REGISTER_DESC
id|grg
suffix:semicolon
DECL|member|U32_item
id|u32
id|U32_item
suffix:semicolon
DECL|member|U16_item
id|u16
id|U16_item
suffix:semicolon
DECL|member|U8item
id|u8
id|U8item
suffix:semicolon
DECL|typedef|ASL_RESOURCE_DESC
)brace
id|ASL_RESOURCE_DESC
suffix:semicolon
DECL|macro|NEXT_RESOURCE_DESC
mdefine_line|#define NEXT_RESOURCE_DESC(a,b)     (ASL_RESOURCE_DESC *) (((char *) (a)) + sizeof(b))
DECL|macro|DEFAULT_RESOURCE_DESC_SIZE
mdefine_line|#define DEFAULT_RESOURCE_DESC_SIZE  (sizeof (ASL_RESOURCE_DESC) + sizeof (ASL_END_TAG_DESC))
multiline_comment|/*&n; * Resource utilities&n; */
id|ASL_RESOURCE_NODE
op_star
id|rs_allocate_resource_node
(paren
id|u32
id|size
)paren
suffix:semicolon
r_void
id|rs_create_bit_field
(paren
id|acpi_parse_object
op_star
id|op
comma
r_char
op_star
id|name
comma
id|u32
id|byte_offset
comma
id|u32
id|bit_offset
)paren
suffix:semicolon
r_void
id|rs_create_byte_field
(paren
id|acpi_parse_object
op_star
id|op
comma
r_char
op_star
id|name
comma
id|u32
id|byte_offset
)paren
suffix:semicolon
r_void
id|rs_set_flag_bits
(paren
id|u8
op_star
id|flags
comma
id|acpi_parse_object
op_star
id|op
comma
id|u8
id|position
comma
id|u8
r_default
)paren
suffix:semicolon
id|acpi_parse_object
op_star
id|rs_complete_node_and_get_next
(paren
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_one_resource_descriptor
(paren
id|acpi_parse_object
op_star
id|descriptor_type_op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|u32
id|rs_link_descriptor_chain
(paren
id|ASL_RESOURCE_NODE
op_star
op_star
id|previous_rnode
comma
id|ASL_RESOURCE_NODE
op_star
id|rnode
)paren
suffix:semicolon
multiline_comment|/*&n; * Small descriptors&n; */
id|ASL_RESOURCE_NODE
op_star
id|rs_do_dma_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_end_dependent_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_fixed_io_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_interrupt_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_io_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_irq_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_irq_no_flags_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_memory24_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_memory32_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_memory32_fixed_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_start_dependent_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_start_dependent_no_pri_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_vendor_small_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
multiline_comment|/*&n; * Large descriptors&n; */
id|u32
id|rs_get_string_data_length
(paren
id|acpi_parse_object
op_star
id|initializer_op
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_dword_io_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_dword_memory_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_qword_io_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_qword_memory_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_word_io_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_word_bus_number_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_vendor_large_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
id|ASL_RESOURCE_NODE
op_star
id|rs_do_general_register_descriptor
(paren
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|current_byte_offset
)paren
suffix:semicolon
macro_line|#endif
eof
