

#include <WiFi.h>
#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

//  the servo is attached to
static const int servoPin = 14;

// Define your static IP configuration
IPAddress staticIP(172, 20, 10, 9);  // Set the desired static IP address
IPAddress gateway(172, 20, 10, 1);      // Set your gateway (router) IP address
IPAddress subnet(255, 255, 255, 240);     // Set your subnet mask
IPAddress dns(8, 8, 8, 8);             // Set your DNS server IP address


// network
const char* ssid     = "MILKY";
const char* password = "123456789";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Decode HTTP GET value
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);

  myservo.attach(servoPin);  // attaches the servo on the servoPin to the servo object

  // Set the static IP configuration
  if (WiFi.config(staticIP, gateway, subnet, dns)) {
    Serial.println("Static IP configured successfully");
  } else {
    Serial.println("Static IP configuration failed");
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

             client.println("<!DOCTYPE html>\n");
client.println("<html lang=\"en\">\n");
client.println("<head>\n");
client.println("    <meta charset=\"UTF-8\">\n");
client.println("    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
client.println("    <title>Feeding</title>\n");
client.println("<style>\n");
client.println("    @import url('https://fonts.googleapis.com/css2?family=Poppins:wght@300;400;500;600;700&display=swap');\n");
client.println("    body{\n");
client.println("        box-sizing: border-box;\n");
client.println("    }\n");
client.println("    header{\n");
client.println("        background-color: #FFF39A;\n");
client.println("        box-shadow:  0px 0px 60px #aaa476,\n");
client.println("             0px 0px 30px #FFF39A;\n");
client.println("        border-radius: 20px;\n");
client.println("        text-align: center;\n");
client.println("        padding-top: 5px;\n");
client.println("        padding-bottom: 5px;\n");
client.println("    }\n");
client.println("    h1{\n");
client.println("        font-family: 'Poppins', sans-serif;\n");
client.println("        font-weight: bolder;\n");
client.println("        font-size: 30px;\n");
client.println("    }\n");
client.println("    .open{\n");
client.println("        width: 150px;\n");
client.println("        height: 120px;\n");
client.println("        border-radius: 50%;\n");
client.println("        font-size: 30px;\n");
client.println("        cursor: pointer;\n");
client.println("        background-color: rgb(38, 143, 38);\n");
client.println("        transition: 0.7s;\n");
client.println("        box-shadow: 2px 15px;\n");
client.println("        font-family: 'Poppins', sans-serif;\n");
client.println("        font-weight: bolder;\n");
client.println("        font-size: 30px;\n");
client.println("    }\n");
client.println("    .close{\n");
client.println("        width: 150px;\n");
client.println("        height: 120px;\n");
client.println("        border-radius: 50%;\n");
client.println("        font-size: 30px;\n");
client.println("        cursor: pointer;\n");
client.println("        background-color: rgb(219, 48, 48);\n");
client.println("        transition: 0.7s;\n");
client.println("        box-shadow: 2px 15px;\n");
client.println("        font-family: 'Poppins', sans-serif;\n");
client.println("        font-weight: bolder;\n");
client.println("        font-size: 30px;\n");
client.println("    }\n");
client.println("    .open:hover{\n");
client.println("        background-color: rgb(93, 93, 180);\n");
client.println("        color: white;\n");
client.println("        box-shadow: 1px 15px black;\n");
client.println("    }\n");
client.println("    .close:hover{\n");
client.println("        background-color: rgb(93, 93, 180);\n");
client.println("        color: white;\n");
client.println("        box-shadow: 1px 15px black;\n");
client.println("    }\n");
client.println("    .process{\n");
client.println("        text-align: center;\n");
client.println("        align-items: center;\n");
client.println("        justify-content: space-evenly;\n");
client.println("        background-color: white;\n");
client.println("        border: 1px solid rgb(36, 56, 70);\n");
client.println("        box-shadow:  0px 0px 0px rgb(36, 56, 70),\n");
client.println("             -25px 25px 10px rgb(36, 56, 70);\n");
client.println("        width: 420px;\n");
client.println("        height: 400px;\n");
client.println("        border-radius: 20px;\n");
client.println("        border: 1px solid black;\n");
client.println("    }\n");
client.println("    .processes{\n");
client.println("        display: flex;\n");
client.println("        align-items: center;\n");
client.println("        justify-content: space-evenly;\n");
client.println("        margin-top: 15%;\n");
client.println("    }\n");
client.println("    .status{\n");
client.println("        text-align: center;\n");
client.println("        align-items: center;\n");
client.println("        justify-content: center;\n");
client.println("        background-color: white;\n");
client.println("        border: 1px solid rgb(36, 56, 70);\n");
client.println("        box-shadow:  0px 0px 0px rgb(36, 56, 70),\n");
client.println("             20px 25px 10px rgb(36, 56, 70);\n");
client.println("        width: 420px;\n");
client.println("        height: 400px;\n");
client.println("        border-radius: 20px;\n");
client.println("        border: 1px solid black;\n");
client.println("        margin: 0;\n");
client.println("    }\n");
client.println("    span {\n");
client.println("        font-family: 'Poppins', sans-serif;\n");
client.println("        font-weight: bolder;\n");
client.println("        font-size: 30px;\n");
client.println("        animation: mymove 5s infinite;\n");
client.println("        position: relative;\n");
client.println("    }\n");
client.println("    #span{\n");
client.println("        animation-timing-function: linear;\n");
client.println("    }\n");
client.println("    @keyframes mymove {\n");
client.println("        from {left: -50px;}\n");
client.println("        to {left: 60px;}\n");
client.println("    }\n");
client.println("    content{\n");
client.println("        display: flex;\n");
client.println("        align-items: center;\n");
client.println("        justify-content: center;\n");
client.println("        margin-top: 5%;\n");
client.println("    }\n");
client.println("    button{\n");
client.println("        width: 90px;\n");
client.println("        height: 40px;\n");
client.println("        border-radius: 10px;\n");
client.println("        margin-top: 4%;\n");
client.println("        margin-left: 3%;\n");
client.println("        background-color: #FFF39A;\n");
client.println("        cursor: pointer;\n");
client.println("        font-family: 'Poppins', sans-serif;\n");
client.println("        font-weight: bolder;\n");
client.println("        font-size: 15px;\n");
client.println("        transition: 0.7s;\n");
client.println("    }\n");
client.println("    button:hover{\n");
client.println("        background-color: rgb(76, 76, 187);\n");
client.println("        color: white;\n");
client.println("    }\n");
client.println("    .latest{\n");
client.println("        background-color: #FFF39A;\n");
client.println("        height: 90px;\n");
client.println("        border-radius: 20px;\n");
client.println("        width: 90%;\n");
client.println("        display: flex;\n");
client.println("        text-align: center;\n");
client.println("        align-items: center;\n");
client.println("        justify-content: center;\n");
client.println("        margin-left: 5%;\n");
client.println("        border: 1px solid black;\n");
client.println("        box-shadow: 5px 10px 5px #888888;\n");
client.println("    }\n");
client.println("    @media (max-width: 730px) {\n");
client.println("    content {\n");
client.println("        display: flex;\n");
client.println("        flex-wrap: wrap;\n");
client.println("        justify-content: space-evenly;\n");
client.println("    }\n");
client.println("    .status{\n");
client.println("        margin-top: 5%;\n");
client.println("    }\n");
client.println("    @keyframes mymove {\n");
client.println("        from {left: -40px;}\n");
client.println("        to {left: 40px;}\n");
client.println("    }\n");
client.println("}\n");
client.println("</style>\n");
client.println("    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>\n");
client.println("</head>\n");
client.println("<body>\n");
client.println("    <header>\n");
client.println("        <h1>Chicken Watering</h1>\n");
client.println("    </header>\n");
client.println("    <content>\n");
client.println("        <div class=\"process\">\n");
client.println("            <br>\n");
client.println("            <h1 class=\"title\">Feeding Process</h1>\n");
client.println("            <div class=\"processes\">\n");
client.println("            <input type=\"button\" class=\"open\" id=\"open\" value=\"Open\" onclick=\"servo(180)\">\n");
client.println("            <input type=\"button\" class=\"close\" id=\"close\" value=\"Close\" onclick=\"servo(0)\">\n");
client.println("            </div>\n");
client.println("        </div>\n");
client.println("        <div class=\"status\">\n");
client.println("            <br>\n");
client.println("             <h1>Feeding Status:</h1><br><br><br><br>\n");
client.println("             <div class=\"latest\">\n");
client.println("             <span id=\"span\">Waiting</span>\n");
client.println("            </div>\n");
client.println("        </div>\n");
client.println("    </content>\n");
client.println("    <footer>\n");
client.println("        <button onclick=\"window.history.back()\">Back</button>\n");
client.println("    </footer>\n");
client.println("    <script>\n");
client.println("        $.ajaxSetup({timeout:1000});\n");
client.println("        function servo(pos) {\n");
client.println("          $.get(\"/?value=\" + pos + \"&\");\n");
client.println("          {Connection: close};\n");
client.println("          if(pos == 180){\n");
client.println("            message = \"Palete is Open\"\n");
client.println("          }\n");
client.println("          else{\n");
client.println("            message = \"Palete is closed\"\n");
client.println("          }\n");
client.println("          document.getElementById('span').innerHTML = message;\n");
client.println("        }\n");
client.println("      </script>\n");
client.println("</body>\n");
client.println("</html>");
            
            //GET /?value=180& HTTP/1.1
            if(header.indexOf("GET /?value=")>=0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('&');
              valueString = header.substring(pos1+1, pos2);
              
              //Rotate the servo
              myservo.write(valueString.toInt());
              Serial.println(valueString); 
            }         
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}