#include <stdio.h>
#include <stdlib.h>

void calculate_overhead_a(int n){
    int data_bytes_per_node = 4;
    int pointer_bytes_per_node = 3 * 4;
    int total_bytes_per_node = data_bytes_per_node + pointer_bytes_per_node;

    long total_data_space = (long)n * data_bytes_per_node;
    long total_space = (long)n * total_bytes_per_node;
    double fraction = (double)total_data_space / total_space;

    printf("(a) (%d dugum): \n", n);
    printf(" - Veri Alani: %ld bayt\\n", total_data_space);
    printf(" - Toplam Alan: %ld bayt\\n", total_space);
    printf(" - Veri Orani (Data / Total): %.4f (%%%0.2f)\\n", fraction, fraction * 100);
    printf(" - Overhead Orani: %0.2f%%\\n\\n", (1.0 - fraction) * 100);
}

void calculate_overhead_b(int n){
    int L = (n + 1) / 2; // yaprak sayisi
    int I = (n - 1) / 2; // ic dugum sayisi

    int leaf_bytes = 4;     // sadece 4 bytelik veri
    int internal_bytes = 4; 

    long total_data_space = (long)L * leaf_bytes;
    long total_space = ((long)L * leaf_bytes) + ((long)I * internal_bytes);
    double fraction = (double)total_data_space / total_space;

    printf("(b) (%d dugum, %d yaprak, %d ic dugum): \n", n, L, I);
    printf(" - Veri Alani (Sadece Yapraklar): %ld bayt\n", total_data_space);
    printf(" - Toplam Alan: %ld bayt\n", total_space);
    printf(" - Veri Orani (Data / Total): %.4f (%%%0.2f)\n", fraction, fraction * 100);
    printf(" - Asymptotik Oran (n -&gt; infinity): ~0.5000 (%%50.00)\n\n");

}

int main(){
    printf("=== Problem 3-5: İkili Ağaç Bellek Analizi ===\n\n");

    int test_n = 1023;

    calculate_overhead_a(test_n);
    calculate_overhead_b(test_n);

    return 0;
}

