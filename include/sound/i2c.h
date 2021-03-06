macro_line|#ifndef __SOUND_I2C_H
DECL|macro|__SOUND_I2C_H
mdefine_line|#define __SOUND_I2C_H
multiline_comment|/*&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; *&n; */
DECL|typedef|snd_i2c_device_t
r_typedef
r_struct
id|_snd_i2c_device
id|snd_i2c_device_t
suffix:semicolon
DECL|typedef|snd_i2c_bus_t
r_typedef
r_struct
id|_snd_i2c_bus
id|snd_i2c_bus_t
suffix:semicolon
DECL|macro|SND_I2C_DEVICE_ADDRTEN
mdefine_line|#define SND_I2C_DEVICE_ADDRTEN&t;(1&lt;&lt;0)&t;/* 10-bit I2C address */
DECL|struct|_snd_i2c_device
r_struct
id|_snd_i2c_device
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|bus
id|snd_i2c_bus_t
op_star
id|bus
suffix:semicolon
multiline_comment|/* I2C bus */
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* some useful device name */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* device flags */
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* device address (might be 10-bit) */
DECL|member|private_value
r_int
r_int
id|private_value
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|private_free
r_void
(paren
op_star
id|private_free
)paren
(paren
id|snd_i2c_device_t
op_star
id|device
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|snd_i2c_device
mdefine_line|#define snd_i2c_device(n) list_entry(n, snd_i2c_device_t, list)
DECL|struct|_snd_i2c_bit_ops
r_typedef
r_struct
id|_snd_i2c_bit_ops
(brace
DECL|member|start
r_void
(paren
op_star
id|start
)paren
(paren
id|snd_i2c_bus_t
op_star
id|bus
)paren
suffix:semicolon
multiline_comment|/* transfer start */
DECL|member|stop
r_void
(paren
op_star
id|stop
)paren
(paren
id|snd_i2c_bus_t
op_star
id|bus
)paren
suffix:semicolon
multiline_comment|/* transfer stop */
DECL|member|direction
r_void
(paren
op_star
id|direction
)paren
(paren
id|snd_i2c_bus_t
op_star
id|bus
comma
r_int
id|clock
comma
r_int
id|data
)paren
suffix:semicolon
multiline_comment|/* set line direction (0 = write, 1 = read) */
DECL|member|setlines
r_void
(paren
op_star
id|setlines
)paren
(paren
id|snd_i2c_bus_t
op_star
id|bus
comma
r_int
id|clock
comma
r_int
id|data
)paren
suffix:semicolon
DECL|member|getclock
r_int
(paren
op_star
id|getclock
)paren
(paren
id|snd_i2c_bus_t
op_star
id|bus
)paren
suffix:semicolon
DECL|member|getdata
r_int
(paren
op_star
id|getdata
)paren
(paren
id|snd_i2c_bus_t
op_star
id|bus
comma
r_int
id|ack
)paren
suffix:semicolon
DECL|typedef|snd_i2c_bit_ops_t
)brace
id|snd_i2c_bit_ops_t
suffix:semicolon
DECL|struct|_snd_i2c_ops
r_typedef
r_struct
id|_snd_i2c_ops
(brace
DECL|member|sendbytes
r_int
(paren
op_star
id|sendbytes
)paren
(paren
id|snd_i2c_device_t
op_star
id|device
comma
r_int
r_char
op_star
id|bytes
comma
r_int
id|count
)paren
suffix:semicolon
DECL|member|readbytes
r_int
(paren
op_star
id|readbytes
)paren
(paren
id|snd_i2c_device_t
op_star
id|device
comma
r_int
r_char
op_star
id|bytes
comma
r_int
id|count
)paren
suffix:semicolon
DECL|member|probeaddr
r_int
(paren
op_star
id|probeaddr
)paren
(paren
id|snd_i2c_bus_t
op_star
id|bus
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|typedef|snd_i2c_ops_t
)brace
id|snd_i2c_ops_t
suffix:semicolon
DECL|struct|_snd_i2c_bus
r_struct
id|_snd_i2c_bus
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
multiline_comment|/* card which I2C belongs to */
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* some useful label */
DECL|member|lock_mutex
r_struct
id|semaphore
id|lock_mutex
suffix:semicolon
DECL|member|master
id|snd_i2c_bus_t
op_star
id|master
suffix:semicolon
multiline_comment|/* master bus when SCK/SCL is shared */
DECL|member|buses
r_struct
id|list_head
id|buses
suffix:semicolon
multiline_comment|/* master: slave buses sharing SCK/SCL, slave: link list */
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
multiline_comment|/* attached devices to this bus */
r_union
(brace
DECL|member|bit
id|snd_i2c_bit_ops_t
op_star
id|bit
suffix:semicolon
DECL|member|ops
r_void
op_star
id|ops
suffix:semicolon
DECL|member|hw_ops
)brace
id|hw_ops
suffix:semicolon
multiline_comment|/* lowlevel operations */
DECL|member|ops
id|snd_i2c_ops_t
op_star
id|ops
suffix:semicolon
multiline_comment|/* midlevel operations */
DECL|member|private_value
r_int
r_int
id|private_value
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|private_free
r_void
(paren
op_star
id|private_free
)paren
(paren
id|snd_i2c_bus_t
op_star
id|bus
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|snd_i2c_slave_bus
mdefine_line|#define snd_i2c_slave_bus(n) list_entry(n, snd_i2c_bus_t, buses)
r_int
id|snd_i2c_bus_create
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_const
r_char
op_star
id|name
comma
id|snd_i2c_bus_t
op_star
id|master
comma
id|snd_i2c_bus_t
op_star
op_star
id|ri2c
)paren
suffix:semicolon
r_int
id|snd_i2c_device_create
c_func
(paren
id|snd_i2c_bus_t
op_star
id|bus
comma
r_const
r_char
op_star
id|name
comma
r_int
r_char
id|addr
comma
id|snd_i2c_device_t
op_star
op_star
id|rdevice
)paren
suffix:semicolon
r_int
id|snd_i2c_device_free
c_func
(paren
id|snd_i2c_device_t
op_star
id|device
)paren
suffix:semicolon
DECL|function|snd_i2c_lock
r_static
r_inline
r_void
id|snd_i2c_lock
c_func
(paren
id|snd_i2c_bus_t
op_star
id|bus
)paren
(brace
r_if
c_cond
(paren
id|bus-&gt;master
)paren
id|down
c_func
(paren
op_amp
id|bus-&gt;master-&gt;lock_mutex
)paren
suffix:semicolon
r_else
id|down
c_func
(paren
op_amp
id|bus-&gt;lock_mutex
)paren
suffix:semicolon
)brace
DECL|function|snd_i2c_unlock
r_static
r_inline
r_void
id|snd_i2c_unlock
c_func
(paren
id|snd_i2c_bus_t
op_star
id|bus
)paren
(brace
r_if
c_cond
(paren
id|bus-&gt;master
)paren
id|up
c_func
(paren
op_amp
id|bus-&gt;master-&gt;lock_mutex
)paren
suffix:semicolon
r_else
id|up
c_func
(paren
op_amp
id|bus-&gt;lock_mutex
)paren
suffix:semicolon
)brace
r_int
id|snd_i2c_sendbytes
c_func
(paren
id|snd_i2c_device_t
op_star
id|device
comma
r_int
r_char
op_star
id|bytes
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|snd_i2c_readbytes
c_func
(paren
id|snd_i2c_device_t
op_star
id|device
comma
r_int
r_char
op_star
id|bytes
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|snd_i2c_probeaddr
c_func
(paren
id|snd_i2c_bus_t
op_star
id|bus
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_I2C_H */
eof
