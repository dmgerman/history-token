macro_line|#ifndef _LINUX_MISCDEVICE_H
DECL|macro|_LINUX_MISCDEVICE_H
mdefine_line|#define _LINUX_MISCDEVICE_H
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
DECL|macro|BUSMOUSE_MINOR
mdefine_line|#define BUSMOUSE_MINOR 0
DECL|macro|PSMOUSE_MINOR
mdefine_line|#define PSMOUSE_MINOR  1
DECL|macro|MS_BUSMOUSE_MINOR
mdefine_line|#define MS_BUSMOUSE_MINOR 2
DECL|macro|ATIXL_BUSMOUSE_MINOR
mdefine_line|#define ATIXL_BUSMOUSE_MINOR 3
DECL|macro|AMIGAMOUSE_MINOR
mdefine_line|#define AMIGAMOUSE_MINOR 4
DECL|macro|ATARIMOUSE_MINOR
mdefine_line|#define ATARIMOUSE_MINOR 5
DECL|macro|SUN_MOUSE_MINOR
mdefine_line|#define SUN_MOUSE_MINOR 6
DECL|macro|APOLLO_MOUSE_MINOR
mdefine_line|#define APOLLO_MOUSE_MINOR 7
DECL|macro|PC110PAD_MINOR
mdefine_line|#define PC110PAD_MINOR 9
DECL|macro|ADB_MOUSE_MINOR
mdefine_line|#define ADB_MOUSE_MINOR 10
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
DECL|macro|NVRAM_MINOR
mdefine_line|#define NVRAM_MINOR 144
DECL|macro|I2O_MINOR
mdefine_line|#define I2O_MINOR 166
DECL|macro|MICROCODE_MINOR
mdefine_line|#define MICROCODE_MINOR&t;&t;184
DECL|macro|MPT_MINOR
mdefine_line|#define MPT_MINOR&t;220
DECL|macro|MISC_DYNAMIC_MINOR
mdefine_line|#define MISC_DYNAMIC_MINOR 255
DECL|macro|SGI_GRAPHICS_MINOR
mdefine_line|#define SGI_GRAPHICS_MINOR   146
DECL|macro|SGI_OPENGL_MINOR
mdefine_line|#define SGI_OPENGL_MINOR     147
DECL|macro|SGI_GFX_MINOR
mdefine_line|#define SGI_GFX_MINOR        148
DECL|macro|SGI_STREAMS_MOUSE
mdefine_line|#define SGI_STREAMS_MOUSE    149
DECL|macro|SGI_STREAMS_KEYBOARD
mdefine_line|#define SGI_STREAMS_KEYBOARD 150
multiline_comment|/* drivers/sgi/char/usema.c */
DECL|macro|SGI_USEMACLONE
mdefine_line|#define SGI_USEMACLONE&t;     151
DECL|macro|TUN_MINOR
mdefine_line|#define TUN_MINOR&t;     200
r_extern
r_int
id|misc_init
c_func
(paren
r_void
)paren
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
DECL|member|next
DECL|member|prev
r_struct
id|miscdevice
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
DECL|member|devfs_handle
id|devfs_handle_t
id|devfs_handle
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
macro_line|#endif
eof
