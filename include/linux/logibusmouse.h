macro_line|#ifndef _LINUX_BUSMOUSE_H
DECL|macro|_LINUX_BUSMOUSE_H
mdefine_line|#define _LINUX_BUSMOUSE_H
multiline_comment|/*&n; * linux/include/linux/busmouse.h: header file for Logitech Bus Mouse driver&n; * by James Banks&n; *&n; * based on information gleamed from various mouse drivers on the net&n; *&n; * Heavily modified by David giller (rafetmad@oxy.edu)&n; *&n; * Minor modifications for Linux 0.96c-pl1 by Nathan Laredo&n; * gt7080a@prism.gatech.edu (13JUL92)&n; *&n; * Microsoft BusMouse support by Teemu Rantanen (tvr@cs.hut.fi) (02AUG92)&n; *&n; * Microsoft Bus Mouse support modified by Derrick Cole (cole@concert.net)&n; *    8/28/92&n; *&n; * Microsoft Bus Mouse support folded into 0.97pl4 code&n; *    by Peter Cervasio (pete%q106fm.uucp@wupost.wustl.edu) (08SEP92)&n; * Changes:  Logitech and Microsoft support in the same kernel.&n; *           Defined new constants in busmouse.h for MS mice.&n; *           Added int mse_busmouse_type to distinguish busmouse types&n; *           Added a couple of new functions to handle differences in using&n; *             MS vs. Logitech (where the int variable wasn&squot;t appropriate).&n; *&n; */
DECL|macro|MOUSE_IRQ
mdefine_line|#define MOUSE_IRQ&t;&t;5
DECL|macro|LOGITECH_BUSMOUSE
mdefine_line|#define LOGITECH_BUSMOUSE       0   /* Minor device # for Logitech  */
DECL|macro|MICROSOFT_BUSMOUSE
mdefine_line|#define MICROSOFT_BUSMOUSE      2   /* Minor device # for Microsoft */
multiline_comment|/*--------- LOGITECH BUSMOUSE ITEMS -------------*/
DECL|macro|LOGIBM_BASE
mdefine_line|#define&t;LOGIBM_BASE&t;&t;0x23c
DECL|macro|MSE_DATA_PORT
mdefine_line|#define&t;MSE_DATA_PORT&t;&t;0x23c
DECL|macro|MSE_SIGNATURE_PORT
mdefine_line|#define&t;MSE_SIGNATURE_PORT&t;0x23d
DECL|macro|MSE_CONTROL_PORT
mdefine_line|#define&t;MSE_CONTROL_PORT&t;0x23e
DECL|macro|MSE_INTERRUPT_PORT
mdefine_line|#define&t;MSE_INTERRUPT_PORT&t;0x23e
DECL|macro|MSE_CONFIG_PORT
mdefine_line|#define&t;MSE_CONFIG_PORT&t;&t;0x23f
DECL|macro|LOGIBM_EXTENT
mdefine_line|#define&t;LOGIBM_EXTENT&t;&t;0x4
DECL|macro|MSE_ENABLE_INTERRUPTS
mdefine_line|#define&t;MSE_ENABLE_INTERRUPTS&t;0x00
DECL|macro|MSE_DISABLE_INTERRUPTS
mdefine_line|#define&t;MSE_DISABLE_INTERRUPTS&t;0x10
DECL|macro|MSE_READ_X_LOW
mdefine_line|#define&t;MSE_READ_X_LOW&t;&t;0x80
DECL|macro|MSE_READ_X_HIGH
mdefine_line|#define&t;MSE_READ_X_HIGH&t;&t;0xa0
DECL|macro|MSE_READ_Y_LOW
mdefine_line|#define&t;MSE_READ_Y_LOW&t;&t;0xc0
DECL|macro|MSE_READ_Y_HIGH
mdefine_line|#define&t;MSE_READ_Y_HIGH&t;&t;0xe0
multiline_comment|/* Magic number used to check if the mouse exists */
DECL|macro|MSE_CONFIG_BYTE
mdefine_line|#define MSE_CONFIG_BYTE&t;&t;0x91
DECL|macro|MSE_DEFAULT_MODE
mdefine_line|#define MSE_DEFAULT_MODE&t;0x90
DECL|macro|MSE_SIGNATURE_BYTE
mdefine_line|#define MSE_SIGNATURE_BYTE&t;0xa5
multiline_comment|/* useful Logitech Mouse macros */
DECL|macro|MSE_INT_OFF
mdefine_line|#define MSE_INT_OFF()&t;outb(MSE_DISABLE_INTERRUPTS, MSE_CONTROL_PORT)
DECL|macro|MSE_INT_ON
mdefine_line|#define MSE_INT_ON()&t;outb(MSE_ENABLE_INTERRUPTS, MSE_CONTROL_PORT)
multiline_comment|/*--------- MICROSOFT BUSMOUSE ITEMS -------------*/
DECL|macro|MSBM_BASE
mdefine_line|#define&t;MSBM_BASE&t;&t;&t;0x23d
DECL|macro|MS_MSE_DATA_PORT
mdefine_line|#define&t;MS_MSE_DATA_PORT&t;        0x23d
DECL|macro|MS_MSE_SIGNATURE_PORT
mdefine_line|#define&t;MS_MSE_SIGNATURE_PORT&t;        0x23e
DECL|macro|MS_MSE_CONTROL_PORT
mdefine_line|#define&t;MS_MSE_CONTROL_PORT&t;        0x23c
DECL|macro|MS_MSE_CONFIG_PORT
mdefine_line|#define&t;MS_MSE_CONFIG_PORT&t;&t;0x23f
DECL|macro|MSBM_EXTENT
mdefine_line|#define&t;MSBM_EXTENT&t;&t;&t;0x3
DECL|macro|MS_MSE_ENABLE_INTERRUPTS
mdefine_line|#define&t;MS_MSE_ENABLE_INTERRUPTS&t;0x11
DECL|macro|MS_MSE_DISABLE_INTERRUPTS
mdefine_line|#define&t;MS_MSE_DISABLE_INTERRUPTS&t;0x10
DECL|macro|MS_MSE_READ_BUTTONS
mdefine_line|#define&t;MS_MSE_READ_BUTTONS             0x00
DECL|macro|MS_MSE_READ_X
mdefine_line|#define&t;MS_MSE_READ_X&t;&t;        0x01
DECL|macro|MS_MSE_READ_Y
mdefine_line|#define&t;MS_MSE_READ_Y                   0x02
DECL|macro|MS_MSE_START
mdefine_line|#define MS_MSE_START                    0x80
DECL|macro|MS_MSE_COMMAND_MODE
mdefine_line|#define MS_MSE_COMMAND_MODE             0x07
multiline_comment|/* useful microsoft busmouse macros */
DECL|macro|MS_MSE_INT_OFF
mdefine_line|#define MS_MSE_INT_OFF() {outb(MS_MSE_COMMAND_MODE, MS_MSE_CONTROL_PORT); &bslash;&n;&t;&t;&t;    outb(MS_MSE_DISABLE_INTERRUPTS, MS_MSE_DATA_PORT);}
DECL|macro|MS_MSE_INT_ON
mdefine_line|#define MS_MSE_INT_ON()  {outb(MS_MSE_COMMAND_MODE, MS_MSE_CONTROL_PORT); &bslash;&n;&t;&t;&t;    outb(MS_MSE_ENABLE_INTERRUPTS, MS_MSE_DATA_PORT);}
DECL|struct|mouse_status
r_struct
id|mouse_status
(brace
DECL|member|buttons
r_int
r_char
id|buttons
suffix:semicolon
DECL|member|latch_buttons
r_int
r_char
id|latch_buttons
suffix:semicolon
DECL|member|dx
r_int
id|dx
suffix:semicolon
DECL|member|dy
r_int
id|dy
suffix:semicolon
DECL|member|present
r_int
id|present
suffix:semicolon
DECL|member|ready
r_int
id|ready
suffix:semicolon
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|fasyncptr
r_struct
id|fasync_struct
op_star
id|fasyncptr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Function Prototypes */
macro_line|#endif
eof
