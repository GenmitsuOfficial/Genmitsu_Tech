

#include <mbedtls/md.h>
#include <WiFi.h>
#include <PubSubClient.h>
//#include <base64.h>

// 

String username;
//String jwt_token ;
String clientId;
String payload ;
String key;
String pub_topic;
String grbl;

//String header = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";
const char* mqtt_broker = "o3089f89.ala.dedicated.aliyun.emqxcloud.cn"; // Get this address from EMQX Cloud Console  
const int mqtt_port = 1883;  // Get this port num from EMQX Cloud Console  


const char* ssid="public@sainFBB";
const char* password="sainM*VFFB";


String mqtt_username="PCHost";
String mqtt_password="20250630";


String mqtt_remote_devicename="device/CNCDevice/data";


 

// For JWT ​​Dynamic Registration, Base64 URL encode
/*
String base64UrlEncode(uint8_t* input, size_t length) {

  String s = base64::encode(input, length);
  s.replace("+", "-");
  s.replace("/", "_");
  s.replace("=", "");
  return s;

}
*/

// For JWT ​​Dynamic Registration, hmacSha256 encode
/*
String hmacSha256(const String& key, const String& data) {

  uint8_t digest[32];
  mbedtls_md_context_t ctx;
  mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 1);
  
  mbedtls_md_hmac_starts(&ctx, (uint8_t*)key.c_str(), key.length());
  mbedtls_md_hmac_update(&ctx, (uint8_t*)data.c_str(), data.length());
  mbedtls_md_hmac_finish(&ctx, digest);
  mbedtls_md_free(&ctx);
  
  // Base64Url编码
  String signature = base64UrlEncode(digest, 32);
  return signature;

}

*/

WiFiClient espClient;
PubSubClient mqttClient(espClient);




// Generate JWT Token
/*String generateJWT(const String& sercet_key,const String& jwt_header ,const String&  jwt_payload){

  // Header
  //String header = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";
  String encodedHeader = base64UrlEncode((uint8_t*)jwt_header.c_str(), jwt_header.length());
  String encodedPayload = base64UrlEncode((uint8_t*)jwt_payload.c_str(), jwt_payload.length());

  // Signature（直接使用原始密钥）
  String signature = hmacSha256(sercet_key, encodedHeader + "." + encodedPayload);

  return encodedHeader + "." + encodedPayload + "." + signature;

}
*/

void reconnect() {
  while (!mqttClient.connected()) {
    //String jwt = generateJWT();
    if (mqttClient.connect(clientId.c_str(),mqtt_username.c_str() , mqtt_password.c_str())) {

      mqttClient.subscribe(mqtt_remote_devicename.c_str());

    } else {

	  
      delay(5000);
    }
  }
}



void callback(char* topic, byte* payload, unsigned int length) {

    for (int i = 0; i < length; i++) {

         Serial2.print((char)payload[i]);  
		 
    }

}

void setup() {

clientId = String(WiFi.macAddress());

pub_topic="device/"+mqtt_username+"/data";
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) delay(500);


//key="genmitsu";
//payload = "{\"username\":\"" + username + "\""
//          ",\"clientid\":\"" + clientId + "\"}";
//jwt_token = generateJWT(key,header,payload);

mqttClient.setServer(mqtt_broker, mqtt_port);
mqttClient.setCallback(callback);
Serial.begin(115200);


}

void loop() {


  if (!mqttClient.connected()) {
    reconnect();
  }

  mqttClient.loop();

    if (Serial.available() > 0) {

     String message = Serial.readStringUntil('\n');
     mqttClient.publish((const char*)pub_topic.c_str(), message.c_str());
	 
    }

}
