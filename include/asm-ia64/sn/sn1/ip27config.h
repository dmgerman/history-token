multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_SN1_IP27CONFIG_H
DECL|macro|_ASM_SN_SN1_IP27CONFIG_H
mdefine_line|#define _ASM_SN_SN1_IP27CONFIG_H
multiline_comment|/*&n; * Structure: &t;ip27config_s&n; * Typedef:&t;ip27config_t&n; * Purpose: &t;Maps out the region of the boot prom used to define&n; *&t;&t;configuration information.&n; * Notes:       Corresponds to ip27config structure found in start.s.&n; *&t;&t;Fields are ulong where possible to facilitate IP27 PROM fetches.&n; */
DECL|macro|CONFIG_INFO_OFFSET
mdefine_line|#define CONFIG_INFO_OFFSET&t;&t;0x60
DECL|macro|IP27CONFIG_ADDR
mdefine_line|#define IP27CONFIG_ADDR&t;&t;&t;(LBOOT_BASE&t;    + &bslash;&n;&t;&t;&t;&t;&t; CONFIG_INFO_OFFSET)
DECL|macro|IP27CONFIG_ADDR_NODE
mdefine_line|#define IP27CONFIG_ADDR_NODE(n)&t;&t;(NODE_RBOOT_BASE(n) + &bslash;&n;&t;&t;&t;&t;&t; CONFIG_INFO_OFFSET)
multiline_comment|/* Offset to the config_type field within local ip27config structure */
DECL|macro|CONFIG_FLAGS_ADDR
mdefine_line|#define CONFIG_FLAGS_ADDR&t;&t;&t;(IP27CONFIG_ADDR + 72)
multiline_comment|/* Offset to the config_type field in the ip27config structure on &n; * node with nasid n&n; */
DECL|macro|CONFIG_FLAGS_ADDR_NODE
mdefine_line|#define CONFIG_FLAGS_ADDR_NODE(n)&t;&t;(IP27CONFIG_ADDR_NODE(n) + 72)
multiline_comment|/* Meaning of each valid bit in the config flags &n; * None are currently defined&n; */
multiline_comment|/* Meaning of each mach_type value&n; */
DECL|macro|SN1_MACH_TYPE
mdefine_line|#define SN1_MACH_TYPE 0
multiline_comment|/*&n; * Since 800 ns works well with various HUB frequencies, (such as 360,&n; * 380, 390, and 400 MHZ), we now use 800ns rtc cycle time instead of&n; * 1 microsec.&n; */
DECL|macro|IP27_RTC_FREQ
mdefine_line|#define IP27_RTC_FREQ&t;&t;&t;1250&t;/* 800ns cycle time */
macro_line|#if _LANGUAGE_C
DECL|struct|ip27config_s
r_typedef
r_struct
id|ip27config_s
(brace
multiline_comment|/* KEEP IN SYNC w/ start.s &amp; below  */
DECL|member|time_const
id|uint
id|time_const
suffix:semicolon
multiline_comment|/* Time constant &t;&t;    */
DECL|member|r10k_mode
id|uint
id|r10k_mode
suffix:semicolon
multiline_comment|/* R10k boot mode bits &t;&t;    */
DECL|member|magic
r_uint64
id|magic
suffix:semicolon
multiline_comment|/* CONFIG_MAGIC&t;&t;&t;    */
DECL|member|freq_cpu
r_uint64
id|freq_cpu
suffix:semicolon
multiline_comment|/* Hz &t;&t;&t;&t;    */
DECL|member|freq_hub
r_uint64
id|freq_hub
suffix:semicolon
multiline_comment|/* Hz &t;&t;&t;&t;    */
DECL|member|freq_rtc
r_uint64
id|freq_rtc
suffix:semicolon
multiline_comment|/* Hz &t;&t;&t;&t;    */
DECL|member|ecc_enable
id|uint
id|ecc_enable
suffix:semicolon
multiline_comment|/* ECC enable flag&t;&t;    */
DECL|member|fprom_cyc
id|uint
id|fprom_cyc
suffix:semicolon
multiline_comment|/* FPROM_CYC speed control  &t;    */
DECL|member|mach_type
id|uint
id|mach_type
suffix:semicolon
multiline_comment|/* Inidicate IP27 (0) or Sn00 (1)    */
DECL|member|check_sum_adj
id|uint
id|check_sum_adj
suffix:semicolon
multiline_comment|/* Used after config hdr overlay    */
multiline_comment|/* to make the checksum 0 again     */
DECL|member|flash_count
id|uint
id|flash_count
suffix:semicolon
multiline_comment|/* Value incr&squot;d on each PROM flash  */
DECL|member|fprom_wr
id|uint
id|fprom_wr
suffix:semicolon
multiline_comment|/* FPROM_WR speed control  &t;    */
DECL|member|pvers_vers
id|uint
id|pvers_vers
suffix:semicolon
multiline_comment|/* Prom version number&t;&t;    */
DECL|member|pvers_rev
id|uint
id|pvers_rev
suffix:semicolon
multiline_comment|/* Prom revision number&t;&t;    */
DECL|member|config_type
id|uint
id|config_type
suffix:semicolon
multiline_comment|/* To support special configurations&n;&t;&t;&t;&t;&t; * (none currently defined)&n;&t;&t;&t;&t;&t; */
DECL|typedef|ip27config_t
)brace
id|ip27config_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|r10k_mode
id|uint
id|r10k_mode
suffix:semicolon
multiline_comment|/* R10k boot mode bits &t;&t;    */
DECL|member|freq_cpu
id|uint
id|freq_cpu
suffix:semicolon
multiline_comment|/* Hz &t;&t;&t;&t;    */
DECL|member|freq_hub
id|uint
id|freq_hub
suffix:semicolon
multiline_comment|/* Hz &t;&t;&t;&t;    */
DECL|member|fprom_cyc
r_char
id|fprom_cyc
suffix:semicolon
multiline_comment|/* FPROM_CYC speed control  &t;    */
DECL|member|mach_type
r_char
id|mach_type
suffix:semicolon
multiline_comment|/* IP35(0) is only type defined      */
DECL|member|fprom_wr
r_char
id|fprom_wr
suffix:semicolon
multiline_comment|/* FPROM_WR speed control  &t;    */
DECL|typedef|config_modifiable_t
)brace
id|config_modifiable_t
suffix:semicolon
DECL|macro|IP27CONFIG
mdefine_line|#define IP27CONFIG&t;&t;(*(ip27config_t *) IP27CONFIG_ADDR)
DECL|macro|IP27CONFIG_NODE
mdefine_line|#define IP27CONFIG_NODE(n)&t;(*(ip27config_t *) IP27CONFIG_ADDR_NODE(n))
DECL|macro|SN00
mdefine_line|#define SN00&t;&t;&t;0 /* IP35 has no Speedo equivalent */
multiline_comment|/* Get the config flags from local ip27config */
DECL|macro|CONFIG_FLAGS
mdefine_line|#define CONFIG_FLAGS&t;&t;(*(uint *) (CONFIG_FLAGS_ADDR))
multiline_comment|/* Get the config flags from ip27config on the node&n; * with nasid n&n; */
DECL|macro|CONFIG_FLAGS_NODE
mdefine_line|#define CONFIG_FLAGS_NODE(n)&t;(*(uint *) (CONFIG_FLAGS_ADDR_NODE(n)))
multiline_comment|/* Macro to check if the local ip27config indicates a config&n; * of 12 p 4io&n; */
DECL|macro|CONFIG_12P4I
mdefine_line|#define CONFIG_12P4I&t;&t;(0) /* IP35 has no 12p4i equivalent */
multiline_comment|/* Macro to check if the ip27config on node with nasid n&n; * indicates a config of 12 p 4io&n; */
DECL|macro|CONFIG_12P4I_NODE
mdefine_line|#define CONFIG_12P4I_NODE(n)&t;(0)
macro_line|#endif /* _LANGUAGE_C */
macro_line|#if _LANGUAGE_ASSEMBLY
dot
r_struct
l_int|0
multiline_comment|/* KEEP IN SYNC WITH C structure */
id|ip27c_time_const
suffix:colon
dot
id|word
l_int|0
id|ip27c_r10k_mode
suffix:colon
dot
id|word
l_int|0
id|ip27c_magic
suffix:colon
dot
id|dword
l_int|0
id|ip27c_freq_cpu
suffix:colon
dot
id|dword
l_int|0
id|ip27c_freq_hub
suffix:colon
dot
id|dword
l_int|0
id|ip27c_freq_rtc
suffix:colon
dot
id|dword
l_int|0
id|ip27c_ecc_enable
suffix:colon
dot
id|word
l_int|1
id|ip27c_fprom_cyc
suffix:colon
dot
id|word
l_int|0
id|ip27c_mach_type
suffix:colon
dot
id|word
l_int|0
id|ip27c_check_sum_adj
suffix:colon
dot
id|word
l_int|0
id|ip27c_flash_count
suffix:colon
dot
id|word
l_int|0
id|ip27c_fprom_wr
suffix:colon
dot
id|word
l_int|0
id|ip27c_pvers_vers
suffix:colon
dot
id|word
l_int|0
id|ip27c_pvers_rev
suffix:colon
dot
id|word
l_int|0
id|ip27c_config_type
suffix:colon
dot
id|word
l_int|0
multiline_comment|/* To recognize special configs */
macro_line|#endif /* _LANGUAGE_ASSEMBLY */
multiline_comment|/*&n; * R10000 Configuration Cycle - These define the SYSAD values used&n; * during the reset cycle.&n; */
DECL|macro|IP27C_R10000_KSEG0CA_SHFT
mdefine_line|#define&t;IP27C_R10000_KSEG0CA_SHFT&t;0
DECL|macro|IP27C_R10000_KSEG0CA_MASK
mdefine_line|#define&t;IP27C_R10000_KSEG0CA_MASK&t;(7 &lt;&lt; IP27C_R10000_KSEG0CA_SHFT)
DECL|macro|IP27C_R10000_KSEG0CA
mdefine_line|#define&t;IP27C_R10000_KSEG0CA(_B)&t; ((_B) &lt;&lt; IP27C_R10000_KSEG0CA_SHFT)
DECL|macro|IP27C_R10000_DEVNUM_SHFT
mdefine_line|#define&t;IP27C_R10000_DEVNUM_SHFT&t;3
DECL|macro|IP27C_R10000_DEVNUM_MASK
mdefine_line|#define&t;IP27C_R10000_DEVNUM_MASK&t;(3 &lt;&lt; IP27C_R10000_DEVNUM_SHFT)
DECL|macro|IP27C_R10000_DEVNUM
mdefine_line|#define&t;IP27C_R10000_DEVNUM(_B)&t;&t;((_B) &lt;&lt; IP27C_R10000_DEVNUM_SHFT)
DECL|macro|IP27C_R10000_CRPT_SHFT
mdefine_line|#define&t;IP27C_R10000_CRPT_SHFT&t;&t;5
DECL|macro|IP27C_R10000_CRPT_MASK
mdefine_line|#define&t;IP27C_R10000_CRPT_MASK&t;&t;(1 &lt;&lt; IP27C_R10000_CRPT_SHFT)
DECL|macro|IP27C_R10000_CPRT
mdefine_line|#define&t;IP27C_R10000_CPRT(_B)&t;&t;((_B)&lt;&lt;IP27C_R10000_CRPT_SHFT)
DECL|macro|IP27C_R10000_PER_SHFT
mdefine_line|#define&t;IP27C_R10000_PER_SHFT&t;&t;6
DECL|macro|IP27C_R10000_PER_MASK
mdefine_line|#define&t;IP27C_R10000_PER_MASK&t;&t;(1 &lt;&lt; IP27C_R10000_PER_SHFT)
DECL|macro|IP27C_R10000_PER
mdefine_line|#define&t;IP27C_R10000_PER(_B)&t;&t;((_B) &lt;&lt; IP27C_R10000_PER_SHFT)
DECL|macro|IP27C_R10000_PRM_SHFT
mdefine_line|#define&t;IP27C_R10000_PRM_SHFT&t;&t;7
DECL|macro|IP27C_R10000_PRM_MASK
mdefine_line|#define&t;IP27C_R10000_PRM_MASK&t;&t;(3 &lt;&lt; IP27C_R10000_PRM_SHFT)
DECL|macro|IP27C_R10000_PRM
mdefine_line|#define&t;IP27C_R10000_PRM(_B)&t;&t;((_B) &lt;&lt; IP27C_R10000_PRM_SHFT)
DECL|macro|IP27C_R10000_SCD_SHFT
mdefine_line|#define&t;IP27C_R10000_SCD_SHFT&t;&t;9
DECL|macro|IP27C_R10000_SCD_MASK
mdefine_line|#define&t;IP27C_R10000_SCD_MASK&t;&t;(0xf &lt;&lt; IP27C_R10000_SCD_MASK)
DECL|macro|IP27C_R10000_SCD
mdefine_line|#define&t;IP27C_R10000_SCD(_B)&t;&t;((_B) &lt;&lt; IP27C_R10000_SCD_SHFT)
DECL|macro|IP27C_R10000_SCBS_SHFT
mdefine_line|#define&t;IP27C_R10000_SCBS_SHFT&t;&t;13
DECL|macro|IP27C_R10000_SCBS_MASK
mdefine_line|#define&t;IP27C_R10000_SCBS_MASK&t;&t;(1 &lt;&lt; IP27C_R10000_SCBS_SHFT)
DECL|macro|IP27C_R10000_SCBS
mdefine_line|#define&t;IP27C_R10000_SCBS(_B)&t;&t;(((_B)) &lt;&lt; IP27C_R10000_SCBS_SHFT)
DECL|macro|IP27C_R10000_SCCE_SHFT
mdefine_line|#define&t;IP27C_R10000_SCCE_SHFT&t;&t;14
DECL|macro|IP27C_R10000_SCCE_MASK
mdefine_line|#define&t;IP27C_R10000_SCCE_MASK&t;&t;(1 &lt;&lt; IP27C_R10000_SCCE_SHFT)
DECL|macro|IP27C_R10000_SCCE
mdefine_line|#define&t;IP27C_R10000_SCCE(_B)&t;&t;((_B) &lt;&lt; IP27C_R10000_SCCE_SHFT)
DECL|macro|IP27C_R10000_ME_SHFT
mdefine_line|#define&t;IP27C_R10000_ME_SHFT&t;&t;15
DECL|macro|IP27C_R10000_ME_MASK
mdefine_line|#define&t;IP27C_R10000_ME_MASK&t;&t;(1 &lt;&lt; IP27C_R10000_ME_SHFT)
DECL|macro|IP27C_R10000_ME
mdefine_line|#define&t;IP27C_R10000_ME(_B)&t;&t;((_B) &lt;&lt; IP27C_R10000_ME_SHFT)
DECL|macro|IP27C_R10000_SCS_SHFT
mdefine_line|#define&t;IP27C_R10000_SCS_SHFT&t;&t;16
DECL|macro|IP27C_R10000_SCS_MASK
mdefine_line|#define&t;IP27C_R10000_SCS_MASK&t;&t;(7 &lt;&lt; IP27C_R10000_SCS_SHFT)
DECL|macro|IP27C_R10000_SCS
mdefine_line|#define&t;IP27C_R10000_SCS(_B)&t;&t;((_B) &lt;&lt; IP27C_R10000_SCS_SHFT)
DECL|macro|IP27C_R10000_SCCD_SHFT
mdefine_line|#define&t;IP27C_R10000_SCCD_SHFT&t;&t;19
DECL|macro|IP27C_R10000_SCCD_MASK
mdefine_line|#define&t;IP27C_R10000_SCCD_MASK&t;&t;(7 &lt;&lt; IP27C_R10000_SCCD_SHFT)
DECL|macro|IP27C_R10000_SCCD
mdefine_line|#define&t;IP27C_R10000_SCCD(_B)&t;&t;((_B) &lt;&lt; IP27C_R10000_SCCD_SHFT)
DECL|macro|IP27C_R10000_SCCT_SHFT
mdefine_line|#define&t;IP27C_R10000_SCCT_SHFT&t;&t;25
DECL|macro|IP27C_R10000_SCCT_MASK
mdefine_line|#define&t;IP27C_R10000_SCCT_MASK&t;&t;(0xf &lt;&lt; IP27C_R10000_SCCT_SHFT)
DECL|macro|IP27C_R10000_SCCT
mdefine_line|#define&t;IP27C_R10000_SCCT(_B)&t;&t;((_B) &lt;&lt; IP27C_R10000_SCCT_SHFT)
DECL|macro|IP27C_R10000_ODSC_SHFT
mdefine_line|#define&t;IP27C_R10000_ODSC_SHFT&t;&t;29
DECL|macro|IP27C_R10000_ODSC_MASK
mdefine_line|#define IP27C_R10000_ODSC_MASK&t;&t;(1 &lt;&lt; IP27C_R10000_ODSC_SHFT)
DECL|macro|IP27C_R10000_ODSC
mdefine_line|#define&t;IP27C_R10000_ODSC(_B)&t;&t;((_B) &lt;&lt; IP27C_R10000_ODSC_SHFT)
DECL|macro|IP27C_R10000_ODSYS_SHFT
mdefine_line|#define&t;IP27C_R10000_ODSYS_SHFT&t;&t;30
DECL|macro|IP27C_R10000_ODSYS_MASK
mdefine_line|#define&t;IP27C_R10000_ODSYS_MASK&t;&t;(1 &lt;&lt; IP27C_R10000_ODSYS_SHFT)
DECL|macro|IP27C_R10000_ODSYS
mdefine_line|#define&t;IP27C_R10000_ODSYS(_B)&t;&t;((_B) &lt;&lt; IP27C_R10000_ODSYS_SHFT)
DECL|macro|IP27C_R10000_CTM_SHFT
mdefine_line|#define&t;IP27C_R10000_CTM_SHFT&t;&t;31
DECL|macro|IP27C_R10000_CTM_MASK
mdefine_line|#define&t;IP27C_R10000_CTM_MASK&t;&t;(1 &lt;&lt; IP27C_R10000_CTM_SHFT)
DECL|macro|IP27C_R10000_CTM
mdefine_line|#define&t;IP27C_R10000_CTM(_B)&t;&t;((_B) &lt;&lt; IP27C_R10000_CTM_SHFT)
DECL|macro|IP27C_MHZ
mdefine_line|#define IP27C_MHZ(x)&t;&t;&t;(1000000 * (x))
DECL|macro|IP27C_KHZ
mdefine_line|#define IP27C_KHZ(x)&t;&t;&t;(1000 * (x))
DECL|macro|IP27C_MB
mdefine_line|#define IP27C_MB(x)&t;&t;&t;((x) &lt;&lt; 20)
multiline_comment|/*&n; * PROM Configurations&n; */
DECL|macro|CONFIG_MAGIC
mdefine_line|#define CONFIG_MAGIC&t;&t;0x69703237636f6e66
multiline_comment|/* The high 32 bits of the &quot;mode bits&quot;.  Bits 7..0 contain one more&n; * than the number of 5ms clocks in the 100ms &quot;long delay&quot; intervals&n; * of the TRex reset sequence.  Bit 8 is the &quot;synergy mode&quot; bit.&n; */
DECL|macro|CONFIG_TIME_CONST
mdefine_line|#define CONFIG_TIME_CONST&t;0x15
DECL|macro|CONFIG_ECC_ENABLE
mdefine_line|#define CONFIG_ECC_ENABLE&t;1
DECL|macro|CONFIG_CHECK_SUM_ADJ
mdefine_line|#define CONFIG_CHECK_SUM_ADJ&t;0
DECL|macro|CONFIG_DEFAULT_FLASH_COUNT
mdefine_line|#define CONFIG_DEFAULT_FLASH_COUNT    0
multiline_comment|/*&n; * Some promICEs have trouble if CONFIG_FPROM_SETUP is too low.&n; * The nominal value for 100 MHz hub is 5, for 200MHz bedrock is 16.&n; * any update to the below should also reflected in the logic in&n; *   IO7prom/flashprom.c function _verify_config_info and _fill_in_config_info&n; */
multiline_comment|/* default junk bus timing values to use */
DECL|macro|CONFIG_SYNERGY_ENABLE
mdefine_line|#define CONFIG_SYNERGY_ENABLE&t;0xff
DECL|macro|CONFIG_SYNERGY_SETUP
mdefine_line|#define CONFIG_SYNERGY_SETUP&t;0xff
DECL|macro|CONFIG_UART_ENABLE
mdefine_line|#define CONFIG_UART_ENABLE&t;0x0c
DECL|macro|CONFIG_UART_SETUP
mdefine_line|#define CONFIG_UART_SETUP&t;0x02
DECL|macro|CONFIG_FPROM_ENABLE
mdefine_line|#define CONFIG_FPROM_ENABLE&t;0x10
DECL|macro|CONFIG_FPROM_SETUP
mdefine_line|#define CONFIG_FPROM_SETUP&t;0x10
DECL|macro|CONFIG_FREQ_RTC
mdefine_line|#define CONFIG_FREQ_RTC&t;IP27C_KHZ(IP27_RTC_FREQ)
macro_line|#if _LANGUAGE_C
multiline_comment|/* we are going to define all the known configs is a table&n; * for building hex images we will pull out the particular&n; * slice we care about by using the IP27_CONFIG_XX_XX as&n; * entries into the table&n; * to keep the table of reasonable size we only include the&n; * values that differ across configurations&n; * please note then that this makes assumptions about what&n; * will and will not change across configurations&n; */
multiline_comment|/* these numbers are as the are ordered in the table below */
DECL|macro|IP27_CONFIG_UNKNOWN
mdefine_line|#define&t;IP27_CONFIG_UNKNOWN -1
DECL|macro|IP27_CONFIG_SN1_1MB_200_400_200_TABLE
mdefine_line|#define IP27_CONFIG_SN1_1MB_200_400_200_TABLE 0
DECL|macro|IP27_CONFIG_SN00_4MB_100_200_133_TABLE
mdefine_line|#define IP27_CONFIG_SN00_4MB_100_200_133_TABLE 1
DECL|macro|IP27_CONFIG_SN1_4MB_200_400_267_TABLE
mdefine_line|#define IP27_CONFIG_SN1_4MB_200_400_267_TABLE 2
DECL|macro|IP27_CONFIG_SN1_8MB_200_500_250_TABLE
mdefine_line|#define IP27_CONFIG_SN1_8MB_200_500_250_TABLE 3
DECL|macro|IP27_CONFIG_SN1_8MB_200_400_267_TABLE
mdefine_line|#define IP27_CONFIG_SN1_8MB_200_400_267_TABLE 4
DECL|macro|IP27_CONFIG_SN1_4MB_180_360_240_TABLE
mdefine_line|#define IP27_CONFIG_SN1_4MB_180_360_240_TABLE 5
DECL|macro|NUMB_IP_CONFIGS
mdefine_line|#define NUMB_IP_CONFIGS 6
macro_line|#ifdef DEF_IP_CONFIG_TABLE
multiline_comment|/*&n; * N.B.: A new entry needs to be added here everytime a new config is added&n; * The table is indexed by the PIMM PSC value&n; */
DECL|variable|psc_to_flash_config
r_static
r_int
id|psc_to_flash_config
(braket
)braket
op_assign
(brace
id|IP27_CONFIG_SN1_4MB_200_400_267_TABLE
comma
multiline_comment|/* 0x0 */
id|IP27_CONFIG_SN1_8MB_200_500_250_TABLE
comma
multiline_comment|/* 0x1 */
id|IP27_CONFIG_SN1_8MB_200_400_267_TABLE
comma
multiline_comment|/* 0x2 */
id|IP27_CONFIG_UNKNOWN
comma
multiline_comment|/* 0x3 */
id|IP27_CONFIG_UNKNOWN
comma
multiline_comment|/* 0x4 */
id|IP27_CONFIG_UNKNOWN
comma
multiline_comment|/* 0x5 */
id|IP27_CONFIG_UNKNOWN
comma
multiline_comment|/* 0x6 */
id|IP27_CONFIG_UNKNOWN
comma
multiline_comment|/* 0x7 */
id|IP27_CONFIG_SN1_4MB_180_360_240_TABLE
comma
multiline_comment|/* 0x8 */
id|IP27_CONFIG_UNKNOWN
comma
multiline_comment|/* 0x9 */
id|IP27_CONFIG_UNKNOWN
comma
multiline_comment|/* 0xa */
id|IP27_CONFIG_UNKNOWN
comma
multiline_comment|/* 0xb */
id|IP27_CONFIG_UNKNOWN
comma
multiline_comment|/* 0xc */
id|IP27_CONFIG_UNKNOWN
comma
multiline_comment|/* 0xd */
id|IP27_CONFIG_SN00_4MB_100_200_133_TABLE
comma
multiline_comment|/* 0xe  O200 PIMM for bringup */
id|IP27_CONFIG_UNKNOWN
multiline_comment|/* 0xf == PIMM not installed */
)brace
suffix:semicolon
DECL|variable|ip_config_table
r_static
id|config_modifiable_t
id|ip_config_table
(braket
id|NUMB_IP_CONFIGS
)braket
op_assign
(brace
multiline_comment|/* the 1MB_200_400_200 values (Generic settings, will work for any config.) */
(brace
(paren
id|IP27C_R10000_KSEG0CA
c_func
(paren
l_int|5
)paren
op_plus
"&bslash;"
id|IP27C_R10000_DEVNUM
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_CPRT
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_PER
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_PRM
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCD
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCBS
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCE
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ME
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCS
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCD
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCT
c_func
(paren
l_int|9
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ODSC
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ODSYS
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_CTM
c_func
(paren
l_int|0
)paren
)paren
comma
id|IP27C_MHZ
c_func
(paren
l_int|400
)paren
comma
id|IP27C_MHZ
c_func
(paren
l_int|200
)paren
comma
id|CONFIG_FPROM_SETUP
comma
id|SN1_MACH_TYPE
comma
id|CONFIG_FPROM_ENABLE
)brace
comma
multiline_comment|/* the 4MB_100_200_133 values (O200 PIMM w/translation board, PSC 0xe)&n; * (SysAD at 100MHz (SCD=3), and bedrock core at 200 MHz) */
(brace
multiline_comment|/* ODSYS == 0 means HSTL1 on SysAD bus; other PIMMs use HSTL2 */
(paren
id|IP27C_R10000_KSEG0CA
c_func
(paren
l_int|5
)paren
op_plus
"&bslash;"
id|IP27C_R10000_DEVNUM
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_CPRT
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_PER
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_PRM
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCD
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCBS
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCE
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ME
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCS
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCD
c_func
(paren
l_int|2
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCT
c_func
(paren
l_int|9
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ODSC
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ODSYS
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_CTM
c_func
(paren
l_int|0
)paren
)paren
comma
id|IP27C_MHZ
c_func
(paren
l_int|200
)paren
comma
id|IP27C_MHZ
c_func
(paren
l_int|200
)paren
comma
id|CONFIG_FPROM_SETUP
comma
id|SN1_MACH_TYPE
comma
id|CONFIG_FPROM_ENABLE
)brace
comma
multiline_comment|/* 4MB_200_400_267 values (R12KS, 3.7ns, LWR, 030-1602-001, PSC 0x0) */
(brace
(paren
id|IP27C_R10000_KSEG0CA
c_func
(paren
l_int|5
)paren
op_plus
"&bslash;"
id|IP27C_R10000_DEVNUM
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_CPRT
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_PER
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_PRM
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCD
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCBS
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCE
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ME
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCS
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCD
c_func
(paren
l_int|2
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCT
c_func
(paren
l_int|0xa
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ODSC
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ODSYS
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_CTM
c_func
(paren
l_int|0
)paren
)paren
comma
id|IP27C_MHZ
c_func
(paren
l_int|400
)paren
comma
id|IP27C_MHZ
c_func
(paren
l_int|200
)paren
comma
id|CONFIG_FPROM_SETUP
comma
id|SN1_MACH_TYPE
comma
id|CONFIG_FPROM_ENABLE
)brace
comma
multiline_comment|/* 8MB_200_500_250 values (R14K, 4.0ns, DDR1, 030-1520-001, PSC 0x1) */
(brace
(paren
id|IP27C_R10000_KSEG0CA
c_func
(paren
l_int|5
)paren
op_plus
"&bslash;"
id|IP27C_R10000_DEVNUM
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_CPRT
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_PER
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_PRM
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCD
c_func
(paren
l_int|4
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCBS
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCE
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ME
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCS
c_func
(paren
l_int|4
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCD
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCT
c_func
(paren
l_int|0xa
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ODSC
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ODSYS
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_CTM
c_func
(paren
l_int|0
)paren
)paren
comma
id|IP27C_MHZ
c_func
(paren
l_int|500
)paren
comma
id|IP27C_MHZ
c_func
(paren
l_int|200
)paren
comma
id|CONFIG_FPROM_SETUP
comma
id|SN1_MACH_TYPE
comma
id|CONFIG_FPROM_ENABLE
)brace
comma
multiline_comment|/* 8MB_200_400_267 values (R12KS, 3.7ns, LWR, 030-1616-001, PSC 0x2) */
(brace
(paren
id|IP27C_R10000_KSEG0CA
c_func
(paren
l_int|5
)paren
op_plus
"&bslash;"
id|IP27C_R10000_DEVNUM
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_CPRT
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_PER
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_PRM
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCD
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCBS
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCE
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ME
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCS
c_func
(paren
l_int|4
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCD
c_func
(paren
l_int|2
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCT
c_func
(paren
l_int|0xa
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ODSC
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ODSYS
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_CTM
c_func
(paren
l_int|0
)paren
)paren
comma
id|IP27C_MHZ
c_func
(paren
l_int|400
)paren
comma
id|IP27C_MHZ
c_func
(paren
l_int|200
)paren
comma
id|CONFIG_FPROM_SETUP
comma
id|SN1_MACH_TYPE
comma
id|CONFIG_FPROM_ENABLE
)brace
comma
multiline_comment|/* 4MB_180_360_240 values (R12KS, 3.7ns, LWR, 030-1627-001, PSC 0x8)&n; * (SysAD at 180 MHz (SCD=3, the fastest possible), bedrock core at 200MHz) */
(brace
(paren
id|IP27C_R10000_KSEG0CA
c_func
(paren
l_int|5
)paren
op_plus
"&bslash;"
id|IP27C_R10000_DEVNUM
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_CPRT
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_PER
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_PRM
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCD
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCBS
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCE
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ME
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCS
c_func
(paren
l_int|3
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCD
c_func
(paren
l_int|2
)paren
op_plus
"&bslash;"
id|IP27C_R10000_SCCT
c_func
(paren
l_int|9
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ODSC
c_func
(paren
l_int|0
)paren
op_plus
"&bslash;"
id|IP27C_R10000_ODSYS
c_func
(paren
l_int|1
)paren
op_plus
"&bslash;"
id|IP27C_R10000_CTM
c_func
(paren
l_int|0
)paren
)paren
comma
id|IP27C_MHZ
c_func
(paren
l_int|360
)paren
comma
id|IP27C_MHZ
c_func
(paren
l_int|200
)paren
comma
id|CONFIG_FPROM_SETUP
comma
id|SN1_MACH_TYPE
comma
id|CONFIG_FPROM_ENABLE
)brace
comma
)brace
suffix:semicolon
macro_line|#else
r_extern
id|config_modifiable_t
id|ip_config_table
(braket
)braket
suffix:semicolon
macro_line|#endif /* DEF_IP27_CONFIG_TABLE */
macro_line|#ifdef IP27_CONFIG_SN00_4MB_100_200_133
DECL|macro|CONFIG_CPU_MODE
mdefine_line|#define CONFIG_CPU_MODE&t;ip_config_table[IP27_CONFIG_SN00_4MB_100_200_133_TABLE].r10k_mode
DECL|macro|CONFIG_FREQ_CPU
mdefine_line|#define CONFIG_FREQ_CPU&t;ip_config_table[IP27_CONFIG_SN00_4MB_100_200_133_TABLE].freq_cpu
DECL|macro|CONFIG_FREQ_HUB
mdefine_line|#define CONFIG_FREQ_HUB&t;ip_config_table[IP27_CONFIG_SN00_4MB_100_200_133_TABLE].freq_hub
DECL|macro|CONFIG_FPROM_CYC
mdefine_line|#define CONFIG_FPROM_CYC ip_config_table[IP27_CONFIG_SN00_4MB_100_200_133_TABLE].fprom_cyc
DECL|macro|CONFIG_MACH_TYPE
mdefine_line|#define CONFIG_MACH_TYPE ip_config_table[IP27_CONFIG_SN00_4MB_100_200_133_TABLE].mach_type
DECL|macro|CONFIG_FPROM_WR
mdefine_line|#define CONFIG_FPROM_WR&t;ip_config_table[IP27_CONFIG_SN00_4MB_100_200_133_TABLE].fprom_wr
macro_line|#endif /* IP27_CONFIG_SN00_4MB_100_200_133 */
macro_line|#ifdef IP27_CONFIG_SN1_1MB_200_400_200
DECL|macro|CONFIG_CPU_MODE
mdefine_line|#define CONFIG_CPU_MODE&t;ip_config_table[IP27_CONFIG_SN1_1MB_200_400_200_TABLE].r10k_mode
DECL|macro|CONFIG_FREQ_CPU
mdefine_line|#define CONFIG_FREQ_CPU&t;ip_config_table[IP27_CONFIG_SN1_1MB_200_400_200_TABLE].freq_cpu
DECL|macro|CONFIG_FREQ_HUB
mdefine_line|#define CONFIG_FREQ_HUB&t;ip_config_table[IP27_CONFIG_SN1_1MB_200_400_200_TABLE].freq_hub
DECL|macro|CONFIG_FPROM_CYC
mdefine_line|#define CONFIG_FPROM_CYC ip_config_table[IP27_CONFIG_SN1_1MB_200_400_200_TABLE].fprom_cyc
DECL|macro|CONFIG_MACH_TYPE
mdefine_line|#define CONFIG_MACH_TYPE ip_config_table[IP27_CONFIG_SN1_1MB_200_400_200_TABLE].mach_type
DECL|macro|CONFIG_FPROM_WR
mdefine_line|#define CONFIG_FPROM_WR&t;ip_config_table[IP27_CONFIG_SN1_1MB_200_400_200_TABLE].fprom_wr
macro_line|#endif /* IP27_CONFIG_SN1_1MB_200_400_200 */
macro_line|#ifdef IP27_CONFIG_SN1_4MB_200_400_267
DECL|macro|CONFIG_CPU_MODE
mdefine_line|#define CONFIG_CPU_MODE&t;ip_config_table[IP27_CONFIG_SN1_4MB_200_400_267_TABLE].r10k_mode
DECL|macro|CONFIG_FREQ_CPU
mdefine_line|#define CONFIG_FREQ_CPU&t;ip_config_table[IP27_CONFIG_SN1_4MB_200_400_267_TABLE].freq_cpu
DECL|macro|CONFIG_FREQ_HUB
mdefine_line|#define CONFIG_FREQ_HUB&t;ip_config_table[IP27_CONFIG_SN1_4MB_200_400_267_TABLE].freq_hub
DECL|macro|CONFIG_FPROM_CYC
mdefine_line|#define CONFIG_FPROM_CYC ip_config_table[IP27_CONFIG_SN1_4MB_200_400_267_TABLE].fprom_cyc
DECL|macro|CONFIG_MACH_TYPE
mdefine_line|#define CONFIG_MACH_TYPE ip_config_table[IP27_CONFIG_SN1_4MB_200_400_267_TABLE].mach_type
DECL|macro|CONFIG_FPROM_WR
mdefine_line|#define CONFIG_FPROM_WR&t;ip_config_table[IP27_CONFIG_SN1_4MB_200_400_267_TABLE].fprom_wr
macro_line|#endif /* IP27_CONFIG_SN1_4MB_200_400_267 */
macro_line|#ifdef IP27_CONFIG_SN1_8MB_200_500_250
DECL|macro|CONFIG_CPU_MODE
mdefine_line|#define CONFIG_CPU_MODE&t;ip_config_table[IP27_CONFIG_SN1_8MB_200_500_250_TABLE].r10k_mode
DECL|macro|CONFIG_FREQ_CPU
mdefine_line|#define CONFIG_FREQ_CPU&t;ip_config_table[IP27_CONFIG_SN1_8MB_200_500_250_TABLE].freq_cpu
DECL|macro|CONFIG_FREQ_HUB
mdefine_line|#define CONFIG_FREQ_HUB&t;ip_config_table[IP27_CONFIG_SN1_8MB_200_500_250_TABLE].freq_hub
DECL|macro|CONFIG_FPROM_CYC
mdefine_line|#define CONFIG_FPROM_CYC ip_config_table[IP27_CONFIG_SN1_8MB_200_500_250_TABLE].fprom_cyc
DECL|macro|CONFIG_MACH_TYPE
mdefine_line|#define CONFIG_MACH_TYPE ip_config_table[IP27_CONFIG_SN1_8MB_200_500_250_TABLE].mach_type
DECL|macro|CONFIG_FPROM_WR
mdefine_line|#define CONFIG_FPROM_WR&t;ip_config_table[IP27_CONFIG_SN1_8MB_200_500_250_TABLE].fprom_wr
macro_line|#endif /* IP27_CONFIG_SN1_8MB_200_500_250 */
macro_line|#ifdef IP27_CONFIG_SN1_8MB_200_400_267
DECL|macro|CONFIG_CPU_MODE
mdefine_line|#define CONFIG_CPU_MODE&t;ip_config_table[IP27_CONFIG_SN1_8MB_200_400_267_TABLE].r10k_mode
DECL|macro|CONFIG_FREQ_CPU
mdefine_line|#define CONFIG_FREQ_CPU&t;ip_config_table[IP27_CONFIG_SN1_8MB_200_400_267_TABLE].freq_cpu
DECL|macro|CONFIG_FREQ_HUB
mdefine_line|#define CONFIG_FREQ_HUB&t;ip_config_table[IP27_CONFIG_SN1_8MB_200_400_267_TABLE].freq_hub
DECL|macro|CONFIG_FPROM_CYC
mdefine_line|#define CONFIG_FPROM_CYC ip_config_table[IP27_CONFIG_SN1_8MB_200_400_267_TABLE].fprom_cyc
DECL|macro|CONFIG_MACH_TYPE
mdefine_line|#define CONFIG_MACH_TYPE ip_config_table[IP27_CONFIG_SN1_8MB_200_400_267_TABLE].mach_type
DECL|macro|CONFIG_FPROM_WR
mdefine_line|#define CONFIG_FPROM_WR&t;ip_config_table[IP27_CONFIG_SN1_8MB_200_400_267_TABLE].fprom_wr
macro_line|#endif /* IP27_CONFIG_SN1_8MB_200_400_267 */
macro_line|#ifdef IP27_CONFIG_SN1_4MB_180_360_240
DECL|macro|CONFIG_CPU_MODE
mdefine_line|#define CONFIG_CPU_MODE&t;ip_config_table[IP27_CONFIG_SN1_4MB_180_360_240_TABLE].r10k_mode
DECL|macro|CONFIG_FREQ_CPU
mdefine_line|#define CONFIG_FREQ_CPU&t;ip_config_table[IP27_CONFIG_SN1_4MB_180_360_240_TABLE].freq_cpu
DECL|macro|CONFIG_FREQ_HUB
mdefine_line|#define CONFIG_FREQ_HUB&t;ip_config_table[IP27_CONFIG_SN1_4MB_180_360_240_TABLE].freq_hub
DECL|macro|CONFIG_FPROM_CYC
mdefine_line|#define CONFIG_FPROM_CYC ip_config_table[IP27_CONFIG_SN1_4MB_180_360_240_TABLE].fprom_cyc
DECL|macro|CONFIG_MACH_TYPE
mdefine_line|#define CONFIG_MACH_TYPE ip_config_table[IP27_CONFIG_SN1_4MB_180_360_240_TABLE].mach_type
DECL|macro|CONFIG_FPROM_WR
mdefine_line|#define CONFIG_FPROM_WR&t;ip_config_table[IP27_CONFIG_SN1_4MB_180_360_240_TABLE].fprom_wr
macro_line|#endif /* IP27_CONFIG_SN1_4MB_180_360_240 */
macro_line|#endif /* _LANGUAGE_C */
macro_line|#if _LANGUAGE_ASSEMBLY
multiline_comment|/* these need to be in here since we need assembly definitions&n; * for building hex images (as required by start.s)&n; */
macro_line|#ifdef IP27_CONFIG_SN00_4MB_100_200_133
macro_line|#ifdef IRIX
multiline_comment|/* Set PrcReqMax to 0 to reduce memory problems */
DECL|macro|BRINGUP_PRM_VAL
mdefine_line|#define&t;BRINGUP_PRM_VAL&t;0
macro_line|#else
DECL|macro|BRINGUP_PRM_VAL
mdefine_line|#define&t;BRINGUP_PRM_VAL&t;3
macro_line|#endif
DECL|macro|CONFIG_CPU_MODE
mdefine_line|#define CONFIG_CPU_MODE &bslash;&n;&t;(IP27C_R10000_KSEG0CA(5) + &bslash;&n;&t; IP27C_R10000_DEVNUM(0)&t; + &bslash;&n;&t; IP27C_R10000_CPRT(0)&t; + &bslash;&n;&t; IP27C_R10000_PER(0)&t; + &bslash;&n;&t; IP27C_R10000_PRM(BRINGUP_PRM_VAL)&t; + &bslash;&n;&t; IP27C_R10000_SCD(3)&t; + &bslash;&n;&t; IP27C_R10000_SCBS(1)&t; + &bslash;&n;&t; IP27C_R10000_SCCE(0)&t; + &bslash;&n;&t; IP27C_R10000_ME(1)&t; + &bslash;&n;&t; IP27C_R10000_SCS(3)&t; + &bslash;&n;&t; IP27C_R10000_SCCD(2)&t; + &bslash;&n;&t; IP27C_R10000_SCCT(9)&t; + &bslash;&n;&t; IP27C_R10000_ODSC(0)&t; + &bslash;&n;&t; IP27C_R10000_ODSYS(0)&t; + &bslash;&n;&t; IP27C_R10000_CTM(0))
DECL|macro|CONFIG_FREQ_CPU
mdefine_line|#define CONFIG_FREQ_CPU IP27C_MHZ(200)
DECL|macro|CONFIG_FREQ_HUB
mdefine_line|#define CONFIG_FREQ_HUB IP27C_MHZ(200)
DECL|macro|CONFIG_FPROM_CYC
mdefine_line|#define CONFIG_FPROM_CYC CONFIG_FPROM_SETUP
DECL|macro|CONFIG_MACH_TYPE
mdefine_line|#define CONFIG_MACH_TYPE SN1_MACH_TYPE
DECL|macro|CONFIG_FPROM_WR
mdefine_line|#define CONFIG_FPROM_WR CONFIG_FPROM_ENABLE
macro_line|#endif /* IP27_CONFIG_SN00_4MB_100_200_133 */
macro_line|#ifdef IP27_CONFIG_SN1_1MB_200_400_200
DECL|macro|CONFIG_CPU_MODE
mdefine_line|#define CONFIG_CPU_MODE &bslash;&n;&t;(IP27C_R10000_KSEG0CA(5) + &bslash;&n;&t; IP27C_R10000_DEVNUM(0)&t; + &bslash;&n;&t; IP27C_R10000_CPRT(0)&t; + &bslash;&n;&t; IP27C_R10000_PER(0)&t; + &bslash;&n;&t; IP27C_R10000_PRM(3)&t; + &bslash;&n;&t; IP27C_R10000_SCD(3)&t; + &bslash;&n;&t; IP27C_R10000_SCBS(1)&t; + &bslash;&n;&t; IP27C_R10000_SCCE(0)&t; + &bslash;&n;&t; IP27C_R10000_ME(1)&t; + &bslash;&n;&t; IP27C_R10000_SCS(1)&t; + &bslash;&n;&t; IP27C_R10000_SCCD(3)&t; + &bslash;&n;&t; IP27C_R10000_SCCT(9)&t; + &bslash;&n;&t; IP27C_R10000_ODSC(0)&t; + &bslash;&n;&t; IP27C_R10000_ODSYS(1)&t; + &bslash;&n;&t; IP27C_R10000_CTM(0))
DECL|macro|CONFIG_FREQ_CPU
mdefine_line|#define CONFIG_FREQ_CPU IP27C_MHZ(400)
DECL|macro|CONFIG_FREQ_HUB
mdefine_line|#define CONFIG_FREQ_HUB IP27C_MHZ(200)
DECL|macro|CONFIG_FPROM_CYC
mdefine_line|#define CONFIG_FPROM_CYC CONFIG_FPROM_SETUP
DECL|macro|CONFIG_MACH_TYPE
mdefine_line|#define CONFIG_MACH_TYPE SN1_MACH_TYPE
DECL|macro|CONFIG_FPROM_WR
mdefine_line|#define CONFIG_FPROM_WR CONFIG_FPROM_ENABLE
macro_line|#endif /* IP27_CONFIG_SN1_1MB_200_400_200 */
macro_line|#ifdef IP27_CONFIG_SN1_4MB_200_400_267
DECL|macro|CONFIG_CPU_MODE
mdefine_line|#define CONFIG_CPU_MODE &bslash;&n;&t;(IP27C_R10000_KSEG0CA(5) + &bslash;&n;&t; IP27C_R10000_DEVNUM(0)&t; + &bslash;&n;&t; IP27C_R10000_CPRT(0)&t; + &bslash;&n;&t; IP27C_R10000_PER(0)&t; + &bslash;&n;&t; IP27C_R10000_PRM(3)&t; + &bslash;&n;&t; IP27C_R10000_SCD(3)&t; + &bslash;&n;&t; IP27C_R10000_SCBS(1)&t; + &bslash;&n;&t; IP27C_R10000_SCCE(0)&t; + &bslash;&n;&t; IP27C_R10000_ME(1)&t; + &bslash;&n;&t; IP27C_R10000_SCS(3)&t; + &bslash;&n;&t; IP27C_R10000_SCCD(2)&t; + &bslash;&n;&t; IP27C_R10000_SCCT(0xa)&t; + &bslash;&n;&t; IP27C_R10000_ODSC(0)&t; + &bslash;&n;&t; IP27C_R10000_ODSYS(1)&t; + &bslash;&n;&t; IP27C_R10000_CTM(0))
DECL|macro|CONFIG_FREQ_CPU
mdefine_line|#define CONFIG_FREQ_CPU IP27C_MHZ(400)
DECL|macro|CONFIG_FREQ_HUB
mdefine_line|#define CONFIG_FREQ_HUB IP27C_MHZ(200)
DECL|macro|CONFIG_FPROM_CYC
mdefine_line|#define CONFIG_FPROM_CYC CONFIG_FPROM_SETUP
DECL|macro|CONFIG_MACH_TYPE
mdefine_line|#define CONFIG_MACH_TYPE SN1_MACH_TYPE
DECL|macro|CONFIG_FPROM_WR
mdefine_line|#define CONFIG_FPROM_WR CONFIG_FPROM_ENABLE
macro_line|#endif /* IP27_CONFIG_SN1_4MB_200_400_267 */
macro_line|#ifdef IP27_CONFIG_SN1_8MB_200_500_250
DECL|macro|CONFIG_CPU_MODE
mdefine_line|#define CONFIG_CPU_MODE &bslash;&n;&t;(IP27C_R10000_KSEG0CA(5) + &bslash;&n;&t; IP27C_R10000_DEVNUM(0)&t; + &bslash;&n;&t; IP27C_R10000_CPRT(0)&t; + &bslash;&n;&t; IP27C_R10000_PER(0)&t; + &bslash;&n;&t; IP27C_R10000_PRM(3)&t; + &bslash;&n;&t; IP27C_R10000_SCD(4)&t; + &bslash;&n;&t; IP27C_R10000_SCBS(1)&t; + &bslash;&n;&t; IP27C_R10000_SCCE(0)&t; + &bslash;&n;&t; IP27C_R10000_ME(1)&t; + &bslash;&n;&t; IP27C_R10000_SCS(4)&t; + &bslash;&n;&t; IP27C_R10000_SCCD(3)&t; + &bslash;&n;&t; IP27C_R10000_SCCT(0xa)&t; + &bslash;&n;&t; IP27C_R10000_ODSC(0)&t; + &bslash;&n;&t; IP27C_R10000_ODSYS(1)&t; + &bslash;&n;&t; IP27C_R10000_CTM(0))
DECL|macro|CONFIG_FREQ_CPU
mdefine_line|#define CONFIG_FREQ_CPU IP27C_MHZ(500)
DECL|macro|CONFIG_FREQ_HUB
mdefine_line|#define CONFIG_FREQ_HUB IP27C_MHZ(200)
DECL|macro|CONFIG_FPROM_CYC
mdefine_line|#define CONFIG_FPROM_CYC CONFIG_FPROM_SETUP
DECL|macro|CONFIG_MACH_TYPE
mdefine_line|#define CONFIG_MACH_TYPE SN1_MACH_TYPE
DECL|macro|CONFIG_FPROM_WR
mdefine_line|#define CONFIG_FPROM_WR CONFIG_FPROM_ENABLE
macro_line|#endif /* IP27_CONFIG_SN1_8MB_200_500_250 */
macro_line|#ifdef IP27_CONFIG_SN1_8MB_200_400_267
DECL|macro|CONFIG_CPU_MODE
mdefine_line|#define CONFIG_CPU_MODE &bslash;&n;&t;(IP27C_R10000_KSEG0CA(5) + &bslash;&n;&t; IP27C_R10000_DEVNUM(0)&t; + &bslash;&n;&t; IP27C_R10000_CPRT(0)&t; + &bslash;&n;&t; IP27C_R10000_PER(0)&t; + &bslash;&n;&t; IP27C_R10000_PRM(3)&t; + &bslash;&n;&t; IP27C_R10000_SCD(3)&t; + &bslash;&n;&t; IP27C_R10000_SCBS(1)&t; + &bslash;&n;&t; IP27C_R10000_SCCE(0)&t; + &bslash;&n;&t; IP27C_R10000_ME(1)&t; + &bslash;&n;&t; IP27C_R10000_SCS(4)&t; + &bslash;&n;&t; IP27C_R10000_SCCD(2)&t; + &bslash;&n;&t; IP27C_R10000_SCCT(0xa)&t; + &bslash;&n;&t; IP27C_R10000_ODSC(0)&t; + &bslash;&n;&t; IP27C_R10000_ODSYS(1)&t; + &bslash;&n;&t; IP27C_R10000_CTM(0))
DECL|macro|CONFIG_FREQ_CPU
mdefine_line|#define CONFIG_FREQ_CPU IP27C_MHZ(400)
DECL|macro|CONFIG_FREQ_HUB
mdefine_line|#define CONFIG_FREQ_HUB IP27C_MHZ(200)
DECL|macro|CONFIG_FPROM_CYC
mdefine_line|#define CONFIG_FPROM_CYC CONFIG_FPROM_SETUP
DECL|macro|CONFIG_MACH_TYPE
mdefine_line|#define CONFIG_MACH_TYPE SN1_MACH_TYPE
DECL|macro|CONFIG_FPROM_WR
mdefine_line|#define CONFIG_FPROM_WR CONFIG_FPROM_ENABLE
macro_line|#endif /* IP27_CONFIG_SN1_8MB_200_400_267 */
macro_line|#ifdef IP27_CONFIG_SN1_4MB_180_360_240
DECL|macro|CONFIG_CPU_MODE
mdefine_line|#define CONFIG_CPU_MODE &bslash;&n;&t;(IP27C_R10000_KSEG0CA(5) + &bslash;&n;&t; IP27C_R10000_DEVNUM(0)&t; + &bslash;&n;&t; IP27C_R10000_CPRT(0)&t; + &bslash;&n;&t; IP27C_R10000_PER(0)&t; + &bslash;&n;&t; IP27C_R10000_PRM(3)&t; + &bslash;&n;&t; IP27C_R10000_SCD(3)&t; + &bslash;&n;&t; IP27C_R10000_SCBS(1)&t; + &bslash;&n;&t; IP27C_R10000_SCCE(0)&t; + &bslash;&n;&t; IP27C_R10000_ME(1)&t; + &bslash;&n;&t; IP27C_R10000_SCS(3)&t; + &bslash;&n;&t; IP27C_R10000_SCCD(2)&t; + &bslash;&n;&t; IP27C_R10000_SCCT(9)&t; + &bslash;&n;&t; IP27C_R10000_ODSC(0)&t; + &bslash;&n;&t; IP27C_R10000_ODSYS(1)&t; + &bslash;&n;&t; IP27C_R10000_CTM(0))
DECL|macro|CONFIG_FREQ_CPU
mdefine_line|#define CONFIG_FREQ_CPU IP27C_MHZ(360)
DECL|macro|CONFIG_FREQ_HUB
mdefine_line|#define CONFIG_FREQ_HUB IP27C_MHZ(200)
DECL|macro|CONFIG_FPROM_CYC
mdefine_line|#define CONFIG_FPROM_CYC CONFIG_FPROM_SETUP
DECL|macro|CONFIG_MACH_TYPE
mdefine_line|#define CONFIG_MACH_TYPE SN1_MACH_TYPE
DECL|macro|CONFIG_FPROM_WR
mdefine_line|#define CONFIG_FPROM_WR CONFIG_FPROM_ENABLE
macro_line|#endif /* IP27_CONFIG_SN1_4MB_180_360_240 */
macro_line|#endif /* _LANGUAGE_C */
macro_line|#endif /* _ASM_SN_SN1_IP27CONFIG_H */
eof
