multiline_comment|/*&n; * linux/include/asm-arm/therm.h: Definitions for Dallas Semiconductor&n; *  DS1620 thermometer driver (as used in the Rebel.com NetWinder)&n; */
macro_line|#ifndef __ASM_THERM_H
DECL|macro|__ASM_THERM_H
mdefine_line|#define __ASM_THERM_H
multiline_comment|/* ioctl numbers for /dev/therm */
DECL|macro|CMD_SET_THERMOSTATE
mdefine_line|#define CMD_SET_THERMOSTATE&t;0x53
DECL|macro|CMD_GET_THERMOSTATE
mdefine_line|#define CMD_GET_THERMOSTATE&t;0x54
DECL|macro|CMD_GET_STATUS
mdefine_line|#define CMD_GET_STATUS&t;&t;0x56
DECL|macro|CMD_GET_TEMPERATURE
mdefine_line|#define CMD_GET_TEMPERATURE&t;0x57
DECL|macro|CMD_SET_THERMOSTATE2
mdefine_line|#define CMD_SET_THERMOSTATE2&t;0x58
DECL|macro|CMD_GET_THERMOSTATE2
mdefine_line|#define CMD_GET_THERMOSTATE2&t;0x59
DECL|macro|CMD_GET_TEMPERATURE2
mdefine_line|#define CMD_GET_TEMPERATURE2&t;0x5a
DECL|macro|CMD_GET_FAN
mdefine_line|#define CMD_GET_FAN&t;&t;0x5b
DECL|macro|CMD_SET_FAN
mdefine_line|#define CMD_SET_FAN&t;&t;0x5c
DECL|macro|FAN_OFF
mdefine_line|#define FAN_OFF&t;&t;&t;0
DECL|macro|FAN_ON
mdefine_line|#define FAN_ON&t;&t;&t;1
DECL|macro|FAN_ALWAYS_ON
mdefine_line|#define FAN_ALWAYS_ON&t;&t;2
DECL|struct|therm
r_struct
id|therm
(brace
DECL|member|hi
r_int
id|hi
suffix:semicolon
DECL|member|lo
r_int
id|lo
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
