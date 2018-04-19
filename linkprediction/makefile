
.PHONY: runGraphOld
runGraphOld: $(wildcard *.h *.cpp)
	g++ -std=c++11 -o runGraph_old old_main.cpp DirectedWeightedGraph.cpp LinkedList.cpp

.PHONY: runGraphNew
runGraphNew: $(wildcard *.h *.cpp)
	g++ -std=c++11 -o runGraph_new -p main.cpp NetworkAlgorithms.cpp    
 
.PHONY: clean
clean:
	echo 'cleaning'
	rm runGraph_new
	rm runGraph_old
#
