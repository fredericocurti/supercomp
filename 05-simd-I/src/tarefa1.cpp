// Original: Nicolas Brailovsky

#define SIZE (400)
long sum(int v[SIZE]) throw() {
    double *d = new double[100];
    int s = 0; // este exemplo eh didatico. soma de ints deveria ser long ;)
    for (unsigned i=0; i<SIZE; i++) s += v[i];
    return s;
}
