/* stddef.h
 * 
 * Copyright (C) 2005-2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

#ifndef _CROCOS_KLIBC_STDDEF_H
#define _CROCOS_KLIBC_STDDEF_H

#define NULL ((void *)0)

/* __PTRDIFF_TYPE__ and __SIZE_TYPE__ should be provided by gcc */
typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __SIZE_TYPE__ size_t;
typedef signed long int ssize_t;
typedef enum tagBoolean{False=0,True=-1} boolean;


#endif /* _CROCOS_KLIBC_STDDEF_H */

