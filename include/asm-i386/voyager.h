multiline_comment|/* Copyright (C) 1999,2001&n; *&n; * Author: J.E.J.Bottomley@HansenPartnership.com&n; *&n; * Standard include definitions for the NCR Voyager system */
DECL|macro|VOYAGER_DEBUG
macro_line|#undef&t;VOYAGER_DEBUG
DECL|macro|VOYAGER_CAT_DEBUG
macro_line|#undef&t;VOYAGER_CAT_DEBUG
macro_line|#ifdef VOYAGER_DEBUG
DECL|macro|VDEBUG
mdefine_line|#define VDEBUG(x)&t;printk x
macro_line|#else
DECL|macro|VDEBUG
mdefine_line|#define VDEBUG(x)
macro_line|#endif
multiline_comment|/* There are three levels of voyager machine: 3,4 and 5. The rule is&n; * if it&squot;s less than 3435 it&squot;s a Level 3 except for a 3360 which is&n; * a level 4.  A 3435 or above is a Level 5 */
DECL|macro|VOYAGER_LEVEL5_AND_ABOVE
mdefine_line|#define VOYAGER_LEVEL5_AND_ABOVE&t;0x3435
DECL|macro|VOYAGER_LEVEL4
mdefine_line|#define VOYAGER_LEVEL4&t;&t;&t;0x3360
multiline_comment|/* The L4 DINO ASIC */
DECL|macro|VOYAGER_DINO
mdefine_line|#define VOYAGER_DINO&t;&t;&t;0x43
multiline_comment|/* voyager ports in standard I/O space */
DECL|macro|VOYAGER_MC_SETUP
mdefine_line|#define VOYAGER_MC_SETUP&t;0x96
DECL|macro|VOYAGER_CAT_CONFIG_PORT
mdefine_line|#define&t;VOYAGER_CAT_CONFIG_PORT&t;&t;&t;0x97
DECL|macro|VOYAGER_CAT_DESELECT
macro_line|#&t;define VOYAGER_CAT_DESELECT&t;&t;0xff
DECL|macro|VOYAGER_SSPB_RELOCATION_PORT
mdefine_line|#define VOYAGER_SSPB_RELOCATION_PORT&t;&t;0x98
multiline_comment|/* Valid CAT controller commands */
multiline_comment|/* start instruction register cycle */
DECL|macro|VOYAGER_CAT_IRCYC
mdefine_line|#define VOYAGER_CAT_IRCYC&t;&t;&t;0x01
multiline_comment|/* start data register cycle */
DECL|macro|VOYAGER_CAT_DRCYC
mdefine_line|#define VOYAGER_CAT_DRCYC&t;&t;&t;0x02
multiline_comment|/* move to execute state */
DECL|macro|VOYAGER_CAT_RUN
mdefine_line|#define VOYAGER_CAT_RUN&t;&t;&t;&t;0x0F
multiline_comment|/* end operation */
DECL|macro|VOYAGER_CAT_END
mdefine_line|#define VOYAGER_CAT_END&t;&t;&t;&t;0x80
multiline_comment|/* hold in idle state */
DECL|macro|VOYAGER_CAT_HOLD
mdefine_line|#define VOYAGER_CAT_HOLD&t;&t;&t;0x90
multiline_comment|/* single step an &quot;intest&quot; vector */
DECL|macro|VOYAGER_CAT_STEP
mdefine_line|#define VOYAGER_CAT_STEP&t;&t;&t;0xE0
multiline_comment|/* return cat controller to CLEMSON mode */
DECL|macro|VOYAGER_CAT_CLEMSON
mdefine_line|#define VOYAGER_CAT_CLEMSON&t;&t;&t;0xFF
multiline_comment|/* the default cat command header */
DECL|macro|VOYAGER_CAT_HEADER
mdefine_line|#define VOYAGER_CAT_HEADER&t;&t;&t;0x7F
multiline_comment|/* the range of possible CAT module ids in the system */
DECL|macro|VOYAGER_MIN_MODULE
mdefine_line|#define VOYAGER_MIN_MODULE&t;&t;&t;0x10
DECL|macro|VOYAGER_MAX_MODULE
mdefine_line|#define VOYAGER_MAX_MODULE&t;&t;&t;0x1f
multiline_comment|/* The voyager registers per asic */
DECL|macro|VOYAGER_ASIC_ID_REG
mdefine_line|#define VOYAGER_ASIC_ID_REG&t;&t;&t;0x00
DECL|macro|VOYAGER_ASIC_TYPE_REG
mdefine_line|#define VOYAGER_ASIC_TYPE_REG&t;&t;&t;0x01
multiline_comment|/* the sub address registers can be made auto incrementing on reads */
DECL|macro|VOYAGER_AUTO_INC_REG
mdefine_line|#define VOYAGER_AUTO_INC_REG&t;&t;&t;0x02
DECL|macro|VOYAGER_AUTO_INC
macro_line|#&t;define VOYAGER_AUTO_INC&t;&t;&t;0x04
DECL|macro|VOYAGER_NO_AUTO_INC
macro_line|#&t;define VOYAGER_NO_AUTO_INC&t;&t;0xfb
DECL|macro|VOYAGER_SUBADDRDATA
mdefine_line|#define VOYAGER_SUBADDRDATA&t;&t;&t;0x03
DECL|macro|VOYAGER_SCANPATH
mdefine_line|#define VOYAGER_SCANPATH&t;&t;&t;0x05
DECL|macro|VOYAGER_CONNECT_ASIC
macro_line|#&t;define VOYAGER_CONNECT_ASIC&t;&t;0x01
DECL|macro|VOYAGER_DISCONNECT_ASIC
macro_line|#&t;define VOYAGER_DISCONNECT_ASIC&t;&t;0xfe
DECL|macro|VOYAGER_SUBADDRLO
mdefine_line|#define VOYAGER_SUBADDRLO&t;&t;&t;0x06
DECL|macro|VOYAGER_SUBADDRHI
mdefine_line|#define VOYAGER_SUBADDRHI&t;&t;&t;0x07
DECL|macro|VOYAGER_SUBMODSELECT
mdefine_line|#define VOYAGER_SUBMODSELECT&t;&t;&t;0x08
DECL|macro|VOYAGER_SUBMODPRESENT
mdefine_line|#define VOYAGER_SUBMODPRESENT&t;&t;&t;0x09
DECL|macro|VOYAGER_SUBADDR_LO
mdefine_line|#define VOYAGER_SUBADDR_LO&t;&t;&t;0xff
DECL|macro|VOYAGER_SUBADDR_HI
mdefine_line|#define VOYAGER_SUBADDR_HI&t;&t;&t;0xffff
multiline_comment|/* the maximum size of a scan path -- used to form instructions */
DECL|macro|VOYAGER_MAX_SCAN_PATH
mdefine_line|#define VOYAGER_MAX_SCAN_PATH&t;&t;&t;0x100
multiline_comment|/* the biggest possible register size (in bytes) */
DECL|macro|VOYAGER_MAX_REG_SIZE
mdefine_line|#define VOYAGER_MAX_REG_SIZE&t;&t;&t;4
multiline_comment|/* Total number of possible modules (including submodules) */
DECL|macro|VOYAGER_MAX_MODULES
mdefine_line|#define VOYAGER_MAX_MODULES&t;&t;&t;16
multiline_comment|/* Largest number of asics per module */
DECL|macro|VOYAGER_MAX_ASICS_PER_MODULE
mdefine_line|#define VOYAGER_MAX_ASICS_PER_MODULE&t;&t;7
multiline_comment|/* the CAT asic of each module is always the first one */
DECL|macro|VOYAGER_CAT_ID
mdefine_line|#define VOYAGER_CAT_ID&t;&t;&t;&t;0
DECL|macro|VOYAGER_PSI
mdefine_line|#define VOYAGER_PSI&t;&t;&t;&t;0x1a
multiline_comment|/* voyager instruction operations and registers */
DECL|macro|VOYAGER_READ_CONFIG
mdefine_line|#define VOYAGER_READ_CONFIG&t;&t;&t;0x1
DECL|macro|VOYAGER_WRITE_CONFIG
mdefine_line|#define VOYAGER_WRITE_CONFIG&t;&t;&t;0x2
DECL|macro|VOYAGER_BYPASS
mdefine_line|#define VOYAGER_BYPASS&t;&t;&t;&t;0xff
DECL|struct|voyager_asic
r_typedef
r_struct
id|voyager_asic
(brace
DECL|member|asic_addr
id|__u8
id|asic_addr
suffix:semicolon
multiline_comment|/* ASIC address; Level 4 */
DECL|member|asic_type
id|__u8
id|asic_type
suffix:semicolon
multiline_comment|/* ASIC type */
DECL|member|asic_id
id|__u8
id|asic_id
suffix:semicolon
multiline_comment|/* ASIC id */
DECL|member|jtag_id
id|__u8
id|jtag_id
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* JTAG id */
DECL|member|asic_location
id|__u8
id|asic_location
suffix:semicolon
multiline_comment|/* Location within scan path; start w/ 0 */
DECL|member|bit_location
id|__u8
id|bit_location
suffix:semicolon
multiline_comment|/* Location within bit stream; start w/ 0 */
DECL|member|ireg_length
id|__u8
id|ireg_length
suffix:semicolon
multiline_comment|/* Instruction register length */
DECL|member|subaddr
id|__u16
id|subaddr
suffix:semicolon
multiline_comment|/* Amount of sub address space */
DECL|member|next
r_struct
id|voyager_asic
op_star
id|next
suffix:semicolon
multiline_comment|/* Next asic in linked list */
DECL|typedef|voyager_asic_t
)brace
id|voyager_asic_t
suffix:semicolon
DECL|struct|voyager_module
r_typedef
r_struct
id|voyager_module
(brace
DECL|member|module_addr
id|__u8
id|module_addr
suffix:semicolon
multiline_comment|/* Module address */
DECL|member|scan_path_connected
id|__u8
id|scan_path_connected
suffix:semicolon
multiline_comment|/* Scan path connected */
DECL|member|ee_size
id|__u16
id|ee_size
suffix:semicolon
multiline_comment|/* Size of the EEPROM */
DECL|member|num_asics
id|__u16
id|num_asics
suffix:semicolon
multiline_comment|/* Number of Asics */
DECL|member|inst_bits
id|__u16
id|inst_bits
suffix:semicolon
multiline_comment|/* Instruction bits in the scan path */
DECL|member|largest_reg
id|__u16
id|largest_reg
suffix:semicolon
multiline_comment|/* Largest register in the scan path */
DECL|member|smallest_reg
id|__u16
id|smallest_reg
suffix:semicolon
multiline_comment|/* Smallest register in the scan path */
DECL|member|asic
id|voyager_asic_t
op_star
id|asic
suffix:semicolon
multiline_comment|/* First ASIC in scan path (CAT_I) */
DECL|member|submodule
r_struct
id|voyager_module
op_star
id|submodule
suffix:semicolon
multiline_comment|/* Submodule pointer */
DECL|member|next
r_struct
id|voyager_module
op_star
id|next
suffix:semicolon
multiline_comment|/* Next module in linked list */
DECL|typedef|voyager_module_t
)brace
id|voyager_module_t
suffix:semicolon
DECL|struct|voyager_eeprom_hdr
r_typedef
r_struct
id|voyager_eeprom_hdr
(brace
DECL|member|module_id
id|__u8
id|module_id
(braket
l_int|4
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|version_id
id|__u8
id|version_id
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|config_id
id|__u8
id|config_id
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|boundry_id
id|__u16
id|boundry_id
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* boundary scan id */
DECL|member|ee_size
id|__u16
id|ee_size
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* size of EEPROM */
DECL|member|assembly
id|__u8
id|assembly
(braket
l_int|11
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* assembly # */
DECL|member|assembly_rev
id|__u8
id|assembly_rev
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* assembly rev */
DECL|member|tracer
id|__u8
id|tracer
(braket
l_int|4
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* tracer number */
DECL|member|assembly_cksum
id|__u16
id|assembly_cksum
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* asm checksum */
DECL|member|power_consump
id|__u16
id|power_consump
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* pwr requirements */
DECL|member|num_asics
id|__u16
id|num_asics
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* number of asics */
DECL|member|bist_time
id|__u16
id|bist_time
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* min. bist time */
DECL|member|err_log_offset
id|__u16
id|err_log_offset
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* error log offset */
DECL|member|scan_path_offset
id|__u16
id|scan_path_offset
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* scan path offset */
DECL|member|cct_offset
id|__u16
id|cct_offset
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|log_length
id|__u16
id|log_length
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* length of err log */
DECL|member|xsum_end
id|__u16
id|xsum_end
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* offset to end of&n;&t;&t;&t;&t;&t;&t;&t;   checksum */
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|4
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|sflag
id|__u8
id|sflag
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* starting sentinal */
DECL|member|part_number
id|__u8
id|part_number
(braket
l_int|13
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* prom part number */
DECL|member|version
id|__u8
id|version
(braket
l_int|10
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* version number */
DECL|member|signature
id|__u8
id|signature
(braket
l_int|8
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|eeprom_chksum
id|__u16
id|eeprom_chksum
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|data_stamp_offset
id|__u32
id|data_stamp_offset
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|eflag
id|__u8
id|eflag
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* ending sentinal */
DECL|typedef|voyager_eprom_hdr_t
)brace
id|voyager_eprom_hdr_t
suffix:semicolon
DECL|macro|VOYAGER_EPROM_SIZE_OFFSET
mdefine_line|#define VOYAGER_EPROM_SIZE_OFFSET   ((__u16)(&amp;(((voyager_eprom_hdr_t *)0)-&gt;ee_size)))
DECL|macro|VOYAGER_XSUM_END_OFFSET
mdefine_line|#define VOYAGER_XSUM_END_OFFSET&t;&t;0x2a
multiline_comment|/* the following three definitions are for internal table layouts&n; * in the module EPROMs.  We really only care about the IDs and&n; * offsets */
DECL|struct|voyager_sp_table
r_typedef
r_struct
id|voyager_sp_table
(brace
DECL|member|asic_id
id|__u8
id|asic_id
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bypass_flag
id|__u8
id|bypass_flag
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|asic_data_offset
id|__u16
id|asic_data_offset
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|config_data_offset
id|__u16
id|config_data_offset
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|voyager_sp_table_t
)brace
id|voyager_sp_table_t
suffix:semicolon
DECL|struct|voyager_jtag_table
r_typedef
r_struct
id|voyager_jtag_table
(brace
DECL|member|icode
id|__u8
id|icode
(braket
l_int|4
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|runbist
id|__u8
id|runbist
(braket
l_int|4
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|intest
id|__u8
id|intest
(braket
l_int|4
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|samp_preld
id|__u8
id|samp_preld
(braket
l_int|4
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|ireg_len
id|__u8
id|ireg_len
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|voyager_jtt_t
)brace
id|voyager_jtt_t
suffix:semicolon
DECL|struct|voyager_asic_data_table
r_typedef
r_struct
id|voyager_asic_data_table
(brace
DECL|member|jtag_id
id|__u8
id|jtag_id
(braket
l_int|4
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|length_bsr
id|__u16
id|length_bsr
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|length_bist_reg
id|__u16
id|length_bist_reg
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|bist_clk
id|__u32
id|bist_clk
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|subaddr_bits
id|__u16
id|subaddr_bits
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|seed_bits
id|__u16
id|seed_bits
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|sig_bits
id|__u16
id|sig_bits
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|jtag_offset
id|__u16
id|jtag_offset
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|voyager_at_t
)brace
id|voyager_at_t
suffix:semicolon
multiline_comment|/* Voyager Interrupt Controller (VIC) registers */
multiline_comment|/* Base to add to Cross Processor Interrupts (CPIs) when triggering&n; * the CPU IRQ line */
multiline_comment|/* register defines for the WCBICs (one per processor) */
DECL|macro|VOYAGER_WCBIC0
mdefine_line|#define VOYAGER_WCBIC0&t;0x41&t;&t;/* bus A node P1 processor 0 */
DECL|macro|VOYAGER_WCBIC1
mdefine_line|#define VOYAGER_WCBIC1&t;0x49&t;&t;/* bus A node P1 processor 1 */
DECL|macro|VOYAGER_WCBIC2
mdefine_line|#define VOYAGER_WCBIC2&t;0x51&t;&t;/* bus A node P2 processor 0 */
DECL|macro|VOYAGER_WCBIC3
mdefine_line|#define VOYAGER_WCBIC3&t;0x59&t;&t;/* bus A node P2 processor 1 */
DECL|macro|VOYAGER_WCBIC4
mdefine_line|#define VOYAGER_WCBIC4&t;0x61&t;&t;/* bus B node P1 processor 0 */
DECL|macro|VOYAGER_WCBIC5
mdefine_line|#define VOYAGER_WCBIC5&t;0x69&t;&t;/* bus B node P1 processor 1 */
DECL|macro|VOYAGER_WCBIC6
mdefine_line|#define VOYAGER_WCBIC6&t;0x71&t;&t;/* bus B node P2 processor 0 */
DECL|macro|VOYAGER_WCBIC7
mdefine_line|#define VOYAGER_WCBIC7&t;0x79&t;&t;/* bus B node P2 processor 1 */
multiline_comment|/* top of memory registers */
DECL|macro|VOYAGER_WCBIC_TOM_L
mdefine_line|#define VOYAGER_WCBIC_TOM_L&t;0x4
DECL|macro|VOYAGER_WCBIC_TOM_H
mdefine_line|#define VOYAGER_WCBIC_TOM_H&t;0x5
multiline_comment|/* register defines for Voyager Memory Contol (VMC) &n; * these are present on L4 machines only */
DECL|macro|VOYAGER_VMC1
mdefine_line|#define&t;VOYAGER_VMC1&t;&t;0x81
DECL|macro|VOYAGER_VMC2
mdefine_line|#define VOYAGER_VMC2&t;&t;0x91
DECL|macro|VOYAGER_VMC3
mdefine_line|#define VOYAGER_VMC3&t;&t;0xa1
DECL|macro|VOYAGER_VMC4
mdefine_line|#define VOYAGER_VMC4&t;&t;0xb1
multiline_comment|/* VMC Ports */
DECL|macro|VOYAGER_VMC_MEMORY_SETUP
mdefine_line|#define VOYAGER_VMC_MEMORY_SETUP&t;0x9
DECL|macro|VMC_Interleaving
macro_line|#&t;define VMC_Interleaving&t;&t;0x01
DECL|macro|VMC_4Way
macro_line|#&t;define VMC_4Way&t;&t;&t;0x02
DECL|macro|VMC_EvenCacheLines
macro_line|#&t;define VMC_EvenCacheLines&t;0x04
DECL|macro|VMC_HighLine
macro_line|#&t;define VMC_HighLine&t;&t;0x08
DECL|macro|VMC_Start0_Enable
macro_line|#&t;define VMC_Start0_Enable&t;0x20
DECL|macro|VMC_Start1_Enable
macro_line|#&t;define VMC_Start1_Enable&t;0x40
DECL|macro|VMC_Vremap
macro_line|#&t;define VMC_Vremap&t;&t;0x80
DECL|macro|VOYAGER_VMC_BANK_DENSITY
mdefine_line|#define VOYAGER_VMC_BANK_DENSITY&t;0xa
DECL|macro|VMC_BANK_EMPTY
macro_line|#&t;define&t;VMC_BANK_EMPTY&t;&t;0
DECL|macro|VMC_BANK_4MB
macro_line|#&t;define&t;VMC_BANK_4MB&t;&t;1
DECL|macro|VMC_BANK_16MB
macro_line|#&t;define&t;VMC_BANK_16MB&t;&t;2
DECL|macro|VMC_BANK_64MB
macro_line|#&t;define&t;VMC_BANK_64MB&t;&t;3
DECL|macro|VMC_BANK0_MASK
macro_line|#&t;define&t;VMC_BANK0_MASK&t;&t;0x03
DECL|macro|VMC_BANK1_MASK
macro_line|#&t;define&t;VMC_BANK1_MASK&t;&t;0x0C
DECL|macro|VMC_BANK2_MASK
macro_line|#&t;define&t;VMC_BANK2_MASK&t;&t;0x30
DECL|macro|VMC_BANK3_MASK
macro_line|#&t;define&t;VMC_BANK3_MASK&t;&t;0xC0
multiline_comment|/* Magellan Memory Controller (MMC) defines - present on L5 */
DECL|macro|VOYAGER_MMC_ASIC_ID
mdefine_line|#define VOYAGER_MMC_ASIC_ID&t;&t;1
multiline_comment|/* the two memory modules corresponding to memory cards in the system */
DECL|macro|VOYAGER_MMC_MEMORY0_MODULE
mdefine_line|#define VOYAGER_MMC_MEMORY0_MODULE&t;0x14
DECL|macro|VOYAGER_MMC_MEMORY1_MODULE
mdefine_line|#define VOYAGER_MMC_MEMORY1_MODULE&t;0x15
multiline_comment|/* the Magellan Memory Address (MMA) defines */
DECL|macro|VOYAGER_MMA_ASIC_ID
mdefine_line|#define VOYAGER_MMA_ASIC_ID&t;&t;2
multiline_comment|/* Submodule number for the Quad Baseboard */
DECL|macro|VOYAGER_QUAD_BASEBOARD
mdefine_line|#define VOYAGER_QUAD_BASEBOARD&t;&t;1
multiline_comment|/* ASIC defines for the Quad Baseboard */
DECL|macro|VOYAGER_QUAD_QDATA0
mdefine_line|#define VOYAGER_QUAD_QDATA0&t;&t;1
DECL|macro|VOYAGER_QUAD_QDATA1
mdefine_line|#define VOYAGER_QUAD_QDATA1&t;&t;2
DECL|macro|VOYAGER_QUAD_QABC
mdefine_line|#define VOYAGER_QUAD_QABC&t;&t;3
multiline_comment|/* Useful areas in extended CMOS */
DECL|macro|VOYAGER_PROCESSOR_PRESENT_MASK
mdefine_line|#define VOYAGER_PROCESSOR_PRESENT_MASK&t;0x88a
DECL|macro|VOYAGER_MEMORY_CLICKMAP
mdefine_line|#define VOYAGER_MEMORY_CLICKMAP&t;&t;0xa23
DECL|macro|VOYAGER_DUMP_LOCATION
mdefine_line|#define VOYAGER_DUMP_LOCATION&t;&t;0xb1a
multiline_comment|/* SUS In Control bit - used to tell SUS that we don&squot;t need to be&n; * babysat anymore */
DECL|macro|VOYAGER_SUS_IN_CONTROL_PORT
mdefine_line|#define VOYAGER_SUS_IN_CONTROL_PORT&t;0x3ff
DECL|macro|VOYAGER_IN_CONTROL_FLAG
macro_line|#&t;define VOYAGER_IN_CONTROL_FLAG&t;0x80
multiline_comment|/* Voyager PSI defines */
DECL|macro|VOYAGER_PSI_STATUS_REG
mdefine_line|#define VOYAGER_PSI_STATUS_REG&t;&t;0x08
DECL|macro|PSI_DC_FAIL
macro_line|#&t;define PSI_DC_FAIL&t;&t;0x01
DECL|macro|PSI_MON
macro_line|#&t;define PSI_MON&t;&t;&t;0x02
DECL|macro|PSI_FAULT
macro_line|#&t;define PSI_FAULT&t;&t;0x04
DECL|macro|PSI_ALARM
macro_line|#&t;define PSI_ALARM&t;&t;0x08
DECL|macro|PSI_CURRENT
macro_line|#&t;define PSI_CURRENT&t;&t;0x10
DECL|macro|PSI_DVM
macro_line|#&t;define PSI_DVM&t;&t;&t;0x20
DECL|macro|PSI_PSCFAULT
macro_line|#&t;define PSI_PSCFAULT&t;&t;0x40
DECL|macro|PSI_STAT_CHG
macro_line|#&t;define PSI_STAT_CHG&t;&t;0x80
DECL|macro|VOYAGER_PSI_SUPPLY_REG
mdefine_line|#define VOYAGER_PSI_SUPPLY_REG&t;&t;0x8000
multiline_comment|/* read */
DECL|macro|PSI_FAIL_DC
macro_line|#&t;define PSI_FAIL_DC&t;&t;0x01
DECL|macro|PSI_FAIL_AC
macro_line|#&t;define PSI_FAIL_AC&t;&t;0x02
DECL|macro|PSI_MON_INT
macro_line|#&t;define PSI_MON_INT&t;&t;0x04
DECL|macro|PSI_SWITCH_OFF
macro_line|#&t;define PSI_SWITCH_OFF&t;&t;0x08
DECL|macro|PSI_HX_OFF
macro_line|#&t;define PSI_HX_OFF&t;&t;0x10
DECL|macro|PSI_SECURITY
macro_line|#&t;define PSI_SECURITY&t;&t;0x20
DECL|macro|PSI_CMOS_BATT_LOW
macro_line|#&t;define PSI_CMOS_BATT_LOW&t;0x40
DECL|macro|PSI_CMOS_BATT_FAIL
macro_line|#&t;define PSI_CMOS_BATT_FAIL&t;0x80
multiline_comment|/* write */
DECL|macro|PSI_CLR_SWITCH_OFF
macro_line|#&t;define PSI_CLR_SWITCH_OFF&t;0x13
DECL|macro|PSI_CLR_HX_OFF
macro_line|#&t;define PSI_CLR_HX_OFF&t;&t;0x14
DECL|macro|PSI_CLR_CMOS_BATT_FAIL
macro_line|#&t;define PSI_CLR_CMOS_BATT_FAIL&t;0x17
DECL|macro|VOYAGER_PSI_MASK
mdefine_line|#define VOYAGER_PSI_MASK&t;&t;0x8001
DECL|macro|PSI_MASK_MASK
macro_line|#&t;define PSI_MASK_MASK&t;&t;0x10
DECL|macro|VOYAGER_PSI_AC_FAIL_REG
mdefine_line|#define VOYAGER_PSI_AC_FAIL_REG&t;&t;0x8004
DECL|macro|AC_FAIL_STAT_CHANGE
mdefine_line|#define&t;AC_FAIL_STAT_CHANGE&t;&t;0x80
DECL|macro|VOYAGER_PSI_GENERAL_REG
mdefine_line|#define VOYAGER_PSI_GENERAL_REG&t;&t;0x8007
multiline_comment|/* read */
DECL|macro|PSI_SWITCH_ON
macro_line|#&t;define PSI_SWITCH_ON&t;&t;0x01
DECL|macro|PSI_SWITCH_ENABLED
macro_line|#&t;define PSI_SWITCH_ENABLED&t;0x02
DECL|macro|PSI_ALARM_ENABLED
macro_line|#&t;define PSI_ALARM_ENABLED&t;0x08
DECL|macro|PSI_SECURE_ENABLED
macro_line|#&t;define PSI_SECURE_ENABLED&t;0x10
DECL|macro|PSI_COLD_RESET
macro_line|#&t;define PSI_COLD_RESET&t;&t;0x20
DECL|macro|PSI_COLD_START
macro_line|#&t;define PSI_COLD_START&t;&t;0x80
multiline_comment|/* write */
DECL|macro|PSI_POWER_DOWN
macro_line|#&t;define PSI_POWER_DOWN&t;&t;0x10
DECL|macro|PSI_SWITCH_DISABLE
macro_line|#&t;define PSI_SWITCH_DISABLE&t;0x01
DECL|macro|PSI_SWITCH_ENABLE
macro_line|#&t;define PSI_SWITCH_ENABLE&t;0x11
DECL|macro|PSI_CLEAR
macro_line|#&t;define PSI_CLEAR&t;&t;0x12
DECL|macro|PSI_ALARM_DISABLE
macro_line|#&t;define PSI_ALARM_DISABLE&t;0x03
DECL|macro|PSI_ALARM_ENABLE
macro_line|#&t;define PSI_ALARM_ENABLE&t;&t;0x13
DECL|macro|PSI_CLEAR_COLD_RESET
macro_line|#&t;define PSI_CLEAR_COLD_RESET&t;0x05
DECL|macro|PSI_SET_COLD_RESET
macro_line|#&t;define PSI_SET_COLD_RESET&t;0x15
DECL|macro|PSI_CLEAR_COLD_START
macro_line|#&t;define PSI_CLEAR_COLD_START&t;0x07
DECL|macro|PSI_SET_COLD_START
macro_line|#&t;define PSI_SET_COLD_START&t;0x17
DECL|struct|voyager_bios_info
r_struct
id|voyager_bios_info
(brace
DECL|member|len
id|__u8
id|len
suffix:semicolon
DECL|member|major
id|__u8
id|major
suffix:semicolon
DECL|member|minor
id|__u8
id|minor
suffix:semicolon
DECL|member|debug
id|__u8
id|debug
suffix:semicolon
DECL|member|num_classes
id|__u8
id|num_classes
suffix:semicolon
DECL|member|class_1
id|__u8
id|class_1
suffix:semicolon
DECL|member|class_2
id|__u8
id|class_2
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The following structures and definitions are for the Kernel/SUS&n; * interface these are needed to find out how SUS initialised any Quad&n; * boards in the system */
DECL|macro|NUMBER_OF_MC_BUSSES
mdefine_line|#define&t;NUMBER_OF_MC_BUSSES&t;2
DECL|macro|SLOTS_PER_MC_BUS
mdefine_line|#define SLOTS_PER_MC_BUS&t;8
DECL|macro|MAX_CPUS
mdefine_line|#define MAX_CPUS                16      /* 16 way CPU system */
DECL|macro|MAX_PROCESSOR_BOARDS
mdefine_line|#define MAX_PROCESSOR_BOARDS&t;4&t;/* 4 processor slot system */
DECL|macro|MAX_CACHE_LEVELS
mdefine_line|#define MAX_CACHE_LEVELS&t;4&t;/* # of cache levels supported */
DECL|macro|MAX_SHARED_CPUS
mdefine_line|#define MAX_SHARED_CPUS&t;&t;4&t;/* # of CPUs that can share a LARC */
DECL|macro|NUMBER_OF_POS_REGS
mdefine_line|#define NUMBER_OF_POS_REGS&t;8
r_typedef
r_struct
(brace
DECL|member|MC_Slot
id|__u8
id|MC_Slot
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|POS_Values
id|__u8
id|POS_Values
(braket
id|NUMBER_OF_POS_REGS
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|MC_SlotInformation_t
)brace
id|MC_SlotInformation_t
suffix:semicolon
DECL|struct|QuadDescription
r_struct
id|QuadDescription
(brace
DECL|member|Type
id|__u8
id|Type
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* for type 0 (DYADIC or MONADIC) all fields&n;                         * will be zero except for slot */
DECL|member|StructureVersion
id|__u8
id|StructureVersion
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|CPI_BaseAddress
id|__u32
id|CPI_BaseAddress
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|LARC_BankSize
id|__u32
id|LARC_BankSize
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|LocalMemoryStateBits
id|__u32
id|LocalMemoryStateBits
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Slot
id|__u8
id|Slot
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Processor slots 1 - 4 */
)brace
suffix:semicolon
DECL|struct|ProcBoardInfo
r_struct
id|ProcBoardInfo
(brace
DECL|member|Type
id|__u8
id|Type
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|StructureVersion
id|__u8
id|StructureVersion
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|NumberOfBoards
id|__u8
id|NumberOfBoards
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|QuadData
r_struct
id|QuadDescription
id|QuadData
(braket
id|MAX_PROCESSOR_BOARDS
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|CacheDescription
r_struct
id|CacheDescription
(brace
DECL|member|Level
id|__u8
id|Level
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|TotalSize
id|__u32
id|TotalSize
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|LineSize
id|__u16
id|LineSize
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Associativity
id|__u8
id|Associativity
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|CacheType
id|__u8
id|CacheType
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|WriteType
id|__u8
id|WriteType
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Number_CPUs_SharedBy
id|__u8
id|Number_CPUs_SharedBy
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|Shared_CPUs_Hardware_IDs
id|__u8
id|Shared_CPUs_Hardware_IDs
(braket
id|MAX_SHARED_CPUS
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|CPU_Description
r_struct
id|CPU_Description
(brace
DECL|member|CPU_HardwareId
id|__u8
id|CPU_HardwareId
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|FRU_String
r_char
op_star
id|FRU_String
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|NumberOfCacheLevels
id|__u8
id|NumberOfCacheLevels
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|CacheLevelData
r_struct
id|CacheDescription
id|CacheLevelData
(braket
id|MAX_CACHE_LEVELS
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|CPU_Info
r_struct
id|CPU_Info
(brace
DECL|member|Type
id|__u8
id|Type
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|StructureVersion
id|__u8
id|StructureVersion
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|NumberOf_CPUs
id|__u8
id|NumberOf_CPUs
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|CPU_Data
r_struct
id|CPU_Description
id|CPU_Data
(braket
id|MAX_CPUS
)braket
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This structure will be used by SUS and the OS.&n; * The assumption about this structure is that no blank space is&n; * packed in it by our friend the compiler.&n; */
r_typedef
r_struct
(brace
DECL|member|Mailbox_SUS
id|__u8
id|Mailbox_SUS
suffix:semicolon
multiline_comment|/* Written to by SUS to give commands/response to the OS */
DECL|member|Mailbox_OS
id|__u8
id|Mailbox_OS
suffix:semicolon
multiline_comment|/* Written to by the OS to give commands/response to SUS */
DECL|member|SUS_MailboxVersion
id|__u8
id|SUS_MailboxVersion
suffix:semicolon
multiline_comment|/* Tells the OS which iteration of the interface SUS supports */
DECL|member|OS_MailboxVersion
id|__u8
id|OS_MailboxVersion
suffix:semicolon
multiline_comment|/* Tells SUS which iteration of the interface the OS supports */
DECL|member|OS_Flags
id|__u32
id|OS_Flags
suffix:semicolon
multiline_comment|/* Flags set by the OS as info for SUS */
DECL|member|SUS_Flags
id|__u32
id|SUS_Flags
suffix:semicolon
multiline_comment|/* Flags set by SUS as info for the OS */
DECL|member|WatchDogPeriod
id|__u32
id|WatchDogPeriod
suffix:semicolon
multiline_comment|/* Watchdog period (in seconds) which the DP uses to see if the OS is dead */
DECL|member|WatchDogCount
id|__u32
id|WatchDogCount
suffix:semicolon
multiline_comment|/* Updated by the OS on every tic. */
DECL|member|MemoryFor_SUS_ErrorLog
id|__u32
id|MemoryFor_SUS_ErrorLog
suffix:semicolon
multiline_comment|/* Flat 32 bit address which tells SUS where to stuff the SUS error log on a dump */
DECL|member|MC_SlotInfo
id|MC_SlotInformation_t
id|MC_SlotInfo
(braket
id|NUMBER_OF_MC_BUSSES
op_star
id|SLOTS_PER_MC_BUS
)braket
suffix:semicolon
multiline_comment|/* Storage for MCA POS data */
multiline_comment|/* All new SECOND_PASS_INTERFACE fields added from this point */
DECL|member|BoardData
r_struct
id|ProcBoardInfo
op_star
id|BoardData
suffix:semicolon
DECL|member|CPU_Data
r_struct
id|CPU_Info
op_star
id|CPU_Data
suffix:semicolon
multiline_comment|/* All new fields must be added from this point */
DECL|typedef|Voyager_KernelSUS_Mbox_t
)brace
id|Voyager_KernelSUS_Mbox_t
suffix:semicolon
multiline_comment|/* structure for finding the right memory address to send a QIC CPI to */
DECL|struct|voyager_qic_cpi
r_struct
id|voyager_qic_cpi
(brace
multiline_comment|/* Each cache line (32 bytes) can trigger a cpi.  The cpi&n;&t; * read/write may occur anywhere in the cache line---pick the&n;&t; * middle to be safe */
r_struct
(brace
DECL|member|pad1
id|__u32
id|pad1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|cpi
id|__u32
id|cpi
suffix:semicolon
DECL|member|pad2
id|__u32
id|pad2
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|qic_cpi
)brace
id|qic_cpi
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|voyager_status
r_struct
id|voyager_status
(brace
DECL|member|power_fail
id|__u32
id|power_fail
suffix:colon
l_int|1
suffix:semicolon
DECL|member|switch_off
id|__u32
id|switch_off
suffix:colon
l_int|1
suffix:semicolon
DECL|member|request_from_kernel
id|__u32
id|request_from_kernel
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|voyager_psi_regs
r_struct
id|voyager_psi_regs
(brace
DECL|member|cat_id
id|__u8
id|cat_id
suffix:semicolon
DECL|member|cat_dev
id|__u8
id|cat_dev
suffix:semicolon
DECL|member|cat_control
id|__u8
id|cat_control
suffix:semicolon
DECL|member|subaddr
id|__u8
id|subaddr
suffix:semicolon
DECL|member|dummy4
id|__u8
id|dummy4
suffix:semicolon
DECL|member|checkbit
id|__u8
id|checkbit
suffix:semicolon
DECL|member|subaddr_low
id|__u8
id|subaddr_low
suffix:semicolon
DECL|member|subaddr_high
id|__u8
id|subaddr_high
suffix:semicolon
DECL|member|intstatus
id|__u8
id|intstatus
suffix:semicolon
DECL|member|stat1
id|__u8
id|stat1
suffix:semicolon
DECL|member|stat3
id|__u8
id|stat3
suffix:semicolon
DECL|member|fault
id|__u8
id|fault
suffix:semicolon
DECL|member|tms
id|__u8
id|tms
suffix:semicolon
DECL|member|gen
id|__u8
id|gen
suffix:semicolon
DECL|member|sysconf
id|__u8
id|sysconf
suffix:semicolon
DECL|member|dummy15
id|__u8
id|dummy15
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|voyager_psi_subregs
r_struct
id|voyager_psi_subregs
(brace
DECL|member|supply
id|__u8
id|supply
suffix:semicolon
DECL|member|mask
id|__u8
id|mask
suffix:semicolon
DECL|member|present
id|__u8
id|present
suffix:semicolon
DECL|member|DCfail
id|__u8
id|DCfail
suffix:semicolon
DECL|member|ACfail
id|__u8
id|ACfail
suffix:semicolon
DECL|member|fail
id|__u8
id|fail
suffix:semicolon
DECL|member|UPSfail
id|__u8
id|UPSfail
suffix:semicolon
DECL|member|genstatus
id|__u8
id|genstatus
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|voyager_psi
r_struct
id|voyager_psi
(brace
DECL|member|regs
r_struct
id|voyager_psi_regs
id|regs
suffix:semicolon
DECL|member|subregs
r_struct
id|voyager_psi_subregs
id|subregs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|voyager_SUS
r_struct
id|voyager_SUS
(brace
DECL|macro|VOYAGER_DUMP_BUTTON_NMI
mdefine_line|#define&t;VOYAGER_DUMP_BUTTON_NMI&t;&t;0x1
DECL|macro|VOYAGER_SUS_VALID
mdefine_line|#define VOYAGER_SUS_VALID&t;&t;0x2
DECL|macro|VOYAGER_SYSINT_COMPLETE
mdefine_line|#define VOYAGER_SYSINT_COMPLETE&t;&t;0x3
DECL|member|SUS_mbox
id|__u8
id|SUS_mbox
suffix:semicolon
DECL|macro|VOYAGER_NO_COMMAND
mdefine_line|#define VOYAGER_NO_COMMAND&t;&t;0x0
DECL|macro|VOYAGER_IGNORE_DUMP
mdefine_line|#define VOYAGER_IGNORE_DUMP&t;&t;0x1
DECL|macro|VOYAGER_DO_DUMP
mdefine_line|#define VOYAGER_DO_DUMP&t;&t;&t;0x2
DECL|macro|VOYAGER_SYSINT_HANDSHAKE
mdefine_line|#define VOYAGER_SYSINT_HANDSHAKE&t;0x3
DECL|macro|VOYAGER_DO_MEM_DUMP
mdefine_line|#define VOYAGER_DO_MEM_DUMP&t;&t;0x4
DECL|macro|VOYAGER_SYSINT_WAS_RECOVERED
mdefine_line|#define VOYAGER_SYSINT_WAS_RECOVERED&t;0x5
DECL|member|kernel_mbox
id|__u8
id|kernel_mbox
suffix:semicolon
DECL|macro|VOYAGER_MAILBOX_VERSION
mdefine_line|#define&t;VOYAGER_MAILBOX_VERSION&t;&t;0x10
DECL|member|SUS_version
id|__u8
id|SUS_version
suffix:semicolon
DECL|member|kernel_version
id|__u8
id|kernel_version
suffix:semicolon
DECL|macro|VOYAGER_OS_HAS_SYSINT
mdefine_line|#define VOYAGER_OS_HAS_SYSINT&t;&t;0x1
DECL|macro|VOYAGER_OS_IN_PROGRESS
mdefine_line|#define VOYAGER_OS_IN_PROGRESS&t;&t;0x2
DECL|macro|VOYAGER_UPDATING_WDPERIOD
mdefine_line|#define VOYAGER_UPDATING_WDPERIOD&t;0x4
DECL|member|kernel_flags
id|__u32
id|kernel_flags
suffix:semicolon
DECL|macro|VOYAGER_SUS_BOOTING
mdefine_line|#define VOYAGER_SUS_BOOTING&t;&t;0x1
DECL|macro|VOYAGER_SUS_IN_PROGRESS
mdefine_line|#define VOYAGER_SUS_IN_PROGRESS&t;&t;0x2
DECL|member|SUS_flags
id|__u32
id|SUS_flags
suffix:semicolon
DECL|member|watchdog_period
id|__u32
id|watchdog_period
suffix:semicolon
DECL|member|watchdog_count
id|__u32
id|watchdog_count
suffix:semicolon
DECL|member|SUS_errorlog
id|__u32
id|SUS_errorlog
suffix:semicolon
multiline_comment|/* lots of system configuration stuff under here */
)brace
suffix:semicolon
multiline_comment|/* Variables exported by voyager_smp */
r_extern
id|__u32
id|voyager_extended_vic_processors
suffix:semicolon
r_extern
id|__u32
id|voyager_allowed_boot_processors
suffix:semicolon
r_extern
id|__u32
id|voyager_quad_processors
suffix:semicolon
r_extern
r_struct
id|voyager_qic_cpi
op_star
id|voyager_quad_cpi_addr
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_struct
id|voyager_SUS
op_star
id|voyager_SUS
suffix:semicolon
multiline_comment|/* variables exported always */
r_extern
r_int
id|voyager_level
suffix:semicolon
r_extern
r_int
id|kvoyagerd_running
suffix:semicolon
r_extern
r_struct
id|semaphore
id|kvoyagerd_sem
suffix:semicolon
r_extern
r_struct
id|voyager_status
id|voyager_status
suffix:semicolon
multiline_comment|/* functions exported by the voyager and voyager_smp modules */
r_extern
r_int
id|voyager_cat_readb
c_func
(paren
id|__u8
id|module
comma
id|__u8
id|asic
comma
r_int
id|reg
)paren
suffix:semicolon
r_extern
r_void
id|voyager_cat_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|voyager_detect
c_func
(paren
r_struct
id|voyager_bios_info
op_star
)paren
suffix:semicolon
r_extern
r_void
id|voyager_trap_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|voyager_setup_irqs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|voyager_memory_detect
c_func
(paren
r_int
id|region
comma
id|__u32
op_star
id|addr
comma
id|__u32
op_star
id|length
)paren
suffix:semicolon
r_extern
r_void
id|voyager_smp_intr_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|__u8
id|voyager_extended_cmos_read
c_func
(paren
id|__u16
id|cmos_address
)paren
suffix:semicolon
r_extern
r_void
id|voyager_smp_dump
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|voyager_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|smp_local_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|voyager_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_voyager_power_off
c_func
(paren
r_void
op_star
id|dummy
)paren
suffix:semicolon
r_extern
r_void
id|voyager_restart
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|voyager_cat_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|voyager_cat_do_common_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|voyager_handle_nmi
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Commands for the following are */
DECL|macro|VOYAGER_PSI_READ
mdefine_line|#define&t;VOYAGER_PSI_READ&t;0
DECL|macro|VOYAGER_PSI_WRITE
mdefine_line|#define VOYAGER_PSI_WRITE&t;1
DECL|macro|VOYAGER_PSI_SUBREAD
mdefine_line|#define VOYAGER_PSI_SUBREAD&t;2
DECL|macro|VOYAGER_PSI_SUBWRITE
mdefine_line|#define VOYAGER_PSI_SUBWRITE&t;3
r_extern
r_void
id|voyager_cat_psi
c_func
(paren
id|__u8
comma
id|__u16
comma
id|__u8
op_star
)paren
suffix:semicolon
eof
