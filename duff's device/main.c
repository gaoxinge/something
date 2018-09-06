#include <stdio.h>


void copy1(char *from, char *to, int count) {
    switch (count % 8) {
        case 0:
            do {
                *to++ = *from++;
                case 7:
                *to++ = *from++;
                case 6:
                *to++ = *from++;
                case 5:
                *to++ = *from++;
                case 4:
                *to++ = *from++;
                case 3:
                *to++ = *from++;
                case 2:
                *to++ = *from++;
                case 1:
                *to++ = *from++;
            } while ((count -= 8) > 0);
    }
}


void copy2(char *from, char *to, int count) {
    for (int i = 0; i < count; i++)
        *to++ = *from++;
}


int main() {
    char *from = "123456";
    char to1[7];
    char to2[7];
    
    // duff's device通过减少循环体的个数来提高效率
    copy1(from, to1, 7);
    copy2(from, to2, 7);

    printf("%s\n", from);
    printf("%s\n", to1);
    printf("%s\n", to2);
    return 0;
    
}