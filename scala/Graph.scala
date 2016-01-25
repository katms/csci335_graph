// weighted, undirected
class Graph[T](adjacencies: Map[T, Set[Edge[T]]]) {
    def this() = this(Map[T, Set[Edge[T]]]().withDefaultValue(Set.empty))
    
    val nodes = adjacencies.keySet
    val edgeCount = (adjacencies.valuesIterator.map(_.size)).sum
    
    override def toString = adjacencies mkString "\n\n"
    
    def connect(node1: T, node2: T, weight: Int): Graph[T] = {
        // edges
        val edge1 = new Edge(node1, node2, weight)
        val edge2 = new Edge(node2, node1, weight)
        
        // adjacency lists
        val adj1 = adjacencies(node1)
        val adj2 = adjacencies(node2)
        
        new Graph(adjacencies.updated(node1, adj1+edge1).updated(node2, adj2+edge2))
    }
}

class Edge[T](val n1: T, val n2: T, val weight: Int) {
    override def toString = s"($n1, $n2): $weight"
    
    // return true if n1==n1 and n2==n2
    override def equals(that: Any): Boolean = that match {
        case other: Edge[T] => this.n1==other.n1 && this.n2==other.n2
        case _ => false
    }
}