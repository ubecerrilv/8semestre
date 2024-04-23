import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
import cryptography.hazmat.backends as backends


def codificar_archivo(archivo_entrada, archivo_salida, clave,iv):
    """
    Codifica un archivo utilizando el algoritmo Triple DES.

    Args:
    archivo_entrada: Ruta del archivo de entrada.
    archivo_salida: Ruta del archivo de salida.
    clave: Clave de cifrado en formato binario.
    """

    with open(archivo_entrada, 'rb') as entrada:
        datos = entrada.read()

    backend = backends.default_backend()
    cipher = Cipher(algorithms.TripleDES(clave), modes.GCM(os.urandom(12)))
    encriptador = cipher.encryptor()
    datos_cifrados = encriptador.update(datos) + encriptador.finalize()

    with open(archivo_salida, 'wb') as salida:
        salida.write(datos_cifrados)


def decodificar_archivo(archivo_entrada, archivo_salida, clave):
    """
    Decodifica un archivo utilizando el algoritmo Triple DES.

    Args:
    archivo_entrada: Ruta del archivo de entrada cifrado.
    archivo_salida: Ruta del archivo de salida decodificado.
    clave: Clave de cifrado en formato binario.
    """

    with open(archivo_entrada, 'rb') as entrada:
        datos_cifrados = entrada.read()

    cifrado = Cipher(algorithms.TripleDES(clave), modes.CBC(iv))
    desencriptador = cifrado.decryptor()
    datos_decodificados = desencriptador.update(datos_cifrados) + desencriptador.finalize()

    with open(archivo_salida, 'wb') as salida:
        salida.write(datos_decodificados)

archivo_entrada = "poema.txt"
archivo_salida = "poemaddd.txt"

clave = os.urandom(8)
iv = os.urandom(8)

codificar_archivo(archivo_entrada, archivo_salida, clave, iv)

archivo_entrada = "poemaddd.txt"
archivo_salida = "poemaDddd.txt"

decodificar_archivo(archivo_entrada, archivo_salida, clave,iv)
