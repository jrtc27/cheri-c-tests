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
#include <assert.h>
#include <stdint.h>

#ifndef __FreeBSD__
#warning The test suite is currently expected to work only on FreeBSD.
#endif

typedef void (*cheri_handler)(void *, int);

extern cheri_handler test_fault_handler;
extern volatile int faults;

void test_setup(void);

static const int cheri_fault_length = 1;
static const int cheri_fault_tag = 2;
static const int cheri_fault_seal = 3;
static const int cheri_fault_load = 0x12;
static const int cheri_fault_store = 0x13;
static const int cheri_fault_load_capability = 0x14;
static const int cheri_fault_store_capability = 0x16;

#define BEGIN_TEST \
	int main(void) { test_setup(); 
#define END_TEST return 0; }

#ifdef INCLUDE_XFAIL
#define XFAIL(x) assert(x)
#else
#define XFAIL(x) do {} while(0)
#endif

#define ASSERT_HAS_PERMISSION(x, perm) \
	assert((__builtin_memcap_perms_get((void*)x) & __CHERI_CAP_PERMISSION_PERMIT_ ## perm ## __) == __CHERI_CAP_PERMISSION_PERMIT_ ## perm ## __)

#define ASSERT_HAS_NOT_PERMISSION(x, perm) \
	assert((__builtin_memcap_perms_get((void*)x) & __CHERI_CAP_PERMISSION_PERMIT_ ## perm ## __) == 0)

