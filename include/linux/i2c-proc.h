multiline_comment|/*&n;    i2c-proc.h - Part of the i2c package&n;    was originally sensors.h - Part of lm_sensors, Linux kernel modules&n;                               for hardware monitoring&n;    Copyright (c) 1998, 1999  Frodo Looijaard &lt;frodol@dds.nl&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef SENSORS_SENSORS_H
DECL|macro|SENSORS_SENSORS_H
mdefine_line|#define SENSORS_SENSORS_H
macro_line|#ifdef __KERNEL__
multiline_comment|/* Next two must be included before sysctl.h can be included, in 2.0 kernels */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
multiline_comment|/* The type of callback functions used in sensors_{proc,sysctl}_real */
DECL|typedef|i2c_real_callback
r_typedef
r_void
(paren
op_star
id|i2c_real_callback
)paren
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
id|operation
comma
r_int
id|ctl_name
comma
r_int
op_star
id|nrels_mag
comma
r_int
op_star
id|results
)paren
suffix:semicolon
multiline_comment|/* Values for the operation field in the above function type */
DECL|macro|SENSORS_PROC_REAL_INFO
mdefine_line|#define SENSORS_PROC_REAL_INFO 1
DECL|macro|SENSORS_PROC_REAL_READ
mdefine_line|#define SENSORS_PROC_REAL_READ 2
DECL|macro|SENSORS_PROC_REAL_WRITE
mdefine_line|#define SENSORS_PROC_REAL_WRITE 3
multiline_comment|/* These funcion reads or writes a &squot;real&squot; value (encoded by the combination&n;   of an integer and a magnitude, the last is the power of ten the value&n;   should be divided with) to a /proc/sys directory. To use these functions,&n;   you must (before registering the ctl_table) set the extra2 field to the&n;   client, and the extra1 field to a function of the form:&n;      void func(struct i2c_client *client, int operation, int ctl_name,&n;                int *nrels_mag, long *results)&n;   This last function can be called for three values of operation. If&n;   operation equals SENSORS_PROC_REAL_INFO, the magnitude should be returned&n;   in nrels_mag. If operation equals SENSORS_PROC_REAL_READ, values should&n;   be read into results. nrels_mag should return the number of elements&n;   read; the maximum number is put in it on entry. Finally, if operation&n;   equals SENSORS_PROC_REAL_WRITE, the values in results should be&n;   written to the chip. nrels_mag contains on entry the number of elements&n;   found.&n;   In all cases, client points to the client we wish to interact with,&n;   and ctl_name is the SYSCTL id of the file we are accessing. */
r_extern
r_int
id|i2c_sysctl_real
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
op_star
id|name
comma
r_int
id|nlen
comma
r_void
op_star
id|oldval
comma
r_int
op_star
id|oldlenp
comma
r_void
op_star
id|newval
comma
r_int
id|newlen
comma
r_void
op_star
op_star
id|context
)paren
suffix:semicolon
r_extern
r_int
id|i2c_proc_real
c_func
(paren
id|ctl_table
op_star
id|ctl
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|lenp
)paren
suffix:semicolon
multiline_comment|/* These rather complex functions must be called when you want to add or&n;   delete an entry in /proc/sys/dev/sensors/chips (not yet implemented). It&n;   also creates a new directory within /proc/sys/dev/sensors/.&n;   ctl_template should be a template of the newly created directory. It is&n;   copied in memory. The extra2 field of each file is set to point to client.&n;   If any driver wants subdirectories within the newly created directory,&n;   these functions must be updated! */
r_extern
r_int
id|i2c_register_entry
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_const
r_char
op_star
id|prefix
comma
id|ctl_table
op_star
id|ctl_template
comma
r_struct
id|module
op_star
id|controlling_mod
)paren
suffix:semicolon
r_extern
r_void
id|i2c_deregister_entry
c_func
(paren
r_int
id|id
)paren
suffix:semicolon
multiline_comment|/* A structure containing detect information.&n;   Force variables overrule all other variables; they force a detection on&n;   that place. If a specific chip is given, the module blindly assumes this&n;   chip type is present; if a general force (kind == 0) is given, the module&n;   will still try to figure out what type of chip is present. This is useful&n;   if for some reasons the detect for SMBus or ISA address space filled&n;   fails.&n;   probe: insmod parameter. Initialize this list with SENSORS_I2C_END values.&n;     A list of pairs. The first value is a bus number (SENSORS_ISA_BUS for&n;     the ISA bus, -1 for any I2C bus), the second is the address. &n;   kind: The kind of chip. 0 equals any chip.&n;*/
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
multiline_comment|/* A structure containing the detect information.&n;   normal_i2c: filled in by the module writer. Terminated by SENSORS_I2C_END.&n;     A list of I2C addresses which should normally be examined.&n;   normal_i2c_range: filled in by the module writer. Terminated by &n;     SENSORS_I2C_END&n;     A list of pairs of I2C addresses, each pair being an inclusive range of&n;     addresses which should normally be examined.&n;   normal_isa: filled in by the module writer. Terminated by SENSORS_ISA_END.&n;     A list of ISA addresses which should normally be examined.&n;   normal_isa_range: filled in by the module writer. Terminated by &n;     SENSORS_ISA_END&n;     A list of triples. The first two elements are ISA addresses, being an&n;     range of addresses which should normally be examined. The third is the&n;     modulo parameter: only addresses which are 0 module this value relative&n;     to the first address of the range are actually considered.&n;   probe: insmod parameter. Initialize this list with SENSORS_I2C_END values.&n;     A list of pairs. The first value is a bus number (SENSORS_ISA_BUS for&n;     the ISA bus, -1 for any I2C bus), the second is the address. These&n;     addresses are also probed, as if they were in the &squot;normal&squot; list.&n;   probe_range: insmod parameter. Initialize this list with SENSORS_I2C_END &n;     values.&n;     A list of triples. The first value is a bus number (SENSORS_ISA_BUS for&n;     the ISA bus, -1 for any I2C bus), the second and third are addresses. &n;     These form an inclusive range of addresses that are also probed, as&n;     if they were in the &squot;normal&squot; list.&n;   ignore: insmod parameter. Initialize this list with SENSORS_I2C_END values.&n;     A list of pairs. The first value is a bus number (SENSORS_ISA_BUS for&n;     the ISA bus, -1 for any I2C bus), the second is the I2C address. These&n;     addresses are never probed. This parameter overrules &squot;normal&squot; and &n;     &squot;probe&squot;, but not the &squot;force&squot; lists.&n;   ignore_range: insmod parameter. Initialize this list with SENSORS_I2C_END &n;      values.&n;     A list of triples. The first value is a bus number (SENSORS_ISA_BUS for&n;     the ISA bus, -1 for any I2C bus), the second and third are addresses. &n;     These form an inclusive range of I2C addresses that are never probed.&n;     This parameter overrules &squot;normal&squot; and &squot;probe&squot;, but not the &squot;force&squot; lists.&n;   force_data: insmod parameters. A list, ending with an element of which&n;     the force field is NULL.&n;*/
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
DECL|member|normal_i2c_range
r_int
r_int
op_star
id|normal_i2c_range
suffix:semicolon
DECL|member|normal_isa
r_int
r_int
op_star
id|normal_isa
suffix:semicolon
DECL|member|normal_isa_range
r_int
r_int
op_star
id|normal_isa_range
suffix:semicolon
DECL|member|probe
r_int
r_int
op_star
id|probe
suffix:semicolon
DECL|member|probe_range
r_int
r_int
op_star
id|probe_range
suffix:semicolon
DECL|member|ignore
r_int
r_int
op_star
id|ignore
suffix:semicolon
DECL|member|ignore_range
r_int
r_int
op_star
id|ignore_range
suffix:semicolon
DECL|member|forces
r_struct
id|i2c_force_data
op_star
id|forces
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Internal numbers to terminate lists */
DECL|macro|SENSORS_I2C_END
mdefine_line|#define SENSORS_I2C_END 0xfffe
DECL|macro|SENSORS_ISA_END
mdefine_line|#define SENSORS_ISA_END 0xfffefffe
multiline_comment|/* The numbers to use to set an ISA or I2C bus address */
DECL|macro|SENSORS_ISA_BUS
mdefine_line|#define SENSORS_ISA_BUS 9191
DECL|macro|SENSORS_ANY_I2C_BUS
mdefine_line|#define SENSORS_ANY_I2C_BUS 0xffff
multiline_comment|/* The length of the option lists */
DECL|macro|SENSORS_MAX_OPTS
mdefine_line|#define SENSORS_MAX_OPTS 48
multiline_comment|/* Default fill of many variables */
DECL|macro|SENSORS_DEFAULTS
mdefine_line|#define SENSORS_DEFAULTS {SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END, &bslash;&n;                          SENSORS_I2C_END, SENSORS_I2C_END, SENSORS_I2C_END}
multiline_comment|/* This is ugly. We need to evaluate SENSORS_MAX_OPTS before it is &n;   stringified */
DECL|macro|SENSORS_MODPARM_AUX1
mdefine_line|#define SENSORS_MODPARM_AUX1(x) &quot;1-&quot; #x &quot;h&quot;
DECL|macro|SENSORS_MODPARM_AUX
mdefine_line|#define SENSORS_MODPARM_AUX(x) SENSORS_MODPARM_AUX1(x)
DECL|macro|SENSORS_MODPARM
mdefine_line|#define SENSORS_MODPARM SENSORS_MODPARM_AUX(SENSORS_MAX_OPTS)
multiline_comment|/* SENSORS_MODULE_PARM creates a module parameter, and puts it in the&n;   module header */
DECL|macro|SENSORS_MODULE_PARM
mdefine_line|#define SENSORS_MODULE_PARM(var,desc) &bslash;&n;  static unsigned short var[SENSORS_MAX_OPTS] = SENSORS_DEFAULTS; &bslash;&n;  MODULE_PARM(var,SENSORS_MODPARM); &bslash;&n;  MODULE_PARM_DESC(var,desc)
multiline_comment|/* SENSORS_MODULE_PARM creates a &squot;force_*&squot; module parameter, and puts it in&n;   the module header */
DECL|macro|SENSORS_MODULE_PARM_FORCE
mdefine_line|#define SENSORS_MODULE_PARM_FORCE(name) &bslash;&n;  SENSORS_MODULE_PARM(force_ ## name, &bslash;&n;                      &quot;List of adapter,address pairs which are unquestionably&quot; &bslash;&n;                      &quot; assumed to contain a `&quot; # name &quot;&squot; chip&quot;)
multiline_comment|/* This defines several insmod variables, and the addr_data structure */
DECL|macro|SENSORS_INSMOD
mdefine_line|#define SENSORS_INSMOD &bslash;&n;  SENSORS_MODULE_PARM(probe, &bslash;&n;                      &quot;List of adapter,address pairs to scan additionally&quot;); &bslash;&n;  SENSORS_MODULE_PARM(probe_range, &bslash;&n;                      &quot;List of adapter,start-addr,end-addr triples to scan &quot; &bslash;&n;                      &quot;additionally&quot;); &bslash;&n;  SENSORS_MODULE_PARM(ignore, &bslash;&n;                      &quot;List of adapter,address pairs not to scan&quot;); &bslash;&n;  SENSORS_MODULE_PARM(ignore_range, &bslash;&n;                      &quot;List of adapter,start-addr,end-addr triples not to &quot; &bslash;&n;                      &quot;scan&quot;); &bslash;&n;  static struct i2c_address_data addr_data = &bslash;&n;                                       {normal_i2c, normal_i2c_range, &bslash;&n;                                        normal_isa, normal_isa_range, &bslash;&n;                                        probe, probe_range, &bslash;&n;                                        ignore, ignore_range, &bslash;&n;                                        forces}
multiline_comment|/* The following functions create an enum with the chip names as elements. &n;   The first element of the enum is any_chip. These are the only macros&n;   a module will want to use. */
DECL|macro|SENSORS_INSMOD_0
mdefine_line|#define SENSORS_INSMOD_0 &bslash;&n;  enum chips { any_chip }; &bslash;&n;  SENSORS_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip},{NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_1
mdefine_line|#define SENSORS_INSMOD_1(chip1) &bslash;&n;  enum chips { any_chip, chip1 }; &bslash;&n;  SENSORS_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip},&bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_2
mdefine_line|#define SENSORS_INSMOD_2(chip1,chip2) &bslash;&n;  enum chips { any_chip, chip1, chip2 }; &bslash;&n;  SENSORS_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip2); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip}, &bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {force_ ## chip2,chip2}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_3
mdefine_line|#define SENSORS_INSMOD_3(chip1,chip2,chip3) &bslash;&n;  enum chips { any_chip, chip1, chip2, chip3 }; &bslash;&n;  SENSORS_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip2); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip3); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip}, &bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {force_ ## chip2,chip2}, &bslash;&n;                                                 {force_ ## chip3,chip3}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_4
mdefine_line|#define SENSORS_INSMOD_4(chip1,chip2,chip3,chip4) &bslash;&n;  enum chips { any_chip, chip1, chip2, chip3, chip4 }; &bslash;&n;  SENSORS_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip2); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip3); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip4); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip}, &bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {force_ ## chip2,chip2}, &bslash;&n;                                                 {force_ ## chip3,chip3}, &bslash;&n;                                                 {force_ ## chip4,chip4}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_5
mdefine_line|#define SENSORS_INSMOD_5(chip1,chip2,chip3,chip4,chip5) &bslash;&n;  enum chips { any_chip, chip1, chip2, chip3, chip4, chip5 }; &bslash;&n;  SENSORS_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip2); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip3); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip4); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip5); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip}, &bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {force_ ## chip2,chip2}, &bslash;&n;                                                 {force_ ## chip3,chip3}, &bslash;&n;                                                 {force_ ## chip4,chip4}, &bslash;&n;                                                 {force_ ## chip5,chip5}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_6
mdefine_line|#define SENSORS_INSMOD_6(chip1,chip2,chip3,chip4,chip5,chip6) &bslash;&n;  enum chips { any_chip, chip1, chip2, chip3, chip4, chip5, chip6 }; &bslash;&n;  SENSORS_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip2); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip3); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip4); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip5); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip6); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip}, &bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {force_ ## chip2,chip2}, &bslash;&n;                                                 {force_ ## chip3,chip3}, &bslash;&n;                                                 {force_ ## chip4,chip4}, &bslash;&n;                                                 {force_ ## chip5,chip5}, &bslash;&n;                                                 {force_ ## chip6,chip6}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|macro|SENSORS_INSMOD_7
mdefine_line|#define SENSORS_INSMOD_7(chip1,chip2,chip3,chip4,chip5,chip6,chip7) &bslash;&n;  enum chips { any_chip, chip1, chip2, chip3, chip4, chip5, chip6, chip7 }; &bslash;&n;  SENSORS_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip1); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip2); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip3); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip4); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip5); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip6); &bslash;&n;  SENSORS_MODULE_PARM_FORCE(chip7); &bslash;&n;  static struct i2c_force_data forces[] = {{force,any_chip}, &bslash;&n;                                                 {force_ ## chip1,chip1}, &bslash;&n;                                                 {force_ ## chip2,chip2}, &bslash;&n;                                                 {force_ ## chip3,chip3}, &bslash;&n;                                                 {force_ ## chip4,chip4}, &bslash;&n;                                                 {force_ ## chip5,chip5}, &bslash;&n;                                                 {force_ ## chip6,chip6}, &bslash;&n;                                                 {force_ ## chip7,chip7}, &bslash;&n;                                                 {NULL}}; &bslash;&n;  SENSORS_INSMOD
DECL|typedef|i2c_found_addr_proc
r_typedef
r_int
id|i2c_found_addr_proc
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
r_int
id|addr
comma
r_int
r_int
id|flags
comma
r_int
id|kind
)paren
suffix:semicolon
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
id|i2c_found_addr_proc
op_star
id|found_proc
)paren
suffix:semicolon
multiline_comment|/* This macro is used to scale user-input to sensible values in almost all&n;   chip drivers. */
DECL|function|SENSORS_LIMIT
r_extern
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
macro_line|#endif&t;&t;&t;&t;/* def __KERNEL__ */
multiline_comment|/* The maximum length of the prefix */
DECL|macro|SENSORS_PREFIX_MAX
mdefine_line|#define SENSORS_PREFIX_MAX 20
multiline_comment|/* Sysctl IDs */
macro_line|#ifdef DEV_HWMON
DECL|macro|DEV_SENSORS
mdefine_line|#define DEV_SENSORS DEV_HWMON
macro_line|#else&t;&t;&t;&t;/* ndef DEV_HWMOM */
DECL|macro|DEV_SENSORS
mdefine_line|#define DEV_SENSORS 2&t;&t;/* The id of the lm_sensors directory within the&n;&t;&t;&t;&t;   dev table */
macro_line|#endif&t;&t;&t;&t;/* def DEV_HWMON */
DECL|macro|SENSORS_CHIPS
mdefine_line|#define SENSORS_CHIPS 1
DECL|struct|i2c_chips_data
r_struct
id|i2c_chips_data
(brace
DECL|member|sysctl_id
r_int
id|sysctl_id
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|SENSORS_PREFIX_MAX
op_plus
l_int|13
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* def SENSORS_SENSORS_H */
eof
