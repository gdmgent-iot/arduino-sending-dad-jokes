# Connect to WiFi met Arduino (WiFiNINA)

Deze repository bevat voorbeeldcode om een Arduino (met WiFiNINA-compatibele module) te verbinden met een WiFi-netwerk.

## Benodigdheden

- Arduino board met WiFiNINA-ondersteuning (vb Arduino Uno WiFi Rev2)
- Arduino IDE
- WiFiNINA library
- Bestand `secrets.h` met je WiFi-gegevens

## `secrets.h` 

Dit bestand moet je zelf aanmaken in dezelfde map als je Arduino sketch. Je kan de inhoud uit secrets.h.example kopiëren en je eigen WiFi-naam en wachtwoord invullen.

```cpp
#ifndef SECRETS_H
#define SECRETS_H

const char* WIFI_SSID = "jouw_wifi_naam";
const char* WIFI_PASSWORD = "jouw_wifi_wachtwoord";

#endif
```


#ifndef SECRETS_H
#define SECRETS_H

const char* WIFI_SSID = "VUL_IN";
const char* WIFI_PASSWORD = "VUL_IN";

#endif

## Gebruik

1. Voeg je WiFi-gegevens toe aan `secrets.h`.
2. Upload de code naar je Arduino.
3. Open de seriële monitor om de verbindingsstatus te zien.

## Wat doet de code?

- Probeert maximaal 5 keer te verbinden met het opgegeven WiFi-netwerk.
- Print het IP-adres bij succesvolle verbinding.
- Probeert automatisch opnieuw te verbinden als de verbinding wegvalt.

## Opmerking

Zorg dat je de juiste WiFiNINA library hebt geïnstalleerd via de Library Manager in de Arduino IDE.
