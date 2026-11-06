###### **Autor: Jorge Augusto Blanco Fernández**



**La práctica consiste de 3 escenas diferentes. Se empieza en la escena 0 (vacía) y desde aquí se accederá al resto de escenas presionando las teclas 1, 2 y 3 respectivamente.**



**- Escena 1:** Torbellino con partículas girando a su alrededor. (Pulsar la tecla 'g' o 'G' para activar/desactivar la gravedad, y la tecla 'h' o 'H' para activar/desactivar el torbellino).



**- Escena 2:** Partículas flotando sin gravedad con una explosión en el origen. (Pulsar la tecla 'r' o 'R' para causar una nueva explosión, y la tecla 'g' o 'G' para activar/desactivar la gravedad de nuestros proyectiles).



**- Escena 3:** "Fuentes de agua" a cada lado de una diana a la que se puede intentar acertar disparando proyectiles. (Pulsar la tecla 'v' o 'V' para disparar una "bala", la tecla 'b' o 'B' para tirar una "pelota de baloncesto", y la tecla 'g' o 'G' para activar/desactivar la gravedad).



###### **Indicaciones de requisitos:**



**- Requisito A.1)** -> "Particle.cpp" 16-60.



**- Requisito A.2)** -> "Particle.cpp" 3-6 atributo masa, "Scene1.h" 37 y "Scene3.h" 38 definición de dos partículas de diferente masa.



**- Requisito A.3)** -> "ForceGenerator.cpp" 6 fuerza añadida, "Particle.h" 48 acumulación de fuerza, "Particle.cpp" 18 aceleración con respecto de la fuerza acumulada y la masa



**- Requisito B)** -> Clase implementada en "Projectile.h", "Scene3.h" 141-149 escalado del proyectil, "Scene3.h" 87-100 definición de dos proyectiles diferentes.



**- Requisito C)** -> Clase implementada en "ParticleForceRegistry.h" y "ParticleForceRegistry.cpp", utilizada en "ParticleSystem" como registro de las partículas y sus fuerzas.



**- Requisito D.1)** -> Clase implementada en "ParticleSystem.h", "Scene1.h" 37-41 definición de un sistema a partir de los atributos de una partícula, "ParticleSystem.cpp" 3-5 constructor del sistema, "ParticleSystem.cpp" 69-74 creación de una nueva partícula a partir de la partícula modelo.



**- Requisito D.2)** -> "Scene1.h" 39 definición de las desviaciones del sistema, "ParticleSystem.cpp" 6 - 10 definición de las distribuciones del generador a partir de las desviaciones indicadas.



**- Requisito D.3)** -> "ParticleSystem.cpp" 76-83 fuerza añadida al registro de fuerzas, "ParticleForceRegistry.cpp" 6 - 27 se añaden o se borran nuevos pares partícula-generador al registro.



**- Requisito E.1)** -> "ParticleSystem.cpp" 25-31 el sistema llama al registro de fuerzas, "ParticleForceRegistry.cpp" 29-34 el registro gestiona las fuerzas de cada partícula.



**- Requisito E.2)** -> "Scene1.h" 42-47 se asignan 2 generadores diferentes al sistema de partículas.



**- Requisito E.3)** -> "ParticleSystem.h" 38 registro de fuerzas, "Scene2.h" 38-42 la gravedad no afecta al sistema de partículas creado, "Scene1.h" 42-50 se utilizan los 2 mismos generadores para las partículas del huracán y las de la escena.



**- Requisito E.4)** -> "Whirlwind.h" clase generador de fuerzas de tornado que depende de la posición de la partícula con respecto al centro de éste, "Explosion.h" clase generador de fuerzas de explosión que depende del tiempo transcurrido.

