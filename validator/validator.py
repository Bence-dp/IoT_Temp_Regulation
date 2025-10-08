import json
# import jsonschema
from jsonschema import validate, ValidationError
import sys



if __name__ == "__main__":
    with open("schema.json") as f:
        schema = json.load(f)

    if not schema:
        print("Schema is empty.")
        sys.exit(1)
    
    if len(sys.argv) < 2:
        print("Usage: python validator.py <json_file>")
        sys.exit(1)
    json_file = sys.argv[1]

    with open(json_file) as f:
        data = json.load(f)

    try:
        validate(data, schema)
        print("JSON data is valid.")
    except ValidationError as e:
        print("JSON data is invalid.")
        print(e.message)
