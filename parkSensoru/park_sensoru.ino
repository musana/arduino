#include <LiquidCrystal.h> 

#define echoPin 11
#define trigPin 12

int buzzerPin = 13; // Arduino'daki buzzer pin numarası
int volume = 0;

LiquidCrystal lcd(9, 8, 5, 4, 3, 2); // Parameters: (rs, enable, d4, d5, d6, d7) 

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);	//Ultrasonic ses sensörü pin ayarlaması
  pinMode(echoPin, INPUT);	//Ultrasonic ses sensörü pin ayarlaması
  pinMode(buzzerPin, OUTPUT);	//Buzzer pin ayarlaması

  lcd.begin(16,2);  		//Lcd satır ve sutun belirtilmesi

  delay(100);
}

void loop()
{
  float uzaklik;
  int sure;

  digitalWrite(trigPin, HIGH);	  // trigpin'e gerilim ver.	
  delay(200);			                // saniyenin 5'te 1 ' i kadar bekle
  digitalWrite(trigPin, LOW);	  	// trigpin'e 0volt ver.
  sure = pulseIn(echoPin, HIGH);	// Sesin çarpıp geri döndükten sonra geçen süreyi hesapla
  uzaklik = (sure/2)/28.5;		    // Uzaklık hesaplaması cm' türünden
  
  lcd.setCursor(0,0);			// imleç'i lcd'nin sıfırıncı satır ve sıfırıncı sutununa getir.
  lcd.print("Mesafe: ");	// Ekrana yazı yaz
  lcd.print(uzaklik,2);		// Virgulden sonra 2  basamak ayarlaması
  lcd.setCursor(14,0);		// imleç posizyonu
  lcd.print("cm");			  //yazı yaz

  lcd.setCursor(0,1);			//imleç posizyonu


  if(uzaklik < 20){
    lcd.print("TEHLİKE!!!");		// uzaklık 20 cm 'nin altında ise yapılacak.
  
  for(int i=0; i<2; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(1200);
      digitalWrite(buzzerPin, LOW);
      delay(10);
  }

  }else if(uzaklik > 20 && uzaklik < 30) {	// uzaklık 20 ile 30 cm arasında ise
    lcd.print("DİKKAT ET!");
    
    for(int i=0; i<2; i++) {
        digitalWrite(buzzerPin, HIGH);
        delay(800);
        digitalWrite(buzzerPin, LOW);
        delay(100);
    }
  
  }else if(uzaklik > 30 && uzaklik < 50){		// uzaklık 30 ile 50 cm arasında ise
     lcd.print("UYARI!");
     
        for(int i=0; i<2; i++) {
        digitalWrite(buzzerPin, HIGH);
        delay(400);
        digitalWrite(buzzerPin, LOW);
        delay(300);
    }
  }

   else {					// uzaklık yarım metreden fazla ise bir şey yapma
        lcd.print("DEVAM ET!");
    }  
    
  delay(100);
  
}
