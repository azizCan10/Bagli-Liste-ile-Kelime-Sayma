#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct n {          //linked list tan�m�
    int adet;
    char *kelime;
    struct n *next;
};

typedef struct n node;      //n tipinde de�i�keni olu�turma

int enKucuk = 0;      //yeni eklenen kelimenin sona eklenip eklenmeyece�ini kontrol etmeyi sa�layan de�i�ken

void bastir(node *r) {   //linked listi bast�rma fonksiyonu, parametre olarak linked listin ba� eleman�n� al�yor
    int b = 1;
    while (r != NULL) {     //NULL olana kadar elemanlar� yazd�rma d�ng�s�
        printf("%2d. %s: %d\n", b, r->kelime, r->adet);
        r = r->next;
        b++;
    }
}

int ara(node *r, char *kelimee) {    //arama fonksiyonu, parametre olarak linked listin ba� eleman�n� ve aranacak kelimeyi al�yor
    int a = 0;
    while (r != NULL) {     //linked list en sona gidene kadar ara, e�er o kelime daha �nceden linked liste eklenmi�se
        if (strcmp(r->kelime, kelimee) == 0) {   //a de�erini 1 yap
            a = 1;
        }
        r = r->next;
    }
    return a;  //aranacak kelime linked listte varsa 1, yoksa 0 d�nd�r
}

int kacTane(char *kelime) {     //o an okunan kelimeden txt dosyas�nda ka� tane oldu�unu bulan d�ng�
    char *str = malloc(sizeof(char) * 100);
    int count = 0;      //ka� tane oldu�unu sayan de�i�ken

    FILE *dosya;
    dosya = fopen("C:\\Users\\JAN\\Desktop\\metin.txt", "r");   //dosyay� okuma modunda a�

    if (dosya == 0) {					//dosya a��lmad�ysa program� sonland�r
        printf("Dosya acilamadi.");
        return 0;
    }

    fscanf(dosya, "%s", str);       //bo�luk g�rene kadar oku ve okudu�un string i str de�i�kenine ata

    while (!feof(dosya)) {      //txt nin sonuna gidene kadar devam eden d�ng�
        if (strcmp(str, kelime) == 0)   //aranacak kelimeden txt de varsa
            count++;                    //count de�i�kenini 1 artt�r
        fscanf(dosya, "%s", str);       //s�radaki kelimeyi oku ve str de�i�kenine ata
    }

    fclose(dosya);      //dosyay� kapa
    return count;       //o kelimeden ka� tane oldu�unu g�steren de�i�kenin de�erini d�nd�r
}

node *basaEkle(node *r, int adet, char *kelime) {   //yeni okunan kelimenin adet de�eri linked listin ilk eleman�n�n
    node *temp = (node *) malloc(sizeof(node));     //de�erinden daha y�ksekse
    temp->adet = adet;          //temp ad�nda kutu olu�turduk, adet ve kelime bilgisini atad�k
    temp->kelime = kelime;
    temp->next = r;             //temp in next i r yi g�sterdi, yani ilk eleman�m�z temp oldu
    return temp;                //temp i d�nd�rd�
}

node *arayaEkle(node *r, int adet, char *kelime) {  //yeni okunan kelimenin adet de�eri linked listin ilk eleman�n�n
    //de�erinden k���k, son eleman�n de�erinden b�y�kse
    node *iter = r;              //node tipinde iter ad�nda de�i�ken olu�turdu ve r de�erini ona atad�

    while (iter->next != NULL && iter->next->adet > adet) {     //eklenen kelimenin adedi linked listteki elemanlar�n
        iter = iter->next;                  //adedinden k���k olana kadar ilerledi
    }
    while (iter->next != NULL && iter->next->adet == adet) {    //kald��� yerden e�it oldu�u s�rece ilerlemeye
        iter = iter->next;          //devam etti, bu sayede ayn� adet say�s�na e�it olanlar aras�nda sonuncu s�raya ilerledi
    }

    node *temp = (node *) malloc(sizeof(node));     //temp ad�nda yeni kutu olu�turuldu
    temp->next = iter->next;        //araya girmek i�in ba�lant�lar kuruldu
    iter->next = temp;
    temp->adet = adet;              //bilgileri atand�
    temp->kelime = kelime;
    return r;                       //r de�eri d�nd�r�ld�
}

node *sonaEkle(node *r, int adet, char *kelime) {   //en k���k de�erden k���k veya e�itse
    node *iter = r;                 //node tipinde iter ad�nda de�i�ken olu�turdu ve r de�erini ona atad�

    while (iter->next != NULL) {    //iter in next i NULL olana kadar iter i ilerletti
        iter = iter->next;
    }

    iter->next = (node *) malloc(sizeof(node));     //iter in next ine yeni kutu ekledi
    iter->next->adet = adet;            //de�erleri atand�
    iter->next->kelime = kelime;
    enKucuk = adet;                 //en k���k de�er de�i�ti ya da ayn� kald�, bu sayede bu fonksiyonu girildi
    iter->next->next = NULL;        //NULL de�eri elle atand�
    return r;                       //r de�eri d�nd�r�ld�
}

node *ekle(node *r, int adet, char *kelime) {       //linked liste eleman ekleyen fonksiyon
    if (r == NULL) {                            //linked list bo�sa
        r = (node *) malloc(sizeof(node));      //kutu ekle
        r->next = NULL;                 //NULL de�eri elle atand�
        r->adet = adet;                 //de�erleri atand�
        r->kelime = kelime;
        return r;                       //r de�eri d�nd�r�ld�
    }

    if (r->adet < adet) {       //ilk elemandan b�y�k bir eleman olma durumu
        return basaEkle(r, adet, kelime);
    }

    else if (adet <= enKucuk) {         //en k���k de�erden e�it veya k���kse sona ekleme durumu
        return sonaEkle(r, adet, kelime);
    }

    return arayaEkle(r, adet, kelime);          //hi�bir ko�ul sa�lanmad�ysa araya ekleme durumu
}

int main() {
    node *root;         //node dan root ad�nda de�i�ken �retti

    root = (node *) malloc(sizeof(node));       //root de�i�keni i�in bellekten yer ayr�ld�

    char *kontrol;
    char *str = malloc(sizeof(char) * 1000);
    FILE *dosya;
    dosya = fopen("C:\\Users\\JAN\\Desktop\\metin.txt", "r");       //dosya okuma modunda a��ld�

    if (dosya == 0) {						//dosya a��lmad�ysa program� sonland�r
        printf("Dosya acilamadi.");
        return 0;
    }

    fscanf(dosya, "%[^NULL]", str);     //dosya okundu ve str de�i�kenine atand�
    kontrol = strtok(str, " ");         //txt den ilk kelime al�nd�
    root->kelime = kontrol;             //ilk kutuya de�erler atand�
    root->adet = kacTane(kontrol);
    root->next = NULL;                  //NULL de�eri elle atand�
    enKucuk = kacTane(kontrol);
    kontrol = strtok(NULL, " ");        //txt den bir sonraki kelime al�nd�

    while (kontrol != NULL) {
        if (!ara(root, kontrol)) {       //e�er linked listte �uan aranan kelime yoksa
            root = ekle(root, kacTane(kontrol), kontrol);   //ekle fonksiyonunu kullanarak linked liste ekle
        }
        kontrol = strtok(NULL, " ");        //txt den bir sonraki kelime al�nd�
    }

    fclose(dosya);          //dosyay� kapa
    bastir(root);           //linked listi konsola bast�r
    return 0;
}
