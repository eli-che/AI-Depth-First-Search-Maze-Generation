# Ai3
Labyrintgenerator med hjälp av Depth-First Search (DFS) algoritmen.
Labyrinten renderas grafiskt med GLFW.

Programmet initierar ett rutnät av celler, var och en med väggar på alla fyra sidor.
Det väljer slumpmässigt en startcell och markerar den som besökt.
Med DFS-algoritmen utforskar det iterativt obesökta intilliggande celler. När det
flyttar till en granne, tas väggen bort mellan den aktuella cellen och den valda
grannen, och sedan markeras grannen som besökt.
Algoritmen fortsätter tills alla celler är besökta, och backtrackar vid behov
