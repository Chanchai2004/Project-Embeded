from pymodbus.client import ModbusTcpClient
import time

def connect(ip_address, port=502):
    client = ModbusTcpClient(ip_address, port=port)
    client.connect()
    return client

def disconnect(client):
    client.close()

def toggle_relay(client, relay):
    # อ่านสถานะของ Relay
    response = client.read_coils(relay, 1)
    if response.isError():
        print(f"Error reading coil {relay}")
        return

    # สลับสถานะ
    new_state = not response.bits[0]
    client.write_coil(relay, new_state)
    print(f"Toggled Relay {relay} to {'ON' if new_state else 'OFF'}")

if __name__ == '__main__':
    try:
        while True:
            ip_address = input("Enter IP address (or 'exit' to quit): ")
            
            if ip_address.lower() == 'exit':
                break
            
            client = connect(ip_address)

            while True:
                relay = input("Enter relay number (0-3) to toggle or 'back' to change IP: ")
                if relay.lower() == 'back':
                    disconnect(client)
                    break
                
                try:
                    relay = int(relay)
                    if relay in [0, 1, 2, 3]:
                        toggle_relay(client, relay)
                    else:
                        print("Invalid relay number. Please enter 0, 1, 2, or 3.")
                except ValueError:
                    print("Please enter a valid number or 'back'.")

    except KeyboardInterrupt:
        print("Program interrupted.")