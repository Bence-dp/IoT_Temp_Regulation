# GR_A - TP - Step 1.5 : JSON and Node_RED

TP `Step 1.5 : JSON and Node_RED` pour l'UE "Software components and services for Internet Of Things" du Master 1 Informatique de l'Université Côte d'Azur.

## Membres du groupe GR_A

- Hugo CLAVEILLE
- Bence DI PLACIDO
- Daniel CARRIBA NOSRATI

## Contenu

- `regul/` Répertoire qui contient les fichiers pour le régulateur (la carte ESP32).
- `val/` Répertoire qui contient un validateur json. Plus d'informations dans `val/README.md`.
- `regul.json` un dashboard Node-RED pour afficher les informations du régulateur ainsi que pour modifier ses réglages.
- `README.md` ce readme.

## Utilisation

### Régulateur (ESP32)

Installez `Arduino IDE` et ouvrez le répertoire `regul/` dans celui-ci. 

Téléchargez les librairies `Adafruit NeoPixel`, `ArduinoJson`, `DallasTemperature` et `One Wire`.

Avec le bouton `Upload` compilez et transférez le programme vers l'ESP32.

### Validateur

Voir `val/README.md`.

### Node-red

Installez `Node-RED` et importez `regul.json`.

Pour les noeuds `serial in` et `serial out` choisissez pour Serial Port le port de votre ESP32, et pour Baud Rate la valeur 9600.

## Fonctionnalités implémentées

### Régulateur (ESP32)

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

### Validator:

- Validateur JSON en python à l'aide de la librairie `jsonschema`
- Fichiers tests (examples)

### Node-RED:

- Dashboard avec plusieurs "Tabs" pour les différentes informations :
    - Infos régulation (temp, luminosité, températures seuil, chauffage, clim, etc.).
    - Infos localisation.
    - Infos diverses.
    - Infos réseau.
- "Tab" Settings pour régler les seuils de température haute et basse, qui seront renvoyés vers l'ESP32. Le seuil de température pour la détection de feu peut également être modifier.
- Une notification "Fire has been detected !" sera affiché si un feu est détecté.
