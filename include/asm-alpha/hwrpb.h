macro_line|#ifndef __ALPHA_HWRPB_H
DECL|macro|__ALPHA_HWRPB_H
mdefine_line|#define __ALPHA_HWRPB_H
DECL|macro|INIT_HWRPB
mdefine_line|#define INIT_HWRPB ((struct hwrpb_struct *) 0x10000000)
multiline_comment|/*&n; * DEC processor types for Alpha systems.  Found in HWRPB.&n; * These values are architected.&n; */
DECL|macro|EV3_CPU
mdefine_line|#define EV3_CPU                 1       /* EV3                  */
DECL|macro|EV4_CPU
mdefine_line|#define EV4_CPU                 2       /* EV4 (21064)          */
DECL|macro|LCA4_CPU
mdefine_line|#define LCA4_CPU                4       /* LCA4 (21066/21068)   */
DECL|macro|EV5_CPU
mdefine_line|#define EV5_CPU                 5       /* EV5 (21164)          */
DECL|macro|EV45_CPU
mdefine_line|#define EV45_CPU                6       /* EV4.5 (21064/xxx)    */
DECL|macro|EV56_CPU
mdefine_line|#define EV56_CPU&t;&t;7&t;/* EV5.6 (21164)&t;*/
DECL|macro|EV6_CPU
mdefine_line|#define EV6_CPU&t;&t;&t;8&t;/* EV6 (21264)&t;&t;*/
DECL|macro|PCA56_CPU
mdefine_line|#define PCA56_CPU&t;&t;9&t;/* PCA56 (21164PC)&t;*/
DECL|macro|PCA57_CPU
mdefine_line|#define PCA57_CPU&t;&t;10&t;/* PCA57 (notyet)&t;*/
DECL|macro|EV67_CPU
mdefine_line|#define EV67_CPU&t;&t;11&t;/* EV67 (21264A)&t;*/
multiline_comment|/*&n; * DEC system types for Alpha systems.  Found in HWRPB.&n; * These values are architected.&n; */
DECL|macro|ST_ADU
mdefine_line|#define ST_ADU&t;&t;&t;  1&t;/* Alpha ADU systype&t;*/
DECL|macro|ST_DEC_4000
mdefine_line|#define ST_DEC_4000&t;&t;  2&t;/* Cobra systype&t;*/
DECL|macro|ST_DEC_7000
mdefine_line|#define ST_DEC_7000&t;&t;  3&t;/* Ruby systype&t;&t;*/
DECL|macro|ST_DEC_3000_500
mdefine_line|#define ST_DEC_3000_500&t;&t;  4&t;/* Flamingo systype&t;*/
DECL|macro|ST_DEC_2000_300
mdefine_line|#define ST_DEC_2000_300&t;&t;  6&t;/* Jensen systype&t;*/
DECL|macro|ST_DEC_3000_300
mdefine_line|#define ST_DEC_3000_300&t;&t;  7&t;/* Pelican systype&t;*/
DECL|macro|ST_DEC_2100_A500
mdefine_line|#define ST_DEC_2100_A500&t;  9&t;/* Sable systype&t;*/
DECL|macro|ST_DEC_AXPVME_64
mdefine_line|#define ST_DEC_AXPVME_64&t; 10&t;/* AXPvme system type&t;*/
DECL|macro|ST_DEC_AXPPCI_33
mdefine_line|#define ST_DEC_AXPPCI_33&t; 11&t;/* NoName system type&t;*/
DECL|macro|ST_DEC_TLASER
mdefine_line|#define ST_DEC_TLASER&t;&t; 12&t;/* Turbolaser systype&t;*/
DECL|macro|ST_DEC_2100_A50
mdefine_line|#define ST_DEC_2100_A50&t;&t; 13&t;/* Avanti systype&t;*/
DECL|macro|ST_DEC_MUSTANG
mdefine_line|#define ST_DEC_MUSTANG&t;&t; 14&t;/* Mustang systype&t;*/
DECL|macro|ST_DEC_ALCOR
mdefine_line|#define ST_DEC_ALCOR&t;&t; 15&t;/* Alcor (EV5) systype&t;*/
DECL|macro|ST_DEC_1000
mdefine_line|#define ST_DEC_1000&t;&t; 17&t;/* Mikasa systype&t;*/
DECL|macro|ST_DEC_EB64
mdefine_line|#define ST_DEC_EB64&t;&t; 18&t;/* EB64 systype&t;&t;*/
DECL|macro|ST_DEC_EB66
mdefine_line|#define ST_DEC_EB66&t;&t; 19&t;/* EB66 systype&t;&t;*/
DECL|macro|ST_DEC_EB64P
mdefine_line|#define ST_DEC_EB64P&t;&t; 20&t;/* EB64+ systype&t;*/
DECL|macro|ST_DEC_BURNS
mdefine_line|#define ST_DEC_BURNS&t;&t; 21&t;/* laptop systype&t;*/
DECL|macro|ST_DEC_RAWHIDE
mdefine_line|#define ST_DEC_RAWHIDE&t;&t; 22&t;/* Rawhide systype&t;*/
DECL|macro|ST_DEC_K2
mdefine_line|#define ST_DEC_K2&t;&t; 23&t;/* K2 systype&t;&t;*/
DECL|macro|ST_DEC_LYNX
mdefine_line|#define ST_DEC_LYNX&t;&t; 24&t;/* Lynx systype&t;&t;*/
DECL|macro|ST_DEC_XL
mdefine_line|#define ST_DEC_XL&t;&t; 25&t;/* Alpha XL systype&t;*/
DECL|macro|ST_DEC_EB164
mdefine_line|#define ST_DEC_EB164&t;&t; 26&t;/* EB164 systype&t;*/
DECL|macro|ST_DEC_NORITAKE
mdefine_line|#define ST_DEC_NORITAKE&t;&t; 27&t;/* Noritake systype&t;*/
DECL|macro|ST_DEC_CORTEX
mdefine_line|#define ST_DEC_CORTEX&t;&t; 28&t;/* Cortex systype&t;*/
DECL|macro|ST_DEC_MIATA
mdefine_line|#define ST_DEC_MIATA&t;&t; 30&t;/* Miata systype        */
DECL|macro|ST_DEC_XXM
mdefine_line|#define ST_DEC_XXM&t;&t; 31&t;/* XXM systype&t;&t;*/
DECL|macro|ST_DEC_TAKARA
mdefine_line|#define ST_DEC_TAKARA&t;&t; 32&t;/* Takara systype&t;*/
DECL|macro|ST_DEC_YUKON
mdefine_line|#define ST_DEC_YUKON&t;&t; 33&t;/* Yukon systype&t;*/
DECL|macro|ST_DEC_TSUNAMI
mdefine_line|#define ST_DEC_TSUNAMI&t;&t; 34&t;/* Tsunami systype&t;*/
DECL|macro|ST_DEC_WILDFIRE
mdefine_line|#define ST_DEC_WILDFIRE&t;&t; 35&t;/* Wildfire systype&t;*/
DECL|macro|ST_DEC_CUSCO
mdefine_line|#define ST_DEC_CUSCO&t;&t; 36&t;/* CUSCO systype&t;*/
DECL|macro|ST_DEC_EIGER
mdefine_line|#define ST_DEC_EIGER&t;&t; 37&t;/* Eiger systype&t;*/
DECL|macro|ST_DEC_TITAN
mdefine_line|#define ST_DEC_TITAN&t;&t; 38&t;/* Titan systype&t;*/
multiline_comment|/* UNOFFICIAL!!! */
DECL|macro|ST_UNOFFICIAL_BIAS
mdefine_line|#define ST_UNOFFICIAL_BIAS&t;100
DECL|macro|ST_DTI_RUFFIAN
mdefine_line|#define ST_DTI_RUFFIAN&t;&t;101&t;/* RUFFIAN systype&t;*/
multiline_comment|/* Alpha Processor, Inc. systems */
DECL|macro|ST_API_BIAS
mdefine_line|#define ST_API_BIAS&t;&t;200
DECL|macro|ST_API_NAUTILUS
mdefine_line|#define ST_API_NAUTILUS&t;&t;201&t;/* UP1000 systype&t;*/
DECL|struct|pcb_struct
r_struct
id|pcb_struct
(brace
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
DECL|member|usp
r_int
r_int
id|usp
suffix:semicolon
DECL|member|ptbr
r_int
r_int
id|ptbr
suffix:semicolon
DECL|member|pcc
r_int
r_int
id|pcc
suffix:semicolon
DECL|member|asn
r_int
r_int
id|asn
suffix:semicolon
DECL|member|unique
r_int
r_int
id|unique
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|res1
DECL|member|res2
r_int
r_int
id|res1
comma
id|res2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|percpu_struct
r_struct
id|percpu_struct
(brace
DECL|member|hwpcb
r_int
r_int
id|hwpcb
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|pal_mem_size
r_int
r_int
id|pal_mem_size
suffix:semicolon
DECL|member|pal_scratch_size
r_int
r_int
id|pal_scratch_size
suffix:semicolon
DECL|member|pal_mem_pa
r_int
r_int
id|pal_mem_pa
suffix:semicolon
DECL|member|pal_scratch_pa
r_int
r_int
id|pal_scratch_pa
suffix:semicolon
DECL|member|pal_revision
r_int
r_int
id|pal_revision
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
DECL|member|variation
r_int
r_int
id|variation
suffix:semicolon
DECL|member|revision
r_int
r_int
id|revision
suffix:semicolon
DECL|member|serial_no
r_int
r_int
id|serial_no
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|logout_area_pa
r_int
r_int
id|logout_area_pa
suffix:semicolon
DECL|member|logout_area_len
r_int
r_int
id|logout_area_len
suffix:semicolon
DECL|member|halt_PCBB
r_int
r_int
id|halt_PCBB
suffix:semicolon
DECL|member|halt_PC
r_int
r_int
id|halt_PC
suffix:semicolon
DECL|member|halt_PS
r_int
r_int
id|halt_PS
suffix:semicolon
DECL|member|halt_arg
r_int
r_int
id|halt_arg
suffix:semicolon
DECL|member|halt_ra
r_int
r_int
id|halt_ra
suffix:semicolon
DECL|member|halt_pv
r_int
r_int
id|halt_pv
suffix:semicolon
DECL|member|halt_reason
r_int
r_int
id|halt_reason
suffix:semicolon
DECL|member|res
r_int
r_int
id|res
suffix:semicolon
DECL|member|ipc_buffer
r_int
r_int
id|ipc_buffer
(braket
l_int|21
)braket
suffix:semicolon
DECL|member|palcode_avail
r_int
r_int
id|palcode_avail
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|compatibility
r_int
r_int
id|compatibility
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|procdesc_struct
r_struct
id|procdesc_struct
(brace
DECL|member|weird_vms_stuff
r_int
r_int
id|weird_vms_stuff
suffix:semicolon
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vf_map_struct
r_struct
id|vf_map_struct
(brace
DECL|member|va
r_int
r_int
id|va
suffix:semicolon
DECL|member|pa
r_int
r_int
id|pa
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|crb_struct
r_struct
id|crb_struct
(brace
DECL|member|dispatch_va
r_struct
id|procdesc_struct
op_star
id|dispatch_va
suffix:semicolon
DECL|member|dispatch_pa
r_struct
id|procdesc_struct
op_star
id|dispatch_pa
suffix:semicolon
DECL|member|fixup_va
r_struct
id|procdesc_struct
op_star
id|fixup_va
suffix:semicolon
DECL|member|fixup_pa
r_struct
id|procdesc_struct
op_star
id|fixup_pa
suffix:semicolon
multiline_comment|/* virtual-&gt;physical map */
DECL|member|map_entries
r_int
r_int
id|map_entries
suffix:semicolon
DECL|member|map_pages
r_int
r_int
id|map_pages
suffix:semicolon
DECL|member|map
r_struct
id|vf_map_struct
id|map
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|memclust_struct
r_struct
id|memclust_struct
(brace
DECL|member|start_pfn
r_int
r_int
id|start_pfn
suffix:semicolon
DECL|member|numpages
r_int
r_int
id|numpages
suffix:semicolon
DECL|member|numtested
r_int
r_int
id|numtested
suffix:semicolon
DECL|member|bitmap_va
r_int
r_int
id|bitmap_va
suffix:semicolon
DECL|member|bitmap_pa
r_int
r_int
id|bitmap_pa
suffix:semicolon
DECL|member|bitmap_chksum
r_int
r_int
id|bitmap_chksum
suffix:semicolon
DECL|member|usage
r_int
r_int
id|usage
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|memdesc_struct
r_struct
id|memdesc_struct
(brace
DECL|member|chksum
r_int
r_int
id|chksum
suffix:semicolon
DECL|member|optional_pa
r_int
r_int
id|optional_pa
suffix:semicolon
DECL|member|numclusters
r_int
r_int
id|numclusters
suffix:semicolon
DECL|member|cluster
r_struct
id|memclust_struct
id|cluster
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|dsr_struct
r_struct
id|dsr_struct
(brace
DECL|member|smm
r_int
id|smm
suffix:semicolon
multiline_comment|/* SMM nubber used by LMF       */
DECL|member|lurt_off
r_int
r_int
id|lurt_off
suffix:semicolon
multiline_comment|/* offset to LURT table         */
DECL|member|sysname_off
r_int
r_int
id|sysname_off
suffix:semicolon
multiline_comment|/* offset to sysname char count */
)brace
suffix:semicolon
DECL|struct|hwrpb_struct
r_struct
id|hwrpb_struct
(brace
DECL|member|phys_addr
r_int
r_int
id|phys_addr
suffix:semicolon
multiline_comment|/* check: physical address of the hwrpb */
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* check: &quot;HWRPB&bslash;0&bslash;0&bslash;0&quot; */
DECL|member|revision
r_int
r_int
id|revision
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of hwrpb */
DECL|member|cpuid
r_int
r_int
id|cpuid
suffix:semicolon
DECL|member|pagesize
r_int
r_int
id|pagesize
suffix:semicolon
multiline_comment|/* 8192, I hope */
DECL|member|pa_bits
r_int
r_int
id|pa_bits
suffix:semicolon
multiline_comment|/* number of physical address bits */
DECL|member|max_asn
r_int
r_int
id|max_asn
suffix:semicolon
DECL|member|ssn
r_int
r_char
id|ssn
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* system serial number: big bother is watching */
DECL|member|sys_type
r_int
r_int
id|sys_type
suffix:semicolon
DECL|member|sys_variation
r_int
r_int
id|sys_variation
suffix:semicolon
DECL|member|sys_revision
r_int
r_int
id|sys_revision
suffix:semicolon
DECL|member|intr_freq
r_int
r_int
id|intr_freq
suffix:semicolon
multiline_comment|/* interval clock frequency * 4096 */
DECL|member|cycle_freq
r_int
r_int
id|cycle_freq
suffix:semicolon
multiline_comment|/* cycle counter frequency */
DECL|member|vptb
r_int
r_int
id|vptb
suffix:semicolon
multiline_comment|/* Virtual Page Table Base address */
DECL|member|res1
r_int
r_int
id|res1
suffix:semicolon
DECL|member|tbhb_offset
r_int
r_int
id|tbhb_offset
suffix:semicolon
multiline_comment|/* Translation Buffer Hint Block */
DECL|member|nr_processors
r_int
r_int
id|nr_processors
suffix:semicolon
DECL|member|processor_size
r_int
r_int
id|processor_size
suffix:semicolon
DECL|member|processor_offset
r_int
r_int
id|processor_offset
suffix:semicolon
DECL|member|ctb_nr
r_int
r_int
id|ctb_nr
suffix:semicolon
DECL|member|ctb_size
r_int
r_int
id|ctb_size
suffix:semicolon
multiline_comment|/* console terminal block size */
DECL|member|ctbt_offset
r_int
r_int
id|ctbt_offset
suffix:semicolon
multiline_comment|/* console terminal block table offset */
DECL|member|crb_offset
r_int
r_int
id|crb_offset
suffix:semicolon
multiline_comment|/* console callback routine block */
DECL|member|mddt_offset
r_int
r_int
id|mddt_offset
suffix:semicolon
multiline_comment|/* memory data descriptor table */
DECL|member|cdb_offset
r_int
r_int
id|cdb_offset
suffix:semicolon
multiline_comment|/* configuration data block (or NULL) */
DECL|member|frut_offset
r_int
r_int
id|frut_offset
suffix:semicolon
multiline_comment|/* FRU table (or NULL) */
DECL|member|save_terminal
r_void
(paren
op_star
id|save_terminal
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|save_terminal_data
r_int
r_int
id|save_terminal_data
suffix:semicolon
DECL|member|restore_terminal
r_void
(paren
op_star
id|restore_terminal
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|restore_terminal_data
r_int
r_int
id|restore_terminal_data
suffix:semicolon
DECL|member|CPU_restart
r_void
(paren
op_star
id|CPU_restart
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|CPU_restart_data
r_int
r_int
id|CPU_restart_data
suffix:semicolon
DECL|member|res2
r_int
r_int
id|res2
suffix:semicolon
DECL|member|res3
r_int
r_int
id|res3
suffix:semicolon
DECL|member|chksum
r_int
r_int
id|chksum
suffix:semicolon
DECL|member|rxrdy
r_int
r_int
id|rxrdy
suffix:semicolon
DECL|member|txrdy
r_int
r_int
id|txrdy
suffix:semicolon
DECL|member|dsr_offset
r_int
r_int
id|dsr_offset
suffix:semicolon
multiline_comment|/* &quot;Dynamic System Recognition Data Block Table&quot; */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
r_struct
id|hwrpb_struct
op_star
id|hwrpb
suffix:semicolon
r_static
r_inline
r_void
DECL|function|hwrpb_update_checksum
id|hwrpb_update_checksum
c_func
(paren
r_struct
id|hwrpb_struct
op_star
id|h
)paren
(brace
r_int
r_int
id|sum
op_assign
l_int|0
comma
op_star
id|l
suffix:semicolon
r_for
c_loop
(paren
id|l
op_assign
(paren
r_int
r_int
op_star
)paren
id|h
suffix:semicolon
id|l
OL
(paren
r_int
r_int
op_star
)paren
op_amp
id|h-&gt;chksum
suffix:semicolon
op_increment
id|l
)paren
id|sum
op_add_assign
op_star
id|l
suffix:semicolon
id|h-&gt;chksum
op_assign
id|sum
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_HWRPB_H */
eof
