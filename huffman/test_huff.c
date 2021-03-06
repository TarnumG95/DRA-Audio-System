#include <stdio.h>
#include "../bitstream/bitstream.h"
#include "../util/vector.h"
#include "../util/errors.h"
#include "huffcoding.h"
#include "huffbook.h"

int main() {
    {
        printf("Test Case 1:\n");
        struct vector* v = vector_init();
        struct vector* result = vector_init();
        struct bit_stream* bs = bitstream_init();

        vector_push_back_int32(v, 147);
        vector_push_back_int32(v, 5);
        vector_push_back_int32(v, 16);
        vector_push_back_int32(v, 12);
        vector_push_back_int32(v, 13);
        vector_push_back_int32(v, 2);
        vector_push_back_int32(v, 1);
        vector_push_back_int32(v, 1);
        vector_push_back_int32(v, 0);
        vector_print_int32(v);

        huff_encode(&HuffDec27_256x1, v, bs);
        bitstream_print(bs);
        
        huff_decode(&HuffDec27_256x1, bs, result);
        vector_print_int32(result);

        vector_destroy(v, NULL);
        vector_destroy(result, NULL);
        bitstream_destroy(bs);
    }
    
    {
        printf("Test Case 2:\n");
        struct bit_stream* bs = bitstream_init();
        HuffEnc(&HuffDec27_256x1, bs, 147);
        HuffEnc(&HuffDec27_256x1, bs, 15);
        HuffEnc(&HuffDec27_256x1, bs, 4);
        HuffEnc(&HuffDec27_256x1, bs, 12);

        bitstream_print(bs);
        
        struct bs_iter* iter = bs_iter_init(bs);
        printf("%d\n", HuffDec(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDec(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDec(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDec(&HuffDec27_256x1, iter));

        bitstream_destroy(bs);
    }

    {
        printf("Test Case 3:\n");
        struct bit_stream* bs = bitstream_init();
        HuffEnc(&HuffDec27_256x1, bs, 204);
        HuffEncRecursive(&HuffDec27_256x1, bs, 254);
        HuffEncRecursive(&HuffDec27_256x1, bs, 257);
        HuffEncRecursive(&HuffDec27_256x1, bs, 256);
        HuffEncRecursive(&HuffDec27_256x1, bs, 255);

        bitstream_print(bs);
        
        struct bs_iter* iter = bs_iter_init(bs);
        printf("%d\n", HuffDec(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDecRecursive(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDecRecursive(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDecRecursive(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDecRecursive(&HuffDec27_256x1, iter));

        bitstream_destroy(bs);
    }

    {
        printf("Test Case 4:\n");
        struct bit_stream* bs = bitstream_init();
        ResetHuffIndex(&HuffDec27_256x1, 0);

        HuffEncDiff(&HuffDec27_256x1, bs, 140);
        HuffEncDiff(&HuffDec27_256x1, bs, 20);
        HuffEncDiff(&HuffDec27_256x1, bs, 222);
        HuffEncDiff(&HuffDec27_256x1, bs, 150);
        HuffEncDiff(&HuffDec27_256x1, bs, 124);
        HuffEnc(&HuffDec27_256x1, bs, 204);
        HuffEncRecursive(&HuffDec27_256x1, bs, 254);
        HuffEncRecursive(&HuffDec27_256x1, bs, 257);
        HuffEnc(&HuffDec27_256x1, bs, 204);
        HuffEncRecursive(&HuffDec27_256x1, bs, 256);
        HuffEnc(&HuffDec27_256x1, bs, 204);
        HuffEncRecursive(&HuffDec27_256x1, bs, 255);

        bitstream_print(bs);
        
        
        struct bs_iter* iter = bs_iter_init(bs);
        ResetHuffIndex(&HuffDec27_256x1, 0);

        printf("%d\n", HuffDecDiff(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDecDiff(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDecDiff(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDecDiff(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDecDiff(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDec(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDecRecursive(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDecRecursive(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDec(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDecRecursive(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDec(&HuffDec27_256x1, iter));
        printf("%d\n", HuffDecRecursive(&HuffDec27_256x1, iter));

        bitstream_destroy(bs);
    }
}