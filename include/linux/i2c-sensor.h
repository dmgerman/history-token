multiline_comment|/*&n;    i2c-sensor.h - Part of the i2c package&n;    was originally sensors.h - Part of lm_sensors, Linux kernel modules&n;                               for hardware monitoring&n;    Copyright (c) 1998, 1999  Frodo Looijaard &lt;frodol@dds.nl&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _LINUX_I2C_SENSOR_H
DECL|macro|_LINUX_I2C_SENSOR_H
mdefine_line|#define _LINUX_I2C_SENSOR_H
multiline_comment|/* A structure containing detect information.&n;   Force variables overrule all other variables; they force a detection on&n;   that place. If a specific chip is given, the module blindly assumes this&n;   chip type is present; if a general force (kind == 0) is given, the module&n;   will still try to figure out what type of chip is present. This is useful&n;   if for some reasons the detect for SMBus or ISA address space filled&n;   fails.&n;   probe: insmod parameter. Initialize this list with I2C_CLIENT_ISA_END values.&n;     A list of pairs. The first value is a bus number (ANY_I2C_ISA_BUS for&n;     the ISA bus, -1 for any I2C bus), the second is the address. &n;   kind: The kind of chip. 0 equals any chip.&n;*/
DECL|struct|i2c_force_data
r_struct
id|i2c_force_data
(brace
DECL|member|force
r_int
r_int
op_star
id|force
suffix:semicolon
DECL|member|kind
r_int
r_int
id|kind
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* A structure containing the detect information.&n;   normal_i2c: filled in by the module writer. Terminated by I2C_CLIENT_ISA_END.&n;     A list of I2C addresses which should normally be examined.&n;   normal_isa: filled in by the module writer. Terminated by SENSORS_ISA_END.&n;     A list of ISA addresses which should normally be examined.&n;   probe: insmod parameter. Initialize this list with I2C_CLIENT_ISA_END values.&n;     A list of pairs. The first value is a bus number (ANY_I2C_ISA_BUS for&n;     the ISA bus, -1 for any I2C bus), the second is the address. These&n;     addresses are also probed, as if they were in the &squot;normal&squot; list.&n;   ignore: insmod parameter. Initialize this list with I2C_CLIENT_ISA_END values.&n;     A list of pairs. The first value is a bus number (ANY_I2C_ISA_BUS for&n;     the ISA bus, -1 for any I2C bus), the second is the I2C address. These&n;     addresses are never probed. This parameter overrules &squot;normal&squot; and &n;     &squot;probe&squot;, but not the &squot;force&squot; lists.&n;   force_data: insmod parameters. A list, ending with an element of which&n;     the force field is NULL.&n;*/
DECL|struct|i2c_address_data
r_struct
id|i2c_address_data
(brace
DECL|member|normal_i2c
r_int
r_int
op_star
id|normal_i2c
suffix:semicolon
DECL|member|normal_isa
r_int
r_int
op_star
id|normal_isa
suffix:semicolon
DECL|member|probe
r_int
r_int
op_star
id|probe
suffix:semicolon
DECL|member|ignore
r_int
r_int
op_star
id|ignore
suffix:semicolon
DECL|member|forces
r_struct
id|i2c_force_data
op_star
id|forces
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SENSORS_MODULE_PARM_FORCE
mdefine_line|#define SENSORS_MODULE_PARM_FORCE(name) &bslash;&n;  I2C_CLIENT_MODULE_PARM(force_ ## name, &bslash;&n;                      &quot;List of adapter,address pairs which are unquestionably&quot; &bslash;&n;                      &quot; assumed to contain a `&quot; # name &quot;&squot; chip&quot;)
multiline_comment|/* This defines several insmod variables, and the addr_data structure */
DECL|macro|SENSORS_INSMOD
mdefine_line|#define SENSORS_INSMOD &bslash;&n;  I2C_CLIENT_MODULE_PARM(probe, &bslash;&n;                      &quot;List of adapter,address pairs to scan additionally&quot;); &bslash;&n;  I2C_CLIENT_MODULE_PARM(ignore, &bslash;&n;                      &quot;List of adapter,address pairs not to scan&quot;); &bslash;&n;&t;static struct i2c_address_data addr_data = {&t;&t;&t;&bslash;&n;&t;&t;&t;.normal_i2c =&t;&t;normal_i2c,&t;&t;&bslash;&n;&t;&t;&t;.normal_isa =&t;&t;normal_isa,&t;&t;&bslash;&n;&t;&t;&t;.probe =&t;&t;probe,&t;&t;&t;&bslash;&n;&t;&t;&t;.ignore =&t;&t;ignore,&t;&t;&t;&bslash;&n;&t;&t;&t;.forces =&t;&t;forces,&t;&t;&t;&bslash;&n;&t;&t;}
multiline_comment|/* The following functions create an enum with the chip names as elements. &n;   The first element of the enum is any_chip. These are the only macros&n;   a module will want to use. */
DECL|macro|SENSORS_INSMOD_0
mdefine_line|#define SENSORS_INSMOD_0 &bslash;&n;  enum chips { any_chip }; &bslash;&n;  I2C_CLIENT_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip},{NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_1
mdefine_line|#define SENSORS_INSMOD_1(chip1) &bslash;&n;  enum chips { any_chip, chip1 }; &bslash;&n;  I2C_CLIENT_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip},&bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_2
mdefine_line|#define SENSORS_INSMOD_2(chip1,chip2) &bslash;&n;  enum chips { any_chip, chip1, chip2 }; &bslash;&n;  I2C_CLIENT_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip2); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip}, &bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {force_ ## chip2,chip2}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_3
mdefine_line|#define SENSORS_INSMOD_3(chip1,chip2,chip3) &bslash;&n;  enum chips { any_chip, chip1, chip2, chip3 }; &bslash;&n;  I2C_CLIENT_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip2); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip3); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip}, &bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {force_ ## chip2,chip2}, &bslash;&n;                                                 {force_ ## chip3,chip3}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_4
mdefine_line|#define SENSORS_INSMOD_4(chip1,chip2,chip3,chip4) &bslash;&n;  enum chips { any_chip, chip1, chip2, chip3, chip4 }; &bslash;&n;  I2C_CLIENT_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip2); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip3); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip4); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip}, &bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {force_ ## chip2,chip2}, &bslash;&n;                                                 {force_ ## chip3,chip3}, &bslash;&n;                                                 {force_ ## chip4,chip4}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_5
mdefine_line|#define SENSORS_INSMOD_5(chip1,chip2,chip3,chip4,chip5) &bslash;&n;  enum chips { any_chip, chip1, chip2, chip3, chip4, chip5 }; &bslash;&n;  I2C_CLIENT_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip2); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip3); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip4); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip5); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip}, &bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {force_ ## chip2,chip2}, &bslash;&n;                                                 {force_ ## chip3,chip3}, &bslash;&n;                                                 {force_ ## chip4,chip4}, &bslash;&n;                                                 {force_ ## chip5,chip5}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_6
mdefine_line|#define SENSORS_INSMOD_6(chip1,chip2,chip3,chip4,chip5,chip6) &bslash;&n;  enum chips { any_chip, chip1, chip2, chip3, chip4, chip5, chip6 }; &bslash;&n;  I2C_CLIENT_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip2); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip3); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip4); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip5); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip6); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip}, &bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {force_ ## chip2,chip2}, &bslash;&n;                                                 {force_ ## chip3,chip3}, &bslash;&n;                                                 {force_ ## chip4,chip4}, &bslash;&n;                                                 {force_ ## chip5,chip5}, &bslash;&n;                                                 {force_ ## chip6,chip6}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_7
mdefine_line|#define SENSORS_INSMOD_7(chip1,chip2,chip3,chip4,chip5,chip6,chip7) &bslash;&n;  enum chips { any_chip, chip1, chip2, chip3, chip4, chip5, chip6, chip7 }; &bslash;&n;  I2C_CLIENT_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip2); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip3); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip4); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip5); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip6); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip7); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip}, &bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {force_ ## chip2,chip2}, &bslash;&n;                                                 {force_ ## chip3,chip3}, &bslash;&n;                                                 {force_ ## chip4,chip4}, &bslash;&n;                                                 {force_ ## chip5,chip5}, &bslash;&n;                                                 {force_ ## chip6,chip6}, &bslash;&n;                                                 {force_ ## chip7,chip7}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_8
mdefine_line|#define SENSORS_INSMOD_8(chip1,chip2,chip3,chip4,chip5,chip6,chip7,chip8) &bslash;&n;  enum chips { any_chip, chip1, chip2, chip3, chip4, chip5, chip6, chip7, chip8 }; &bslash;&n;  I2C_CLIENT_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip2); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip3); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip4); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip5); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip6); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip7); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip8); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip}, &bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {force_ ## chip2,chip2}, &bslash;&n;                                                 {force_ ## chip3,chip3}, &bslash;&n;                                                 {force_ ## chip4,chip4}, &bslash;&n;                                                 {force_ ## chip5,chip5}, &bslash;&n;                                                 {force_ ## chip6,chip6}, &bslash;&n;                                                 {force_ ## chip7,chip7}, &bslash;&n;                                                 {force_ ## chip8,chip8}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
multiline_comment|/* Detect function. It iterates over all possible addresses itself. For&n;   SMBus addresses, it will only call found_proc if some client is connected&n;   to the SMBus (unless a &squot;force&squot; matched); for ISA detections, this is not&n;   done. */
r_extern
r_int
id|i2c_detect
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
r_struct
id|i2c_address_data
op_star
id|address_data
comma
r_int
(paren
op_star
id|found_proc
)paren
(paren
r_struct
id|i2c_adapter
op_star
comma
r_int
comma
r_int
)paren
)paren
suffix:semicolon
multiline_comment|/* This macro is used to scale user-input to sensible values in almost all&n;   chip drivers. */
DECL|function|SENSORS_LIMIT
r_static
r_inline
r_int
id|SENSORS_LIMIT
c_func
(paren
r_int
id|value
comma
r_int
id|low
comma
r_int
id|high
)paren
(brace
r_if
c_cond
(paren
id|value
OL
id|low
)paren
r_return
id|low
suffix:semicolon
r_else
r_if
c_cond
(paren
id|value
OG
id|high
)paren
r_return
id|high
suffix:semicolon
r_else
r_return
id|value
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* def _LINUX_I2C_SENSOR_H */
eof
