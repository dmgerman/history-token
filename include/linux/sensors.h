multiline_comment|/*&n;    sensors.h - Part of lm_sensors, Linux kernel modules for hardware&n;                monitoring&n;    Copyright (c) 1998, 1999  Frodo Looijaard &lt;frodol@dds.nl&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef SENSORS_NSENSORS_H
DECL|macro|SENSORS_NSENSORS_H
mdefine_line|#define SENSORS_NSENSORS_H
DECL|macro|LM_DATE
mdefine_line|#define LM_DATE &quot;20020915&quot;
DECL|macro|LM_VERSION
mdefine_line|#define LM_VERSION &quot;2.6.5&quot;
macro_line|#include &lt;linux/i2c-proc.h&gt;
DECL|macro|LM78_SYSCTL_IN0
mdefine_line|#define LM78_SYSCTL_IN0 1000&t;/* Volts * 100 */
DECL|macro|LM78_SYSCTL_IN1
mdefine_line|#define LM78_SYSCTL_IN1 1001
DECL|macro|LM78_SYSCTL_IN2
mdefine_line|#define LM78_SYSCTL_IN2 1002
DECL|macro|LM78_SYSCTL_IN3
mdefine_line|#define LM78_SYSCTL_IN3 1003
DECL|macro|LM78_SYSCTL_IN4
mdefine_line|#define LM78_SYSCTL_IN4 1004
DECL|macro|LM78_SYSCTL_IN5
mdefine_line|#define LM78_SYSCTL_IN5 1005
DECL|macro|LM78_SYSCTL_IN6
mdefine_line|#define LM78_SYSCTL_IN6 1006
DECL|macro|LM78_SYSCTL_FAN1
mdefine_line|#define LM78_SYSCTL_FAN1 1101&t;/* Rotations/min */
DECL|macro|LM78_SYSCTL_FAN2
mdefine_line|#define LM78_SYSCTL_FAN2 1102
DECL|macro|LM78_SYSCTL_FAN3
mdefine_line|#define LM78_SYSCTL_FAN3 1103
DECL|macro|LM78_SYSCTL_TEMP
mdefine_line|#define LM78_SYSCTL_TEMP 1200&t;/* Degrees Celcius * 10 */
DECL|macro|LM78_SYSCTL_VID
mdefine_line|#define LM78_SYSCTL_VID 1300&t;/* Volts * 100 */
DECL|macro|LM78_SYSCTL_FAN_DIV
mdefine_line|#define LM78_SYSCTL_FAN_DIV 2000&t;/* 1, 2, 4 or 8 */
DECL|macro|LM78_SYSCTL_ALARMS
mdefine_line|#define LM78_SYSCTL_ALARMS 2001&t;/* bitvector */
DECL|macro|LM78_ALARM_IN0
mdefine_line|#define LM78_ALARM_IN0 0x0001
DECL|macro|LM78_ALARM_IN1
mdefine_line|#define LM78_ALARM_IN1 0x0002
DECL|macro|LM78_ALARM_IN2
mdefine_line|#define LM78_ALARM_IN2 0x0004
DECL|macro|LM78_ALARM_IN3
mdefine_line|#define LM78_ALARM_IN3 0x0008
DECL|macro|LM78_ALARM_IN4
mdefine_line|#define LM78_ALARM_IN4 0x0100
DECL|macro|LM78_ALARM_IN5
mdefine_line|#define LM78_ALARM_IN5 0x0200
DECL|macro|LM78_ALARM_IN6
mdefine_line|#define LM78_ALARM_IN6 0x0400
DECL|macro|LM78_ALARM_FAN1
mdefine_line|#define LM78_ALARM_FAN1 0x0040
DECL|macro|LM78_ALARM_FAN2
mdefine_line|#define LM78_ALARM_FAN2 0x0080
DECL|macro|LM78_ALARM_FAN3
mdefine_line|#define LM78_ALARM_FAN3 0x0800
DECL|macro|LM78_ALARM_TEMP
mdefine_line|#define LM78_ALARM_TEMP 0x0010
DECL|macro|LM78_ALARM_BTI
mdefine_line|#define LM78_ALARM_BTI 0x0020
DECL|macro|LM78_ALARM_CHAS
mdefine_line|#define LM78_ALARM_CHAS 0x1000
DECL|macro|LM78_ALARM_FIFO
mdefine_line|#define LM78_ALARM_FIFO 0x2000
DECL|macro|LM78_ALARM_SMI_IN
mdefine_line|#define LM78_ALARM_SMI_IN 0x4000
DECL|macro|W83781D_SYSCTL_IN0
mdefine_line|#define W83781D_SYSCTL_IN0 1000&t;/* Volts * 100 */
DECL|macro|W83781D_SYSCTL_IN1
mdefine_line|#define W83781D_SYSCTL_IN1 1001
DECL|macro|W83781D_SYSCTL_IN2
mdefine_line|#define W83781D_SYSCTL_IN2 1002
DECL|macro|W83781D_SYSCTL_IN3
mdefine_line|#define W83781D_SYSCTL_IN3 1003
DECL|macro|W83781D_SYSCTL_IN4
mdefine_line|#define W83781D_SYSCTL_IN4 1004
DECL|macro|W83781D_SYSCTL_IN5
mdefine_line|#define W83781D_SYSCTL_IN5 1005
DECL|macro|W83781D_SYSCTL_IN6
mdefine_line|#define W83781D_SYSCTL_IN6 1006
DECL|macro|W83781D_SYSCTL_IN7
mdefine_line|#define W83781D_SYSCTL_IN7 1007
DECL|macro|W83781D_SYSCTL_IN8
mdefine_line|#define W83781D_SYSCTL_IN8 1008
DECL|macro|W83781D_SYSCTL_FAN1
mdefine_line|#define W83781D_SYSCTL_FAN1 1101&t;/* Rotations/min */
DECL|macro|W83781D_SYSCTL_FAN2
mdefine_line|#define W83781D_SYSCTL_FAN2 1102
DECL|macro|W83781D_SYSCTL_FAN3
mdefine_line|#define W83781D_SYSCTL_FAN3 1103
DECL|macro|W83781D_SYSCTL_TEMP1
mdefine_line|#define W83781D_SYSCTL_TEMP1 1200&t;/* Degrees Celcius * 10 */
DECL|macro|W83781D_SYSCTL_TEMP2
mdefine_line|#define W83781D_SYSCTL_TEMP2 1201&t;/* Degrees Celcius * 10 */
DECL|macro|W83781D_SYSCTL_TEMP3
mdefine_line|#define W83781D_SYSCTL_TEMP3 1202&t;/* Degrees Celcius * 10 */
DECL|macro|W83781D_SYSCTL_VID
mdefine_line|#define W83781D_SYSCTL_VID 1300&t;&t;/* Volts * 1000 */
DECL|macro|W83781D_SYSCTL_VRM
mdefine_line|#define W83781D_SYSCTL_VRM 1301
DECL|macro|W83781D_SYSCTL_PWM1
mdefine_line|#define W83781D_SYSCTL_PWM1 1401
DECL|macro|W83781D_SYSCTL_PWM2
mdefine_line|#define W83781D_SYSCTL_PWM2 1402
DECL|macro|W83781D_SYSCTL_PWM3
mdefine_line|#define W83781D_SYSCTL_PWM3 1403
DECL|macro|W83781D_SYSCTL_PWM4
mdefine_line|#define W83781D_SYSCTL_PWM4 1404
DECL|macro|W83781D_SYSCTL_SENS1
mdefine_line|#define W83781D_SYSCTL_SENS1 1501&t;/* 1, 2, or Beta (3000-5000) */
DECL|macro|W83781D_SYSCTL_SENS2
mdefine_line|#define W83781D_SYSCTL_SENS2 1502
DECL|macro|W83781D_SYSCTL_SENS3
mdefine_line|#define W83781D_SYSCTL_SENS3 1503
DECL|macro|W83781D_SYSCTL_RT1
mdefine_line|#define W83781D_SYSCTL_RT1   1601&t;/* 32-entry table */
DECL|macro|W83781D_SYSCTL_RT2
mdefine_line|#define W83781D_SYSCTL_RT2   1602&t;/* 32-entry table */
DECL|macro|W83781D_SYSCTL_RT3
mdefine_line|#define W83781D_SYSCTL_RT3   1603&t;/* 32-entry table */
DECL|macro|W83781D_SYSCTL_FAN_DIV
mdefine_line|#define W83781D_SYSCTL_FAN_DIV 2000&t;/* 1, 2, 4 or 8 */
DECL|macro|W83781D_SYSCTL_ALARMS
mdefine_line|#define W83781D_SYSCTL_ALARMS 2001&t;/* bitvector */
DECL|macro|W83781D_SYSCTL_BEEP
mdefine_line|#define W83781D_SYSCTL_BEEP 2002&t;/* bitvector */
DECL|macro|W83781D_ALARM_IN0
mdefine_line|#define W83781D_ALARM_IN0 0x0001
DECL|macro|W83781D_ALARM_IN1
mdefine_line|#define W83781D_ALARM_IN1 0x0002
DECL|macro|W83781D_ALARM_IN2
mdefine_line|#define W83781D_ALARM_IN2 0x0004
DECL|macro|W83781D_ALARM_IN3
mdefine_line|#define W83781D_ALARM_IN3 0x0008
DECL|macro|W83781D_ALARM_IN4
mdefine_line|#define W83781D_ALARM_IN4 0x0100
DECL|macro|W83781D_ALARM_IN5
mdefine_line|#define W83781D_ALARM_IN5 0x0200
DECL|macro|W83781D_ALARM_IN6
mdefine_line|#define W83781D_ALARM_IN6 0x0400
DECL|macro|W83782D_ALARM_IN7
mdefine_line|#define W83782D_ALARM_IN7 0x10000
DECL|macro|W83782D_ALARM_IN8
mdefine_line|#define W83782D_ALARM_IN8 0x20000
DECL|macro|W83781D_ALARM_FAN1
mdefine_line|#define W83781D_ALARM_FAN1 0x0040
DECL|macro|W83781D_ALARM_FAN2
mdefine_line|#define W83781D_ALARM_FAN2 0x0080
DECL|macro|W83781D_ALARM_FAN3
mdefine_line|#define W83781D_ALARM_FAN3 0x0800
DECL|macro|W83781D_ALARM_TEMP1
mdefine_line|#define W83781D_ALARM_TEMP1 0x0010
DECL|macro|W83781D_ALARM_TEMP23
mdefine_line|#define W83781D_ALARM_TEMP23 0x0020&t;/* 781D only */
DECL|macro|W83781D_ALARM_TEMP2
mdefine_line|#define W83781D_ALARM_TEMP2 0x0020&t;/* 782D/783S */
DECL|macro|W83781D_ALARM_TEMP3
mdefine_line|#define W83781D_ALARM_TEMP3 0x2000&t;/* 782D only */
DECL|macro|W83781D_ALARM_CHAS
mdefine_line|#define W83781D_ALARM_CHAS 0x1000
DECL|macro|LM75_SYSCTL_TEMP
mdefine_line|#define LM75_SYSCTL_TEMP 1200&t;/* Degrees Celcius * 10 */
DECL|macro|ADM1021_SYSCTL_TEMP
mdefine_line|#define ADM1021_SYSCTL_TEMP 1200
DECL|macro|ADM1021_SYSCTL_REMOTE_TEMP
mdefine_line|#define ADM1021_SYSCTL_REMOTE_TEMP 1201
DECL|macro|ADM1021_SYSCTL_DIE_CODE
mdefine_line|#define ADM1021_SYSCTL_DIE_CODE 1202
DECL|macro|ADM1021_SYSCTL_ALARMS
mdefine_line|#define ADM1021_SYSCTL_ALARMS 1203
DECL|macro|ADM1021_ALARM_TEMP_HIGH
mdefine_line|#define ADM1021_ALARM_TEMP_HIGH 0x40
DECL|macro|ADM1021_ALARM_TEMP_LOW
mdefine_line|#define ADM1021_ALARM_TEMP_LOW 0x20
DECL|macro|ADM1021_ALARM_RTEMP_HIGH
mdefine_line|#define ADM1021_ALARM_RTEMP_HIGH 0x10
DECL|macro|ADM1021_ALARM_RTEMP_LOW
mdefine_line|#define ADM1021_ALARM_RTEMP_LOW 0x08
DECL|macro|ADM1021_ALARM_RTEMP_NA
mdefine_line|#define ADM1021_ALARM_RTEMP_NA 0x04
DECL|macro|GL518_SYSCTL_VDD
mdefine_line|#define GL518_SYSCTL_VDD  1000&t;/* Volts * 100 */
DECL|macro|GL518_SYSCTL_VIN1
mdefine_line|#define GL518_SYSCTL_VIN1 1001
DECL|macro|GL518_SYSCTL_VIN2
mdefine_line|#define GL518_SYSCTL_VIN2 1002
DECL|macro|GL518_SYSCTL_VIN3
mdefine_line|#define GL518_SYSCTL_VIN3 1003
DECL|macro|GL518_SYSCTL_FAN1
mdefine_line|#define GL518_SYSCTL_FAN1 1101&t;/* RPM */
DECL|macro|GL518_SYSCTL_FAN2
mdefine_line|#define GL518_SYSCTL_FAN2 1102
DECL|macro|GL518_SYSCTL_TEMP
mdefine_line|#define GL518_SYSCTL_TEMP 1200&t;/* Degrees Celcius * 10 */
DECL|macro|GL518_SYSCTL_FAN_DIV
mdefine_line|#define GL518_SYSCTL_FAN_DIV 2000&t;/* 1, 2, 4 or 8 */
DECL|macro|GL518_SYSCTL_ALARMS
mdefine_line|#define GL518_SYSCTL_ALARMS 2001&t;/* bitvector */
DECL|macro|GL518_SYSCTL_BEEP
mdefine_line|#define GL518_SYSCTL_BEEP 2002&t;/* bitvector */
DECL|macro|GL518_SYSCTL_FAN1OFF
mdefine_line|#define GL518_SYSCTL_FAN1OFF 2003
DECL|macro|GL518_SYSCTL_ITERATE
mdefine_line|#define GL518_SYSCTL_ITERATE 2004
DECL|macro|GL518_ALARM_VDD
mdefine_line|#define GL518_ALARM_VDD 0x01
DECL|macro|GL518_ALARM_VIN1
mdefine_line|#define GL518_ALARM_VIN1 0x02
DECL|macro|GL518_ALARM_VIN2
mdefine_line|#define GL518_ALARM_VIN2 0x04
DECL|macro|GL518_ALARM_VIN3
mdefine_line|#define GL518_ALARM_VIN3 0x08
DECL|macro|GL518_ALARM_TEMP
mdefine_line|#define GL518_ALARM_TEMP 0x10
DECL|macro|GL518_ALARM_FAN1
mdefine_line|#define GL518_ALARM_FAN1 0x20
DECL|macro|GL518_ALARM_FAN2
mdefine_line|#define GL518_ALARM_FAN2 0x40
DECL|macro|GL520_SYSCTL_VDD
mdefine_line|#define GL520_SYSCTL_VDD  1000&t;/* Volts * 100 */
DECL|macro|GL520_SYSCTL_VIN1
mdefine_line|#define GL520_SYSCTL_VIN1 1001
DECL|macro|GL520_SYSCTL_VIN2
mdefine_line|#define GL520_SYSCTL_VIN2 1002
DECL|macro|GL520_SYSCTL_VIN3
mdefine_line|#define GL520_SYSCTL_VIN3 1003
DECL|macro|GL520_SYSCTL_VIN4
mdefine_line|#define GL520_SYSCTL_VIN4 1004
DECL|macro|GL520_SYSCTL_FAN1
mdefine_line|#define GL520_SYSCTL_FAN1 1101&t;/* RPM */
DECL|macro|GL520_SYSCTL_FAN2
mdefine_line|#define GL520_SYSCTL_FAN2 1102
DECL|macro|GL520_SYSCTL_TEMP1
mdefine_line|#define GL520_SYSCTL_TEMP1 1200&t;/* Degrees Celcius * 10 */
DECL|macro|GL520_SYSCTL_TEMP2
mdefine_line|#define GL520_SYSCTL_TEMP2 1201&t;/* Degrees Celcius * 10 */
DECL|macro|GL520_SYSCTL_VID
mdefine_line|#define GL520_SYSCTL_VID 1300
DECL|macro|GL520_SYSCTL_FAN_DIV
mdefine_line|#define GL520_SYSCTL_FAN_DIV 2000&t;/* 1, 2, 4 or 8 */
DECL|macro|GL520_SYSCTL_ALARMS
mdefine_line|#define GL520_SYSCTL_ALARMS 2001&t;/* bitvector */
DECL|macro|GL520_SYSCTL_BEEP
mdefine_line|#define GL520_SYSCTL_BEEP 2002&t;/* bitvector */
DECL|macro|GL520_SYSCTL_FAN1OFF
mdefine_line|#define GL520_SYSCTL_FAN1OFF 2003
DECL|macro|GL520_SYSCTL_CONFIG
mdefine_line|#define GL520_SYSCTL_CONFIG 2004
DECL|macro|GL520_ALARM_VDD
mdefine_line|#define GL520_ALARM_VDD 0x01
DECL|macro|GL520_ALARM_VIN1
mdefine_line|#define GL520_ALARM_VIN1 0x02
DECL|macro|GL520_ALARM_VIN2
mdefine_line|#define GL520_ALARM_VIN2 0x04
DECL|macro|GL520_ALARM_VIN3
mdefine_line|#define GL520_ALARM_VIN3 0x08
DECL|macro|GL520_ALARM_TEMP1
mdefine_line|#define GL520_ALARM_TEMP1 0x10
DECL|macro|GL520_ALARM_FAN1
mdefine_line|#define GL520_ALARM_FAN1 0x20
DECL|macro|GL520_ALARM_FAN2
mdefine_line|#define GL520_ALARM_FAN2 0x40
DECL|macro|GL520_ALARM_TEMP2
mdefine_line|#define GL520_ALARM_TEMP2 0x80
DECL|macro|GL520_ALARM_VIN4
mdefine_line|#define GL520_ALARM_VIN4 0x80
DECL|macro|EEPROM_SYSCTL1
mdefine_line|#define EEPROM_SYSCTL1 1000
DECL|macro|EEPROM_SYSCTL2
mdefine_line|#define EEPROM_SYSCTL2 1001
DECL|macro|EEPROM_SYSCTL3
mdefine_line|#define EEPROM_SYSCTL3 1002
DECL|macro|EEPROM_SYSCTL4
mdefine_line|#define EEPROM_SYSCTL4 1003
DECL|macro|EEPROM_SYSCTL5
mdefine_line|#define EEPROM_SYSCTL5 1004
DECL|macro|EEPROM_SYSCTL6
mdefine_line|#define EEPROM_SYSCTL6 1005
DECL|macro|EEPROM_SYSCTL7
mdefine_line|#define EEPROM_SYSCTL7 1006
DECL|macro|EEPROM_SYSCTL8
mdefine_line|#define EEPROM_SYSCTL8 1007
DECL|macro|EEPROM_SYSCTL9
mdefine_line|#define EEPROM_SYSCTL9 1008
DECL|macro|EEPROM_SYSCTL10
mdefine_line|#define EEPROM_SYSCTL10 1009
DECL|macro|EEPROM_SYSCTL11
mdefine_line|#define EEPROM_SYSCTL11 1010
DECL|macro|EEPROM_SYSCTL12
mdefine_line|#define EEPROM_SYSCTL12 1011
DECL|macro|EEPROM_SYSCTL13
mdefine_line|#define EEPROM_SYSCTL13 1012
DECL|macro|EEPROM_SYSCTL14
mdefine_line|#define EEPROM_SYSCTL14 1013
DECL|macro|EEPROM_SYSCTL15
mdefine_line|#define EEPROM_SYSCTL15 1014
DECL|macro|EEPROM_SYSCTL16
mdefine_line|#define EEPROM_SYSCTL16 1015
DECL|macro|LM80_SYSCTL_IN0
mdefine_line|#define LM80_SYSCTL_IN0 1000&t;/* Volts * 100 */
DECL|macro|LM80_SYSCTL_IN1
mdefine_line|#define LM80_SYSCTL_IN1 1001
DECL|macro|LM80_SYSCTL_IN2
mdefine_line|#define LM80_SYSCTL_IN2 1002
DECL|macro|LM80_SYSCTL_IN3
mdefine_line|#define LM80_SYSCTL_IN3 1003
DECL|macro|LM80_SYSCTL_IN4
mdefine_line|#define LM80_SYSCTL_IN4 1004
DECL|macro|LM80_SYSCTL_IN5
mdefine_line|#define LM80_SYSCTL_IN5 1005
DECL|macro|LM80_SYSCTL_IN6
mdefine_line|#define LM80_SYSCTL_IN6 1006
DECL|macro|LM80_SYSCTL_FAN1
mdefine_line|#define LM80_SYSCTL_FAN1 1101&t;/* Rotations/min */
DECL|macro|LM80_SYSCTL_FAN2
mdefine_line|#define LM80_SYSCTL_FAN2 1102
DECL|macro|LM80_SYSCTL_TEMP
mdefine_line|#define LM80_SYSCTL_TEMP 1250&t;/* Degrees Celcius * 100 */
DECL|macro|LM80_SYSCTL_FAN_DIV
mdefine_line|#define LM80_SYSCTL_FAN_DIV 2000&t;/* 1, 2, 4 or 8 */
DECL|macro|LM80_SYSCTL_ALARMS
mdefine_line|#define LM80_SYSCTL_ALARMS 2001&t;/* bitvector */
DECL|macro|ADM9240_SYSCTL_IN0
mdefine_line|#define ADM9240_SYSCTL_IN0 1000&t;/* Volts * 100 */
DECL|macro|ADM9240_SYSCTL_IN1
mdefine_line|#define ADM9240_SYSCTL_IN1 1001
DECL|macro|ADM9240_SYSCTL_IN2
mdefine_line|#define ADM9240_SYSCTL_IN2 1002
DECL|macro|ADM9240_SYSCTL_IN3
mdefine_line|#define ADM9240_SYSCTL_IN3 1003
DECL|macro|ADM9240_SYSCTL_IN4
mdefine_line|#define ADM9240_SYSCTL_IN4 1004
DECL|macro|ADM9240_SYSCTL_IN5
mdefine_line|#define ADM9240_SYSCTL_IN5 1005
DECL|macro|ADM9240_SYSCTL_FAN1
mdefine_line|#define ADM9240_SYSCTL_FAN1 1101&t;/* Rotations/min */
DECL|macro|ADM9240_SYSCTL_FAN2
mdefine_line|#define ADM9240_SYSCTL_FAN2 1102
DECL|macro|ADM9240_SYSCTL_TEMP
mdefine_line|#define ADM9240_SYSCTL_TEMP 1250&t;/* Degrees Celcius * 100 */
DECL|macro|ADM9240_SYSCTL_FAN_DIV
mdefine_line|#define ADM9240_SYSCTL_FAN_DIV 2000&t;/* 1, 2, 4 or 8 */
DECL|macro|ADM9240_SYSCTL_ALARMS
mdefine_line|#define ADM9240_SYSCTL_ALARMS 2001&t;/* bitvector */
DECL|macro|ADM9240_SYSCTL_ANALOG_OUT
mdefine_line|#define ADM9240_SYSCTL_ANALOG_OUT 2002
DECL|macro|ADM9240_SYSCTL_VID
mdefine_line|#define ADM9240_SYSCTL_VID 2003
DECL|macro|ADM9240_ALARM_IN0
mdefine_line|#define ADM9240_ALARM_IN0 0x0001
DECL|macro|ADM9240_ALARM_IN1
mdefine_line|#define ADM9240_ALARM_IN1 0x0002
DECL|macro|ADM9240_ALARM_IN2
mdefine_line|#define ADM9240_ALARM_IN2 0x0004
DECL|macro|ADM9240_ALARM_IN3
mdefine_line|#define ADM9240_ALARM_IN3 0x0008
DECL|macro|ADM9240_ALARM_IN4
mdefine_line|#define ADM9240_ALARM_IN4 0x0100
DECL|macro|ADM9240_ALARM_IN5
mdefine_line|#define ADM9240_ALARM_IN5 0x0200
DECL|macro|ADM9240_ALARM_FAN1
mdefine_line|#define ADM9240_ALARM_FAN1 0x0040
DECL|macro|ADM9240_ALARM_FAN2
mdefine_line|#define ADM9240_ALARM_FAN2 0x0080
DECL|macro|ADM9240_ALARM_TEMP
mdefine_line|#define ADM9240_ALARM_TEMP 0x0010
DECL|macro|ADM9240_ALARM_CHAS
mdefine_line|#define ADM9240_ALARM_CHAS 0x1000
DECL|macro|ADM1024_SYSCTL_IN0
mdefine_line|#define ADM1024_SYSCTL_IN0 1000&t;/* Volts * 100 */
DECL|macro|ADM1024_SYSCTL_IN1
mdefine_line|#define ADM1024_SYSCTL_IN1 1001
DECL|macro|ADM1024_SYSCTL_IN2
mdefine_line|#define ADM1024_SYSCTL_IN2 1002
DECL|macro|ADM1024_SYSCTL_IN3
mdefine_line|#define ADM1024_SYSCTL_IN3 1003
DECL|macro|ADM1024_SYSCTL_IN4
mdefine_line|#define ADM1024_SYSCTL_IN4 1004
DECL|macro|ADM1024_SYSCTL_IN5
mdefine_line|#define ADM1024_SYSCTL_IN5 1005
DECL|macro|ADM1024_SYSCTL_FAN1
mdefine_line|#define ADM1024_SYSCTL_FAN1 1101&t;/* Rotations/min */
DECL|macro|ADM1024_SYSCTL_FAN2
mdefine_line|#define ADM1024_SYSCTL_FAN2 1102
DECL|macro|ADM1024_SYSCTL_TEMP
mdefine_line|#define ADM1024_SYSCTL_TEMP 1250&t;/* Degrees Celcius * 100 */
DECL|macro|ADM1024_SYSCTL_TEMP1
mdefine_line|#define ADM1024_SYSCTL_TEMP1 1290&t;/* Degrees Celcius */
DECL|macro|ADM1024_SYSCTL_TEMP2
mdefine_line|#define ADM1024_SYSCTL_TEMP2 1295&t;/* Degrees Celcius */
DECL|macro|ADM1024_SYSCTL_FAN_DIV
mdefine_line|#define ADM1024_SYSCTL_FAN_DIV 2000&t;/* 1, 2, 4 or 8 */
DECL|macro|ADM1024_SYSCTL_ALARMS
mdefine_line|#define ADM1024_SYSCTL_ALARMS 2001&t;/* bitvector */
DECL|macro|ADM1024_SYSCTL_ANALOG_OUT
mdefine_line|#define ADM1024_SYSCTL_ANALOG_OUT 2002
DECL|macro|ADM1024_SYSCTL_VID
mdefine_line|#define ADM1024_SYSCTL_VID 2003
DECL|macro|ADM1024_ALARM_IN0
mdefine_line|#define ADM1024_ALARM_IN0 0x0001
DECL|macro|ADM1024_ALARM_IN1
mdefine_line|#define ADM1024_ALARM_IN1 0x0002
DECL|macro|ADM1024_ALARM_IN2
mdefine_line|#define ADM1024_ALARM_IN2 0x0004
DECL|macro|ADM1024_ALARM_IN3
mdefine_line|#define ADM1024_ALARM_IN3 0x0008
DECL|macro|ADM1024_ALARM_IN4
mdefine_line|#define ADM1024_ALARM_IN4 0x0100
DECL|macro|ADM1024_ALARM_IN5
mdefine_line|#define ADM1024_ALARM_IN5 0x0200
DECL|macro|ADM1024_ALARM_FAN1
mdefine_line|#define ADM1024_ALARM_FAN1 0x0040
DECL|macro|ADM1024_ALARM_FAN2
mdefine_line|#define ADM1024_ALARM_FAN2 0x0080
DECL|macro|ADM1024_ALARM_TEMP
mdefine_line|#define ADM1024_ALARM_TEMP 0x0010
DECL|macro|ADM1024_ALARM_TEMP1
mdefine_line|#define ADM1024_ALARM_TEMP1 0x0020
DECL|macro|ADM1024_ALARM_TEMP2
mdefine_line|#define ADM1024_ALARM_TEMP2 0x0001
DECL|macro|ADM1024_ALARM_CHAS
mdefine_line|#define ADM1024_ALARM_CHAS 0x1000
DECL|macro|ADM1025_SYSCTL_IN0
mdefine_line|#define ADM1025_SYSCTL_IN0 1000 /* Volts * 100 */
DECL|macro|ADM1025_SYSCTL_IN1
mdefine_line|#define ADM1025_SYSCTL_IN1 1001
DECL|macro|ADM1025_SYSCTL_IN2
mdefine_line|#define ADM1025_SYSCTL_IN2 1002
DECL|macro|ADM1025_SYSCTL_IN3
mdefine_line|#define ADM1025_SYSCTL_IN3 1003
DECL|macro|ADM1025_SYSCTL_IN4
mdefine_line|#define ADM1025_SYSCTL_IN4 1004
DECL|macro|ADM1025_SYSCTL_IN5
mdefine_line|#define ADM1025_SYSCTL_IN5 1005
DECL|macro|ADM1025_SYSCTL_RTEMP
mdefine_line|#define ADM1025_SYSCTL_RTEMP 1251
DECL|macro|ADM1025_SYSCTL_TEMP
mdefine_line|#define ADM1025_SYSCTL_TEMP 1250        /* Degrees Celcius * 100 */
DECL|macro|ADM1025_SYSCTL_ALARMS
mdefine_line|#define ADM1025_SYSCTL_ALARMS 2001      /* bitvector */
DECL|macro|ADM1025_SYSCTL_ANALOG_OUT
mdefine_line|#define ADM1025_SYSCTL_ANALOG_OUT 2002
DECL|macro|ADM1025_SYSCTL_VID
mdefine_line|#define ADM1025_SYSCTL_VID 2003
DECL|macro|ADM1025_SYSCTL_VRM
mdefine_line|#define ADM1025_SYSCTL_VRM 2004
DECL|macro|ADM1025_ALARM_IN0
mdefine_line|#define ADM1025_ALARM_IN0 0x0001
DECL|macro|ADM1025_ALARM_IN1
mdefine_line|#define ADM1025_ALARM_IN1 0x0002
DECL|macro|ADM1025_ALARM_IN2
mdefine_line|#define ADM1025_ALARM_IN2 0x0004
DECL|macro|ADM1025_ALARM_IN3
mdefine_line|#define ADM1025_ALARM_IN3 0x0008
DECL|macro|ADM1025_ALARM_IN4
mdefine_line|#define ADM1025_ALARM_IN4 0x0100
DECL|macro|ADM1025_ALARM_IN5
mdefine_line|#define ADM1025_ALARM_IN5 0x0200
DECL|macro|ADM1025_ALARM_RTEMP
mdefine_line|#define ADM1025_ALARM_RTEMP 0x0020
DECL|macro|ADM1025_ALARM_TEMP
mdefine_line|#define ADM1025_ALARM_TEMP 0x0010
DECL|macro|LTC1710_SYSCTL_SWITCH_1
mdefine_line|#define LTC1710_SYSCTL_SWITCH_1 1000
DECL|macro|LTC1710_SYSCTL_SWITCH_2
mdefine_line|#define LTC1710_SYSCTL_SWITCH_2 1001
DECL|macro|LM80_ALARM_IN0
mdefine_line|#define LM80_ALARM_IN0 0x0001
DECL|macro|LM80_ALARM_IN1
mdefine_line|#define LM80_ALARM_IN1 0x0002
DECL|macro|LM80_ALARM_IN2
mdefine_line|#define LM80_ALARM_IN2 0x0004
DECL|macro|LM80_ALARM_IN3
mdefine_line|#define LM80_ALARM_IN3 0x0008
DECL|macro|LM80_ALARM_IN4
mdefine_line|#define LM80_ALARM_IN4 0x0010
DECL|macro|LM80_ALARM_IN5
mdefine_line|#define LM80_ALARM_IN5 0x0020
DECL|macro|LM80_ALARM_IN6
mdefine_line|#define LM80_ALARM_IN6 0x0040
DECL|macro|LM80_ALARM_FAN1
mdefine_line|#define LM80_ALARM_FAN1 0x0400
DECL|macro|LM80_ALARM_FAN2
mdefine_line|#define LM80_ALARM_FAN2 0x0800
DECL|macro|LM80_ALARM_TEMP_HOT
mdefine_line|#define LM80_ALARM_TEMP_HOT 0x0100
DECL|macro|LM80_ALARM_TEMP_OS
mdefine_line|#define LM80_ALARM_TEMP_OS 0x2000
DECL|macro|LM80_ALARM_CHAS
mdefine_line|#define LM80_ALARM_CHAS 0x1000
DECL|macro|LM80_ALARM_BTI
mdefine_line|#define LM80_ALARM_BTI 0x0200
DECL|macro|LM80_ALARM_INT_IN
mdefine_line|#define LM80_ALARM_INT_IN 0x0080
DECL|macro|MAXI_SYSCTL_FAN1
mdefine_line|#define MAXI_SYSCTL_FAN1   1101&t;/* Rotations/min */
DECL|macro|MAXI_SYSCTL_FAN2
mdefine_line|#define MAXI_SYSCTL_FAN2   1102&t;/* Rotations/min */
DECL|macro|MAXI_SYSCTL_FAN3
mdefine_line|#define MAXI_SYSCTL_FAN3   1103&t;/* Rotations/min */
DECL|macro|MAXI_SYSCTL_FAN4
mdefine_line|#define MAXI_SYSCTL_FAN4   1104&t;/* Rotations/min */
DECL|macro|MAXI_SYSCTL_TEMP1
mdefine_line|#define MAXI_SYSCTL_TEMP1  1201&t;/* Degrees Celcius */
DECL|macro|MAXI_SYSCTL_TEMP2
mdefine_line|#define MAXI_SYSCTL_TEMP2  1202&t;/* Degrees Celcius */
DECL|macro|MAXI_SYSCTL_TEMP3
mdefine_line|#define MAXI_SYSCTL_TEMP3  1203&t;/* Degrees Celcius */
DECL|macro|MAXI_SYSCTL_TEMP4
mdefine_line|#define MAXI_SYSCTL_TEMP4  1204&t;/* Degrees Celcius */
DECL|macro|MAXI_SYSCTL_TEMP5
mdefine_line|#define MAXI_SYSCTL_TEMP5  1205&t;/* Degrees Celcius */
DECL|macro|MAXI_SYSCTL_TEMP6
mdefine_line|#define MAXI_SYSCTL_TEMP6  1206&t;/* Degrees Celcius */
DECL|macro|MAXI_SYSCTL_PLL
mdefine_line|#define MAXI_SYSCTL_PLL    1301&t;/* MHz */
DECL|macro|MAXI_SYSCTL_VID1
mdefine_line|#define MAXI_SYSCTL_VID1   1401&t;/* Volts / 6.337, for nba just Volts */
DECL|macro|MAXI_SYSCTL_VID2
mdefine_line|#define MAXI_SYSCTL_VID2   1402&t;/* Volts */
DECL|macro|MAXI_SYSCTL_VID3
mdefine_line|#define MAXI_SYSCTL_VID3   1403&t;/* Volts */
DECL|macro|MAXI_SYSCTL_VID4
mdefine_line|#define MAXI_SYSCTL_VID4   1404&t;/* Volts */
DECL|macro|MAXI_SYSCTL_VID5
mdefine_line|#define MAXI_SYSCTL_VID5   1405&t;/* Volts */
DECL|macro|MAXI_SYSCTL_LCD1
mdefine_line|#define MAXI_SYSCTL_LCD1   1501&t;/* Line 1 of LCD */
DECL|macro|MAXI_SYSCTL_LCD2
mdefine_line|#define MAXI_SYSCTL_LCD2   1502&t;/* Line 2 of LCD */
DECL|macro|MAXI_SYSCTL_LCD3
mdefine_line|#define MAXI_SYSCTL_LCD3   1503&t;/* Line 3 of LCD */
DECL|macro|MAXI_SYSCTL_LCD4
mdefine_line|#define MAXI_SYSCTL_LCD4   1504&t;/* Line 4 of LCD */
DECL|macro|MAXI_SYSCTL_ALARMS
mdefine_line|#define MAXI_SYSCTL_ALARMS 2001&t;/* Bitvector (see below) */
DECL|macro|MAXI_ALARM_VID4
mdefine_line|#define MAXI_ALARM_VID4      0x0001
DECL|macro|MAXI_ALARM_TEMP2
mdefine_line|#define MAXI_ALARM_TEMP2     0x0002
DECL|macro|MAXI_ALARM_VID1
mdefine_line|#define MAXI_ALARM_VID1      0x0004
DECL|macro|MAXI_ALARM_VID2
mdefine_line|#define MAXI_ALARM_VID2      0x0008
DECL|macro|MAXI_ALARM_VID3
mdefine_line|#define MAXI_ALARM_VID3      0x0010
DECL|macro|MAXI_ALARM_PLL
mdefine_line|#define MAXI_ALARM_PLL       0x0080
DECL|macro|MAXI_ALARM_TEMP4
mdefine_line|#define MAXI_ALARM_TEMP4     0x0100
DECL|macro|MAXI_ALARM_TEMP5
mdefine_line|#define MAXI_ALARM_TEMP5     0x0200
DECL|macro|MAXI_ALARM_FAN1
mdefine_line|#define MAXI_ALARM_FAN1      0x1000
DECL|macro|MAXI_ALARM_FAN2
mdefine_line|#define MAXI_ALARM_FAN2      0x2000
DECL|macro|MAXI_ALARM_FAN3
mdefine_line|#define MAXI_ALARM_FAN3      0x4000
DECL|macro|MAXI_ALARM_FAN
mdefine_line|#define MAXI_ALARM_FAN       0x0100&t;/* To be used with  MaxiLife&squot;99 */
DECL|macro|MAXI_ALARM_VID
mdefine_line|#define MAXI_ALARM_VID       0x0200&t;/* The MSB specifies which sensor */
DECL|macro|MAXI_ALARM_TEMP
mdefine_line|#define MAXI_ALARM_TEMP      0x0400&t;/* in the alarm group failed, i.e.: */
DECL|macro|MAXI_ALARM_VADD
mdefine_line|#define MAXI_ALARM_VADD      0x0800&t;/* 0x0402 = TEMP2 failed = CPU2 temp */
DECL|macro|SIS5595_SYSCTL_IN0
mdefine_line|#define SIS5595_SYSCTL_IN0 1000&t;/* Volts * 100 */
DECL|macro|SIS5595_SYSCTL_IN1
mdefine_line|#define SIS5595_SYSCTL_IN1 1001
DECL|macro|SIS5595_SYSCTL_IN2
mdefine_line|#define SIS5595_SYSCTL_IN2 1002
DECL|macro|SIS5595_SYSCTL_IN3
mdefine_line|#define SIS5595_SYSCTL_IN3 1003
DECL|macro|SIS5595_SYSCTL_IN4
mdefine_line|#define SIS5595_SYSCTL_IN4 1004
DECL|macro|SIS5595_SYSCTL_FAN1
mdefine_line|#define SIS5595_SYSCTL_FAN1 1101&t;/* Rotations/min */
DECL|macro|SIS5595_SYSCTL_FAN2
mdefine_line|#define SIS5595_SYSCTL_FAN2 1102
DECL|macro|SIS5595_SYSCTL_TEMP
mdefine_line|#define SIS5595_SYSCTL_TEMP 1200&t;/* Degrees Celcius * 10 */
DECL|macro|SIS5595_SYSCTL_FAN_DIV
mdefine_line|#define SIS5595_SYSCTL_FAN_DIV 2000&t;/* 1, 2, 4 or 8 */
DECL|macro|SIS5595_SYSCTL_ALARMS
mdefine_line|#define SIS5595_SYSCTL_ALARMS 2001&t;/* bitvector */
DECL|macro|SIS5595_ALARM_IN0
mdefine_line|#define SIS5595_ALARM_IN0 0x01
DECL|macro|SIS5595_ALARM_IN1
mdefine_line|#define SIS5595_ALARM_IN1 0x02
DECL|macro|SIS5595_ALARM_IN2
mdefine_line|#define SIS5595_ALARM_IN2 0x04
DECL|macro|SIS5595_ALARM_IN3
mdefine_line|#define SIS5595_ALARM_IN3 0x08
DECL|macro|SIS5595_ALARM_BTI
mdefine_line|#define SIS5595_ALARM_BTI 0x20
DECL|macro|SIS5595_ALARM_FAN1
mdefine_line|#define SIS5595_ALARM_FAN1 0x40
DECL|macro|SIS5595_ALARM_FAN2
mdefine_line|#define SIS5595_ALARM_FAN2 0x80
DECL|macro|SIS5595_ALARM_IN4
mdefine_line|#define SIS5595_ALARM_IN4  0x8000
DECL|macro|SIS5595_ALARM_TEMP
mdefine_line|#define SIS5595_ALARM_TEMP 0x8000
DECL|macro|VIA686A_SYSCTL_IN0
mdefine_line|#define VIA686A_SYSCTL_IN0 1000
DECL|macro|VIA686A_SYSCTL_IN1
mdefine_line|#define VIA686A_SYSCTL_IN1 1001
DECL|macro|VIA686A_SYSCTL_IN2
mdefine_line|#define VIA686A_SYSCTL_IN2 1002
DECL|macro|VIA686A_SYSCTL_IN3
mdefine_line|#define VIA686A_SYSCTL_IN3 1003
DECL|macro|VIA686A_SYSCTL_IN4
mdefine_line|#define VIA686A_SYSCTL_IN4 1004
DECL|macro|VIA686A_SYSCTL_FAN1
mdefine_line|#define VIA686A_SYSCTL_FAN1 1101
DECL|macro|VIA686A_SYSCTL_FAN2
mdefine_line|#define VIA686A_SYSCTL_FAN2 1102
DECL|macro|VIA686A_SYSCTL_TEMP
mdefine_line|#define VIA686A_SYSCTL_TEMP 1200
DECL|macro|VIA686A_SYSCTL_TEMP2
mdefine_line|#define VIA686A_SYSCTL_TEMP2 1201
DECL|macro|VIA686A_SYSCTL_TEMP3
mdefine_line|#define VIA686A_SYSCTL_TEMP3 1202
DECL|macro|VIA686A_SYSCTL_FAN_DIV
mdefine_line|#define VIA686A_SYSCTL_FAN_DIV 2000
DECL|macro|VIA686A_SYSCTL_ALARMS
mdefine_line|#define VIA686A_SYSCTL_ALARMS 2001
DECL|macro|VIA686A_ALARM_IN0
mdefine_line|#define VIA686A_ALARM_IN0 0x01
DECL|macro|VIA686A_ALARM_IN1
mdefine_line|#define VIA686A_ALARM_IN1 0x02
DECL|macro|VIA686A_ALARM_IN2
mdefine_line|#define VIA686A_ALARM_IN2 0x04
DECL|macro|VIA686A_ALARM_IN3
mdefine_line|#define VIA686A_ALARM_IN3 0x08
DECL|macro|VIA686A_ALARM_TEMP
mdefine_line|#define VIA686A_ALARM_TEMP 0x10
DECL|macro|VIA686A_ALARM_FAN1
mdefine_line|#define VIA686A_ALARM_FAN1 0x40
DECL|macro|VIA686A_ALARM_FAN2
mdefine_line|#define VIA686A_ALARM_FAN2 0x80
DECL|macro|VIA686A_ALARM_IN4
mdefine_line|#define VIA686A_ALARM_IN4 0x100
DECL|macro|VIA686A_ALARM_TEMP2
mdefine_line|#define VIA686A_ALARM_TEMP2 0x800
DECL|macro|VIA686A_ALARM_CHAS
mdefine_line|#define VIA686A_ALARM_CHAS 0x1000
DECL|macro|VIA686A_ALARM_TEMP3
mdefine_line|#define VIA686A_ALARM_TEMP3 0x8000
DECL|macro|ICSPLL_SYSCTL1
mdefine_line|#define ICSPLL_SYSCTL1 1000
DECL|macro|BT869_SYSCTL_STATUS
mdefine_line|#define BT869_SYSCTL_STATUS 1000
DECL|macro|BT869_SYSCTL_NTSC
mdefine_line|#define BT869_SYSCTL_NTSC   1001
DECL|macro|BT869_SYSCTL_HALF
mdefine_line|#define BT869_SYSCTL_HALF   1002
DECL|macro|BT869_SYSCTL_RES
mdefine_line|#define BT869_SYSCTL_RES    1003
DECL|macro|BT869_SYSCTL_COLORBARS
mdefine_line|#define BT869_SYSCTL_COLORBARS    1004
DECL|macro|BT869_SYSCTL_DEPTH
mdefine_line|#define BT869_SYSCTL_DEPTH  1005
DECL|macro|BT869_SYSCTL_SVIDEO
mdefine_line|#define BT869_SYSCTL_SVIDEO 1006
DECL|macro|MATORB_SYSCTL_DISP
mdefine_line|#define MATORB_SYSCTL_DISP 1000
DECL|macro|THMC50_SYSCTL_TEMP
mdefine_line|#define THMC50_SYSCTL_TEMP 1200&t;/* Degrees Celcius */
DECL|macro|THMC50_SYSCTL_REMOTE_TEMP
mdefine_line|#define THMC50_SYSCTL_REMOTE_TEMP 1201&t;/* Degrees Celcius */
DECL|macro|THMC50_SYSCTL_INTER
mdefine_line|#define THMC50_SYSCTL_INTER 1202
DECL|macro|THMC50_SYSCTL_INTER_MASK
mdefine_line|#define THMC50_SYSCTL_INTER_MASK 1203
DECL|macro|THMC50_SYSCTL_DIE_CODE
mdefine_line|#define THMC50_SYSCTL_DIE_CODE 1204
DECL|macro|THMC50_SYSCTL_ANALOG_OUT
mdefine_line|#define THMC50_SYSCTL_ANALOG_OUT 1205
DECL|macro|DDCMON_SYSCTL_ID
mdefine_line|#define DDCMON_SYSCTL_ID 1010
DECL|macro|DDCMON_SYSCTL_SIZE
mdefine_line|#define DDCMON_SYSCTL_SIZE 1011
DECL|macro|DDCMON_SYSCTL_SYNC
mdefine_line|#define DDCMON_SYSCTL_SYNC 1012
DECL|macro|DDCMON_SYSCTL_TIMINGS
mdefine_line|#define DDCMON_SYSCTL_TIMINGS 1013
DECL|macro|DDCMON_SYSCTL_SERIAL
mdefine_line|#define DDCMON_SYSCTL_SERIAL 1014
DECL|macro|LM87_SYSCTL_IN0
mdefine_line|#define LM87_SYSCTL_IN0        1000 /* Volts * 100 */
DECL|macro|LM87_SYSCTL_IN1
mdefine_line|#define LM87_SYSCTL_IN1        1001
DECL|macro|LM87_SYSCTL_IN2
mdefine_line|#define LM87_SYSCTL_IN2        1002
DECL|macro|LM87_SYSCTL_IN3
mdefine_line|#define LM87_SYSCTL_IN3        1003
DECL|macro|LM87_SYSCTL_IN4
mdefine_line|#define LM87_SYSCTL_IN4        1004
DECL|macro|LM87_SYSCTL_IN5
mdefine_line|#define LM87_SYSCTL_IN5        1005
DECL|macro|LM87_SYSCTL_AIN1
mdefine_line|#define LM87_SYSCTL_AIN1       1006
DECL|macro|LM87_SYSCTL_AIN2
mdefine_line|#define LM87_SYSCTL_AIN2       1007
DECL|macro|LM87_SYSCTL_FAN1
mdefine_line|#define LM87_SYSCTL_FAN1       1102
DECL|macro|LM87_SYSCTL_FAN2
mdefine_line|#define LM87_SYSCTL_FAN2       1103
DECL|macro|LM87_SYSCTL_TEMP1
mdefine_line|#define LM87_SYSCTL_TEMP1  1250 /* Degrees Celcius * 100 */
DECL|macro|LM87_SYSCTL_TEMP2
mdefine_line|#define LM87_SYSCTL_TEMP2   1251 /* Degrees Celcius * 100 */
DECL|macro|LM87_SYSCTL_TEMP3
mdefine_line|#define LM87_SYSCTL_TEMP3   1252 /* Degrees Celcius * 100 */
DECL|macro|LM87_SYSCTL_FAN_DIV
mdefine_line|#define LM87_SYSCTL_FAN_DIV    2000 /* 1, 2, 4 or 8 */
DECL|macro|LM87_SYSCTL_ALARMS
mdefine_line|#define LM87_SYSCTL_ALARMS     2001 /* bitvector */
DECL|macro|LM87_SYSCTL_ANALOG_OUT
mdefine_line|#define LM87_SYSCTL_ANALOG_OUT 2002
DECL|macro|LM87_SYSCTL_VID
mdefine_line|#define LM87_SYSCTL_VID        2003
DECL|macro|LM87_SYSCTL_VRM
mdefine_line|#define LM87_SYSCTL_VRM        2004
DECL|macro|LM87_ALARM_IN0
mdefine_line|#define LM87_ALARM_IN0          0x0001
DECL|macro|LM87_ALARM_IN1
mdefine_line|#define LM87_ALARM_IN1          0x0002
DECL|macro|LM87_ALARM_IN2
mdefine_line|#define LM87_ALARM_IN2          0x0004
DECL|macro|LM87_ALARM_IN3
mdefine_line|#define LM87_ALARM_IN3          0x0008
DECL|macro|LM87_ALARM_TEMP1
mdefine_line|#define LM87_ALARM_TEMP1        0x0010
DECL|macro|LM87_ALARM_TEMP2
mdefine_line|#define LM87_ALARM_TEMP2        0x0020
DECL|macro|LM87_ALARM_TEMP3
mdefine_line|#define LM87_ALARM_TEMP3        0x0020 /* same?? */
DECL|macro|LM87_ALARM_FAN1
mdefine_line|#define LM87_ALARM_FAN1         0x0040
DECL|macro|LM87_ALARM_FAN2
mdefine_line|#define LM87_ALARM_FAN2         0x0080
DECL|macro|LM87_ALARM_IN4
mdefine_line|#define LM87_ALARM_IN4          0x0100
DECL|macro|LM87_ALARM_IN5
mdefine_line|#define LM87_ALARM_IN5          0x0200
DECL|macro|LM87_ALARM_RESERVED1
mdefine_line|#define LM87_ALARM_RESERVED1    0x0400
DECL|macro|LM87_ALARM_RESERVED2
mdefine_line|#define LM87_ALARM_RESERVED2    0x0800
DECL|macro|LM87_ALARM_CHAS
mdefine_line|#define LM87_ALARM_CHAS         0x1000
DECL|macro|LM87_ALARM_THERM_SIG
mdefine_line|#define LM87_ALARM_THERM_SIG    0x2000
DECL|macro|LM87_ALARM_TEMP2_FAULT
mdefine_line|#define LM87_ALARM_TEMP2_FAULT  0x4000
DECL|macro|LM87_ALARM_TEMP3_FAULT
mdefine_line|#define LM87_ALARM_TEMP3_FAULT 0x08000
DECL|macro|PCF8574_SYSCTL_READ
mdefine_line|#define PCF8574_SYSCTL_READ     1000
DECL|macro|PCF8574_SYSCTL_WRITE
mdefine_line|#define PCF8574_SYSCTL_WRITE    1001
DECL|macro|MTP008_SYSCTL_IN0
mdefine_line|#define MTP008_SYSCTL_IN0&t;1000&t;/* Volts * 100 */
DECL|macro|MTP008_SYSCTL_IN1
mdefine_line|#define MTP008_SYSCTL_IN1&t;1001
DECL|macro|MTP008_SYSCTL_IN2
mdefine_line|#define MTP008_SYSCTL_IN2&t;1002
DECL|macro|MTP008_SYSCTL_IN3
mdefine_line|#define MTP008_SYSCTL_IN3&t;1003
DECL|macro|MTP008_SYSCTL_IN4
mdefine_line|#define MTP008_SYSCTL_IN4&t;1004
DECL|macro|MTP008_SYSCTL_IN5
mdefine_line|#define MTP008_SYSCTL_IN5&t;1005
DECL|macro|MTP008_SYSCTL_IN6
mdefine_line|#define MTP008_SYSCTL_IN6&t;1006
DECL|macro|MTP008_SYSCTL_FAN1
mdefine_line|#define MTP008_SYSCTL_FAN1&t;1101&t;/* Rotations/min */
DECL|macro|MTP008_SYSCTL_FAN2
mdefine_line|#define MTP008_SYSCTL_FAN2&t;1102
DECL|macro|MTP008_SYSCTL_FAN3
mdefine_line|#define MTP008_SYSCTL_FAN3&t;1103
DECL|macro|MTP008_SYSCTL_TEMP1
mdefine_line|#define MTP008_SYSCTL_TEMP1&t;1200&t;/* Degrees Celcius * 10 */
DECL|macro|MTP008_SYSCTL_TEMP2
mdefine_line|#define MTP008_SYSCTL_TEMP2&t;1201&t;/* Degrees Celcius * 10 */
DECL|macro|MTP008_SYSCTL_TEMP3
mdefine_line|#define MTP008_SYSCTL_TEMP3&t;1202&t;/* Degrees Celcius * 10 */
DECL|macro|MTP008_SYSCTL_VID
mdefine_line|#define MTP008_SYSCTL_VID&t;1300&t;/* Volts * 100 */
DECL|macro|MTP008_SYSCTL_PWM1
mdefine_line|#define MTP008_SYSCTL_PWM1&t;1401
DECL|macro|MTP008_SYSCTL_PWM2
mdefine_line|#define MTP008_SYSCTL_PWM2&t;1402
DECL|macro|MTP008_SYSCTL_PWM3
mdefine_line|#define MTP008_SYSCTL_PWM3&t;1403
DECL|macro|MTP008_SYSCTL_SENS1
mdefine_line|#define MTP008_SYSCTL_SENS1&t;1501&t;/* 1, 2, or Beta (3000-5000) */
DECL|macro|MTP008_SYSCTL_SENS2
mdefine_line|#define MTP008_SYSCTL_SENS2&t;1502
DECL|macro|MTP008_SYSCTL_SENS3
mdefine_line|#define MTP008_SYSCTL_SENS3&t;1503
DECL|macro|MTP008_SYSCTL_FAN_DIV
mdefine_line|#define MTP008_SYSCTL_FAN_DIV&t;2000&t;/* 1, 2, 4 or 8 */
DECL|macro|MTP008_SYSCTL_ALARMS
mdefine_line|#define MTP008_SYSCTL_ALARMS&t;2001&t;/* bitvector */
DECL|macro|MTP008_SYSCTL_BEEP
mdefine_line|#define MTP008_SYSCTL_BEEP&t;2002&t;/* bitvector */
DECL|macro|MTP008_ALARM_IN0
mdefine_line|#define MTP008_ALARM_IN0&t;0x0001
DECL|macro|MTP008_ALARM_IN1
mdefine_line|#define MTP008_ALARM_IN1&t;0x0002
DECL|macro|MTP008_ALARM_IN2
mdefine_line|#define MTP008_ALARM_IN2&t;0x0004
DECL|macro|MTP008_ALARM_IN3
mdefine_line|#define MTP008_ALARM_IN3&t;0x0008
DECL|macro|MTP008_ALARM_IN4
mdefine_line|#define MTP008_ALARM_IN4&t;0x0100
DECL|macro|MTP008_ALARM_IN5
mdefine_line|#define MTP008_ALARM_IN5&t;0x0200
DECL|macro|MTP008_ALARM_IN6
mdefine_line|#define MTP008_ALARM_IN6&t;0x0400
DECL|macro|MTP008_ALARM_FAN1
mdefine_line|#define MTP008_ALARM_FAN1&t;0x0040
DECL|macro|MTP008_ALARM_FAN2
mdefine_line|#define MTP008_ALARM_FAN2&t;0x0080
DECL|macro|MTP008_ALARM_FAN3
mdefine_line|#define MTP008_ALARM_FAN3&t;0x0800
DECL|macro|MTP008_ALARM_TEMP1
mdefine_line|#define MTP008_ALARM_TEMP1&t;0x0010
DECL|macro|MTP008_ALARM_TEMP2
mdefine_line|#define MTP008_ALARM_TEMP2&t;0x0100
DECL|macro|MTP008_ALARM_TEMP3
mdefine_line|#define MTP008_ALARM_TEMP3&t;0x0200
DECL|macro|DS1621_SYSCTL_TEMP
mdefine_line|#define DS1621_SYSCTL_TEMP 1200&t;/* Degrees Celcius * 10 */
DECL|macro|DS1621_SYSCTL_ALARMS
mdefine_line|#define DS1621_SYSCTL_ALARMS 2001&t;/* bitvector */
DECL|macro|DS1621_ALARM_TEMP_HIGH
mdefine_line|#define DS1621_ALARM_TEMP_HIGH 0x40
DECL|macro|DS1621_ALARM_TEMP_LOW
mdefine_line|#define DS1621_ALARM_TEMP_LOW 0x20
DECL|macro|DS1621_SYSCTL_ENABLE
mdefine_line|#define DS1621_SYSCTL_ENABLE 2002
DECL|macro|DS1621_SYSCTL_CONTINUOUS
mdefine_line|#define DS1621_SYSCTL_CONTINUOUS 2003
DECL|macro|DS1621_SYSCTL_POLARITY
mdefine_line|#define DS1621_SYSCTL_POLARITY 2004
DECL|macro|IT87_SYSCTL_IN0
mdefine_line|#define IT87_SYSCTL_IN0 1000    /* Volts * 100 */
DECL|macro|IT87_SYSCTL_IN1
mdefine_line|#define IT87_SYSCTL_IN1 1001
DECL|macro|IT87_SYSCTL_IN2
mdefine_line|#define IT87_SYSCTL_IN2 1002
DECL|macro|IT87_SYSCTL_IN3
mdefine_line|#define IT87_SYSCTL_IN3 1003
DECL|macro|IT87_SYSCTL_IN4
mdefine_line|#define IT87_SYSCTL_IN4 1004
DECL|macro|IT87_SYSCTL_IN5
mdefine_line|#define IT87_SYSCTL_IN5 1005
DECL|macro|IT87_SYSCTL_IN6
mdefine_line|#define IT87_SYSCTL_IN6 1006
DECL|macro|IT87_SYSCTL_IN7
mdefine_line|#define IT87_SYSCTL_IN7 1007
DECL|macro|IT87_SYSCTL_IN8
mdefine_line|#define IT87_SYSCTL_IN8 1008
DECL|macro|IT87_SYSCTL_FAN1
mdefine_line|#define IT87_SYSCTL_FAN1 1101   /* Rotations/min */
DECL|macro|IT87_SYSCTL_FAN2
mdefine_line|#define IT87_SYSCTL_FAN2 1102
DECL|macro|IT87_SYSCTL_FAN3
mdefine_line|#define IT87_SYSCTL_FAN3 1103
DECL|macro|IT87_SYSCTL_TEMP1
mdefine_line|#define IT87_SYSCTL_TEMP1 1200  /* Degrees Celcius * 10 */
DECL|macro|IT87_SYSCTL_TEMP2
mdefine_line|#define IT87_SYSCTL_TEMP2 1201  /* Degrees Celcius * 10 */
DECL|macro|IT87_SYSCTL_TEMP3
mdefine_line|#define IT87_SYSCTL_TEMP3 1202  /* Degrees Celcius * 10 */
DECL|macro|IT87_SYSCTL_VID
mdefine_line|#define IT87_SYSCTL_VID 1300    /* Volts * 100 */
DECL|macro|IT87_SYSCTL_FAN_DIV
mdefine_line|#define IT87_SYSCTL_FAN_DIV 2000        /* 1, 2, 4 or 8 */
DECL|macro|IT87_SYSCTL_ALARMS
mdefine_line|#define IT87_SYSCTL_ALARMS 2004    /* bitvector */
DECL|macro|IT87_ALARM_IN0
mdefine_line|#define IT87_ALARM_IN0 0x000100
DECL|macro|IT87_ALARM_IN1
mdefine_line|#define IT87_ALARM_IN1 0x000200
DECL|macro|IT87_ALARM_IN2
mdefine_line|#define IT87_ALARM_IN2 0x000400
DECL|macro|IT87_ALARM_IN3
mdefine_line|#define IT87_ALARM_IN3 0x000800
DECL|macro|IT87_ALARM_IN4
mdefine_line|#define IT87_ALARM_IN4 0x001000
DECL|macro|IT87_ALARM_IN5
mdefine_line|#define IT87_ALARM_IN5 0x002000
DECL|macro|IT87_ALARM_IN6
mdefine_line|#define IT87_ALARM_IN6 0x004000
DECL|macro|IT87_ALARM_IN7
mdefine_line|#define IT87_ALARM_IN7 0x008000
DECL|macro|IT87_ALARM_FAN1
mdefine_line|#define IT87_ALARM_FAN1 0x0001
DECL|macro|IT87_ALARM_FAN2
mdefine_line|#define IT87_ALARM_FAN2 0x0002
DECL|macro|IT87_ALARM_FAN3
mdefine_line|#define IT87_ALARM_FAN3 0x0004
DECL|macro|IT87_ALARM_TEMP1
mdefine_line|#define IT87_ALARM_TEMP1 0x00010000
DECL|macro|IT87_ALARM_TEMP2
mdefine_line|#define IT87_ALARM_TEMP2 0x00020000
DECL|macro|IT87_ALARM_TEMP3
mdefine_line|#define IT87_ALARM_TEMP3 0x00040000
DECL|macro|FSCPOS_SYSCTL_VOLT0
mdefine_line|#define FSCPOS_SYSCTL_VOLT0    1000       /* 12 volt supply */
DECL|macro|FSCPOS_SYSCTL_VOLT1
mdefine_line|#define FSCPOS_SYSCTL_VOLT1    1001       /* 5 volt supply */
DECL|macro|FSCPOS_SYSCTL_VOLT2
mdefine_line|#define FSCPOS_SYSCTL_VOLT2    1002       /* batterie voltage*/
DECL|macro|FSCPOS_SYSCTL_FAN0
mdefine_line|#define FSCPOS_SYSCTL_FAN0     1101       /* state, min, ripple, actual value fan 0 */
DECL|macro|FSCPOS_SYSCTL_FAN1
mdefine_line|#define FSCPOS_SYSCTL_FAN1     1102       /* state, min, ripple, actual value fan 1 */
DECL|macro|FSCPOS_SYSCTL_FAN2
mdefine_line|#define FSCPOS_SYSCTL_FAN2     1103       /* state, min, ripple, actual value fan 2 */
DECL|macro|FSCPOS_SYSCTL_TEMP0
mdefine_line|#define FSCPOS_SYSCTL_TEMP0    1201       /* state and value of sensor 0, cpu die */
DECL|macro|FSCPOS_SYSCTL_TEMP1
mdefine_line|#define FSCPOS_SYSCTL_TEMP1    1202       /* state and value of sensor 1, motherboard */
DECL|macro|FSCPOS_SYSCTL_TEMP2
mdefine_line|#define FSCPOS_SYSCTL_TEMP2    1203       /* state and value of sensor 2, chassis */
DECL|macro|FSCPOS_SYSCTL_REV
mdefine_line|#define FSCPOS_SYSCTL_REV     2000        /* Revision */
DECL|macro|FSCPOS_SYSCTL_EVENT
mdefine_line|#define FSCPOS_SYSCTL_EVENT   2001        /* global event status */
DECL|macro|FSCPOS_SYSCTL_CONTROL
mdefine_line|#define FSCPOS_SYSCTL_CONTROL 2002        /* global control byte */
DECL|macro|FSCPOS_SYSCTL_WDOG
mdefine_line|#define FSCPOS_SYSCTL_WDOG     2003       /* state, min, ripple, actual value fan 2 */
DECL|macro|FSCSCY_SYSCTL_VOLT0
mdefine_line|#define FSCSCY_SYSCTL_VOLT0    1000       /* 12 volt supply */
DECL|macro|FSCSCY_SYSCTL_VOLT1
mdefine_line|#define FSCSCY_SYSCTL_VOLT1    1001       /* 5 volt supply */
DECL|macro|FSCSCY_SYSCTL_VOLT2
mdefine_line|#define FSCSCY_SYSCTL_VOLT2    1002       /* batterie voltage*/
DECL|macro|FSCSCY_SYSCTL_FAN0
mdefine_line|#define FSCSCY_SYSCTL_FAN0     1101       /* state, min, ripple, actual value fan 0 */
DECL|macro|FSCSCY_SYSCTL_FAN1
mdefine_line|#define FSCSCY_SYSCTL_FAN1     1102       /* state, min, ripple, actual value fan 1 */
DECL|macro|FSCSCY_SYSCTL_FAN2
mdefine_line|#define FSCSCY_SYSCTL_FAN2     1103       /* state, min, ripple, actual value fan 2 */
DECL|macro|FSCSCY_SYSCTL_FAN3
mdefine_line|#define FSCSCY_SYSCTL_FAN3     1104       /* state, min, ripple, actual value fan 3 */
DECL|macro|FSCSCY_SYSCTL_FAN4
mdefine_line|#define FSCSCY_SYSCTL_FAN4     1105       /* state, min, ripple, actual value fan 4 */
DECL|macro|FSCSCY_SYSCTL_FAN5
mdefine_line|#define FSCSCY_SYSCTL_FAN5     1106       /* state, min, ripple, actual value fan 5 */
DECL|macro|FSCSCY_SYSCTL_TEMP0
mdefine_line|#define FSCSCY_SYSCTL_TEMP0    1201       /* state and value of sensor 0, cpu die */
DECL|macro|FSCSCY_SYSCTL_TEMP1
mdefine_line|#define FSCSCY_SYSCTL_TEMP1    1202       /* state and value of sensor 1, motherboard */
DECL|macro|FSCSCY_SYSCTL_TEMP2
mdefine_line|#define FSCSCY_SYSCTL_TEMP2    1203       /* state and value of sensor 2, chassis */
DECL|macro|FSCSCY_SYSCTL_TEMP3
mdefine_line|#define FSCSCY_SYSCTL_TEMP3    1204       /* state and value of sensor 3, chassis */
DECL|macro|FSCSCY_SYSCTL_REV
mdefine_line|#define FSCSCY_SYSCTL_REV     2000        /* Revision */
DECL|macro|FSCSCY_SYSCTL_EVENT
mdefine_line|#define FSCSCY_SYSCTL_EVENT   2001        /* global event status */
DECL|macro|FSCSCY_SYSCTL_CONTROL
mdefine_line|#define FSCSCY_SYSCTL_CONTROL 2002        /* global control byte */
DECL|macro|FSCSCY_SYSCTL_WDOG
mdefine_line|#define FSCSCY_SYSCTL_WDOG     2003       /* state, min, ripple, actual value fan 2 */
DECL|macro|FSCSCY_SYSCTL_PCILOAD
mdefine_line|#define FSCSCY_SYSCTL_PCILOAD  2004       /* PCILoad value */
DECL|macro|FSCSCY_SYSCTL_INTRUSION
mdefine_line|#define FSCSCY_SYSCTL_INTRUSION 2005      /* state, control for intrusion sensor */
DECL|macro|PCF8591_SYSCTL_AIN_CONF
mdefine_line|#define PCF8591_SYSCTL_AIN_CONF 1000      /* Analog input configuration */
DECL|macro|PCF8591_SYSCTL_CH0
mdefine_line|#define PCF8591_SYSCTL_CH0 1001           /* Input channel 1 */
DECL|macro|PCF8591_SYSCTL_CH1
mdefine_line|#define PCF8591_SYSCTL_CH1 1002           /* Input channel 2 */
DECL|macro|PCF8591_SYSCTL_CH2
mdefine_line|#define PCF8591_SYSCTL_CH2 1003           /* Input channel 3 */
DECL|macro|PCF8591_SYSCTL_CH3
mdefine_line|#define PCF8591_SYSCTL_CH3 1004           /* Input channel 4 */
DECL|macro|PCF8591_SYSCTL_AOUT_ENABLE
mdefine_line|#define PCF8591_SYSCTL_AOUT_ENABLE 1005   /* Analog output enable flag */
DECL|macro|PCF8591_SYSCTL_AOUT
mdefine_line|#define PCF8591_SYSCTL_AOUT 1006          /* Analog output */
DECL|macro|ARP_SYSCTL1
mdefine_line|#define ARP_SYSCTL1 1000
DECL|macro|ARP_SYSCTL2
mdefine_line|#define ARP_SYSCTL2 1001
DECL|macro|ARP_SYSCTL3
mdefine_line|#define ARP_SYSCTL3 1002
DECL|macro|ARP_SYSCTL4
mdefine_line|#define ARP_SYSCTL4 1003
DECL|macro|ARP_SYSCTL5
mdefine_line|#define ARP_SYSCTL5 1004
DECL|macro|ARP_SYSCTL6
mdefine_line|#define ARP_SYSCTL6 1005
DECL|macro|ARP_SYSCTL7
mdefine_line|#define ARP_SYSCTL7 1006
DECL|macro|ARP_SYSCTL8
mdefine_line|#define ARP_SYSCTL8 1007
DECL|macro|SMSC47M1_SYSCTL_FAN1
mdefine_line|#define SMSC47M1_SYSCTL_FAN1 1101   /* Rotations/min */
DECL|macro|SMSC47M1_SYSCTL_FAN2
mdefine_line|#define SMSC47M1_SYSCTL_FAN2 1102
DECL|macro|SMSC47M1_SYSCTL_PWM1
mdefine_line|#define SMSC47M1_SYSCTL_PWM1 1401
DECL|macro|SMSC47M1_SYSCTL_PWM2
mdefine_line|#define SMSC47M1_SYSCTL_PWM2 1402
DECL|macro|SMSC47M1_SYSCTL_FAN_DIV
mdefine_line|#define SMSC47M1_SYSCTL_FAN_DIV 2000        /* 1, 2, 4 or 8 */
DECL|macro|SMSC47M1_SYSCTL_ALARMS
mdefine_line|#define SMSC47M1_SYSCTL_ALARMS 2004    /* bitvector */
DECL|macro|SMSC47M1_ALARM_FAN1
mdefine_line|#define SMSC47M1_ALARM_FAN1 0x0001
DECL|macro|SMSC47M1_ALARM_FAN2
mdefine_line|#define SMSC47M1_ALARM_FAN2 0x0002
DECL|macro|VT1211_SYSCTL_IN0
mdefine_line|#define VT1211_SYSCTL_IN0 1000
DECL|macro|VT1211_SYSCTL_IN1
mdefine_line|#define VT1211_SYSCTL_IN1 1001
DECL|macro|VT1211_SYSCTL_IN2
mdefine_line|#define VT1211_SYSCTL_IN2 1002
DECL|macro|VT1211_SYSCTL_IN3
mdefine_line|#define VT1211_SYSCTL_IN3 1003
DECL|macro|VT1211_SYSCTL_IN4
mdefine_line|#define VT1211_SYSCTL_IN4 1004
DECL|macro|VT1211_SYSCTL_IN5
mdefine_line|#define VT1211_SYSCTL_IN5 1005
DECL|macro|VT1211_SYSCTL_IN6
mdefine_line|#define VT1211_SYSCTL_IN6 1006
DECL|macro|VT1211_SYSCTL_FAN1
mdefine_line|#define VT1211_SYSCTL_FAN1 1101
DECL|macro|VT1211_SYSCTL_FAN2
mdefine_line|#define VT1211_SYSCTL_FAN2 1102
DECL|macro|VT1211_SYSCTL_TEMP
mdefine_line|#define VT1211_SYSCTL_TEMP 1200
DECL|macro|VT1211_SYSCTL_TEMP2
mdefine_line|#define VT1211_SYSCTL_TEMP2 1201
DECL|macro|VT1211_SYSCTL_TEMP3
mdefine_line|#define VT1211_SYSCTL_TEMP3 1202
DECL|macro|VT1211_SYSCTL_TEMP4
mdefine_line|#define VT1211_SYSCTL_TEMP4 1203
DECL|macro|VT1211_SYSCTL_TEMP5
mdefine_line|#define VT1211_SYSCTL_TEMP5 1204
DECL|macro|VT1211_SYSCTL_TEMP6
mdefine_line|#define VT1211_SYSCTL_TEMP6 1205
DECL|macro|VT1211_SYSCTL_TEMP7
mdefine_line|#define VT1211_SYSCTL_TEMP7 1206
DECL|macro|VT1211_SYSCTL_VID
mdefine_line|#define VT1211_SYSCTL_VID&t;1300
DECL|macro|VT1211_SYSCTL_PWM1
mdefine_line|#define VT1211_SYSCTL_PWM1&t;1401
DECL|macro|VT1211_SYSCTL_PWM2
mdefine_line|#define VT1211_SYSCTL_PWM2&t;1402
DECL|macro|VT1211_SYSCTL_VRM
mdefine_line|#define VT1211_SYSCTL_VRM&t;1600
DECL|macro|VT1211_SYSCTL_UCH
mdefine_line|#define VT1211_SYSCTL_UCH&t;1700
DECL|macro|VT1211_SYSCTL_FAN_DIV
mdefine_line|#define VT1211_SYSCTL_FAN_DIV 2000
DECL|macro|VT1211_SYSCTL_ALARMS
mdefine_line|#define VT1211_SYSCTL_ALARMS 2001
DECL|macro|VT1211_ALARM_IN1
mdefine_line|#define VT1211_ALARM_IN1 0x01
DECL|macro|VT1211_ALARM_IN2
mdefine_line|#define VT1211_ALARM_IN2 0x02
DECL|macro|VT1211_ALARM_IN5
mdefine_line|#define VT1211_ALARM_IN5 0x04
DECL|macro|VT1211_ALARM_IN3
mdefine_line|#define VT1211_ALARM_IN3 0x08
DECL|macro|VT1211_ALARM_TEMP
mdefine_line|#define VT1211_ALARM_TEMP 0x10
DECL|macro|VT1211_ALARM_FAN1
mdefine_line|#define VT1211_ALARM_FAN1 0x40
DECL|macro|VT1211_ALARM_FAN2
mdefine_line|#define VT1211_ALARM_FAN2 0x80
DECL|macro|VT1211_ALARM_IN4
mdefine_line|#define VT1211_ALARM_IN4 0x100
DECL|macro|VT1211_ALARM_IN6
mdefine_line|#define VT1211_ALARM_IN6 0x200
DECL|macro|VT1211_ALARM_TEMP2
mdefine_line|#define VT1211_ALARM_TEMP2 0x800
DECL|macro|VT1211_ALARM_CHAS
mdefine_line|#define VT1211_ALARM_CHAS 0x1000
DECL|macro|VT1211_ALARM_TEMP3
mdefine_line|#define VT1211_ALARM_TEMP3 0x8000
multiline_comment|/* duplicates */
DECL|macro|VT1211_ALARM_IN0
mdefine_line|#define VT1211_ALARM_IN0 VT1211_ALARM_TEMP
DECL|macro|VT1211_ALARM_TEMP4
mdefine_line|#define VT1211_ALARM_TEMP4 VT1211_ALARM_IN1
DECL|macro|VT1211_ALARM_TEMP5
mdefine_line|#define VT1211_ALARM_TEMP5 VT1211_ALARM_IN2
DECL|macro|VT1211_ALARM_TEMP6
mdefine_line|#define VT1211_ALARM_TEMP6 VT1211_ALARM_IN3
DECL|macro|VT1211_ALARM_TEMP7
mdefine_line|#define VT1211_ALARM_TEMP7 VT1211_ALARM_IN4
DECL|macro|LM92_SYSCTL_ALARMS
mdefine_line|#define LM92_SYSCTL_ALARMS&t;&t;2001&t;/* high, low, critical */
DECL|macro|LM92_SYSCTL_TEMP
mdefine_line|#define LM92_SYSCTL_TEMP&t;&t;1200&t;/* high, low, critical, hysterisis, input */
DECL|macro|LM92_ALARM_TEMP_HIGH
mdefine_line|#define LM92_ALARM_TEMP_HIGH&t;0x01
DECL|macro|LM92_ALARM_TEMP_LOW
mdefine_line|#define LM92_ALARM_TEMP_LOW&t;&t;0x02
DECL|macro|LM92_ALARM_TEMP_CRIT
mdefine_line|#define LM92_ALARM_TEMP_CRIT&t;0x04
DECL|macro|LM92_TEMP_HIGH
mdefine_line|#define LM92_TEMP_HIGH&t;&t;&t;0x08
DECL|macro|LM92_TEMP_LOW
mdefine_line|#define LM92_TEMP_LOW&t;&t;&t;0x10
DECL|macro|LM92_TEMP_CRIT
mdefine_line|#define LM92_TEMP_CRIT&t;&t;&t;0x20
DECL|macro|LM92_TEMP_HYST
mdefine_line|#define LM92_TEMP_HYST&t;&t;&t;0x40
DECL|macro|LM92_TEMP_INPUT
mdefine_line|#define LM92_TEMP_INPUT&t;&t;&t;0x80
DECL|macro|VT8231_SYSCTL_IN0
mdefine_line|#define VT8231_SYSCTL_IN0 1000
DECL|macro|VT8231_SYSCTL_IN1
mdefine_line|#define VT8231_SYSCTL_IN1 1001
DECL|macro|VT8231_SYSCTL_IN2
mdefine_line|#define VT8231_SYSCTL_IN2 1002
DECL|macro|VT8231_SYSCTL_IN3
mdefine_line|#define VT8231_SYSCTL_IN3 1003
DECL|macro|VT8231_SYSCTL_IN4
mdefine_line|#define VT8231_SYSCTL_IN4 1004
DECL|macro|VT8231_SYSCTL_IN5
mdefine_line|#define VT8231_SYSCTL_IN5 1005
DECL|macro|VT8231_SYSCTL_IN6
mdefine_line|#define VT8231_SYSCTL_IN6 1006
DECL|macro|VT8231_SYSCTL_FAN1
mdefine_line|#define VT8231_SYSCTL_FAN1 1101
DECL|macro|VT8231_SYSCTL_FAN2
mdefine_line|#define VT8231_SYSCTL_FAN2 1102
DECL|macro|VT8231_SYSCTL_TEMP
mdefine_line|#define VT8231_SYSCTL_TEMP 1200
DECL|macro|VT8231_SYSCTL_TEMP2
mdefine_line|#define VT8231_SYSCTL_TEMP2 1201
DECL|macro|VT8231_SYSCTL_TEMP3
mdefine_line|#define VT8231_SYSCTL_TEMP3 1202
DECL|macro|VT8231_SYSCTL_TEMP4
mdefine_line|#define VT8231_SYSCTL_TEMP4 1203
DECL|macro|VT8231_SYSCTL_TEMP5
mdefine_line|#define VT8231_SYSCTL_TEMP5 1204
DECL|macro|VT8231_SYSCTL_TEMP6
mdefine_line|#define VT8231_SYSCTL_TEMP6 1205
DECL|macro|VT8231_SYSCTL_TEMP7
mdefine_line|#define VT8231_SYSCTL_TEMP7 1206
DECL|macro|VT8231_SYSCTL_VID
mdefine_line|#define VT8231_SYSCTL_VID&t;1300
DECL|macro|VT8231_SYSCTL_PWM1
mdefine_line|#define VT8231_SYSCTL_PWM1&t;1401
DECL|macro|VT8231_SYSCTL_PWM2
mdefine_line|#define VT8231_SYSCTL_PWM2&t;1402
DECL|macro|VT8231_SYSCTL_VRM
mdefine_line|#define VT8231_SYSCTL_VRM&t;1600
DECL|macro|VT8231_SYSCTL_UCH
mdefine_line|#define VT8231_SYSCTL_UCH&t;1700
DECL|macro|VT8231_SYSCTL_FAN_DIV
mdefine_line|#define VT8231_SYSCTL_FAN_DIV 2000
DECL|macro|VT8231_SYSCTL_ALARMS
mdefine_line|#define VT8231_SYSCTL_ALARMS 2001
DECL|macro|VT8231_ALARM_IN1
mdefine_line|#define VT8231_ALARM_IN1 0x01
DECL|macro|VT8231_ALARM_IN2
mdefine_line|#define VT8231_ALARM_IN2 0x02
DECL|macro|VT8231_ALARM_IN5
mdefine_line|#define VT8231_ALARM_IN5 0x04
DECL|macro|VT8231_ALARM_IN3
mdefine_line|#define VT8231_ALARM_IN3 0x08
DECL|macro|VT8231_ALARM_TEMP
mdefine_line|#define VT8231_ALARM_TEMP 0x10
DECL|macro|VT8231_ALARM_FAN1
mdefine_line|#define VT8231_ALARM_FAN1 0x40
DECL|macro|VT8231_ALARM_FAN2
mdefine_line|#define VT8231_ALARM_FAN2 0x80
DECL|macro|VT8231_ALARM_IN4
mdefine_line|#define VT8231_ALARM_IN4 0x100
DECL|macro|VT8231_ALARM_IN6
mdefine_line|#define VT8231_ALARM_IN6 0x200
DECL|macro|VT8231_ALARM_TEMP2
mdefine_line|#define VT8231_ALARM_TEMP2 0x800
DECL|macro|VT8231_ALARM_CHAS
mdefine_line|#define VT8231_ALARM_CHAS 0x1000
DECL|macro|VT8231_ALARM_TEMP3
mdefine_line|#define VT8231_ALARM_TEMP3 0x8000
multiline_comment|/* duplicates */
DECL|macro|VT8231_ALARM_IN0
mdefine_line|#define VT8231_ALARM_IN0 VT8231_ALARM_TEMP
DECL|macro|VT8231_ALARM_TEMP4
mdefine_line|#define VT8231_ALARM_TEMP4 VT8231_ALARM_IN1
DECL|macro|VT8231_ALARM_TEMP5
mdefine_line|#define VT8231_ALARM_TEMP5 VT8231_ALARM_IN2
DECL|macro|VT8231_ALARM_TEMP6
mdefine_line|#define VT8231_ALARM_TEMP6 VT8231_ALARM_IN3
DECL|macro|VT8231_ALARM_TEMP7
mdefine_line|#define VT8231_ALARM_TEMP7 VT8231_ALARM_IN4
DECL|macro|SMARTBATT_SYSCTL_I
mdefine_line|#define SMARTBATT_SYSCTL_I 1001
DECL|macro|SMARTBATT_SYSCTL_V
mdefine_line|#define SMARTBATT_SYSCTL_V 1002
DECL|macro|SMARTBATT_SYSCTL_TEMP
mdefine_line|#define SMARTBATT_SYSCTL_TEMP 1003
DECL|macro|SMARTBATT_SYSCTL_TIME
mdefine_line|#define SMARTBATT_SYSCTL_TIME 1004
DECL|macro|SMARTBATT_SYSCTL_ALARMS
mdefine_line|#define SMARTBATT_SYSCTL_ALARMS 1005
DECL|macro|SMARTBATT_SYSCTL_CHARGE
mdefine_line|#define SMARTBATT_SYSCTL_CHARGE 1006
macro_line|#endif&t;&t;&t;&t;/* def SENSORS_SENSORS_H */
eof
