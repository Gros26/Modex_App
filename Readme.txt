=====================================================================
 PROYECTO ModEx - Moderando el extremismo de opiniones en una red social
 Analisis y Diseno de Algoritmos II - Universidad del Valle
=====================================================================

Integrantes: [Grosman Klein García Valencia - 202340247]
Fecha: [12 Noviembre 2026]


1. CONTENIDO DEL PAQUETE
------------------------
[Garcia]/
  exe/Modex.app          Aplicacion ya compilada, SOLO para macOS.
  src/                   Codigo fuente completo (C++ / Qt / CMake).
    CMakeLists.txt       Archivo de proyecto (abrir este en Qt Creator).
    modex.h              Estructuras (Agent, Network, ModexResult) y
                         declaracion de effort, ext, modexFB, modexV, modexPD.
    [ModexFB].cpp        modexFB  (fuerza bruta)
    [ModexV].cpp         modexV   (voraz)
    [ModexPD].cpp        modexPD  (programacion dinamica)
    [archivos de la interfaz: main.cpp, mainwindow.*, etc.]
  test_cases/                 Casos de prueba: archivos .txt (entrada)
  Informe.pdf            Informe del proyecto.
  Sustentacion.txt       Link al video explicativo del codigo
  Readme.txt             Este archivo.


2. EJECUTAR EN macOS
--------------------
1. Abrir la carpeta exe/ y hacer doble clic en Modex.app.
2. Si macOS indica que la app "proviene de un desarrollador no identificado",
   hacer clic derecho sobre Modex.app > Abrir > Abrir.
   (Es normal: la app no esta firmada por Apple.)
3. La aplicacion trae incluidas las librerias de Qt; no necesita instalar nada.

Probada con: Qt 6.12.0 para macOS.


3. EJECUTAR EN WINDOWS (compilando desde el codigo fuente)
----------------------------------------------------------
La aplicacion incluida (Modex.app) NO funciona en Windows. Para usarla en
Windows hay que compilar el codigo fuente de la carpeta src/. El codigo es
portable (C++17 + Qt + CMake).

3.1 Requisitos
  - Qt 6.12.0 (o una version 6.x reciente) para Windows, incluyendo:
      * el componente "MinGW 64-bit" (o "MSVC 2022 64-bit"),
      * Qt Creator,
      * "CMake" y "Ninja" (vienen en la seccion Tools del instalador de Qt).
  - Descarga: https://www.qt.io/download-qt-installer
    (se requiere una cuenta gratuita de Qt para el instalador).

3.2 Compilar con Qt Creator (recomendado)
  1. Abrir Qt Creator y elegir File > Open File or Project.
  2. Seleccionar src/CMakeLists.txt.
  3. En la pantalla "Configure Project", marcar el kit de Qt 6
     (por ejemplo "Desktop Qt 6.x.x MinGW 64-bit") y pulsar Configure Project.
  4. En la parte inferior izquierda cambiar el modo de compilacion de Debug a
     Release (Projects > Build Settings > Add > Release, si no existe).
  5. Compilar con Ctrl+B y ejecutar con Ctrl+R.

3.3 Compilar desde la linea de comandos (alternativa)
  Abrir la terminal "Qt 6.x.x (MinGW 64-bit)" desde el menu Inicio y ejecutar,
  desde la carpeta src/ (ajustando la ruta de Qt si es distinta):

     cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release ^
           -DCMAKE_PREFIX_PATH=C:\Qt\6.12.0\mingw_64
     cmake --build build

  El ejecutable (Modex.exe) queda en la carpeta build/.

3.4 (Opcional) Ejecutar fuera de Qt Creator
  Para que Modex.exe abra con doble clic en un equipo sin Qt, copiarlo a una
  carpeta nueva y ejecutar, desde la terminal de Qt del mismo kit:

     windeployqt Modex.exe


4. USO DE LA APLICACION
-----------------------

Para subir un archivo de click en el botón add file, una vez cargado el archivo puede hacer click en el botón calculate y escoger el algoritmo que desea usar. Automaticamente se cargara la respuesta en el panel derecho y se guardara un archivo en el misma carpeta con el nombre del archivo de entrada mas out.

Formato de entrada (archivo de texto, n + 2 lineas):
   n
   opinion0, receptividad0, influencia0
   ...
   opinion(n-1), receptividad(n-1), influencia(n-1)
   R_max

Formato de salida (archivo de texto, n + 2 lineas):
   Extremismo de la red moderada
   Esfuerzo de la estrategia
   0 o 1 por cada agente (1 = agente moderado)

Los archivos de la carpeta casos/ siguen estos formatos y pueden cargarse
directamente desde la aplicacion. La fuerza bruta solo es practica hasta
n ~ 20 agentes.


5. NOTAS
--------
- Las funciones pedidas por el enunciado se llaman modexFB, modexV y modexPD y
  devuelven (estrategia, esfuerzo, extremismo).
- El esfuerzo de cada agente es el techo de |opinion| * (1 - receptividad) *
  influencia, calculado con la misma funcion en las tres soluciones.
