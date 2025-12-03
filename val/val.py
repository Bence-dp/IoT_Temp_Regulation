import json
from jsonschema import validate, ValidationError
import sys

def load_schema(schema_path: str) -> dict:
    """Load JSON schema from a file."""
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
    """Load JSON data from a file."""
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
    """Validate JSON data against a schema."""
    try:
        validate(data, schema)
        print("JSON data is valid.")
    except ValidationError as e:
        print("JSON data is invalid.")
        print(e.message)
        sys.exit(1)

def validate_file(file, schema):
    """Validate a JSON file against a schema."""
    data = load_json(file)
    validate_json(data, schema)

def check_duplicate_keys(file_path: str):
    """Check for duplicate keys in a JSON file."""
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()
            pairs = []
            def object_pairs_hook(pairs_list):
                keys = [key for key, _ in pairs_list]
                if len(keys) != len(set(keys)):
                    raise ValueError("Duplicate keys found in JSON.")
                return dict(pairs_list)
            json.loads(content, object_pairs_hook=object_pairs_hook)
    except ValueError as e:
        print(f"Error: {e}")
        sys.exit(1)
    except Exception as e:
        print(f"Error: Unexpected error checking duplicate keys - {e}")
        sys.exit(1)

def main():
    """Main function to handle command line arguments and initiate validation."""
    if len(sys.argv) < 2:
        print("Usage: python validator.py <json_file>")
        print("Example: python validator.py examples/jsonExample.json")
        sys.exit(1)
    elif len(sys.argv) > 2:
        print("Error: Too many arguments provided.")
        print("Usage: python validator.py <json_file>")
        sys.exit(1)
    json_file = sys.argv[1]
    
    # check current directory first, then val/ directory
    schema_file = "./schema.json"
    try:
        import os
        if not os.path.isfile(schema_file):
            schema_file = "./val/schema.json"
            if not os.path.isfile(schema_file):
                print("Error: Schema file not found.")
                sys.exit(1)
    except Exception as e:
        print(f"Error: Unexpected error locating schema file - {e}")
        # sys.exit(1)
    
    schema = load_schema(schema_file)

    if not schema:
        print("Schema is empty.")
        sys.exit(1)
    
    check_duplicate_keys(json_file)
    validate_file(json_file, schema)
    
if __name__ == "__main__":
    main()