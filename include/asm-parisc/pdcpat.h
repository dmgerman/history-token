macro_line|#ifndef __PARISC_PATPDC_H
DECL|macro|__PARISC_PATPDC_H
mdefine_line|#define __PARISC_PATPDC_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright 2000 (c) Hewlett Packard (Paul Bame &lt;bame()spam.parisc-linux.org&gt;)&n; * Copyright 2000,2004 (c) Grant Grundler &lt;grundler()nahspam.parisc-linux.org&gt;&n; */
DECL|macro|PDC_PAT_CELL
mdefine_line|#define PDC_PAT_CELL           &t;64L   /* Interface for gaining and &n;                                         * manipulatin g cell state within PD */
DECL|macro|PDC_PAT_CELL_GET_NUMBER
mdefine_line|#define PDC_PAT_CELL_GET_NUMBER    0L   /* Return Cell number */
DECL|macro|PDC_PAT_CELL_GET_INFO
mdefine_line|#define PDC_PAT_CELL_GET_INFO      1L   /* Returns info about Cell */
DECL|macro|PDC_PAT_CELL_MODULE
mdefine_line|#define PDC_PAT_CELL_MODULE        2L   /* Returns info about Module */
DECL|macro|PDC_PAT_CELL_SET_ATTENTION
mdefine_line|#define PDC_PAT_CELL_SET_ATTENTION 9L   /* Set Cell Attention indicator */
DECL|macro|PDC_PAT_CELL_NUMBER_TO_LOC
mdefine_line|#define PDC_PAT_CELL_NUMBER_TO_LOC 10L   /* Cell Number -&gt; Location */
DECL|macro|PDC_PAT_CELL_WALK_FABRIC
mdefine_line|#define PDC_PAT_CELL_WALK_FABRIC   11L   /* Walk the Fabric */
DECL|macro|PDC_PAT_CELL_GET_RDT_SIZE
mdefine_line|#define PDC_PAT_CELL_GET_RDT_SIZE  12L   /* Return Route Distance Table Sizes */
DECL|macro|PDC_PAT_CELL_GET_RDT
mdefine_line|#define PDC_PAT_CELL_GET_RDT       13L   /* Return Route Distance Tables */
DECL|macro|PDC_PAT_CELL_GET_LOCAL_PDH_SZ
mdefine_line|#define PDC_PAT_CELL_GET_LOCAL_PDH_SZ 14L /* Read Local PDH Buffer Size */
DECL|macro|PDC_PAT_CELL_SET_LOCAL_PDH
mdefine_line|#define PDC_PAT_CELL_SET_LOCAL_PDH    15L  /* Write Local PDH Buffer */
DECL|macro|PDC_PAT_CELL_GET_REMOTE_PDH_SZ
mdefine_line|#define PDC_PAT_CELL_GET_REMOTE_PDH_SZ 16L /* Return Remote PDH Buffer Size */
DECL|macro|PDC_PAT_CELL_GET_REMOTE_PDH
mdefine_line|#define PDC_PAT_CELL_GET_REMOTE_PDH 17L /* Read Remote PDH Buffer */
DECL|macro|PDC_PAT_CELL_GET_DBG_INFO
mdefine_line|#define PDC_PAT_CELL_GET_DBG_INFO   128L  /* Return DBG Buffer Info */
DECL|macro|PDC_PAT_CELL_CHANGE_ALIAS
mdefine_line|#define PDC_PAT_CELL_CHANGE_ALIAS   129L  /* Change Non-Equivalent Alias Chacking */
multiline_comment|/*&n;** Arg to PDC_PAT_CELL_MODULE memaddr[4]&n;**&n;** Addresses on the Merced Bus != all Runway Bus addresses.&n;** This is intended for programming SBA/LBA chips range registers.&n;*/
DECL|macro|IO_VIEW
mdefine_line|#define IO_VIEW      0UL
DECL|macro|PA_VIEW
mdefine_line|#define PA_VIEW      1UL
multiline_comment|/* PDC_PAT_CELL_MODULE entity type values */
DECL|macro|PAT_ENTITY_CA
mdefine_line|#define&t;PAT_ENTITY_CA&t;0&t;/* central agent */
DECL|macro|PAT_ENTITY_PROC
mdefine_line|#define&t;PAT_ENTITY_PROC&t;1&t;/* processor */
DECL|macro|PAT_ENTITY_MEM
mdefine_line|#define&t;PAT_ENTITY_MEM&t;2&t;/* memory controller */
DECL|macro|PAT_ENTITY_SBA
mdefine_line|#define&t;PAT_ENTITY_SBA&t;3&t;/* system bus adapter */
DECL|macro|PAT_ENTITY_LBA
mdefine_line|#define&t;PAT_ENTITY_LBA&t;4&t;/* local bus adapter */
DECL|macro|PAT_ENTITY_PBC
mdefine_line|#define&t;PAT_ENTITY_PBC&t;5&t;/* processor bus converter */
DECL|macro|PAT_ENTITY_XBC
mdefine_line|#define&t;PAT_ENTITY_XBC&t;6&t;/* crossbar fabric connect */
DECL|macro|PAT_ENTITY_RC
mdefine_line|#define&t;PAT_ENTITY_RC&t;7&t;/* fabric interconnect */
multiline_comment|/* PDC_PAT_CELL_MODULE address range type values */
DECL|macro|PAT_PBNUM
mdefine_line|#define PAT_PBNUM           0         /* PCI Bus Number */
DECL|macro|PAT_LMMIO
mdefine_line|#define PAT_LMMIO           1         /* &lt; 4G MMIO Space */
DECL|macro|PAT_GMMIO
mdefine_line|#define PAT_GMMIO           2         /* &gt; 4G MMIO Space */
DECL|macro|PAT_NPIOP
mdefine_line|#define PAT_NPIOP           3         /* Non Postable I/O Port Space */
DECL|macro|PAT_PIOP
mdefine_line|#define PAT_PIOP            4         /* Postable I/O Port Space */
DECL|macro|PAT_AHPA
mdefine_line|#define PAT_AHPA            5         /* Addional HPA Space */
DECL|macro|PAT_UFO
mdefine_line|#define PAT_UFO             6         /* HPA Space (UFO for Mariposa) */
DECL|macro|PAT_GNIP
mdefine_line|#define PAT_GNIP            7         /* GNI Reserved Space */
multiline_comment|/* PDC PAT CHASSIS LOG -- Platform logging &amp; forward progress functions */
DECL|macro|PDC_PAT_CHASSIS_LOG
mdefine_line|#define PDC_PAT_CHASSIS_LOG&t;&t;65L
DECL|macro|PDC_PAT_CHASSIS_WRITE_LOG
mdefine_line|#define PDC_PAT_CHASSIS_WRITE_LOG    &t;0L /* Write Log Entry */
DECL|macro|PDC_PAT_CHASSIS_READ_LOG
mdefine_line|#define PDC_PAT_CHASSIS_READ_LOG     &t;1L /* Read  Log Entry */
multiline_comment|/* PDC PAT CPU  -- CPU configuration within the protection domain */
DECL|macro|PDC_PAT_CPU
mdefine_line|#define PDC_PAT_CPU                &t;67L
DECL|macro|PDC_PAT_CPU_INFO
mdefine_line|#define PDC_PAT_CPU_INFO            &t;0L /* Return CPU config info */
DECL|macro|PDC_PAT_CPU_DELETE
mdefine_line|#define PDC_PAT_CPU_DELETE          &t;1L /* Delete CPU */
DECL|macro|PDC_PAT_CPU_ADD
mdefine_line|#define PDC_PAT_CPU_ADD             &t;2L /* Add    CPU */
DECL|macro|PDC_PAT_CPU_GET_NUMBER
mdefine_line|#define PDC_PAT_CPU_GET_NUMBER      &t;3L /* Return CPU Number */
DECL|macro|PDC_PAT_CPU_GET_HPA
mdefine_line|#define PDC_PAT_CPU_GET_HPA         &t;4L /* Return CPU HPA */
DECL|macro|PDC_PAT_CPU_STOP
mdefine_line|#define PDC_PAT_CPU_STOP            &t;5L /* Stop   CPU */
DECL|macro|PDC_PAT_CPU_RENDEZVOUS
mdefine_line|#define PDC_PAT_CPU_RENDEZVOUS      &t;6L /* Rendezvous CPU */
DECL|macro|PDC_PAT_CPU_GET_CLOCK_INFO
mdefine_line|#define PDC_PAT_CPU_GET_CLOCK_INFO  &t;7L /* Return CPU Clock info */
DECL|macro|PDC_PAT_CPU_GET_RENDEZVOUS_STATE
mdefine_line|#define PDC_PAT_CPU_GET_RENDEZVOUS_STATE 8L /* Return Rendezvous State */
DECL|macro|PDC_PAT_CPU_PLUNGE_FABRIC
mdefine_line|#define PDC_PAT_CPU_PLUNGE_FABRIC &t;128L /* Plunge Fabric */
DECL|macro|PDC_PAT_CPU_UPDATE_CACHE_CLEANSING
mdefine_line|#define PDC_PAT_CPU_UPDATE_CACHE_CLEANSING 129L /* Manipulate Cache &n;                                                 * Cleansing Mode */
multiline_comment|/*  PDC PAT EVENT -- Platform Events */
DECL|macro|PDC_PAT_EVENT
mdefine_line|#define PDC_PAT_EVENT              &t;68L
DECL|macro|PDC_PAT_EVENT_GET_CAPS
mdefine_line|#define PDC_PAT_EVENT_GET_CAPS     &t;0L /* Get Capabilities */
DECL|macro|PDC_PAT_EVENT_SET_MODE
mdefine_line|#define PDC_PAT_EVENT_SET_MODE     &t;1L /* Set Notification Mode */
DECL|macro|PDC_PAT_EVENT_SCAN
mdefine_line|#define PDC_PAT_EVENT_SCAN         &t;2L /* Scan Event */
DECL|macro|PDC_PAT_EVENT_HANDLE
mdefine_line|#define PDC_PAT_EVENT_HANDLE       &t;3L /* Handle Event */
DECL|macro|PDC_PAT_EVENT_GET_NB_CALL
mdefine_line|#define PDC_PAT_EVENT_GET_NB_CALL  &t;4L /* Get Non-Blocking call Args */
multiline_comment|/*  PDC PAT HPMC -- Cause processor to go into spin loop, and wait&n; *  &t;&t;&t;for wake up from Monarch Processor.&n; */
DECL|macro|PDC_PAT_HPMC
mdefine_line|#define PDC_PAT_HPMC               70L
DECL|macro|PDC_PAT_HPMC_RENDEZ_CPU
mdefine_line|#define PDC_PAT_HPMC_RENDEZ_CPU     0L /* go into spin loop */
DECL|macro|PDC_PAT_HPMC_SET_PARAMS
mdefine_line|#define PDC_PAT_HPMC_SET_PARAMS     1L /* Allows OS to specify intr which PDC &n;                                        * will use to interrupt OS during&n;                                        * machine check rendezvous */
multiline_comment|/* parameters for PDC_PAT_HPMC_SET_PARAMS: */
DECL|macro|HPMC_SET_PARAMS_INTR
mdefine_line|#define HPMC_SET_PARAMS_INTR &t;    1L /* Rendezvous Interrupt */
DECL|macro|HPMC_SET_PARAMS_WAKE
mdefine_line|#define HPMC_SET_PARAMS_WAKE &t;    2L /* Wake up processor */
multiline_comment|/*  PDC PAT IO  -- On-line services for I/O modules */
DECL|macro|PDC_PAT_IO
mdefine_line|#define PDC_PAT_IO                  71L
DECL|macro|PDC_PAT_IO_GET_SLOT_STATUS
mdefine_line|#define PDC_PAT_IO_GET_SLOT_STATUS   &t;5L /* Get Slot Status Info*/
DECL|macro|PDC_PAT_IO_GET_LOC_FROM_HARDWARE
mdefine_line|#define PDC_PAT_IO_GET_LOC_FROM_HARDWARE 6L /* Get Physical Location from */
multiline_comment|/* Hardware Path */
DECL|macro|PDC_PAT_IO_GET_HARDWARE_FROM_LOC
mdefine_line|#define PDC_PAT_IO_GET_HARDWARE_FROM_LOC 7L /* Get Hardware Path from &n;                                             * Physical Location */
DECL|macro|PDC_PAT_IO_GET_PCI_CONFIG_FROM_HW
mdefine_line|#define PDC_PAT_IO_GET_PCI_CONFIG_FROM_HW 11L /* Get PCI Configuration&n;                                               * Address from Hardware Path */
DECL|macro|PDC_PAT_IO_GET_HW_FROM_PCI_CONFIG
mdefine_line|#define PDC_PAT_IO_GET_HW_FROM_PCI_CONFIG 12L /* Get Hardware Path &n;                                               * from PCI Configuration Address */
DECL|macro|PDC_PAT_IO_READ_HOST_BRIDGE_INFO
mdefine_line|#define PDC_PAT_IO_READ_HOST_BRIDGE_INFO 13L  /* Read Host Bridge State Info */
DECL|macro|PDC_PAT_IO_CLEAR_HOST_BRIDGE_INFO
mdefine_line|#define PDC_PAT_IO_CLEAR_HOST_BRIDGE_INFO 14L /* Clear Host Bridge State Info*/
DECL|macro|PDC_PAT_IO_GET_PCI_ROUTING_TABLE_SIZE
mdefine_line|#define PDC_PAT_IO_GET_PCI_ROUTING_TABLE_SIZE 15L /* Get PCI INT Routing Table &n;                                                   * Size */
DECL|macro|PDC_PAT_IO_GET_PCI_ROUTING_TABLE
mdefine_line|#define PDC_PAT_IO_GET_PCI_ROUTING_TABLE  16L /* Get PCI INT Routing Table */
DECL|macro|PDC_PAT_IO_GET_HINT_TABLE_SIZE
mdefine_line|#define PDC_PAT_IO_GET_HINT_TABLE_SIZE &t;17L /* Get Hint Table Size */
DECL|macro|PDC_PAT_IO_GET_HINT_TABLE
mdefine_line|#define PDC_PAT_IO_GET_HINT_TABLE   &t;18L /* Get Hint Table */
DECL|macro|PDC_PAT_IO_PCI_CONFIG_READ
mdefine_line|#define PDC_PAT_IO_PCI_CONFIG_READ  &t;19L /* PCI Config Read */
DECL|macro|PDC_PAT_IO_PCI_CONFIG_WRITE
mdefine_line|#define PDC_PAT_IO_PCI_CONFIG_WRITE &t;20L /* PCI Config Write */
DECL|macro|PDC_PAT_IO_GET_NUM_IO_SLOTS
mdefine_line|#define PDC_PAT_IO_GET_NUM_IO_SLOTS &t;21L /* Get Number of I/O Bay Slots in &n;                                       &t;&t;  * Cabinet */
DECL|macro|PDC_PAT_IO_GET_LOC_IO_SLOTS
mdefine_line|#define PDC_PAT_IO_GET_LOC_IO_SLOTS &t;22L /* Get Physical Location of I/O */
multiline_comment|/* Bay Slots in Cabinet */
DECL|macro|PDC_PAT_IO_BAY_STATUS_INFO
mdefine_line|#define PDC_PAT_IO_BAY_STATUS_INFO  &t;28L /* Get I/O Bay Slot Status Info */
DECL|macro|PDC_PAT_IO_GET_PROC_VIEW
mdefine_line|#define PDC_PAT_IO_GET_PROC_VIEW        29L /* Get Processor view of IO address */
DECL|macro|PDC_PAT_IO_PROG_SBA_DIR_RANGE
mdefine_line|#define PDC_PAT_IO_PROG_SBA_DIR_RANGE   30L /* Program directed range */
multiline_comment|/* PDC PAT MEM  -- Manage memory page deallocation */
DECL|macro|PDC_PAT_MEM
mdefine_line|#define PDC_PAT_MEM            72L
DECL|macro|PDC_PAT_MEM_PD_INFO
mdefine_line|#define PDC_PAT_MEM_PD_INFO     &t;0L /* Return PDT info for PD       */
DECL|macro|PDC_PAT_MEM_PD_CLEAR
mdefine_line|#define PDC_PAT_MEM_PD_CLEAR    &t;1L /* Clear PDT for PD             */
DECL|macro|PDC_PAT_MEM_PD_READ
mdefine_line|#define PDC_PAT_MEM_PD_READ     &t;2L /* Read PDT entries for PD      */
DECL|macro|PDC_PAT_MEM_PD_RESET
mdefine_line|#define PDC_PAT_MEM_PD_RESET    &t;3L /* Reset clear bit for PD       */
DECL|macro|PDC_PAT_MEM_CELL_INFO
mdefine_line|#define PDC_PAT_MEM_CELL_INFO   &t;5L /* Return PDT info For Cell     */
DECL|macro|PDC_PAT_MEM_CELL_CLEAR
mdefine_line|#define PDC_PAT_MEM_CELL_CLEAR  &t;6L /* Clear PDT For Cell           */
DECL|macro|PDC_PAT_MEM_CELL_READ
mdefine_line|#define PDC_PAT_MEM_CELL_READ   &t;7L /* Read PDT entries For Cell    */
DECL|macro|PDC_PAT_MEM_CELL_RESET
mdefine_line|#define PDC_PAT_MEM_CELL_RESET  &t;8L /* Reset clear bit For Cell     */
DECL|macro|PDC_PAT_MEM_SETGM
mdefine_line|#define PDC_PAT_MEM_SETGM&t;  &t;9L /* Set Golden Memory value      */
DECL|macro|PDC_PAT_MEM_ADD_PAGE
mdefine_line|#define PDC_PAT_MEM_ADD_PAGE    &t;10L /* ADDs a page to the cell      */
DECL|macro|PDC_PAT_MEM_ADDRESS
mdefine_line|#define PDC_PAT_MEM_ADDRESS     &t;11L /* Get Physical Location From   */
multiline_comment|/* Memory Address               */
DECL|macro|PDC_PAT_MEM_GET_TXT_SIZE
mdefine_line|#define PDC_PAT_MEM_GET_TXT_SIZE   &t;12L /* Get Formatted Text Size   */
DECL|macro|PDC_PAT_MEM_GET_PD_TXT
mdefine_line|#define PDC_PAT_MEM_GET_PD_TXT     &t;13L /* Get PD Formatted Text     */
DECL|macro|PDC_PAT_MEM_GET_CELL_TXT
mdefine_line|#define PDC_PAT_MEM_GET_CELL_TXT   &t;14L /* Get Cell Formatted Text   */
DECL|macro|PDC_PAT_MEM_RD_STATE_INFO
mdefine_line|#define PDC_PAT_MEM_RD_STATE_INFO  &t;15L /* Read Mem Module State Info*/
DECL|macro|PDC_PAT_MEM_CLR_STATE_INFO
mdefine_line|#define PDC_PAT_MEM_CLR_STATE_INFO &t;16L /*Clear Mem Module State Info*/
DECL|macro|PDC_PAT_MEM_CLEAN_RANGE
mdefine_line|#define PDC_PAT_MEM_CLEAN_RANGE    &t;128L /*Clean Mem in specific range*/
DECL|macro|PDC_PAT_MEM_GET_TBL_SIZE
mdefine_line|#define PDC_PAT_MEM_GET_TBL_SIZE   &t;131L /* Get Memory Table Size     */
DECL|macro|PDC_PAT_MEM_GET_TBL
mdefine_line|#define PDC_PAT_MEM_GET_TBL        &t;132L /* Get Memory Table          */
multiline_comment|/* PDC PAT NVOLATILE  --  Access Non-Volatile Memory */
DECL|macro|PDC_PAT_NVOLATILE
mdefine_line|#define PDC_PAT_NVOLATILE&t;73L
DECL|macro|PDC_PAT_NVOLATILE_READ
mdefine_line|#define PDC_PAT_NVOLATILE_READ&t;&t;0L /* Read Non-Volatile Memory   */
DECL|macro|PDC_PAT_NVOLATILE_WRITE
mdefine_line|#define PDC_PAT_NVOLATILE_WRITE&t;&t;1L /* Write Non-Volatile Memory  */
DECL|macro|PDC_PAT_NVOLATILE_GET_SIZE
mdefine_line|#define PDC_PAT_NVOLATILE_GET_SIZE&t;2L /* Return size of NVM         */
DECL|macro|PDC_PAT_NVOLATILE_VERIFY
mdefine_line|#define PDC_PAT_NVOLATILE_VERIFY&t;3L /* Verify contents of NVM     */
DECL|macro|PDC_PAT_NVOLATILE_INIT
mdefine_line|#define PDC_PAT_NVOLATILE_INIT&t;&t;4L /* Initialize NVM             */
multiline_comment|/* PDC PAT PD */
DECL|macro|PDC_PAT_PD
mdefine_line|#define PDC_PAT_PD&t;&t;74L         /* Protection Domain Info   */
DECL|macro|PDC_PAT_PD_GET_ADDR_MAP
mdefine_line|#define PDC_PAT_PD_GET_ADDR_MAP&t;&t;0L  /* Get Address Map          */
multiline_comment|/* PDC_PAT_PD_GET_ADDR_MAP entry types */
DECL|macro|PAT_MEMORY_DESCRIPTOR
mdefine_line|#define PAT_MEMORY_DESCRIPTOR&t;&t;1   
multiline_comment|/* PDC_PAT_PD_GET_ADDR_MAP memory types */
DECL|macro|PAT_MEMTYPE_MEMORY
mdefine_line|#define PAT_MEMTYPE_MEMORY&t;&t;0
DECL|macro|PAT_MEMTYPE_FIRMWARE
mdefine_line|#define PAT_MEMTYPE_FIRMWARE&t;&t;4
multiline_comment|/* PDC_PAT_PD_GET_ADDR_MAP memory usage */
DECL|macro|PAT_MEMUSE_GENERAL
mdefine_line|#define PAT_MEMUSE_GENERAL&t;&t;0
DECL|macro|PAT_MEMUSE_GI
mdefine_line|#define PAT_MEMUSE_GI&t;&t;&t;128
DECL|macro|PAT_MEMUSE_GNI
mdefine_line|#define PAT_MEMUSE_GNI&t;&t;&t;129
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#ifdef CONFIG_64BIT
DECL|macro|is_pdc_pat
mdefine_line|#define is_pdc_pat()&t;(PDC_TYPE_PAT == pdc_type)
r_extern
r_int
id|pdc_pat_get_irt_size
c_func
(paren
r_int
r_int
op_star
id|num_entries
comma
r_int
r_int
id|cell_num
)paren
suffix:semicolon
r_extern
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
macro_line|#else&t;/* ! CONFIG_64BIT */
multiline_comment|/* No PAT support for 32-bit kernels...sorry */
DECL|macro|is_pdc_pat
mdefine_line|#define is_pdc_pat()&t;(0)
DECL|macro|pdc_pat_get_irt_size
mdefine_line|#define pdc_pat_get_irt_size(num_entries, cell_numn)&t;PDC_BAD_PROC
DECL|macro|pdc_pat_get_irt
mdefine_line|#define pdc_pat_get_irt(r_addr, cell_num)&t;&t;PDC_BAD_PROC
macro_line|#endif&t;/* ! CONFIG_64BIT */
DECL|struct|pdc_pat_cell_num
r_struct
id|pdc_pat_cell_num
(brace
DECL|member|cell_num
r_int
r_int
id|cell_num
suffix:semicolon
DECL|member|cell_loc
r_int
r_int
id|cell_loc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pdc_pat_cpu_num
r_struct
id|pdc_pat_cpu_num
(brace
DECL|member|cpu_num
r_int
r_int
id|cpu_num
suffix:semicolon
DECL|member|cpu_loc
r_int
r_int
id|cpu_loc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pdc_pat_pd_addr_map_entry
r_struct
id|pdc_pat_pd_addr_map_entry
(brace
DECL|member|entry_type
r_int
r_char
id|entry_type
suffix:semicolon
multiline_comment|/* 1 = Memory Descriptor Entry Type */
DECL|member|reserve1
r_int
r_char
id|reserve1
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|memory_type
r_int
r_char
id|memory_type
suffix:semicolon
DECL|member|memory_usage
r_int
r_char
id|memory_usage
suffix:semicolon
DECL|member|paddr
r_int
r_int
id|paddr
suffix:semicolon
DECL|member|pages
r_int
r_int
id|pages
suffix:semicolon
multiline_comment|/* Length in 4K pages */
DECL|member|reserve2
r_int
r_int
id|reserve2
suffix:semicolon
DECL|member|cell_map
r_int
r_int
id|cell_map
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/********************************************************************&n;* PDC_PAT_CELL[Return Cell Module] memaddr[0] conf_base_addr&n;* ----------------------------------------------------------&n;* Bit  0 to 51 - conf_base_addr&n;* Bit 52 to 62 - reserved&n;* Bit       63 - endianess bit&n;********************************************************************/
DECL|macro|PAT_GET_CBA
mdefine_line|#define PAT_GET_CBA(value) ((value) &amp; 0xfffffffffffff000UL)
multiline_comment|/********************************************************************&n;* PDC_PAT_CELL[Return Cell Module] memaddr[1] mod_info&n;* ----------------------------------------------------&n;* Bit  0 to  7 - entity type&n;*    0 = central agent,            1 = processor,&n;*    2 = memory controller,        3 = system bus adapter,&n;*    4 = local bus adapter,        5 = processor bus converter,&n;*    6 = crossbar fabric connect,  7 = fabric interconnect,&n;*    8 to 254 reserved,            255 = unknown.&n;* Bit  8 to 15 - DVI&n;* Bit 16 to 23 - IOC functions&n;* Bit 24 to 39 - reserved&n;* Bit 40 to 63 - mod_pages&n;*    number of 4K pages a module occupies starting at conf_base_addr&n;********************************************************************/
DECL|macro|PAT_GET_ENTITY
mdefine_line|#define PAT_GET_ENTITY(value)&t;(((value) &gt;&gt; 56) &amp; 0xffUL)
DECL|macro|PAT_GET_DVI
mdefine_line|#define PAT_GET_DVI(value)&t;(((value) &gt;&gt; 48) &amp; 0xffUL)
DECL|macro|PAT_GET_IOC
mdefine_line|#define PAT_GET_IOC(value)&t;(((value) &gt;&gt; 40) &amp; 0xffUL)
DECL|macro|PAT_GET_MOD_PAGES
mdefine_line|#define PAT_GET_MOD_PAGES(value)(((value) &amp; 0xffffffUL)
multiline_comment|/*&n;** PDC_PAT_CELL_GET_INFO return block&n;*/
DECL|struct|pdc_pat_cell_info_rtn_block
r_typedef
r_struct
id|pdc_pat_cell_info_rtn_block
(brace
DECL|member|cpu_info
r_int
r_int
id|cpu_info
suffix:semicolon
DECL|member|cell_info
r_int
r_int
id|cell_info
suffix:semicolon
DECL|member|cell_location
r_int
r_int
id|cell_location
suffix:semicolon
DECL|member|reo_location
r_int
r_int
id|reo_location
suffix:semicolon
DECL|member|mem_size
r_int
r_int
id|mem_size
suffix:semicolon
DECL|member|dimm_status
r_int
r_int
id|dimm_status
suffix:semicolon
DECL|member|pdc_rev
r_int
r_int
id|pdc_rev
suffix:semicolon
DECL|member|fabric_info0
r_int
r_int
id|fabric_info0
suffix:semicolon
DECL|member|fabric_info1
r_int
r_int
id|fabric_info1
suffix:semicolon
DECL|member|fabric_info2
r_int
r_int
id|fabric_info2
suffix:semicolon
DECL|member|fabric_info3
r_int
r_int
id|fabric_info3
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
(braket
l_int|21
)braket
suffix:semicolon
DECL|typedef|pdc_pat_cell_info_rtn_block_t
)brace
id|pdc_pat_cell_info_rtn_block_t
suffix:semicolon
multiline_comment|/* FIXME: mod[508] should really be a union of the various mod components */
DECL|struct|pdc_pat_cell_mod_maddr_block
r_struct
id|pdc_pat_cell_mod_maddr_block
(brace
multiline_comment|/* PDC_PAT_CELL_MODULE */
DECL|member|cba
r_int
r_int
id|cba
suffix:semicolon
multiline_comment|/* func 0 cfg space address */
DECL|member|mod_info
r_int
r_int
id|mod_info
suffix:semicolon
multiline_comment|/* module information */
DECL|member|mod_location
r_int
r_int
id|mod_location
suffix:semicolon
multiline_comment|/* physical location of the module */
DECL|member|mod_path
r_struct
id|hardware_path
id|mod_path
suffix:semicolon
multiline_comment|/* module path (device path - layers) */
DECL|member|mod
r_int
r_int
id|mod
(braket
l_int|508
)braket
suffix:semicolon
multiline_comment|/* PAT cell module components */
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
DECL|typedef|pdc_pat_cell_mod_maddr_block_t
r_typedef
r_struct
id|pdc_pat_cell_mod_maddr_block
id|pdc_pat_cell_mod_maddr_block_t
suffix:semicolon
r_extern
r_int
id|pdc_pat_chassis_send_log
c_func
(paren
r_int
r_int
id|status
comma
r_int
r_int
id|data
)paren
suffix:semicolon
r_extern
r_int
id|pdc_pat_cell_get_number
c_func
(paren
r_struct
id|pdc_pat_cell_num
op_star
id|cell_info
)paren
suffix:semicolon
r_extern
r_int
id|pdc_pat_cell_module
c_func
(paren
r_int
r_int
op_star
id|actcnt
comma
r_int
r_int
id|ploc
comma
r_int
r_int
id|mod
comma
r_int
r_int
id|view_type
comma
r_void
op_star
id|mem_addr
)paren
suffix:semicolon
r_extern
r_int
id|pdc_pat_cell_num_to_loc
c_func
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|pdc_pat_cpu_get_number
c_func
(paren
r_struct
id|pdc_pat_cpu_num
op_star
id|cpu_info
comma
r_void
op_star
id|hpa
)paren
suffix:semicolon
r_extern
r_int
id|pdc_pat_pd_get_addr_map
c_func
(paren
r_int
r_int
op_star
id|actual_len
comma
r_void
op_star
id|mem_addr
comma
r_int
r_int
id|count
comma
r_int
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_int
id|pdc_pat_io_pci_cfg_read
c_func
(paren
r_int
r_int
id|pci_addr
comma
r_int
id|pci_size
comma
id|u32
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|pdc_pat_io_pci_cfg_write
c_func
(paren
r_int
r_int
id|pci_addr
comma
r_int
id|pci_size
comma
id|u32
id|val
)paren
suffix:semicolon
multiline_comment|/* Flag to indicate this is a PAT box...don&squot;t use this unless you&n;** really have to...it might go away some day.&n;*/
r_extern
r_int
id|pdc_pat
suffix:semicolon
multiline_comment|/* arch/parisc/kernel/inventory.c */
multiline_comment|/********************************************************************&n;* PDC_PAT_CELL[Return Cell Module] memaddr[0] conf_base_addr&n;* ----------------------------------------------------------&n;* Bit  0 to 51 - conf_base_addr&n;* Bit 52 to 62 - reserved&n;* Bit       63 - endianess bit&n;********************************************************************/
DECL|macro|PAT_GET_CBA
mdefine_line|#define PAT_GET_CBA(value) ((value) &amp; 0xfffffffffffff000UL)
multiline_comment|/********************************************************************&n;* PDC_PAT_CELL[Return Cell Module] memaddr[1] mod_info&n;* ----------------------------------------------------&n;* Bit  0 to  7 - entity type&n;*    0 = central agent,            1 = processor,&n;*    2 = memory controller,        3 = system bus adapter,&n;*    4 = local bus adapter,        5 = processor bus converter,&n;*    6 = crossbar fabric connect,  7 = fabric interconnect,&n;*    8 to 254 reserved,            255 = unknown.&n;* Bit  8 to 15 - DVI&n;* Bit 16 to 23 - IOC functions&n;* Bit 24 to 39 - reserved&n;* Bit 40 to 63 - mod_pages&n;*    number of 4K pages a module occupies starting at conf_base_addr&n;********************************************************************/
DECL|macro|PAT_GET_ENTITY
mdefine_line|#define PAT_GET_ENTITY(value)&t;(((value) &gt;&gt; 56) &amp; 0xffUL)
DECL|macro|PAT_GET_DVI
mdefine_line|#define PAT_GET_DVI(value)&t;(((value) &gt;&gt; 48) &amp; 0xffUL)
DECL|macro|PAT_GET_IOC
mdefine_line|#define PAT_GET_IOC(value)&t;(((value) &gt;&gt; 40) &amp; 0xffUL)
DECL|macro|PAT_GET_MOD_PAGES
mdefine_line|#define PAT_GET_MOD_PAGES(value)(((value) &amp; 0xffffffUL)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* ! __PARISC_PATPDC_H */
eof
