//
// Created by toxaxab on 01.06.18.
//
extern int code();
extern int decode();
int main() {
    if(!code()) {
        decode();
        return 0;
    }
    return 1;
}