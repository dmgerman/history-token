multiline_comment|/* keyctl.h: keyctl command IDs&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_KEYCTL_H
DECL|macro|_LINUX_KEYCTL_H
mdefine_line|#define _LINUX_KEYCTL_H
multiline_comment|/* special process keyring shortcut IDs */
DECL|macro|KEY_SPEC_THREAD_KEYRING
mdefine_line|#define KEY_SPEC_THREAD_KEYRING&t;&t;-1&t;/* - key ID for thread-specific keyring */
DECL|macro|KEY_SPEC_PROCESS_KEYRING
mdefine_line|#define KEY_SPEC_PROCESS_KEYRING&t;-2&t;/* - key ID for process-specific keyring */
DECL|macro|KEY_SPEC_SESSION_KEYRING
mdefine_line|#define KEY_SPEC_SESSION_KEYRING&t;-3&t;/* - key ID for session-specific keyring */
DECL|macro|KEY_SPEC_USER_KEYRING
mdefine_line|#define KEY_SPEC_USER_KEYRING&t;&t;-4&t;/* - key ID for UID-specific keyring */
DECL|macro|KEY_SPEC_USER_SESSION_KEYRING
mdefine_line|#define KEY_SPEC_USER_SESSION_KEYRING&t;-5&t;/* - key ID for UID-session keyring */
DECL|macro|KEY_SPEC_GROUP_KEYRING
mdefine_line|#define KEY_SPEC_GROUP_KEYRING&t;&t;-6&t;/* - key ID for GID-specific keyring */
multiline_comment|/* keyctl commands */
DECL|macro|KEYCTL_GET_KEYRING_ID
mdefine_line|#define KEYCTL_GET_KEYRING_ID&t;&t;0&t;/* ask for a keyring&squot;s ID */
DECL|macro|KEYCTL_JOIN_SESSION_KEYRING
mdefine_line|#define KEYCTL_JOIN_SESSION_KEYRING&t;1&t;/* join or start named session keyring */
DECL|macro|KEYCTL_UPDATE
mdefine_line|#define KEYCTL_UPDATE&t;&t;&t;2&t;/* update a key */
DECL|macro|KEYCTL_REVOKE
mdefine_line|#define KEYCTL_REVOKE&t;&t;&t;3&t;/* revoke a key */
DECL|macro|KEYCTL_CHOWN
mdefine_line|#define KEYCTL_CHOWN&t;&t;&t;4&t;/* set ownership of a key */
DECL|macro|KEYCTL_SETPERM
mdefine_line|#define KEYCTL_SETPERM&t;&t;&t;5&t;/* set perms on a key */
DECL|macro|KEYCTL_DESCRIBE
mdefine_line|#define KEYCTL_DESCRIBE&t;&t;&t;6&t;/* describe a key */
DECL|macro|KEYCTL_CLEAR
mdefine_line|#define KEYCTL_CLEAR&t;&t;&t;7&t;/* clear contents of a keyring */
DECL|macro|KEYCTL_LINK
mdefine_line|#define KEYCTL_LINK&t;&t;&t;8&t;/* link a key into a keyring */
DECL|macro|KEYCTL_UNLINK
mdefine_line|#define KEYCTL_UNLINK&t;&t;&t;9&t;/* unlink a key from a keyring */
DECL|macro|KEYCTL_SEARCH
mdefine_line|#define KEYCTL_SEARCH&t;&t;&t;10&t;/* search for a key in a keyring */
DECL|macro|KEYCTL_READ
mdefine_line|#define KEYCTL_READ&t;&t;&t;11&t;/* read a key or keyring&squot;s contents */
DECL|macro|KEYCTL_INSTANTIATE
mdefine_line|#define KEYCTL_INSTANTIATE&t;&t;12&t;/* instantiate a partially constructed key */
DECL|macro|KEYCTL_NEGATE
mdefine_line|#define KEYCTL_NEGATE&t;&t;&t;13&t;/* negate a partially constructed key */
macro_line|#endif /*  _LINUX_KEYCTL_H */
eof
