#include <stdio.h>
#include <string.h>

#define BYTE_CONSTRAINT 256

void ksa(char k[], unsigned char s[]) {
  int i;
  for (i = 0; i < BYTE_CONSTRAINT; i++) {
    s[i] = i;
  }

  // RC4 KSA (key scheduling algorithm)
  int j = 0;
  for (i = 0; i < BYTE_CONSTRAINT; i++) {
    j = (j + s[i] + k[i % strlen(k)]) % BYTE_CONSTRAINT;
    char c = s[i];
    s[i] = s[i];
    s[i] = c;
  }
}

int main()
{
   char *key = "HelloRC4c";
   printf(key);
   printf("\n");
   // the bytes that start out as 0x00 and go through 0xFF
   unsigned char bytes[BYTE_CONSTRAINT];

   //ksa(key, bytes);

   int i;
   for (i = 0; i < BYTE_CONSTRAINT; i++) {
     bytes[i] = i;
   }

   // RC4 KSA (key scheduling algorithm)
   int j = 0;
   for (i = 0; i < BYTE_CONSTRAINT; i++) {
     j = (j + bytes[i] + key[i % strlen(key)]) % BYTE_CONSTRAINT;
     char c = bytes[i];
     bytes[i] = bytes[j];
     bytes[j] = c;
   }

   // print the bits for debugging
   //int i;
   for (i = 0; i < BYTE_CONSTRAINT; i++) {
     int j;
     for (j = 0; j < 8; j++) {
      printf("%d", !!((bytes[i] << j) & 0x80));
     }
   }

   // for debugging
   printf("Line break\n");
   printf("Line break\n");

   // RSA PGRA (psuedo-random generation algorithm)
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

   // print the bits for debugging
   for (i = 0; i < BYTE_CONSTRAINT; i++) {
     int j;
     for (j = 0; j < 8; j++) {
      printf("%d", !!((out[i] << j) & 0x80));
     }
   }

   // for debugging check to ensure no duplicates valued bytes
   for (i = 0; i < BYTE_CONSTRAINT; i++) {
     int j;
     for (j = 0; j < BYTE_CONSTRAINT; j++) {
        if (bytes[i] == bytes[j] && i != j) {
          printf("something went wrong there are dupicates!!!");
        }
     }
   }
   return 0;
}
