#include <PZEM004Tv30.h>
#include <ESP8266WiFi.h>
//

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  pinMode(Led_OnBoard, OUTPUT);       // Initialize the Led_OnBoard pin as an output
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

 Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(Led_OnBoard, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(Led_OnBoard, HIGH);
    delay(250);
  }

  digitalWrite(Led_OnBoard, HIGH);
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.println("Connected to Network/SSID");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void loop() {
   float voltage = pzem.voltage();
   if(voltage != NAN){
       Serial.print("Voltage: ");
       Serial.print(voltage);
       Serial.println("V");
   } else {
       Serial.println("Error reading voltage");
   }

   float current = pzem.current();
   if(current != NAN){
       Serial.print("Current: ");
       Serial.print(current);
       Serial.println("A");
   } else {
       Serial.println("Error reading current");
   }

   float power = pzem.power();
   if(current != NAN){
       Serial.print("Power: ");
       Serial.print(power);
       Serial.println("W");
   } else {
       Serial.println("Error reading power");
   }

   float energy = pzem.energy();
   if(current != NAN){
       Serial.print("Energy: ");
       Serial.print(energy,3);
       Serial.println("kWh");
   } else {
       Serial.println("Error reading energy");
   }

   float frequency = pzem.frequency();
   if(current != NAN){
       Serial.print("Frequency: ");
       Serial.print(frequency, 1);
       Serial.println("Hz");
   } else {
       Serial.println("Error reading frequency");
   }

   float pf = pzem.pf();
   if(current != NAN){
       Serial.print("PF: ");
       Serial.println(pf);
   } else {
       Serial.println("Error reading power factor");
   }

  HTTPClient http;    //Declare object of class HTTPClient
 
  String PzemValueSend, postData;
  int pzemvalue=analogRead(A0);  //Read Analog value of LDR
  PzemValueSend = String(pzemvalue);   //String to interger conversion
 
  //Post Data
  postData = "pzemvalue=" + PzemValueSend;
  
  http.begin("http://localhost/PZEM_db_record_view/InsertDB.php");              //Specify request destination
  //http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  //Serial.println("LDR Value=" + ldrvalue);
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  Serial.println("Pzem Value=" + PzemValueSend);
  
  http.end();  //Close connection

  delay(4000);  //Here there is 4 seconds delay plus 1 second delay below, so Post Data at every 5 seconds
  digitalWrite(Led_OnBoard, LOW);
  delay(1000);
  digitalWrite(Led_OnBoard, HIGH);
}
