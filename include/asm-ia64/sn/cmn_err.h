multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_CMN_ERR_H
DECL|macro|_ASM_SN_CMN_ERR_H
mdefine_line|#define _ASM_SN_CMN_ERR_H
multiline_comment|/*&n;** Common error handling severity levels.  Converted to be&n;** represented by the associated 4.3BSD syslog priorities.&n;*/
DECL|macro|CE_DEBUG
mdefine_line|#define CE_DEBUG&t;KERN_DEBUG&t;/* debug&t;*/
DECL|macro|CE_CONT
mdefine_line|#define CE_CONT&t;&t;KERN_INFO&t;/* continuation&t;*/
DECL|macro|CE_NOTE
mdefine_line|#define CE_NOTE&t;&t;KERN_NOTICE&t;/* notice&t;*/
DECL|macro|CE_WARN
mdefine_line|#define CE_WARN&t;&t;KERN_WARNING&t;/* warning&t;*/
DECL|macro|CE_ALERT
mdefine_line|#define CE_ALERT&t;KERN_ALERT&t;/* alert&t;*/
DECL|macro|CE_PANIC
mdefine_line|#define CE_PANIC&t;KERN_EMERG&t;/* panic&t;*/
DECL|macro|CE_LEVELMASK
mdefine_line|#define&t;CE_LEVELMASK&t;LOG_PRIMASK&t;/* mask for severity level&t;*/
DECL|macro|CE_CPUID
mdefine_line|#define&t;CE_CPUID&t;0x8&t;&t;/* prepend CPU id to output&t;*/
DECL|macro|CE_PHYSID
mdefine_line|#define CE_PHYSID&t;0x10&t;&t;/* prepend CPU phys location    */
DECL|macro|CE_SYNC
mdefine_line|#define CE_SYNC&t;&t;0x20&t;&t;/* wait for uart to drain before returning */
multiline_comment|/* Flags for Availmon Monitoring&n; * When a developer or&squot;s these bits into the cmn_err flags above,&n; * and they have availmon installed, certain &quot;actions&quot; will take&n; * place depending upon how they have the availmon software configured.&n; */
DECL|macro|CE_TOOKACTIONS
mdefine_line|#define CE_TOOKACTIONS   0x0100            /* Actions taken by some error   */
DECL|macro|CE_RUNNINGPOOR
mdefine_line|#define CE_RUNNINGPOOR   0x0200            /* System running degraded       */
DECL|macro|CE_MAINTENANCE
mdefine_line|#define CE_MAINTENANCE   0x0400            /* System needs maintenance      */
DECL|macro|CE_CONFIGERROR
mdefine_line|#define CE_CONFIGERROR   0x0800            /* System configured incorrectly */
multiline_comment|/* Bitmasks for separating subtasks from priority levels */
DECL|macro|CE_PRIOLEVELMASK
mdefine_line|#define CE_PRIOLEVELMASK 0x00ff  /* bitmask for severity levels of cmn_err */
DECL|macro|CE_SUBTASKMASK
mdefine_line|#define CE_SUBTASKMASK   0xff00  /* bitmask for availmon actions of cmn_err */
DECL|macro|CE_AVAILMONALL
mdefine_line|#define CE_AVAILMONALL   (CE_TOOKACTIONS|CE_RUNNINGPOOR| &bslash;&n;                                 CE_MAINTENANCE|CE_CONFIGERROR)
macro_line|#ifdef __KERNEL__
DECL|macro|CE_PBPANIC
mdefine_line|#define CE_PBPANIC&t;KERN_CRIT&t;/* Special define used to manipulate&n;&t;&t;&t;&t;&t; * putbufndx in kernel */
multiline_comment|/* Console output flushing flag and routine */
r_extern
r_int
id|constrlen
suffix:semicolon
multiline_comment|/* Length of current console string, if zero,&n;&t;&t;&t;&t;   there are no characters to flush */
DECL|macro|CONBUF_LOCKED
mdefine_line|#define&t;CONBUF_LOCKED&t;0&t;/* conbuf is already locked */
DECL|macro|CONBUF_UNLOCKED
mdefine_line|#define&t;CONBUF_UNLOCKED&t;1&t;/* need to reacquire lock */
DECL|macro|CONBUF_DRAIN
mdefine_line|#define CONBUF_DRAIN&t;2&t;/* ensure output before returning */
multiline_comment|/*&n; * bit field descriptions for printf %r and %R formats&n; *&n; * printf(&quot;%r %R&quot;, val, reg_descp);&n; * struct reg_desc *reg_descp;&n; *&n; * the %r and %R formats allow formatted print of bit fields.  individual&n; * bit fields are described by a struct reg_desc, multiple bit fields within&n; * a single word can be described by multiple reg_desc structures.&n; * %r outputs a string of the format &quot;&lt;bit field descriptions&gt;&quot;&n; * %R outputs a string of the format &quot;0x%x&lt;bit field descriptions&gt;&quot;&n; *&n; * The fields in a reg_desc are:&n; *&t;__psunsigned_t rd_mask;&t;An appropriate mask to isolate the bit field&n; *&t;&t;&t;&t;within a word, and&squot;ed with val&n; *&n; *&t;int rd_shift;&t;&t;A shift amount to be done to the isolated&n; *&t;&t;&t;&t;bit field.  done before printing the isolate&n; *&t;&t;&t;&t;bit field with rd_format and before searching&n; *&t;&t;&t;&t;for symbolic value names in rd_values&n; *&n; *&t;char *rd_name;&t;&t;If non-null, a bit field name to label any&n; *&t;&t;&t;&t;out from rd_format or searching rd_values.&n; *&t;&t;&t;&t;if neither rd_format or rd_values is non-null&n; *&t;&t;&t;&t;rd_name is printed only if the isolated&n; *&t;&t;&t;&t;bit field is non-null.&n; *&n; *&t;char *rd_format;&t;If non-null, the shifted bit field value&n; *&t;&t;&t;&t;is printed using this format.&n; *&n; *&t;struct reg_values *rd_values;&t;If non-null, a pointer to a table&n; *&t;&t;&t;&t;matching numeric values with symbolic names.&n; *&t;&t;&t;&t;rd_values are searched and the symbolic&n; *&t;&t;&t;&t;value is printed if a match is found, if no&n; *&t;&t;&t;&t;match is found &quot;???&quot; is printed.&n; *&t;&t;&t;&t;&n; */
multiline_comment|/*&n; * register values&n; * map between numeric values and symbolic values&n; */
DECL|struct|reg_values
r_struct
id|reg_values
(brace
DECL|member|rv_value
id|__psunsigned_t
id|rv_value
suffix:semicolon
DECL|member|rv_name
r_char
op_star
id|rv_name
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * register descriptors are used for formatted prints of register values&n; * rd_mask and rd_shift must be defined, other entries may be null&n; */
DECL|struct|reg_desc
r_struct
id|reg_desc
(brace
DECL|member|rd_mask
id|k_machreg_t
id|rd_mask
suffix:semicolon
multiline_comment|/* mask to extract field */
DECL|member|rd_shift
r_int
id|rd_shift
suffix:semicolon
multiline_comment|/* shift for extracted value, - &gt;&gt;, + &lt;&lt; */
DECL|member|rd_name
r_char
op_star
id|rd_name
suffix:semicolon
multiline_comment|/* field name */
DECL|member|rd_format
r_char
op_star
id|rd_format
suffix:semicolon
multiline_comment|/* format to print field */
DECL|member|rd_values
r_struct
id|reg_values
op_star
id|rd_values
suffix:semicolon
multiline_comment|/* symbolic names of values */
)brace
suffix:semicolon
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* _ASM_SN_CMN_ERR_H */
eof
