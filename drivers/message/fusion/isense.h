macro_line|#ifndef ISENSE_H_INCLUDED
DECL|macro|ISENSE_H_INCLUDED
mdefine_line|#define ISENSE_H_INCLUDED
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;&t;&t;/* needed for u8, etc. */
macro_line|#include &lt;linux/string.h&gt;&t;&t;/* needed for strcat   */
macro_line|#include &lt;linux/kernel.h&gt;&t;&t;/* needed for sprintf  */
macro_line|#else
macro_line|#ifndef U_STUFF_DEFINED
DECL|macro|U_STUFF_DEFINED
mdefine_line|#define U_STUFF_DEFINED
DECL|typedef|u8
r_typedef
r_int
r_char
id|u8
suffix:semicolon
DECL|typedef|u16
r_typedef
r_int
r_int
id|u16
suffix:semicolon
DECL|typedef|u32
r_typedef
r_int
r_int
id|u32
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#include &quot;scsi3.h&quot;&t;&t;&t;/* needed for all things SCSI */
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *  Defines and typedefs...&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|PrintF
mdefine_line|#define PrintF(x) printk x
macro_line|#else
DECL|macro|PrintF
mdefine_line|#define PrintF(x) printf x
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
DECL|macro|RETRY_STATUS
mdefine_line|#define RETRY_STATUS  ((int) 1)
DECL|macro|PUT_STATUS
mdefine_line|#define PUT_STATUS    ((int) 0)
multiline_comment|/*&n; *    A generic structure to hold info about IO request that caused&n; *    a Request Sense to be performed, and the resulting Sense Data.&n; */
DECL|struct|IO_Info
r_typedef
r_struct
id|IO_Info
(brace
DECL|member|DevIDStr
r_char
op_star
id|DevIDStr
suffix:semicolon
multiline_comment|/* String of chars which identifies the device.       */
DECL|member|cdbPtr
id|u8
op_star
id|cdbPtr
suffix:semicolon
multiline_comment|/* Pointer (Virtual/Logical addr) to CDB bytes of&n;                           IO request that caused ContAllegianceCond.       */
DECL|member|sensePtr
id|u8
op_star
id|sensePtr
suffix:semicolon
multiline_comment|/* Pointer (Virtual/Logical addr) to Sense Data&n;                           returned by Request Sense operation.             */
DECL|member|dataPtr
id|u8
op_star
id|dataPtr
suffix:semicolon
multiline_comment|/* Pointer (Virtual/Logical addr) to Data buffer&n;                           of IO request caused ContAllegianceCondition.    */
DECL|member|inqPtr
id|u8
op_star
id|inqPtr
suffix:semicolon
multiline_comment|/* Pointer (Virtual/Logical addr) to Inquiry Data for&n;                           IO *Device* that caused ContAllegianceCondition. */
DECL|member|SCSIStatus
id|u8
id|SCSIStatus
suffix:semicolon
multiline_comment|/* SCSI status byte of IO request that caused&n;                           Contingent Allegiance Condition.                 */
DECL|member|DoDisplay
id|u8
id|DoDisplay
suffix:semicolon
multiline_comment|/* Shall we display any messages?                     */
DECL|member|rsvd_align1
id|u16
id|rsvd_align1
suffix:semicolon
DECL|member|ComplCode
id|u32
id|ComplCode
suffix:semicolon
multiline_comment|/* Four-byte OS-dependent completion code.            */
DECL|member|NotifyL
id|u32
id|NotifyL
suffix:semicolon
multiline_comment|/* Four-byte OS-dependent notification field.         */
DECL|typedef|IO_Info_t
)brace
id|IO_Info_t
suffix:semicolon
multiline_comment|/*&n; *  SCSI Additional Sense Code and Additional Sense Code Qualifier table.&n; */
DECL|struct|ASCQ_Table
r_typedef
r_struct
id|ASCQ_Table
(brace
DECL|member|ASC
id|u8
id|ASC
suffix:semicolon
DECL|member|ASCQ
id|u8
id|ASCQ
suffix:semicolon
DECL|member|DevTypes
r_char
op_star
id|DevTypes
suffix:semicolon
DECL|member|Description
r_char
op_star
id|Description
suffix:semicolon
DECL|typedef|ASCQ_Table_t
)brace
id|ASCQ_Table_t
suffix:semicolon
macro_line|#if 0
multiline_comment|/*&n; *  SCSI Opcodes table.&n; */
r_typedef
r_struct
id|SCSI_OPS_Table
(brace
id|u8
id|OpCode
suffix:semicolon
r_char
op_star
id|DevTypes
suffix:semicolon
r_char
op_star
id|ScsiCmndStr
suffix:semicolon
)brace
id|SCSI_OPS_Table_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *  Public entry point prototypes&n; */
multiline_comment|/* in scsiherr.c, needed by mptscsih.c */
r_extern
r_int
id|mpt_ScsiHost_ErrorReport
c_func
(paren
id|IO_Info_t
op_star
id|ioop
)paren
suffix:semicolon
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#endif
eof
