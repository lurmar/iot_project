import ollama

client = ollama.Client()
model = "deepseek-ri:1.5b"
prompt = "Generame una tabla de los comandos mas utiles de macos"

print("Respuesta del modelo:")
for chunk in client.generate(model=model, prompt=prompt, stream=True): #Para que vaya mandando trocitos como si fuese una IA
    print(chunk.response, end="", flush=True)
print()  #salto de línea al final