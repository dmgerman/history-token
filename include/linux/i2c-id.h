multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* &t;&t;&t;&t;&t;&t;&t;&t;&t;     */
multiline_comment|/* i2c.h - definitions for the i2c-bus interface&t;&t;&t;     */
multiline_comment|/* &t;&t;&t;&t;&t;&t;&t;&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 1995-1999 Simon G. Vogl&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* $Id: i2c-id.h,v 1.25 2000/10/12 07:27:29 simon Exp $ */
macro_line|#ifndef I2C_ID_H
DECL|macro|I2C_ID_H
mdefine_line|#define I2C_ID_H
multiline_comment|/*&n; * This file is part of the i2c-bus package and contains the identifier&n; * values for drivers, adapters and other folk populating these serial&n; * worlds. &n; *&n; * These will change often (i.e. additions) , therefore this has been &n; * separated from the functional interface definitions of the i2c api.&n; *&n; */
multiline_comment|/*&n; * ---- Driver types -----------------------------------------------------&n; *       device id name + number        function description, i2c address(es)&n; *&n; *  Range 1000-1999 range is defined in sensors/sensors.h &n; *  Range 0x100 - 0x1ff is for V4L2 Common Components &n; *  Range 0xf000 - 0xffff is reserved for local experimentation, and should&n; *        never be used in official drivers &n; */
DECL|macro|I2C_DRIVERID_MSP3400
mdefine_line|#define I2C_DRIVERID_MSP3400&t; 1
DECL|macro|I2C_DRIVERID_TUNER
mdefine_line|#define I2C_DRIVERID_TUNER&t; 2
DECL|macro|I2C_DRIVERID_VIDEOTEX
mdefine_line|#define I2C_DRIVERID_VIDEOTEX&t; 3&t;/* please rename&t;&t;*/
DECL|macro|I2C_DRIVERID_TDA8425
mdefine_line|#define I2C_DRIVERID_TDA8425&t; 4&t;/* stereo sound processor&t;*/
DECL|macro|I2C_DRIVERID_TEA6420
mdefine_line|#define I2C_DRIVERID_TEA6420&t; 5&t;/* audio matrix switch&t;&t;*/
DECL|macro|I2C_DRIVERID_TEA6415C
mdefine_line|#define I2C_DRIVERID_TEA6415C&t; 6&t;/* video matrix switch&t;&t;*/
DECL|macro|I2C_DRIVERID_TDA9840
mdefine_line|#define I2C_DRIVERID_TDA9840&t; 7&t;/* stereo sound processor&t;*/
DECL|macro|I2C_DRIVERID_SAA7111A
mdefine_line|#define I2C_DRIVERID_SAA7111A&t; 8&t;/* video input processor&t;*/
DECL|macro|I2C_DRIVERID_SAA5281
mdefine_line|#define I2C_DRIVERID_SAA5281&t; 9&t;/* videotext decoder&t;&t;*/
DECL|macro|I2C_DRIVERID_SAA7112
mdefine_line|#define I2C_DRIVERID_SAA7112&t;10&t;/* video decoder, image scaler&t;*/
DECL|macro|I2C_DRIVERID_SAA7120
mdefine_line|#define I2C_DRIVERID_SAA7120&t;11&t;/* video encoder&t;&t;*/
DECL|macro|I2C_DRIVERID_SAA7121
mdefine_line|#define I2C_DRIVERID_SAA7121&t;12&t;/* video encoder&t;&t;*/
DECL|macro|I2C_DRIVERID_SAA7185B
mdefine_line|#define I2C_DRIVERID_SAA7185B&t;13&t;/* video encoder&t;&t;*/
DECL|macro|I2C_DRIVERID_CH7003
mdefine_line|#define I2C_DRIVERID_CH7003&t;14&t;/* digital pc to tv encoder &t;*/
DECL|macro|I2C_DRIVERID_PCF8574A
mdefine_line|#define I2C_DRIVERID_PCF8574A&t;15&t;/* i2c expander - 8 bit in/out&t;*/
DECL|macro|I2C_DRIVERID_PCF8582C
mdefine_line|#define I2C_DRIVERID_PCF8582C&t;16&t;/* eeprom&t;&t;&t;*/
DECL|macro|I2C_DRIVERID_AT24Cxx
mdefine_line|#define I2C_DRIVERID_AT24Cxx&t;17&t;/* eeprom 1/2/4/8/16 K &t;&t;*/
DECL|macro|I2C_DRIVERID_TEA6300
mdefine_line|#define I2C_DRIVERID_TEA6300&t;18&t;/* audio mixer&t;&t;&t;*/
DECL|macro|I2C_DRIVERID_BT829
mdefine_line|#define I2C_DRIVERID_BT829&t;19&t;/* pc to tv encoder&t;&t;*/
DECL|macro|I2C_DRIVERID_TDA9850
mdefine_line|#define I2C_DRIVERID_TDA9850&t;20&t;/* audio mixer&t;&t;&t;*/
DECL|macro|I2C_DRIVERID_TDA9855
mdefine_line|#define I2C_DRIVERID_TDA9855&t;21&t;/* audio mixer&t;&t;&t;*/
DECL|macro|I2C_DRIVERID_SAA7110
mdefine_line|#define I2C_DRIVERID_SAA7110&t;22&t;/* &t;&t;&t;&t;*/
DECL|macro|I2C_DRIVERID_MGATVO
mdefine_line|#define I2C_DRIVERID_MGATVO&t;23&t;/* Matrox TVOut&t;&t;&t;*/
DECL|macro|I2C_DRIVERID_SAA5249
mdefine_line|#define I2C_DRIVERID_SAA5249&t;24&t;/* SAA5249 and compatibles&t;*/
DECL|macro|I2C_DRIVERID_PCF8583
mdefine_line|#define I2C_DRIVERID_PCF8583&t;25&t;/* real time clock&t;&t;*/
DECL|macro|I2C_DRIVERID_SAB3036
mdefine_line|#define I2C_DRIVERID_SAB3036&t;26&t;/* SAB3036 tuner&t;&t;*/
DECL|macro|I2C_DRIVERID_TDA7432
mdefine_line|#define I2C_DRIVERID_TDA7432&t;27&t;/* Stereo sound processor&t;*/
DECL|macro|I2C_DRIVERID_TVMIXER
mdefine_line|#define I2C_DRIVERID_TVMIXER    28      /* Mixer driver for tv cards    */
DECL|macro|I2C_DRIVERID_TVAUDIO
mdefine_line|#define I2C_DRIVERID_TVAUDIO    29      /* Generic TV sound driver      */
DECL|macro|I2C_DRIVERID_DPL3518
mdefine_line|#define I2C_DRIVERID_DPL3518    30      /* Dolby decoder chip           */
DECL|macro|I2C_DRIVERID_TDA9873
mdefine_line|#define I2C_DRIVERID_TDA9873    31      /* TV sound decoder chip        */
DECL|macro|I2C_DRIVERID_TDA9875
mdefine_line|#define I2C_DRIVERID_TDA9875    32      /* TV sound decoder chip        */
DECL|macro|I2C_DRIVERID_PIC16C54_PV9
mdefine_line|#define I2C_DRIVERID_PIC16C54_PV9 33    /* Audio mux/ir receiver        */
DECL|macro|I2C_DRIVERID_SBATT
mdefine_line|#define I2C_DRIVERID_SBATT      34     /* Smart Battery Device&t;&t;*/
DECL|macro|I2C_DRIVERID_SBS
mdefine_line|#define I2C_DRIVERID_SBS        35     /* SB System Manager&t;&t;*/
DECL|macro|I2C_DRIVERID_VES1893
mdefine_line|#define I2C_DRIVERID_VES1893&t;36     /* VLSI DVB-S decoder&t;&t;*/
DECL|macro|I2C_DRIVERID_VES1820
mdefine_line|#define I2C_DRIVERID_VES1820&t;37     /* VLSI DVB-C decoder&t;&t;*/
DECL|macro|I2C_DRIVERID_SAA7113
mdefine_line|#define I2C_DRIVERID_SAA7113&t;38     /* video decoder&t;&t;&t;*/
DECL|macro|I2C_DRIVERID_TDA8444
mdefine_line|#define I2C_DRIVERID_TDA8444&t;39     /* octuple 6-bit DAC             */
DECL|macro|I2C_DRIVERID_EXP0
mdefine_line|#define I2C_DRIVERID_EXP0&t;0xF0&t;/* experimental use id&squot;s&t;*/
DECL|macro|I2C_DRIVERID_EXP1
mdefine_line|#define I2C_DRIVERID_EXP1&t;0xF1
DECL|macro|I2C_DRIVERID_EXP2
mdefine_line|#define I2C_DRIVERID_EXP2&t;0xF2
DECL|macro|I2C_DRIVERID_EXP3
mdefine_line|#define I2C_DRIVERID_EXP3&t;0xF3
DECL|macro|I2C_DRIVERID_I2CDEV
mdefine_line|#define I2C_DRIVERID_I2CDEV&t;900
DECL|macro|I2C_DRIVERID_I2CPROC
mdefine_line|#define I2C_DRIVERID_I2CPROC&t;901
multiline_comment|/*&n; * ---- Adapter types ----------------------------------------------------&n; *&n; * First, we distinguish between several algorithms to access the hardware&n; * interface types, as a PCF 8584 needs other care than a bit adapter.&n; */
DECL|macro|I2C_ALGO_NONE
mdefine_line|#define I2C_ALGO_NONE&t;0x000000
DECL|macro|I2C_ALGO_BIT
mdefine_line|#define I2C_ALGO_BIT&t;0x010000&t;/* bit style adapters&t;&t;*/
DECL|macro|I2C_ALGO_PCF
mdefine_line|#define I2C_ALGO_PCF&t;0x020000&t;/* PCF 8584 style adapters&t;*/
DECL|macro|I2C_ALGO_ATI
mdefine_line|#define I2C_ALGO_ATI&t;0x030000&t;/* ATI video card&t;&t;*/
DECL|macro|I2C_ALGO_SMBUS
mdefine_line|#define I2C_ALGO_SMBUS&t;0x040000
DECL|macro|I2C_ALGO_ISA
mdefine_line|#define I2C_ALGO_ISA &t;0x050000&t;/* lm_sensors ISA pseudo-adapter */
DECL|macro|I2C_ALGO_SAA7146
mdefine_line|#define I2C_ALGO_SAA7146 0x060000&t;/* SAA 7146 video decoder bus&t;*/
DECL|macro|I2C_ALGO_ACB
mdefine_line|#define I2C_ALGO_ACB &t;0x070000&t;/* ACCESS.bus algorithm         */
DECL|macro|I2C_ALGO_EC
mdefine_line|#define I2C_ALGO_EC     0x100000        /* ACPI embedded controller     */
DECL|macro|I2C_ALGO_MPC8XX
mdefine_line|#define I2C_ALGO_MPC8XX 0x110000&t;/* MPC8xx PowerPC I2C algorithm */
DECL|macro|I2C_ALGO_EXP
mdefine_line|#define I2C_ALGO_EXP&t;0x800000&t;/* experimental&t;&t;&t;*/
DECL|macro|I2C_ALGO_MASK
mdefine_line|#define I2C_ALGO_MASK&t;0xff0000&t;/* Mask for algorithms&t;&t;*/
DECL|macro|I2C_ALGO_SHIFT
mdefine_line|#define I2C_ALGO_SHIFT&t;0x10&t;/* right shift to get index values &t;*/
DECL|macro|I2C_HW_ADAPS
mdefine_line|#define I2C_HW_ADAPS&t;0x10000&t;&t;/* # adapter types&t;&t;*/
DECL|macro|I2C_HW_MASK
mdefine_line|#define I2C_HW_MASK&t;0xffff&t;&t;
multiline_comment|/* hw specific modules that are defined per algorithm layer&n; */
multiline_comment|/* --- Bit algorithm adapters &t;&t;&t;&t;&t;&t;*/
DECL|macro|I2C_HW_B_LP
mdefine_line|#define I2C_HW_B_LP&t;0x00&t;/* Parallel port Philips style adapter&t;*/
DECL|macro|I2C_HW_B_LPC
mdefine_line|#define I2C_HW_B_LPC&t;0x01&t;/* Parallel port, over control reg.&t;*/
DECL|macro|I2C_HW_B_SER
mdefine_line|#define I2C_HW_B_SER&t;0x02&t;/* Serial line interface&t;&t;*/
DECL|macro|I2C_HW_B_ELV
mdefine_line|#define I2C_HW_B_ELV&t;0x03&t;/* ELV Card&t;&t;&t;&t;*/
DECL|macro|I2C_HW_B_VELLE
mdefine_line|#define I2C_HW_B_VELLE&t;0x04&t;/* Vellemann K8000&t;&t;&t;*/
DECL|macro|I2C_HW_B_BT848
mdefine_line|#define I2C_HW_B_BT848&t;0x05&t;/* BT848 video boards&t;&t;&t;*/
DECL|macro|I2C_HW_B_WNV
mdefine_line|#define I2C_HW_B_WNV&t;0x06&t;/* Winnov Videums&t;&t;&t;*/
DECL|macro|I2C_HW_B_VIA
mdefine_line|#define I2C_HW_B_VIA&t;0x07&t;/* Via vt82c586b&t;&t;&t;*/
DECL|macro|I2C_HW_B_HYDRA
mdefine_line|#define I2C_HW_B_HYDRA&t;0x08&t;/* Apple Hydra Mac I/O&t;&t;&t;*/
DECL|macro|I2C_HW_B_G400
mdefine_line|#define I2C_HW_B_G400&t;0x09&t;/* Matrox G400&t;&t;&t;&t;*/
DECL|macro|I2C_HW_B_I810
mdefine_line|#define I2C_HW_B_I810&t;0x0a&t;/* Intel I810 &t;&t;&t;&t;*/
DECL|macro|I2C_HW_B_VOO
mdefine_line|#define I2C_HW_B_VOO&t;0x0b&t;/* 3dfx Voodoo 3 / Banshee      &t;*/
DECL|macro|I2C_HW_B_RIVA
mdefine_line|#define I2C_HW_B_RIVA&t;0x10&t;/* Riva based graphics cards&t;&t;*/
DECL|macro|I2C_HW_B_IOC
mdefine_line|#define I2C_HW_B_IOC&t;0x11&t;/* IOC bit-wiggling&t;&t;&t;*/
multiline_comment|/* --- PCF 8584 based algorithms&t;&t;&t;&t;&t;*/
DECL|macro|I2C_HW_P_LP
mdefine_line|#define I2C_HW_P_LP&t;0x00&t;/* Parallel port interface&t;&t;*/
DECL|macro|I2C_HW_P_ISA
mdefine_line|#define I2C_HW_P_ISA&t;0x01&t;/* generic ISA Bus inteface card&t;*/
DECL|macro|I2C_HW_P_ELEK
mdefine_line|#define I2C_HW_P_ELEK&t;0x02&t;/* Elektor ISA Bus inteface card&t;*/
multiline_comment|/* --- ACPI Embedded controller algorithms                              */
DECL|macro|I2C_HW_ACPI_EC
mdefine_line|#define I2C_HW_ACPI_EC          0x00
multiline_comment|/* --- MPC8xx PowerPC adapters&t;&t;&t;&t;&t;&t;*/
DECL|macro|I2C_HW_MPC8XX_EPON
mdefine_line|#define I2C_HW_MPC8XX_EPON 0x00&t;/* Eponymous MPC8xx I2C adapter &t;*/
multiline_comment|/* --- SMBus only adapters&t;&t;&t;&t;&t;&t;*/
DECL|macro|I2C_HW_SMBUS_PIIX4
mdefine_line|#define I2C_HW_SMBUS_PIIX4&t;0x00
DECL|macro|I2C_HW_SMBUS_ALI15X3
mdefine_line|#define I2C_HW_SMBUS_ALI15X3&t;0x01
DECL|macro|I2C_HW_SMBUS_VIA2
mdefine_line|#define I2C_HW_SMBUS_VIA2&t;0x02
DECL|macro|I2C_HW_SMBUS_VOODOO3
mdefine_line|#define I2C_HW_SMBUS_VOODOO3&t;0x03
DECL|macro|I2C_HW_SMBUS_I801
mdefine_line|#define I2C_HW_SMBUS_I801&t;0x04
DECL|macro|I2C_HW_SMBUS_AMD756
mdefine_line|#define I2C_HW_SMBUS_AMD756&t;0x05
DECL|macro|I2C_HW_SMBUS_SIS5595
mdefine_line|#define I2C_HW_SMBUS_SIS5595&t;0x06
DECL|macro|I2C_HW_SMBUS_ALI1535
mdefine_line|#define I2C_HW_SMBUS_ALI1535&t;0x07
multiline_comment|/* --- ISA pseudo-adapter&t;&t;&t;&t;&t;&t;*/
DECL|macro|I2C_HW_ISA
mdefine_line|#define I2C_HW_ISA 0x00
macro_line|#endif /* I2C_ID_H */
eof
