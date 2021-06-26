#include <ESP8266WiFi.h>
#include <UniversalTelegramBot.h>

#define WIFI_SSID "*****"
#define WIFI_PASSWORD "*****"
WiFiClientSecure secured_client;
//Конфигурация телеграм
#define BOT_TOKEN "*****"
#define CHAT_ID "*****"
const unsigned long BOT_MTBS = 3000; //Значение задержки Между запросом и обработкой был интервал времени)
X509List cert(TELEGRAM_CERTIFICATE_ROOT); //Сертификат шифрования
UniversalTelegramBot bot(BOT_TOKEN, secured_client); //Объект бота(Бот токен, объект подключения к интернету)
unsigned long bot_lasttime; //Время с последнего момента опроса телеграма(по факту, чтобы не пользоваться дилеем)

String strData = "";

// Обьявление функции подключения к точкt доступа WIFI 
void setup() {
  Serial.begin(9600);
  configTime(0, 0, "pool.ntp.org"); //Синхронизирует время(Обязательно)
  secured_client.setTrustAnchors(&cert);  //Идет работа с сертификатом
  Serial.print("Connecting to WiFi SSID: ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.print("\nWiFi connecred.\nIP address: ");
  Serial.print(WiFi.localIP());
  delay(1000);
  bot.sendMessage(CHAT_ID, "HI! I'm online.", ""); //("", "", ""-МОДИФИКАЦИЯ ПАРСИНГА)
  Serial.println("\nЯ отправиль?(");
}


//Основная функция
void loop() { 
  if(millis() - bot_lasttime > BOT_MTBS){
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  while(numNewMessages){
    handleNewMessages(numNewMessages);
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }       
  if(Serial.available()){
    strData = Serial.readString();
    bot.sendMessage(CHAT_ID, strData, "");
    Serial.print("Send!");
    }
  bot_lasttime = millis();
  }
}


void handleNewMessages(int numNewMessages){
  for(int i = 0; i < numNewMessages; i++){
    if(bot.messages[i].chat_id == CHAT_ID){
      String text = bot.messages[i].text;
      if(text == "/ip"){
        Serial.print("/ip");
        bot.sendMessage(CHAT_ID, "u WaNT UP?? fuck u!!!", "");
        }
        else{Serial.print("not ip");}
      }
    }
  }
