multiline_comment|/*&n; * Copyright (c) 2001-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.&t; Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/SGIGPLNoticeExplan/&n; */
multiline_comment|/*&n; * Dummy file that can contain a timestamp to put into the&n; * XFS init string, to help users keep track of what they&squot;re&n; * running&n; */
macro_line|#ifndef __XFS_VERSION_H__
DECL|macro|__XFS_VERSION_H__
mdefine_line|#define __XFS_VERSION_H__
macro_line|#include &lt;linux/version.h&gt;
DECL|macro|XFS_VERSION_STRING
mdefine_line|#define XFS_VERSION_STRING &quot;for Linux &quot; UTS_RELEASE
macro_line|#endif /* __XFS_VERSION_H__ */
eof
