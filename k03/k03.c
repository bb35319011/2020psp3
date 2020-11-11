#include <stdio.h>
#include <stdlib.h>

#define DEBUG

#define ALPHABET_LEN    255

char StrOriginal[] = "On a dark deseart highway, cool wind in my hair.";
char StrKey[] = "wind";

char* ForceSearch(char text[], char key[])
{
    //  ここを実装する
    char* ch ;
    int start;
    int pos;

    for ( start=0; text[start] != NULL; start++)
    {
        ch = &text[start];//chに検索開始位置を保持
        for (pos = 0; key[pos] != NULL; pos++)
        {
            if (text[start+pos] != key[pos])//一文字ずつ比較
            {
                ch = NULL;
                break;
            }
        }
        if(ch != NULL) //最後まで一致したらreturn
        {
            ch[pos]="\0";
            return ch;
        }
    }

    return NULL;
}

char* BMSearch(char text[], char key[])
{
    //  ここを実装する
    char* ch;
    int start,pos;
    int keyLength=0;
    int *table[256];
    
    //文字数しゅとく
    while (key[keyLength]!=NULL)
    {
        keyLength++;
    }

    //ずらし両テーブル作成
    for(int i=0; i<256; i++)
    {
        table[i]=keyLength;
    }
    for (int i = 0; key[i]!=NULL; i++)
    {
        table[key[i]]=(keyLength-1)-i;
    }

    //比較
    start=keyLength-1;  //検索開始位置の初期化
    while(text[start] != NULL)
    {
        ch =&text[start-(keyLength-1)];  //検索する位置の先頭アドレスを保持
        for(pos=0; key[pos]!=0; pos++)
        {
            if(text[start-pos] != key[(keyLength-1)-pos])//keyの後ろから一文字ずつ比較
            {
                //一致しなかった場所から開始位置をずらす
                if(table[text[start-pos]] > pos)
                {
                    start += (int)table[text[start-pos]] - pos;
                }else{  //開始位置がループしないための処理
                    start++;
                }
                ch=NULL;
                break;
            }
        }
        if(ch !=NULL)//最後まで一致したらreturn
        {
            ch[pos]="\0";
            return ch;
        }
    }

    return NULL;

}

int main(void)
{
    char*   str;
    str = ForceSearch(StrOriginal, StrKey);
    printf("Force Search. Find keyword at:%s\n", str);

    str = BMSearch(StrOriginal, StrKey);
    printf("BM Search. Find keyword at:%s\n", str);

    return 0;
}