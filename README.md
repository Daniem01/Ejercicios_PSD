# 🌐 Programación de Sistemas Distribuidos (PSD)

Repositorio progresivo de ejercicios y prácticas de Programación de Sistemas Distribuidos (UCM). Este espacio sirve como entorno de trabajo y material de estudio para dominar los diferentes paradigmas y tecnologías de comunicación entre procesos.

*(Nota: Este repositorio se encuentra en constante actualización. Se irán añadiendo nuevos ejercicios progresivamente).*

---

## 📂 Índice de Contenidos

El repositorio está estructurado en base a las principales tecnologías de sistemas distribuidos:

### 🔌 1. Sockets
Comunicación a bajo nivel mediante el paso de mensajes utilizando el API de Sockets (TCP/UDP) bajo el estándar POSIX.
*   ✅ **[Numeros](./Sockets/Numeros):** [AÑADE AQUÍ UNA BREVE DESCRIPCIÓN: p.ej. Arquitectura cliente-servidor para el intercambio y procesamiento de números enteros].
*   ⏳ *Más ejercicios en desarrollo...*

### 🛠️ 2. RPC (Remote Procedure Call)
Llamadas a procedimientos remotos para abstraer la comunicación y simular ejecuciones locales en entornos distribuidos.
*   ⏳ *Próximamente...*

### 🕸️ 3. SOAP (Web Services)
Servicios web basados en XML para el intercambio de información estructurada en entornos heterogéneos.
*   ⏳ *Próximamente...*

### 🚀 4. MPI (Message Passing Interface)
Estándar de paso de mensajes diseñado para la computación paralela y de alto rendimiento.
*   ⏳ *Próximamente...*

---

## ⚙️ Tecnologías y Entorno

*   **Lenguajes:** C / C++ *(principalmente)*
*   **Sistema Operativo:** Linux (Fedora / GNOME)
*   **Compilador:** GCC / G++

---

## 🚀 Guía de Uso

Cada carpeta de ejercicio es independiente. Para probar cualquiera de los ejercicios completados, navega a su directorio correspondiente. 

Por ejemplo, para el ejercicio de Sockets:

```bash
# Navegar al directorio del ejercicio
cd Sockets/Numeros

# (Añade aquí tus comandos habituales de compilación, por ejemplo:)
make all

# Ejecutar el servidor y luego el cliente en terminales separadas
./servidor
./cliente