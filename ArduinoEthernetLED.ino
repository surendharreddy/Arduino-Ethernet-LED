 #include <SPI.h> 
 #include <Ethernet.h> 
 
 byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };    // MAC ID of your Arduino
 byte ip[] = { 169, 254, 72, 67 };                       // The IP address will be dependent on your local network
 EthernetServer server(80); 
 String readString;  

    
    
   void setup()
       { 
       
        pinMode(6, OUTPUT);                           //Arduino Pin selected to control LED 
        Ethernet.begin(mac, ip);                      //Start Ethernet connection and Server
        server.begin();  
        Serial.begin(9600); 
        Serial.println("Arduino smart LED connected"); //To keep on track 
       }   
        
   void loop()
       { 
        EthernetClient client = server.available();  //Listen for the incoming ports
        if (client)                                  //Connects to clinet
        {                                
        while (client.connected()) { 
        if (client.available()) { 
        char c = client.read(); 
        if (readString.length() < 100) {  
        readString += c; 
       } 
    //if HTTP request has ended 
   if (c == '\n') { 
    
    Serial.println(readString);        //Print to serial monitor for debuging 
    client.println("HTTP/1.1 200 OK"); //Send new page 
    client.println("Content-Type: text/html"); 
    client.println(); 
    client.println("<HTML>"); 
    client.println("<HEAD>"); 
    client.println("<TITLE>Arduino Ethernet LEDn</TITLE>"); 
    client.println("</HEAD>"); 
    client.println("<BODY bgcolor='white'>"); 
    client.println("<H1>Arduino smart LED</H1>"); 
    client.println("<hr />"); 
    client.println("<br />"); 
    client.println("<a href=\"/?lighton\"\">Turn On LED</a>"); 
    client.println("<a href=\"/?lightoff\"\">Turn Off LED</a><br />");        
    client.println("</BODY>"); 
    client.println("</HTML>"); 
    
    delay(1); 
    
    //Stoping Client 
    client.stop(); 
    
    //Control Arduino Pin 
    if(readString.indexOf("?lighton") >0) //Checking for ON 
    { 
      digitalWrite(6, HIGH);              // Set Pin 6 to HIGH 
      Serial.println("LED On"); 
    } 
    else{ 
    if(readString.indexOf("?lightoff") >0)//Checking for OFF
    { 
      digitalWrite(6, LOW);               // Set Pin 6 to LOW 
      Serial.println("LED Off"); 
    } 
    } 
    readString="";                        //Clearing string for next read 
            } 
          } 
        } 
      } 
    } 
