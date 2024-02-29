
# Desarrollo de Proyecto miniRT

## Fase 1: Planificación y Diseño

### Investigación Preliminar
- Aprender sobre el trazado de rayos y sus principios fundamentales.
- Revisar la documentación de miniLibX y familiarizarse con sus capacidades.

### Diseño del Sistema
- Esquematizar la arquitectura general del programa.
- Definir las estructuras de datos para representar escenas, cámaras, luces, y objetos geométricos (esfera, plano, cilindro).

## Fase 2: Configuración del Entorno de Desarrollo

### Configuración de miniLibX
- Instalar y configurar miniLibX en el entorno de desarrollo.

### Configuración del Proyecto
- Crear la estructura básica del proyecto y el Makefile.
- Establecer un repositorio de versiones (por ejemplo, Git).

## Fase 3: Desarrollo del Core

### Renderizado de la Imagen
- Implementar la capacidad de crear una ventana y mostrar imágenes básicas.

### Interpretación de la Escena
- Desarrollar un parser para leer archivos .rt y cargar la configuración de la escena.

### Trazado de Rayos Básico
- Implementar el algoritmo de trazado de rayos para renderizar escenas simples sin iluminación.

## Fase 4: Implementación de Objetos y Luces

### Objetos Geométricos
- Implementar el cálculo de intersecciones para esferas, planos y cilindros.

### Sistema de Iluminación
- Añadir soporte para iluminación ambiental, difusa y especular.
- Implementar cálculo de sombras.

## Fase 5: Funcionalidades Avanzadas

### Transformaciones
- Permitir la traslación y rotación de objetos y cámaras.

### Optimización del Rendimiento
- Implementar técnicas para acelerar el renderizado, como el culling o la indexación espacial.

## Fase 6: Interfaz de Usuario y Experiencia

### Control de la Interfaz
- Implementar la funcionalidad para cerrar la ventana y salir del programa.
- Añadir controles básicos para manipular la vista o cambiar escenas.

## Fase 7: Pruebas y Depuración

### Pruebas Unitarias y de Integración
- Desarrollar pruebas para cada componente clave del sistema.

### Depuración
- Identificar y corregir errores y problemas de rendimiento.

## Fase 8: Documentación y Entrega

### Documentación
- Escribir documentación interna del código y guías de usuario.

### Preparación para la Entrega
- Revisar el cumplimiento de todos los requisitos del proyecto.
- Preparar el paquete final para la entrega.

## Fase 9: Bonificaciones (Opcional)

### Reflexiones, Refracciones, y Efectos Avanzados
- Investigar y, si el tiempo lo permite, implementar efectos avanzados como reflexiones, refracciones, o texturas avanzadas.
## Técnicas para Acelerar el Renderizado

El trazado de rayos es computacionalmente intensivo, por lo que se han desarrollado diversas técnicas para acelerar el proceso sin comprometer significativamente la calidad de la imagen resultante.

### Culling

El **culling** o recorte es una técnica que consiste en descartar objetos o partes de la escena que no contribuyen al resultado final antes de realizar cálculos complejos. Hay diferentes tipos de culling:

- **Back-face culling:** Se descartan las caras de los objetos que no están orientadas hacia la cámara, ya que no son visibles para el observador.
- **Frustum culling:** Se descartan los objetos que están fuera del campo de visión de la cámara, es decir, fuera del "frustum".

### Indexación Espacial

La **indexación espacial** involucra estructuras de datos como árboles BVH (Bounding Volume Hierarchies), rejillas (grids), y octrees, que organizan los objetos de la escena de manera que se pueda determinar rápidamente cuáles objetos son relevantes para un rayo específico. Esto reduce el número de intersecciones que necesitan ser calculadas.

- **Árboles BVH:** Dividen la escena en volúmenes delimitadores que encapsulan grupos de objetos, permitiendo descartar rápidamente muchos objetos con un mínimo de cálculos.
- **Rejillas:** Dividen la escena en una cuadrícula regular, y solo se consideran para el cálculo de intersecciones aquellos objetos que residen en las celdas atravesadas por un rayo.
- **Octrees:** Similar a los árboles BVH pero dividiendo el espacio en octantes, son especialmente útiles para escenas con una distribución espacial uniforme.

Estas técnicas pueden mejorar drásticamente la eficiencia del trazado de rayos, permitiendo la creación de imágenes complejas y detalladas en tiempos de renderizado razonables.
