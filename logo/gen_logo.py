from PIL import Image

SRC = "boost_oled_128x32.png"
img = Image.open(SRC).convert("L")
W, H = img.size
assert (W, H) == (128, 32), f"Se esperaba 128x32, llego {W}x{H}"

# Umbral: pixel encendido si es claro (wordmark blanco sobre negro)
px = img.load()
def on(x, y):
    return 1 if px[x, y] >= 128 else 0

# Formato pagina SSD1306, orientacion NATIVA del panel (128 ancho x 32 alto, 4 paginas).
# indice = page*128 + x ; bit = y % 8 (LSB = fila superior de la pagina)
pages = H // 8  # 4
data = []
for page in range(pages):
    for x in range(W):
        b = 0
        for bit in range(8):
            y = page * 8 + bit
            if on(x, y):
                b |= (1 << bit)
        data.append(b)
assert len(data) == 512, len(data)

# --- Escribir boost_logo.h ---
lines = []
lines.append("// boost_logo.h - generado automaticamente desde boost_oled_128x32.png")
lines.append("// Formato: framebuffer NATIVO SSD1306 128x32 (4 paginas), listo para oled_write_raw_P.")
lines.append("// El OLED del Corne va montado en PORTRAIT; oled_write_raw escribe en orientacion")
lines.append("// nativa (NO aplica la rotacion de texto). Si en hardware se ve rotado, regenerar")
lines.append("// el PNG con rotacion 90/180 y volver a correr gen_logo.py.")
lines.append("#pragma once")
lines.append("")
lines.append("static const char PROGMEM boost_logo[] = {")
for i in range(0, 512, 16):
    chunk = data[i:i+16]
    lines.append("    " + ", ".join("0x%02X" % b for b in chunk) + ",")
lines.append("};")
hdr = "\n".join(lines) + "\n"
with open("boost_logo.h", "w") as f:
    f.write(hdr)

# --- Previsualizacion: reconstruir EXACTAMENTE el framebuffer enviado al panel ---
sim = Image.new("L", (W, H), 0)
sp = sim.load()
for page in range(pages):
    for x in range(W):
        b = data[page * 128 + x]
        for bit in range(8):
            if b & (1 << bit):
                sp[x, page * 8 + bit] = 255
sim = sim.resize((W * 8, H * 8), Image.NEAREST)
sim.save("slave_oled_sim.png")
print("OK: boost_logo.h (%d bytes de datos), slave_oled_sim.png generados" % len(data))
