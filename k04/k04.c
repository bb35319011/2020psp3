#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int id;
    char name[19];  //  市の名前、UTF-8対応
    float members;  //  世帯人員
    int total;      //  食料合計
    int grain;      //  穀類
    int seafood;    //  魚介類
    int meat;       //  肉類
    int milk;       //  乳卵類
    int vegetable;  //  野菜類
    int fruit;      //  果物
    int seasoning;  //  調味料
    int snack;      //  菓子類
    int cocking;    //  調理料理
    int drink;      //  飲料
    int liquor;     //  酒類
    int eatout;     //  外食
} City;

#define DEBUG
#define MAX_CITY    47


void PrintCity(City city)
{
    printf("%d, %s, %.2f, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", 
        city.id, city.name, city.members, city.total, 
        city.grain, city.seafood, city.meat, city.milk, city.vegetable, city.fruit,
        city.seasoning, city.snack, city.cocking, city.drink, city.liquor, city.eatout);
}

void PrintArray(City city[], int size)
{
    int i;

    for (i=0; i<size; i++) {
        PrintCity(city[i]);
    }
}

int LoadData(City arrayCity[])
{
    char buf[256];
    FILE* fp;

    fp = fopen("consumption.csv","r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        return -1;
    }

    int cn = 0; // 市の数
    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%d,%[^,],%f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
            &(arrayCity[cn].id), arrayCity[cn].name, &(arrayCity[cn].members), &(arrayCity[cn].total), 
            &(arrayCity[cn].grain),  &(arrayCity[cn].seafood),  &(arrayCity[cn].meat), &(arrayCity[cn].milk), 
            &(arrayCity[cn].vegetable),  &(arrayCity[cn].fruit),  &(arrayCity[cn].seasoning),  &(arrayCity[cn].snack),
            &(arrayCity[cn].cocking),  &(arrayCity[cn].drink),  &(arrayCity[cn].liquor),  &(arrayCity[cn].eatout));
#ifdef DEBUG
        PrintCity(arrayCity[cn]);
#endif
        cn++;
    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        return -1;
    }

    return cn;
}


void BubbleSort(City arrayCity[], int size)
{
    //  ここを実装する
    City tempCity;
    int tempCount;
    int pos;

    while(1)
    {
        tempCount=0;
        for (pos = 0; pos < (size-1)-pos; pos++)
        {
            if (arrayCity[pos].total > arrayCity[pos+1].total)
            {
                tempCity = arrayCity[pos];
                arrayCity[pos] = arrayCity[pos+1];
                arrayCity[pos+1] = tempCity;

                tempCount++;    //カウントを進める
            }
        }

        if (tempCount == 0)
            break;
    }

}


void QuickSort(City arrayCity[], int left, int right)
{
    //  ここを実装する
    int pos;
    City tempCity;

    int i=left;
    int j=right;
    int pivot=left;

    while (left <= right)//要素が一つ以上なら実行
    {
        for (pos = left; pos <= right ; pos++)
        {
            if(arrayCity[pos].seafood>arrayCity[pivot].seafood)
            {
                i=pos;
                break;
            }
        }
        for (pos = right; pos >=left; pos--)
        {
            if (arrayCity[pos].seafood<=arrayCity[pivot].seafood)
            {
                j=pos;
                break;
            }
        }

        if(i>=j || i==pivot)//ピボットとjを入れ替える条件
        {
            tempCity=arrayCity[pivot];
            arrayCity[pivot]=arrayCity[j];
            arrayCity[j]=tempCity;

            QuickSort(arrayCity,left,j-1);  //ピボットより小さい部分のソート
            QuickSort(arrayCity,j+1,right); //ピボットよりも大きい部分のソート
            break;
        }
    
        //iとjを入れ替えてくりかえす
        tempCity=arrayCity[i];
        arrayCity[i]=arrayCity[j];
        arrayCity[j]=tempCity;
    
    }
    
}



void HeapSort(City arrayCity[], int size)
{
    //  チャレンジ問題(1)
    //  ここを実装する

}


void MergeSort(City arrayCity[], int left, int right)
{
    //  チャレンジ問題2
    //  ここを実装する
    int mid;
    int i,j,k;
    // City* right_buff;
    // City* left_buff;
    City right_buff[256];
    City left_buff[256];

    if (left < right)
    {
        mid = left+(right-left)/2;
        //printf("%d, %d :mid%d\n",left,right,mid);

        MergeSort(arrayCity,left,mid);
        MergeSort(arrayCity,mid+1,right);

        //printf("marge:%d-%d\n",left,right);

        //   right_buff= malloc(sizeof(City)*(mid-left+1));
        //   left_buff = malloc(sizeof(City)*(right-mid));
        //配列コピー
        for (i = 0; i < mid-left+1; i++)
        {
            left_buff[i] = arrayCity[left+i];
        }
        for (j = 0; j < right-mid; j++)
        {
            right_buff[j] = arrayCity[mid+1+j];
        }
       
    //    //-------------------------------------
    //     for (int i = 0; i < mid-left+1; i++)
    //     {
    //         printf("left_buf[%d]=%d\n",i,left_buff[i].liquor);
    //     }
    //     for (int j = 0; j < right-mid; j++)
    //     {
    //         printf("right_buf[%d]=%d\n",j,right_buff[j].liquor);
    //     }
    //    //-------------------------------------    
        

        i=0;
        j=0;
        for( k=0; k < right-left+1; k++ )
        {
            if(i<(mid-left+1) && j<(right-mid))
            {
                if(left_buff[i].liquor < right_buff[j].liquor)
                {
                    arrayCity[left+k]=left_buff[i];
                    i++;
                }else{
                    arrayCity[left+k]=right_buff[j];
                    j++;
                }
            }else{
                if(i<(mid-left+1))
                {
                    arrayCity[left+k]=left_buff[i];
                    i++;
                }else{
                    arrayCity[left+k]=right_buff[j];
                    j++;
                }
            }
        }

        // printf("marged%d-%d:",left,right);
        // for (int index = 0; index < (right-left+1); index++)
        // {
        //     printf("%d, ",arrayCity[left+index].liquor);
        // }
        // printf("\n");
        

        //  free(right_buff);
        //  free(left_buff);      
     }
}

int main(void)
{
 
    //  事前準備。データの読み込み、配列の作成
    City* arrayCity;
    int cn;
    arrayCity = (City*)malloc(sizeof(City) * MAX_CITY);
    cn = LoadData(arrayCity);
    if (cn == -1) {
        exit(EXIT_FAILURE);
    }

    //  食料品合計で並び替え
    printf("===== Sorted by total =====\n");
    BubbleSort(arrayCity, MAX_CITY);
    PrintArray(arrayCity, MAX_CITY);

    //  魚介類で並び替え   
    printf("===== Sorted by seafood =====\n");
    QuickSort(arrayCity, 0, MAX_CITY - 1);
    PrintArray(arrayCity, MAX_CITY);
   
   printf("===== Sorted by MergeSort =====\n");
    MergeSort(arrayCity, 0, MAX_CITY - 1);
//    HeapSort(arrayCity, MAX_CITY);
    PrintArray(arrayCity, MAX_CITY);



    //  後処理
    free(arrayCity);

    return 0;
}