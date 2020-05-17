#include <stdio.h>
#include <string.h>
#include <conio.h>

struct kayit{
  char isim[16];
  char soyisim[21];
  char tel[11];
};

void menuHazirla();
int telefonEkle();
int telefonlariListele();
int aramaYap(char *);

void menuHazirla(){
  printf("--------------------------------------\n");
  printf("*                                    *\n");
  printf("*          telefon rehberi           *\n");
  printf("*            programi !              *\n");
  printf("*                                    *\n");
  printf("*                                    *\n");
  printf("*        1. telefon Ekle             *\n");
  printf("*        2. telefonlari Listele      *\n");
  printf("*        3. Arama Yap                *\n");
  printf("*        4. Cikis                    *\n");
  printf("*                                    *\n");
  printf("--------------------------------------\n");
}

int telefonEkle(){

  struct kayit yeniKayit;
  FILE *ptVeritabani;

  // dosyaya ac:
  if((ptVeritabani=fopen("telefonVeritabani.txt","a"))==NULL){
    return -1;
  }
  printf("\n\n");
  printf("isim giriniz(max 15 karakter): ");
  scanf("%s",yeniKayit.isim);

  printf("soyisim giriniz(max 20 karakter): ");
  scanf("%s",yeniKayit.soyisim);

  printf("telefon numarasini giriniz(max 10 karakter): ");
  scanf("%s",yeniKayit.tel);

  fprintf(ptVeritabani, "\n%s\t%s\t%s", yeniKayit.isim, yeniKayit.soyisim, yeniKayit.tel);

  fclose(ptVeritabani);
  return 0;
}


int telefonlariListele(){

  // dosyadaki tum telefonlari listele
  // dosyaya ac:
  FILE *ptVeritabani;
  struct kayit aktifKayit;
  if((ptVeritabani=fopen("telefonVeritabani.txt","r"))==NULL){
    return -1;
  }

  printf("\n\nisim\t\t\tsoyisim\t\t\ttel\n");
  printf("----\t\t\t-----\t\t\t---\n\n");
  // dosya sonuna kadar tum verileri oku:

  while(!feof(ptVeritabani)){
    fscanf(ptVeritabani,"%s%s%s",&aktifKayit.isim, &aktifKayit.soyisim, &aktifKayit.tel);
    printf("%s\t\t\t",aktifKayit.isim);
    printf("%s\t\t\t",aktifKayit.soyisim);
    printf("%s\n",aktifKayit.tel);
  }

  fclose(ptVeritabani);
  return 0;
}

int aramaYap(char *arananIsim){

  // dosyadaki tum telefonlarini ara
  // dosyaya ac:
  FILE *ptVeritabani;
  struct kayit aktifKayit;
  int bulunan=0;

  if((ptVeritabani=fopen("telefonVeritabani.txt","r"))==NULL){
    return -1;
  }

  // dosya sonuna kadar tum verileri oku:
  while(!feof(ptVeritabani)){
    fscanf(ptVeritabani,"%s%s%s",&aktifKayit.isim, &aktifKayit.soyisim,&aktifKayit.tel);

    if(!strcmp(arananIsim, aktifKayit.isim)){ // bbulundu!
      printf("%s\t\t\t",aktifKayit.isim);
      printf("%s\t\t\t",aktifKayit.soyisim);
      printf("%s\n",aktifKayit.tel);
      bulunan++;
    }
  }

  fclose(ptVeritabani);
  return bulunan;
}

int main(){
  char secim='0';
  char aranacakIsim[16];
  int telAra=-1;

  // menu hazirla:
  menuHazirla();

  do{
    printf("\n\nseciminiz: ");
    secim = putch(getch());

    switch (secim){
      case '1':
        if (telefonEkle()==0){ // geri bildirim:
          printf("\ntel basariyla eklendi.");
        }else{
          printf("\nHATA: tel eklenemedi!");
        }
        break;
      case '2':
        if (telefonlariListele()==0){ // geri bildirim:
          printf("\ntel basariyla listelendi.");
        }else{
          printf("\nHATA: telefon tellari listelenemedi!");
        }
        break;
      case '3':
        printf("\naranacak ismi giriniz(max 15 karakter):");
        scanf("%s",aranacakIsim);

        telAra = aramaYap(aranacakIsim);
        if (telAra == 0){ // geri bildirim:
          printf("\naranan isim kayitlarda bulunamadi.");
        }else {
          if(telAra > 0)
            printf("\ntoplam %d kayit bulundu.",telAra);
          else
            printf("\nHATA: tel aranamadi!");
        }
        break;
      case '4':
       
        return 0;
        break;
      default:
        printf("\nlutfen 1-4 arasinda bir secim yapiniz.");

    }
  }while(secim!=4);

  return 0;
}
