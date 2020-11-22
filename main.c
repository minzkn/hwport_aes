/*
    Copyright (C) HWPORT.COM
    All rights reserved.
    Author: JAEHYUK CHO <mailto:minzkn@minzkn.com>
*/

#if !defined(_ISOC99_SOURCE)
# define _ISOC99_SOURCE (1L)
#endif

#if !defined(_GNU_SOURCE)
# define _GNU_SOURCE (1L)
#endif

#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "hwport_aes.h"

static void hwport_dump(const char *s_title, const void *s_data, size_t s_size);

static void test_aes(const char *s_title, size_t s_block_size, size_t s_user_key_size, size_t s_round_key_size, hwport_make_round_key_handler_t s_make_round_key_handler, hwport_encrypt_handler_t s_encrypt_handler, hwport_decrypt_handler_t s_decrypt_handler);

int main(int s_argc, char **s_argv);

static void hwport_dump(const char *s_title, const void *s_data, size_t s_size)
{
    size_t s_o,s_w,s_i;uint8_t s_b[17];
    (void)fprintf(stdout, "%s:\n", s_title);
    s_b[16]='\0';s_o=(size_t)0u;
    while(s_o<s_size){
        s_w=(s_size-s_o)<((size_t)16u)?(s_size-s_o):((size_t)16u);
        printf("%08lX",(unsigned long)s_o);for(s_i=(size_t)0u;s_i<s_w;s_i++){if(s_i==((size_t)8u))printf(" | ");else printf(" ");
        s_b[s_i]=*(((const uint8_t *)(s_data))+s_o+s_i);printf("%02X",(unsigned int)s_b[s_i]);if((s_b[s_i]&0x80)||(s_b[s_i]<' '))s_b[s_i]='.';}
    while(s_i<16){if(s_i==8)printf("     ");else printf("   ");s_b[s_i]=' ';s_i++;}
    printf(" [%s]\n",(char *)s_b);s_o+=(size_t)16u;}
    (void)fprintf(stdout, "\n");
}

static void test_aes(const char *s_title, size_t s_block_size, size_t s_user_key_size, size_t s_round_key_size, hwport_make_round_key_handler_t s_make_round_key_handler, hwport_encrypt_handler_t s_encrypt_handler, hwport_decrypt_handler_t s_decrypt_handler)
{
    static const char s_data[] = {
        "AES encrypt/decrypt library/example source\n"
        "Copyright (C) JAEHYUK CHO\n"
        "All rights reserved.\n"
        "Code by JaeHyuk Cho <mailto:minzkn@minzkn.com>\n"
    };

    size_t s_data_size, s_padding_data_size;
    void *s_padding_data;

#if 0L
    uint8_t s_user_key[ s_user_key_size ];
    uint8_t s_round_key[ s_round_key_size ];
#else
    uint8_t s_user_key[ def_hwport_aes_max_user_key_size ];
    uint8_t s_round_key[ def_hwport_aes_max_round_key_size ];

    (void)s_round_key_size;
#endif
 
    (void)fprintf(stdout, "\x1b[1;33m%s\x1b[0m\n~~~~~~~~~~~~~~~~\n\n", s_title);

    /* password */
    (void)memset(&s_user_key[0], 0, sizeof(s_user_key));
    (void)strncpy((char *)(&s_user_key[0]), "ABCDEFGHIJKLMNOPQRSTUVWX", sizeof(s_user_key));
 
    hwport_dump("user key", &s_user_key[0], s_user_key_size);

    (void)(*s_make_round_key_handler)(&s_round_key[0], &s_user_key[0]);

    /* padding process */
    s_data_size = sizeof(s_data);
    s_padding_data_size = s_data_size + (s_block_size - 1);
    s_padding_data_size -= s_padding_data_size % s_block_size;
    s_padding_data = malloc(s_padding_data_size);
    if(s_padding_data == ((void *)0)) {
        (void)fprintf(stderr, "not enough memory !\n");
        return;
    }
    (void)memcpy(s_padding_data, s_data, s_data_size);
    if((s_padding_data_size - s_data_size) > ((size_t)0u)) { /* zero padding */
        (void)memset(((uint8_t *)s_padding_data) + s_data_size, 0, s_padding_data_size - s_data_size);
    }
 
    hwport_dump("data", &s_data[0], s_data_size);

    (void)fprintf(stdout, "data_size + pad_size = %lu + %lu = %lu [%lux%lu]\n", (unsigned long)s_data_size, (unsigned long)(s_padding_data_size - s_data_size), (unsigned long)s_padding_data_size, (unsigned long)(s_padding_data_size / s_block_size), (unsigned long)s_block_size); 

    hwport_dump("encrpyt",
        (*s_encrypt_handler)(s_padding_data, s_padding_data_size, &s_round_key[0]),
        s_padding_data_size
    );
 
    hwport_dump("decrypt",
        (*s_decrypt_handler)(s_padding_data, s_padding_data_size, &s_round_key[0]),
        s_data_size
    );

    free((void *)s_padding_data);
}

int main(int s_argc, char **s_argv)
{
    (void)s_argc;
    (void)s_argv;

    test_aes(
        "AES128 test",
        (size_t)def_hwport_aes128_block_size,
        (size_t)def_hwport_aes128_user_key_size,
        (size_t)def_hwport_aes128_round_key_size,
        &hwport_make_round_key_aes128,
        &hwport_encrypt_aes128_ecb,
        &hwport_decrypt_aes128_ecb
    );
    test_aes(
        "AES192 test",
        (size_t)def_hwport_aes192_block_size,
        (size_t)def_hwport_aes192_user_key_size,
        (size_t)def_hwport_aes192_round_key_size,
        &hwport_make_round_key_aes192,
        &hwport_encrypt_aes192_ecb,
        &hwport_decrypt_aes192_ecb
    );
    test_aes(
        "AES256 test",
        (size_t)def_hwport_aes256_block_size,
        (size_t)def_hwport_aes256_user_key_size,
        (size_t)def_hwport_aes256_round_key_size,
        &hwport_make_round_key_aes256,
        &hwport_encrypt_aes256_ecb,
        &hwport_decrypt_aes256_ecb
    );

    return(EXIT_SUCCESS);
}

/* vim: set expandtab: */
/* End of source */
