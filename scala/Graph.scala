// weighted, undirected
class Graph[T](adjacencies: Map[T, Set[Edge[T]]]) {
    def this() = this(Map[T, Set[Edge[T]]]().withDefaultValue(Set.empty))
    
    val nodes = adjacencies.keySet
    val edgeCount = (adjacencies.valuesIterator.map(_.size)).sum / 2
    
    val isMST = nodes.size == edgeCount+1
    
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
    
    // Prim's algorithm
    def MST(center: T): Graph[T] = {
        def iter(candidates: Set[Edge[T]], acc: Graph[T]): Graph[T] = {
            /*  if we have all the nodes
                or we're out of edges 
                because the original was not fully connected
                or because center wasn't found
                */
            if(acc.nodes==this.nodes || candidates.isEmpty) acc
            else {
                val min = candidates.min(Ordering.by[Edge[T], Int](_.weight))
                val newNode = min.n2
                val connected = acc.connect(min.n1, min.n2, min.weight)
                
                /*
                There are two types of redundant edges to be eliminated: 
                Edges with a greater weight that link to newNode
                Edges starting at newNode that lead to nodes already in the graph
                  Test for the latter using connected to catch a one-time case
                  where the second node's edge back to center isn't caught
                */
                val edges = (candidates.filterNot(_.n2==newNode)) ++ (adjacencies(newNode).filterNot(connected.nodes contains _.n2))
                iter(edges, connected)
            }
        }
        if(isMST) this
        else iter(adjacencies(center), new Graph[T])
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