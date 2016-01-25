class Graph[T](adjacencies: Map[T, Set[Edge[T]]]) {
    def this() = this(Map[T, Set[Edge[T]]]().withDefaultValue(Set.empty))
    
    override def toString = adjacencies.toString
}

class Edge[T](val n1: T, val n2: T, val weight: Int) {
    
}