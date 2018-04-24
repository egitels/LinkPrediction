
.PHONY: runGraphOld
runGraphOld: $(wildcard *.h *.cpp)
	g++ -std=c++11 -o runGraph_old old_main.cpp DirectedWeightedGraph.cpp LinkedList.cpp -larmadillo

.PHONY: new
new: $(wildcard *.h *.cpp)
	g++ -std=c++11 -o runGraph_new -p main.cpp NetworkAlgorithms.cpp -larmadillo 


.PHONY: mymain
mymain: $(wildcard *.h *.cpp)
	g++ -std=c++11 -o mymain mymain.cpp NetworkAlgorithms.cpp -larmadillo

.PHONY: clean
clean:
	echo 'cleaning'
	rm runGraph_new
	rm runGraph_old
#
