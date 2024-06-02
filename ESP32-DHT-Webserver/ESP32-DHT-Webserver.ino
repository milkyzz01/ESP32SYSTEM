#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <DHT.h>
#include <NTPClient.h>
#include <WiFiUdp.h>



String URL = "https://fecarro.com/Capstone/connect.php";

const char *ssid = "MILKY";
const char *password = "123456789";
const char* host = "fecarro.com";
const int httpsPort = 443;

// Define the static IP address, gateway, and subnet
IPAddress staticIP(172, 20, 10, 10);  // Set your desired static IP address
IPAddress gateway(172, 20, 10, 1);    // Set your gateway IP address
IPAddress subnet(255, 255, 255, 240);   // Set your subnet mask
IPAddress dnsServer(8, 8, 8, 8);


int temperature = 0;
int humidity = 0;

WebServer server(80);
DHT dht(26, DHT11);

void handleRoot() {
  char msg[5500];

  snprintf(msg, 5500,
"<!DOCTYPE html>\n"
"    <html lang=\"en\">\n"
"    <head>\n"
"        <meta http-equiv='refresh' content='4'/>\n"
"        <meta charset=\"UTF-8\">\n"
"        <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
"        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
"        <title> Circular Progress Bar </title>  \n"
"        <script src=\"https://cdn.jsdelivr.net/npm/sweetalert2@10\"></script>                            \n"
"    </head>\n"
"\n"
"    <style>\n"
"       \n"
"@import url('https://fonts.googleapis.com/css2?family=Poppins:wght@300;400;500;600;700&display=swap');\n"
"\n"
"*{\n"
"    \n"
"    font-family: 'Poppins', sans-serif;\n"
"}\n"
"body{\n"
"    \n"
"    background: white;\n"
"}\n"
".container{\n"
"    display: flex;\n"
"    width: 420px;\n"
"    padding: 50px 0;\n"
"    border-radius: 8px;\n"
"    background: #fff;\n"
"    border: 1px solid rgb(36, 56, 70);\n"
"    box-shadow:  20px 20px 60px #bebebe,\n"
"             -5px -5px 20px rgb(36, 56, 70);\n"
"    row-gap: 30px;\n"
"    flex-direction: column;\n"
"    align-items: center;\n"
"}\n"
".circular-progress{\n"
"    position: relative;\n"
"    height: 250px;\n"
"    width: 250px;\n"
"    border-radius: 50%%;\n"
"    background: rgb(223,235,20);\n"
"    background: linear-gradient(90deg, rgba(223,235,20,1) 5%%, rgba(217,138,53,1) 25%%, rgba(217,135,53,1) 61%%, rgba(217,212,53,1) 96%%);\n"
"    display: flex;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"}\n"
"\n"
".circular-progress::before{\n"
"    content: \"\";\n"
"    position: absolute;\n"
"    height: 210px;\n"
"    width: 210px;\n"
"    border-radius: 50%%;\n"
"    background-color: #fff;\n"
"}\n"
".progress-value{\n"
"    position: relative;\n"
"    font-size: 40px;\n"
"    font-weight: 600;\n"
"    color: black;\n"
"}\n"
"\n"
".progress-valuee{\n"
"    position: absolute;\n"
"    font-size: 40px;\n"
"    font-weight: 600;\n"
"    color: black;\n"
"}\n"
"\n"
".containerr{\n"
"    display: flex;\n"
"    width: 420px;\n"
"    padding: 50px 0;\n"
"    border-radius: 8px;\n"
"    background: #fff;\n"
"    border: 1px solid rgb(36, 56, 70);\n"
"    box-shadow:  20px 20px 60px #bebebe,\n"
"             -5px -5px 20px rgb(36, 56, 70);\n"
"    row-gap: 30px;\n"
"    flex-direction: column;\n"
"    align-items: center;\n"
"}\n"
".text{\n"
"    font-size: 30px;\n"
"    font-weight: 500;\n"
"    color: #606060;\n"
"}\n"
"\n"
".circular-progresss{\n"
"    position: relative;\n"
"    height: 250px;\n"
"    width: 250px;\n"
"    border-radius: 50%%;\n"
"    background: rgb(223,235,20);\n"
"    background: linear-gradient(90deg, rgba(223,235,20,1) 5%%, rgba(217,138,53,1) 25%%, rgba(217,135,53,1) 61%%, rgba(217,212,53,1) 96%%);\n"
"    display: flex;\n"
"    align-items: center;\n"
"    justify-content: center;\n"
"}\n"
"\n"
".circular-progresss::before{\n"
"    content: \"\";\n"
"    position: absolute;\n"
"    height: 210px;\n"
"    width: 210px;\n"
"    border-radius: 50%%;\n"
"    background-color: #fff;\n"
"}\n"
"\n"
"content{\n"
"    display: flex;\n"
"    align-items: center;\n"
"    justify-content: space-evenly;\n"
"    margin-top: 5%%;\n"
"}\n"
"\n"
"@media (max-width: 730px) {\n"
"    content {\n"
"        display: flex;\n"
"        flex-wrap: wrap;\n"
"        justify-content: space-evenly;\n"
"    }\n"
"\n"
"    .containerr{\n"
"        margin-top: 5%%;\n"
"    }\n"
"\n"
"    .container .containerr{\n"
"        margin-left: 5%%;\n"
"        margin-right: 5%%;\n"
"    }\n"
"}\n"
"\n"
"header h1{\n"
"    background-color: #FFF39A;\n"
"    box-shadow:  0px 0px 60px #aaa476,\n"
"             0px 0px 30px #FFF39A;\n"
"    border-radius: 20px;\n"
"    text-align: center;\n"
"    padding-top: 15px;\n"
"    padding-bottom: 15px;\n"
"    align-items: center;\n"
"}\n"
"button{\n"
"    width: 80px;\n"
"    height:40px;\n"
"    font-size: 20px;\n"
"    margin-top: 3%%;\n"
"    margin-left: 5%%;\n"
"    cursor: pointer;\n"
"    background-color: #FFF39A;\n"
"    transition: 0.6s;\n"
"}\n"
"button:hover{\n"
"    background-color: #cc7524;\n"
"}\n"
"    </style>\n"
"\n"
"\n"
"    <body>\n"
"        <header>\n"
"            <h1>Temperature and Humidity Monitoring</h1>\n"
"        </header>\n"
"        <content>\n"
"        <div class=\"container\">\n"
"            <div class=\"circular-progress\">\n"
"                <div class=\"progress-value\">\n"
"                <span id=\"progress-value\">%.2f</span>\n"
"                <sup class='units'>&deg;C</sup>\n"
"            </div>\n"
"            </div>\n"
"\n"
"            <span class=\"text\">Temperature</span>\n"
"        </div>\n"
"\n"
"        <div class=\"containerr\">\n"
"            <div class=\"circular-progresss\">\n"
"                <div class=\"progress-valuee\">\n"
"                <span id=\"progress-valuee\">%.2f</span>\n"
"                <sup class='units'>&percnt;</sup>\n"
"            </div>\n"
"            </div>\n"
"            <span class=\"text\">Humidity</span>\n"
"        </div>\n"
"        </content>\n"
"\n"
"        <footer>\n"
"            <Button onclick=\"window.history.back()\">Backk</Button>\n"
"        </footer>\n"
"\n"
"        <script>\n"
"            var temp = document.getElementById(\"progress-value\");\n"
"            var hum = document.getElementById(\"progress-valuee\");\n"
"            \n"
"\n"
"            if(temp.textContent <= 32 || hum.textContent >= 75){\n"
"                console.log(\"Alert Activated\");\n"
"                Swal.fire({\n"
"                icon: 'warning',\n"
"                title: 'Warning',\n"
"                text: 'The Temperature or Humidity has been Increasing'\n"
"        })\n"
"            }\n"
"        </script>\n"
"        \n"
"        \n"
"    </body>\n"
"</html>",
           readDHTTemperature(), readDHTHumidity()
          );
  server.send(200, "text/html", msg);
}

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org"); // You can use other NTP servers too.

void setup(void) {

  Serial.begin(115200);
  dht.begin();
  
  WiFi.mode(WIFI_STA);
  WiFi.config(staticIP, gateway, subnet, dnsServer);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("q");
  }

  
  timeClient.begin();
  timeClient.setTimeOffset(0);  // Set your time zone offset (in seconds) here.

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  

  server.begin();
  Serial.println("HTTP server started");
}

unsigned long lastWebpageRefresh = 0;
unsigned long lastPostDataTime = 0;
const unsigned long webpageRefreshInterval = 4000; // 4 seconds
const unsigned long postDataInterval = 180000; // 3 min

void loop(void) {
  
  unsigned long currentMillis = millis();

  // Handle webpage refresh every 4 seconds
  if (currentMillis - lastWebpageRefresh >= webpageRefreshInterval) {
    server.handleClient();
    lastWebpageRefresh = currentMillis; // Reset the timer
  }

  // Handle posting data every 1 minute
  if (currentMillis - lastPostDataTime >= postDataInterval) {
    if (WiFi.status() == WL_CONNECTED) {
    try {
    Load_DHT11_Data();
    HTTPClient http;
    String url = "https://fecarro.com/Capstone/connect.php";
    http.begin(url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String postData = "temperature=" + String(temperature) + "&humidity=" + String(humidity);

    int httpCode = http.POST(postData);
String payload = http.getString();
    Serial.println("Attempting to connect...");
Serial.print("httpCode: ");
Serial.println(httpCode);
timeClient.update();
Serial.println(timeClient.getFormattedTime());
Serial.print("payload: ");
Serial.println(payload);
    if (httpCode == HTTP_CODE_OK) {
    // Successful POST request
    Serial.println("POST request successful");
} else {
    // POST request failed
    Serial.println("POST request failed");
}

} catch (const std::exception& e) {
    Serial.print("Exception: ");
    Serial.println(e.what());
}

    }

    lastPostDataTime = currentMillis; // Reset the timer
  }

}

void Load_DHT11_Data(){
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read");
    temperature = 0;
    humidity = 0;
  }
  Serial.printf("Temperature: %d C\n", temperature);
  Serial.printf("Humidity: %d", humidity);
  
}


float readDHTTemperature() {
  // Sensor readings may also be up to 2 seconds
  // Read temperature as Celsius (the default)
  float temperaturee = dht.readTemperature();
  if (isnan(temperaturee)) {    
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }
  else {
    Serial.println(temperaturee);
    return temperaturee;
  }
}

float readDHTHumidity() {
  // Sensor readings may also be up to 2 seconds
  float humidityy = dht.readHumidity();
  if (isnan(humidityy)) {
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }
  else {
    Serial.println(humidityy);
    return humidityy;
  }
}