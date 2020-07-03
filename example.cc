#include "obfuscator.hh"
#include "stdio.h"

using namespace ob;

auto gstr = STR("Global HELLO\n");
int main() {
    printf("%s", gstr);
    printf("%s", STR("Stack HELLO\n"));
    printf("%s", "raw HELLO\n");
    return 0;
}
