/*
    Copyright (C) HWPORT.COM
    All rights reserved.
    Author: JAEHYUK CHO <mailto:minzkn@minzkn.com>
*/

#if !defined(__def_hwport_pgl_header_hwport_aes_h__)
# define __def_hwport_pgl_header_hwport_aes_h__ "hwport_aes.h"

#include <sys/types.h>

#if defined(__cplusplus)
# define def_hwport_aes_import_c extern "C"
#else
# define def_hwport_aes_import_c extern
#endif

#if !defined(hwport_make_round_key_handler_t)
typedef void * (*__hwport_make_round_key_handler_t)(void *s_round_key, const void *s_user_key);
# define hwport_make_round_key_handler_t __hwport_make_round_key_handler_t
#endif

#if !defined(hwport_encrypt_handler_t)
typedef void * (*__hwport_encrypt_handler_t)(void *s_data, size_t s_size, const void *s_round_key);
# define hwport_encrypt_handler_t __hwport_encrypt_handler_t
#endif

#if !defined(hwport_decrypt_handler_t)
typedef void * (*__hwport_decrypt_handler_t)(void *s_data, size_t s_size, const void *s_round_key);
# define hwport_decrypt_handler_t __hwport_decrypt_handler_t
#endif

#define def_hwport_aes_block_size 16 /* AES is always 16-bytes block */

#define def_hwport_aes128_block_size def_hwport_aes_block_size
#define def_hwport_aes128_rounds 10
#define def_hwport_aes128_user_key_size (128>>3) /* 128 bits = 16 bytes */
#define def_hwport_aes128_round_key_size ((1+def_hwport_aes128_rounds)*def_hwport_aes128_block_size)

#define def_hwport_aes192_block_size def_hwport_aes_block_size
#define def_hwport_aes192_rounds 12
#define def_hwport_aes192_user_key_size (192>>3) /* 192 bits = 24 bytes */
#define def_hwport_aes192_round_key_size ((1+def_hwport_aes192_rounds)*def_hwport_aes192_block_size)

#define def_hwport_aes256_block_size def_hwport_aes_block_size
#define def_hwport_aes256_rounds 14
#define def_hwport_aes256_user_key_size (256>>3) /* 256 bits = 32 bytes */
#define def_hwport_aes256_round_key_size ((1+def_hwport_aes256_rounds)*def_hwport_aes256_block_size)

#define def_hwport_aes_max_user_key_size def_hwport_aes256_user_key_size
#define def_hwport_aes_max_round_key_size def_hwport_aes256_round_key_size

#if !defined(__def_hwport_pgl_source_aes_c__)
def_hwport_aes_import_c void *hwport_encrypt_mode_cfb8(hwport_encrypt_handler_t s_handler, size_t s_block_size, void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);
def_hwport_aes_import_c void *hwport_decrypt_mode_cfb8(hwport_encrypt_handler_t s_handler, size_t s_block_size, void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);

def_hwport_aes_import_c void *hwport_encrypt_mode_cfb8_for_product_key(hwport_encrypt_handler_t s_handler, size_t s_block_size, void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);
def_hwport_aes_import_c void *hwport_decrypt_mode_cfb8_for_product_key(hwport_encrypt_handler_t s_handler, size_t s_block_size, void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);

def_hwport_aes_import_c void *hwport_encrypt_mode_ofb8(hwport_encrypt_handler_t s_handler, size_t s_block_size, void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);
def_hwport_aes_import_c void *hwport_decrypt_mode_ofb8(hwport_encrypt_handler_t s_handler, size_t s_block_size, void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);

def_hwport_aes_import_c void *hwport_make_round_key_aes128(void *s_round_key, const void *s_user_key);
def_hwport_aes_import_c void *hwport_make_round_key_aes192(void *s_round_key, const void *s_user_key);
def_hwport_aes_import_c void *hwport_make_round_key_aes256(void *s_round_key, const void *s_user_key);

def_hwport_aes_import_c void *hwport_encrypt_aes128_ecb(void *s_data, size_t s_size, const void *s_round_key);
def_hwport_aes_import_c void *hwport_decrypt_aes128_ecb(void *s_data, size_t s_size, const void *s_round_key);
def_hwport_aes_import_c void *hwport_encrypt_aes128_cfb8(void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);
def_hwport_aes_import_c void *hwport_decrypt_aes128_cfb8(void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);
def_hwport_aes_import_c void *hwport_encrypt_aes128_ofb8(void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);
def_hwport_aes_import_c void *hwport_decrypt_aes128_ofb8(void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);

def_hwport_aes_import_c void *hwport_encrypt_aes192_ecb(void *s_data, size_t s_size, const void *s_round_key);
def_hwport_aes_import_c void *hwport_decrypt_aes192_ecb(void *s_data, size_t s_size, const void *s_round_key);
def_hwport_aes_import_c void *hwport_encrypt_aes192_cfb8(void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);
def_hwport_aes_import_c void *hwport_decrypt_aes192_cfb8(void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);
def_hwport_aes_import_c void *hwport_encrypt_aes192_ofb8(void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);
def_hwport_aes_import_c void *hwport_decrypt_aes192_ofb8(void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);

def_hwport_aes_import_c void *hwport_encrypt_aes256_ecb(void *s_data, size_t s_size, const void *s_round_key);
def_hwport_aes_import_c void *hwport_decrypt_aes256_ecb(void *s_data, size_t s_size, const void *s_round_key);
def_hwport_aes_import_c void *hwport_encrypt_aes256_cfb8(void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);
def_hwport_aes_import_c void *hwport_decrypt_aes256_cfb8(void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);
def_hwport_aes_import_c void *hwport_encrypt_aes256_ofb8(void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);
def_hwport_aes_import_c void *hwport_decrypt_aes256_ofb8(void *s_data, size_t s_size, void *s_initial_vector, const void *s_round_key);
#endif
#endif

/* vim: set expandtab: */
/* End of source */
