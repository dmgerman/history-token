macro_line|#ifndef __THERM_PMAC_7_2_H__
DECL|macro|__THERM_PMAC_7_2_H__
mdefine_line|#define __THERM_PMAC_7_2_H__
DECL|typedef|fu16
r_typedef
r_int
r_int
id|fu16
suffix:semicolon
DECL|typedef|fs32
r_typedef
r_int
id|fs32
suffix:semicolon
DECL|typedef|fs16
r_typedef
r_int
id|fs16
suffix:semicolon
DECL|struct|mpu_data
r_struct
id|mpu_data
(brace
DECL|member|signature
id|u8
id|signature
suffix:semicolon
multiline_comment|/* 0x00 - EEPROM sig. */
DECL|member|bytes_used
id|u8
id|bytes_used
suffix:semicolon
multiline_comment|/* 0x01 - Bytes used in eeprom (160 ?) */
DECL|member|size
id|u8
id|size
suffix:semicolon
multiline_comment|/* 0x02 - EEPROM size (256 ?) */
DECL|member|version
id|u8
id|version
suffix:semicolon
multiline_comment|/* 0x03 - EEPROM version */
DECL|member|data_revision
id|u32
id|data_revision
suffix:semicolon
multiline_comment|/* 0x04 - Dataset revision */
DECL|member|processor_bin_code
id|u8
id|processor_bin_code
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 0x08 - Processor BIN code */
DECL|member|bin_code_expansion
id|u8
id|bin_code_expansion
suffix:semicolon
multiline_comment|/* 0x0b - ??? (padding ?) */
DECL|member|processor_num
id|u8
id|processor_num
suffix:semicolon
multiline_comment|/* 0x0c - Number of CPUs on this MPU */
DECL|member|input_mul_bus_div
id|u8
id|input_mul_bus_div
suffix:semicolon
multiline_comment|/* 0x0d - Clock input multiplier/bus divider */
DECL|member|reserved1
id|u8
id|reserved1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x0e - */
DECL|member|input_clk_freq_high
id|u32
id|input_clk_freq_high
suffix:semicolon
multiline_comment|/* 0x10 - Input clock frequency high */
DECL|member|cpu_nb_target_cycles
id|u8
id|cpu_nb_target_cycles
suffix:semicolon
multiline_comment|/* 0x14 - ??? */
DECL|member|cpu_statlat
id|u8
id|cpu_statlat
suffix:semicolon
multiline_comment|/* 0x15 - ??? */
DECL|member|cpu_snooplat
id|u8
id|cpu_snooplat
suffix:semicolon
multiline_comment|/* 0x16 - ??? */
DECL|member|cpu_snoopacc
id|u8
id|cpu_snoopacc
suffix:semicolon
multiline_comment|/* 0x17 - ??? */
DECL|member|nb_paamwin
id|u8
id|nb_paamwin
suffix:semicolon
multiline_comment|/* 0x18 - ??? */
DECL|member|nb_statlat
id|u8
id|nb_statlat
suffix:semicolon
multiline_comment|/* 0x19 - ??? */
DECL|member|nb_snooplat
id|u8
id|nb_snooplat
suffix:semicolon
multiline_comment|/* 0x1a - ??? */
DECL|member|nb_snoopwin
id|u8
id|nb_snoopwin
suffix:semicolon
multiline_comment|/* 0x1b - ??? */
DECL|member|api_bus_mode
id|u8
id|api_bus_mode
suffix:semicolon
multiline_comment|/* 0x1c - ??? */
DECL|member|reserved2
id|u8
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 0x1d - */
DECL|member|input_clk_freq_low
id|u32
id|input_clk_freq_low
suffix:semicolon
multiline_comment|/* 0x20 - Input clock frequency low */
DECL|member|processor_card_slot
id|u8
id|processor_card_slot
suffix:semicolon
multiline_comment|/* 0x24 - Processor card slot number */
DECL|member|reserved3
id|u8
id|reserved3
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x25 - */
DECL|member|padjmax
id|u8
id|padjmax
suffix:semicolon
multiline_comment|/* 0x27 - Max power adjustment (Not in OF!) */
DECL|member|ttarget
id|u8
id|ttarget
suffix:semicolon
multiline_comment|/* 0x28 - Target temperature */
DECL|member|tmax
id|u8
id|tmax
suffix:semicolon
multiline_comment|/* 0x29 - Max temperature */
DECL|member|pmaxh
id|u8
id|pmaxh
suffix:semicolon
multiline_comment|/* 0x2a - Max power */
DECL|member|tguardband
id|u8
id|tguardband
suffix:semicolon
multiline_comment|/* 0x2b - Guardband temp ??? Hist. len in OSX */
DECL|member|pid_gp
id|fs32
id|pid_gp
suffix:semicolon
multiline_comment|/* 0x2c - PID proportional gain */
DECL|member|pid_gr
id|fs32
id|pid_gr
suffix:semicolon
multiline_comment|/* 0x30 - PID reset gain */
DECL|member|pid_gd
id|fs32
id|pid_gd
suffix:semicolon
multiline_comment|/* 0x34 - PID derivative gain */
DECL|member|voph
id|fu16
id|voph
suffix:semicolon
multiline_comment|/* 0x38 - Vop High */
DECL|member|vopl
id|fu16
id|vopl
suffix:semicolon
multiline_comment|/* 0x3a - Vop Low */
DECL|member|nactual_die
id|fs16
id|nactual_die
suffix:semicolon
multiline_comment|/* 0x3c - nActual Die */
DECL|member|nactual_heatsink
id|fs16
id|nactual_heatsink
suffix:semicolon
multiline_comment|/* 0x3e - nActual Heatsink */
DECL|member|nactual_system
id|fs16
id|nactual_system
suffix:semicolon
multiline_comment|/* 0x40 - nActual System */
DECL|member|calibration_flags
id|u16
id|calibration_flags
suffix:semicolon
multiline_comment|/* 0x42 - Calibration flags */
DECL|member|mdiode
id|fu16
id|mdiode
suffix:semicolon
multiline_comment|/* 0x44 - Diode M value (scaling factor) */
DECL|member|bdiode
id|fs16
id|bdiode
suffix:semicolon
multiline_comment|/* 0x46 - Diode B value (offset) */
DECL|member|theta_heat_sink
id|fs32
id|theta_heat_sink
suffix:semicolon
multiline_comment|/* 0x48 - Theta heat sink */
DECL|member|rminn_intake_fan
id|u16
id|rminn_intake_fan
suffix:semicolon
multiline_comment|/* 0x4c - Intake fan min RPM */
DECL|member|rmaxn_intake_fan
id|u16
id|rmaxn_intake_fan
suffix:semicolon
multiline_comment|/* 0x4e - Intake fan max RPM */
DECL|member|rminn_exhaust_fan
id|u16
id|rminn_exhaust_fan
suffix:semicolon
multiline_comment|/* 0x50 - Exhaust fan min RPM */
DECL|member|rmaxn_exhaust_fan
id|u16
id|rmaxn_exhaust_fan
suffix:semicolon
multiline_comment|/* 0x52 - Exhaust fan max RPM */
DECL|member|processor_part_num
id|u8
id|processor_part_num
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x54 - Processor part number */
DECL|member|processor_lot_num
id|u32
id|processor_lot_num
suffix:semicolon
multiline_comment|/* 0x5c - Processor lot number */
DECL|member|orig_card_sernum
id|u8
id|orig_card_sernum
(braket
l_int|0x10
)braket
suffix:semicolon
multiline_comment|/* 0x60 - Card original serial number */
DECL|member|curr_card_sernum
id|u8
id|curr_card_sernum
(braket
l_int|0x10
)braket
suffix:semicolon
multiline_comment|/* 0x70 - Card current serial number */
DECL|member|mlb_sernum
id|u8
id|mlb_sernum
(braket
l_int|0x18
)braket
suffix:semicolon
multiline_comment|/* 0x80 - MLB serial number */
DECL|member|checksum1
id|u32
id|checksum1
suffix:semicolon
multiline_comment|/* 0x98 - */
DECL|member|checksum2
id|u32
id|checksum2
suffix:semicolon
multiline_comment|/* 0x9c - */
)brace
suffix:semicolon
multiline_comment|/* Total size = 0xa0 */
multiline_comment|/* Display a 16.16 fixed point value */
DECL|macro|FIX32TOPRINT
mdefine_line|#define FIX32TOPRINT(f)&t;((f) &gt;&gt; 16),((((f) &amp; 0xffff) * 1000) &gt;&gt; 16)
multiline_comment|/*&n; * Maximum number of seconds to be in critical state (after a&n; * normal shutdown attempt). If the machine isn&squot;t down after&n; * this counter elapses, we force an immediate machine power&n; * off.&n; */
DECL|macro|MAX_CRITICAL_STATE
mdefine_line|#define MAX_CRITICAL_STATE&t;&t;&t;30
DECL|variable|critical_overtemp_path
r_static
r_char
op_star
id|critical_overtemp_path
op_assign
l_string|&quot;/sbin/critical_overtemp&quot;
suffix:semicolon
multiline_comment|/*&n; * This option is &quot;weird&quot; :) Basically, if you define this to 1&n; * the control loop for the RPMs fans (not PWMs) will apply the&n; * correction factor obtained from the PID to the _actual_ RPM&n; * speed read from the FCU.&n; * If you define the below constant to 0, then it will be&n; * applied to the setpoint RPM speed, that is basically the&n; * speed we proviously &quot;asked&quot; for.&n; *&n; * I&squot;m not sure which of these Apple&squot;s algorithm is supposed&n; * to use&n; */
DECL|macro|RPM_PID_USE_ACTUAL_SPEED
mdefine_line|#define RPM_PID_USE_ACTUAL_SPEED&t;&t;0
multiline_comment|/*&n; * i2c IDs. Currently, we hard code those and assume that&n; * the FCU is on U3 bus 1 while all sensors are on U3 bus&n; * 0. This appear to be safe enough for this first version&n; * of the driver, though I would accept any clean patch&n; * doing a better use of the device-tree without turning the&n; * while i2c registration mecanism into a racy mess&n; */
DECL|macro|FAN_CTRLER_ID
mdefine_line|#define FAN_CTRLER_ID&t;&t;0x15e
DECL|macro|SUPPLY_MONITOR_ID
mdefine_line|#define SUPPLY_MONITOR_ID      &t;0x58
DECL|macro|SUPPLY_MONITORB_ID
mdefine_line|#define SUPPLY_MONITORB_ID     &t;0x5a
DECL|macro|DRIVES_DALLAS_ID
mdefine_line|#define DRIVES_DALLAS_ID&t;0x94
DECL|macro|BACKSIDE_MAX_ID
mdefine_line|#define BACKSIDE_MAX_ID&t;&t;0x98
multiline_comment|/*&n; * Some MAX6690 &amp; DS1775 register definitions&n; */
DECL|macro|MAX6690_INT_TEMP
mdefine_line|#define MAX6690_INT_TEMP&t;0
DECL|macro|MAX6690_EXT_TEMP
mdefine_line|#define MAX6690_EXT_TEMP&t;1
DECL|macro|DS1775_TEMP
mdefine_line|#define DS1775_TEMP&t;&t;0
multiline_comment|/*&n; * Scaling factors for the AD7417 ADC converters (except&n; * for the CPU diode which is obtained from the EEPROM).&n; * Those values are obtained from the property list of&n; * the darwin driver&n; */
DECL|macro|ADC_12V_CURRENT_SCALE
mdefine_line|#define ADC_12V_CURRENT_SCALE&t;0x0320&t;/* _AD2 */
DECL|macro|ADC_CPU_VOLTAGE_SCALE
mdefine_line|#define ADC_CPU_VOLTAGE_SCALE&t;0x00a0&t;/* _AD3 */
DECL|macro|ADC_CPU_CURRENT_SCALE
mdefine_line|#define ADC_CPU_CURRENT_SCALE&t;0x1f40&t;/* _AD4 */
multiline_comment|/*&n; * PID factors for the U3/Backside fan control loop. We have 2 sets&n; * of values here, one set for U3 and one set for U3H&n; */
DECL|macro|BACKSIDE_FAN_PWM_DEFAULT_ID
mdefine_line|#define BACKSIDE_FAN_PWM_DEFAULT_ID&t;1
DECL|macro|BACKSIDE_FAN_PWM_INDEX
mdefine_line|#define BACKSIDE_FAN_PWM_INDEX&t;&t;0
DECL|macro|BACKSIDE_PID_U3_G_d
mdefine_line|#define BACKSIDE_PID_U3_G_d&t;&t;0x02800000
DECL|macro|BACKSIDE_PID_U3H_G_d
mdefine_line|#define BACKSIDE_PID_U3H_G_d&t;&t;0x01400000
DECL|macro|BACKSIDE_PID_G_p
mdefine_line|#define BACKSIDE_PID_G_p&t;&t;0x00500000
DECL|macro|BACKSIDE_PID_G_r
mdefine_line|#define BACKSIDE_PID_G_r&t;&t;0x00000000
DECL|macro|BACKSIDE_PID_U3_INPUT_TARGET
mdefine_line|#define BACKSIDE_PID_U3_INPUT_TARGET&t;0x00410000
DECL|macro|BACKSIDE_PID_U3H_INPUT_TARGET
mdefine_line|#define BACKSIDE_PID_U3H_INPUT_TARGET&t;0x004b0000
DECL|macro|BACKSIDE_PID_INTERVAL
mdefine_line|#define BACKSIDE_PID_INTERVAL&t;&t;5
DECL|macro|BACKSIDE_PID_OUTPUT_MAX
mdefine_line|#define BACKSIDE_PID_OUTPUT_MAX&t;&t;100
DECL|macro|BACKSIDE_PID_U3_OUTPUT_MIN
mdefine_line|#define BACKSIDE_PID_U3_OUTPUT_MIN&t;20
DECL|macro|BACKSIDE_PID_U3H_OUTPUT_MIN
mdefine_line|#define BACKSIDE_PID_U3H_OUTPUT_MIN&t;30
DECL|macro|BACKSIDE_PID_HISTORY_SIZE
mdefine_line|#define BACKSIDE_PID_HISTORY_SIZE&t;2
DECL|struct|basckside_pid_params
r_struct
id|basckside_pid_params
(brace
DECL|member|G_d
id|s32
id|G_d
suffix:semicolon
DECL|member|G_p
id|s32
id|G_p
suffix:semicolon
DECL|member|G_r
id|s32
id|G_r
suffix:semicolon
DECL|member|input_target
id|s32
id|input_target
suffix:semicolon
DECL|member|output_min
id|s32
id|output_min
suffix:semicolon
DECL|member|output_max
id|s32
id|output_max
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|backside_pid_state
r_struct
id|backside_pid_state
(brace
DECL|member|ticks
r_int
id|ticks
suffix:semicolon
DECL|member|monitor
r_struct
id|i2c_client
op_star
id|monitor
suffix:semicolon
DECL|member|sample_history
id|s32
id|sample_history
(braket
id|BACKSIDE_PID_HISTORY_SIZE
)braket
suffix:semicolon
DECL|member|error_history
id|s32
id|error_history
(braket
id|BACKSIDE_PID_HISTORY_SIZE
)braket
suffix:semicolon
DECL|member|cur_sample
r_int
id|cur_sample
suffix:semicolon
DECL|member|last_temp
id|s32
id|last_temp
suffix:semicolon
DECL|member|pwm
r_int
id|pwm
suffix:semicolon
DECL|member|first
r_int
id|first
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * PID factors for the Drive Bay fan control loop&n; */
DECL|macro|DRIVES_FAN_RPM_DEFAULT_ID
mdefine_line|#define DRIVES_FAN_RPM_DEFAULT_ID&t;2
DECL|macro|DRIVES_FAN_RPM_INDEX
mdefine_line|#define DRIVES_FAN_RPM_INDEX&t;&t;1
DECL|macro|DRIVES_PID_G_d
mdefine_line|#define DRIVES_PID_G_d&t;&t;&t;0x01e00000
DECL|macro|DRIVES_PID_G_p
mdefine_line|#define DRIVES_PID_G_p&t;&t;&t;0x00500000
DECL|macro|DRIVES_PID_G_r
mdefine_line|#define DRIVES_PID_G_r&t;&t;&t;0x00000000
DECL|macro|DRIVES_PID_INPUT_TARGET
mdefine_line|#define DRIVES_PID_INPUT_TARGET&t;&t;0x00280000
DECL|macro|DRIVES_PID_INTERVAL
mdefine_line|#define DRIVES_PID_INTERVAL    &t;&t;5
DECL|macro|DRIVES_PID_OUTPUT_MAX
mdefine_line|#define DRIVES_PID_OUTPUT_MAX&t;&t;4000
DECL|macro|DRIVES_PID_OUTPUT_MIN
mdefine_line|#define DRIVES_PID_OUTPUT_MIN&t;&t;300
DECL|macro|DRIVES_PID_HISTORY_SIZE
mdefine_line|#define DRIVES_PID_HISTORY_SIZE&t;&t;2
DECL|struct|drives_pid_state
r_struct
id|drives_pid_state
(brace
DECL|member|ticks
r_int
id|ticks
suffix:semicolon
DECL|member|monitor
r_struct
id|i2c_client
op_star
id|monitor
suffix:semicolon
DECL|member|sample_history
id|s32
id|sample_history
(braket
id|BACKSIDE_PID_HISTORY_SIZE
)braket
suffix:semicolon
DECL|member|error_history
id|s32
id|error_history
(braket
id|BACKSIDE_PID_HISTORY_SIZE
)braket
suffix:semicolon
DECL|member|cur_sample
r_int
id|cur_sample
suffix:semicolon
DECL|member|last_temp
id|s32
id|last_temp
suffix:semicolon
DECL|member|rpm
r_int
id|rpm
suffix:semicolon
DECL|member|first
r_int
id|first
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SLOTS_FAN_PWM_DEFAULT_ID
mdefine_line|#define SLOTS_FAN_PWM_DEFAULT_ID&t;2
DECL|macro|SLOTS_FAN_PWM_INDEX
mdefine_line|#define SLOTS_FAN_PWM_INDEX&t;&t;2
DECL|macro|SLOTS_FAN_DEFAULT_PWM
mdefine_line|#define&t;SLOTS_FAN_DEFAULT_PWM&t;&t;50 /* Do better here ! */
multiline_comment|/*&n; * IDs in Darwin for the sensors &amp; fans&n; *&n; * CPU A AD7417_TEMP&t;10&t;(CPU A ambient temperature)&n; * CPU A AD7417_AD1&t;11&t;(CPU A diode temperature)&n; * CPU A AD7417_AD2&t;12&t;(CPU A 12V current)&n; * CPU A AD7417_AD3&t;13&t;(CPU A voltage)&n; * CPU A AD7417_AD4&t;14&t;(CPU A current)&n; *&n; * CPU A FAKE POWER&t;48&t;(I_V_inputs: 13, 14)&n; *&n; * CPU B AD7417_TEMP&t;15&t;(CPU B ambient temperature)&n; * CPU B AD7417_AD1&t;16&t;(CPU B diode temperature)&n; * CPU B AD7417_AD2&t;17&t;(CPU B 12V current)&n; * CPU B AD7417_AD3&t;18&t;(CPU B voltage)&n; * CPU B AD7417_AD4&t;19&t;(CPU B current)&n; *&n; * CPU B FAKE POWER&t;49&t;(I_V_inputs: 18, 19)&n; */
DECL|macro|CPUA_INTAKE_FAN_RPM_DEFAULT_ID
mdefine_line|#define CPUA_INTAKE_FAN_RPM_DEFAULT_ID&t;3
DECL|macro|CPUA_EXHAUST_FAN_RPM_DEFAULT_ID
mdefine_line|#define CPUA_EXHAUST_FAN_RPM_DEFAULT_ID&t;4
DECL|macro|CPUB_INTAKE_FAN_RPM_DEFAULT_ID
mdefine_line|#define CPUB_INTAKE_FAN_RPM_DEFAULT_ID&t;5
DECL|macro|CPUB_EXHAUST_FAN_RPM_DEFAULT_ID
mdefine_line|#define CPUB_EXHAUST_FAN_RPM_DEFAULT_ID&t;6
DECL|macro|CPUA_INTAKE_FAN_RPM_INDEX
mdefine_line|#define CPUA_INTAKE_FAN_RPM_INDEX&t;3
DECL|macro|CPUA_EXHAUST_FAN_RPM_INDEX
mdefine_line|#define CPUA_EXHAUST_FAN_RPM_INDEX&t;4
DECL|macro|CPUB_INTAKE_FAN_RPM_INDEX
mdefine_line|#define CPUB_INTAKE_FAN_RPM_INDEX&t;5
DECL|macro|CPUB_EXHAUST_FAN_RPM_INDEX
mdefine_line|#define CPUB_EXHAUST_FAN_RPM_INDEX&t;6
DECL|macro|CPU_INTAKE_SCALE
mdefine_line|#define CPU_INTAKE_SCALE&t;&t;0x0000f852
DECL|macro|CPU_TEMP_HISTORY_SIZE
mdefine_line|#define CPU_TEMP_HISTORY_SIZE&t;&t;2
DECL|macro|CPU_POWER_HISTORY_SIZE
mdefine_line|#define CPU_POWER_HISTORY_SIZE&t;&t;10
DECL|macro|CPU_PID_INTERVAL
mdefine_line|#define CPU_PID_INTERVAL&t;&t;1
DECL|macro|CPU_MAX_OVERTEMP
mdefine_line|#define CPU_MAX_OVERTEMP&t;&t;30
DECL|macro|CPUA_PUMP_RPM_INDEX
mdefine_line|#define CPUA_PUMP_RPM_INDEX&t;&t;7
DECL|macro|CPUB_PUMP_RPM_INDEX
mdefine_line|#define CPUB_PUMP_RPM_INDEX&t;&t;8
DECL|macro|CPU_PUMP_OUTPUT_MAX
mdefine_line|#define CPU_PUMP_OUTPUT_MAX&t;&t;3700
DECL|macro|CPU_PUMP_OUTPUT_MIN
mdefine_line|#define CPU_PUMP_OUTPUT_MIN&t;&t;1000
DECL|struct|cpu_pid_state
r_struct
id|cpu_pid_state
(brace
DECL|member|index
r_int
id|index
suffix:semicolon
DECL|member|monitor
r_struct
id|i2c_client
op_star
id|monitor
suffix:semicolon
DECL|member|mpu
r_struct
id|mpu_data
id|mpu
suffix:semicolon
DECL|member|overtemp
r_int
id|overtemp
suffix:semicolon
DECL|member|temp_history
id|s32
id|temp_history
(braket
id|CPU_TEMP_HISTORY_SIZE
)braket
suffix:semicolon
DECL|member|cur_temp
r_int
id|cur_temp
suffix:semicolon
DECL|member|power_history
id|s32
id|power_history
(braket
id|CPU_POWER_HISTORY_SIZE
)braket
suffix:semicolon
DECL|member|error_history
id|s32
id|error_history
(braket
id|CPU_POWER_HISTORY_SIZE
)braket
suffix:semicolon
DECL|member|cur_power
r_int
id|cur_power
suffix:semicolon
DECL|member|count_power
r_int
id|count_power
suffix:semicolon
DECL|member|rpm
r_int
id|rpm
suffix:semicolon
DECL|member|intake_rpm
r_int
id|intake_rpm
suffix:semicolon
DECL|member|voltage
id|s32
id|voltage
suffix:semicolon
DECL|member|current_a
id|s32
id|current_a
suffix:semicolon
DECL|member|last_temp
id|s32
id|last_temp
suffix:semicolon
DECL|member|last_power
id|s32
id|last_power
suffix:semicolon
DECL|member|first
r_int
id|first
suffix:semicolon
DECL|member|adc_config
id|u8
id|adc_config
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Driver state&n; */
r_enum
(brace
DECL|enumerator|state_detached
id|state_detached
comma
DECL|enumerator|state_attaching
id|state_attaching
comma
DECL|enumerator|state_attached
id|state_attached
comma
DECL|enumerator|state_detaching
id|state_detaching
comma
)brace
suffix:semicolon
macro_line|#endif /* __THERM_PMAC_7_2_H__ */
eof
