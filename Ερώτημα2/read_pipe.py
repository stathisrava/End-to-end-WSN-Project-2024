import os
import json  # Ensure the json module is imported
import pymongo
from datetime import datetime

# The name of the named pipe
pipe_name = 'out_pipe'

try:
    # Open the named pipe for reading
    pipe_fd = os.open(pipe_name, os.O_RDONLY)
except OSError as e:
    print(f"Error opening pipe {pipe_name}: {e}")
    exit(1)

# Skip the first line
os.read(pipe_fd, 1024)  # Adjust buffer size as needed

# Connect to the MongoDB database
try:
    client = pymongo.MongoClient('mongodb+srv://stathisrav:stathis2001@cluster0.q5nesqa.mongodb.net/iotdb?retryWrites=true&w=majority')
    db = client['iotdb']
    collection = db['sensor_data']
except pymongo.errors.ConnectionError as e:
    print(f"Error connecting to MongoDB: {e}")
    os.close(pipe_fd)
    exit(1)

try:
    # Read from the named pipe
    while True:
        try:
            # Read a line from the named pipe
            line = os.read(pipe_fd, 1024).decode().strip()
            if not line:
                continue  # Skip empty lines
            
            # Extract the timestamp from the line
            #timestamp_str = line.split('] ')[0].strip('[')
            #timestamp = datetime.strptime(timestamp_str, '%Y-%m-%d %H:%M:%S') 

            # Extract the necessary data
            #sensor_data = line.split(':')[4]  # Extract the part after 4 appearances
            #sensor_values = {}
        
            #for pair in line.split(', '):
            #    key, value = pair.split('=')
            #    sensor_values[key.strip()] = value.strip()
            
            
            
            
            # Separate the timestamp from the rest of the data
            timestamp_str, data_str = line.split('] ', 1)
            timestamp_str = timestamp_str.strip('[')
            timestamp = datetime.strptime(timestamp_str, '%Y-%m-%d %H:%M:%S')

            # Extract the necessary data
            #sensor_values = {}
            #for pair in data_str.split(', '):
            #    key, value = pair.split('=')
            #    sensor_values[key.strip()] = value.strip()
                
            sensor_values = {}
            for pair in data_str.split(', '):
                if '=' in pair:
                    key, value = pair.split('=', 1)
                    sensor_values[key.strip()] = value.strip()
                else:
                    print(f"Skipping malformed pair: {pair}")    
                
                
                
            # Convert numeric values to integers or floats
            sensor_values['Count'] = int(sensor_values['Count'])
            sensor_values['Temp'] = float(sensor_values['Temp'])
            sensor_values['Hum'] = float(sensor_values['Hum'])
		
    
	    # Add the timestamp to the sensor values
            sensor_values['timestamp'] = timestamp
            
            # Print the extracted data
            #print(f"Parsed timestamp: {timestamp}")
            print(f"Data to be inserted into MongoDB: {sensor_values}")
            
            # Insert the data into the MongoDB database
            collection.insert_one(sensor_values)
        
        except Exception as e:
            print(f"Error processing data: {e}")
except KeyboardInterrupt:
    print("Terminating script...")

# Close the named pipe
os.close(pipe_fd)
# Close the MongoDB connection
client.close()


"""
import os
import json  # Ensure the json module is imported
import pymongo
from datetime import datetime

# The name of the named pipe
pipe_name = 'out_pipe'

try:
    # Open the named pipe for reading
    pipe_fd = os.open(pipe_name, os.O_RDONLY)
except OSError as e:
    print(f"Error opening pipe {pipe_name}: {e}")
    exit(1)

# Skip the first line
os.read(pipe_fd, 1024)  # Adjust buffer size as needed

# Connect to the MongoDB database
try:
    client = pymongo.MongoClient('mongodb+srv://stathisrav:stathis2001@cluster0.q5nesqa.mongodb.net/iotdb?retryWrites=true&w=majority')
    db = client['iotdb']
    collection = db['sensor_data']
except pymongo.errors.ConnectionError as e:
    print(f"Error connecting to MongoDB: {e}")
    os.close(pipe_fd)
    exit(1)

try:
    # Read from the named pipe
    while True:
        try:
            # Read a line from the named pipe
            line = os.read(pipe_fd, 1024).decode().strip()
            if not line:
                continue  # Skip empty lines
            
            # Extract the timestamp from the line
            timestamp_str = line.split('] ')[0].strip('[')
            timestamp = datetime.strptime(timestamp_str, '%Y-%m-%d %H:%M:%S') 

            # Extract the necessary data
            sensor_data = line.split(':')[4]  # Extract the part after 4 appearances
            sensor_values = {}
        
            for pair in sensor_data.split(', '):
                key, value = pair.split('=')
                sensor_values[key.strip()] = value.strip()
                
            # Convert numeric values to integers or floats
            sensor_values['Count'] = int(sensor_values['Count'])
            sensor_values['Temp'] = float(sensor_values['Temp'])
            sensor_values['Hum'] = float(sensor_values['Hum'])
		
    
	    # Add the timestamp to the sensor values
            sensor_values['timestamp'] = timestamp
            
            # Print the extracted data
            #print(f"Parsed timestamp: {timestamp}")
            print(f"Data to be inserted into MongoDB: {sensor_values}")
            
            # Insert the data into the MongoDB database
            collection.insert_one(sensor_values)
        
        except Exception as e:
            print(f"Error processing data: {e}")
except KeyboardInterrupt:
    print("Terminating script...")

# Close the named pipe
os.close(pipe_fd)
# Close the MongoDB connection
client.close()
"""


"""
import os
import json  # Ensure the json module is imported
import pymongo

# The name of the named pipe
pipe_name = 'out_pipe'

try:
    # Open the named pipe for reading
    pipe_fd = os.open(pipe_name, os.O_RDONLY)
except OSError as e:
    print(f"Error opening pipe {pipe_name}: {e}")
    exit(1)


# Skip the first line
os.read(pipe_fd, 1024)  # Adjust buffer size as needed


# Connect to the MongoDB database
try:
    client = pymongo.MongoClient('mongodb+srv://stathisrav:stathis2001@cluster0.q5nesqa.mongodb.net/iotdb?retryWrites=true&w=majority')
    db = client['iotdb']
    collection = db['sensor_data']
except pymongo.errors.ConnectionError as e:
    print(f"Error connecting to MongoDB: {e}")
    os.close(pipe_fd)
    exit(1)

try:
    # Read from the named pipe
    while True:
        try:
            # Read a line from the named pipe
            line = os.read(pipe_fd, 1024).decode().strip()
            if not line:
                continue  # Skip empty lines
            
            # Extract the necessary data
            sensor_data = line.split(':')[4]  # Extract the part after 4 appearances
            sensor_values = {}
            
        
            for pair in sensor_data.split(', '):
                key, value = pair.split('=')
                sensor_values[key.strip()] = value.strip()
            
            # Print the extracted data
            print(f"Data to be inserted into MongoDB: {sensor_values}")
            
            # Insert the data into the MongoDB database
            collection.insert_one(sensor_values)
        
        except Exception as e:
            print(f"Error processing data: {e}")
except KeyboardInterrupt:
    print("Terminating script...")

# Close the named pipe
os.close(pipe_fd)
# Close the MongoDB connection
client.close()
"""


"""
import os
import json  # Ensure the json module is imported
import pymongo

# The name of the named pipe
pipe_name = 'out_pipe'

try:
    # Open the named pipe for reading
    pipe_fd = os.open(pipe_name, os.O_RDONLY)
except OSError as e:
    print(f"Error opening pipe {pipe_name}: {e}")
    exit(1)

# Connect to the MongoDB database
try:
    client = pymongo.MongoClient('mongodb+srv://stathisrav:stathis2001@cluster0.q5nesqa.mongodb.net/iotdb?retryWrites=true&w=majority')
    db = client['iotdb']
    collection = db['sensor_data']
except pymongo.errors.ConnectionError as e:
    print(f"Error connecting to MongoDB: {e}")
    os.close(pipe_fd)
    exit(1)

try:
    # Read from the named pipe
    while True:
        try:
            # Read a line from the named pipe
            line = os.read(pipe_fd, 1024).decode().strip()
            if not line:
                continue  # Skip empty lines
            
            
             # Attempt to parse the line as JSON
            try:
                data = json.loads(line)
            except json.JSONDecodeError:
                print(f"Skipping line: {line}")
                continue
            
            # Extract the necessary data
            timestamp = data.get('timestamp')
            sensor_id = data.get('ID')  # Use sensor_id instead of id to avoid shadowing built-in id function
            count = data.get('Count')
            temp = data.get('Temp')
            humidity = data.get('Hum')
            
            # Print the extracted data
            print(f"Data to be inserted into MongoDB: {data}")
            
            # Insert the data into the MongoDB database
            collection.insert_one({'timestamp': timestamp, 
            'ID': sensor_id, 'Count': Count, 'Temp': Temp, 'Hum': hum})
        
        except json.JSONDecodeError as e:
            print(f"Error decoding JSON: {e}")
        except KeyError as e:
            print(f"Missing key in data: {e}")
        except pymongo.errors.PyMongoError as e:
            print(f"Error inserting into MongoDB: {e}")
except KeyboardInterrupt:
    print("Terminating script...")

# Close the named pipe
os.close(pipe_fd)
# Close the MongoDB connection
client.close()
"""

"""
#----------------------------------------------------------
import os

# Το όνομα του named pipe
pipe_name = 'out_pipe'

# Ανοίγει το named pipe για ανάγνωση
pipe_fd = os.open(pipe_name, os.O_RDONLY)

# Ανάγνωση από το named pipe
while True:
    # Διαβάζει μια γραμμή από το named pipe
    line = os.read(pipe_fd, 1024).decode().strip()

    # Εκτύπωση της γραμμής
    print(line)

# Κλείσιμο του named pipe
os.close(pipe_fd)

#----------------------------------------------------------- 
"""

"""
import os
import pymongo

# The name of the named pipe
pipe_name = 'out_pipe'

# Open the named pipe for reading
pipe_fd = os.open(pipe_name, os.O_RDONLY)

# Connect to the MongoDB database
client = pymongo.MongoClient('mongodb://localhost:27017/')
db = client['iotdb']
collection = db['sensor_data']

# Read from the named pipe
while True:
    # Read a line from the named pipe
    line = os.read(pipe_fd, 1024).decode().strip()

    # Parse the JSON string
    data = json.loads(line)

    # Extract the necessary data
    timestamp = data['timestamp']
    id = data['id']
    count = data['count']
    temp = data['temp']
    humidity = data['humidity']

    # Insert the data into the MongoDB database
    collection.insert_one({'timestamp': timestamp, 'id': id, 'count': count, 'temp': temp, 'humidity': humidity})

# Close the named pipe
os.close(pipe_fd)
"""
