object FindNames {
    def main(args: Array[String]): Unit = {
        if(args.length != 1) {
            println("Error: No input file provided")
        }
        else if(!(new java.io.File(args(0)).exists)) {
            println("Error: could not open file")
        }
        else {
            val names = io.Source.fromFile(args(0)).mkString.split("\r\n")
            
            // get all possible combinations
            val pairs = for{
                i <- 0 until names.length-1
                j <- i+1 until names.length
            } yield (names(i), names(j))
            
            // draw an edge between every pair of names with a levenshtein distance <= 4 as weight
            def collectToGraph(pairs: Seq[(String, String)]): Graph[String] = {
                def iter(pairsLeft: Seq[(String, String)], acc: Graph[String]): Graph[String] = {
                    if(pairsLeft.isEmpty) acc
                    else {
                        val (n1, n2) = pairsLeft.head
                        val dist = levenshtein(n1, n2)
                        if(dist <= 4) iter(pairsLeft.tail, acc.connect(n1, n2, dist))
                        else iter(pairsLeft.tail, acc)
                    }
                }
                iter(pairs, new Graph[String])
            }
            
            val graph = collectToGraph(pairs)
            println(graph)
            println("Nodes: "+graph.nodes.size)
            println("Edge: "+graph.edgeCount)
        }
    }
    
    // http://rosettacode.org/wiki/Levenshtein_distance#Scala
    def levenshtein(s1: String, s2: String): Int = {
      val dist=Array.tabulate(s2.length+1, s1.length+1){(j,i)=>if(j==0) i else if (i==0) j else 0}
 
      for(j<-1 to s2.length; i<-1 to s1.length)
         dist(j)(i) =  if(s2(j-1)==s1(i-1)) dist(j-1)(i-1)
	                   else List(dist(j-1)(i)+1, dist(j)(i-1)+1, dist(j-1)(i-1)+1).min
 
      dist(s2.length)(s1.length)
    }
}