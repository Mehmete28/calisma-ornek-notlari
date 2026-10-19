#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// recursive blackbox simulator

bool black_box_subset_sum(int X[], int len, int k){
    if(k == 0) return true;
    if(len == 0 || k < 0) return false;
    return black_box_subset_sum(X, len - 1, k)|| black_box_subset_sum(X, len - 1, k - X[len - 1]);
}

// Blackbox cagirisi ile subnet bulma algoritmasi

void find_subset_sum(int S[], int n, int target_k){
    printf("Hedef Toplam (k): %d\n",target_k);

    if(!black_box_subset_sum(S, n, target_k)){
        printf("Toplami %d olan bir alt kume YOK!\n", target_k);
        return;
    }

    int current_S[2], temp_S[2], result_subset[2];
    int current_len = n,  result_count = 0;
    int current_k = target_k, total_calls = 1;

    for (int i = 0; i < n; i++){
        int elem = S[i];
        
        // "elem" haric diger elemanlardan olusan temp_S dizisini olustur

        int temp_len = 0;
        bool skipped = false;

        for(int j = 0; j < current_len; j++){
            if(!skipped && current_S[j] == elem){
                skipped = true;
                continue;
            }
            temp_S[temp_len++] = current_S[j];
        }
        total_calls++;
        
        // elem olmadan hedef k elemani olusturulabiliyor mu

        if(black_box_subset_sum(temp_S, temp_len,current_k)){
            //evet ise: Bu eleman zorunlu degildir
            current_len = temp_len;
            for(int j =0 ; j< temp_len;j++) current_S[j] =temp_S[j];
        } else {
            // Hayir ise : Bu eleman alt kume icin Zorunldur
            result_subset[result_count++] = elem;
            current_k -= elem; // Hedef toplami guncelliyoruz
            current_len = temp_len;
            for(int j = 0; j <  temp_len; j++) current_S[j] = temp_S[j];
        }
    }


}

    