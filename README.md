# Plan de Desarrollo del Proyecto miniRT

## FASE 1: Parseo
- **Iniciación de Estructuras**: Crear y definir las estructuras de datos necesarias para la escena, incluyendo cámaras, luces y objetos geométricos.
- **Integración**: Desarrollar un sistema que integre las diferentes partes del proyecto, permitiendo que trabajen juntas de manera eficiente.
- **Manejo de Errores**: Implementar un sistema robusto de manejo de errores para el proceso de parseo, asegurando estabilidad y facilidad de depuración.

## FASE 2: Cámara y Objetos
- **Movimientos Dinámicos de Cámara**: Permitir a los usuarios manipular la cámara en tiempo real para explorar la escena desde diferentes ángulos.
- **Interacción con Objetos**: Desarrollar la lógica para mover y alterar objetos en la escena, proporcionando una experiencia interactiva.

## FASE 3: Pantalla
- **Responsive Size Change**: Garantizar que la aplicación se ajuste dinámicamente a los cambios de tamaño de la ventana, manteniendo la calidad y proporciones de la imagen.

## FASE 4: Bonus List
1. **Specular Reflection**: Implementar la reflexión especular para añadir realismo a las superficies y mejorar la calidad visual de la escena.
2. **Color Disruption (Checker Board)**: Crear un efecto de tablero de ajedrez para texturas, añadiendo complejidad visual y detalle a los objetos.
3. **Colored and Multispot Lights**: Integrar luces de diferentes colores y múltiples fuentes de luz para enriquecer la iluminación de la escena y crear efectos más dinámicos.
4. **One Other 2nd Degree Object**: Incorporar objetos geométricos adicionales como conos, hiperboloides y paraboloides para diversificar las formas presentes en la escena.
5. **Handle Bump Map Textures**: Implementar texturas de bump mapping para simular relieve y textura en las superficies, aumentando el realismo de los objetos.


## Idea

### Reflexiones, Refracciones, y Efectos Avanzados
- Investigar y, si el tiempo lo permite, implementar efectos avanzados como reflexiones, refracciones, o texturas avanzadas.
## Técnicas para Acelerar el Renderizado

### Culling

El **culling** o recorte es una técnica que consiste en descartar objetos o partes de la escena que no contribuyen al resultado final antes de realizar cálculos complejos. Hay diferentes tipos de culling:

- **Back-face culling:** Se descartan las caras de los objetos que no están orientadas hacia la cámara, ya que no son visibles para el observador.
- **Frustum culling:** Se descartan los objetos que están fuera del campo de visión de la cámara, es decir, fuera del "frustum".

### Indexación Espacial

La **indexación espacial** involucra estructuras de datos como árboles BVH (Bounding Volume Hierarchies), rejillas (grids), y octrees, que organizan los objetos de la escena de manera que se pueda determinar rápidamente cuáles objetos son relevantes para un rayo específico. Esto reduce el número de intersecciones que necesitan ser calculadas.

- **Árboles BVH:** Dividen la escena en volúmenes delimitadores que encapsulan grupos de objetos, permitiendo descartar rápidamente muchos objetos con un mínimo de cálculos.
- **Rejillas:** Dividen la escena en una cuadrícula regular, y solo se consideran para el cálculo de intersecciones aquellos objetos que residen en las celdas atravesadas por un rayo.
- **Octrees:** Similar a los árboles BVH pero dividiendo el espacio en octantes, son especialmente útiles para escenas con una distribución espacial uniforme.
