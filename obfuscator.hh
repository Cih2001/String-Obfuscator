/* -------------------------------- LICENSE ------------------------------------
 *
 * This is free and unencumbered software released into the public domain.
 * 
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 * 
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 * For more information, please refer to <http://unlicense.org/>
 *
 * ----------------------------------------------------------------------------- */

#ifndef OBFUSCATOR_H__
#define OBFUSCATOR_H__
namespace ob {

/*
 * XOR Encryption key.
 */
#define KEY 0x55

/*
 * obfuscator is a class that helps with the storage of encrypted strings 
 * and their decryption.
 *
 * How much space do we need to store a strings? that depends to the string.
 * thats why we used a template class where N is defined at compile time,
 * depending the string size.
 */
template <unsigned int N>
struct obfuscator {
    /*
     * m_data stores the obfuscated string.
     */
    char m_data[N] = {0};

    /*
     * Using constexpr ensures that the strings will be obfuscated in this
     * constructor function at compile time.
     */
    constexpr obfuscator(const char* data) {
        /*
         * Implement encryption algorithm here.
         * Here we have simple XOR algorithm.
         */
        for (unsigned int i = 0; i < N; i++) {
            m_data[i] = data[i] ^ KEY;
        }
    }

    /*
     * deobfoscate decrypts the strings. Implement decryption algorithm here.
     * Here we have a simple XOR algorithm.
     */
    void deobfoscate(unsigned char * des) const{
        int i = 0;
        do {
            des[i] = m_data[i] ^ KEY;
            i++;
        } while (des[i-1]);
    }
};


/*
 * This macro is a lambda function to pack all required steps into one single command
 * when defining strings.
 */
#define STR(str) \
    []() -> char* { \
        constexpr auto size = sizeof(str)/sizeof(str[0]); \
        constexpr auto obfuscated_str = obfuscator<size>(str); \
        static char original_string[size]; \
        obfuscated_str.deobfoscate((unsigned char *)original_string); \
        return original_string; \
    }()

}

#endif
