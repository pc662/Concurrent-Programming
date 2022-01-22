
global int i, j, k;

Main:
    array a, b, c;
    bool done = false;





Thread looper (array &a, array &b, array &c, bool &done):

    while (true) {
        if (a[i] == b[j] && a[i] == c[k]) {
            std::cout << "i: " << i << " j: " << j << " k: " << k << std::endl;
            done = true;
            break;
        } 
    }
    


Thread a (array &a, array &b, array &c, bool &done):

while (!done) {
    if (a[i] < b[j] || a[i] < c[k]) {
        i++;
    }
}

Thread b (array &a, array &b, array &c, bool &done):

while (!done) {
    if (b[j] < a[i] || b[j] < c[k]) {
        j++;
    }
}

Thread c (array &a, array &b, array &c, bool &done):

while (!done) {
    if (c[k] < a[i] || c[k] < b[j]) {
        k++;
    }
}