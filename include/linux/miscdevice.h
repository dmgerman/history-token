macro_line|#ifndef _LINUX_MISCDEVICE_H
DECL|macro|_LINUX_MISCDEVICE_H
mdefine_line|#define _LINUX_MISCDEVICE_H
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/major.h&gt;
DECL|macro|PSMOUSE_MINOR
mdefine_line|#define PSMOUSE_MINOR  1
DECL|macro|MS_BUSMOUSE_MINOR
mdefine_line|#define MS_BUSMOUSE_MINOR 2
DECL|macro|ATIXL_BUSMOUSE_MINOR
mdefine_line|#define ATIXL_BUSMOUSE_MINOR 3
multiline_comment|/*#define AMIGAMOUSE_MINOR 4&t;FIXME OBSOLETE */
DECL|macro|ATARIMOUSE_MINOR
mdefine_line|#define ATARIMOUSE_MINOR 5
DECL|macro|SUN_MOUSE_MINOR
mdefine_line|#define SUN_MOUSE_MINOR 6
DECL|macro|APOLLO_MOUSE_MINOR
mdefine_line|#define APOLLO_MOUSE_MINOR 7
DECL|macro|PC110PAD_MINOR
mdefine_line|#define PC110PAD_MINOR 9
multiline_comment|/*#define ADB_MOUSE_MINOR 10&t;FIXME OBSOLETE */
DECL|macro|WATCHDOG_MINOR
mdefine_line|#define WATCHDOG_MINOR&t;&t;130&t;/* Watchdog timer     */
DECL|macro|TEMP_MINOR
mdefine_line|#define TEMP_MINOR&t;&t;131&t;/* Temperature Sensor */
DECL|macro|RTC_MINOR
mdefine_line|#define RTC_MINOR 135
DECL|macro|EFI_RTC_MINOR
mdefine_line|#define EFI_RTC_MINOR&t;&t;136&t;/* EFI Time services */
DECL|macro|SUN_OPENPROM_MINOR
mdefine_line|#define SUN_OPENPROM_MINOR 139
DECL|macro|DMAPI_MINOR
mdefine_line|#define DMAPI_MINOR&t;&t;140&t;/* DMAPI */
DECL|macro|NVRAM_MINOR
mdefine_line|#define NVRAM_MINOR 144
DECL|macro|SGI_MMTIMER
mdefine_line|#define SGI_MMTIMER        153
DECL|macro|STORE_QUEUE_MINOR
mdefine_line|#define STORE_QUEUE_MINOR&t;155
DECL|macro|I2O_MINOR
mdefine_line|#define I2O_MINOR 166
DECL|macro|MICROCODE_MINOR
mdefine_line|#define MICROCODE_MINOR&t;&t;184
DECL|macro|MWAVE_MINOR
mdefine_line|#define MWAVE_MINOR&t;219&t;&t;/* ACP/Mwave Modem */
DECL|macro|MPT_MINOR
mdefine_line|#define MPT_MINOR&t;220
DECL|macro|MISC_DYNAMIC_MINOR
mdefine_line|#define MISC_DYNAMIC_MINOR 255
DECL|macro|TUN_MINOR
mdefine_line|#define TUN_MINOR&t;     200
DECL|macro|HPET_MINOR
mdefine_line|#define&t;HPET_MINOR&t;     228
r_struct
id|device
suffix:semicolon
r_struct
id|class_device
suffix:semicolon
DECL|struct|miscdevice
r_struct
id|miscdevice
(brace
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|fops
r_struct
id|file_operations
op_star
id|fops
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|class
r_struct
id|class_device
op_star
r_class
suffix:semicolon
DECL|member|devfs_name
r_char
id|devfs_name
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|misc_register
c_func
(paren
r_struct
id|miscdevice
op_star
id|misc
)paren
suffix:semicolon
r_extern
r_int
id|misc_deregister
c_func
(paren
r_struct
id|miscdevice
op_star
id|misc
)paren
suffix:semicolon
DECL|macro|MODULE_ALIAS_MISCDEV
mdefine_line|#define MODULE_ALIAS_MISCDEV(minor)&t;&t;&t;&t;&bslash;&n;&t;MODULE_ALIAS(&quot;char-major-&quot; __stringify(MISC_MAJOR)&t;&bslash;&n;&t;&quot;-&quot; __stringify(minor))
macro_line|#endif
eof
