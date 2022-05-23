#include <SPI.h>
#include <Ethernet.h>
//Mac ADRESS - Só alterar se for necessário
by mac[] = {
    0xDe, 0xAD, 0xBE, 0xEF, 0xED
};

IPAddress ip(192,168,0,107); //Define o IP que o arduíno irá usar.

EthernetServer server(80);

int pinLed1 = 3;

int led = 0;
String msg = "LED DESLIGADO";

void setup(){
    Serial.begin(9600);
    while(!Serial){
        ;
    }
    
    pinMode(pinLed1, OUTPUT);
    digitalwrite(pinLed1, LOW);
    
    Ethernet.begin(mac, ip);
    server.begin();
    Serial.print("Server is at ");
    Serial.println(Ethernet.localIP());
}

void loop() {
    Ethernetclient client = server.available();
        if(client){
            Serial.println("New client");
            
            boolean currentLineIsBlank = true;
            
            String DatEth;
            
            while (client.connected()){
                if(client.available()){
                    
                    char c= client.read();
                    Serial.write(c);

                    DatEth.concat(c);
                    if(DatEth.endsWith("/ledon")) {led= 1; msg "LED LIGADO";}
                    if(DatEth.endsWith("/ledof")) {led 0; msg "LED DESLIGADO";}
                                                   
                    if(c== '\n' && currentLineIsBlank){
                    /**********  código HTML ************/
                        client.println("<!DOCTYPE html>");
                        client.println("<html lang="pt-br\">");
                        client.println("<head>");
                        client.println("<title>Projeto V1.0</title>");
                        client.println("<meta http-equiv="refresh" content=\"21" charset=\"UTF-8\">");
                        client.println("</head>");
                        client.println("<body style="background-color: #DDD;\">");
                        client.println("<br>");
                        client.println("<form align=\"center\">");
                        client.println("<label style=\"font-size: 18pt;\">" msg+"</label>");
                        client.println("<br>");
                        client.println("<br>");
                        client.println("<button type=\"submit\" formaction="ledon\">Ligar</button>");//Button
                        client.println("<button type-\"submit\" formaction="ledof\">Desligar</button>");//But
                        client.println("</form>");
                        client.println("<br>");
                        client.println("</body>");
                        client.println("</html>");
                    /**********  código HTML ************/
                        
                    /**********  LED ************/
                        if(led == 1){
                            digitalWrite(pinLed1, HIGH);
                        }
                        
                        if(led == 0){
                            digitalWrite(pinLed1, LOW);
                        }
                        
                        break;
                    }
                        
                    if(c == '\n'){
                            currentLineIsBlank = true;
                    }
                    else if(c != '\r'){
                        currentLineIsBlank = false;
                    }

                }
            
            }
            
            delay(1);
            
            client.stop();
            Serial.println("Client disconnected");
            
        }
}

