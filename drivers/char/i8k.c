multiline_comment|/*&n; * i8k.c -- Linux driver for accessing the SMM BIOS on Dell laptops.&n; *&t;    See http://www.debian.org/~dz/i8k/ for more information&n; *&t;    and for latest version of this driver.&n; *&n; * Copyright (C) 2001  Massimo Dal Zotto &lt;dz@debian.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/apm_bios.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/i8k.h&gt;
DECL|macro|I8K_VERSION
mdefine_line|#define I8K_VERSION&t;&t;&quot;1.13 14/05/2002&quot;
DECL|macro|I8K_SMM_FN_STATUS
mdefine_line|#define I8K_SMM_FN_STATUS&t;0x0025
DECL|macro|I8K_SMM_POWER_STATUS
mdefine_line|#define I8K_SMM_POWER_STATUS&t;0x0069
DECL|macro|I8K_SMM_SET_FAN
mdefine_line|#define I8K_SMM_SET_FAN&t;&t;0x01a3
DECL|macro|I8K_SMM_GET_FAN
mdefine_line|#define I8K_SMM_GET_FAN&t;&t;0x00a3
DECL|macro|I8K_SMM_GET_SPEED
mdefine_line|#define I8K_SMM_GET_SPEED&t;0x02a3
DECL|macro|I8K_SMM_GET_TEMP
mdefine_line|#define I8K_SMM_GET_TEMP&t;0x10a3
DECL|macro|I8K_SMM_GET_DELL_SIG
mdefine_line|#define I8K_SMM_GET_DELL_SIG&t;0xffa3
DECL|macro|I8K_SMM_BIOS_VERSION
mdefine_line|#define I8K_SMM_BIOS_VERSION&t;0x00a6
DECL|macro|I8K_FAN_MULT
mdefine_line|#define I8K_FAN_MULT&t;&t;30
DECL|macro|I8K_MAX_TEMP
mdefine_line|#define I8K_MAX_TEMP&t;&t;127
DECL|macro|I8K_FN_NONE
mdefine_line|#define I8K_FN_NONE&t;&t;0x00
DECL|macro|I8K_FN_UP
mdefine_line|#define I8K_FN_UP&t;&t;0x01
DECL|macro|I8K_FN_DOWN
mdefine_line|#define I8K_FN_DOWN&t;&t;0x02
DECL|macro|I8K_FN_MUTE
mdefine_line|#define I8K_FN_MUTE&t;&t;0x04
DECL|macro|I8K_FN_MASK
mdefine_line|#define I8K_FN_MASK&t;&t;0x07
DECL|macro|I8K_FN_SHIFT
mdefine_line|#define I8K_FN_SHIFT&t;&t;8
DECL|macro|I8K_POWER_AC
mdefine_line|#define I8K_POWER_AC&t;&t;0x05
DECL|macro|I8K_POWER_BATTERY
mdefine_line|#define I8K_POWER_BATTERY&t;0x01
DECL|macro|I8K_TEMPERATURE_BUG
mdefine_line|#define I8K_TEMPERATURE_BUG&t;1
DECL|macro|DELL_SIGNATURE
mdefine_line|#define DELL_SIGNATURE&t;&t;&quot;Dell Computer&quot;
DECL|variable|supported_models
r_static
r_char
op_star
id|supported_models
(braket
)braket
op_assign
(brace
l_string|&quot;Inspiron&quot;
comma
l_string|&quot;Latitude&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|system_vendor
r_static
r_char
id|system_vendor
(braket
l_int|48
)braket
op_assign
l_string|&quot;?&quot;
suffix:semicolon
DECL|variable|product_name
r_static
r_char
id|product_name
(braket
l_int|48
)braket
op_assign
l_string|&quot;?&quot;
suffix:semicolon
DECL|variable|bios_version
r_static
r_char
id|bios_version
(braket
l_int|4
)braket
op_assign
l_string|&quot;?&quot;
suffix:semicolon
DECL|variable|serial_number
r_static
r_char
id|serial_number
(braket
l_int|16
)braket
op_assign
l_string|&quot;?&quot;
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Massimo Dal Zotto (dz@debian.org)&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for accessing SMM BIOS on Dell laptops&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|force
r_static
r_int
id|force
suffix:semicolon
id|module_param
c_func
(paren
id|force
comma
r_bool
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|force
comma
l_string|&quot;Force loading without checking for supported models&quot;
)paren
suffix:semicolon
DECL|variable|restricted
r_static
r_int
id|restricted
suffix:semicolon
id|module_param
c_func
(paren
id|restricted
comma
r_bool
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|restricted
comma
l_string|&quot;Allow fan control if SYS_ADMIN capability set&quot;
)paren
suffix:semicolon
DECL|variable|power_status
r_static
r_int
id|power_status
suffix:semicolon
id|module_param
c_func
(paren
id|power_status
comma
r_bool
comma
l_int|0600
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|power_status
comma
l_string|&quot;Report power status in /proc/i8k&quot;
)paren
suffix:semicolon
r_static
id|ssize_t
id|i8k_read
c_func
(paren
r_struct
id|file
op_star
comma
r_char
id|__user
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_static
r_int
id|i8k_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|variable|i8k_fops
r_static
r_struct
id|file_operations
id|i8k_fops
op_assign
(brace
dot
id|read
op_assign
id|i8k_read
comma
dot
id|ioctl
op_assign
id|i8k_ioctl
comma
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|eax
r_int
r_int
id|eax
suffix:semicolon
DECL|member|ebx
r_int
r_int
id|ebx
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|ecx
r_int
r_int
id|ecx
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|edx
r_int
r_int
id|edx
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|esi
r_int
r_int
id|esi
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|edi
r_int
r_int
id|edi
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|SMMRegisters
)brace
id|SMMRegisters
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|length
id|u8
id|length
suffix:semicolon
DECL|member|handle
id|u16
id|handle
suffix:semicolon
DECL|typedef|DMIHeader
)brace
id|DMIHeader
suffix:semicolon
multiline_comment|/*&n; * Call the System Management Mode BIOS. Code provided by Jonathan Buzzard.&n; */
DECL|function|i8k_smm
r_static
r_int
id|i8k_smm
c_func
(paren
id|SMMRegisters
op_star
id|regs
)paren
(brace
r_int
id|rc
suffix:semicolon
r_int
id|eax
op_assign
id|regs-&gt;eax
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;pushl %%eax&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;movl 0(%%eax),%%edx&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;push %%edx&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;movl 4(%%eax),%%ebx&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;movl 8(%%eax),%%ecx&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;movl 12(%%eax),%%edx&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;movl 16(%%eax),%%esi&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;movl 20(%%eax),%%edi&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;popl %%eax&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;out %%al,$0xb2&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;out %%al,$0x84&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;xchgl %%eax,(%%esp)&bslash;n&bslash;t&quot;
l_string|&quot;movl %%ebx,4(%%eax)&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;movl %%ecx,8(%%eax)&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;movl %%edx,12(%%eax)&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;movl %%esi,16(%%eax)&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;movl %%edi,20(%%eax)&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;popl %%edx&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;movl %%edx,0(%%eax)&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;lahf&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;shrl $8,%%eax&bslash;n&bslash;t&quot;
"&bslash;"
l_string|&quot;andl $1,%%eax&bslash;n&quot;
"&bslash;"
suffix:colon
l_string|&quot;=a&quot;
(paren
id|rc
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|regs
)paren
suffix:colon
l_string|&quot;%ebx&quot;
comma
l_string|&quot;%ecx&quot;
comma
l_string|&quot;%edx&quot;
comma
l_string|&quot;%esi&quot;
comma
l_string|&quot;%edi&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_ne
l_int|0
)paren
op_logical_or
(paren
(paren
id|regs-&gt;eax
op_amp
l_int|0xffff
)paren
op_eq
l_int|0xffff
)paren
op_logical_or
(paren
id|regs-&gt;eax
op_eq
id|eax
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the bios version. Return the version as an integer corresponding&n; * to the ascii value, for example &quot;A17&quot; is returned as 0x00413137.&n; */
DECL|function|i8k_get_bios_version
r_static
r_int
id|i8k_get_bios_version
c_func
(paren
r_void
)paren
(brace
id|SMMRegisters
id|regs
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|regs.eax
op_assign
id|I8K_SMM_BIOS_VERSION
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|i8k_smm
c_func
(paren
op_amp
id|regs
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
r_return
id|regs.eax
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the machine id.&n; */
DECL|function|i8k_get_serial_number
r_static
r_int
id|i8k_get_serial_number
c_func
(paren
r_int
r_char
op_star
id|buff
)paren
(brace
id|strlcpy
c_func
(paren
id|buff
comma
id|serial_number
comma
r_sizeof
(paren
id|serial_number
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the Fn key status.&n; */
DECL|function|i8k_get_fn_status
r_static
r_int
id|i8k_get_fn_status
c_func
(paren
r_void
)paren
(brace
id|SMMRegisters
id|regs
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|regs.eax
op_assign
id|I8K_SMM_FN_STATUS
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|i8k_smm
c_func
(paren
op_amp
id|regs
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
r_switch
c_cond
(paren
(paren
id|regs.eax
op_rshift
id|I8K_FN_SHIFT
)paren
op_amp
id|I8K_FN_MASK
)paren
(brace
r_case
id|I8K_FN_UP
suffix:colon
r_return
id|I8K_VOL_UP
suffix:semicolon
r_case
id|I8K_FN_DOWN
suffix:colon
r_return
id|I8K_VOL_DOWN
suffix:semicolon
r_case
id|I8K_FN_MUTE
suffix:colon
r_return
id|I8K_VOL_MUTE
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Read the power status.&n; */
DECL|function|i8k_get_power_status
r_static
r_int
id|i8k_get_power_status
c_func
(paren
r_void
)paren
(brace
id|SMMRegisters
id|regs
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|regs.eax
op_assign
id|I8K_SMM_POWER_STATUS
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|i8k_smm
c_func
(paren
op_amp
id|regs
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|regs.eax
op_amp
l_int|0xff
)paren
(brace
r_case
id|I8K_POWER_AC
suffix:colon
r_return
id|I8K_AC
suffix:semicolon
r_default
suffix:colon
r_return
id|I8K_BATTERY
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Read the fan status.&n; */
DECL|function|i8k_get_fan_status
r_static
r_int
id|i8k_get_fan_status
c_func
(paren
r_int
id|fan
)paren
(brace
id|SMMRegisters
id|regs
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|regs.eax
op_assign
id|I8K_SMM_GET_FAN
suffix:semicolon
id|regs.ebx
op_assign
id|fan
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|i8k_smm
c_func
(paren
op_amp
id|regs
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
r_return
(paren
id|regs.eax
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the fan speed in RPM.&n; */
DECL|function|i8k_get_fan_speed
r_static
r_int
id|i8k_get_fan_speed
c_func
(paren
r_int
id|fan
)paren
(brace
id|SMMRegisters
id|regs
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|regs.eax
op_assign
id|I8K_SMM_GET_SPEED
suffix:semicolon
id|regs.ebx
op_assign
id|fan
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|i8k_smm
c_func
(paren
op_amp
id|regs
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
r_return
(paren
id|regs.eax
op_amp
l_int|0xffff
)paren
op_star
id|I8K_FAN_MULT
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the fan speed (off, low, high). Returns the new fan status.&n; */
DECL|function|i8k_set_fan
r_static
r_int
id|i8k_set_fan
c_func
(paren
r_int
id|fan
comma
r_int
id|speed
)paren
(brace
id|SMMRegisters
id|regs
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|speed
op_assign
(paren
id|speed
OL
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
(paren
id|speed
OG
id|I8K_FAN_MAX
)paren
ques
c_cond
id|I8K_FAN_MAX
suffix:colon
id|speed
)paren
suffix:semicolon
id|regs.eax
op_assign
id|I8K_SMM_SET_FAN
suffix:semicolon
id|regs.ebx
op_assign
(paren
id|fan
op_amp
l_int|0xff
)paren
op_or
(paren
id|speed
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|i8k_smm
c_func
(paren
op_amp
id|regs
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
r_return
(paren
id|i8k_get_fan_status
c_func
(paren
id|fan
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the cpu temperature.&n; */
DECL|function|i8k_get_cpu_temp
r_static
r_int
id|i8k_get_cpu_temp
c_func
(paren
r_void
)paren
(brace
id|SMMRegisters
id|regs
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_int
id|temp
suffix:semicolon
macro_line|#ifdef I8K_TEMPERATURE_BUG
r_static
r_int
id|prev
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|regs.eax
op_assign
id|I8K_SMM_GET_TEMP
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|i8k_smm
c_func
(paren
op_amp
id|regs
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
id|temp
op_assign
id|regs.eax
op_amp
l_int|0xff
suffix:semicolon
macro_line|#ifdef I8K_TEMPERATURE_BUG
multiline_comment|/*&n;     * Sometimes the temperature sensor returns 0x99, which is out of range.&n;     * In this case we return (once) the previous cached value. For example:&n;     # 1003655137 00000058 00005a4b&n;     # 1003655138 00000099 00003a80 &lt;--- 0x99 = 153 degrees&n;     # 1003655139 00000054 00005c52&n;     */
r_if
c_cond
(paren
id|temp
OG
id|I8K_MAX_TEMP
)paren
(brace
id|temp
op_assign
id|prev
suffix:semicolon
id|prev
op_assign
id|I8K_MAX_TEMP
suffix:semicolon
)brace
r_else
(brace
id|prev
op_assign
id|temp
suffix:semicolon
)brace
macro_line|#endif
r_return
id|temp
suffix:semicolon
)brace
DECL|function|i8k_get_dell_signature
r_static
r_int
id|i8k_get_dell_signature
c_func
(paren
r_void
)paren
(brace
id|SMMRegisters
id|regs
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|regs.eax
op_assign
id|I8K_SMM_GET_DELL_SIG
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|i8k_smm
c_func
(paren
op_amp
id|regs
)paren
)paren
OL
l_int|0
)paren
(brace
r_return
id|rc
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|regs.eax
op_eq
l_int|1145651527
)paren
op_logical_and
(paren
id|regs.edx
op_eq
l_int|1145392204
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|i8k_ioctl
r_static
r_int
id|i8k_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_struct
id|file
op_star
id|fp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|val
suffix:semicolon
r_int
id|speed
suffix:semicolon
r_int
r_char
id|buff
(braket
l_int|16
)braket
suffix:semicolon
r_int
id|__user
op_star
id|argp
op_assign
(paren
r_int
id|__user
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|argp
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|I8K_BIOS_VERSION
suffix:colon
id|val
op_assign
id|i8k_get_bios_version
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I8K_MACHINE_ID
suffix:colon
id|memset
c_func
(paren
id|buff
comma
l_int|0
comma
l_int|16
)paren
suffix:semicolon
id|val
op_assign
id|i8k_get_serial_number
c_func
(paren
id|buff
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I8K_FN_STATUS
suffix:colon
id|val
op_assign
id|i8k_get_fn_status
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I8K_POWER_STATUS
suffix:colon
id|val
op_assign
id|i8k_get_power_status
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I8K_GET_TEMP
suffix:colon
id|val
op_assign
id|i8k_get_cpu_temp
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I8K_GET_SPEED
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|val
comma
id|argp
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|val
op_assign
id|i8k_get_fan_speed
c_func
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I8K_GET_FAN
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|val
comma
id|argp
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|val
op_assign
id|i8k_get_fan_status
c_func
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I8K_SET_FAN
suffix:colon
r_if
c_cond
(paren
id|restricted
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|val
comma
id|argp
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|speed
comma
id|argp
op_plus
l_int|1
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|val
op_assign
id|i8k_set_fan
c_func
(paren
id|val
comma
id|speed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
OL
l_int|0
)paren
(brace
r_return
id|val
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|I8K_BIOS_VERSION
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|argp
comma
op_amp
id|val
comma
l_int|4
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|I8K_MACHINE_ID
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|argp
comma
id|buff
comma
l_int|16
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|argp
comma
op_amp
id|val
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Print the information for /proc/i8k.&n; */
DECL|function|i8k_get_info
r_static
r_int
id|i8k_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|fpos
comma
r_int
id|length
)paren
(brace
r_int
id|n
comma
id|fn_key
comma
id|cpu_temp
comma
id|ac_power
suffix:semicolon
r_int
id|left_fan
comma
id|right_fan
comma
id|left_speed
comma
id|right_speed
suffix:semicolon
id|cpu_temp
op_assign
id|i8k_get_cpu_temp
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* 11100 &#xfffd;s */
id|left_fan
op_assign
id|i8k_get_fan_status
c_func
(paren
id|I8K_FAN_LEFT
)paren
suffix:semicolon
multiline_comment|/*   580 &#xfffd;s */
id|right_fan
op_assign
id|i8k_get_fan_status
c_func
(paren
id|I8K_FAN_RIGHT
)paren
suffix:semicolon
multiline_comment|/*   580 &#xfffd;s */
id|left_speed
op_assign
id|i8k_get_fan_speed
c_func
(paren
id|I8K_FAN_LEFT
)paren
suffix:semicolon
multiline_comment|/*   580 &#xfffd;s */
id|right_speed
op_assign
id|i8k_get_fan_speed
c_func
(paren
id|I8K_FAN_RIGHT
)paren
suffix:semicolon
multiline_comment|/*   580 &#xfffd;s */
id|fn_key
op_assign
id|i8k_get_fn_status
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*   750 &#xfffd;s */
r_if
c_cond
(paren
id|power_status
)paren
(brace
id|ac_power
op_assign
id|i8k_get_power_status
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* 14700 &#xfffd;s */
)brace
r_else
(brace
id|ac_power
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;     * Info:&n;     *&n;     * 1)  Format version (this will change if format changes)&n;     * 2)  BIOS version&n;     * 3)  BIOS machine ID&n;     * 4)  Cpu temperature&n;     * 5)  Left fan status&n;     * 6)  Right fan status&n;     * 7)  Left fan speed&n;     * 8)  Right fan speed&n;     * 9)  AC power&n;     * 10) Fn Key status&n;     */
id|n
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s %s %s %d %d %d %d %d %d %d&bslash;n&quot;
comma
id|I8K_PROC_FMT
comma
id|bios_version
comma
id|serial_number
comma
id|cpu_temp
comma
id|left_fan
comma
id|right_fan
comma
id|left_speed
comma
id|right_speed
comma
id|ac_power
comma
id|fn_key
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|i8k_read
r_static
id|ssize_t
id|i8k_read
c_func
(paren
r_struct
id|file
op_star
id|f
comma
r_char
id|__user
op_star
id|buffer
comma
r_int
id|len
comma
id|loff_t
op_star
id|fpos
)paren
(brace
r_int
id|n
suffix:semicolon
r_char
id|info
(braket
l_int|128
)braket
suffix:semicolon
id|n
op_assign
id|i8k_get_info
c_func
(paren
id|info
comma
l_int|NULL
comma
l_int|0
comma
l_int|128
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
(brace
r_return
id|n
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|fpos
op_ge
id|n
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_star
id|fpos
op_plus
id|len
)paren
op_ge
id|n
)paren
(brace
id|len
op_assign
id|n
op_minus
op_star
id|fpos
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|info
comma
id|len
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
op_star
id|fpos
op_add_assign
id|len
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|string_trim
r_static
r_char
op_star
id|__init
id|string_trim
c_func
(paren
r_char
op_star
id|s
comma
r_int
id|size
)paren
(brace
r_int
id|len
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_assign
id|strlen
c_func
(paren
id|s
)paren
)paren
OG
id|size
)paren
(brace
id|len
op_assign
id|size
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
id|s
op_plus
id|len
op_minus
l_int|1
suffix:semicolon
id|len
op_logical_and
(paren
op_star
id|p
op_eq
l_char|&squot; &squot;
)paren
suffix:semicolon
id|len
op_decrement
comma
id|p
op_decrement
)paren
(brace
op_star
id|p
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_return
id|s
suffix:semicolon
)brace
multiline_comment|/* DMI code, stolen from arch/i386/kernel/dmi_scan.c */
multiline_comment|/*&n; * |&lt;-- dmi-&gt;length --&gt;|&n; * |                   |&n; * |dmi header    s=N  | string1,&bslash;0, ..., stringN,&bslash;0, ..., &bslash;0&n; *                |                       |&n; *                +-----------------------+&n; */
DECL|function|dmi_string
r_static
r_char
op_star
id|__init
id|dmi_string
c_func
(paren
id|DMIHeader
op_star
id|dmi
comma
id|u8
id|s
)paren
(brace
id|u8
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
(brace
r_return
l_string|&quot;&quot;
suffix:semicolon
)brace
id|s
op_decrement
suffix:semicolon
id|p
op_assign
(paren
id|u8
op_star
)paren
id|dmi
op_plus
id|dmi-&gt;length
suffix:semicolon
r_while
c_loop
(paren
id|s
OG
l_int|0
)paren
(brace
id|p
op_add_assign
id|strlen
c_func
(paren
id|p
)paren
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|s
op_decrement
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
DECL|function|dmi_decode
r_static
r_void
id|__init
id|dmi_decode
c_func
(paren
id|DMIHeader
op_star
id|dmi
)paren
(brace
id|u8
op_star
id|data
op_assign
(paren
id|u8
op_star
)paren
id|dmi
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
macro_line|#ifdef I8K_DEBUG
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
(paren
r_int
)paren
id|data
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|data
(braket
l_int|1
)braket
op_logical_and
id|i
OL
l_int|64
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|dmi-&gt;type
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* BIOS Information */
id|p
op_assign
id|dmi_string
c_func
(paren
id|dmi
comma
id|data
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
)paren
(brace
id|strlcpy
c_func
(paren
id|bios_version
comma
id|p
comma
r_sizeof
(paren
id|bios_version
)paren
)paren
suffix:semicolon
id|string_trim
c_func
(paren
id|bios_version
comma
r_sizeof
(paren
id|bios_version
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* System Information */
id|p
op_assign
id|dmi_string
c_func
(paren
id|dmi
comma
id|data
(braket
l_int|4
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
)paren
(brace
id|strlcpy
c_func
(paren
id|system_vendor
comma
id|p
comma
r_sizeof
(paren
id|system_vendor
)paren
)paren
suffix:semicolon
id|string_trim
c_func
(paren
id|system_vendor
comma
r_sizeof
(paren
id|system_vendor
)paren
)paren
suffix:semicolon
)brace
id|p
op_assign
id|dmi_string
c_func
(paren
id|dmi
comma
id|data
(braket
l_int|5
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
)paren
(brace
id|strlcpy
c_func
(paren
id|product_name
comma
id|p
comma
r_sizeof
(paren
id|product_name
)paren
)paren
suffix:semicolon
id|string_trim
c_func
(paren
id|product_name
comma
r_sizeof
(paren
id|product_name
)paren
)paren
suffix:semicolon
)brace
id|p
op_assign
id|dmi_string
c_func
(paren
id|dmi
comma
id|data
(braket
l_int|7
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
)paren
(brace
id|strlcpy
c_func
(paren
id|serial_number
comma
id|p
comma
r_sizeof
(paren
id|serial_number
)paren
)paren
suffix:semicolon
id|string_trim
c_func
(paren
id|serial_number
comma
r_sizeof
(paren
id|serial_number
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
DECL|function|dmi_table
r_static
r_int
id|__init
id|dmi_table
c_func
(paren
id|u32
id|base
comma
r_int
id|len
comma
r_int
id|num
comma
r_void
(paren
op_star
id|fn
)paren
(paren
id|DMIHeader
op_star
)paren
)paren
(brace
id|u8
op_star
id|buf
suffix:semicolon
id|u8
op_star
id|data
suffix:semicolon
id|DMIHeader
op_star
id|dmi
suffix:semicolon
r_int
id|i
op_assign
l_int|1
suffix:semicolon
id|buf
op_assign
id|ioremap
c_func
(paren
id|base
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|data
op_assign
id|buf
suffix:semicolon
multiline_comment|/*&n;     * Stop when we see al the items the table claimed to have&n;     * or we run off the end of the table (also happens)&n;     */
r_while
c_loop
(paren
(paren
id|i
OL
id|num
)paren
op_logical_and
(paren
(paren
id|data
op_minus
id|buf
)paren
OL
id|len
)paren
)paren
(brace
id|dmi
op_assign
(paren
id|DMIHeader
op_star
)paren
id|data
suffix:semicolon
multiline_comment|/*&n;&t; * Avoid misparsing crud if the length of the last&n;&t; * record is crap&n;&t; */
r_if
c_cond
(paren
(paren
id|data
op_minus
id|buf
op_plus
id|dmi-&gt;length
)paren
op_ge
id|len
)paren
(brace
r_break
suffix:semicolon
)brace
id|fn
c_func
(paren
id|dmi
)paren
suffix:semicolon
id|data
op_add_assign
id|dmi-&gt;length
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t go off the end of the data if there is&n;&t; * stuff looking like string fill past the end&n;&t; */
r_while
c_loop
(paren
(paren
(paren
id|data
op_minus
id|buf
)paren
OL
id|len
)paren
op_logical_and
(paren
op_star
id|data
op_logical_or
id|data
(braket
l_int|1
)braket
)paren
)paren
(brace
id|data
op_increment
suffix:semicolon
)brace
id|data
op_add_assign
l_int|2
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|iounmap
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dmi_iterate
r_static
r_int
id|__init
id|dmi_iterate
c_func
(paren
r_void
(paren
op_star
id|decode
)paren
(paren
id|DMIHeader
op_star
)paren
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|20
)braket
suffix:semicolon
r_void
id|__iomem
op_star
id|p
op_assign
id|ioremap
c_func
(paren
l_int|0xe0000
comma
l_int|0x20000
)paren
comma
op_star
id|q
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|q
op_assign
id|p
suffix:semicolon
id|q
OL
id|p
op_plus
l_int|0x20000
suffix:semicolon
id|q
op_add_assign
l_int|16
)paren
(brace
id|memcpy_fromio
c_func
(paren
id|buf
comma
id|q
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buf
comma
l_string|&quot;_DMI_&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
(brace
id|u16
id|num
op_assign
id|buf
(braket
l_int|13
)braket
op_lshift
l_int|8
op_or
id|buf
(braket
l_int|12
)braket
suffix:semicolon
id|u16
id|len
op_assign
id|buf
(braket
l_int|7
)braket
op_lshift
l_int|8
op_or
id|buf
(braket
l_int|6
)braket
suffix:semicolon
id|u32
id|base
op_assign
id|buf
(braket
l_int|11
)braket
op_lshift
l_int|24
op_or
id|buf
(braket
l_int|10
)braket
op_lshift
l_int|16
op_or
id|buf
(braket
l_int|9
)braket
op_lshift
l_int|8
op_or
id|buf
(braket
l_int|8
)braket
suffix:semicolon
macro_line|#ifdef I8K_DEBUG
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;DMI %d.%d present.&bslash;n&quot;
comma
id|buf
(braket
l_int|14
)braket
op_rshift
l_int|4
comma
id|buf
(braket
l_int|14
)braket
op_amp
l_int|0x0F
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%d structures occupying %d bytes.&bslash;n&quot;
comma
id|buf
(braket
l_int|13
)braket
op_lshift
l_int|8
op_or
id|buf
(braket
l_int|12
)braket
comma
id|buf
(braket
l_int|7
)braket
op_lshift
l_int|8
op_or
id|buf
(braket
l_int|6
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;DMI table at 0x%08X.&bslash;n&quot;
comma
id|buf
(braket
l_int|11
)braket
op_lshift
l_int|24
op_or
id|buf
(braket
l_int|10
)braket
op_lshift
l_int|16
op_or
id|buf
(braket
l_int|9
)braket
op_lshift
l_int|8
op_or
id|buf
(braket
l_int|8
)braket
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|dmi_table
c_func
(paren
id|base
comma
id|len
comma
id|num
comma
id|decode
)paren
op_eq
l_int|0
)paren
(brace
id|iounmap
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
id|iounmap
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* end of DMI code */
multiline_comment|/*&n; * Get DMI information.&n; */
DECL|function|i8k_dmi_probe
r_static
r_int
id|__init
id|i8k_dmi_probe
c_func
(paren
r_void
)paren
(brace
r_char
op_star
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|dmi_iterate
c_func
(paren
id|dmi_decode
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i8k: unable to get DMI information&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|system_vendor
comma
id|DELL_SIGNATURE
comma
id|strlen
c_func
(paren
id|DELL_SIGNATURE
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i8k: not running on a Dell system&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
id|supported_models
suffix:semicolon
suffix:semicolon
id|p
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|p
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i8k: unsupported model: %s&bslash;n&quot;
comma
id|product_name
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|product_name
comma
op_star
id|p
comma
id|strlen
c_func
(paren
op_star
id|p
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Probe for the presence of a supported laptop.&n; */
DECL|function|i8k_probe
r_static
r_int
id|__init
id|i8k_probe
c_func
(paren
r_void
)paren
(brace
r_char
id|buff
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|version
suffix:semicolon
r_int
id|smm_found
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;     * Get DMI information&n;     */
r_if
c_cond
(paren
id|i8k_dmi_probe
c_func
(paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i8k: vendor=%s, model=%s, version=%s&bslash;n&quot;
comma
id|system_vendor
comma
id|product_name
comma
id|bios_version
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     * Get SMM Dell signature&n;     */
r_if
c_cond
(paren
id|i8k_get_dell_signature
c_func
(paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i8k: unable to get SMM Dell signature&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|smm_found
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;     * Get SMM BIOS version.&n;     */
id|version
op_assign
id|i8k_get_bios_version
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|version
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i8k: unable to get SMM BIOS version&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|smm_found
op_assign
l_int|1
suffix:semicolon
id|buff
(braket
l_int|0
)braket
op_assign
(paren
id|version
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buff
(braket
l_int|1
)braket
op_assign
(paren
id|version
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buff
(braket
l_int|2
)braket
op_assign
(paren
id|version
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buff
(braket
l_int|3
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/*&n;&t; * If DMI BIOS version is unknown use SMM BIOS version.&n;&t; */
r_if
c_cond
(paren
id|bios_version
(braket
l_int|0
)braket
op_eq
l_char|&squot;?&squot;
)paren
(brace
id|strcpy
c_func
(paren
id|bios_version
comma
id|buff
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check if the two versions match.&n;&t; */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|buff
comma
id|bios_version
comma
r_sizeof
(paren
id|bios_version
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i8k: BIOS version mismatch: %s != %s&bslash;n&quot;
comma
id|buff
comma
id|bios_version
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|smm_found
op_logical_and
op_logical_neg
id|force
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
r_static
macro_line|#endif
DECL|function|i8k_init
r_int
id|__init
id|i8k_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|proc_i8k
suffix:semicolon
multiline_comment|/* Are we running on an supported laptop? */
r_if
c_cond
(paren
id|i8k_probe
c_func
(paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Register the proc entry */
id|proc_i8k
op_assign
id|create_proc_info_entry
c_func
(paren
l_string|&quot;i8k&quot;
comma
l_int|0
comma
l_int|NULL
comma
id|i8k_get_info
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_i8k
)paren
(brace
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|proc_i8k-&gt;proc_fops
op_assign
op_amp
id|i8k_fops
suffix:semicolon
id|proc_i8k-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Dell laptop SMM driver v%s Massimo Dal Zotto (dz@debian.org)&bslash;n&quot;
comma
id|I8K_VERSION
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|i8k_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Remove the proc entry */
id|remove_proc_entry
c_func
(paren
l_string|&quot;i8k&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i8k: module unloaded&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* end of file */
eof
