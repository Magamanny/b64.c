
/**
 * `b64.h' - b64
 *
 * copyright (c) 2014 joseph werle
 */

#ifndef B64_H
#define B64_H 1

/**
 *  Memory allocation functions to use. You can define b64_malloc and
 * b64_realloc to custom functions if you want.
 */

#ifndef b64_malloc
#  define b64_malloc(ptr) malloc(ptr)
#endif
#ifndef b64_realloc
#  define b64_realloc(ptr, size) realloc(ptr, size)
#endif

 // How much memory to allocate per buffer
#define B64_BUFFER_SIZE		(1024 * 64) // 64K

 // Start buffered memory
char* b64_buf_malloc();

// Update memory size. Returns the same pointer if we
// have enough space in the buffer. Otherwise, we add
// additional buffers.
char* b64_buf_realloc(unsigned char* ptr, size_t size);

/**
 * Base64 index table.
 */

static const char b64_table[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
  'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
  'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
  'w', 'x', 'y', 'z', '0', '1', '2', '3',
  '4', '5', '6', '7', '8', '9', '+', '/'
};

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Encode `unsigned char *' source with `size_t' size.
 * @note Returns a `char *' base64 encoded string.
 * @param src: pointer to the stirng that is to be encoded to base64
 * @param enc: encoded buffer,pointer to the string where the resultant base64 string will be held
 * @param len: The lenght of the src string(the message to be encoded)
 * @return 0 on success 1 on fail
 */

int
b64_encode (const unsigned char *src,char *enc, size_t len);

/**
 * @brief Decode `char *' source with `size_t' size.
 * @note Returns a `unsigned char *' base64 decoded string.
 * @param src: pointer to the stirng(base64) that is to be decoded to hex(array)
 * @param dec: decoded buffer,pointer to the string(array) where the resultant binary(hex) string will be held
 * @param len: The lenght of the src string(the encoded massage)
 * @return 0 on success 1 on fail
 */
int
b64_decode (const char *src,unsigned char *dec, size_t len);

/**
 * @brief Decode `char *' source with `size_t' size.
 * @note Returns a `unsigned char *' base64 decoded string + size of decoded string.
 * @param src: pointer to the stirng(base64) that is to be decoded to hex(array)
 * @param dec: decoded buffer, pointer to the string(array) where the resultant binary(hex) string will be held
 * @param len: The lenght of the src string
 * @param decsize: pointer to variable where the dst size will be returned
 * @return 0 on success 1 on fail
 */
int
b64_decode_ex (const char *src,unsigned char *dec, size_t len, size_t *decsize);

#ifdef __cplusplus
}
#endif

#endif
