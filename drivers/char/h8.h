multiline_comment|/*&n; */
macro_line|#ifndef __H8_H__
DECL|macro|__H8_H__
mdefine_line|#define __H8_H__
multiline_comment|/*&n; * Register address and offsets&n; */
DECL|macro|H8_BASE_ADDR
mdefine_line|#define H8_BASE_ADDR                   0x170            /* default */
DECL|macro|H8_IRQ
mdefine_line|#define H8_IRQ&t;&t;&t;       9                /* default */
DECL|macro|H8_STATUS_REG_OFF
mdefine_line|#define H8_STATUS_REG_OFF              0x4              
DECL|macro|H8_CMD_REG_OFF
mdefine_line|#define H8_CMD_REG_OFF                 0x4
DECL|macro|H8_DATA_REG_OFF
mdefine_line|#define H8_DATA_REG_OFF                0x0
multiline_comment|/* H8 register bit definitions */
multiline_comment|/* status register */
DECL|macro|H8_OFULL
mdefine_line|#define H8_OFULL                       0x1              /* output data register full */
DECL|macro|H8_IFULL
mdefine_line|#define H8_IFULL                       0x2              /* input data register full */
DECL|macro|H8_CMD
mdefine_line|#define H8_CMD                         0x8              /* command / not data */
DECL|macro|H8_INTR
mdefine_line|#define H8_INTR                        0xfa
DECL|macro|H8_NACK
mdefine_line|#define H8_NACK                        0xfc
DECL|macro|H8_BYTE_LEVEL_ACK
mdefine_line|#define H8_BYTE_LEVEL_ACK              0xfd
DECL|macro|H8_CMD_ACK
mdefine_line|#define H8_CMD_ACK                     0xfe
DECL|macro|H8_SYNC_BYTE
mdefine_line|#define H8_SYNC_BYTE                   0x99
multiline_comment|/*&n; * H8 command definitions&n; */
multiline_comment|/* System info commands */
DECL|macro|H8_SYNC
mdefine_line|#define H8_SYNC                         0x0
DECL|macro|H8_RD_SN
mdefine_line|#define H8_RD_SN                        0x1
DECL|macro|H8_RD_ENET_ADDR
mdefine_line|#define H8_RD_ENET_ADDR                 0x2
DECL|macro|H8_RD_HW_VER
mdefine_line|#define H8_RD_HW_VER                    0x3
DECL|macro|H8_RD_MIC_VER
mdefine_line|#define H8_RD_MIC_VER                   0x4
DECL|macro|H8_RD_MAX_TEMP
mdefine_line|#define H8_RD_MAX_TEMP                  0x5
DECL|macro|H8_RD_MIN_TEMP
mdefine_line|#define H8_RD_MIN_TEMP                  0x6
DECL|macro|H8_RD_CURR_TEMP
mdefine_line|#define H8_RD_CURR_TEMP                 0x7
DECL|macro|H8_RD_SYS_VARIENT
mdefine_line|#define H8_RD_SYS_VARIENT               0x8
DECL|macro|H8_RD_PWR_ON_CYCLES
mdefine_line|#define H8_RD_PWR_ON_CYCLES             0x9
DECL|macro|H8_RD_PWR_ON_SECS
mdefine_line|#define H8_RD_PWR_ON_SECS               0xa
DECL|macro|H8_RD_RESET_STATUS
mdefine_line|#define H8_RD_RESET_STATUS              0xb
DECL|macro|H8_RD_PWR_DN_STATUS
mdefine_line|#define H8_RD_PWR_DN_STATUS             0xc
DECL|macro|H8_RD_EVENT_STATUS
mdefine_line|#define H8_RD_EVENT_STATUS              0xd
DECL|macro|H8_RD_ROM_CKSM
mdefine_line|#define H8_RD_ROM_CKSM                  0xe
DECL|macro|H8_RD_EXT_STATUS
mdefine_line|#define H8_RD_EXT_STATUS                0xf
DECL|macro|H8_RD_USER_CFG
mdefine_line|#define H8_RD_USER_CFG                  0x10
DECL|macro|H8_RD_INT_BATT_VOLT
mdefine_line|#define H8_RD_INT_BATT_VOLT             0x11
DECL|macro|H8_RD_DC_INPUT_VOLT
mdefine_line|#define H8_RD_DC_INPUT_VOLT             0x12
DECL|macro|H8_RD_HORIZ_PTR_VOLT
mdefine_line|#define H8_RD_HORIZ_PTR_VOLT            0x13
DECL|macro|H8_RD_VERT_PTR_VOLT
mdefine_line|#define H8_RD_VERT_PTR_VOLT             0x14
DECL|macro|H8_RD_EEPROM_STATUS
mdefine_line|#define H8_RD_EEPROM_STATUS             0x15
DECL|macro|H8_RD_ERR_STATUS
mdefine_line|#define H8_RD_ERR_STATUS                0x16
DECL|macro|H8_RD_NEW_BUSY_SPEED
mdefine_line|#define H8_RD_NEW_BUSY_SPEED            0x17
DECL|macro|H8_RD_CONFIG_INTERFACE
mdefine_line|#define H8_RD_CONFIG_INTERFACE          0x18
DECL|macro|H8_RD_INT_BATT_STATUS
mdefine_line|#define H8_RD_INT_BATT_STATUS           0x19
DECL|macro|H8_RD_EXT_BATT_STATUS
mdefine_line|#define H8_RD_EXT_BATT_STATUS           0x1a
DECL|macro|H8_RD_PWR_UP_STATUS
mdefine_line|#define H8_RD_PWR_UP_STATUS             0x1b
DECL|macro|H8_RD_EVENT_STATUS_MASK
mdefine_line|#define H8_RD_EVENT_STATUS_MASK         0x56
multiline_comment|/* Read/write/modify commands */
DECL|macro|H8_CTL_EMU_BITPORT
mdefine_line|#define H8_CTL_EMU_BITPORT              0x32
DECL|macro|H8_DEVICE_CONTROL
mdefine_line|#define H8_DEVICE_CONTROL               0x21
DECL|macro|H8_CTL_TFT_BRT_DC
mdefine_line|#define H8_CTL_TFT_BRT_DC               0x22
DECL|macro|H8_CTL_WATCHDOG
mdefine_line|#define H8_CTL_WATCHDOG                 0x23
DECL|macro|H8_CTL_MIC_PROT
mdefine_line|#define H8_CTL_MIC_PROT                 0x24
DECL|macro|H8_CTL_INT_BATT_CHG
mdefine_line|#define H8_CTL_INT_BATT_CHG             0x25
DECL|macro|H8_CTL_EXT_BATT_CHG
mdefine_line|#define H8_CTL_EXT_BATT_CHG             0x26
DECL|macro|H8_CTL_MARK_SPACE
mdefine_line|#define H8_CTL_MARK_SPACE               0x27
DECL|macro|H8_CTL_MOUSE_SENSITIVITY
mdefine_line|#define H8_CTL_MOUSE_SENSITIVITY        0x28
DECL|macro|H8_CTL_DIAG_MODE
mdefine_line|#define H8_CTL_DIAG_MODE                0x29
DECL|macro|H8_CTL_IDLE_AND_BUSY_SPDS
mdefine_line|#define H8_CTL_IDLE_AND_BUSY_SPDS       0x2a
DECL|macro|H8_CTL_TFT_BRT_BATT
mdefine_line|#define H8_CTL_TFT_BRT_BATT             0x2b
DECL|macro|H8_CTL_UPPER_TEMP
mdefine_line|#define H8_CTL_UPPER_TEMP               0x2c
DECL|macro|H8_CTL_LOWER_TEMP
mdefine_line|#define H8_CTL_LOWER_TEMP               0x2d
DECL|macro|H8_CTL_TEMP_CUTOUT
mdefine_line|#define H8_CTL_TEMP_CUTOUT              0x2e
DECL|macro|H8_CTL_WAKEUP
mdefine_line|#define H8_CTL_WAKEUP                   0x2f
DECL|macro|H8_CTL_CHG_THRESHOLD
mdefine_line|#define H8_CTL_CHG_THRESHOLD            0x30
DECL|macro|H8_CTL_TURBO_MODE
mdefine_line|#define H8_CTL_TURBO_MODE               0x31
DECL|macro|H8_SET_DIAG_STATUS
mdefine_line|#define H8_SET_DIAG_STATUS              0x40
DECL|macro|H8_SOFTWARE_RESET
mdefine_line|#define H8_SOFTWARE_RESET               0x41
DECL|macro|H8_RECAL_PTR
mdefine_line|#define H8_RECAL_PTR                    0x42
DECL|macro|H8_SET_INT_BATT_PERCENT
mdefine_line|#define H8_SET_INT_BATT_PERCENT         0x43
DECL|macro|H8_WRT_CFG_INTERFACE_REG
mdefine_line|#define H8_WRT_CFG_INTERFACE_REG        0x45
DECL|macro|H8_WRT_EVENT_STATUS_MASK
mdefine_line|#define H8_WRT_EVENT_STATUS_MASK        0x57
DECL|macro|H8_ENTER_POST_MODE
mdefine_line|#define H8_ENTER_POST_MODE              0x46
DECL|macro|H8_EXIT_POST_MODE
mdefine_line|#define H8_EXIT_POST_MODE               0x47
multiline_comment|/* Block transfer commands */
DECL|macro|H8_RD_EEPROM
mdefine_line|#define H8_RD_EEPROM                    0x50
DECL|macro|H8_WRT_EEPROM
mdefine_line|#define H8_WRT_EEPROM                   0x51
DECL|macro|H8_WRT_TO_STATUS_DISP
mdefine_line|#define H8_WRT_TO_STATUS_DISP           0x52
DECL|macro|H8_DEFINE_SPC_CHAR
mdefine_line|#define H8_DEFINE_SPC_CHAR              0x53
multiline_comment|/* Generic commands */
DECL|macro|H8_DEFINE_TABLE_STRING_ENTRY
mdefine_line|#define H8_DEFINE_TABLE_STRING_ENTRY    0x60
multiline_comment|/* Battery control commands */
DECL|macro|H8_PERFORM_EMU_CMD
mdefine_line|#define H8_PERFORM_EMU_CMD              0x70
DECL|macro|H8_EMU_RD_REG
mdefine_line|#define H8_EMU_RD_REG                   0x71
DECL|macro|H8_EMU_WRT_REG
mdefine_line|#define H8_EMU_WRT_REG                  0x72
DECL|macro|H8_EMU_RD_RAM
mdefine_line|#define H8_EMU_RD_RAM                   0x73
DECL|macro|H8_EMU_WRT_RAM
mdefine_line|#define H8_EMU_WRT_RAM                  0x74
DECL|macro|H8_BQ_RD_REG
mdefine_line|#define H8_BQ_RD_REG                    0x75
DECL|macro|H8_BQ_WRT_REG
mdefine_line|#define H8_BQ_WRT_REG                   0x76
multiline_comment|/* System admin commands */
DECL|macro|H8_PWR_OFF
mdefine_line|#define H8_PWR_OFF                      0x80
multiline_comment|/*&n; * H8 command related definitions&n; */
multiline_comment|/* device control argument bits */
DECL|macro|H8_ENAB_EXTSMI
mdefine_line|#define H8_ENAB_EXTSMI                  0x1
DECL|macro|H8_DISAB_IRQ
mdefine_line|#define H8_DISAB_IRQ                    0x2
DECL|macro|H8_ENAB_FLASH_WRT
mdefine_line|#define H8_ENAB_FLASH_WRT               0x4
DECL|macro|H8_ENAB_THERM
mdefine_line|#define H8_ENAB_THERM                   0x8
DECL|macro|H8_ENAB_INT_PTR
mdefine_line|#define H8_ENAB_INT_PTR                 0x10
DECL|macro|H8_ENAB_LOW_SPD_IND
mdefine_line|#define H8_ENAB_LOW_SPD_IND             0x20
DECL|macro|H8_ENAB_EXT_PTR
mdefine_line|#define H8_ENAB_EXT_PTR                 0x40
DECL|macro|H8_DISAB_PWR_OFF_SW
mdefine_line|#define H8_DISAB_PWR_OFF_SW             0x80
DECL|macro|H8_POWER_OFF
mdefine_line|#define H8_POWER_OFF&t;&t;&t;0x80
multiline_comment|/* H8 read event status bits */
DECL|macro|H8_DC_CHANGE
mdefine_line|#define H8_DC_CHANGE                    0x1
DECL|macro|H8_INT_BATT_LOW
mdefine_line|#define H8_INT_BATT_LOW                 0x2
DECL|macro|H8_INT_BATT_CHARGE_THRESHOLD
mdefine_line|#define H8_INT_BATT_CHARGE_THRESHOLD    0x4
DECL|macro|H8_INT_BATT_CHARGE_STATE
mdefine_line|#define H8_INT_BATT_CHARGE_STATE        0x8
DECL|macro|H8_INT_BATT_STATUS
mdefine_line|#define H8_INT_BATT_STATUS              0x10
DECL|macro|H8_EXT_BATT_CHARGE_STATE
mdefine_line|#define H8_EXT_BATT_CHARGE_STATE        0x20
DECL|macro|H8_EXT_BATT_LOW
mdefine_line|#define H8_EXT_BATT_LOW                 0x40
DECL|macro|H8_EXT_BATT_STATUS
mdefine_line|#define H8_EXT_BATT_STATUS              0x80
DECL|macro|H8_THERMAL_THRESHOLD
mdefine_line|#define H8_THERMAL_THRESHOLD            0x100
DECL|macro|H8_WATCHDOG
mdefine_line|#define H8_WATCHDOG                     0x200
DECL|macro|H8_DOCKING_STATION_STATUS
mdefine_line|#define H8_DOCKING_STATION_STATUS       0x400
DECL|macro|H8_EXT_MOUSE_OR_CASE_SWITCH
mdefine_line|#define H8_EXT_MOUSE_OR_CASE_SWITCH     0x800
DECL|macro|H8_KEYBOARD
mdefine_line|#define H8_KEYBOARD                     0x1000
DECL|macro|H8_BATT_CHANGE_OVER
mdefine_line|#define H8_BATT_CHANGE_OVER             0x2000
DECL|macro|H8_POWER_BUTTON
mdefine_line|#define H8_POWER_BUTTON                 0x4000
DECL|macro|H8_SHUTDOWN
mdefine_line|#define H8_SHUTDOWN                     0x8000
multiline_comment|/* H8 control idle and busy speeds */
DECL|macro|H8_SPEED_LOW
mdefine_line|#define H8_SPEED_LOW                    0x1
DECL|macro|H8_SPEED_MED
mdefine_line|#define H8_SPEED_MED                    0x2
DECL|macro|H8_SPEED_HI
mdefine_line|#define H8_SPEED_HI                     0x3
DECL|macro|H8_SPEED_LOCKED
mdefine_line|#define H8_SPEED_LOCKED                 0x80
DECL|macro|H8_MAX_CMD_SIZE
mdefine_line|#define H8_MAX_CMD_SIZE                 18      
DECL|macro|H8_Q_ALLOC_AMOUNT
mdefine_line|#define H8_Q_ALLOC_AMOUNT               10      
multiline_comment|/* H8 state field values */
DECL|macro|H8_IDLE
mdefine_line|#define H8_IDLE                         1
DECL|macro|H8_XMIT
mdefine_line|#define H8_XMIT                         2
DECL|macro|H8_RCV
mdefine_line|#define H8_RCV                          3
DECL|macro|H8_RESYNC
mdefine_line|#define H8_RESYNC                       4
DECL|macro|H8_INTR_MODE
mdefine_line|#define H8_INTR_MODE                    5
multiline_comment|/* Mask values for control functions */
DECL|macro|UTH_HYSTERESIS
mdefine_line|#define UTH_HYSTERESIS                  5
DECL|macro|DEFAULT_UTHERMAL_THRESHOLD
mdefine_line|#define DEFAULT_UTHERMAL_THRESHOLD      115
DECL|macro|H8_TIMEOUT_INTERVAL
mdefine_line|#define H8_TIMEOUT_INTERVAL&t;&t;30
DECL|macro|H8_RUN
mdefine_line|#define H8_RUN                          4
DECL|macro|H8_GET_MAX_TEMP
mdefine_line|#define H8_GET_MAX_TEMP                 0x1
DECL|macro|H8_GET_CURR_TEMP
mdefine_line|#define H8_GET_CURR_TEMP                0x2
DECL|macro|H8_GET_UPPR_THRMAL_THOLD
mdefine_line|#define H8_GET_UPPR_THRMAL_THOLD        0x4
DECL|macro|H8_GET_ETHERNET_ADDR
mdefine_line|#define H8_GET_ETHERNET_ADDR            0x8
DECL|macro|H8_SYNC_OP
mdefine_line|#define H8_SYNC_OP                      0x10 
DECL|macro|H8_SET_UPPR_THRMAL_THOLD
mdefine_line|#define H8_SET_UPPR_THRMAL_THOLD        0x20
DECL|macro|H8_GET_INT_BATT_STAT
mdefine_line|#define H8_GET_INT_BATT_STAT            0x40
DECL|macro|H8_GET_CPU_SPD
mdefine_line|#define H8_GET_CPU_SPD                  0x80
DECL|macro|H8_MANAGE_UTHERM
mdefine_line|#define H8_MANAGE_UTHERM                0x100 
DECL|macro|H8_MANAGE_LTHERM
mdefine_line|#define H8_MANAGE_LTHERM                0x200 
DECL|macro|H8_HALT
mdefine_line|#define H8_HALT                         0x400 
DECL|macro|H8_CRASH
mdefine_line|#define H8_CRASH                        0x800 
DECL|macro|H8_GET_EXT_STATUS
mdefine_line|#define H8_GET_EXT_STATUS               0x10000
DECL|macro|H8_MANAGE_QUIET
mdefine_line|#define H8_MANAGE_QUIET                 0x20000
DECL|macro|H8_MANAGE_SPEEDUP
mdefine_line|#define H8_MANAGE_SPEEDUP               0x40000
DECL|macro|H8_MANAGE_BATTERY
mdefine_line|#define H8_MANAGE_BATTERY               0x80000
DECL|macro|H8_SYSTEM_DELAY_TEST
mdefine_line|#define H8_SYSTEM_DELAY_TEST            0x100000
DECL|macro|H8_POWER_SWITCH_TEST
mdefine_line|#define H8_POWER_SWITCH_TEST            0x200000
multiline_comment|/* CPU speeds and clock divisor values */
DECL|macro|MHZ_14
mdefine_line|#define MHZ_14                           5
DECL|macro|MHZ_28
mdefine_line|#define MHZ_28                           4
DECL|macro|MHZ_57
mdefine_line|#define MHZ_57                           3
DECL|macro|MHZ_115
mdefine_line|#define MHZ_115                          2
DECL|macro|MHZ_230
mdefine_line|#define MHZ_230                          0 
multiline_comment|/*&n; * H8 data&n; */
DECL|struct|h8_data
r_struct
id|h8_data
(brace
DECL|member|ser_num
id|u_int
id|ser_num
suffix:semicolon
DECL|member|ether_add
id|u_char
id|ether_add
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|hw_ver
id|u_short
id|hw_ver
suffix:semicolon
DECL|member|mic_ver
id|u_short
id|mic_ver
suffix:semicolon
DECL|member|max_tmp
id|u_short
id|max_tmp
suffix:semicolon
DECL|member|min_tmp
id|u_short
id|min_tmp
suffix:semicolon
DECL|member|cur_tmp
id|u_short
id|cur_tmp
suffix:semicolon
DECL|member|sys_var
id|u_int
id|sys_var
suffix:semicolon
DECL|member|pow_on
id|u_int
id|pow_on
suffix:semicolon
DECL|member|pow_on_secs
id|u_int
id|pow_on_secs
suffix:semicolon
DECL|member|reset_status
id|u_char
id|reset_status
suffix:semicolon
DECL|member|pwr_dn_status
id|u_char
id|pwr_dn_status
suffix:semicolon
DECL|member|event_status
id|u_short
id|event_status
suffix:semicolon
DECL|member|rom_cksm
id|u_short
id|rom_cksm
suffix:semicolon
DECL|member|ext_status
id|u_short
id|ext_status
suffix:semicolon
DECL|member|u_cfg
id|u_short
id|u_cfg
suffix:semicolon
DECL|member|ibatt_volt
id|u_char
id|ibatt_volt
suffix:semicolon
DECL|member|dc_volt
id|u_char
id|dc_volt
suffix:semicolon
DECL|member|ptr_horiz
id|u_char
id|ptr_horiz
suffix:semicolon
DECL|member|ptr_vert
id|u_char
id|ptr_vert
suffix:semicolon
DECL|member|eeprom_status
id|u_char
id|eeprom_status
suffix:semicolon
DECL|member|error_status
id|u_char
id|error_status
suffix:semicolon
DECL|member|new_busy_speed
id|u_char
id|new_busy_speed
suffix:semicolon
DECL|member|cfg_interface
id|u_char
id|cfg_interface
suffix:semicolon
DECL|member|int_batt_status
id|u_short
id|int_batt_status
suffix:semicolon
DECL|member|ext_batt_status
id|u_short
id|ext_batt_status
suffix:semicolon
DECL|member|pow_up_status
id|u_char
id|pow_up_status
suffix:semicolon
DECL|member|event_status_mask
id|u_char
id|event_status_mask
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * H8 command buffers&n; */
DECL|struct|h8_cmd_q
r_typedef
r_struct
id|h8_cmd_q
(brace
DECL|member|link
r_struct
id|list_head
id|link
suffix:semicolon
multiline_comment|/* double linked list */
DECL|member|ncmd
r_int
id|ncmd
suffix:semicolon
multiline_comment|/* number of bytes in command */
DECL|member|nrsp
r_int
id|nrsp
suffix:semicolon
multiline_comment|/* number of bytes in response */
DECL|member|cnt
r_int
id|cnt
suffix:semicolon
multiline_comment|/* number of bytes sent/received */
DECL|member|nacks
r_int
id|nacks
suffix:semicolon
multiline_comment|/* number of byte level acks */
DECL|member|cmdbuf
id|u_char
id|cmdbuf
(braket
id|H8_MAX_CMD_SIZE
)braket
suffix:semicolon
multiline_comment|/* buffer to store command */
DECL|member|rcvbuf
id|u_char
id|rcvbuf
(braket
id|H8_MAX_CMD_SIZE
)braket
suffix:semicolon
multiline_comment|/* buffer to store response */
DECL|typedef|h8_cmd_q_t
)brace
id|h8_cmd_q_t
suffix:semicolon
DECL|union|intr_buf
r_union
id|intr_buf
(brace
DECL|member|byte
id|u_char
id|byte
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|word
id|u_int
id|word
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __H8_H_ */
eof
