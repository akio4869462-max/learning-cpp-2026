int main(void) {
    int a = 1, b = 2;

    const int *p = &a;
    p = &b;
    *p = 100;

    int *const p2 = &a;
    p2 = &b;
    *p2 = 100;

    return 0;
}