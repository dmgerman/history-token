multiline_comment|/*&n; * Written by: Patricia Gaughen, IBM Corporation&n; *&n; * Copyright (C) 2002, IBM Corp.&n; *&n; * All rights reserved.          &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or&n; * NON INFRINGEMENT.  See the GNU General Public License for more&n; * details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Send feedback to &lt;gone@us.ibm.com&gt;&n; */
macro_line|#ifndef NUMAQ_H
DECL|macro|NUMAQ_H
mdefine_line|#define NUMAQ_H
macro_line|#ifdef CONFIG_X86_NUMAQ
DECL|macro|MAX_NUMNODES
mdefine_line|#define MAX_NUMNODES&t;&t;16
r_extern
r_void
id|get_memcfg_numaq
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|get_memcfg_numa
mdefine_line|#define get_memcfg_numa() get_memcfg_numaq()
multiline_comment|/*&n; * SYS_CFG_DATA_PRIV_ADDR, struct eachquadmem, and struct sys_cfg_data are the&n; */
DECL|macro|SYS_CFG_DATA_PRIV_ADDR
mdefine_line|#define SYS_CFG_DATA_PRIV_ADDR&t;&t;0x0009d000 /* place for scd in private quad space */
multiline_comment|/*&n; * Communication area for each processor on lynxer-processor tests.&n; *&n; * NOTE: If you change the size of this eachproc structure you need&n; *       to change the definition for EACH_QUAD_SIZE.&n; */
DECL|struct|eachquadmem
r_struct
id|eachquadmem
(brace
DECL|member|priv_mem_start
r_int
r_int
id|priv_mem_start
suffix:semicolon
multiline_comment|/* Starting address of this */
multiline_comment|/* quad&squot;s private memory. */
multiline_comment|/* This is always 0. */
multiline_comment|/* In MB. */
DECL|member|priv_mem_size
r_int
r_int
id|priv_mem_size
suffix:semicolon
multiline_comment|/* Size of this quad&squot;s */
multiline_comment|/* private memory. */
multiline_comment|/* In MB. */
DECL|member|low_shrd_mem_strp_start
r_int
r_int
id|low_shrd_mem_strp_start
suffix:semicolon
multiline_comment|/* Starting address of this */
multiline_comment|/* quad&squot;s low shared block */
multiline_comment|/* (untranslated). */
multiline_comment|/* In MB. */
DECL|member|low_shrd_mem_start
r_int
r_int
id|low_shrd_mem_start
suffix:semicolon
multiline_comment|/* Starting address of this */
multiline_comment|/* quad&squot;s low shared memory */
multiline_comment|/* (untranslated). */
multiline_comment|/* In MB. */
DECL|member|low_shrd_mem_size
r_int
r_int
id|low_shrd_mem_size
suffix:semicolon
multiline_comment|/* Size of this quad&squot;s low */
multiline_comment|/* shared memory. */
multiline_comment|/* In MB. */
DECL|member|lmmio_copb_start
r_int
r_int
id|lmmio_copb_start
suffix:semicolon
multiline_comment|/* Starting address of this */
multiline_comment|/* quad&squot;s local memory */
multiline_comment|/* mapped I/O in the */
multiline_comment|/* compatibility OPB. */
multiline_comment|/* In MB. */
DECL|member|lmmio_copb_size
r_int
r_int
id|lmmio_copb_size
suffix:semicolon
multiline_comment|/* Size of this quad&squot;s local */
multiline_comment|/* memory mapped I/O in the */
multiline_comment|/* compatibility OPB. */
multiline_comment|/* In MB. */
DECL|member|lmmio_nopb_start
r_int
r_int
id|lmmio_nopb_start
suffix:semicolon
multiline_comment|/* Starting address of this */
multiline_comment|/* quad&squot;s local memory */
multiline_comment|/* mapped I/O in the */
multiline_comment|/* non-compatibility OPB. */
multiline_comment|/* In MB. */
DECL|member|lmmio_nopb_size
r_int
r_int
id|lmmio_nopb_size
suffix:semicolon
multiline_comment|/* Size of this quad&squot;s local */
multiline_comment|/* memory mapped I/O in the */
multiline_comment|/* non-compatibility OPB. */
multiline_comment|/* In MB. */
DECL|member|io_apic_0_start
r_int
r_int
id|io_apic_0_start
suffix:semicolon
multiline_comment|/* Starting address of I/O */
multiline_comment|/* APIC 0. */
DECL|member|io_apic_0_sz
r_int
r_int
id|io_apic_0_sz
suffix:semicolon
multiline_comment|/* Size I/O APIC 0. */
DECL|member|io_apic_1_start
r_int
r_int
id|io_apic_1_start
suffix:semicolon
multiline_comment|/* Starting address of I/O */
multiline_comment|/* APIC 1. */
DECL|member|io_apic_1_sz
r_int
r_int
id|io_apic_1_sz
suffix:semicolon
multiline_comment|/* Size I/O APIC 1. */
DECL|member|hi_shrd_mem_start
r_int
r_int
id|hi_shrd_mem_start
suffix:semicolon
multiline_comment|/* Starting address of this */
multiline_comment|/* quad&squot;s high shared memory.*/
multiline_comment|/* In MB. */
DECL|member|hi_shrd_mem_size
r_int
r_int
id|hi_shrd_mem_size
suffix:semicolon
multiline_comment|/* Size of this quad&squot;s high */
multiline_comment|/* shared memory. */
multiline_comment|/* In MB. */
DECL|member|mps_table_addr
r_int
r_int
id|mps_table_addr
suffix:semicolon
multiline_comment|/* Address of this quad&squot;s */
multiline_comment|/* MPS tables from BIOS, */
multiline_comment|/* in system space.*/
DECL|member|lcl_MDC_pio_addr
r_int
r_int
id|lcl_MDC_pio_addr
suffix:semicolon
multiline_comment|/* Port-I/O address for */
multiline_comment|/* local access of MDC. */
DECL|member|rmt_MDC_mmpio_addr
r_int
r_int
id|rmt_MDC_mmpio_addr
suffix:semicolon
multiline_comment|/* MM-Port-I/O address for */
multiline_comment|/* remote access of MDC. */
DECL|member|mm_port_io_start
r_int
r_int
id|mm_port_io_start
suffix:semicolon
multiline_comment|/* Starting address of this */
multiline_comment|/* quad&squot;s memory mapped Port */
multiline_comment|/* I/O space. */
DECL|member|mm_port_io_size
r_int
r_int
id|mm_port_io_size
suffix:semicolon
multiline_comment|/* Size of this quad&squot;s memory*/
multiline_comment|/* mapped Port I/O space. */
DECL|member|mm_rmt_io_apic_start
r_int
r_int
id|mm_rmt_io_apic_start
suffix:semicolon
multiline_comment|/* Starting address of this */
multiline_comment|/* quad&squot;s memory mapped */
multiline_comment|/* remote I/O APIC space. */
DECL|member|mm_rmt_io_apic_size
r_int
r_int
id|mm_rmt_io_apic_size
suffix:semicolon
multiline_comment|/* Size of this quad&squot;s memory*/
multiline_comment|/* mapped remote I/O APIC */
multiline_comment|/* space. */
DECL|member|mm_isa_start
r_int
r_int
id|mm_isa_start
suffix:semicolon
multiline_comment|/* Starting address of this */
multiline_comment|/* quad&squot;s memory mapped ISA */
multiline_comment|/* space (contains MDC */
multiline_comment|/* memory space). */
DECL|member|mm_isa_size
r_int
r_int
id|mm_isa_size
suffix:semicolon
multiline_comment|/* Size of this quad&squot;s memory*/
multiline_comment|/* mapped ISA space (contains*/
multiline_comment|/* MDC memory space). */
DECL|member|rmt_qmi_addr
r_int
r_int
id|rmt_qmi_addr
suffix:semicolon
multiline_comment|/* Remote addr to access QMI.*/
DECL|member|lcl_qmi_addr
r_int
r_int
id|lcl_qmi_addr
suffix:semicolon
multiline_comment|/* Local addr to access QMI. */
)brace
suffix:semicolon
multiline_comment|/*&n; * Note: This structure must be NOT be changed unless the multiproc and&n; * OS are changed to reflect the new structure.&n; */
DECL|struct|sys_cfg_data
r_struct
id|sys_cfg_data
(brace
DECL|member|quad_id
r_int
r_int
id|quad_id
suffix:semicolon
DECL|member|bsp_proc_id
r_int
r_int
id|bsp_proc_id
suffix:semicolon
multiline_comment|/* Boot Strap Processor in this quad. */
DECL|member|scd_version
r_int
r_int
id|scd_version
suffix:semicolon
multiline_comment|/* Version number of this table. */
DECL|member|first_quad_id
r_int
r_int
id|first_quad_id
suffix:semicolon
DECL|member|quads_present31_0
r_int
r_int
id|quads_present31_0
suffix:semicolon
multiline_comment|/* 1 bit for each quad */
DECL|member|quads_present63_32
r_int
r_int
id|quads_present63_32
suffix:semicolon
multiline_comment|/* 1 bit for each quad */
DECL|member|config_flags
r_int
r_int
id|config_flags
suffix:semicolon
DECL|member|boot_flags
r_int
r_int
id|boot_flags
suffix:semicolon
DECL|member|csr_start_addr
r_int
r_int
id|csr_start_addr
suffix:semicolon
multiline_comment|/* Absolute value (not in MB) */
DECL|member|csr_size
r_int
r_int
id|csr_size
suffix:semicolon
multiline_comment|/* Absolute value (not in MB) */
DECL|member|lcl_apic_start_addr
r_int
r_int
id|lcl_apic_start_addr
suffix:semicolon
multiline_comment|/* Absolute value (not in MB) */
DECL|member|lcl_apic_size
r_int
r_int
id|lcl_apic_size
suffix:semicolon
multiline_comment|/* Absolute value (not in MB) */
DECL|member|low_shrd_mem_base
r_int
r_int
id|low_shrd_mem_base
suffix:semicolon
multiline_comment|/* 0 or 512MB or 1GB */
DECL|member|low_shrd_mem_quad_offset
r_int
r_int
id|low_shrd_mem_quad_offset
suffix:semicolon
multiline_comment|/* 0,128M,256M,512M,1G */
multiline_comment|/* may not be totally populated */
DECL|member|split_mem_enbl
r_int
r_int
id|split_mem_enbl
suffix:semicolon
multiline_comment|/* 0 for no low shared memory */
DECL|member|mmio_sz
r_int
r_int
id|mmio_sz
suffix:semicolon
multiline_comment|/* Size of total system memory mapped I/O */
multiline_comment|/* (in MB). */
DECL|member|quad_spin_lock
r_int
r_int
id|quad_spin_lock
suffix:semicolon
multiline_comment|/* Spare location used for quad */
multiline_comment|/* bringup. */
DECL|member|nonzero55
r_int
r_int
id|nonzero55
suffix:semicolon
multiline_comment|/* For checksumming. */
DECL|member|nonzeroaa
r_int
r_int
id|nonzeroaa
suffix:semicolon
multiline_comment|/* For checksumming. */
DECL|member|scd_magic_number
r_int
r_int
id|scd_magic_number
suffix:semicolon
DECL|member|system_type
r_int
r_int
id|system_type
suffix:semicolon
DECL|member|checksum
r_int
r_int
id|checksum
suffix:semicolon
multiline_comment|/*&n;&t; *&t;memory configuration area for each quad&n;&t; */
DECL|member|eq
r_struct
id|eachquadmem
id|eq
(braket
id|MAX_NUMNODES
)braket
suffix:semicolon
multiline_comment|/* indexed by quad id */
)brace
suffix:semicolon
DECL|function|get_zholes_size
r_static
r_inline
r_int
r_int
op_star
id|get_zholes_size
c_func
(paren
r_int
id|nid
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_X86_NUMAQ */
macro_line|#endif /* NUMAQ_H */
eof
