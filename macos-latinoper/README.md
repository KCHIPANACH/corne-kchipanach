# Distribución de teclado "LatinoPer" (macOS)

Distribución de teclado personalizada para macOS, basada en Latinoamérica. El
firmware del Corne manda códigos US/ANSI y **macOS los traduce al español con
esta distribución** (por eso la ñ sale en su tecla, los acentos y los símbolos
quedan en su lugar).

Esta carpeta incluye dos archivos que van juntos:

- `LatinoPer.keylayout` — la distribución.
- `LatinoPer.icns` — el icono que aparece en la barra de menú.

## Cómo instalarla

1. Copia **ambos** archivos (`LatinoPer.keylayout` y `LatinoPer.icns`) a una de
   estas carpetas:
   - **Solo tu usuario:** `~/Library/Keyboard Layouts/`
   - **Todos los usuarios** (pide permiso de administrador): `/Library/Keyboard Layouts/`

   Si la carpeta no existe, créala.

2. Cierra sesión y vuelve a entrar (o reinicia la Mac) para que macOS la detecte.

3. Actívala en **Ajustes del Sistema → Teclado → Fuentes de entrada**
   (Text Input → Input Sources) → botón **+** o **Editar** → busca **"LatinoPer"**
   → **Agregar**.

4. Selecciónala como distribución activa desde el selector de teclado de la
   barra de menú.

> Sin esta distribución activa, varias teclas (incluida la **ñ** y algunos
> símbolos) saldrán distintas, porque el firmware asume que macOS traduce con
> este layout.
