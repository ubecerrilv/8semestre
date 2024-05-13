#!/bin/bash
# Verifica que se hayan proporcionado los tres argumentos necesarios
if [ "$#" -ne 3 ]; then
    echo "Uso: $0 <archivo_de_texto> <video_original.mp4> <archivo_recuperado.txt>"
    exit 1
fi

# Asigna los argumentos a variables
TEXTO_ORIGINAL=$1
ARCHIVO_ORIGINAL=$2
TEXTO_RECUPERADO=$3

# Convierte el archivo de texto a hexadecimal
xxd -p $TEXTO_ORIGINAL > temp_hex.txt

# Construye el nombre del archivo modificado
ARCHIVO_MODIFICADO="${ARCHIVO_ORIGINAL%.*}_modificado.${ARCHIVO_ORIGINAL##*.}"

# Concatena el archivo de texto en formato hexadecimal al final del video
cat $ARCHIVO_ORIGINAL temp_hex.txt > $ARCHIVO_MODIFICADO

# Obtiene el tamaño en bytes del video original
TAMANO_VIDEO_ORIGINAL=$(stat --format=%s $ARCHIVO_ORIGINAL)

# Extrae el contenido oculto del video modificado
dd if=$ARCHIVO_MODIFICADO of=temp_extraido_hex.txt bs=1 skip=$TAMANO_VIDEO_ORIGINAL

# Convierte el contenido hexadecimal extraído de nuevo a texto plano
xxd -r -p temp_extraido_hex.txt $TEXTO_RECUPERADO

# Limpia los archivos temporales
rm temp_hex.txt temp_extraido_hex.txt

echo "Proceso completado. El archivo de texto recuperado se ha guardado en '$ARCHIVO_RECUPERADO'."
