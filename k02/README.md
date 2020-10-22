# 課題2 レポート
bb35319011 江島奨悟


## 課題
長崎県にある市町村別人口データを読み込み、リスト構造にするプログラムを作成する。

1. 使用するデータ  
長崎県の人口データは、nagasaki.csvに保存されている。
nagasaki.csvには、csv形式で以下のデータが含まれる
- ID
- 県名
- 市町村名
- 人口
- 男性人口
- 女性人口

長崎県の市町村別人口データは、下記に構造体に読み込まれる。
```
typedef struct {
    int id;
    char pref[13];  // UTF-8対応
    char name[19];  // UTF-8対応
    int population;
    int m_population;
    int f_population;
} City;
```

2. 必須問題：実装する関数  
(1) InsertNewNode：必要なメモリを確保し、リストの先頭に新しいデータを挿入する。  
    [入力]
    - City newCity: リストに挿入する市町村のデータ
    - Node* pNext: リストの先頭アドレス  

    [出力]  
    - return値: (リストの先頭に新しいデータを挿入した後の)リストの先頭アドレス

    (2) SearchCityByID: IDをキーとし、リストを検索する。  
    [入力]  
    - Node* pList: リストの先頭アドレス
    - int ID: 検索する市町村のID 
    
    [出力]  
    - return値: IDが合致した場所(先頭を0とする)。IDが一致するデータがない場合は-1。  
    - City* pCity: IDが合致した市町村のデータを入れる

3. 補助関数  
以下の関数はすでに実装されており、利用することができる。  
- PrintCity: 市町村データを出力する
- ReleaseList: リストで確保したメモリを解放する
- PrintList: リストの内容を出力する。

4. チャレンジ問題  
(1) DeleteNodeAt: 任意のノードをリストから削除する(10点)  
    [入力]  
    - Node** ppNode: リストの先頭を指すポインタ変数のアドレス(ポインタのポインタ)  
    - int cn: ノードの位置(先頭のノードを0とする)  
    [出力]  
    - return値: 削除に成功したらSUCCESS、失敗したらERRR  

    (2) SearchCityByName: 市町村を名称で検索する(5点)  
    [入力]
    - int key: 検索する市町村のID
    - City arrayCity: 検索対象の都市別人口データ(配列)
    - int size: データの数  

    [出力]  
    - return値: IDが合致した配列データのindex。IDが一致するデータがない場合は-1。

## ソースコードの説明
関数InsertNewNodeの実装
    新しくnewnodeのメモリを確保しCityデータとPNextデータを代入。確保したメモリの先頭アドレスをreturnする。

関数SearchCityByIDの実装
    カウント用変数iとNodeポインタを用意して先頭から探索を行う。一致したidがあった場合、受け取ったCityアドレスの中身にデータを代入し、その時のカウンタをリターンする。

関数SearchCityByNameの実装
    カウント用変数iとNodeポインタを用意してID探索の時と同様に先頭から探索を行う（文字列の比較には関数strcmpを用いた）。名前が一致した場合はそのcityデータを受け取ったcity型ポインタの中身に格納してメイン関数でも利用できるようにし、その時のカウンタをリターンする。

関数DeleteNodeAtの実装
    要素の位置(先頭を0とする)を指定して要素の削除を行う。リスト一番目の削除をうまく処理できなかったので、一番目を消すときと2番目以降を消すときの2つを分けて考えた。
    一番目を消すときは受け取ったPPNodeの中身に直接2番目のアドレスを渡してメモリ開放を行った
    二番目以降を消すときはpPrevとpNodeを用いて連続しているリストのアドレスを保持し、削除を行うひとつ前の要素（pPrev）のpNextを、削除を行う要素（pNode）のpNextに繋ぎ直してメモリ開放を行った。



## 出力結果

```
42201, NagasakiKen, Nagasaki, 429508, 198716, 230792
42202, NagasakiKen, Sasebo, 255439, 120198, 135241
42203, NagasakiKen, Shimabara, 45436, 20999, 24437
42204, NagasakiKen, Isahaya, 138078, 65029, 73049
42205, NagasakiKen, Omura, 92757, 43938, 48819
42207, NagasakiKen, Hirado, 31920, 14874, 17046
42208, NagasakiKen, Matsuura, 23309, 11164, 12145
42209, NagasakiKen, Tsushima, 31457, 15361, 16096
42210, NagasakiKen, Iki, 27103, 12860, 14243
42211, NagasakiKen, Goto, 37327, 17339, 19988
42212, NagasakiKen, Saikai, 28691, 14032, 14659
42213, NagasakiKen, Unzen, 44115, 20847, 23268
42214, NagasakiKen, MinamiShimabara, 46535, 21574, 24961
42307, NagasakiKen, Nagayo, 42548, 20090, 22458
42308, NagasakiKen, Togitsu, 29804, 14326, 15478
42321, NagasakiKen, HigashiSonogi, 8298, 3886, 4412
42322, NagasakiKen, Kawatana, 14067, 6656, 7411
42323, NagasakiKen, Hasami, 14891, 7079, 7812
42383, NagasakiKen, Ojika, 2560, 1172, 1388
42391, NagasakiKen, Sasa, 13626, 6426, 7200
42411, NagasakiKen, ShinKamigoto, 19718, 9197, 10521
===== Start Printing =====
42411, NagasakiKen, ShinKamigoto, 19718, 9197, 10521
42391, NagasakiKen, Sasa, 13626, 6426, 7200
42383, NagasakiKen, Ojika, 2560, 1172, 1388
42323, NagasakiKen, Hasami, 14891, 7079, 7812
42322, NagasakiKen, Kawatana, 14067, 6656, 7411
42321, NagasakiKen, HigashiSonogi, 8298, 3886, 4412
42308, NagasakiKen, Togitsu, 29804, 14326, 15478
42307, NagasakiKen, Nagayo, 42548, 20090, 22458
42214, NagasakiKen, MinamiShimabara, 46535, 21574, 24961
42213, NagasakiKen, Unzen, 44115, 20847, 23268
42212, NagasakiKen, Saikai, 28691, 14032, 14659
42211, NagasakiKen, Goto, 37327, 17339, 19988
42210, NagasakiKen, Iki, 27103, 12860, 14243
42209, NagasakiKen, Tsushima, 31457, 15361, 16096
42208, NagasakiKen, Matsuura, 23309, 11164, 12145
42207, NagasakiKen, Hirado, 31920, 14874, 17046
42205, NagasakiKen, Omura, 92757, 43938, 48819
42204, NagasakiKen, Isahaya, 138078, 65029, 73049
42203, NagasakiKen, Shimabara, 45436, 20999, 24437
42202, NagasakiKen, Sasebo, 255439, 120198, 135241
42201, NagasakiKen, Nagasaki, 429508, 198716, 230792
print list. items = 21
===== Print End =====
City ID?42308
the city was found at 6
42308, NagasakiKen, Togitsu, 29804, 14326, 15478
City Name?Togitsu
the city was found at 6
42308, NagasakiKen, Togitsu, 29804, 14326, 15478        
===== Start Printing =====
42411, NagasakiKen, ShinKamigoto, 19718, 9197, 10521    
42391, NagasakiKen, Sasa, 13626, 6426, 7200
42383, NagasakiKen, Ojika, 2560, 1172, 1388
42323, NagasakiKen, Hasami, 14891, 7079, 7812
42322, NagasakiKen, Kawatana, 14067, 6656, 7411
42321, NagasakiKen, HigashiSonogi, 8298, 3886, 4412     
42307, NagasakiKen, Nagayo, 42548, 20090, 22458
42214, NagasakiKen, MinamiShimabara, 46535, 21574, 24961
42213, NagasakiKen, Unzen, 44115, 20847, 23268
42212, NagasakiKen, Saikai, 28691, 14032, 14659
42211, NagasakiKen, Goto, 37327, 17339, 19988
42210, NagasakiKen, Iki, 27103, 12860, 14243
42209, NagasakiKen, Tsushima, 31457, 15361, 16096
42208, NagasakiKen, Matsuura, 23309, 11164, 12145
42207, NagasakiKen, Hirado, 31920, 14874, 17046
42205, NagasakiKen, Omura, 92757, 43938, 48819
42204, NagasakiKen, Isahaya, 138078, 65029, 73049
42203, NagasakiKen, Shimabara, 45436, 20999, 24437
42202, NagasakiKen, Sasebo, 255439, 120198, 135241
42201, NagasakiKen, Nagasaki, 429508, 198716, 230792
print list. items = 20
===== Print End =====
free list. items = 20

```

## 修正履歴

