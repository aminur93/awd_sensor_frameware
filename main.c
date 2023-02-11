#include <stdio.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

int main(void) {
    printf("Hello world");
}

void loop(){

    if(WiFi.status() == WL_CONNECTED)
    {
        long rand = random(1, 10);
        HTTPClient client;

        client.begin("https://jsonplaceholder.typicode.com/comments?postId=" + String(rand));
        int httpCode = client.GET();

        if(httpCode > 0)
        {
            String payload = client.getString();
            serial.println("\nStatuscode: " + String(httpCode));
            serial.println(payload);

            char json[500];
            payload.replace(" ", "");
            payload.replace("\n", "");
            payload.trim();
            payload.remove(0,1);
            payload.toCharArray(json, 500);

            StaticJsonDocument<200> doc;
            deserializeJson(doc, json);

            int id = doc["id"];
            int total_duration = doc["total_duration"];
            const char *email = doc["email"];

            Serial.println(String(id) + " - " + String(email) + "\n");
        }else{
            Serial.println("Error on http request");
        }
    }else{

        Serial.println("Connection lost");
    }

    delay(10000);
}

void loop(){

    if(WiFi.status() == WL_CONNECTED)
    {

        HTTPClient client;

        client.begin("https://jsonplaceholder.typicode.com/posts");
        client.addHeader("Content-Type", "application/json");

        const size_t CAPACITY = JSON_OBJECT_SIZE(1);
        StaticJsonDocument<CAPACITY> doc;

        JsonObject object = doc.to<JsonObject>();
        object['pump_status'] = 0;

        serializeJson(doc, JsonOutput);

        int httpCode = client.POST(String(JsonOutput));

        if(httpCode > 0)
        {
            String.payload = client.getString();
            Serial.println("\nStatuscode: " + String(httpCode));
            Serial.println(payload);

            client.end();
        }else{

            Serial.println("Error on http request");
        }

    }else{
        Serial.println("Connection lost");
    }

}
