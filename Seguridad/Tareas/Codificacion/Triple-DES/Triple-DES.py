from Crypto.Cipher import DES3
from Crypto.Random import get_random_bytes
import os

def pad(data):
    """Añade padding al dato para que sea múltiplo de 8."""
    return data + (8 - len(data) % 8) * bytes([8 - len(data) % 8])

def unpad(data):
    """Elimina el padding del dato."""
    return data[:-data[-1]]

def encrypt_file(input_file_path, output_file_path, key):
    """Cifra un archivo."""
    try:
        with open(input_file_path, 'rb') as f:
            data = f.read()
        
        cipher = DES3.new(key, DES3.MODE_ECB)
        padded_data = pad(data)
        encrypted_data = cipher.encrypt(padded_data)

        with open(output_file_path, 'wb') as f:
            f.write(encrypted_data)
        print("Archivo cifrado con éxito.")
    except Exception as e:
        print(f"Error al cifrar el archivo: {e}")

def decrypt_file(input_file_path, output_file_path, key):
    """Descifra un archivo."""
    try:
        with open(input_file_path, 'rb') as f:
            data = f.read()
        
        cipher = DES3.new(key, DES3.MODE_ECB)
        decrypted_data = cipher.decrypt(data)
        unpadded_data = unpad(decrypted_data)

        with open(output_file_path, 'wb') as f:
            f.write(unpadded_data)
        print("Archivo descifrado con éxito.")
    except Exception as e:
        print(f"Error al descifrar el archivo: {e}")

def main():
    choice = input("Elige una opción (cifrar/decifrar): ").lower()
    if choice not in ['cifrar', 'decifrar']:
        print("Opción no válida. Debe ser 'cifrar' o 'decifrar'.")
        return
    
    input_file_path = input("Ruta del archivo de entrada: ")
    output_file_path = input("Ruta del archivo de salida: ")
    key = input("Introduce una clave de 24 bytes (por ejemplo, 24 caracteres): ").encode()

    if len(key) != 24:
        print("La clave debe tener 24 bytes.")
        return

    if choice == 'cifrar':
        encrypt_file(input_file_path, output_file_path, key)
    elif choice == 'decifrar':
        decrypt_file(input_file_path, output_file_path, key)

if __name__ == "__main__":
    main()
