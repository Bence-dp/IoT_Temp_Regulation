# GR_A - Projet IOT

Projet pour l'UE "Software components and services for Internet Of Things" du Master 1 Informatique de l'Université Côte d'Azur.

## Membres (3) du groupe GR_A

- Hugo CLAVEILLE
- Bence DI PLACIDO
- Daniel CARRIBA NOSRATI

## Contenu

- `regul/` Répertoire qui contient les fichiers pour le régulateur (la carte ESP32).
- `val/` Répertoire qui contient un validateur json. Plus d'informations dans `val/README.md`.
- `regul.json` un dashboard Node-RED pour afficher les informations du régulateur, pour modifier ses réglages ainsi que pour visualiser la carte des "piscines".
- `README.md` ce readme.

## Utilisation

### Régulateur (ESP32)

Installez `Arduino IDE` et ouvrez le répertoire `regul/` dans celui-ci. 

Téléchargez les librairies `ArduinoHttpClient`, `Adafruit NeoPixel`, `ArduinoJson`, `Async TCP`, `DallasTemperature`, `ESP Async WebServer`, `One Wire` et `PubSubClient`.

Connecter la carte ESP32 avec votre ordinateur et configurer dans `Tools` (ou `Outils`) : `Board: ESP32 Dev Module` et pour `Port` le port USB sur lequel la carte est connecté.

Avec `Control Shift P` selectionner `Upload to LittleFS to Pico/ESP8266/ESP32`, enfin avec le bouton `Upload` compilez et transférez le programme vers l'ESP32.

### Validateur

Un validateur JSON en Python, appelé dans Node-RED pour valider le format des JSON reçus.

Pour plus d'information voir `val/README.md`.

### Node-RED

Installez [Node-RED](https://nodered.org/).

IMPORTANT : assurez-vous de vous situer dans le root du projet avant de lancer Node-RED (important pour le bon fonctionnement du validateur appelé par Node-RED).

```
[...]/IoT_Temp_Regulation $
```

Dans le root du projet lancer Node-RED :

```bash
node-red
```

Importez `regul.json`.

Vous pouvez activer/désactiver les noeuds des groupes `MQTT`, `HTTP` et `Serial` pour changer le protocole utilisé pour récupérer les données de la carte ESP32. 

Pour les noeuds du groupe `MQTT` vous pouvez activer/désactiver ou modifier des noeuds pour changer de broker MQTT.



Pour les noeuds `serial in` et `serial out` choisissez pour Serial Port le port de votre ESP32, et pour Baud Rate la valeur 9600.

## Fonctionnalités implémentées

### Régulateur (ESP32)

#### Step 1.5

- Mesures de températures.
- Mesures de luminosité (Remarque : on mesure 4095 si la luminosité est basse, et 0 si élevée).
- Régulation de température :
    - Chauffage (représenté par la LED rouge).
    - Climatisation (représenté par la LED verte). 
    - Ventilation progressive en fonction de la température.
- Signalisation du seuil de température sur la bande LEDs (3 seuils/couleurs : bas/bleu, normal/vert, chaud/rouge).
- Détection d’incendie si la température moyenne est supérieur au "seuil feu" (35 C par défaut) et si la luminosité est particulièrement élevée (en cas de flammes) ou basse (en cas de fumée sans flammes). En cas d'incendie, la ventilation s'arrête et la LED 2 s'allume.
- Modification d’une structure de données "esp" avec les infos nécessaires.
- Sérialisation en JSON à l'aide d'`ArduinoJson` de Blanchon.
- Envoi du JSON a Node-RED a travers le port USB.

#### Step 2, 3, 4

- Connection au Wifi (wificonnect_multi)
- ESP32 as async webserver littlefs
- "Page HTML Administrateur" (accessible sur http://\<adresse_IP_ESP32\>/) de la carte ESP32 affichant différents infos et permettant à modifier : 
    - l'adresse et port IP pour le reporting HTTP ainsi que la sampling period
    - adresse du broker MQTT, Topic ainsi que la sampling period
- Envoi du JSON au dashboard Node-RED a travers via HTTP.
- Mis-à-jour des seuils de température et de luminosité via les requetes HTTP reçus du Dashboard
- Gestion de l'hotspot

### Validator

- Validateur JSON en python à l'aide de la librairie `jsonschema`
- Fichiers tests (examples)
- Est appelé dans Node-RED pour valider le format des JSON reçus.

### Node-RED

- Dashboard avec plusieurs "Tabs" pour les différentes informations :
    - Infos régulation (temp, luminosité, températures seuil, chauffage, clim, etc.).
    - Infos localisation.
    - Infos diverses.
    - Infos réseau.
- "Tab" `Settings` pour régler les seuils de température haute et basse, qui seront renvoyés vers l'ESP32 (via HTTP). Le seuil de température pour la détection de feu peut également être modifier. 
- Une notification "Fire has been detected !" est affiché lorsqu'un feu est détecté.
- "Tab" `Tab of Swimming Pools` affichant tout les ESP32s et l'hotspot

