#include <stdio.h>
#include <string.h>

#define BYTE_CONSTRAINT 256

int main()
{
   char *key = "HelloRC4c";
   printf(key);
   printf("\n");
   // the bytes
   unsigned char bytes[BYTE_CONSTRAINT];
   int i;
   for (i = 0; i < BYTE_CONSTRAINT; i++) {
     bytes[i] = i;
   }

   int j = 0;
   for (i = 0; i < BYTE_CONSTRAINT; i++) {
     j = (j + bytes[i] + key[i % strlen(key)]) % BYTE_CONSTRAINT;
     char c = bytes[i];
     bytes[i] = bytes[j];
     bytes[j] = c;
   }
   for (i = 0; i < BYTE_CONSTRAINT; i++) {
     int j;
     for (j = 0; j < 8; j++) {
      printf("%d", !!((bytes[i] << j) & 0x80));
     }
   }
   printf("Line break\n");
   printf("Line break\n");
   j = i = 0;
   int n;
   char out[256];
   for (n = 0; n < strlen(key); n++) {
     i = (i + 1) % BYTE_CONSTRAINT;
     j = (j + bytes[i]) % BYTE_CONSTRAINT;
     char c = bytes[i];
     bytes[i] = bytes[j];
     bytes[j] = c;
     out[n] = bytes[(bytes[i] + bytes[j]) % BYTE_CONSTRAINT];
   }
   for (i = 0; i < BYTE_CONSTRAINT; i++) {
     int j;
     for (j = 0; j < 8; j++) {
      printf("%d", !!((out[i] << j) & 0x80));
     }
   }

   return 0;
}
