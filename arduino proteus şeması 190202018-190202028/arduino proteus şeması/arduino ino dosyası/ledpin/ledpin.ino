#include <LiquidCrystal.h> //lcd kütüphanesi
#include<Time.h>
// hex dosyası değişebiliyor güncellemeyi unutma her seferinde
// muhammed enbiya demir 190202018 - çağkan çağman ceran 190202028

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // lcd portları
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //lcd objesi oluşturma

int yuz=0;
int elli=0;
int yirmi=0;
int on=0;
int bes=0;

boolean birkere=true;

int mode=0; // 0 ise para , 1 ise hizmet modu
int odenen=0; // müşterinin girdiği para

int secilenid=0; 

int secilenucret=0; // secilen hizmetin ucreti
int kalan=0; 


int banka[]={20,20,10,30,5}; // atmde kalan paralar
int bankatoplam=(banka[0]*5)+(banka[1]*10)+(banka[2]*20)+(banka[3]*50)+(banka[4]*100);
int hizmetId [4]={1,2,3,4};
String hizmetad [4]={"köpükle","yıka","kurula","cila"};
int hizmetsayi [4]={30,50,100,20};
int hizmetucret [4]={15,10,5,50};

//led girişleri
int ledPinRed=9;
int ledPinGreen=10;

// buton stateleri
boolean buttonState13=false;
boolean buttonState14=false;
boolean buttonState15=false;
boolean buttonState16=false;
boolean buttonState17=false;
boolean buttonState18=false;
boolean buttonState19=false;

long randomnumb; //random num

void setup(){

  

 lcd.begin(16, 2); // lcd modeli 16x2
 
  
  //pin outputları
    pinMode(ledPinRed,OUTPUT);
    pinMode(ledPinGreen,OUTPUT);

// buton inputları
    for(int i = 15;20>i;i++){
  pinMode(i, INPUT);  //initialize the pushbutton pin as an output
  }
  pinMode(13, INPUT);
  pinMode(8, INPUT);

 //virtual terminal için serial begin
  Serial.begin(9600);

  // random sayı farklı olsun randomseed fonksiyonu
  randomSeed(analogRead(A0)); 
        
  delay(10);

// virtual terminale neyden ne kadar kaldığı yazdırılıyor
  Serial.print(" 5luk:");  Serial.print(banka[0]);     
  Serial.print(" 10luk:"); Serial.print(banka[1]);   
  Serial.print(" 20luk:"); Serial.print(banka[2]);
  Serial.print(" 50luk:"); Serial.print(banka[3]);
  Serial.print(" 100luk:"); Serial.print(banka[4]);
  Serial.println("");
  
  Serial.print(" kopukle:"); Serial.print(hizmetsayi[0]);
  Serial.print(" yikama:"); Serial.print(hizmetsayi[1]);
  Serial.print(" kurulama:"); Serial.print(hizmetsayi[2]);
  Serial.print(" cilalama:"); Serial.print(hizmetsayi[3]);
}

// köpük  yıka  kurula  cila       bitiş reset
// 5       10    20     50    100  bitiş reset  

void loop() {
  
  
  //buton stateleri eşleştiriyoz
  buttonState13=digitalRead(13); 
  buttonState14=digitalRead(8);
  buttonState15=digitalRead(15);
  buttonState16=digitalRead(16);
  buttonState17=digitalRead(17);
  buttonState18=digitalRead(18); // bitiş
  buttonState19=digitalRead(19); //reset

   //lcd.print("ne yazacaksa");
   //lcd.setCursor(column,row);  
  //if(buttonState13==HIGH){
   // digitalWrite(ledPinRed,HIGH);
  //delay(500);
  //digitalWrite(ledPinRed,LOW);

if(mode==0){ // mode 0 para girme modu
  birkere=true;
  if(buttonState13==HIGH){
      delay(300);
     odenen+=5;
     lcd.clear();
     lcd.print("Para = ");
     lcd.print(odenen);
     lcd.print(" TL");
    }
    if(buttonState14==HIGH){
       delay(300);
     odenen+=10;
     lcd.clear();
     lcd.print("Para = ");
     lcd.print(odenen);
     lcd.print(" TL");
    }
    if(buttonState15==HIGH){ 
      delay(300);
     odenen+=20;
     lcd.clear();
     lcd.print("Para = ");
     lcd.print(odenen);
     lcd.print(" TL");
    }
    if(buttonState16==HIGH){ 
      delay(300);
     odenen+=50;
     lcd.clear();
     lcd.print("Para = ");
     lcd.print(odenen);
     lcd.print(" TL");
    }
    if(buttonState17==HIGH){ 
      delay(300);
     odenen+=100;
     lcd.clear();
     lcd.print("Para = ");
     lcd.print(odenen);
     lcd.print(" TL");
    }
    if(buttonState18==HIGH&&odenen>0){ //bitis
      delay(500);
      lcd.clear();
      lcd.print(odenen);
      lcd.print(" TL");
      lcd.print(" ATTINIZ");
      delay(700);
      lcd.setCursor(0,1);
      mode=1;
    }
    if(buttonState19==HIGH){ //reset
      delay(300);
     odenen=0;
     lcd.clear();
     lcd.print("RESET ATTINIZ");
     delay(400);
     lcd.clear();
    }
    
    // hizmet secme aşaması
    }

    buttonState13=digitalRead(13); 
  buttonState14=digitalRead(8);
  buttonState15=digitalRead(15);
  buttonState16=digitalRead(16);
  buttonState17=digitalRead(17);
  buttonState18=digitalRead(18); // bitiş
  buttonState19=digitalRead(19); //reset

// HİZMET SECME ASAMASI MODE 1
  
    if(mode==1){
      if(buttonState13==HIGH){
        delay(300);
        lcd.clear();
        lcd.print("Kopukleme ");
        secilenid=1;
        secilenucret=hizmetucret[0];
        lcd.print(hizmetucret[0]);
        }
        
        if(buttonState14==HIGH){
        delay(300);
        lcd.clear();
        lcd.println("Yikama ");
                secilenid=2;
        secilenucret=hizmetucret[1];
        lcd.print(hizmetucret[1]);
        }
        
        if(buttonState15==HIGH){
        delay(300);
        lcd.clear();
        lcd.print("Kurulama ");
                secilenid=3;
        secilenucret=hizmetucret[2];
        lcd.print(hizmetucret[2]);
        }
        
        if(buttonState16==HIGH){
        delay(300);
        lcd.clear();
        lcd.print("Cilalama ");
        secilenid=4;
        secilenucret=hizmetucret[3];
        lcd.print(hizmetucret[3]);
        }
        
//state18 butonu için farklı durumlar

         if(buttonState18==HIGH&&hizmetsayi[secilenid-1]<=0){
          delay(300);
        lcd.clear();
        lcd.print("hizmet kalmadi");
        digitalWrite(ledPinRed,HIGH);
        delay(1000);
        lcd.clear();
        digitalWrite(ledPinRed,LOW);
        mode=0;
          }

         if(buttonState18==HIGH&&odenen-secilenucret<0){ //bitiş ama fakirsen
        delay(300);
        lcd.clear();
        lcd.print("Paran yetersiz.Reset.");
        digitalWrite(ledPinRed,HIGH);
        delay(1000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.clear();
        mode=0;
        digitalWrite(ledPinRed,LOW);
        }

        if(buttonState18==HIGH&&ustuolurmu(banka,odenen,secilenucret)==0){ //bitiş ama para üstünün hepsini veremiyor
        delay(300);
        lcd.clear();
        lcd.print("atm para kalmadi");
        digitalWrite(ledPinRed,HIGH);
        delay(1000);
        lcd.clear();
        digitalWrite(ledPinRed,LOW);
        mode=0;
        }

        if(birkere==true){
      randomnumb = random(1,5); 
      Serial.println(" ");
      Serial.print("RANDOM SAYI: "); 
     Serial.print(randomnumb);
     Serial.println(" ");

      birkere = false;
       }
        
        if(randomnumb==2){ // para sıkışması
         mode=0;
         odenen=0;
        digitalWrite(ledPinRed,HIGH);
        lcd.clear();
        lcd.print("PARA SIKISTI");
        delay(1200);
        digitalWrite(ledPinRed,LOW);
        }

        if(buttonState18==HIGH&&odenen-secilenucret>=0&&ustuolurmu(banka,odenen,secilenucret)==1&&randomnumb!=2){ //bitiş gerçek
          
        delay(300);
        lcd.setCursor(0,1);
        lcd.print("sectiniz");
        digitalWrite(ledPinGreen,HIGH);
        delay(1000);
        digitalWrite(ledPinGreen,LOW);
        mode=0;

hizmetsayi[secilenid-1]--;

 
 
  kalan=odenen-secilenucret;
  odenen=0;
  
  lcd.clear();
  lcd.print("PARA USTU: ");
  lcd.print(kalan);
  
  delay(1000);

  
  for(;banka[4]>0;banka[4]--){
  if(kalan>=100){
     yuz++;
      kalan-=100;}
      else{
      break;}
      }
  
  for(;banka[3]>0;banka[3]--){
  if(kalan>=50){
     elli++;
      kalan-=50;}
      else{
      break;}
      }
  
  for(;banka[2]>0;banka[2]--){
  if(kalan>=20){
     yirmi++;
      kalan-=20;}
      else{
      break;}
      }

 for(;banka[1]>0;banka[1]--){
  if(kalan>=10){
      on++;
      kalan-=10;}
      else{
      break;}
      }

  for(;banka[0]>0;banka[0]--){
  if(kalan>=5){
      bes++;
      kalan-=5;}
      else{
      break;}
      }

      

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ustu:");
  lcd.print(" 5:");
  lcd.print(bes);
  lcd.print(" 10:");
  lcd.print(on);
  lcd.setCursor(0,1);
  lcd.print(" 20:");
  lcd.print(yirmi);
  lcd.print(" 50:");
  lcd.print(elli);
  lcd.print(" 100:");
  lcd.print(yuz);

      //kasadaki para ve kalan hizmet virtual terminalde gözlemlenebilir
  Serial.println("");
  Serial.print(" 5luk:");  Serial.print(banka[0]);     
  Serial.print(" 10luk:"); Serial.print(banka[1]);   
  Serial.print(" 20luk:"); Serial.print(banka[2]);
  Serial.print(" 50luk:"); Serial.print(banka[3]);
  Serial.print(" 100luk:"); Serial.print(banka[4]);
  Serial.println("");
  
  Serial.print(" kopukle:"); Serial.print(hizmetsayi[0]);
  Serial.print(" yikama:"); Serial.print(hizmetsayi[1]);
  Serial.print(" kurulama:"); Serial.print(hizmetsayi[2]);
  Serial.print(" cilalama:"); Serial.print(hizmetsayi[3]);

  
  delay(1000);
 yuz=0;
 elli=0;
 yirmi=0;
 on=0;
 bes=0;

 
        }
        
         //state 18 bitti
         
        if(buttonState19==HIGH){ //reset
        delay(300);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.clear();
        odenen=0;
        lcd.print("RESET ATTINIZ");
        mode=0;
        delay(300);

        }
        
      }
   
   
  delay(100);
  
}

int ustuolurmu(int banka[],int odenen,int secilenucret){ // istenen banknotlara sahip mi testi
  
  int kalan=odenen-secilenucret;
  
int sayac100=0;
int sayac50=0;
int sayac20=0;
int sayac10=0;
int sayac5=0;

for(;banka[4]>0;banka[4]--){
  if(kalan>=100){
    sayac100++;
      kalan-=100;}
      else{
      break;}
      }
  
  for(;banka[3]>0;banka[3]--){
  if(kalan>=50){
     sayac50++;
      kalan-=50;}
      else{
      break;}
      }
  
  for(;banka[2]>0;banka[2]--){
  if(kalan>=20){
     sayac20++;
      kalan-=20;}
      else{
      break;}
      }

 for(;banka[1]>0;banka[1]--){
  if(kalan>=10){
     sayac10++;
      kalan-=10;}
      else{
      break;}
      }

  for(;banka[0]>0;banka[0]--){
  if(kalan>=5){
      sayac5++;
      kalan-=5;}
      else{
      break;}
      }

for(;sayac100>0;sayac100--){banka[4]++;}
for(;sayac50>0;sayac50--){banka[3]++;}
for(;sayac20>0;sayac20--){banka[2]++;}
for(;sayac10>0;sayac10--){banka[1]++;}
for(;sayac5>0;sayac5--){banka[0]++;}


      if(kalan==0){
        return 1;
        }
        else{return 0;}
  
  }
