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
            println(names.last)

            val graph = new Graph[Int]
            println(graph)
        }
    }
}