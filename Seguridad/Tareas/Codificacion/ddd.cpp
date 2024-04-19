#include <iostream>
#include <openssl/evp.h>

using namespace std;

string tripleDESEncrypt(string plaintext, string key){

    // Inicializar la biblioteca OpenSSL
    EVP_MD_CTX ctx;
    EVP_CIPHER_CTX enc_ctx;

    // Definir el algoritmo de cifrado
    const EVP_CIPHER *cipher = EVP_get_cipher("des-ede3-cbc");

    // Verificar si se pudo cargar el algoritmo
    if (!cipher){
        cerr << "Error al cargar el algoritmo de cifrado Triple-DES" << endl;
        return "";
    }

    // Configurar el contexto de cifrado
    EVP_CIPHER_CTX_init(&enc_ctx);

    // Establecer el modo de operación (CBC) y el vector de inicialización (IV)
    EVP_CIPHER_CTX_set_iv(&enc_ctx, (unsigned char *)"1234567890123456", 16);

    // Establecer la clave de cifrado
    EVP_CIPHER_CTX_set_key(&enc_ctx, (unsigned char *)key.c_str(), key.size());

    // Configurar el modo de cifrado (encriptación)
    EVP_CIPHER_CTX_set_mode(&enc_ctx, EVP_CIPHER_MODE_CBC);

    // Obtener el tamaño del bloque cifrado
    int block_size = EVP_CIPHER_block_size(cipher);

    // Reservar memoria para el texto cifrado
    size_t padded_plaintext_len = plaintext.size() + block_size - (plaintext.size() % block_size);
    unsigned char *ciphertext = new unsigned char[padded_plaintext_len];
    int ciphertext_len = padded_plaintext_len;

    // Agregar relleno al texto plano
    int pad_len = block_size - (plaintext.size() % block_size);
    for (int i = plaintext.size(); i < padded_plaintext_len; i++){
        ciphertext[i] = pad_len;
    }

    // Cifrar el texto plano
    EVP_EncryptUpdate(&enc_ctx, ciphertext, &ciphertext_len, (unsigned char *)plaintext.c_str(), plaintext.size());

    // Obtener el texto cifrado final
    EVP_EncryptFinal(&enc_ctx, ciphertext + ciphertext_len, &ciphertext_len);

    // Liberar la memoria del contexto de cifrado
    EVP_CIPHER_CTX_cleanup(&enc_ctx);

    // Convertir el texto cifrado a una cadena
    string encrypted_text(ciphertext, ciphertext_len);

    // Eliminar la memoria del texto cifrado
    delete[] ciphertext;

    // Devolver el texto cifrado
    return encrypted_text;
}

int main(){
    string plaintext = "Este es el texto que se cifrará";
    string key = "ClaveSecretaParaTripleDES";

    string encrypted_text = tripleDESEncrypt(plaintext, key);

    cout << "Texto cifrado: " << encrypted_text << endl;

    return 0;
}
