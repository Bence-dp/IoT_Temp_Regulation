## Validator — utilisation de `val.py`

Comment utiliser le script de validation `val.py` fourni dans ce répertoire pour valider des fichiers JSON contre le schéma `schema.json`.

### Pré-requis

- Python 3.x installé
- Le paquet `jsonschema` (installable via pip)

### Structure du dossier

- `val.py` : script de validation
- `schema.json` : schéma JSON (JSON Schema draft 2020-12)
- `examples/` : exemples JSON valides et invalides

### Usage

```bash
python val.py <chemin_vers_fichier_json>
```
Exemple :

```bash
python ./val.py ./examples/jsonExample.json
```

Sorties et codes de retour :

- Code 0 : JSON valide
- Code 1 : JSON invalide ou erreur (fichier non trouvé, JSON invalide, schéma manquant, etc.)

### Que valide le schéma ? (résumé)

Le schéma `schema.json` attend un objet contenant les clés obligatoires : `status`, `location`, `regul`, `info`, `net`, `reporthost`.

- `status` : status matériel (température, luminosité, état des régulations, etc.)
- `location` : informations de localisation (salle, gps, adresse)
- `regul` : seuils `lt` et `ht`
- `info` : métadonnées (ident, user, loc)
- `net` : informations réseau (uptime, ssid, mac, ip)
- `reporthost` : info d'hébergement du rapport (ip, port, sp)

Le schéma utilise des contraintes de type, d'énumération et des plages pour les coordonnées et adresses MAC, ainsi que des règles `additionalProperties: false` pour empêcher des champs non déclarés.

### Exemples fournis

Le dossier `examples/` contient :

- `jsonExample.json` — exemple valide
- `bad/` — répertoire avec plusieurs exemples invalides illustrant différents cas d'erreur

Testez rapidement :

```bash
python ./val.py ./examples/jsonExample.json    # devrait afficher "JSON data is valid."
python ./val.py ./examples/bad/jsonExampleWrong.json  # devrait afficher une erreur
```

### Dépannage rapide

- Si vous voyez `Error: Schema file not found at ./schema.json` : exécutez depuis le dossier `val/` ou fournissez le schéma via une modification du script.

### Remarque importante sur le répertoire de travail

Le script `val.py` charge le schéma avec `./schema.json` (chemin relatif). Par conséquent, il faut exécuter le script depuis le dossier `val/` ou s'assurer que `schema.json` est accessible depuis le répertoire courant.

Se placer dans le dossier `val/` puis lancer :

```bash
cd ./val/
python ./val.py ./examples/jsonExample.json
```
