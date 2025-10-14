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
    
    schema = load_schema("./schema.json")

    if not schema:
        print("Schema is empty.")
        sys.exit(1)
    
    validate_file(json_file, schema)
    
if __name__ == "__main__":
    main()