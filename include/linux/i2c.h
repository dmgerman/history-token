multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* &t;&t;&t;&t;&t;&t;&t;&t;&t;     */
multiline_comment|/* i2c.h - definitions for the i2c-bus interface&t;&t;&t;     */
multiline_comment|/* &t;&t;&t;&t;&t;&t;&t;&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 1995-2000 Simon G. Vogl&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* With some changes from Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt; and&n;   Frodo Looijaard &lt;frodol@dds.nl&gt; */
multiline_comment|/* $Id: i2c.h,v 1.42 2000/09/06 20:14:06 frodo Exp $ */
macro_line|#ifndef I2C_H
DECL|macro|I2C_H
mdefine_line|#define I2C_H
macro_line|#include &lt;linux/i2c-id.h&gt;&t;/* id values of adapters et. al. &t;*/
macro_line|#include &lt;linux/types.h&gt;
r_struct
id|i2c_msg
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* --- Includes and compatibility declarations ------------------------ */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifndef KERNEL_VERSION
DECL|macro|KERNEL_VERSION
mdefine_line|#define KERNEL_VERSION(a,b,c) (((a) &lt;&lt; 16) | ((b) &lt;&lt; 8) | (c))
macro_line|#endif
macro_line|#include &lt;asm/page.h&gt;&t;&t;&t;/* for 2.2.xx &t;&t;&t;*/
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,0,25)
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#else
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* --- General options ------------------------------------------------&t;*/
DECL|macro|I2C_ALGO_MAX
mdefine_line|#define I2C_ALGO_MAX&t;4&t;&t;/* control memory consumption&t;*/
DECL|macro|I2C_ADAP_MAX
mdefine_line|#define I2C_ADAP_MAX&t;16
DECL|macro|I2C_DRIVER_MAX
mdefine_line|#define I2C_DRIVER_MAX&t;16
DECL|macro|I2C_CLIENT_MAX
mdefine_line|#define I2C_CLIENT_MAX&t;32
DECL|macro|I2C_DUMMY_MAX
mdefine_line|#define I2C_DUMMY_MAX 4
r_struct
id|i2c_algorithm
suffix:semicolon
r_struct
id|i2c_adapter
suffix:semicolon
r_struct
id|i2c_client
suffix:semicolon
r_struct
id|i2c_driver
suffix:semicolon
r_struct
id|i2c_client_address_data
suffix:semicolon
r_union
id|i2c_smbus_data
suffix:semicolon
multiline_comment|/*&n; * The master routines are the ones normally used to transmit data to devices&n; * on a bus (or read from them). Apart from two basic transfer functions to &n; * transmit one message at a time, a more complex version can be used to &n; * transmit an arbitrary number of messages without interruption.&n; */
r_extern
r_int
id|i2c_master_send
c_func
(paren
r_struct
id|i2c_client
op_star
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2c_master_recv
c_func
(paren
r_struct
id|i2c_client
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Transfer num messages.&n; */
r_extern
r_int
id|i2c_transfer
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_struct
id|i2c_msg
id|msg
(braket
)braket
comma
r_int
id|num
)paren
suffix:semicolon
multiline_comment|/*&n; * Some adapter types (i.e. PCF 8584 based ones) may support slave behaviuor. &n; * This is not tested/implemented yet and will change in the future.&n; */
r_extern
r_int
id|i2c_slave_send
c_func
(paren
r_struct
id|i2c_client
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2c_slave_recv
c_func
(paren
r_struct
id|i2c_client
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* This is the very generalized SMBus access routine. You probably do not&n;   want to use this, though; one of the functions below may be much easier,&n;   and probably just as fast. &n;   Note that we use i2c_adapter here, because you do not need a specific&n;   smbus adapter to call this function. */
r_extern
id|s32
id|i2c_smbus_xfer
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
id|u16
id|addr
comma
r_int
r_int
id|flags
comma
r_char
id|read_write
comma
id|u8
id|command
comma
r_int
id|size
comma
r_union
id|i2c_smbus_data
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* Now follow the &squot;nice&squot; access routines. These also document the calling&n;   conventions of smbus_access. */
r_extern
id|s32
id|i2c_smbus_write_quick
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|value
)paren
suffix:semicolon
r_extern
id|s32
id|i2c_smbus_read_byte
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
r_extern
id|s32
id|i2c_smbus_write_byte
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|value
)paren
suffix:semicolon
r_extern
id|s32
id|i2c_smbus_read_byte_data
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|command
)paren
suffix:semicolon
r_extern
id|s32
id|i2c_smbus_write_byte_data
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|command
comma
id|u8
id|value
)paren
suffix:semicolon
r_extern
id|s32
id|i2c_smbus_read_word_data
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|command
)paren
suffix:semicolon
r_extern
id|s32
id|i2c_smbus_write_word_data
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|command
comma
id|u16
id|value
)paren
suffix:semicolon
r_extern
id|s32
id|i2c_smbus_process_call
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|command
comma
id|u16
id|value
)paren
suffix:semicolon
multiline_comment|/* Returns the number of read bytes */
r_extern
id|s32
id|i2c_smbus_read_block_data
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|command
comma
id|u8
op_star
id|values
)paren
suffix:semicolon
r_extern
id|s32
id|i2c_smbus_write_block_data
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|command
comma
id|u8
id|length
comma
id|u8
op_star
id|values
)paren
suffix:semicolon
r_extern
id|s32
id|i2c_smbus_write_i2c_block_data
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
id|u8
id|command
comma
id|u8
id|length
comma
id|u8
op_star
id|values
)paren
suffix:semicolon
multiline_comment|/*&n; * A driver is capable of handling one or more physical devices present on&n; * I2C adapters. This information is used to inform the driver of adapter&n; * events.&n; */
DECL|struct|i2c_driver
r_struct
id|i2c_driver
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* div., see below&t;&t;*/
multiline_comment|/* Notifies the driver that a new bus has appeared. This routine&n;&t; * can be used by the driver to test if the bus meets its conditions&n;&t; * &amp; seek for the presence of the chip(s) it supports. If found, it &n;&t; * registers the client(s) that are on the bus to the i2c admin. via&n;&t; * i2c_attach_client.&n;&t; */
DECL|member|attach_adapter
r_int
(paren
op_star
id|attach_adapter
)paren
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
multiline_comment|/* tells the driver that a client is about to be deleted &amp; gives it &n;&t; * the chance to remove its private data. Also, if the client struct&n;&t; * has been dynamically allocated by the driver in the function above,&n;&t; * it must be freed here.&n;&t; */
DECL|member|detach_client
r_int
(paren
op_star
id|detach_client
)paren
(paren
r_struct
id|i2c_client
op_star
)paren
suffix:semicolon
multiline_comment|/* a ioctl like command that can be used to perform specific functions&n;&t; * with the device.&n;&t; */
DECL|member|command
r_int
(paren
op_star
id|command
)paren
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
multiline_comment|/* These two are mainly used for bookkeeping &amp; dynamic unloading of &n;&t; * kernel modules. inc_use tells the driver that a client is being  &n;&t; * used by another module &amp; that it should increase its ref. counter.&n;&t; * dec_use is the inverse operation.&n;&t; * NB: Make sure you have no circular dependencies, or else you get a &n;&t; * deadlock when trying to unload the modules.&n;&t;* You should use the i2c_{inc,dec}_use_client functions instead of&n;&t;* calling this function directly.&n;&t; */
DECL|member|inc_use
r_void
(paren
op_star
id|inc_use
)paren
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
DECL|member|dec_use
r_void
(paren
op_star
id|dec_use
)paren
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * i2c_client identifies a single device (i.e. chip) that is connected to an &n; * i2c bus. The behaviour is defined by the routines of the driver. This&n; * function is mainly used for lookup &amp; other admin. functions.&n; */
DECL|struct|i2c_client
r_struct
id|i2c_client
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* div., see below&t;&t;*/
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* chip address - NOTE: 7bit &t;*/
multiline_comment|/* addresses are stored in the&t;*/
multiline_comment|/* _LOWER_ 7 bits of this char&t;*/
multiline_comment|/* addr: unsigned int to make lm_sensors i2c-isa adapter work&n;&t;  more cleanly. It does not take any more memory space, due to&n;&t;  alignment considerations */
DECL|member|adapter
r_struct
id|i2c_adapter
op_star
id|adapter
suffix:semicolon
multiline_comment|/* the adapter we sit on&t;*/
DECL|member|driver
r_struct
id|i2c_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* and our access routines&t;*/
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* for the clients&t;&t;*/
DECL|member|usage_count
r_int
id|usage_count
suffix:semicolon
multiline_comment|/* How many accesses currently  */
multiline_comment|/* to the client&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/*&n; * The following structs are for those who like to implement new bus drivers:&n; * i2c_algorithm is the interface to a class of hardware solutions which can&n; * be addressed using the same bus algorithms - i.e. bit-banging or the PCF8584&n; * to name two of the most common.&n; */
DECL|struct|i2c_algorithm
r_struct
id|i2c_algorithm
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* textual description &t;*/
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* If a adapter algorithm can&squot;t to I2C-level access, set master_xfer&n;&t;   to NULL. If an adapter algorithm can do SMBus access, set &n;&t;   smbus_xfer. If set to NULL, the SMBus protocol is simulated&n;&t;   using common I2C messages */
DECL|member|master_xfer
r_int
(paren
op_star
id|master_xfer
)paren
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_struct
id|i2c_msg
id|msgs
(braket
)braket
comma
r_int
id|num
)paren
suffix:semicolon
DECL|member|smbus_xfer
r_int
(paren
op_star
id|smbus_xfer
)paren
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
id|u16
id|addr
comma
r_int
r_int
id|flags
comma
r_char
id|read_write
comma
id|u8
id|command
comma
r_int
id|size
comma
r_union
id|i2c_smbus_data
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* --- these optional/future use for some adapter types.*/
DECL|member|slave_send
r_int
(paren
op_star
id|slave_send
)paren
(paren
r_struct
id|i2c_adapter
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|slave_recv
r_int
(paren
op_star
id|slave_recv
)paren
(paren
r_struct
id|i2c_adapter
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* --- ioctl like call to set div. parameters. */
DECL|member|algo_control
r_int
(paren
op_star
id|algo_control
)paren
(paren
r_struct
id|i2c_adapter
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* To determine what the adapter supports */
DECL|member|functionality
id|u32
(paren
op_star
id|functionality
)paren
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,1,29)
r_struct
id|proc_dir_entry
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * i2c_adapter is the structure used to identify a physical i2c bus along&n; * with the access algorithms necessary to access it.&n; */
DECL|struct|i2c_adapter
r_struct
id|i2c_adapter
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* some useful name to identify the adapter&t;*/
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* == is algo-&gt;id | hwdep.struct-&gt;id, &t;&t;*/
multiline_comment|/* for registered values see below&t;&t;*/
DECL|member|algo
r_struct
id|i2c_algorithm
op_star
id|algo
suffix:semicolon
multiline_comment|/* the algorithm to access the bus&t;*/
DECL|member|algo_data
r_void
op_star
id|algo_data
suffix:semicolon
multiline_comment|/* --- These may be NULL, but should increase the module use count */
DECL|member|inc_use
r_void
(paren
op_star
id|inc_use
)paren
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
DECL|member|dec_use
r_void
(paren
op_star
id|dec_use
)paren
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
multiline_comment|/* --- administration stuff. */
DECL|member|client_register
r_int
(paren
op_star
id|client_register
)paren
(paren
r_struct
id|i2c_client
op_star
)paren
suffix:semicolon
DECL|member|client_unregister
r_int
(paren
op_star
id|client_unregister
)paren
(paren
r_struct
id|i2c_client
op_star
)paren
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* private data for the adapter&t;&t;&t;*/
multiline_comment|/* some data fields that are used by all types&t;*/
multiline_comment|/* these data fields are readonly to the public&t;*/
multiline_comment|/* and can be set via the i2c_ioctl call&t;*/
multiline_comment|/* data fields that are valid for all devices&t;*/
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* flags specifying div. data&t;&t;*/
DECL|member|clients
r_struct
id|i2c_client
op_star
id|clients
(braket
id|I2C_CLIENT_MAX
)braket
suffix:semicolon
DECL|member|client_count
r_int
id|client_count
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|retries
r_int
id|retries
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS 
multiline_comment|/* No need to set this when you initialize the adapter          */
DECL|member|inode
r_int
id|inode
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,1,29)
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
macro_line|#endif
macro_line|#endif /* def CONFIG_PROC_FS */
)brace
suffix:semicolon
multiline_comment|/*flags for the driver struct: */
DECL|macro|I2C_DF_NOTIFY
mdefine_line|#define I2C_DF_NOTIFY&t;0x01&t;&t;/* notify on bus (de/a)ttaches &t;*/
DECL|macro|I2C_DF_DUMMY
mdefine_line|#define I2C_DF_DUMMY&t;0x02&t;&t;/* do not connect any clients */
multiline_comment|/*flags for the client struct: */
DECL|macro|I2C_CLIENT_ALLOW_USE
mdefine_line|#define I2C_CLIENT_ALLOW_USE&t;&t;0x01&t;/* Client allows access */
DECL|macro|I2C_CLIENT_ALLOW_MULTIPLE_USE
mdefine_line|#define I2C_CLIENT_ALLOW_MULTIPLE_USE &t;0x02  &t;/* Allow multiple access-locks */
multiline_comment|/* on an i2c_client */
multiline_comment|/* i2c_client_address_data is the struct for holding default client&n; * addresses for a driver and for the parameters supplied on the&n; * command line&n; */
DECL|struct|i2c_client_address_data
r_struct
id|i2c_client_address_data
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
DECL|member|force
r_int
r_int
op_star
id|force
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Internal numbers to terminate lists */
DECL|macro|I2C_CLIENT_END
mdefine_line|#define I2C_CLIENT_END 0xfffe
multiline_comment|/* The numbers to use to set I2C bus address */
DECL|macro|ANY_I2C_BUS
mdefine_line|#define ANY_I2C_BUS 0xffff
multiline_comment|/* The length of the option lists */
DECL|macro|I2C_CLIENT_MAX_OPTS
mdefine_line|#define I2C_CLIENT_MAX_OPTS 48
multiline_comment|/* ----- functions exported by i2c.o */
multiline_comment|/* administration...&n; */
r_extern
r_int
id|i2c_add_adapter
c_func
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2c_del_adapter
c_func
(paren
r_struct
id|i2c_adapter
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2c_add_driver
c_func
(paren
r_struct
id|i2c_driver
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2c_del_driver
c_func
(paren
r_struct
id|i2c_driver
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2c_attach_client
c_func
(paren
r_struct
id|i2c_client
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2c_detach_client
c_func
(paren
r_struct
id|i2c_client
op_star
)paren
suffix:semicolon
multiline_comment|/* Only call these if you grab a resource that makes unloading the&n;   client and the adapter it is on completely impossible. Like when a&n;   /proc directory is entered. */
r_extern
r_void
id|i2c_inc_use_client
c_func
(paren
r_struct
id|i2c_client
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2c_dec_use_client
c_func
(paren
r_struct
id|i2c_client
op_star
)paren
suffix:semicolon
multiline_comment|/* New function: This is to get an i2c_client-struct for controlling the &n;   client either by using i2c_control-function or having the &n;   client-module export functions that can be used with the i2c_client&n;   -struct. */
r_extern
r_struct
id|i2c_client
op_star
id|i2c_get_client
c_func
(paren
r_int
id|driver_id
comma
r_int
id|adapter_id
comma
r_struct
id|i2c_client
op_star
id|prev
)paren
suffix:semicolon
multiline_comment|/* Should be used with new function&n;   extern struct i2c_client *i2c_get_client(int,int,struct i2c_client *);&n;   to make sure that client-struct is valid and that it is okay to access&n;   the i2c-client. &n;   returns -EACCES if client doesn&squot;t allow use (default)&n;   returns -EBUSY if client doesn&squot;t allow multiple use (default) and &n;   usage_count &gt;0 */
r_extern
r_int
id|i2c_use_client
c_func
(paren
r_struct
id|i2c_client
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2c_release_client
c_func
(paren
r_struct
id|i2c_client
op_star
)paren
suffix:semicolon
multiline_comment|/* returns -EBUSY if address has been taken, 0 if not. Note that the only&n;   other place at which this is called is within i2c_attach_client; so&n;   you can cheat by simply not registering. Not recommended, of course! */
r_extern
r_int
id|i2c_check_addr
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
r_int
id|addr
)paren
suffix:semicolon
multiline_comment|/* Detect function. It itterates over all possible addresses itself.&n; * It will only call found_proc if some client is connected at the&n; * specific address (unless a &squot;force&squot; matched);&n; */
DECL|typedef|i2c_client_found_addr_proc
r_typedef
r_int
id|i2c_client_found_addr_proc
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
r_extern
r_int
id|i2c_probe
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
r_struct
id|i2c_client_address_data
op_star
id|address_data
comma
id|i2c_client_found_addr_proc
op_star
id|found_proc
)paren
suffix:semicolon
multiline_comment|/* An ioctl like call to set div. parameters of the adapter.&n; */
r_extern
r_int
id|i2c_control
c_func
(paren
r_struct
id|i2c_client
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* This call returns a unique low identifier for each registered adapter,&n; * or -1 if the adapter was not regisitered. &n; */
r_extern
r_int
id|i2c_adapter_id
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
suffix:semicolon
multiline_comment|/* Return the functionality mask */
r_extern
id|u32
id|i2c_get_functionality
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
suffix:semicolon
multiline_comment|/* Return 1 if adapter supports everything we need, 0 if not. */
r_extern
r_int
id|i2c_check_functionality
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
id|u32
id|func
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * I2C Message - used for pure i2c transaction, also from /dev interface&n; */
DECL|struct|i2c_msg
r_struct
id|i2c_msg
(brace
DECL|member|addr
id|__u16
id|addr
suffix:semicolon
multiline_comment|/* slave address&t;&t;&t;*/
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|macro|I2C_M_TEN
mdefine_line|#define I2C_M_TEN&t;0x10&t;/* we have a ten bit chip address&t;*/
DECL|macro|I2C_M_RD
mdefine_line|#define I2C_M_RD&t;0x01
DECL|macro|I2C_M_NOSTART
mdefine_line|#define I2C_M_NOSTART&t;0x4000
DECL|macro|I2C_M_REV_DIR_ADDR
mdefine_line|#define I2C_M_REV_DIR_ADDR&t;0x2000
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* msg length&t;&t;&t;&t;*/
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
multiline_comment|/* pointer to msg data&t;&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/* To determine what functionality is present */
DECL|macro|I2C_FUNC_I2C
mdefine_line|#define I2C_FUNC_I2C&t;&t;&t;0x00000001
DECL|macro|I2C_FUNC_10BIT_ADDR
mdefine_line|#define I2C_FUNC_10BIT_ADDR&t;&t;0x00000002
DECL|macro|I2C_FUNC_PROTOCOL_MANGLING
mdefine_line|#define I2C_FUNC_PROTOCOL_MANGLING&t;0x00000004 /* I2C_M_{REV_DIR_ADDR,NOSTART} */
DECL|macro|I2C_FUNC_SMBUS_QUICK
mdefine_line|#define I2C_FUNC_SMBUS_QUICK&t;&t;0x00010000 
DECL|macro|I2C_FUNC_SMBUS_READ_BYTE
mdefine_line|#define I2C_FUNC_SMBUS_READ_BYTE&t;0x00020000 
DECL|macro|I2C_FUNC_SMBUS_WRITE_BYTE
mdefine_line|#define I2C_FUNC_SMBUS_WRITE_BYTE&t;0x00040000 
DECL|macro|I2C_FUNC_SMBUS_READ_BYTE_DATA
mdefine_line|#define I2C_FUNC_SMBUS_READ_BYTE_DATA&t;0x00080000 
DECL|macro|I2C_FUNC_SMBUS_WRITE_BYTE_DATA
mdefine_line|#define I2C_FUNC_SMBUS_WRITE_BYTE_DATA&t;0x00100000 
DECL|macro|I2C_FUNC_SMBUS_READ_WORD_DATA
mdefine_line|#define I2C_FUNC_SMBUS_READ_WORD_DATA&t;0x00200000 
DECL|macro|I2C_FUNC_SMBUS_WRITE_WORD_DATA
mdefine_line|#define I2C_FUNC_SMBUS_WRITE_WORD_DATA&t;0x00400000 
DECL|macro|I2C_FUNC_SMBUS_PROC_CALL
mdefine_line|#define I2C_FUNC_SMBUS_PROC_CALL&t;0x00800000 
DECL|macro|I2C_FUNC_SMBUS_READ_BLOCK_DATA
mdefine_line|#define I2C_FUNC_SMBUS_READ_BLOCK_DATA&t;0x01000000 
DECL|macro|I2C_FUNC_SMBUS_WRITE_BLOCK_DATA
mdefine_line|#define I2C_FUNC_SMBUS_WRITE_BLOCK_DATA 0x02000000 
DECL|macro|I2C_FUNC_SMBUS_READ_I2C_BLOCK
mdefine_line|#define I2C_FUNC_SMBUS_READ_I2C_BLOCK&t;0x04000000 /* New I2C-like block */
DECL|macro|I2C_FUNC_SMBUS_WRITE_I2C_BLOCK
mdefine_line|#define I2C_FUNC_SMBUS_WRITE_I2C_BLOCK&t;0x08000000 /* transfer */
DECL|macro|I2C_FUNC_SMBUS_BYTE
mdefine_line|#define I2C_FUNC_SMBUS_BYTE I2C_FUNC_SMBUS_READ_BYTE | &bslash;&n;                            I2C_FUNC_SMBUS_WRITE_BYTE
DECL|macro|I2C_FUNC_SMBUS_BYTE_DATA
mdefine_line|#define I2C_FUNC_SMBUS_BYTE_DATA I2C_FUNC_SMBUS_READ_BYTE_DATA | &bslash;&n;                                 I2C_FUNC_SMBUS_WRITE_BYTE_DATA
DECL|macro|I2C_FUNC_SMBUS_WORD_DATA
mdefine_line|#define I2C_FUNC_SMBUS_WORD_DATA I2C_FUNC_SMBUS_READ_WORD_DATA | &bslash;&n;                                 I2C_FUNC_SMBUS_WRITE_WORD_DATA
DECL|macro|I2C_FUNC_SMBUS_BLOCK_DATA
mdefine_line|#define I2C_FUNC_SMBUS_BLOCK_DATA I2C_FUNC_SMBUS_READ_BLOCK_DATA | &bslash;&n;                                  I2C_FUNC_SMBUS_WRITE_BLOCK_DATA
DECL|macro|I2C_FUNC_SMBUS_I2C_BLOCK
mdefine_line|#define I2C_FUNC_SMBUS_I2C_BLOCK I2C_FUNC_SMBUS_READ_I2C_BLOCK | &bslash;&n;                                  I2C_FUNC_SMBUS_WRITE_I2C_BLOCK
DECL|macro|I2C_FUNC_SMBUS_EMUL
mdefine_line|#define I2C_FUNC_SMBUS_EMUL I2C_FUNC_SMBUS_QUICK | &bslash;&n;                            I2C_FUNC_SMBUS_BYTE | &bslash;&n;                            I2C_FUNC_SMBUS_BYTE_DATA | &bslash;&n;                            I2C_FUNC_SMBUS_WORD_DATA | &bslash;&n;                            I2C_FUNC_SMBUS_PROC_CALL | &bslash;&n;                            I2C_FUNC_SMBUS_WRITE_BLOCK_DATA
multiline_comment|/* &n; * Data for SMBus Messages &n; */
DECL|union|i2c_smbus_data
r_union
id|i2c_smbus_data
(brace
DECL|member|byte
id|__u8
id|byte
suffix:semicolon
DECL|member|word
id|__u16
id|word
suffix:semicolon
DECL|member|block
id|__u8
id|block
(braket
l_int|33
)braket
suffix:semicolon
multiline_comment|/* block[0] is used for length */
)brace
suffix:semicolon
multiline_comment|/* smbus_access read or write markers */
DECL|macro|I2C_SMBUS_READ
mdefine_line|#define I2C_SMBUS_READ&t;1
DECL|macro|I2C_SMBUS_WRITE
mdefine_line|#define I2C_SMBUS_WRITE&t;0
multiline_comment|/* SMBus transaction types (size parameter in the above functions) &n;   Note: these no longer correspond to the (arbitrary) PIIX4 internal codes! */
DECL|macro|I2C_SMBUS_QUICK
mdefine_line|#define I2C_SMBUS_QUICK&t;&t;    0
DECL|macro|I2C_SMBUS_BYTE
mdefine_line|#define I2C_SMBUS_BYTE&t;&t;    1
DECL|macro|I2C_SMBUS_BYTE_DATA
mdefine_line|#define I2C_SMBUS_BYTE_DATA&t;    2 
DECL|macro|I2C_SMBUS_WORD_DATA
mdefine_line|#define I2C_SMBUS_WORD_DATA&t;    3
DECL|macro|I2C_SMBUS_PROC_CALL
mdefine_line|#define I2C_SMBUS_PROC_CALL&t;    4
DECL|macro|I2C_SMBUS_BLOCK_DATA
mdefine_line|#define I2C_SMBUS_BLOCK_DATA&t;    5
DECL|macro|I2C_SMBUS_I2C_BLOCK_DATA
mdefine_line|#define I2C_SMBUS_I2C_BLOCK_DATA    6
multiline_comment|/* ----- commands for the ioctl like i2c_command call:&n; * note that additional calls are defined in the algorithm and hw &n; *&t;dependent layers - these can be listed here, or see the &n; *&t;corresponding header files.&n; */
multiline_comment|/* -&gt; bit-adapter specific ioctls&t;*/
DECL|macro|I2C_RETRIES
mdefine_line|#define I2C_RETRIES&t;0x0701&t;/* number times a device address should&t;*/
multiline_comment|/* be polled when not acknowledging &t;*/
DECL|macro|I2C_TIMEOUT
mdefine_line|#define I2C_TIMEOUT&t;0x0702&t;/* set timeout - call with int &t;&t;*/
multiline_comment|/* this is for i2c-dev.c&t;*/
DECL|macro|I2C_SLAVE
mdefine_line|#define I2C_SLAVE&t;0x0703&t;/* Change slave address&t;&t;&t;*/
multiline_comment|/* Attn.: Slave address is 7 or 10 bits */
DECL|macro|I2C_SLAVE_FORCE
mdefine_line|#define I2C_SLAVE_FORCE&t;0x0706&t;/* Change slave address&t;&t;&t;*/
multiline_comment|/* Attn.: Slave address is 7 or 10 bits */
multiline_comment|/* This changes the address, even if it */
multiline_comment|/* is already taken!&t;&t;&t;*/
DECL|macro|I2C_TENBIT
mdefine_line|#define I2C_TENBIT&t;0x0704&t;/* 0 for 7 bit addrs, != 0 for 10 bit&t;*/
DECL|macro|I2C_FUNCS
mdefine_line|#define I2C_FUNCS&t;0x0705&t;/* Get the adapter functionality */
DECL|macro|I2C_RDWR
mdefine_line|#define I2C_RDWR&t;0x0707&t;/* Combined R/W transfer (one stop only)*/
macro_line|#if 0
mdefine_line|#define I2C_ACK_TEST&t;0x0710&t;/* See if a slave is at a specific address */
macro_line|#endif
DECL|macro|I2C_SMBUS
mdefine_line|#define I2C_SMBUS&t;0x0720&t;/* SMBus-level access */
multiline_comment|/* ... algo-bit.c recognizes */
DECL|macro|I2C_UDELAY
mdefine_line|#define I2C_UDELAY&t;0x0705&t;/* set delay in microsecs between each&t;*/
multiline_comment|/* written byte (except address)&t;*/
DECL|macro|I2C_MDELAY
mdefine_line|#define I2C_MDELAY&t;0x0706&t;/* millisec delay between written bytes */
multiline_comment|/* ----- I2C-DEV: char device interface stuff ------------------------- */
DECL|macro|I2C_MAJOR
mdefine_line|#define I2C_MAJOR&t;89&t;&t;/* Device major number&t;&t;*/
macro_line|#ifdef __KERNEL__
macro_line|#  ifndef NULL
DECL|macro|NULL
macro_line|#    define NULL ( (void *) 0 )
macro_line|#  endif
macro_line|#  ifndef ENODEV
macro_line|#    include &lt;asm/errno.h&gt;
macro_line|#  endif
multiline_comment|/* These defines are used for probing i2c client addresses */
multiline_comment|/* Default fill of many variables */
DECL|macro|I2C_CLIENT_DEFAULTS
mdefine_line|#define I2C_CLIENT_DEFAULTS {I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END, &bslash;&n;                          I2C_CLIENT_END, I2C_CLIENT_END, I2C_CLIENT_END}
multiline_comment|/* This is ugly. We need to evaluate I2C_CLIENT_MAX_OPTS before it is &n;   stringified */
DECL|macro|I2C_CLIENT_MODPARM_AUX1
mdefine_line|#define I2C_CLIENT_MODPARM_AUX1(x) &quot;1-&quot; #x &quot;h&quot;
DECL|macro|I2C_CLIENT_MODPARM_AUX
mdefine_line|#define I2C_CLIENT_MODPARM_AUX(x) I2C_CLIENT_MODPARM_AUX1(x)
DECL|macro|I2C_CLIENT_MODPARM
mdefine_line|#define I2C_CLIENT_MODPARM I2C_CLIENT_MODPARM_AUX(I2C_CLIENT_MAX_OPTS)
multiline_comment|/* I2C_CLIENT_MODULE_PARM creates a module parameter, and puts it in the&n;   module header */
DECL|macro|I2C_CLIENT_MODULE_PARM
mdefine_line|#define I2C_CLIENT_MODULE_PARM(var,desc) &bslash;&n;  static unsigned short var[I2C_CLIENT_MAX_OPTS] = I2C_CLIENT_DEFAULTS; &bslash;&n;  MODULE_PARM(var,I2C_CLIENT_MODPARM); &bslash;&n;  MODULE_PARM_DESC(var,desc)
multiline_comment|/* This is the one you want to use in your own modules */
DECL|macro|I2C_CLIENT_INSMOD
mdefine_line|#define I2C_CLIENT_INSMOD &bslash;&n;  I2C_CLIENT_MODULE_PARM(probe, &bslash;&n;                      &quot;List of adapter,address pairs to scan additionally&quot;); &bslash;&n;  I2C_CLIENT_MODULE_PARM(probe_range, &bslash;&n;                      &quot;List of adapter,start-addr,end-addr triples to scan &quot; &bslash;&n;                      &quot;additionally&quot;); &bslash;&n;  I2C_CLIENT_MODULE_PARM(ignore, &bslash;&n;                      &quot;List of adapter,address pairs not to scan&quot;); &bslash;&n;  I2C_CLIENT_MODULE_PARM(ignore_range, &bslash;&n;                      &quot;List of adapter,start-addr,end-addr triples not to &quot; &bslash;&n;                      &quot;scan&quot;); &bslash;&n;  I2C_CLIENT_MODULE_PARM(force, &bslash;&n;                      &quot;List of adapter,address pairs to boldly assume &quot; &bslash;&n;                      &quot;to be present&quot;); &bslash;&n;  static struct i2c_client_address_data addr_data = &bslash;&n;                                       {normal_i2c, normal_i2c_range, &bslash;&n;                                        probe, probe_range, &bslash;&n;                                        ignore, ignore_range, &bslash;&n;                                        force}
macro_line|#endif /* def __KERNEL__ */
macro_line|#endif /* I2C_H */
eof
