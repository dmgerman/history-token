multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; *  linux/openpic.h -- OpenPIC definitions&n; *&n; *  Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This file is based on the following documentation:&n; *&n; *&t;The Open Programmable Interrupt Controller (PIC)&n; *&t;Register Interface Specification Revision 1.2&n; *&n; *&t;Issue Date: October 1995&n; *&n; *&t;Issued jointly by Advanced Micro Devices and Cyrix Corporation&n; *&n; *&t;AMD is a registered trademark of Advanced Micro Devices, Inc.&n; *&t;Copyright (C) 1995, Advanced Micro Devices, Inc. and Cyrix, Inc.&n; *&t;All Rights Reserved.&n; *&n; *  To receive a copy of this documentation, send an email to openpic@amd.com.&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifndef _LINUX_OPENPIC_H
DECL|macro|_LINUX_OPENPIC_H
mdefine_line|#define _LINUX_OPENPIC_H
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n;     *  OpenPIC supports up to 2048 interrupt sources and up to 32 processors&n;     */
DECL|macro|OPENPIC_MAX_SOURCES
mdefine_line|#define OPENPIC_MAX_SOURCES&t;2048
DECL|macro|OPENPIC_MAX_PROCESSORS
mdefine_line|#define OPENPIC_MAX_PROCESSORS&t;32
DECL|macro|OPENPIC_MAX_ISU
mdefine_line|#define OPENPIC_MAX_ISU&t;&t;16
DECL|macro|OPENPIC_NUM_TIMERS
mdefine_line|#define OPENPIC_NUM_TIMERS&t;4
DECL|macro|OPENPIC_NUM_IPI
mdefine_line|#define OPENPIC_NUM_IPI&t;&t;4
DECL|macro|OPENPIC_NUM_PRI
mdefine_line|#define OPENPIC_NUM_PRI&t;&t;16
DECL|macro|OPENPIC_NUM_VECTORS
mdefine_line|#define OPENPIC_NUM_VECTORS&t;256
multiline_comment|/*&n;     *  OpenPIC Registers are 32 bits and aligned on 128 bit boundaries&n;     */
DECL|struct|_OpenPIC_Reg
r_typedef
r_struct
id|_OpenPIC_Reg
(brace
DECL|member|Reg
id|u_int
id|Reg
suffix:semicolon
multiline_comment|/* Little endian! */
DECL|member|Pad
r_char
id|Pad
(braket
l_int|0xc
)braket
suffix:semicolon
DECL|typedef|OpenPIC_Reg
)brace
id|OpenPIC_Reg
suffix:semicolon
multiline_comment|/*&n;     *  Per Processor Registers&n;     */
DECL|struct|_OpenPIC_Processor
r_typedef
r_struct
id|_OpenPIC_Processor
(brace
multiline_comment|/*&n;     *  Private Shadow Registers (for SLiC backwards compatibility)&n;     */
DECL|member|IPI0_Dispatch_Shadow
id|u_int
id|IPI0_Dispatch_Shadow
suffix:semicolon
multiline_comment|/* Write Only */
DECL|member|Pad1
r_char
id|Pad1
(braket
l_int|0x4
)braket
suffix:semicolon
DECL|member|IPI0_Vector_Priority_Shadow
id|u_int
id|IPI0_Vector_Priority_Shadow
suffix:semicolon
multiline_comment|/* Read/Write */
DECL|member|Pad2
r_char
id|Pad2
(braket
l_int|0x34
)braket
suffix:semicolon
multiline_comment|/*&n;     *  Interprocessor Interrupt Command Ports&n;     */
DECL|member|_IPI_Dispatch
id|OpenPIC_Reg
id|_IPI_Dispatch
(braket
id|OPENPIC_NUM_IPI
)braket
suffix:semicolon
multiline_comment|/* Write Only */
multiline_comment|/*&n;     *  Current Task Priority Register&n;     */
DECL|member|_Current_Task_Priority
id|OpenPIC_Reg
id|_Current_Task_Priority
suffix:semicolon
multiline_comment|/* Read/Write */
DECL|member|Pad3
r_char
id|Pad3
(braket
l_int|0x10
)braket
suffix:semicolon
multiline_comment|/*&n;     *  Interrupt Acknowledge Register&n;     */
DECL|member|_Interrupt_Acknowledge
id|OpenPIC_Reg
id|_Interrupt_Acknowledge
suffix:semicolon
multiline_comment|/* Read Only */
multiline_comment|/*&n;     *  End of Interrupt (EOI) Register&n;     */
DECL|member|_EOI
id|OpenPIC_Reg
id|_EOI
suffix:semicolon
multiline_comment|/* Read/Write */
DECL|member|Pad5
r_char
id|Pad5
(braket
l_int|0xf40
)braket
suffix:semicolon
DECL|typedef|OpenPIC_Processor
)brace
id|OpenPIC_Processor
suffix:semicolon
multiline_comment|/*&n;     *  Timer Registers&n;     */
DECL|struct|_OpenPIC_Timer
r_typedef
r_struct
id|_OpenPIC_Timer
(brace
DECL|member|_Current_Count
id|OpenPIC_Reg
id|_Current_Count
suffix:semicolon
multiline_comment|/* Read Only */
DECL|member|_Base_Count
id|OpenPIC_Reg
id|_Base_Count
suffix:semicolon
multiline_comment|/* Read/Write */
DECL|member|_Vector_Priority
id|OpenPIC_Reg
id|_Vector_Priority
suffix:semicolon
multiline_comment|/* Read/Write */
DECL|member|_Destination
id|OpenPIC_Reg
id|_Destination
suffix:semicolon
multiline_comment|/* Read/Write */
DECL|typedef|OpenPIC_Timer
)brace
id|OpenPIC_Timer
suffix:semicolon
multiline_comment|/*&n;     *  Global Registers&n;     */
DECL|struct|_OpenPIC_Global
r_typedef
r_struct
id|_OpenPIC_Global
(brace
multiline_comment|/*&n;     *  Feature Reporting Registers&n;     */
DECL|member|_Feature_Reporting0
id|OpenPIC_Reg
id|_Feature_Reporting0
suffix:semicolon
multiline_comment|/* Read Only */
DECL|member|_Feature_Reporting1
id|OpenPIC_Reg
id|_Feature_Reporting1
suffix:semicolon
multiline_comment|/* Future Expansion */
multiline_comment|/*&n;     *  Global Configuration Registers&n;     */
DECL|member|_Global_Configuration0
id|OpenPIC_Reg
id|_Global_Configuration0
suffix:semicolon
multiline_comment|/* Read/Write */
DECL|member|_Global_Configuration1
id|OpenPIC_Reg
id|_Global_Configuration1
suffix:semicolon
multiline_comment|/* Future Expansion */
multiline_comment|/*&n;     *  Vendor Specific Registers&n;     */
DECL|member|_Vendor_Specific
id|OpenPIC_Reg
id|_Vendor_Specific
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/*&n;     *  Vendor Identification Register&n;     */
DECL|member|_Vendor_Identification
id|OpenPIC_Reg
id|_Vendor_Identification
suffix:semicolon
multiline_comment|/* Read Only */
multiline_comment|/*&n;     *  Processor Initialization Register&n;     */
DECL|member|_Processor_Initialization
id|OpenPIC_Reg
id|_Processor_Initialization
suffix:semicolon
multiline_comment|/* Read/Write */
multiline_comment|/*&n;     *  IPI Vector/Priority Registers&n;     */
DECL|member|_IPI_Vector_Priority
id|OpenPIC_Reg
id|_IPI_Vector_Priority
(braket
id|OPENPIC_NUM_IPI
)braket
suffix:semicolon
multiline_comment|/* Read/Write */
multiline_comment|/*&n;     *  Spurious Vector Register&n;     */
DECL|member|_Spurious_Vector
id|OpenPIC_Reg
id|_Spurious_Vector
suffix:semicolon
multiline_comment|/* Read/Write */
multiline_comment|/*&n;     *  Global Timer Registers&n;     */
DECL|member|_Timer_Frequency
id|OpenPIC_Reg
id|_Timer_Frequency
suffix:semicolon
multiline_comment|/* Read/Write */
DECL|member|Timer
id|OpenPIC_Timer
id|Timer
(braket
id|OPENPIC_NUM_TIMERS
)braket
suffix:semicolon
DECL|member|Pad1
r_char
id|Pad1
(braket
l_int|0xee00
)braket
suffix:semicolon
DECL|typedef|OpenPIC_Global
)brace
id|OpenPIC_Global
suffix:semicolon
multiline_comment|/*&n;     *  Interrupt Source Registers&n;     */
DECL|struct|_OpenPIC_Source
r_typedef
r_struct
id|_OpenPIC_Source
(brace
DECL|member|_Vector_Priority
id|OpenPIC_Reg
id|_Vector_Priority
suffix:semicolon
multiline_comment|/* Read/Write */
DECL|member|_Destination
id|OpenPIC_Reg
id|_Destination
suffix:semicolon
multiline_comment|/* Read/Write */
DECL|typedef|OpenPIC_Source
DECL|typedef|OpenPIC_SourcePtr
)brace
id|OpenPIC_Source
comma
op_star
id|OpenPIC_SourcePtr
suffix:semicolon
multiline_comment|/*&n;     *  OpenPIC Register Map&n;     */
DECL|struct|OpenPIC
r_struct
id|OpenPIC
(brace
DECL|member|Pad1
r_char
id|Pad1
(braket
l_int|0x1000
)braket
suffix:semicolon
multiline_comment|/*&n;     *  Global Registers&n;     */
DECL|member|Global
id|OpenPIC_Global
id|Global
suffix:semicolon
multiline_comment|/*&n;     *  Interrupt Source Configuration Registers&n;     */
DECL|member|Source
id|OpenPIC_Source
id|Source
(braket
id|OPENPIC_MAX_SOURCES
)braket
suffix:semicolon
multiline_comment|/*&n;     *  Per Processor Registers&n;     */
DECL|member|Processor
id|OpenPIC_Processor
id|Processor
(braket
id|OPENPIC_MAX_PROCESSORS
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_volatile
r_struct
id|OpenPIC
op_star
id|OpenPIC
suffix:semicolon
multiline_comment|/*&n;     *  Current Task Priority Register&n;     */
DECL|macro|OPENPIC_CURRENT_TASK_PRIORITY_MASK
mdefine_line|#define OPENPIC_CURRENT_TASK_PRIORITY_MASK&t;0x0000000f
multiline_comment|/*&n;     *  Who Am I Register&n;     */
DECL|macro|OPENPIC_WHO_AM_I_ID_MASK
mdefine_line|#define OPENPIC_WHO_AM_I_ID_MASK&t;&t;0x0000001f
multiline_comment|/*&n;     *  Feature Reporting Register 0&n;     */
DECL|macro|OPENPIC_FEATURE_LAST_SOURCE_MASK
mdefine_line|#define OPENPIC_FEATURE_LAST_SOURCE_MASK&t;0x07ff0000
DECL|macro|OPENPIC_FEATURE_LAST_SOURCE_SHIFT
mdefine_line|#define OPENPIC_FEATURE_LAST_SOURCE_SHIFT&t;16
DECL|macro|OPENPIC_FEATURE_LAST_PROCESSOR_MASK
mdefine_line|#define OPENPIC_FEATURE_LAST_PROCESSOR_MASK&t;0x00001f00
DECL|macro|OPENPIC_FEATURE_LAST_PROCESSOR_SHIFT
mdefine_line|#define OPENPIC_FEATURE_LAST_PROCESSOR_SHIFT&t;8
DECL|macro|OPENPIC_FEATURE_VERSION_MASK
mdefine_line|#define OPENPIC_FEATURE_VERSION_MASK&t;&t;0x000000ff
multiline_comment|/*&n;     *  Global Configuration Register 0&n;     */
DECL|macro|OPENPIC_CONFIG_RESET
mdefine_line|#define OPENPIC_CONFIG_RESET&t;&t;&t;0x80000000
DECL|macro|OPENPIC_CONFIG_8259_PASSTHROUGH_DISABLE
mdefine_line|#define OPENPIC_CONFIG_8259_PASSTHROUGH_DISABLE&t;0x20000000
DECL|macro|OPENPIC_CONFIG_BASE_MASK
mdefine_line|#define OPENPIC_CONFIG_BASE_MASK&t;&t;0x000fffff
multiline_comment|/*&n;     *  Global Configuration Register 1&n;     *  This is the EICR on EPICs.&n;     */
DECL|macro|OPENPIC_EICR_S_CLK_MASK
mdefine_line|#define OPENPIC_EICR_S_CLK_MASK&t;&t;&t;0x70000000
DECL|macro|OPENPIC_EICR_SIE
mdefine_line|#define OPENPIC_EICR_SIE&t;&t;&t;0x08000000
multiline_comment|/*&n;     *  Vendor Identification Register&n;     */
DECL|macro|OPENPIC_VENDOR_ID_STEPPING_MASK
mdefine_line|#define OPENPIC_VENDOR_ID_STEPPING_MASK&t;&t;0x00ff0000
DECL|macro|OPENPIC_VENDOR_ID_STEPPING_SHIFT
mdefine_line|#define OPENPIC_VENDOR_ID_STEPPING_SHIFT&t;16
DECL|macro|OPENPIC_VENDOR_ID_DEVICE_ID_MASK
mdefine_line|#define OPENPIC_VENDOR_ID_DEVICE_ID_MASK&t;0x0000ff00
DECL|macro|OPENPIC_VENDOR_ID_DEVICE_ID_SHIFT
mdefine_line|#define OPENPIC_VENDOR_ID_DEVICE_ID_SHIFT&t;8
DECL|macro|OPENPIC_VENDOR_ID_VENDOR_ID_MASK
mdefine_line|#define OPENPIC_VENDOR_ID_VENDOR_ID_MASK&t;0x000000ff
multiline_comment|/*&n;     *  Vector/Priority Registers&n;     */
DECL|macro|OPENPIC_MASK
mdefine_line|#define OPENPIC_MASK&t;&t;&t;&t;0x80000000
DECL|macro|OPENPIC_ACTIVITY
mdefine_line|#define OPENPIC_ACTIVITY&t;&t;&t;0x40000000&t;/* Read Only */
DECL|macro|OPENPIC_PRIORITY_MASK
mdefine_line|#define OPENPIC_PRIORITY_MASK&t;&t;&t;0x000f0000
DECL|macro|OPENPIC_PRIORITY_SHIFT
mdefine_line|#define OPENPIC_PRIORITY_SHIFT&t;&t;&t;16
DECL|macro|OPENPIC_VECTOR_MASK
mdefine_line|#define OPENPIC_VECTOR_MASK&t;&t;&t;0x000000ff
multiline_comment|/*&n;     *  Interrupt Source Registers&n;     */
DECL|macro|OPENPIC_POLARITY_POSITIVE
mdefine_line|#define OPENPIC_POLARITY_POSITIVE&t;&t;0x00800000
DECL|macro|OPENPIC_POLARITY_NEGATIVE
mdefine_line|#define OPENPIC_POLARITY_NEGATIVE&t;&t;0x00000000
DECL|macro|OPENPIC_POLARITY_MASK
mdefine_line|#define OPENPIC_POLARITY_MASK&t;&t;&t;0x00800000
DECL|macro|OPENPIC_SENSE_LEVEL
mdefine_line|#define OPENPIC_SENSE_LEVEL&t;&t;&t;0x00400000
DECL|macro|OPENPIC_SENSE_EDGE
mdefine_line|#define OPENPIC_SENSE_EDGE&t;&t;&t;0x00000000
DECL|macro|OPENPIC_SENSE_MASK
mdefine_line|#define OPENPIC_SENSE_MASK&t;&t;&t;0x00400000
multiline_comment|/*&n;     *  Timer Registers&n;     */
DECL|macro|OPENPIC_COUNT_MASK
mdefine_line|#define OPENPIC_COUNT_MASK&t;&t;&t;0x7fffffff
DECL|macro|OPENPIC_TIMER_TOGGLE
mdefine_line|#define OPENPIC_TIMER_TOGGLE&t;&t;&t;0x80000000
DECL|macro|OPENPIC_TIMER_COUNT_INHIBIT
mdefine_line|#define OPENPIC_TIMER_COUNT_INHIBIT&t;&t;0x80000000
multiline_comment|/*&n;     *  Aliases to make life simpler&n;     */
multiline_comment|/* Per Processor Registers */
DECL|macro|IPI_Dispatch
mdefine_line|#define IPI_Dispatch(i)&t;&t;&t;_IPI_Dispatch[i].Reg
DECL|macro|Current_Task_Priority
mdefine_line|#define Current_Task_Priority&t;&t;_Current_Task_Priority.Reg
DECL|macro|Interrupt_Acknowledge
mdefine_line|#define Interrupt_Acknowledge&t;&t;_Interrupt_Acknowledge.Reg
DECL|macro|EOI
mdefine_line|#define EOI&t;&t;&t;&t;_EOI.Reg
multiline_comment|/* Global Registers */
DECL|macro|Feature_Reporting0
mdefine_line|#define Feature_Reporting0&t;&t;_Feature_Reporting0.Reg
DECL|macro|Feature_Reporting1
mdefine_line|#define Feature_Reporting1&t;&t;_Feature_Reporting1.Reg
DECL|macro|Global_Configuration0
mdefine_line|#define Global_Configuration0&t;&t;_Global_Configuration0.Reg
DECL|macro|Global_Configuration1
mdefine_line|#define Global_Configuration1&t;&t;_Global_Configuration1.Reg
DECL|macro|Vendor_Specific
mdefine_line|#define Vendor_Specific(i)&t;&t;_Vendor_Specific[i].Reg
DECL|macro|Vendor_Identification
mdefine_line|#define Vendor_Identification&t;&t;_Vendor_Identification.Reg
DECL|macro|Processor_Initialization
mdefine_line|#define Processor_Initialization&t;_Processor_Initialization.Reg
DECL|macro|IPI_Vector_Priority
mdefine_line|#define IPI_Vector_Priority(i)&t;&t;_IPI_Vector_Priority[i].Reg
DECL|macro|Spurious_Vector
mdefine_line|#define Spurious_Vector&t;&t;&t;_Spurious_Vector.Reg
DECL|macro|Timer_Frequency
mdefine_line|#define Timer_Frequency&t;&t;&t;_Timer_Frequency.Reg
multiline_comment|/* Timer Registers */
DECL|macro|Current_Count
mdefine_line|#define Current_Count&t;&t;&t;_Current_Count.Reg
DECL|macro|Base_Count
mdefine_line|#define Base_Count&t;&t;&t;_Base_Count.Reg
DECL|macro|Vector_Priority
mdefine_line|#define Vector_Priority&t;&t;&t;_Vector_Priority.Reg
DECL|macro|Destination
mdefine_line|#define Destination&t;&t;&t;_Destination.Reg
multiline_comment|/* Interrupt Source Registers */
DECL|macro|Vector_Priority
mdefine_line|#define Vector_Priority&t;&t;&t;_Vector_Priority.Reg
DECL|macro|Destination
mdefine_line|#define Destination&t;&t;&t;_Destination.Reg
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_OPENPIC_H */
eof
