macro_line|#ifndef _PARISC_PDC_H
DECL|macro|_PARISC_PDC_H
mdefine_line|#define _PARISC_PDC_H
multiline_comment|/*&n;    PDC entry points...&n;*/
DECL|macro|PDC_POW_FAIL
mdefine_line|#define PDC_POW_FAIL&t;1&t;&t;/* perform a power-fail&t;&t;*/
DECL|macro|PDC_POW_FAIL_PREPARE
mdefine_line|#define PDC_POW_FAIL_PREPARE&t;0&t;/* prepare for powerfail&t;*/
DECL|macro|PDC_CHASSIS
mdefine_line|#define PDC_CHASSIS&t;2&t;&t;/* PDC-chassis functions&t;*/
DECL|macro|PDC_CHASSIS_DISP
mdefine_line|#define PDC_CHASSIS_DISP&t;0&t;/* update chassis display&t;*/
DECL|macro|PDC_CHASSIS_WARN
mdefine_line|#define PDC_CHASSIS_WARN&t;1&t;/* return chassis warnings&t;*/
DECL|macro|PDC_CHASSIS_DISPWARN
mdefine_line|#define PDC_CHASSIS_DISPWARN&t;2&t;/* update&amp;return chassis status */
DECL|macro|PDC_RETURN_CHASSIS_INFO
mdefine_line|#define PDC_RETURN_CHASSIS_INFO 128&t;/* HVERSION dependend: return chassis LED/LCD info  */
DECL|macro|PDC_PIM
mdefine_line|#define PDC_PIM         3               /* Get PIM data                 */
DECL|macro|PDC_PIM_HPMC
mdefine_line|#define PDC_PIM_HPMC            0       /* Transfer HPMC data           */
DECL|macro|PDC_PIM_RETURN_SIZE
mdefine_line|#define PDC_PIM_RETURN_SIZE     1       /* Get Max buffer needed for PIM*/
DECL|macro|PDC_PIM_LPMC
mdefine_line|#define PDC_PIM_LPMC            2       /* Transfer HPMC data           */
DECL|macro|PDC_PIM_SOFT_BOOT
mdefine_line|#define PDC_PIM_SOFT_BOOT       3       /* Transfer Soft Boot data      */
DECL|macro|PDC_PIM_TOC
mdefine_line|#define PDC_PIM_TOC             4       /* Transfer TOC data            */
DECL|macro|PDC_MODEL
mdefine_line|#define PDC_MODEL&t;4&t;&t;/* PDC model information call&t;*/
DECL|macro|PDC_MODEL_INFO
mdefine_line|#define PDC_MODEL_INFO&t;&t;0&t;/* returns information &t;&t;*/
DECL|macro|PDC_MODEL_BOOTID
mdefine_line|#define PDC_MODEL_BOOTID&t;1&t;/* set the BOOT_ID&t;&t;*/
DECL|macro|PDC_MODEL_VERSIONS
mdefine_line|#define PDC_MODEL_VERSIONS&t;2&t;/* returns cpu-internal versions*/
DECL|macro|PDC_MODEL_SYSMODEL
mdefine_line|#define PDC_MODEL_SYSMODEL&t;3&t;/* return system model info&t;*/
DECL|macro|PDC_MODEL_ENSPEC
mdefine_line|#define PDC_MODEL_ENSPEC&t;4&t;/* ??? */
DECL|macro|PDC_MODEL_DISPEC
mdefine_line|#define PDC_MODEL_DISPEC&t;5&t;/* ??? */
DECL|macro|PDC_MODEL_CPU_ID
mdefine_line|#define PDC_MODEL_CPU_ID&t;6&t;/* returns cpu-id (only newer machines!) */
DECL|macro|PDC_MODEL_CAPABILITIES
mdefine_line|#define PDC_MODEL_CAPABILITIES&t;7&t;/* returns OS32/OS64-flags&t;*/
DECL|macro|PDC_MODEL_GET_BOOT__OP
mdefine_line|#define PDC_MODEL_GET_BOOT__OP&t;8&t;/* returns boot test options&t;*/
DECL|macro|PDC_MODEL_SET_BOOT__OP
mdefine_line|#define PDC_MODEL_SET_BOOT__OP&t;9&t;/* set boot test options&t;*/
DECL|macro|PDC_CACHE
mdefine_line|#define PDC_CACHE&t;5&t;&t;/* return/set cache (&amp; TLB) info*/
DECL|macro|PDC_CACHE_INFO
mdefine_line|#define PDC_CACHE_INFO&t;&t;0&t;/* returns information &t;&t;*/
DECL|macro|PDC_CACHE_SET_COH
mdefine_line|#define PDC_CACHE_SET_COH&t;1&t;/* set coherence state&t;&t;*/
DECL|macro|PDC_CACHE_RET_SPID
mdefine_line|#define PDC_CACHE_RET_SPID&t;2&t;/* returns space-ID bits&t;*/
DECL|macro|PDC_HPA
mdefine_line|#define PDC_HPA&t; 6       &t;/* return HPA of processor */
DECL|macro|PDC_HPA_PROCESSOR
mdefine_line|#define PDC_HPA_PROCESSOR       0
DECL|macro|PDC_HPA_MODULES
mdefine_line|#define PDC_HPA_MODULES&t; 1
DECL|macro|PDC_IODC
mdefine_line|#define PDC_IODC&t;8       /* talk to IODC */
DECL|macro|PDC_IODC_READ
mdefine_line|#define PDC_IODC_READ&t;   0       /* read IODC entry point */
multiline_comment|/*      PDC_IODC_RI_*&t;&t;      INDEX parameter of PDC_IODC_READ   */
DECL|macro|PDC_IODC_RI_DATA_BYTES
mdefine_line|#define PDC_IODC_RI_DATA_BYTES&t;0&t;/* IODC Data Bytes&t;&t;    */
multiline_comment|/*&t;&t;&t;&t;1, 2&t;   obsolete - HVERSION dependent      */
DECL|macro|PDC_IODC_RI_INIT
mdefine_line|#define PDC_IODC_RI_INIT&t;3&t;/* Initialize module&t;&t;  */
DECL|macro|PDC_IODC_RI_IO
mdefine_line|#define PDC_IODC_RI_IO&t;&t;4&t;/* Module input/output&t;&t;*/
DECL|macro|PDC_IODC_RI_SPA
mdefine_line|#define PDC_IODC_RI_SPA&t;&t;5&t;/* Module input/output&t;&t;*/
DECL|macro|PDC_IODC_RI_CONFIG
mdefine_line|#define PDC_IODC_RI_CONFIG&t;6&t;/* Module input/output&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;7&t;  obsolete - HVERSION dependent      */
DECL|macro|PDC_IODC_RI_TEST
mdefine_line|#define PDC_IODC_RI_TEST&t;8&t;/* Module input/output&t;&t;*/
DECL|macro|PDC_IODC_RI_TLB
mdefine_line|#define PDC_IODC_RI_TLB&t;&t;9&t;/* Module input/output&t;&t;*/
DECL|macro|PDC_IODC_NINIT
mdefine_line|#define PDC_IODC_NINIT&t;  2       /* non-destructive init */
DECL|macro|PDC_IODC_DINIT
mdefine_line|#define PDC_IODC_DINIT&t;  3       /* destructive init */
DECL|macro|PDC_IODC_MEMERR
mdefine_line|#define PDC_IODC_MEMERR&t; 4       /* check for memory errors */
DECL|macro|PDC_IODC_INDEX_DATA
mdefine_line|#define PDC_IODC_INDEX_DATA     0       /* get first 16 bytes from mod IODC */
DECL|macro|PDC_IODC_BUS_ERROR
mdefine_line|#define PDC_IODC_BUS_ERROR      -4      /* bus error return value */
DECL|macro|PDC_IODC_INVALID_INDEX
mdefine_line|#define PDC_IODC_INVALID_INDEX  -5      /* invalid index return value */
DECL|macro|PDC_IODC_COUNT
mdefine_line|#define PDC_IODC_COUNT&t;  -6      /* count is too small */
DECL|macro|PDC_TOD
mdefine_line|#define&t;PDC_TOD&t;&t;9&t;&t;/* time-of-day clock (TOD) */
DECL|macro|PDC_TOD_READ
mdefine_line|#define&t;PDC_TOD_READ&t;&t;0&t;/* read TOD  */
DECL|macro|PDC_TOD_WRITE
mdefine_line|#define&t;PDC_TOD_WRITE&t;&t;1&t;/* write TOD */
DECL|macro|PDC_TOD_ITIMER
mdefine_line|#define&t;PDC_TOD_ITIMER&t;&t;2&t;/* calibrate Interval Timer (CR16) */
DECL|macro|PDC_ADD_VALID
mdefine_line|#define PDC_ADD_VALID&t;12    &t;&t;/* Memory validation PDC call */
DECL|macro|PDC_ADD_VALID_VERIFY
mdefine_line|#define PDC_ADD_VALID_VERIFY  0    &t;/* Make PDC_ADD_VALID verify region */
DECL|macro|PDC_INSTR
mdefine_line|#define PDC_INSTR&t;15&t;&t;/* get instr to invoke PDCE_CHECK() */
DECL|macro|PDC_BLOCK_TLB
mdefine_line|#define PDC_BLOCK_TLB&t;18&t;&t;/* manage hardware block-TLB&t;*/
DECL|macro|PDC_BTLB_INFO
mdefine_line|#define PDC_BTLB_INFO&t;&t;0&t;/* returns parameter &t;&t;*/
DECL|macro|PDC_BTLB_INSERT
mdefine_line|#define PDC_BTLB_INSERT&t;&t;1&t;/* insert BTLB entry&t;&t;*/
DECL|macro|PDC_BTLB_PURGE
mdefine_line|#define PDC_BTLB_PURGE&t;&t;2&t;/* purge BTLB entries &t;&t;*/
DECL|macro|PDC_BTLB_PURGE_ALL
mdefine_line|#define PDC_BTLB_PURGE_ALL&t;3&t;/* purge all BTLB entries &t;*/
DECL|macro|PDC_TLB
mdefine_line|#define PDC_TLB&t;&t;19&t;&t;/* manage hardware TLB miss handling */
DECL|macro|PDC_TLB_INFO
mdefine_line|#define PDC_TLB_INFO&t;&t;0&t;/* returns parameter &t;&t;*/
DECL|macro|PDC_TLB_SETUP
mdefine_line|#define PDC_TLB_SETUP&t;&t;1&t;/* set up miss handling &t;*/
DECL|macro|PDC_SYSTEM_MAP
mdefine_line|#define PDC_SYSTEM_MAP&t;22&t;&t;/* find system modules */
DECL|macro|PDC_FIND_MODULE
mdefine_line|#define PDC_FIND_MODULE &t;0
multiline_comment|/* HVERSION dependent */
DECL|macro|PDC_IO
mdefine_line|#define PDC_IO&t;&t;&t;135&t;/* log error info, reset IO system  */
DECL|macro|PDC_BROADCAST_RESET
mdefine_line|#define PDC_BROADCAST_RESET&t;136&t;/* reset all processors&t;     */
DECL|macro|PDC_DO_RESET
mdefine_line|#define PDC_DO_RESET            0UL&t;/* option: perform a broadcast reset */
DECL|macro|PDC_DO_FIRM_TEST_RESET
mdefine_line|#define PDC_DO_FIRM_TEST_RESET  1UL&t;/* Do broadcast reset with bitmap */
DECL|macro|PDC_BR_RECONFIGURATION
mdefine_line|#define PDC_BR_RECONFIGURATION  2UL&t;/* reset w/reconfiguration */
DECL|macro|PDC_FIRM_TEST_MAGIC
mdefine_line|#define PDC_FIRM_TEST_MAGIC &t;0xab9ec36fUL    /* for this reboot only */
DECL|macro|PDC_LAN_STATION_ID
mdefine_line|#define PDC_LAN_STATION_ID      138     /* Hversion dependent mechanism for */
DECL|macro|PDC_LAN_STATION_ID_READ
mdefine_line|#define PDC_LAN_STATION_ID_READ 0       /* getting the lan station address  */
DECL|macro|PDC_LAN_STATION_ID_SIZE
mdefine_line|#define&t;PDC_LAN_STATION_ID_SIZE&t;6
multiline_comment|/* Legacy PDC definitions for same stuff */
DECL|macro|PDC_PCI_INDEX
mdefine_line|#define PDC_PCI_INDEX&t;&t;   147UL
DECL|macro|PDC_PCI_GET_INT_TBL_SIZE
mdefine_line|#define PDC_PCI_GET_INT_TBL_SIZE&t;13UL
DECL|macro|PDC_PCI_GET_INT_TBL
mdefine_line|#define PDC_PCI_GET_INT_TBL&t;     14UL
multiline_comment|/* generic error codes returned by all PDC-functions */
DECL|macro|PDC_WARN
mdefine_line|#define PDC_WARN&t;    3  /* Call completed with a warning */
DECL|macro|PDC_REQ_ERR_1
mdefine_line|#define PDC_REQ_ERR_1       2  /* See above */
DECL|macro|PDC_REQ_ERR_0
mdefine_line|#define PDC_REQ_ERR_0       1  /* Call would generate a requestor error */
DECL|macro|PDC_OK
mdefine_line|#define PDC_OK&t;      0  /* Call completed successfully */
DECL|macro|PDC_BAD_PROC
mdefine_line|#define PDC_BAD_PROC&t;   -1  /* Called non-existant procedure */
DECL|macro|PDC_BAD_OPTION
mdefine_line|#define PDC_BAD_OPTION     -2  /* Called with non-existant option */
DECL|macro|PDC_ERROR
mdefine_line|#define PDC_ERROR&t;  -3  /* Call could not complete without an error */
DECL|macro|PDC_INVALID_ARG
mdefine_line|#define PDC_INVALID_ARG   -10  /* Called with an invalid argument */
DECL|macro|PDC_BUS_POW_WARN
mdefine_line|#define PDC_BUS_POW_WARN  -12  /* Call could not complete in allowed power budget */
multiline_comment|/* The following are from the HPUX .h files, and are just for&n;compatibility */
DECL|macro|PDC_RET_OK
mdefine_line|#define PDC_RET_OK       0L&t;/* Call completed successfully */
DECL|macro|PDC_RET_NE_PROC
mdefine_line|#define PDC_RET_NE_PROC -1L&t;/* Non-existent procedure */
DECL|macro|PDC_RET_NE_OPT
mdefine_line|#define PDC_RET_NE_OPT  -2L&t;/* non-existant option - arg1 */
DECL|macro|PDC_RET_NE_MOD
mdefine_line|#define PDC_RET_NE_MOD  -5L&t;/* Module not found */
DECL|macro|PDC_RET_NE_CELL_MOD
mdefine_line|#define PDC_RET_NE_CELL_MOD -7L&t;/* Cell module not found */
DECL|macro|PDC_RET_INV_ARG
mdefine_line|#define PDC_RET_INV_ARG&t;-10L&t;/* Invalid argument */
DECL|macro|PDC_RET_NOT_NARROW
mdefine_line|#define PDC_RET_NOT_NARROW -17L /* Narrow mode not supported */
multiline_comment|/* Error codes for PDC_ADD_VALID */
DECL|macro|PDC_ADD_VALID_WARN
mdefine_line|#define PDC_ADD_VALID_WARN&t;    3  /* Call completed with a warning */
DECL|macro|PDC_ADD_VALID_REQ_ERR_1
mdefine_line|#define PDC_ADD_VALID_REQ_ERR_1       2  /* See above */
DECL|macro|PDC_ADD_VALID_REQ_ERR_0
mdefine_line|#define PDC_ADD_VALID_REQ_ERR_0       1  /* Call would generate a requestor error */
DECL|macro|PDC_ADD_VALID_OK
mdefine_line|#define PDC_ADD_VALID_OK&t;      0  /* Call completed successfully */
DECL|macro|PDC_ADD_VALID_BAD_OPTION
mdefine_line|#define PDC_ADD_VALID_BAD_OPTION     -2  /* Called with non-existant option */
DECL|macro|PDC_ADD_VALID_ERROR
mdefine_line|#define PDC_ADD_VALID_ERROR&t;  -3  /* Call could not complete without an error */
DECL|macro|PDC_ADD_VALID_INVALID_ARG
mdefine_line|#define PDC_ADD_VALID_INVALID_ARG   -10  /* Called with an invalid argument */
DECL|macro|PDC_ADD_VALID_BUS_POW_WARN
mdefine_line|#define PDC_ADD_VALID_BUS_POW_WARN  -12  /* Call could not complete in allowed power budget */
multiline_comment|/* The PDC_MEM_MAP calls */
DECL|macro|PDC_MEM_MAP
mdefine_line|#define PDC_MEM_MAP&t;    128
DECL|macro|PDC_MEM_MAP_HPA
mdefine_line|#define PDC_MEM_MAP_HPA&t;&t;0
multiline_comment|/* constants for OS (NVM...) */
DECL|macro|OS_ID_NONE
mdefine_line|#define OS_ID_NONE&t;0
DECL|macro|OS_ID_HPUX
mdefine_line|#define OS_ID_HPUX&t;1
DECL|macro|OS_ID_MPEXL
mdefine_line|#define OS_ID_MPEXL&t;2
DECL|macro|OS_ID_OSF
mdefine_line|#define OS_ID_OSF&t;3
DECL|macro|OS_ID_LINUX
mdefine_line|#define OS_ID_LINUX&t;OS_ID_HPUX
multiline_comment|/* constants for PDC_CHASSIS */
DECL|macro|OSTAT_OFF
mdefine_line|#define OSTAT_OFF&t;&t;      0
DECL|macro|OSTAT_FLT
mdefine_line|#define OSTAT_FLT&t;&t;      1 
DECL|macro|OSTAT_TEST
mdefine_line|#define OSTAT_TEST&t;&t;     2
DECL|macro|OSTAT_INIT
mdefine_line|#define OSTAT_INIT&t;&t;     3
DECL|macro|OSTAT_SHUT
mdefine_line|#define OSTAT_SHUT&t;&t;     4
DECL|macro|OSTAT_WARN
mdefine_line|#define OSTAT_WARN&t;&t;     5
DECL|macro|OSTAT_RUN
mdefine_line|#define OSTAT_RUN&t;&t;      6
DECL|macro|OSTAT_ON
mdefine_line|#define OSTAT_ON&t;&t;       7
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|pdc_model
r_struct
id|pdc_model
(brace
multiline_comment|/* for PDC_MODEL */
DECL|member|hversion
r_int
r_int
id|hversion
suffix:semicolon
DECL|member|sversion
r_int
r_int
id|sversion
suffix:semicolon
DECL|member|hw_id
r_int
r_int
id|hw_id
suffix:semicolon
DECL|member|boot_id
r_int
r_int
id|boot_id
suffix:semicolon
DECL|member|sw_id
r_int
r_int
id|sw_id
suffix:semicolon
DECL|member|sw_cap
r_int
r_int
id|sw_cap
suffix:semicolon
DECL|member|arch_rev
r_int
r_int
id|arch_rev
suffix:semicolon
DECL|member|pot_key
r_int
r_int
id|pot_key
suffix:semicolon
DECL|member|curr_key
r_int
r_int
id|curr_key
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
(braket
l_int|32
op_minus
l_int|9
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
macro_line|#if 0
r_struct
id|pdc_chassis_warn
(brace
multiline_comment|/* for PDC_CHASSIS */
r_int
r_int
id|warn
suffix:semicolon
r_int
r_int
id|pad
(braket
l_int|32
op_minus
l_int|1
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
DECL|struct|pdc_model_sysmodel
r_struct
id|pdc_model_sysmodel
(brace
multiline_comment|/* for PDC_MODEL_SYSMODEL */
DECL|member|mod_len
r_int
r_int
id|mod_len
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
(braket
l_int|32
op_minus
l_int|1
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|struct|pdc_model_cpuid
r_struct
id|pdc_model_cpuid
(brace
multiline_comment|/* for PDC_MODEL_CPU_ID */
DECL|member|cpuid
r_int
r_int
id|cpuid
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
(braket
l_int|32
op_minus
l_int|1
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|struct|pdc_cache_cf
r_struct
id|pdc_cache_cf
(brace
multiline_comment|/* for PDC_CACHE  (I/D-caches) */
r_int
r_int
macro_line|#ifdef __LP64__
DECL|member|cc_padW
id|cc_padW
suffix:colon
l_int|32
comma
macro_line|#endif
DECL|member|cc_alias
id|cc_alias
suffix:colon
l_int|4
comma
multiline_comment|/* alias boundaries for virtual adresses   */
DECL|member|cc_block
id|cc_block
suffix:colon
l_int|4
comma
multiline_comment|/* to determine most efficient stride */
DECL|member|cc_line
id|cc_line
suffix:colon
l_int|3
comma
multiline_comment|/* maximum amount written back as a result of store (multiple of 16 bytes) */
DECL|member|cc_pad0
id|cc_pad0
suffix:colon
l_int|2
comma
multiline_comment|/* reserved */
DECL|member|cc_wt
id|cc_wt
suffix:colon
l_int|1
comma
multiline_comment|/* 0 = WT-Dcache, 1 = WB-Dcache */
DECL|member|cc_sh
id|cc_sh
suffix:colon
l_int|2
comma
multiline_comment|/* 0 = separate I/D-cache, else shared I/D-cache */
DECL|member|cc_cst
id|cc_cst
suffix:colon
l_int|3
comma
multiline_comment|/* 0 = incoherent D-cache, 1=coherent D-cache */
DECL|member|cc_pad1
id|cc_pad1
suffix:colon
l_int|5
comma
multiline_comment|/* reserved */
DECL|member|cc_assoc
id|cc_assoc
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* associativity of I/D-cache */
)brace
suffix:semicolon
DECL|struct|pdc_tlb_cf
r_struct
id|pdc_tlb_cf
(brace
multiline_comment|/* for PDC_CACHE (I/D-TLB&squot;s) */
DECL|member|tc_pad0
r_int
r_int
id|tc_pad0
suffix:colon
l_int|12
comma
multiline_comment|/* reserved */
macro_line|#ifdef __LP64__
DECL|member|tc_padW
id|tc_padW
suffix:colon
l_int|32
comma
macro_line|#endif
DECL|member|tc_sh
id|tc_sh
suffix:colon
l_int|2
comma
multiline_comment|/* 0 = separate I/D-TLB, else shared I/D-TLB */
DECL|member|tc_hv
id|tc_hv
suffix:colon
l_int|1
comma
multiline_comment|/* HV */
DECL|member|tc_page
id|tc_page
suffix:colon
l_int|1
comma
multiline_comment|/* 0 = 2K page-size-machine, 1 = 4k page size */
DECL|member|tc_cst
id|tc_cst
suffix:colon
l_int|3
comma
multiline_comment|/* 0 = incoherent operations, else coherent operations */
DECL|member|tc_aid
id|tc_aid
suffix:colon
l_int|5
comma
multiline_comment|/* ITLB: width of access ids of processor (encoded!) */
DECL|member|tc_pad1
id|tc_pad1
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* ITLB: width of space-registers (encoded) */
)brace
suffix:semicolon
DECL|struct|pdc_cache_info
r_struct
id|pdc_cache_info
(brace
multiline_comment|/* main-PDC_CACHE-structure (caches &amp; TLB&squot;s) */
multiline_comment|/* I-cache */
DECL|member|ic_size
r_int
r_int
id|ic_size
suffix:semicolon
multiline_comment|/* size in bytes */
DECL|member|ic_conf
r_struct
id|pdc_cache_cf
id|ic_conf
suffix:semicolon
multiline_comment|/* configuration */
DECL|member|ic_base
r_int
r_int
id|ic_base
suffix:semicolon
multiline_comment|/* base-addr */
DECL|member|ic_stride
r_int
r_int
id|ic_stride
suffix:semicolon
DECL|member|ic_count
r_int
r_int
id|ic_count
suffix:semicolon
DECL|member|ic_loop
r_int
r_int
id|ic_loop
suffix:semicolon
multiline_comment|/* D-cache */
DECL|member|dc_size
r_int
r_int
id|dc_size
suffix:semicolon
multiline_comment|/* size in bytes */
DECL|member|dc_conf
r_struct
id|pdc_cache_cf
id|dc_conf
suffix:semicolon
multiline_comment|/* configuration */
DECL|member|dc_base
r_int
r_int
id|dc_base
suffix:semicolon
multiline_comment|/* base-addr */
DECL|member|dc_stride
r_int
r_int
id|dc_stride
suffix:semicolon
DECL|member|dc_count
r_int
r_int
id|dc_count
suffix:semicolon
DECL|member|dc_loop
r_int
r_int
id|dc_loop
suffix:semicolon
multiline_comment|/* Instruction-TLB */
DECL|member|it_size
r_int
r_int
id|it_size
suffix:semicolon
multiline_comment|/* number of entries in I-TLB */
DECL|member|it_conf
r_struct
id|pdc_tlb_cf
id|it_conf
suffix:semicolon
multiline_comment|/* I-TLB-configuration */
DECL|member|it_sp_base
r_int
r_int
id|it_sp_base
suffix:semicolon
DECL|member|it_sp_stride
r_int
r_int
id|it_sp_stride
suffix:semicolon
DECL|member|it_sp_count
r_int
r_int
id|it_sp_count
suffix:semicolon
DECL|member|it_off_base
r_int
r_int
id|it_off_base
suffix:semicolon
DECL|member|it_off_stride
r_int
r_int
id|it_off_stride
suffix:semicolon
DECL|member|it_off_count
r_int
r_int
id|it_off_count
suffix:semicolon
DECL|member|it_loop
r_int
r_int
id|it_loop
suffix:semicolon
multiline_comment|/* data-TLB */
DECL|member|dt_size
r_int
r_int
id|dt_size
suffix:semicolon
multiline_comment|/* number of entries in D-TLB */
DECL|member|dt_conf
r_struct
id|pdc_tlb_cf
id|dt_conf
suffix:semicolon
multiline_comment|/* D-TLB-configuration */
DECL|member|dt_sp_base
r_int
r_int
id|dt_sp_base
suffix:semicolon
DECL|member|dt_sp_stride
r_int
r_int
id|dt_sp_stride
suffix:semicolon
DECL|member|dt_sp_count
r_int
r_int
id|dt_sp_count
suffix:semicolon
DECL|member|dt_off_base
r_int
r_int
id|dt_off_base
suffix:semicolon
DECL|member|dt_off_stride
r_int
r_int
id|dt_off_stride
suffix:semicolon
DECL|member|dt_off_count
r_int
r_int
id|dt_off_count
suffix:semicolon
DECL|member|dt_loop
r_int
r_int
id|dt_loop
suffix:semicolon
multiline_comment|/* padded to 32 entries... */
DECL|member|pad
r_int
r_int
id|pad
(braket
l_int|32
op_minus
l_int|30
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|struct|pdc_hpa
r_struct
id|pdc_hpa
(brace
multiline_comment|/* PDC_HPA */
DECL|member|hpa
r_int
r_int
id|hpa
suffix:semicolon
DECL|member|filler
r_int
r_int
id|filler
(braket
l_int|31
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* If you start using the next struct, you&squot;ll have to adjust it to&n; * work with 64-bit firmware I think -PB&n; */
r_struct
id|pdc_iodc
(brace
multiline_comment|/* PDC_IODC */
r_int
r_char
id|hversion_model
suffix:semicolon
r_int
r_char
id|hversion
suffix:semicolon
r_int
r_char
id|spa
suffix:semicolon
r_int
r_char
id|type
suffix:semicolon
r_int
r_int
id|sversion_rev
suffix:colon
l_int|4
suffix:semicolon
r_int
r_int
id|sversion_model
suffix:colon
l_int|19
suffix:semicolon
r_int
r_int
id|sversion_opt
suffix:colon
l_int|8
suffix:semicolon
r_int
r_char
id|rev
suffix:semicolon
r_int
r_char
id|dep
suffix:semicolon
r_int
r_char
id|features
suffix:semicolon
r_int
r_char
id|filler1
suffix:semicolon
r_int
r_int
id|checksum
suffix:colon
l_int|16
suffix:semicolon
r_int
r_int
id|length
suffix:colon
l_int|16
suffix:semicolon
r_int
r_int
id|filler
(braket
l_int|15
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __LP64__
multiline_comment|/* no BLTBs in pa2.0 processors */
DECL|struct|pdc_btlb_info_range
r_struct
id|pdc_btlb_info_range
(brace
DECL|member|res00
id|__u8
id|res00
suffix:semicolon
DECL|member|num_i
id|__u8
id|num_i
suffix:semicolon
DECL|member|num_d
id|__u8
id|num_d
suffix:semicolon
DECL|member|num_comb
id|__u8
id|num_comb
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pdc_btlb_info
r_struct
id|pdc_btlb_info
(brace
multiline_comment|/* PDC_BLOCK_TLB, return of PDC_BTLB_INFO */
DECL|member|min_size
r_int
r_int
id|min_size
suffix:semicolon
multiline_comment|/* minimum size of BTLB in pages */
DECL|member|max_size
r_int
r_int
id|max_size
suffix:semicolon
multiline_comment|/* maximum size of BTLB in pages */
DECL|member|fixed_range_info
r_struct
id|pdc_btlb_info_range
id|fixed_range_info
suffix:semicolon
DECL|member|variable_range_info
r_struct
id|pdc_btlb_info_range
id|variable_range_info
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
(braket
l_int|32
op_minus
l_int|4
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
DECL|struct|pdc_tlb
r_struct
id|pdc_tlb
(brace
multiline_comment|/* for PDC_TLB */
DECL|member|min_size
r_int
r_int
id|min_size
suffix:semicolon
DECL|member|max_size
r_int
r_int
id|max_size
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
(braket
l_int|32
op_minus
l_int|2
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|struct|pdc_system_map
r_struct
id|pdc_system_map
(brace
multiline_comment|/* PDC_SYTEM_MAP/FIND_MODULE */
DECL|member|mod_addr
r_void
op_star
id|mod_addr
suffix:semicolon
DECL|member|mod_pgs
r_int
r_int
id|mod_pgs
suffix:semicolon
DECL|member|add_addrs
r_int
r_int
id|add_addrs
suffix:semicolon
DECL|member|filler
r_int
r_int
id|filler
(braket
l_int|29
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * Device path specifications used by PDC.&n; */
DECL|struct|pdc_module_path
r_struct
id|pdc_module_path
(brace
DECL|member|flags
r_char
id|flags
suffix:semicolon
multiline_comment|/* see bit definitions below */
DECL|member|bc
r_char
id|bc
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Bus Converter routing info to a specific */
multiline_comment|/* I/O adaptor (&lt; 0 means none, &gt; 63 resvd) */
DECL|member|mod
r_char
id|mod
suffix:semicolon
multiline_comment|/* fixed field of specified module */
DECL|member|layers
r_int
r_int
id|layers
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* device-specific info (ctlr #, unit # ...) */
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
macro_line|#ifndef __LP64__
multiline_comment|/* Probably needs 64-bit porting -PB */
DECL|struct|pdc_memory_map
r_struct
id|pdc_memory_map
(brace
multiline_comment|/* PDC_MEMORY_MAP */
DECL|member|hpa
r_int
r_int
id|hpa
suffix:semicolon
multiline_comment|/* mod&squot;s register set address */
DECL|member|more_pgs
r_int
r_int
id|more_pgs
suffix:semicolon
multiline_comment|/* number of additional I/O pgs */
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|struct|pdc_lan_station_id
r_struct
id|pdc_lan_station_id
(brace
multiline_comment|/* PDC_LAN_STATION_ID */
DECL|member|addr
r_int
r_char
id|addr
(braket
id|PDC_LAN_STATION_ID_SIZE
)braket
suffix:semicolon
DECL|member|pad0
r_int
r_char
id|pad0
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pad1
r_int
id|pad1
(braket
l_int|30
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|struct|pdc_tod
r_struct
id|pdc_tod
(brace
DECL|member|tod_sec
r_int
r_int
id|tod_sec
suffix:semicolon
DECL|member|tod_usec
r_int
r_int
id|tod_usec
suffix:semicolon
DECL|member|pad
r_int
id|pad
(braket
l_int|30
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* architected results from PDC_PIM/transfer hpmc on a PA1.1 machine */
DECL|struct|pdc_hpmc_pim_11
r_struct
id|pdc_hpmc_pim_11
(brace
multiline_comment|/* PDC_PIM */
DECL|member|gr
id|__u32
id|gr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|cr
id|__u32
id|cr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sr
id|__u32
id|sr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|iasq_back
id|__u32
id|iasq_back
suffix:semicolon
DECL|member|iaoq_back
id|__u32
id|iaoq_back
suffix:semicolon
DECL|member|check_type
id|__u32
id|check_type
suffix:semicolon
DECL|member|cpu_state
id|__u32
id|cpu_state
suffix:semicolon
DECL|member|rsvd1
id|__u32
id|rsvd1
suffix:semicolon
DECL|member|cache_check
id|__u32
id|cache_check
suffix:semicolon
DECL|member|tlb_check
id|__u32
id|tlb_check
suffix:semicolon
DECL|member|bus_check
id|__u32
id|bus_check
suffix:semicolon
DECL|member|assists_check
id|__u32
id|assists_check
suffix:semicolon
DECL|member|rsvd2
id|__u32
id|rsvd2
suffix:semicolon
DECL|member|assist_state
id|__u32
id|assist_state
suffix:semicolon
DECL|member|responder_addr
id|__u32
id|responder_addr
suffix:semicolon
DECL|member|requestor_addr
id|__u32
id|requestor_addr
suffix:semicolon
DECL|member|path_info
id|__u32
id|path_info
suffix:semicolon
DECL|member|fr
id|__u64
id|fr
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * architected results from PDC_PIM/transfer hpmc on a PA2.0 machine&n; *&n; * Note that PDC_PIM doesn&squot;t care whether or not wide mode was enabled&n; * so the results are different on  PA1.1 vs. PA2.0 when in narrow mode.&n; *&n; * Note also that there are unarchitected results available, which&n; * are hversion dependent. Do a &quot;ser pim 0 hpmc&quot; after rebooting, since&n; * the firmware is probably the best way of printing hversion dependent&n; * data.&n; */
DECL|struct|pdc_hpmc_pim_20
r_struct
id|pdc_hpmc_pim_20
(brace
multiline_comment|/* PDC_PIM */
DECL|member|gr
id|__u64
id|gr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|cr
id|__u64
id|cr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sr
id|__u64
id|sr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|iasq_back
id|__u64
id|iasq_back
suffix:semicolon
DECL|member|iaoq_back
id|__u64
id|iaoq_back
suffix:semicolon
DECL|member|check_type
id|__u32
id|check_type
suffix:semicolon
DECL|member|cpu_state
id|__u32
id|cpu_state
suffix:semicolon
DECL|member|cache_check
id|__u32
id|cache_check
suffix:semicolon
DECL|member|tlb_check
id|__u32
id|tlb_check
suffix:semicolon
DECL|member|bus_check
id|__u32
id|bus_check
suffix:semicolon
DECL|member|assists_check
id|__u32
id|assists_check
suffix:semicolon
DECL|member|assist_state
id|__u32
id|assist_state
suffix:semicolon
DECL|member|path_info
id|__u32
id|path_info
suffix:semicolon
DECL|member|responder_addr
id|__u64
id|responder_addr
suffix:semicolon
DECL|member|requestor_addr
id|__u64
id|requestor_addr
suffix:semicolon
DECL|member|fr
id|__u64
id|fr
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* flags of the device_path (see below) */
DECL|macro|PF_AUTOBOOT
mdefine_line|#define&t;PF_AUTOBOOT&t;0x80
DECL|macro|PF_AUTOSEARCH
mdefine_line|#define&t;PF_AUTOSEARCH&t;0x40
DECL|macro|PF_TIMER
mdefine_line|#define&t;PF_TIMER&t;0x0F
macro_line|#ifndef __ASSEMBLY__
DECL|struct|device_path
r_struct
id|device_path
(brace
multiline_comment|/* page 1-69 */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* flags see above! */
DECL|member|bc
r_int
r_char
id|bc
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* bus converter routing info */
DECL|member|mod
r_int
r_char
id|mod
suffix:semicolon
DECL|member|layers
r_int
r_int
id|layers
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* device-specific layer-info */
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
DECL|struct|pz_device
r_struct
id|pz_device
(brace
DECL|member|dp
r_struct
id|device_path
id|dp
suffix:semicolon
multiline_comment|/* see above */
multiline_comment|/* struct&t;iomod *hpa; */
DECL|member|hpa
r_int
r_int
id|hpa
suffix:semicolon
multiline_comment|/* HPA base address */
multiline_comment|/* char&t;*spa; */
DECL|member|spa
r_int
r_int
id|spa
suffix:semicolon
multiline_comment|/* SPA base address */
multiline_comment|/* int&t;(*iodc_io)(struct iomod*, ...); */
DECL|member|iodc_io
r_int
r_int
id|iodc_io
suffix:semicolon
multiline_comment|/* device entry point */
DECL|member|pad
r_int
id|pad
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|cl_class
r_int
r_int
id|cl_class
suffix:semicolon
multiline_comment|/* see below */
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* cl_class&n; * page 3-33 of IO-Firmware ARS&n; * IODC ENTRY_INIT(Search first) RET[1]&n; */
DECL|macro|CL_NULL
mdefine_line|#define&t;CL_NULL&t;&t;0&t;/* invalid */
DECL|macro|CL_RANDOM
mdefine_line|#define&t;CL_RANDOM&t;1&t;/* random access (as disk) */
DECL|macro|CL_SEQU
mdefine_line|#define&t;CL_SEQU&t;&t;2&t;/* sequential access (as tape) */
DECL|macro|CL_DUPLEX
mdefine_line|#define&t;CL_DUPLEX&t;7&t;/* full-duplex point-to-point (RS-232, Net) */
DECL|macro|CL_KEYBD
mdefine_line|#define&t;CL_KEYBD&t;8&t;/* half-duplex console (HIL Keyboard) */
DECL|macro|CL_DISPL
mdefine_line|#define&t;CL_DISPL&t;9&t;/* half-duplex console (display) */
DECL|macro|CL_FC
mdefine_line|#define&t;CL_FC&t;&t;10&t;/* FiberChannel access media */
macro_line|#if 0
multiline_comment|/* FIXME: DEVCLASS_* duplicates CL_* (above).  Delete DEVCLASS_*? */
mdefine_line|#define DEVCLASS_RANDOM&t;&t;1
mdefine_line|#define DEVCLASS_SEQU&t;&t;2
mdefine_line|#define DEVCLASS_DUPLEX&t;&t;7
mdefine_line|#define DEVCLASS_KEYBD&t;&t;8
mdefine_line|#define DEVCLASS_DISP&t;&t;9
macro_line|#endif
multiline_comment|/* IODC ENTRY_INIT() */
DECL|macro|ENTRY_INIT_SRCH_FRST
mdefine_line|#define ENTRY_INIT_SRCH_FRST&t;2
DECL|macro|ENTRY_INIT_SRCH_NEXT
mdefine_line|#define ENTRY_INIT_SRCH_NEXT&t;3
DECL|macro|ENTRY_INIT_MOD_DEV
mdefine_line|#define ENTRY_INIT_MOD_DEV&t;4
DECL|macro|ENTRY_INIT_DEV
mdefine_line|#define ENTRY_INIT_DEV&t;&t;5
DECL|macro|ENTRY_INIT_MOD
mdefine_line|#define ENTRY_INIT_MOD&t;&t;6
DECL|macro|ENTRY_INIT_MSG
mdefine_line|#define ENTRY_INIT_MSG&t;&t;9
multiline_comment|/* IODC ENTRY_IO() */
DECL|macro|ENTRY_IO_BOOTIN
mdefine_line|#define ENTRY_IO_BOOTIN&t;&t;0
DECL|macro|ENTRY_IO_CIN
mdefine_line|#define ENTRY_IO_CIN&t;&t;2
DECL|macro|ENTRY_IO_COUT
mdefine_line|#define ENTRY_IO_COUT&t;&t;3
DECL|macro|ENTRY_IO_CLOSE
mdefine_line|#define ENTRY_IO_CLOSE&t;&t;4
DECL|macro|ENTRY_IO_GETMSG
mdefine_line|#define ENTRY_IO_GETMSG&t;&t;9
multiline_comment|/* IODC ENTRY_SPA() */
multiline_comment|/* IODC ENTRY_CONFIG() */
multiline_comment|/* IODC ENTRY_TEST() */
multiline_comment|/* IODC ENTRY_TLB() */
multiline_comment|/* DEFINITION OF THE ZERO-PAGE (PAG0) */
multiline_comment|/* based on work by Jason Eckhardt (jason@equator.com) */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|PAGE0
mdefine_line|#define&t;PAGE0&t;((struct zeropage *)0xc0000000)
DECL|struct|zeropage
r_struct
id|zeropage
(brace
multiline_comment|/* [0x000] initialize vectors (VEC) */
DECL|member|vec_special
r_int
r_int
id|vec_special
suffix:semicolon
multiline_comment|/* must be zero */
multiline_comment|/* int&t;(*vec_pow_fail)(void);*/
DECL|member|vec_pow_fail
r_int
r_int
id|vec_pow_fail
suffix:semicolon
multiline_comment|/* power failure handler */
multiline_comment|/* int&t;(*vec_toc)(void); */
DECL|member|vec_toc
r_int
r_int
id|vec_toc
suffix:semicolon
DECL|member|vec_toclen
r_int
r_int
id|vec_toclen
suffix:semicolon
multiline_comment|/* int&t;(*vec_rendz)(void); */
DECL|member|vec_rendz
r_int
r_int
id|vec_rendz
suffix:semicolon
DECL|member|vec_pow_fail_flen
r_int
id|vec_pow_fail_flen
suffix:semicolon
DECL|member|vec_pad
r_int
id|vec_pad
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* [0x040] reserved processor dependent */
DECL|member|pad0
r_int
id|pad0
(braket
l_int|112
)braket
suffix:semicolon
multiline_comment|/* [0x200] reserved */
DECL|member|pad1
r_int
id|pad1
(braket
l_int|84
)braket
suffix:semicolon
multiline_comment|/* [0x350] memory configuration (MC) */
DECL|member|memc_cont
r_int
id|memc_cont
suffix:semicolon
multiline_comment|/* contiguous mem size (bytes) */
DECL|member|memc_phsize
r_int
id|memc_phsize
suffix:semicolon
multiline_comment|/* physical memory size */
DECL|member|memc_adsize
r_int
id|memc_adsize
suffix:semicolon
multiline_comment|/* additional mem size, bytes of SPA space used by PDC */
DECL|member|mem_pdc_hi
r_int
r_int
id|mem_pdc_hi
suffix:semicolon
multiline_comment|/* used for 64-bit */
multiline_comment|/* [0x360] various parameters for the boot-CPU */
multiline_comment|/* unsigned int *mem_booterr[8]; */
DECL|member|mem_booterr
r_int
r_int
id|mem_booterr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* ptr to boot errors */
DECL|member|mem_free
r_int
r_int
id|mem_free
suffix:semicolon
multiline_comment|/* first location, where OS can be loaded */
multiline_comment|/* struct iomod *mem_hpa; */
DECL|member|mem_hpa
r_int
r_int
id|mem_hpa
suffix:semicolon
multiline_comment|/* HPA of the boot-CPU */
multiline_comment|/* int (*mem_pdc)(int, ...); */
DECL|member|mem_pdc
r_int
r_int
id|mem_pdc
suffix:semicolon
multiline_comment|/* PDC entry point */
DECL|member|mem_10msec
r_int
r_int
id|mem_10msec
suffix:semicolon
multiline_comment|/* number of clock ticks in 10msec */
multiline_comment|/* [0x390] initial memory module (IMM) */
multiline_comment|/* struct iomod *imm_hpa; */
DECL|member|imm_hpa
r_int
r_int
id|imm_hpa
suffix:semicolon
multiline_comment|/* HPA of the IMM */
DECL|member|imm_soft_boot
r_int
id|imm_soft_boot
suffix:semicolon
multiline_comment|/* 0 = was hard boot, 1 = was soft boot */
DECL|member|imm_spa_size
r_int
r_int
id|imm_spa_size
suffix:semicolon
multiline_comment|/* SPA size of the IMM in bytes */
DECL|member|imm_max_mem
r_int
r_int
id|imm_max_mem
suffix:semicolon
multiline_comment|/* bytes of mem in IMM */
multiline_comment|/* [0x3A0] boot console, display device and keyboard */
DECL|member|mem_cons
r_struct
id|pz_device
id|mem_cons
suffix:semicolon
multiline_comment|/* description of console device */
DECL|member|mem_boot
r_struct
id|pz_device
id|mem_boot
suffix:semicolon
multiline_comment|/* description of boot device */
DECL|member|mem_kbd
r_struct
id|pz_device
id|mem_kbd
suffix:semicolon
multiline_comment|/* description of keyboard device */
multiline_comment|/* [0x430] reserved */
DECL|member|pad430
r_int
id|pad430
(braket
l_int|116
)braket
suffix:semicolon
multiline_comment|/* [0x600] processor dependent */
DECL|member|pad600
id|__u32
id|pad600
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|proc_sti
id|__u32
id|proc_sti
suffix:semicolon
multiline_comment|/* pointer to STI ROM */
DECL|member|pad608
id|__u32
id|pad608
(braket
l_int|126
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* Page Zero constant offsets used by the HPMC handler */
DECL|macro|BOOT_CONSOLE_HPA_OFFSET
mdefine_line|#define BOOT_CONSOLE_HPA_OFFSET  0x3c0
DECL|macro|BOOT_CONSOLE_SPA_OFFSET
mdefine_line|#define BOOT_CONSOLE_SPA_OFFSET  0x3c4
DECL|macro|BOOT_CONSOLE_PATH_OFFSET
mdefine_line|#define BOOT_CONSOLE_PATH_OFFSET 0x3a8
macro_line|#ifndef __ASSEMBLY__
DECL|struct|pdc_pat_io_num
r_struct
id|pdc_pat_io_num
(brace
DECL|member|num
r_int
r_int
id|num
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|31
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|pdc_console_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pdc_getc
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* wait for char */
r_extern
r_void
id|pdc_putc
c_func
(paren
r_int
r_char
)paren
suffix:semicolon
multiline_comment|/* print char */
multiline_comment|/* wrapper-functions from pdc.c */
r_int
id|pdc_add_valid
c_func
(paren
r_void
op_star
id|address
)paren
suffix:semicolon
r_int
id|pdc_hpa_processor
c_func
(paren
r_void
op_star
id|address
)paren
suffix:semicolon
macro_line|#if 0
r_int
id|pdc_hpa_modules
c_func
(paren
r_void
op_star
id|address
)paren
suffix:semicolon
macro_line|#endif
r_int
id|pdc_iodc_read
c_func
(paren
r_void
op_star
id|address
comma
r_void
op_star
id|hpa
comma
r_int
r_int
id|index
comma
r_void
op_star
id|iodc_data
comma
r_int
r_int
id|iodc_data_size
)paren
suffix:semicolon
r_int
id|pdc_system_map_find_mods
c_func
(paren
r_void
op_star
id|pdc_mod_info
comma
r_void
op_star
id|mod_path
comma
r_int
id|index
)paren
suffix:semicolon
r_int
id|pdc_model_info
c_func
(paren
r_struct
id|pdc_model
op_star
id|model
)paren
suffix:semicolon
r_int
id|pdc_model_sysmodel
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|pdc_model_cpuid
c_func
(paren
r_struct
id|pdc_model_cpuid
op_star
id|cpu_id
)paren
suffix:semicolon
r_int
id|pdc_model_versions
c_func
(paren
r_struct
id|pdc_model_cpuid
op_star
id|cpu_id
comma
r_int
id|id
)paren
suffix:semicolon
r_int
id|pdc_cache_info
c_func
(paren
r_struct
id|pdc_cache_info
op_star
id|cache
)paren
suffix:semicolon
macro_line|#ifndef __LP64__
r_int
id|pdc_btlb_info
c_func
(paren
r_struct
id|pdc_btlb_info
op_star
id|btlb
)paren
suffix:semicolon
r_int
id|pdc_lan_station_id
c_func
(paren
r_char
op_star
id|lan_addr
comma
r_void
op_star
id|net_hpa
)paren
suffix:semicolon
macro_line|#endif
r_int
id|pdc_mem_map_hpa
c_func
(paren
r_void
op_star
id|r_addr
comma
r_void
op_star
id|mod_path
)paren
suffix:semicolon
r_extern
r_int
id|pdc_chassis_disp
c_func
(paren
r_int
r_int
id|disp
)paren
suffix:semicolon
r_extern
r_int
id|pdc_chassis_info
c_func
(paren
r_void
op_star
id|pdc_result
comma
r_void
op_star
id|chassis_info
comma
r_int
r_int
id|len
)paren
suffix:semicolon
macro_line|#ifdef __LP64__
r_int
id|pdc_pat_get_irt_size
c_func
(paren
r_void
op_star
id|r_addr
comma
r_int
r_int
id|cell_num
)paren
suffix:semicolon
r_int
id|pdc_pat_get_irt
c_func
(paren
r_void
op_star
id|r_addr
comma
r_int
r_int
id|cell_num
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* No PAT support for 32-bit kernels...sorry */
DECL|macro|pdc_pat_get_irt_size
mdefine_line|#define pdc_pat_get_irt_size(r_addr, cell_numn)&t;PDC_RET_NE_PROC
DECL|macro|pdc_pat_get_irt
mdefine_line|#define pdc_pat_get_irt(r_addr, cell_num)&t;PDC_RET_NE_PROC
macro_line|#endif
r_int
id|pdc_pci_irt_size
c_func
(paren
r_void
op_star
id|r_addr
comma
r_void
op_star
id|hpa
)paren
suffix:semicolon
r_int
id|pdc_pci_irt
c_func
(paren
r_void
op_star
id|r_addr
comma
r_void
op_star
id|hpa
comma
r_void
op_star
id|tbl
)paren
suffix:semicolon
r_int
id|pdc_tod_read
c_func
(paren
r_struct
id|pdc_tod
op_star
id|tod
)paren
suffix:semicolon
r_int
id|pdc_tod_set
c_func
(paren
r_int
r_int
id|sec
comma
r_int
r_int
id|usec
)paren
suffix:semicolon
multiline_comment|/* on all currently-supported platforms, IODC I/O calls are always&n; * 32-bit calls, and MEM_PDC calls are always the same width as the OS.&n; * This means Cxxx boxes can&squot;t run wide kernels right now. -PB&n; *&n; * Note that some PAT boxes may have 64-bit IODC I/O...&n; */
macro_line|#ifdef __LP64__
DECL|macro|mem_pdc_call
macro_line|#   define mem_pdc_call(args...) real64_call(0L, ##args)
macro_line|#else
DECL|macro|mem_pdc_call
macro_line|#   define mem_pdc_call(args...) real32_call(0L, ##args)
macro_line|#endif
multiline_comment|/* yes &squot;int&squot;, not &squot;long&squot; -- IODC I/O is always 32-bit stuff */
r_extern
r_int
id|real64_call
c_func
(paren
r_int
r_int
id|function
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_int
id|real32_call
c_func
(paren
r_int
r_int
id|function
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|pdc_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _PARISC_PDC_H */
eof
