multiline_comment|/******************************************************************************&n; *&n; * Module Name: amlresrc.h - AML resource descriptors&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
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
mdefine_line|#define ASL_RESNAME_INTERRUPTLEVEL              &quot;_LL_&quot;  /* active_lo(1), active_hi(0) */
DECL|macro|ASL_RESNAME_INTERRUPTSHARE
mdefine_line|#define ASL_RESNAME_INTERRUPTSHARE              &quot;_SHR&quot;  /* Shareable(1), no_share(0) */
DECL|macro|ASL_RESNAME_INTERRUPTTYPE
mdefine_line|#define ASL_RESNAME_INTERRUPTTYPE               &quot;_HE_&quot;  /* Edge(1), Level(0) */
DECL|macro|ASL_RESNAME_LENGTH
mdefine_line|#define ASL_RESNAME_LENGTH                      &quot;_LEN&quot;
DECL|macro|ASL_RESNAME_MEMATTRIBUTES
mdefine_line|#define ASL_RESNAME_MEMATTRIBUTES               &quot;_MTP&quot;  /* Memory(0), Reserved(1), ACPI(2), NVS(3) */
DECL|macro|ASL_RESNAME_MEMTYPE
mdefine_line|#define ASL_RESNAME_MEMTYPE                     &quot;_MEM&quot;  /* non_cache(0), Cacheable(1) Cache+combine(2), Cache+prefetch(3) */
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
mdefine_line|#define ASL_RESNAME_READWRITETYPE               &quot;_RW_&quot;  /* read_only(0), Writeable (1) */
DECL|macro|ASL_RESNAME_TRANSLATION
mdefine_line|#define ASL_RESNAME_TRANSLATION                 &quot;_TRA&quot;
DECL|macro|ASL_RESNAME_TRANSTYPE
mdefine_line|#define ASL_RESNAME_TRANSTYPE                   &quot;_TRS&quot;  /* Sparse(1), Dense(0) */
DECL|macro|ASL_RESNAME_TYPE
mdefine_line|#define ASL_RESNAME_TYPE                        &quot;_TTP&quot;  /* Translation(1), Static (0) */
DECL|macro|ASL_RESNAME_XFERTYPE
mdefine_line|#define ASL_RESNAME_XFERTYPE                    &quot;_SIz&quot;  /* 8(0), 8_and16(1), 16(2) */
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
)brace
suffix:semicolon
multiline_comment|/*&n; * Resource descriptors defined in the ACPI specification.&n; *&n; * Packing/alignment must be BYTE because these descriptors&n; * are used to overlay the AML byte stream.&n; */
macro_line|#pragma pack(1)
DECL|struct|asl_irq_format_desc
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
)brace
suffix:semicolon
DECL|struct|asl_irq_noflags_desc
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
)brace
suffix:semicolon
DECL|struct|asl_dma_format_desc
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
)brace
suffix:semicolon
DECL|struct|asl_start_dependent_desc
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
)brace
suffix:semicolon
DECL|struct|asl_start_dependent_noprio_desc
r_struct
id|asl_start_dependent_noprio_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|asl_end_dependent_desc
r_struct
id|asl_end_dependent_desc
(brace
DECL|member|descriptor_type
id|u8
id|descriptor_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|asl_io_port_desc
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
)brace
suffix:semicolon
DECL|struct|asl_fixed_io_port_desc
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
)brace
suffix:semicolon
DECL|struct|asl_small_vendor_desc
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
)brace
suffix:semicolon
DECL|struct|asl_end_tag_desc
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
)brace
suffix:semicolon
multiline_comment|/* LARGE descriptors */
DECL|struct|asl_memory_24_desc
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
)brace
suffix:semicolon
DECL|struct|asl_large_vendor_desc
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
)brace
suffix:semicolon
DECL|struct|asl_memory_32_desc
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
)brace
suffix:semicolon
DECL|struct|asl_fixed_memory_32_desc
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
)brace
suffix:semicolon
DECL|struct|asl_qword_address_desc
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
)brace
suffix:semicolon
DECL|struct|asl_dword_address_desc
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
)brace
suffix:semicolon
DECL|struct|asl_word_address_desc
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
)brace
suffix:semicolon
DECL|struct|asl_extended_xrupt_desc
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
multiline_comment|/* res_source_index, res_source optional fields follow */
)brace
suffix:semicolon
DECL|struct|asl_general_register_desc
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
)brace
suffix:semicolon
multiline_comment|/* restore default alignment */
macro_line|#pragma pack()
multiline_comment|/* Union of all resource descriptors, so we can allocate the worst case */
DECL|union|asl_resource_desc
r_union
id|asl_resource_desc
(brace
DECL|member|irq
r_struct
id|asl_irq_format_desc
id|irq
suffix:semicolon
DECL|member|dma
r_struct
id|asl_dma_format_desc
id|dma
suffix:semicolon
DECL|member|std
r_struct
id|asl_start_dependent_desc
id|std
suffix:semicolon
DECL|member|end
r_struct
id|asl_end_dependent_desc
id|end
suffix:semicolon
DECL|member|iop
r_struct
id|asl_io_port_desc
id|iop
suffix:semicolon
DECL|member|fio
r_struct
id|asl_fixed_io_port_desc
id|fio
suffix:semicolon
DECL|member|smv
r_struct
id|asl_small_vendor_desc
id|smv
suffix:semicolon
DECL|member|et
r_struct
id|asl_end_tag_desc
id|et
suffix:semicolon
DECL|member|M24
r_struct
id|asl_memory_24_desc
id|M24
suffix:semicolon
DECL|member|lgv
r_struct
id|asl_large_vendor_desc
id|lgv
suffix:semicolon
DECL|member|M32
r_struct
id|asl_memory_32_desc
id|M32
suffix:semicolon
DECL|member|F32
r_struct
id|asl_fixed_memory_32_desc
id|F32
suffix:semicolon
DECL|member|qas
r_struct
id|asl_qword_address_desc
id|qas
suffix:semicolon
DECL|member|das
r_struct
id|asl_dword_address_desc
id|das
suffix:semicolon
DECL|member|was
r_struct
id|asl_word_address_desc
id|was
suffix:semicolon
DECL|member|exx
r_struct
id|asl_extended_xrupt_desc
id|exx
suffix:semicolon
DECL|member|grg
r_struct
id|asl_general_register_desc
id|grg
suffix:semicolon
DECL|member|u32_item
id|u32
id|u32_item
suffix:semicolon
DECL|member|u16_item
id|u16
id|u16_item
suffix:semicolon
DECL|member|U8item
id|u8
id|U8item
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
