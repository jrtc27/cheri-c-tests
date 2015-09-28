/*-
 * Copyright (c) 2015 David Chisnall
 * All rights reserved.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory under DARPA/AFRL contract (FA8750-10-C-0237)
 * ("CTSRD"), as part of the DARPA CRASH research programme.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include <stdarg.h>
#include "cheri_c_test.h"

char str[] = "012345678901234567890";
volatile void *ptrs[] = 
{
	&str[0],
	&str[1],
	&str[2],
	&str[3],
	&str[4],
	&str[5],
	&str[6],
	&str[7],
	&str[8],
	&str[9],
	&str[0],
	&str[11],
	&str[12],
	&str[13],
	&str[14],
	&str[15],
	&str[16],
	&str[17],
	&str[18],
	&str[19]
};

void printstuff(int argpairs, ...)
{
	va_list ap;
	va_start(ap, argpairs);
	// Check that the length corresponds to the number of arguments, with
	// appropriate padding.
	assert(__builtin_memcap_length_get(ap) == argpairs * sizeof(void*) * 2);
	for (int i=0 ; i<argpairs ; i++)
	{
		int x = va_arg(ap, int);
		char *p = va_arg(ap, void*);
		assert(x == i);
		assert(p == ptrs[i]);
		assert(*p = str[i]);
	}
	va_end(ap);
}

BEGIN_TEST
	printstuff(8, 0,ptrs[0],1,ptrs[1],2,ptrs[2],3,ptrs[3],4,ptrs[4],5,ptrs[5],6,ptrs[6],7,ptrs[7]);
	assert(faults == 0);
END_TEST
