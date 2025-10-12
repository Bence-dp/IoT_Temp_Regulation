import json
# import jsonschema
from jsonschema import validate, ValidationError
import sys

def load_schema(schema_path: str) -> dict:
    try:
        with open(schema_path, 'r', encoding='utf-8') as file:
            return json.load(file)
    except FileNotFoundError:
        print(f"Error: Schema file not found at {schema_path}")
        sys.exit(1)
    except json.JSONDecodeError as e:
        print(f"Error: Invalid JSON in schema file - {e}")
        sys.exit(1)
    except Exception as e:
        print(f"Error: Unexpected error reading schema file - {e}")
        sys.exit(1)
    
def load_json(json_path: str) -> dict:
    try:
        with open(json_path, 'r', encoding='utf-8') as file:
            return json.load(file)
    except FileNotFoundError:
        print(f"Error: JSON file not found at {json_path}")
        sys.exit(1)
    except json.JSONDecodeError as e:
        print(f"Error: Invalid JSON in file - {e}")
        sys.exit(1)
    except Exception as e:
        print(f"Error: Unexpected error reading JSON file - {e}")
        sys.exit(1)


def validate_json(data: dict, schema: dict):
    try:
        validate(data, schema)
        print("JSON data is valid.")
    except ValidationError as e:
        print("JSON data is invalid.")
        print(e.message)
        sys.exit(1)

def main():
    if len(sys.argv) < 2:
        print("Usage: python validator.py <json_file>")
        print("Example: python validator.py examples/jsonExample.json")
        sys.exit(1)
    elif len(sys.argv) > 2:
        print("Error: Too many arguments provided.")
        print("Usage: python validator.py <json_file>")
        sys.exit(1)
    json_file = sys.argv[1]
    
    schema = load_schema("./schema.json")

    if not schema:
        print("Schema is empty.")
        sys.exit(1)
    
    data = load_json(json_file)

    validate_json(data, schema)

if __name__ == "__main__":
    main()



"""
import json
# import jsonschema
from jsonschema import validate, ValidationError
import sys
import os


if __name__ == "__main__":
    # Get the directory of the current script for robust file path handling
    script_dir = os.path.dirname(os.path.abspath(__file__))
    schema_path = os.path.join(script_dir, "schema.json")
    
    # Load schema with robust error handling
    try:
        with open(schema_path, 'r', encoding='utf-8') as file:
            schema = json.load(file)
    except FileNotFoundError:
        print(f"Error: Schema file not found at {schema_path}")
        sys.exit(1)
    except json.JSONDecodeError as e:
        print(f"Error: Invalid JSON in schema file - {e}")
        sys.exit(1)
    except Exception as e:
        print(f"Error: Unexpected error reading schema file - {e}")
        sys.exit(1)
    

    if not schema:
        print("Error: Schema is empty.")
        sys.exit(1)
    
    # Check command line arguments
    if len(sys.argv) < 2:
        print("Usage: python validator.py <json_file>")
        print("Example: python validator.py examples/jsonExample.json")
        sys.exit(1)
    
    json_file = sys.argv[1]
    
    # Check if input file exists
    if not os.path.exists(json_file):
        print(f"Error: Input file '{json_file}' not found.")
        sys.exit(1)

    # Load and validate input JSON with robust error handling
    try:
        with open(json_file, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except json.JSONDecodeError as e:
        print(f"Error: Invalid JSON in input file '{json_file}'")
        print(f"JSON decode error: {e}")
        print(f"Error at line {e.lineno}, column {e.colno}")
        sys.exit(1)
    except FileNotFoundError:
        print(f"Error: Input file '{json_file}' not found.")
        sys.exit(1)
    except Exception as e:
        print(f"Error: Unexpected error reading input file - {e}")
        sys.exit(1)

    # Validate JSON against schema
    try:
        validate(data, schema)
        print(f"✅ JSON data in '{json_file}' is valid according to the schema.")
    except ValidationError as e:
        print(f"❌ JSON data in '{json_file}' is invalid.")
        print(f"Validation error: {e.message}")
        if e.absolute_path:
            print(f"Path to error: {' -> '.join(str(p) for p in e.absolute_path)}")
        sys.exit(1)
    except Exception as e:
        print(f"Error: Unexpected error during validation - {e}")
        sys.exit(1)
"""