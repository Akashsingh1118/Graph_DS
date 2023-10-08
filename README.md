# Graph
General purpose graph library with several graph algorithms all at one place.
This graph library is designed with a modular and extensible architecture to facilitate the implementation of various graph-related algorithms.<br>
The structure of the project follows an object-oriented paradigm, with an abstract base class and two derived classes:

## Structure
1. Graph Class (Base Class)
   - The Graph class serves as an abstract base class, providing a fundamental structure for graph modeling.
   - It includes essential methods and attributes that are common to both directed and undirected graphs.
2. directedGraph Class (Derived Class)
   - The DirectedGraph class inherits from the Graph base class, extending and specializing the base class to model directed graphs.
   - Additional methods and properties specific to directed graphs are implemented in this class.
3. undirectedGraph Class (Derived Class)
   - The UndirectedGraph class also inherits from the Graph base class, catering to the modeling of undirected graphs.
   - It includes methods and properties tailored to the characteristics of undirected graphs.
