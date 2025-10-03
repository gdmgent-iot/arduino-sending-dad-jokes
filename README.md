# Connect to WiFi en Verstuur Dad Jokes met Arduino (WiFiNINA)

Deze repository bevat voorbeeldcode om een Arduino (met WiFiNINA-compatibele module) te verbinden met een WiFi-netwerk, een dad joke op te halen via een API en deze via het netwerk te versturen naar een andere Arduino.

## Benodigdheden

- Arduino board met WiFiNINA-ondersteuning (vb Arduino Uno WiFi Rev2)
- Arduino IDE
- WiFiNINA library
- ArduinoHttpClient library
- Arduino_JSON library
- Bestand `secrets.h` met je WiFi-gegevens

## `secrets.h` 

Maak dit bestand aan in dezelfde map als je Arduino sketch. Kopieer de inhoud uit `secrets.h.example` en vul je eigen WiFi-naam en wachtwoord in.

```cpp
#ifndef SECRETS_H
#define SECRETS_H

const char* WIFI_SSID = "jouw_wifi_naam";
const char* WIFI_PASSWORD = "jouw_wifi_wachtwoord";

#endif
```

## Gebruik

1. Voeg je WiFi-gegevens toe aan `secrets.h`.
2. Upload de code naar je Arduino.
3. Open de seriële monitor om de verbindingsstatus en ontvangen/verzonden grappen te zien.

## Wat doet de code?

- Verbindt met het opgegeven WiFi-netwerk (maximaal 5 pogingen).
- Start een TCP-server op poort 5000.
- Haalt elke 10 seconden een random dad joke op via de [Official Joke API](https://official-joke-api.appspot.com/jokes/random).
- Stuurt de opgehaalde grap automatisch door naar een andere Arduino in het netwerk.
- Ontvangt berichten van andere Arduino’s en toont deze in de seriële monitor.
- Probeert opnieuw te verbinden als de WiFi-verbinding wegvalt.

## Opmerking

Zorg dat je de juiste WiFiNINA, ArduinoHttpClient en Arduino_JSON libraries hebt geïnstalleerd via de Library Manager in de Arduino IDE.

