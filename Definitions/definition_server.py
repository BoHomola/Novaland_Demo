import json
from flask import Flask, jsonify
from copy import deepcopy

app = Flask(__name__)

def load_definitions():
    with open('NovalandDefinitions.json', 'r') as file:
        return json.load(file)

def process_object(obj, is_client):
    if isinstance(obj, dict):
        new_obj = {}
        for key, value in obj.items():
            if '.client' in key or '.server' in key:
                if (is_client and '.client' in key) or (not is_client and '.server' in key):
                    new_key = key.replace('.client', '').replace('.server', '')
                    new_obj[new_key] = value
            else:
                new_obj[key] = process_object(value, is_client)
        return new_obj
    elif isinstance(obj, list):
        return [process_object(item, is_client) for item in obj]
    else:
        return obj

def process_definitions(definitions, is_client):
    return process_object(definitions, is_client)

@app.route('/get_client_definitions')
def get_client_definitions():
    definitions = load_definitions()
    return jsonify(process_definitions(definitions, is_client=True))

@app.route('/get_server_definitions')
def get_server_definitions():
    definitions = load_definitions()
    return jsonify(process_definitions(definitions, is_client=False))

if __name__ == '__main__':
    app.run(debug=True, port=5555)
