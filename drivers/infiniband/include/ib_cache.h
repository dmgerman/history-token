multiline_comment|/*&n; * Copyright (c) 2004 Topspin Communications.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: ib_cache.h 1349 2004-12-16 21:09:43Z roland $&n; */
macro_line|#ifndef _IB_CACHE_H
DECL|macro|_IB_CACHE_H
mdefine_line|#define _IB_CACHE_H
macro_line|#include &lt;ib_verbs.h&gt;
multiline_comment|/**&n; * ib_get_cached_gid - Returns a cached GID table entry&n; * @device: The device to query.&n; * @port_num: The port number of the device to query.&n; * @index: The index into the cached GID table to query.&n; * @gid: The GID value found at the specified index.&n; *&n; * ib_get_cached_gid() fetches the specified GID table entry stored in&n; * the local software cache.&n; */
r_int
id|ib_get_cached_gid
c_func
(paren
r_struct
id|ib_device
op_star
id|device
comma
id|u8
id|port_num
comma
r_int
id|index
comma
r_union
id|ib_gid
op_star
id|gid
)paren
suffix:semicolon
multiline_comment|/**&n; * ib_find_cached_gid - Returns the port number and GID table index where&n; *   a specified GID value occurs.&n; * @device: The device to query.&n; * @gid: The GID value to search for.&n; * @port_num: The port number of the device where the GID value was found.&n; * @index: The index into the cached GID table where the GID was found.  This&n; *   parameter may be NULL.&n; *&n; * ib_find_cached_gid() searches for the specified GID value in&n; * the local software cache.&n; */
r_int
id|ib_find_cached_gid
c_func
(paren
r_struct
id|ib_device
op_star
id|device
comma
r_union
id|ib_gid
op_star
id|gid
comma
id|u8
op_star
id|port_num
comma
id|u16
op_star
id|index
)paren
suffix:semicolon
multiline_comment|/**&n; * ib_get_cached_pkey - Returns a cached PKey table entry&n; * @device: The device to query.&n; * @port_num: The port number of the device to query.&n; * @index: The index into the cached PKey table to query.&n; * @pkey: The PKey value found at the specified index.&n; *&n; * ib_get_cached_pkey() fetches the specified PKey table entry stored in&n; * the local software cache.&n; */
r_int
id|ib_get_cached_pkey
c_func
(paren
r_struct
id|ib_device
op_star
id|device_handle
comma
id|u8
id|port_num
comma
r_int
id|index
comma
id|u16
op_star
id|pkey
)paren
suffix:semicolon
multiline_comment|/**&n; * ib_find_cached_pkey - Returns the PKey table index where a specified&n; *   PKey value occurs.&n; * @device: The device to query.&n; * @port_num: The port number of the device to search for the PKey.&n; * @pkey: The PKey value to search for.&n; * @index: The index into the cached PKey table where the PKey was found.&n; *&n; * ib_find_cached_pkey() searches the specified PKey table in&n; * the local software cache.&n; */
r_int
id|ib_find_cached_pkey
c_func
(paren
r_struct
id|ib_device
op_star
id|device
comma
id|u8
id|port_num
comma
id|u16
id|pkey
comma
id|u16
op_star
id|index
)paren
suffix:semicolon
macro_line|#endif /* _IB_CACHE_H */
eof
