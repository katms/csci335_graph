class Graph[T](adjacencies: Map[T, Set[Edge[T]]]) {
    def this() = this(Map[T, Set[Edge[T]]]().withDefaultValue(Set.empty))
    
    val nodes = adjacencies.keySet
    val edgeCount = (adjacencies.valuesIterator.map(_.size)).sum
    
    override def toString = adjacencies.toString
}

class Edge[T](val n1: T, val n2: T, val weight: Int) {
    
}